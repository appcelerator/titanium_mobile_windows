/**
 * Titanium.UI.ListView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/ListView.hpp"
#include "Titanium/UI/ListSection.hpp"
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Platform::Collections;
		using namespace Windows::UI::Xaml;

		ListView::ListView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::ListView(js_context)
		{
		}

		ListView::~ListView() 
		{
			clearListViewData();
		}

		void ListView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::ListView::postCallAsConstructor(js_context, arguments);	
			
			listview__ = ref new Controls::ListView();
			listview__->IsItemClickEnabled = true;

			resetListViewDataBinding();

			Titanium::UI::ListView::setLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(listview__);
		}

		void ListView::resetListViewDataBinding() 
		{
			collectionViewSource__ = ref new Data::CollectionViewSource();
			collectionViewItems__  = ref new Vector<Platform::Object^>();
			collectionViewSource__->Source = collectionViewItems__;
			collectionViewSource__->IsSourceGrouped = true;

			auto binding = ref new Data::Binding();
			binding->Source = collectionViewSource__;
			Data::BindingOperations::SetBinding(listview__, Controls::ListView::ItemsSourceProperty, binding);
		}

		void ListView::clearListViewData() 
		{
			for (const auto section : sections__) {
				unregisterListViewItemAsLayoutNode(section->get_headerView());
				unregisterListViewItemAsLayoutNode(section->get_footerView());
				const auto items = section->get_items();
				for (const auto item : items) {
					unregisterListViewItemAsLayoutNode(item.view);
				}
			}

			resetListViewDataBinding();
			collectionViewItems__->Clear();
			unfiltered_headers__.clear();
			unfiltered_sectionItems__.clear();

			for (const auto view : headerViews__) {
				unregisterListViewItemAsLayoutNode(view);
			}
			headerViews__.clear();
			for (const auto view : footerViews__) {
				unregisterListViewItemAsLayoutNode(view);
			}
			footerViews__.clear();
		}

		void ListView::JSExportInitialize() 
		{
			JSExport<ListView>::SetClassVersion(1);
			JSExport<ListView>::SetParent(JSExport<Titanium::UI::ListView>::Class());
		}

		/*
		 * Search for section index and item index
		 * TODO: Is there a better way to do this?
		 */
		std::tuple<std::uint32_t, std::int32_t> ListView::searchFromSelectedIndex(const std::uint32_t& selectedIndex) 
		{
			std::int32_t  itemIndex      = -1; // -1 means it's a header
			std::uint32_t sectionIndex   =  0;
			std::uint32_t totalItemCount =  0;
			for (sectionIndex = 0; sectionIndex < collectionViewItems__->Size; sectionIndex++) {
				const auto items = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
				totalItemCount += items->Size;
				if (totalItemCount < selectedIndex) {
					// we just count the total item
					continue;
				} else if (selectedIndex == 0) {
					// that's a first header
					break;
				} else if (totalItemCount == selectedIndex) {
					// this indicates header is selected
					itemIndex = -1;
					sectionIndex++;
					break;
				} else {
					// this indicates selected index is in this section
					itemIndex = selectedIndex - (totalItemCount - items->Size) - 1;
					break;
				}
			}
			return std::make_tuple(sectionIndex, itemIndex);
		}

		void ListView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			if (event_name == "itemclick") {
				itemclick_event__ = listview__->ItemClick += ref new Controls::ItemClickEventHandler(
					[this, ctx](Platform::Object^ sender, Controls::ItemClickEventArgs^ e) {
					auto listview = safe_cast<Controls::ListView^>(sender);

					uint32_t selectedIndex = -1;
					listview->Items->IndexOf(e->ClickedItem, &selectedIndex);
					if (selectedIndex == -1) return;

					const auto result = searchFromSelectedIndex(selectedIndex);
					const auto sectionIndex = std::get<0>(result);
					const auto itemIndex    = std::get<1>(result);
					const auto section      = sections__.at(sectionIndex);

					JSObject eventArgs = ctx.CreateObject();
					if (itemIndex >= 0) {
						TITANIUM_ASSERT(section->get_items().size() > static_cast<std::uint32_t>(itemIndex));
						const auto properties = section->getItemAt(itemIndex).properties;
						if (properties.find("itemId") != properties.end()) {
							eventArgs.SetProperty("itemId", properties.at("itemId"));
						}
						if (properties.find("bindId") != properties.end()) {
							eventArgs.SetProperty("bindId", properties.at("bindId"));
						}
					}
					eventArgs.SetProperty("section", section->get_object());
					eventArgs.SetProperty("sectionIndex", ctx.CreateNumber(sectionIndex));
					eventArgs.SetProperty("itemIndex", ctx.CreateNumber(itemIndex));
					this->fireEvent("itemclick", eventArgs);
				});
			}
		}

		void ListView::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::disableEvent(event_name);

			if (event_name == "itemclick") {
				listview__->ItemClick -= itemclick_event__;
			}
		}

		void ListView::set_searchText(const std::string& pretransform_searchText) TITANIUM_NOEXCEPT 
		{
			if (pretransform_searchText == searchText__) { // if value didn't change don't do any work
				return;
			}
			Titanium::UI::ListView::set_searchText(pretransform_searchText);

			if (is_filtering__) {
				return;
			}

			is_filtering__ = true;

			if (!pretransform_searchText.empty()) {
				auto searchText = pretransform_searchText;
				const bool case_insensitive = get_caseInsensitiveSearch();
				if (case_insensitive) {
					// Make searchText lowercase! Note that this likely _isn't_ UTF-8 friendly
					std::transform(searchText.begin(), searchText.end(), searchText.begin(), ::tolower);
				}
				// restore views and items so that we can search from entire items
				if (unfiltered_sectionItems__.size() > 0) {
					for (std::uint32_t sectionIndex = 0; sectionIndex < sections__.size(); sectionIndex++) {
						const auto section = sections__.at(sectionIndex);
						const auto items = unfiltered_sectionItems__.at(sectionIndex);
						if (items.size() > 0 && (section->get_items().size() != items.size())) {
							// save header view as it may be hidden according to the results
							restoreHeaderViewIfNecessary(sectionIndex);

							// restore section items without updating view
							section->set_items(items);
						}
					}
				}

				unfiltered_sectionItems__.clear();

				for (std::uint32_t sectionIndex = 0; sectionIndex < sections__.size(); sectionIndex++) {
					const auto section = sections__.at(sectionIndex);

					std::vector<Titanium::UI::ListDataItem> filtered_items;
					const auto items = section->get_items();

					// save "unfiltered" section items
					unfiltered_sectionItems__.push_back(items);

					for (std::uint32_t itemIndex = 0; itemIndex < items.size(); itemIndex++) {
						const auto item = items.at(itemIndex);
						const auto properties = item.properties;
						if (properties.find("searchableText") != properties.end()) {
							const auto text = properties.at("searchableText");
							TITANIUM_ASSERT(text.IsString());
							auto str = static_cast<std::string>(text);
							if (case_insensitive) {
								// make string lowercase! Note that this likely _isn't_ UTF-8 friendly
								std::transform(str.begin(), str.end(), str.begin(), ::tolower);
							}
							if (str.find(searchText) != std::string::npos) {
								// match, add item to filtered collection!
								filtered_items.push_back(item);
							}
						}
					}
					section->set_items(filtered_items);

					// hide header view when no items are found
					if (filtered_items.size() == 0) {
						hideHeaderView(sectionIndex);
					}
				}
			} else {
				// restore "unfiltered" section items
				for (std::uint32_t sectionIndex = 0; sectionIndex < sections__.size(); sectionIndex++) {
					const auto section = sections__.at(sectionIndex);
					const auto unfiltered_items = unfiltered_sectionItems__.at(sectionIndex);
					if (unfiltered_items.size() > 0 && (unfiltered_items.size() != section->get_items().size())) {
						restoreHeaderViewIfNecessary(sectionIndex);
						section->set_items(unfiltered_items);
					}
				}
				unfiltered_sectionItems__.clear();
			}

			is_filtering__ = false;
		}

		void ListView::hideHeaderView(const std::uint32_t& sectionIndex) 
		{
			TITANIUM_ASSERT(sections__.size() > sectionIndex);
			const auto section = sections__.at(sectionIndex);
			const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
			if (views->Size > 0 && views->Size != section->get_items().size()) {
				views->RemoveAt(0);
			}
		}

		// restore header view as it may be hidden according to the search results
		void ListView::restoreHeaderViewIfNecessary(const std::uint32_t& sectionIndex)
		{
			TITANIUM_ASSERT(sections__.size() > sectionIndex);
			const auto section = sections__.at(sectionIndex);
			const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
			if (views->Size == section->get_items().size()) {
				views->InsertAt(0, unfiltered_headers__.at(sectionIndex));
			}
		}

		void ListView::bindCollectionViewSource() 
		{
			collectionViewSource__->Source = collectionViewItems__;
		}

		void ListView::unbindCollectionViewSource()
		{
			collectionViewSource__->Source = ref new Vector<Platform::Object^>();
		}

		void ListView::appendSection(const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& sections, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			auto start = sections__.size();

			Titanium::UI::ListView::appendSection(sections, animation);

			// unbind collection view source to avoid exception
			unbindCollectionViewSource();

			for (std::uint32_t i = 0; i < sections.size(); i++) {
				const auto section = sections.at(i);
				const auto sectionIndex = start + i;
				collectionViewItems__->Append(createUIElementsForSection(sectionIndex));
				unfiltered_headers__.push_back(static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex))->GetAt(0));
			}

			// bind collection view again
			bindCollectionViewSource();
		}

		void ListView::deleteSectionAt(const uint32_t& sectionIndex, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::deleteSectionAt(sectionIndex, animation);

			// unbind collection view source to avoid exception
			unbindCollectionViewSource();

			collectionViewItems__->RemoveAt(sectionIndex);
			unfiltered_headers__.erase(unfiltered_headers__.begin() + sectionIndex);

			// bind collection view again
			bindCollectionViewSource();
		}

		void ListView::insertSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::insertSectionAt(sectionIndex, section, animation);

			// NOTE: reset all sections beucase collectionViewItems__->InsertAt() messed up views.
			// something to do with section.views JavaScript array maybe? Need to revisit.
			set_sections(sections__);
		}

		void ListView::replaceSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::replaceSectionAt(sectionIndex, section, animation);

			// NOTE: reset all sections beucase collectionViewItems__->InsertAt() messed up views. need to revisit.
			// something to do with section.views JavaScript array maybe? Need to revisit.
			set_sections(sections__);
		}

		void ListView::fireListSectionEvent(const std::string& name, const std::shared_ptr<Titanium::UI::ListSection>& section, const std::uint32_t& itemIndex, const std::uint32_t& itemCount, const std::uint32_t& affectedRows)
		{
			const std::uint32_t sectionIndex = std::distance(sections__.begin(), std::find(sections__.begin(), sections__.end(), section));
			if (sectionIndex < 0 || collectionViewItems__->Size <= sectionIndex) {
				return;
			}
			// this is list of view for the section including header view
			const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
			
			TITANIUM_ASSERT(views);

			if (name == "append") {
				for (std::uint32_t i = itemIndex; i < itemIndex + itemCount; i++) {
					const auto view = createSectionItemViewAt<TitaniumWindows::UI::View>(sectionIndex, i);
					appendListViewItemForSection(view, views);
					section->setViewForSectionItem(i, view);
				}
			} else if (name == "update" || name == "replace") {
				// "update" and "replace" are basically same, it removes existing content and insert new one
				std::uint32_t index = itemIndex + 1; // +1 because index=0 is header
				for (std::uint32_t i = index; i < index + affectedRows; i++) {
					views->RemoveAt(index);
					unregisterListViewItemAsLayoutNode(section->getViewForSectionItem(i - 1));
					section->setViewForSectionItem(i - 1, nullptr);
				}
				for (std::uint32_t i = itemIndex; i < itemIndex + itemCount; i++) {
					const auto view = createSectionItemViewAt<TitaniumWindows::UI::View>(sectionIndex, i);
					insertListViewItemForSection(view, views, index++);
					section->setViewForSectionItem(i, view);
				}
			} else if (name == "delete") {
				const std::uint32_t index = itemIndex + 1; // +1 because index=0 is header
				TITANIUM_ASSERT(views->Size > index);
				for (std::uint32_t i = index; i < index + itemCount; i++) {
					views->RemoveAt(index);
					unregisterListViewItemAsLayoutNode(section->getViewForSectionItem(i - 1));
					section->setViewForSectionItem(i - 1, nullptr);
				}
			} else if (name == "clear") {
				for (std::uint32_t i = itemIndex; i < itemIndex + itemCount; i++) {
					unregisterListViewItemAsLayoutNode(section->getViewForSectionItem(i));
					section->setViewForSectionItem(i, nullptr);
				}
				if (views->Size > 0) {
					// clear section view except header view
					const auto header = views->GetAt(0);
					views->Clear();
					views->Append(header);
				} else {
					views->Clear();
				}
			}
			Titanium::UI::ListView::fireListSectionEvent(name, section, itemIndex, itemCount, affectedRows);
		}

		Vector<UIElement^>^ ListView::createUIElementsForSection(const std::uint32_t& sectionIndex) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(sections__.size() > sectionIndex);
			auto group = ref new Vector<UIElement^>();

			const auto itemsCountToBeCreated = sections__.at(sectionIndex)->get_items().size();
			const auto views = createSectionViewAt<TitaniumWindows::UI::View>(sectionIndex);
			TITANIUM_ASSERT(views.size() == itemsCountToBeCreated);

			// set section header
			const auto section = sections__.at(sectionIndex);
			const auto headerView = section->get_headerView();
			if (headerView != nullptr) {
				const auto view = dynamic_cast<TitaniumWindows::UI::View*>(headerView.get());
				if (view == nullptr) {
					TITANIUM_LOG_ERROR("ListView: headerView must be of type Titanium.UI.View");
				} else {
					const auto component = view->getComponent();
					group->Append(component);

					// add as child view to make layout engine work
					registerListViewItemAsLayoutNode(headerView);
					headerViews__.push_back(headerView);
				}
			} else if (!section->get_headerTitle().empty()) {
				Controls::ListViewHeaderItem^ header = ref new Controls::ListViewHeaderItem();
				const auto headerText = ref new Controls::TextBlock();
				headerText->Text = Utility::ConvertUTF8String(section->get_headerTitle());
				headerText->FontSize = 28; // change this?
				header->Content = headerText;
				group->Append(header);
			}

			for (uint32_t itemIndex = 0; itemIndex < views.size(); itemIndex++) {
				const auto view = views.at(itemIndex);
				appendListViewItemForSection(view, group);
				section->setViewForSectionItem(itemIndex, view);
			}

			// set footer
			const auto footerView = section->get_footerView();
			if (footerView != nullptr) {
				const auto view = dynamic_cast<TitaniumWindows::UI::View*>(footerView.get());
				if (view == nullptr) {
					TITANIUM_LOG_ERROR("ListView: footerView must be of type Titanium.UI.View");
				} else {
					const auto component = view->getComponent();
					group->Append(component);

					// add as child view to make layout engine work
					registerListViewItemAsLayoutNode(footerView);
					footerViews__.push_back(footerView);
				}
			} else if (!section->get_footerTitle().empty()) {
				Controls::ListViewHeaderItem^ footer = ref new Controls::ListViewHeaderItem();
				const auto footerText = ref new Controls::TextBlock();
				footerText->Text = Utility::ConvertUTF8String(section->get_footerTitle());
				footerText->FontSize = 28; // change this?
				footer->Content = footerText;
				group->Append(footer);
			}

			return group;
		}

		void ListView::registerListViewItemAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view)
		{
			if (view == nullptr) {
				return;
			}
			auto layoutDelegate = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			Titanium::LayoutEngine::nodeAddChild(layoutDelegate->getLayoutNode(), view->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getLayoutNode());
		}

		void ListView::unregisterListViewItemAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view) 
		{
			if (view == nullptr) {
				return;
			}
			TITANIUM_LOG_DEBUG("ListView::unregisterListViewItemAsLayoutNode ", view.get(), " for ", this);
			auto layoutDelegate = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			Titanium::LayoutEngine::nodeRemoveChild(layoutDelegate->getLayoutNode(), view->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getLayoutNode());
		}

		void ListView::appendListViewItemForSection(const std::shared_ptr<TitaniumWindows::UI::View>& view, Vector<UIElement^>^ group)
		{
			group->Append(view->getComponent());
			registerListViewItemAsLayoutNode(view);
		}

		void ListView::insertListViewItemForSection(const std::shared_ptr<TitaniumWindows::UI::View>& view, Vector<UIElement^>^ group, const std::uint32_t& index) 
		{
			group->InsertAt(index, view->getComponent());
			registerListViewItemAsLayoutNode(view);
		}

		void ListView::set_sections(const std::vector<std::shared_ptr <Titanium::UI::ListSection>>& sections) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::set_sections(sections);

			clearListViewData();

			for (uint32_t sectionIndex = 0; sectionIndex < sections.size(); sectionIndex++) {
				collectionViewItems__->Append(createUIElementsForSection(sectionIndex));
				unfiltered_headers__.push_back(static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex))->GetAt(0));
			}
		}
	}  // namespace UI
}  // namespace TitaniumWindows