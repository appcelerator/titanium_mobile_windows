/**
 * Titanium.UI.ListView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/ListView.hpp"
#include "TitaniumWindows/UI/View.hpp"
#include <collection.h>
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		ListView::ListView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::ListView(js_context)
		{
		}

		void ListView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::ListView::postCallAsConstructor(js_context, arguments);	
			
			listview__ = ref new Windows::UI::Xaml::Controls::ListView();

			collectionViewSource__ = ref new Windows::UI::Xaml::Data::CollectionViewSource();
			collectionViewItems__  = ref new ::Platform::Collections::Vector<::Platform::Object^>();
			collectionViewSource__->Source = collectionViewItems__;
			collectionViewSource__->IsSourceGrouped = true;

			auto binding = ref new Windows::UI::Xaml::Data::Binding();
			binding->Source = collectionViewSource__;
			Windows::UI::Xaml::Data::BindingOperations::SetBinding(listview__, Windows::UI::Xaml::Controls::ListView::ItemsSourceProperty, binding);

			// Use "SelectionChanged" event to handle click event
			listview__->IsItemClickEnabled = false;

			listViewItems__ = ref new ::Platform::Collections::Vector<ListViewItem^>();

			Titanium::UI::ListView::setLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(listview__);
		}

		void ListView::JSExportInitialize() 
		{
			JSExport<ListView>::SetClassVersion(1);
			JSExport<ListView>::SetParent(JSExport<Titanium::UI::ListView>::Class());
		}

		void ListView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			if (event_name == "itemclick") {
				click_event__ = listview__->SelectionChanged += ref new Windows::UI::Xaml::Controls::SelectionChangedEventHandler(
					[this, ctx](::Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e) {
					if (is_filtering__) return; // setting the new filtered source will trigger this callback
					auto listview = safe_cast<Windows::UI::Xaml::Controls::ListView^>(sender);

					auto index = listview->SelectedIndex;
					TITANIUM_ASSERT((index < 0) || (static_cast<unsigned int>(index) < listViewItems__->Size));
					if (index == -1) {
						return;
					}
					auto uindex = static_cast<uint32_t>(index);
					
					TitaniumWindows::UI::ListViewItem^ listViewItem;
					if (get_searchText() != "") { // get mapped index when filtered
						auto real_index = filteredItems__.at(uindex);
						listViewItem = listViewItems__->GetAt(real_index);
					}
					else {
						listViewItem = listViewItems__->GetAt(uindex);
					}
					if (listViewItem->isHeader) return;

					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("sectionIndex", ctx.CreateNumber(listViewItem->SectionIndex));
					eventArgs.SetProperty("itemIndex", ctx.CreateNumber(listViewItem->ItemIndex));

					// TODO more properties
					this->fireEvent("itemclick", eventArgs);
				});
			}
		}

		void ListView::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::disableEvent(event_name);

			if (event_name == "itemclick") {
				listview__->ItemClick -= click_event__;
			}
		}
		// TODO We should really override the methods that modify sections and items in sections, so that we don't do unnecessary work rebuilding the filtered listing if the new item/s are filtered out!
		void ListView::set_searchText(const std::string& searchText) TITANIUM_NOEXCEPT {
			if (searchText == searchText__) { // if value didn't change don't do any work
				return;
			}
			Titanium::UI::ListView::set_searchText(searchText); // set field
			is_filtering__ = true;
			filteredItems__.clear();

			auto search = searchText;
			const bool filtering = (search != "");
			const bool case_insensitive = get_caseInsensitiveSearch();
			if (case_insensitive) {
				// Make searchText lowercase! Note that this likely _isn't_ UTF-8 friendly
				std::transform(search.begin(), search.end(), search.begin(), ::tolower);
			}

			// Let's build up a filtered listing
			auto filtered = ref new ::Platform::Collections::Vector<::Platform::Object^>();
			// We store all results in a single "group"/section with no header
			auto group = ref new ::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>();

			uint32_t listViewItemsIndex = 0; // Keep track of what index we correspond to in listViewItems__
			for (uint32_t sectionIndex = 0; sectionIndex < get_sectionCount(); sectionIndex++) {
				auto items = sections__[sectionIndex]->get_items();
				// if we're not filtering, we show the section's header, and we place results into groups/sections - not one single group of results
				if (!filtering) {
					group = ref new ::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>();
					group->Append(listViewItems__->GetAt(listViewItemsIndex)->View);
					filteredItems__.emplace_back(listViewItemsIndex);
				}

				listViewItemsIndex++; // there's headers in the listViewItems__ collection, so we need to bump up the index to skip them
				for (uint32_t itemIndex = 0; itemIndex < items.size(); itemIndex++) {
					if (filtering) {
						auto item = items[itemIndex];
						auto properties = item.properties;
						if (properties.find("searchableText") != properties.end()) {
							const auto text = properties.at("searchableText");
							TITANIUM_ASSERT(text.IsString());
							auto string = static_cast<std::string>(text);
							if (case_insensitive) {
								// make string lowercase! Note that this likely _isn't_ UTF-8 friendly
								std::transform(string.begin(), string.end(), string.begin(), ::tolower);
							}
							if (string.find(search) != std::string::npos) {
								// match, add item to filtered collection!
								group->Append(listViewItems__->GetAt(listViewItemsIndex)->View);
								filteredItems__.emplace_back(listViewItemsIndex);
							}
						}
					} else {
						group->Append(listViewItems__->GetAt(listViewItemsIndex)->View);
						filteredItems__.emplace_back(listViewItemsIndex);
					}
					listViewItemsIndex++; // record that we're moving on to the next item
				}
				// When no filter, append each original section/group
				if (!filtering) {
					filtered->Append(group);
				}
			}
			// We're actually filtering, so append the one and only group holding results
			if (filtering) {
				filtered->Append(group);
			}
			// Now let's tell the ListView to use the filtered listing
			collectionViewItems__ = filtered;
			collectionViewSource__->Source = collectionViewItems__;
			is_filtering__ = false;
		}

		void ListView::set_sections(const std::vector<ListSection_shared_ptr_t>& sections) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ListView::set_sections(sections);

			listViewItems__->Clear();
			collectionViewItems__->Clear();
			filteredItems__.clear();

			for (uint32_t sectionIndex = 0; sectionIndex < get_sectionCount(); sectionIndex++) {
				auto views = createSectionViewAt<TitaniumWindows::UI::View>(sectionIndex);
				auto group = ref new ::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>();

				// Set section header
				auto header_item = ref new ListViewItem();
				const auto section = sections[sectionIndex];
				auto view = section->get_headerView();
				if (view != nullptr) {
					auto windows_view = dynamic_cast<TitaniumWindows::UI::View*>(view.get());
					auto component = windows_view->getComponent();
					group->Append(component);
					header_item->View = component;

					// Add as child view to make layout engine work
					auto layoutDelegate = getViewLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>();
					Titanium::LayoutEngine::nodeAddChild(layoutDelegate->getLayoutNode(), view->getViewLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>()->getLayoutNode());
					if (layoutDelegate->isLoaded()) {
						layoutDelegate->requestLayout();
					}
				} else {
					Windows::UI::Xaml::Controls::ListViewHeaderItem^ header = ref new Windows::UI::Xaml::Controls::ListViewHeaderItem();
					auto headerText = ref new Windows::UI::Xaml::Controls::TextBlock();
					headerText->Text = Utility::ConvertUTF8String(section->get_headerTitle());
					headerText->FontSize = 28; // Change this?
					header->Content = headerText;
					group->Append(header);
				}

				// Create ListViewItem header placeholder to keep index mapping valid
				header_item->isHeader = true;
				listViewItems__->Append(header_item);

				for (uint32_t itemIndex = 0; itemIndex < views.size(); itemIndex++) {
					auto view = views.at(itemIndex);

					auto nativeChildView = view->getComponent();
					TITANIUM_ASSERT(nativeChildView);

					// Add as list item
					group->Append(nativeChildView);

					// Add as ListViewItem so that we can map item index
					auto item = ref new ListViewItem();
					item->View = nativeChildView;
					item->ItemIndex = itemIndex;
					item->SectionIndex = sectionIndex;
					listViewItems__->Append(item);

					// Add as child view to make layout engine work
					auto layoutDelegate = getViewLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>();
					Titanium::LayoutEngine::nodeAddChild(layoutDelegate->getLayoutNode(), view->getViewLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>()->getLayoutNode());
					if (layoutDelegate->isLoaded()) {
						layoutDelegate->requestLayout();
					}
				}

				collectionViewItems__->Append(group);
			}
		}
	}  // namespace UI
}  // namespace TitaniumWindows