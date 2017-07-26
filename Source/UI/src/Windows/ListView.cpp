/**
 * Titanium Windows Native Module - thin.listview
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#include "TitaniumWindows/UI/Windows/ListView.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/WindowsTiImpl.hpp"
#include "TitaniumWindows/UI/SearchBar.hpp"

using namespace Platform::Collections;
using namespace Windows::UI::Xaml;

namespace TitaniumWindows
{
	namespace UI
	{
		namespace WindowsXaml {
			ListView::ListView(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::UI::ListView(js_context)
			{

			}

			void ListView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
			{
				Titanium::UI::ListView::postCallAsConstructor(js_context, arguments);

				listview__ = ref new Controls::ListView();
				listview__->IsItemClickEnabled = true;
				listview__->SelectionMode = Controls::ListViewSelectionMode::None;

				resetData();

				parent__ = ref new Controls::Grid();
				parent__->Children->Append(listview__);
				parent__->SetColumn(listview__, 0);
				parent__->SetRow(listview__, 0);

				Titanium::UI::ListView::setLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>();
				layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
				layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
				layoutDelegate__->set_autoLayoutForHeight(Titanium::UI::LAYOUT::FILL);
				layoutDelegate__->set_autoLayoutForWidth(Titanium::UI::LAYOUT::FILL);

				getViewLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>()->setComponent(parent__, listview__);
			}

			void ListView::set_defaultItemTemplate(const std::string& defaultItemTemplate) TITANIUM_NOEXCEPT
			{
				Titanium::UI::ListView::set_defaultItemTemplate(defaultItemTemplate);
				const auto rd = ref new ResourceDictionary();
				rd->Source = ref new Windows::Foundation::Uri(listViewItemTemplateUri__);
				const auto key = TitaniumWindows::Utility::ConvertUTF8String(defaultItemTemplate);
				if (rd->HasKey(key)) {
					const auto itemTemplate = dynamic_cast<DataTemplate^>(rd->Lookup(key));
					if (itemTemplate) {
						listview__->ItemTemplate = itemTemplate;
					}
				}
			}

			void ListView::resetData()
			{
				const auto rd = ref new ResourceDictionary();
				rd->Source = ref new Windows::Foundation::Uri(listViewItemTemplateUri__);

				DataTemplate^ itemTemplate;
				if (rd->HasKey(defaultItemTemplate__)) {
					itemTemplate = dynamic_cast<DataTemplate^>(rd->Lookup(defaultItemTemplate__));
				}
				else {
					itemTemplate = dynamic_cast<DataTemplate^>(rd->First()->Current->Value);
				}

				if (itemTemplate == nullptr) {
					detail::ThrowRuntimeError("ListView", "Unable to get DataTemplate for ListView");
					return;
				}

				if (rd->HasKey(defaultGroupStyle__)) {
					listview__->GroupStyle->Append(dynamic_cast<Controls::GroupStyle^>(rd->Lookup(defaultGroupStyle__)));
				}
				listview__->ItemTemplate = itemTemplate;

				collectionViewSource__ = ref new Data::CollectionViewSource();
				collectionViewSource__->IsSourceGrouped = true;
				collectionViewItems__ = ref new Vector<ListViewModel::DataTemplateModelCollection^>();
				collectionViewSource__->Source = collectionViewItems__;

				const auto binding1 = ref new Data::Binding();
				binding1->Source = collectionViewSource__;
				Data::BindingOperations::SetBinding(listview__, Controls::ListView::ItemsSourceProperty, binding1);
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
					itemclick_event__ = listview__->ItemClick += ref new Controls::ItemClickEventHandler(
						[this, ctx](Platform::Object^ sender, Controls::ItemClickEventArgs^ e) {
						const auto item = dynamic_cast<ListViewModel::DataTemplateModel^>(e->ClickedItem);
						auto object = ctx.CreateObject();
						if (item) {
							auto propsObj = ctx.CreateObject();
							const auto properties = item->GetProperties();
							for (auto pair : properties) {
								propsObj.SetProperty(
									TitaniumWindows::Utility::ConvertUTF8String(pair->Key),
									ctx.CreateString(TitaniumWindows::Utility::ConvertUTF8String(pair->Value))
								);
							}
							object.SetProperty("properties", propsObj);
						}
						fireEvent("itemclick", object);
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
					const auto inputBox = searchBar->getViewLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>()->getComponent();

					parent__->Children->Append(inputBox);
					parent__->SetColumn(inputBox, 0);
					parent__->SetRow(inputBox, 0);

					parent__->Children->Append(listview__);
					parent__->SetColumn(listview__, 0);
					parent__->SetRow(listview__, 1);
				}
				else {
					parent__->Children->Append(listview__);
					parent__->SetColumn(listview__, 0);
					parent__->SetRow(listview__, 0);
				}

			}

			void ListView::scrollToItem(const uint32_t& sectionIndex, const uint32_t& itemIndex, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
			{
				if (collectionViewItems__->Size <= sectionIndex) {
					detail::ThrowRuntimeError("ListView::scrollToItem", "scrollToItem: Invalid argument supplied");
					return;
				}
				const auto items = collectionViewItems__->GetAt(sectionIndex);
				if (items->Size <= itemIndex) {
					detail::ThrowRuntimeError("ListView::scrollToItem", "scrollToItem: Invalid argument supplied");
					return;
				}
				listview__->ScrollIntoView(items->GetAt(itemIndex), Controls::ScrollIntoViewAlignment::Leading);
			}

			void ListView::fireListSectionEvent(const std::string& name, const std::shared_ptr<Titanium::UI::ListSection>& section, const std::uint32_t& itemIndex, const std::uint32_t& itemCount, const std::uint32_t& affectedRows)
			{
				const auto sectionIndex = model__->getSectionIndex(section);
				if (sectionIndex < 0 || collectionViewItems__->Size <= static_cast<std::uint32_t>(sectionIndex)) {
					return;
				}

				const auto items = collectionViewItems__->GetAt(sectionIndex);

				if (name == "append") {
					for (std::uint32_t i = itemIndex; i < itemIndex + itemCount; i++) {
						items->InsertAt(i, createDataModel(section->getItemAt(i)));
					}
				}
				else if (name == "update" || name == "replace") {
					// "update" and "replace" are basically same, it removes existing content and insert new one
					for (std::uint32_t i = itemIndex; i < itemIndex + affectedRows; i++) {
						items->SetAt(i, createDataModel(section->getItemAt(i)));
					}
				}
				else if (name == "delete") {
					items->RemoveAt(itemIndex);
				}
				else if (name == "clear") {
					// clear section view except header view
					items->Clear();
				}
				else if (name == "insert") {
					for (std::uint32_t i = itemIndex; i < itemIndex + itemCount; i++) {
						items->InsertAt(i, createDataModel(section->getItemAt(i)));
					}
				}
				Titanium::UI::ListView::fireListSectionEvent(name, section, itemIndex, itemCount, affectedRows);
			}

			void ListView::appendSection(const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& sections, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
			{
				Titanium::UI::ListView::appendSection(sections, animation);
				for (const auto section : sections) {
					collectionViewItems__->Append(createSectionModel(section));
				}
			}

			void ListView::deleteSectionAt(const uint32_t& sectionIndex, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
			{
				Titanium::UI::ListView::deleteSectionAt(sectionIndex, animation);
				collectionViewItems__->RemoveAt(sectionIndex);
			}

			void ListView::insertSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& sections, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
			{
				Titanium::UI::ListView::insertSectionAt(sectionIndex, sections, animation);
				auto start = sectionIndex;
				for (const auto section : sections) {
					collectionViewItems__->InsertAt(start, createSectionModel(section));
					start++;
				}
			}

			void ListView::replaceSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& sections, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
			{
				Titanium::UI::ListView::replaceSectionAt(sectionIndex, sections, animation);
				collectionViewItems__->RemoveAt(sectionIndex);
				auto start = sectionIndex;
				for (const auto section : sections) {
					collectionViewItems__->InsertAt(start, createSectionModel(section));
					start++;
				}
			}

			ListViewModel::DataTemplateModel^ ListView::createDataModel(const Titanium::UI::ListDataItem item)
			{
				const auto properties = item.properties;
				const auto model = ref new ListViewModel::DataTemplateModel();

				for (const auto prop : properties) {
					model->SetProperty(
						TitaniumWindows::Utility::ConvertUTF8String(prop.first),
						TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(prop.second)));
				}
				return model;
			}

			ListViewModel::DataTemplateModelCollection^ ListView::createSectionModel(const std::shared_ptr<Titanium::UI::ListSection>& section)
			{
				const auto sectionData = ref new ListViewModel::DataTemplateModelCollection();
				sectionData->Title = TitaniumWindows::Utility::ConvertUTF8String(section->get_headerTitle());
				for (std::size_t i = 0; i < section->get_itemCount(); i++) {
					sectionData->Append(createDataModel(section->getItemAt(i)));
				}

				return sectionData;
			}

			void ListView::set_sections(const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& sections) TITANIUM_NOEXCEPT
			{
				Titanium::UI::ListView::set_sections(sections);

				collectionViewItems__->Clear();

				auto enableGroupStyle = false;
				for (uint32_t sectionIndex = 0; sectionIndex < sections.size(); sectionIndex++) {
					const auto section = sections.at(sectionIndex);
					if (section->hasHeader())
					{
						enableGroupStyle = true;
					}
					section->get_object().SetProperty("listview", get_object());
					collectionViewItems__->Append(createSectionModel(section));
				}

				if (!enableGroupStyle) {
					listview__->GroupStyle->Clear();
				}
			}
		} // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
