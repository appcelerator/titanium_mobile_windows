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
#include "TitaniumWindows/WindowsTiImpl.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/SearchBar.hpp"
#include "TitaniumWindows/UI/SearchBar.hpp"

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
			if (listview__) {
				clearListViewData();
			}
		}

		void ListView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::ListView::postCallAsConstructor(js_context, arguments);	
			
			listview__ = ref new Controls::ListView();
			listview__->IsItemClickEnabled = true;
			listview__->SelectionMode = Controls::ListViewSelectionMode::None;

			// Since VisualTreeHelper is only available after Loaded event is fired, we need to register scroll/scrollend event after that.
			loaded_event__ = listview__->Loaded += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				scrollview__ = GetScrollView(Media::VisualTreeHelper::GetChild(listview__, 0));
				TITANIUM_ASSERT(scrollview__ != nullptr);
				if (hasEventListener("scrollstart")) {
					registerScrollstartEvent();
				}
				if (hasEventListener("scrolling")) {
					registerScrollingEvent();
				}
				if (hasEventListener("scrollend")) {
					registerScrollendEvent();
				}
				if (hasEventListener("marker")) {
					registerMarkerEvent();
				}

				checkMarkers();
			});

			resetListViewDataBinding();

			parent__ = ref new Controls::Grid();
			parent__->Children->Append(listview__);
			parent__->SetColumn(listview__, 0);
			parent__->SetRow(listview__, 0);

			Titanium::UI::ListView::setLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForWidth(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(parent__, listview__);
		}

		Controls::ScrollViewer^ ListView::GetScrollView(DependencyObject^ root)
		{
			const auto count = Media::VisualTreeHelper::GetChildrenCount(root);
			for (int i = 0; i < count; i++) {
				const auto child = Media::VisualTreeHelper::GetChild(root, i);
				const auto scrollview = dynamic_cast<Controls::ScrollViewer^>(child);
				if (scrollview) {
					return scrollview;
				} else {
					return ListView::GetScrollView(child);
				}
			}
			return nullptr;
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

		void ListView::unregisterSectionLayoutNode(const std::shared_ptr<Titanium::UI::ListSection>& section)
		{
			unregisterListViewItemAsLayoutNode(section->get_headerView());
			unregisterListViewItemAsLayoutNode(section->get_footerView());
			const auto items = section->get_items();
			for (const auto item : items) {
				unregisterListViewItemAsLayoutNode(item.view);
			}
		}
		void ListView::clearListViewData() 
		{
			for (const auto section : model__->get_sections()) {
				unregisterSectionLayoutNode(section);
			}

			resetListViewDataBinding();
		}

		void ListView::JSExportInitialize() 
		{
			JSExport<ListView>::SetClassVersion(1);
			JSExport<ListView>::SetParent(JSExport<Titanium::UI::ListView>::Class());
		}

		void ListView::updateScrollParams(const JSContext& ctx, JSObject params)
		{
			const auto itemsSize = listview__->Items->Size;
			const auto itemHeight = scrollview__->ExtentHeight / itemsSize;
			const auto visibleItemIndex = static_cast<std::size_t>(scrollview__->VerticalOffset / itemHeight);
			const auto visibleItemCount = static_cast<std::size_t>(scrollview__->ViewportHeight / itemHeight);

			const auto rowInfo = model__->searchRowBySelectedIndex(visibleItemIndex);

			params.SetProperty("visibleItemCount", ctx.CreateNumber(visibleItemCount));
			params.SetProperty("firstVisibleItemIndex", ctx.CreateNumber(rowInfo.rowIndex));
			params.SetProperty("firstVisibleSectionIndex", ctx.CreateNumber(rowInfo.sectionIndex));

			if (get_sectionCount() > rowInfo.sectionIndex) {
				const auto section = get_sections().at(rowInfo.sectionIndex);
				params.SetProperty("firstVisibleSection", section->get_object());
				if (section->get_itemCount() > rowInfo.rowIndex) {
					params.SetProperty("firstVisibleItem", ListDataItem_to_js(ctx, section->getItemAt(rowInfo.rowIndex)));
				}
			}
		}

		void ListView::checkMarkers()
		{
			const auto itemsSize = listview__->Items->Size;
			const auto itemHeight = scrollview__->ExtentHeight / itemsSize;
			const auto visibleItemIndex = static_cast<std::size_t>(scrollview__->VerticalOffset / itemHeight);
			const auto visibleItemCount = static_cast<std::size_t>(scrollview__->ViewportHeight / itemHeight);

			for (std::size_t i = visibleItemIndex; i < visibleItemIndex + visibleItemCount; i++) {
				const auto row = model__->searchRowBySelectedIndex(i);
				for (std::size_t m = 0; m < markers__.size(); m++) {
					auto marker = markers__.at(m);
					if (!marker.fired && marker.sectionIndex == row.sectionIndex && marker.itemIndex == row.rowIndex) {
						const auto ctx = get_context();
						auto eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("sectionIndex", ctx.CreateNumber(marker.sectionIndex));
						eventArgs.SetProperty("itemIndex", ctx.CreateNumber(marker.itemIndex));
						fireEvent("marker", eventArgs);
						marker.fired = true;
						markers__[m] = marker;
					}
				}
			}
		}

		void ListView::registerMarkerEvent()
		{
			marker_event__ = scrollview__->ViewChanged += ref new Windows::Foundation::EventHandler<Controls::ScrollViewerViewChangedEventArgs ^>([this](Platform::Object^ sender, Controls::ScrollViewerViewChangedEventArgs^ e) {
				checkMarkers();
			});
		}

		void ListView::registerScrollstartEvent()
		{
			scrollstart_event__ = scrollview__->ViewChanging += ref new Windows::Foundation::EventHandler<Controls::ScrollViewerViewChangingEventArgs ^>([this](Platform::Object^ sender, Controls::ScrollViewerViewChangingEventArgs^ e) {
				if (scrollstop__) {
					scrollstop__ = false;

					const auto ctx = get_context();
					auto eventArgs = ctx.CreateObject();

					updateScrollParams(ctx, eventArgs);

					fireEvent("scrollstart", eventArgs);
				}
			});
		}

		void ListView::registerScrollingEvent()
		{
			scrolling_event__ = scrollview__->ViewChanging += ref new Windows::Foundation::EventHandler<Controls::ScrollViewerViewChangingEventArgs ^>([this](Platform::Object^ sender, Controls::ScrollViewerViewChangingEventArgs^ e) {

				const auto ctx = get_context();
				auto eventArgs = ctx.CreateObject();

				updateScrollParams(ctx, eventArgs);

				fireEvent("scrolling", eventArgs);
			});
		}

		void ListView::registerScrollendEvent()
		{
			scrollend_event__ = scrollview__->ViewChanged += ref new Windows::Foundation::EventHandler<Controls::ScrollViewerViewChangedEventArgs ^>([this](Platform::Object^ sender, Controls::ScrollViewerViewChangedEventArgs^ e) {
				// Stop firing event when ScrollView didn't actually move
				if (!e->IsIntermediate && oldScrollPosX__ != scrollview__->VerticalOffset || oldScrollPosY__ != scrollview__->HorizontalOffset) {
					scrollstop__ = true;

					const auto ctx = get_context();
					auto eventArgs = ctx.CreateObject();

					updateScrollParams(ctx, eventArgs);

					fireEvent("scrollend", eventArgs);

					oldScrollPosX__ = scrollview__->VerticalOffset;
					oldScrollPosY__ = scrollview__->HorizontalOffset;
				}
			});
		}

		void ListView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			if (event_name == "itemclick") {
				itemclick_event__ = listview__->ItemClick += ref new Controls::ItemClickEventHandler(
					[this, ctx](Platform::Object^ sender, Controls::ItemClickEventArgs^ e) {
					TITANIUM_EXCEPTION_CATCH_START {
						auto listview = safe_cast<Controls::ListView^>(sender);

						uint32_t selectedIndex;
						const bool found = listview->Items->IndexOf(e->ClickedItem, &selectedIndex);
						if (!found) return;

						const auto result = model__->searchRowBySelectedIndex(selectedIndex);
						if (result.found) {
							const auto section = model__->getFilteredSectionAtIndex(result.sectionIndex);
							auto this_object = get_object();

							TITANIUM_ASSERT(section->get_items().size() > static_cast<std::uint32_t>(result.rowIndex));
							const auto properties = section->getItemAt(result.rowIndex).properties;
							if (properties.find("itemId") != properties.end()) {
								this_object.SetProperty("_itemclick_itemId_", properties.at("itemId"));
							}
							if (properties.find("bindId") != properties.end()) {
								this_object.SetProperty("_itemclick_bindId_", properties.at("bindId"));
							}
							// we just forward event properties to underlying view so that it can process itemclick event
							this_object.SetProperty("_itemclick_section_", section->get_object());
							this_object.SetProperty("_itemclick_sectionIndex_", ctx.CreateNumber(result.sectionIndex));
							this_object.SetProperty("_itemclick_itemIndex_", ctx.CreateNumber(result.rowIndex));
						}
						// hack: fallback when no view processes the event
						TitaniumWindows::Utility::RunOnUIThread([this]() {
							auto this_object = get_object();
							// this means no one catches the event
							if (this_object.HasProperty("_itemclick_section_")) {
								auto eventArgs = get_context().CreateObject();

								eventArgs.SetProperty("section", this_object.GetProperty("_itemclick_section_"));
								eventArgs.SetProperty("sectionIndex", this_object.GetProperty("_itemclick_sectionIndex_"));
								eventArgs.SetProperty("itemIndex", this_object.GetProperty("_itemclick_itemIndex_"));
								eventArgs.SetProperty("itemId", this_object.GetProperty("_itemclick_itemId_"));
								eventArgs.SetProperty("bindId", this_object.GetProperty("_itemclick_bindId_"));

								fireEvent("itemclick", eventArgs);

								this_object.DeleteProperty("_itemclick_section_");
								this_object.DeleteProperty("_itemclick_sectionIndex_");
								this_object.DeleteProperty("_itemclick_itemIndex_");
								this_object.DeleteProperty("_itemclick_itemId_");
								this_object.DeleteProperty("_itemclick_bindId_");
							}
						});
					} TITANIUMWINDOWS_EXCEPTION_CATCH_END
				});
			}
		}

		void ListView::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::disableEvent(event_name);

			if (event_name == "itemclick") {
				listview__->ItemClick -= itemclick_event__;
			} else if (event_name == "scrollstart") {
				if (scrollview__) {
					scrollview__->ViewChanging -= scrollstart_event__;
				}
			} else if (event_name == "scrolling") {
				if (scrollview__) {
					scrollview__->ViewChanged -= scrolling_event__;
				}
			} else if (event_name == "scrollend") {
				if (scrollview__) {
					scrollview__->ViewChanged -= scrollend_event__;
				}
			} else if (event_name == "marker") {
				if (scrollview__) {
					scrollview__->ViewChanged -= marker_event__;
				}

			}
		}

		void ListView::set_searchText(const std::string& query) TITANIUM_NOEXCEPT 
		{
			if (!model__->isSaved()) {
				model__->save();
			}

			querySubmitted(query);
		}

		void ListView::set_searchView(const std::shared_ptr<Titanium::UI::SearchBar>& search) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::set_searchView(search);

			parent__->Children->Clear();
			parent__->RowDefinitions->Clear();

			if (search) {
				const auto row1 = ref new Windows::UI::Xaml::Controls::RowDefinition();
				const auto row2 = ref new Windows::UI::Xaml::Controls::RowDefinition();

				row1->Height = GridLengthHelper::Auto;
				row2->Height = GridLengthHelper::FromValueAndType(1.0, GridUnitType::Star); // <RowDefinition Height="*"/>

				parent__->RowDefinitions->Append(row1);
				parent__->RowDefinitions->Append(row2);

				const auto searchBar = std::dynamic_pointer_cast<TitaniumWindows::UI::SearchBar>(search);
				const auto inputBox = searchBar->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();

				parent__->Children->Append(inputBox);
				parent__->SetColumn(inputBox, 0);
				parent__->SetRow(inputBox, 0);

				parent__->Children->Append(listview__);
				parent__->SetColumn(listview__, 0);
				parent__->SetRow(listview__, 1);
			} else {
				parent__->Children->Append(listview__);
				parent__->SetColumn(listview__, 0);
				parent__->SetRow(listview__, 0);
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
			auto start = model__->get_sectionCount();

			Titanium::UI::ListView::appendSection(sections, animation);

			// unbind collection view source to avoid exception
			unbindCollectionViewSource();

			for (std::uint32_t i = 0; i < sections.size(); i++) {
				const auto section = sections.at(i);
				const auto sectionIndex = start + i;
				collectionViewItems__->Append(createUIElementsForSection(sectionIndex));
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

			// bind collection view again
			bindCollectionViewSource();
		}

		void ListView::insertSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::insertSectionAt(sectionIndex, section, animation);

			// NOTE: reset all sections beucase collectionViewItems__->InsertAt() messed up views.
			// something to do with section.views JavaScript array maybe? Need to revisit.
			set_sections(model__->get_sections());
		}

		void ListView::replaceSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::replaceSectionAt(sectionIndex, section, animation);

			// NOTE: reset all sections beucase collectionViewItems__->InsertAt() messed up views. need to revisit.
			// something to do with section.views JavaScript array maybe? Need to revisit.
			set_sections(model__->get_sections());
		}

		void ListView::scrollToItem(const uint32_t& sectionIndex, const uint32_t& itemIndex, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			const auto items = listview__->Items;
			const auto sections = model__->get_sections();

			std::size_t index = 0;
			for (std::uint32_t i = 0; i < sections.size(); i++) {
				const auto section = sections.at(i);
				index += (section->hasHeader() ? 1 : 0);
				if (i == sectionIndex) {
					index += itemIndex;
					break;
				}
				index += section->get_itemCount() + (section->hasFooter() ? 1 : 0);
			}

			if (index < items->Size) {
				listview__->ScrollIntoView(items->GetAt(index));
			}
		}

		void ListView::fireListSectionEvent(const std::string& name, const std::shared_ptr<Titanium::UI::ListSection>& section, const std::uint32_t& itemIndex, const std::uint32_t& itemCount, const std::uint32_t& affectedRows)
		{
			const auto sectionIndex = model__->getSectionIndex(section);
			if (sectionIndex < 0 || collectionViewItems__->Size <= static_cast<std::uint32_t>(sectionIndex)) {
				return;
			}
			// this is list of view for the section including header view
			const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
			
			TITANIUM_ASSERT(views);

			std::uint32_t index = section->hasHeader() ? itemIndex + 1 : itemIndex;
			if (name == "append") {
				for (std::uint32_t i = itemIndex; i < itemIndex + itemCount; i++) {
					const auto view = createSectionItemViewAt<TitaniumWindows::UI::View>(sectionIndex, i);
					UIElement^ footer = nullptr;
					if (section->hasFooter()) {
						footer = views->GetAt(views->Size-1);
						views->RemoveAtEnd();
					}
					appendListViewItemForSection(view, views);
					if (footer) {
						views->Append(footer);
					}
					section->setViewForSectionItem(i, view);
				}
			} else if (name == "update" || name == "replace") {
				// "update" and "replace" are basically same, it removes existing content and insert new one
				for (std::uint32_t i = itemIndex; i < itemIndex + affectedRows; i++) {
					views->RemoveAt(index);
					unregisterListViewItemAsLayoutNode(section->getViewForSectionItem(i));
					section->setViewForSectionItem(i, nullptr);
				}
				for (std::uint32_t i = itemIndex; i < itemIndex + itemCount; i++) {
					const auto view = createSectionItemViewAt<TitaniumWindows::UI::View>(sectionIndex, i);
					insertListViewItemForSection(view, views, index++);
					section->setViewForSectionItem(i, view);
				}
			} else if (name == "delete") {
				TITANIUM_ASSERT(views->Size > index);
				for (std::uint32_t i = itemIndex; i < itemIndex + itemCount; i++) {
					views->RemoveAt(index);
					unregisterListViewItemAsLayoutNode(section->getViewForSectionItem(i));
					section->setViewForSectionItem(i, nullptr);
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
					if (section->hasHeader()) {
						views->Append(header);
					}
				} else {
					views->Clear();
				}
			} else if (name == "insert") {
				for (std::uint32_t i = itemIndex; i < itemIndex + itemCount; i++) {
					const auto view = createSectionItemViewAt<TitaniumWindows::UI::View>(sectionIndex, i);
					insertListViewItemForSection(view, views, index++);
					section->setViewForSectionItem(i, view);
				}
			}
			Titanium::UI::ListView::fireListSectionEvent(name, section, itemIndex, itemCount, affectedRows);
		}

		Vector<UIElement^>^ ListView::createUIElementsForSection(const std::uint32_t& sectionIndex) TITANIUM_NOEXCEPT
		{
			auto group = ref new Vector<UIElement^>();

			const auto section = model__->getSectionAtIndex(sectionIndex);
			const auto itemsCountToBeCreated = section->get_items().size();
			const auto views = createSectionViewAt<TitaniumWindows::UI::View>(sectionIndex);
			TITANIUM_ASSERT(views.size() == itemsCountToBeCreated);

			// set section header
			const auto headerView = section->get_headerView();
			if (headerView != nullptr) {
				const auto view_delegate = headerView->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
				if (view_delegate == nullptr) {
					TITANIUM_LOG_ERROR("ListView: headerView must be of type Titanium.UI.View");
				} else {
					if (view_delegate->get_height().empty()) {
						view_delegate->set_height(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE));
					}
					const auto component = view_delegate->getComponent();
					group->Append(component);

					// add as child view to make layout engine work
					registerListViewItemAsLayoutNode(headerView);
				}
			} else if (section->hasHeaderTitle()) {
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
				const auto view_delegate = footerView->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
				if (view_delegate == nullptr) {
					TITANIUM_LOG_ERROR("ListView: footerView must be of type Titanium.UI.View");
				} else {
					if (view_delegate->get_height().empty()) {
						view_delegate->set_height(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE));
					}
					const auto component = view_delegate->getComponent();
					group->Append(component);

					// add as child view to make layout engine work
					registerListViewItemAsLayoutNode(footerView);
				}
			} else if (section->hasFooterTitle()) {
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
			const auto layout = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			const auto view_layout = view->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			Titanium::LayoutEngine::nodeRemoveChild(layout->getLayoutNode(), view_layout->getLayoutNode());
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
			}
		}
	}  // namespace UI
}  // namespace TitaniumWindows