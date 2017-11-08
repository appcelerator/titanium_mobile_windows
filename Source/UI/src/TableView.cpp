/**
 * Titanium.UI.TableView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/TableView.hpp"
#include "TitaniumWindows/UI/TableViewRow.hpp"
#include "Titanium/UI/TableViewSection.hpp"
#include "Titanium/UI/SearchBar.hpp"
#include "TitaniumWindows/UI/SearchBar.hpp"
#include <collection.h>
#include <windows.h>
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include "TitaniumWindows/LogForwarder.hpp"
#include "TitaniumWindows/WindowsTiImpl.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace Platform::Collections;
		using namespace Windows::UI::Xaml;
		using namespace Windows::Foundation;

		TableView::TableView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::TableView(js_context)
		{
			TITANIUM_LOG_DEBUG("TableView::ctor Initialize");
		}

		TableView::~TableView()
		{
			tableview__->Loaded -= loaded_event__;
		}

		void TableView::resetTableDataBinding()
		{
			collectionViewSource__ = ref new Data::CollectionViewSource();
			collectionViewSource__->Source = collectionViewItems__;
			collectionViewSource__->IsSourceGrouped = true;

			auto binding = ref new Data::Binding();
			binding->Source = collectionViewSource__;
			Data::BindingOperations::SetBinding(tableview__, Controls::ListView::ItemsSourceProperty, binding);
		}

		void TableView::clearTableData() 
		{
			collectionViewItems__->Clear();
			resetTableDataBinding();
		}

		Controls::ScrollViewer^ TableView::GetScrollView(DependencyObject^ root)
		{
			const auto count = Media::VisualTreeHelper::GetChildrenCount(root);
			for (int i = 0; i < count; i++) {
				const auto child = Media::VisualTreeHelper::GetChild(root, i);
				const auto scrollview = dynamic_cast<Controls::ScrollViewer^>(child);
				if (scrollview) {
					return scrollview;
				} else {
					return TableView::GetScrollView(child);
				}
			}
			return nullptr;
		}

		void TableView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::TableView::postCallAsConstructor(js_context, arguments);

			parent__ = ref new Controls::Grid();
			tableview__ = ref new Controls::ListView();
			collectionViewItems__ = ref new Vector<Platform::Object^>();
			separatorBrush__ = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Transparent);

			// TIMOB-25273: Remove default padding
			auto itemStyle = ref new Windows::UI::Xaml::Style(Controls::ListViewItem::typeid);
			itemStyle->Setters->Append(ref new Setter(Controls::ListViewItem::PaddingProperty, Windows::UI::Xaml::Thickness(0)));
			tableview__->ItemContainerStyle = itemStyle;

			resetTableDataBinding();

			tableview__->IsItemClickEnabled = true;
			tableview__->SelectionMode = Controls::ListViewSelectionMode::None;

			// Since VisualTreeHelper is only available after Loaded event is fired, we need to register scroll/scrollend event after that.
			loaded_event__ = tableview__->Loaded += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				try {
					scrollview__ = GetScrollView(Media::VisualTreeHelper::GetChild(tableview__, 0));
					TITANIUM_ASSERT(scrollview__ != nullptr);
					if (hasEventListener("scroll")) {
						registerScrollEvent();
					}
					if (hasEventListener("scrollend")) {
						registerScrollendEvent();
					}
				} catch (...) {
					TITANIUM_LOG_DEBUG("Error at TableView::Loaded");
				}
			});

			parent__->Children->Append(tableview__);
			parent__->SetColumn(tableview__, 0);
			parent__->SetRow(tableview__, 0);

			Titanium::UI::TableView::setLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForWidth(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(parent__, tableview__);
		}

		void TableView::JSExportInitialize() 
		{
			JSExport<TableView>::SetClassVersion(1);
			JSExport<TableView>::SetParent(JSExport<Titanium::UI::TableView>::Class());
		}

		void TableView::querySubmitted(const std::string& query)
		{
			// Make sure to update UI from UI thread
			TitaniumWindows::Utility::RunOnUIThread([this, query]() {
				Titanium::UI::TableView::querySubmitted(query);
			});
		}

		// unregister all rows in section from LayoutEngine
		void TableView::unregisterSectionLayoutNode(const std::shared_ptr<Titanium::UI::TableViewSection>& section)
		{
			unregisterTableViewRowAsLayoutNode(section->get_headerView());
			unregisterTableViewRowAsLayoutNode(section->get_footerView());
			for (const auto row : section->get_rows()) {
				unregisterTableViewRowAsLayoutNode(row);
			}
		}

		// unregister all rows from LayoutEngine
		void TableView::unregisterSections() 
		{
			for (const auto section : model__->get_sections()) {
				unregisterSectionLayoutNode(section);
			}
			collectionViewItems__->Clear();
		}

		void TableView::setTableHeader()
		{
			auto headerView = get_headerView();
			if (headerView != nullptr) {
				const auto view_delegate = headerView->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
				if (view_delegate == nullptr) {
					TITANIUM_LOG_ERROR("TableView: headerView must be of type Titanium.UI.View");
				} else {
					if (view_delegate->get_height().empty()) {
						view_delegate->set_height(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE));
					}

					// Header width should be always FILL regardless of value
					view_delegate->set_width(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));

					tableview__->Header = view_delegate->getComponent();
					// Add as child view to make layout engine work
					registerTableViewRowAsLayoutNode(headerView);
				}
			} else if (hasHeader()) {
				tableview__->Header = createDefaultHeader();
			}
		}

		void TableView::setTableFooter()
		{
			auto footerView = get_footerView();
			if (footerView != nullptr) {
				const auto view_delegate = footerView->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
				if (view_delegate == nullptr) {
					TITANIUM_LOG_ERROR("TableView: footerView must be of type Titanium.UI.View");
				} else {
					if (view_delegate->get_height().empty()) {
						view_delegate->set_height(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE));
					}
					tableview__->Footer = view_delegate->getComponent();
					// Add as child view to make layout engine work
					registerTableViewRowAsLayoutNode(footerView);
				}
			} else if (hasFooter()) {
				tableview__->Footer = createDefaultFooter();
			}
		}

		void TableView::set_headerView(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			if (propertiesSet__) {
				unregisterSections();
				Titanium::UI::TableView::set_headerView(view);
				createTableSectionUIElements();
			} else {
				Titanium::UI::TableView::set_headerView(view);
			}
		}

		void TableView::set_headerTitle(const std::string& title) TITANIUM_NOEXCEPT
		{
			if (propertiesSet__) {
				unregisterSections();
				Titanium::UI::TableView::set_headerTitle(title);
				createTableSectionUIElements();
			} else {
				Titanium::UI::TableView::set_headerTitle(title);
			}
		}

		void TableView::set_data(const std::vector<JSObject>& data) TITANIUM_NOEXCEPT
		{
			if (propertiesSet__) {
				unregisterSections();
				Titanium::UI::TableView::set_data(data);
				createTableSectionUIElements();
			} else {
				Titanium::UI::TableView::set_data(data);
			}
		}

		void TableView::set_sections(const std::vector<std::shared_ptr<Titanium::UI::TableViewSection>>& sections) TITANIUM_NOEXCEPT
		{
			if (propertiesSet__) {
				unregisterSections();
				Titanium::UI::TableView::set_sections(sections);
				createTableSectionUIElements();
			} else {
				Titanium::UI::TableView::set_sections(sections);
			}
		}

		void TableView::set_search(const std::shared_ptr<Titanium::UI::SearchBar>& search) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::set_search(search);

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

				parent__->Children->Append(tableview__);
				parent__->SetColumn(tableview__, 0);
				parent__->SetRow(tableview__, 1);
			} else {
				parent__->Children->Append(tableview__);
				parent__->SetColumn(tableview__, 0);
				parent__->SetRow(tableview__, 0);
			}
		}

		void TableView::afterPropertiesSet() TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::afterPropertiesSet();
			createTableSectionUIElements();
		}

		void TableView::createTableSectionUIElements() TITANIUM_NOEXCEPT
		{
			clearTableData();
			setTableHeader();
			setTableFooter();
			for (uint32_t i = 0; i < model__->get_sectionCount(); i++) {
				collectionViewItems__->Append(createUIElementsForSection(i));
			}
		}

		void TableView::createEmptyTableViewSection()
		{
			Titanium::UI::TableView::createEmptyTableViewSection();
			collectionViewItems__->Append(createUIElementsForSection(0));
		}

		Vector<UIElement^>^ TableView::createUIElementsForSection(const std::uint32_t& sectionIndex) TITANIUM_NOEXCEPT
		{
			const auto section = model__->getSectionAtIndex(sectionIndex);
			const auto rows    = section->get_rows();
			auto group = ref new Vector<UIElement^>();

			// attach table view to this section so it receives callback
			section->attachTableView(get_object().GetPrivate<TitaniumWindows::UI::TableView>());

			// Set section header
			auto headerView = section->get_headerView();
			if (headerView != nullptr) {
				const auto view_delegate = headerView->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
				if (view_delegate == nullptr) {
					TITANIUM_LOG_ERROR("TableView: headerView must be of type Titanium.UI.View");
				} else {
					if (view_delegate->get_height().empty()) {
						view_delegate->set_height(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE));
					}
					group->Append(view_delegate->getComponent());
					// Add as child view to make layout engine work
					registerTableViewRowAsLayoutNode(headerView);
				}
			} else if (section->hasHeader()) {
				group->Append(createDefaultHeader(section));
			}

			for (uint32_t i = 0; i < rows.size(); i++) {
				auto row = rows.at(i);
				auto view = row->get_object().GetPrivate<TitaniumWindows::UI::TableViewRow>();
				auto rowContent = view->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
				TITANIUM_ASSERT(rowContent);

				const auto panel = ref new Windows::UI::Xaml::Controls::StackPanel();
				panel->Children->Append(rowContent);
				const auto line = ref new Windows::UI::Xaml::Shapes::Line();
				line->Stretch = Windows::UI::Xaml::Media::Stretch::Fill;
				line->Stroke = separatorBrush__;
				line->X2 = 1;
				panel->Children->Append(line);
				group->Append(panel);

				// Add as child view to make layout engine work
				registerTableViewRowAsLayoutNode(view);
			}

			// set section footer
			auto footerView = section->get_footerView();
			if (footerView != nullptr) {
				const auto view_delegate = footerView->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
				if (view_delegate == nullptr) {
					TITANIUM_LOG_ERROR("TableView: footerView must be of type Titanium.UI.View");
				} else {
					if (view_delegate->get_height().empty()) {
						view_delegate->set_height(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE));
					}
					group->Append(view_delegate->getComponent());
					registerTableViewRowAsLayoutNode(footerView);
				}
			} else if (section->hasFooter()) {
				group->Append(createDefaultFooter(section));
			}

			return group;
		}

		void TableView::set_separatorColor(const std::string& color) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::set_separatorColor(color);
			separatorBrush__ = ref new Windows::UI::Xaml::Media::SolidColorBrush(getViewLayoutDelegate<WindowsViewLayoutDelegate>()->ColorForName(color));

			unbindCollectionViewSource();
			for (size_t g = 0; g < collectionViewItems__->Size; g++) {
				const auto group = reinterpret_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(g));
				if (group->Size == 0) {
					continue;
				}
				const auto section = model__->getSectionAtIndex(g);
				const auto startIndex = section->hasHeader() ? 1 : 0;
				for (size_t i = startIndex; i < group->Size - 1; i++) {
					const auto panel = reinterpret_cast<Windows::UI::Xaml::Controls::StackPanel^>(group->GetAt(i));
					const auto line = reinterpret_cast<Windows::UI::Xaml::Shapes::Line^>(panel->Children->GetAt(1));
					line->Stroke = separatorBrush__;
				}
			}
			bindCollectionViewSource();
		}

		void TableView::updateSection(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::updateSection(index, section, animation);
			unbindCollectionViewSource();

			// Make sure to unregister rows from LayoutEngine
			unregisterSectionLayoutNode(section);

			collectionViewItems__->SetAt(index, createUIElementsForSection(index));

			bindCollectionViewSource();
		}

		void TableView::appendSection(const std::vector<std::shared_ptr<Titanium::UI::TableViewSection>>& sections, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			const auto startSectionIndex = model__->get_sectionCount();

			Titanium::UI::TableView::appendSection(sections, animation);
			unbindCollectionViewSource();

			for (std::uint32_t i = 0; i < sections.size(); i++) {
				collectionViewItems__->Append(createUIElementsForSection(startSectionIndex + i));
			}

			bindCollectionViewSource();
		}

		void TableView::deleteSection(const uint32_t& sectionIndex, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			auto section = model__->getSectionAtIndex(sectionIndex);

			Titanium::UI::TableView::deleteSection(sectionIndex, animation);
			unbindCollectionViewSource();

			unregisterSectionLayoutNode(section);

			collectionViewItems__->RemoveAt(sectionIndex);

			bindCollectionViewSource();

		}

		void TableView::insertSectionAfter(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::insertSectionAfter(index, section, animation);
			unbindCollectionViewSource();
			collectionViewItems__->InsertAt(index + 1, createUIElementsForSection(index + 1));
			bindCollectionViewSource();
		}

		void TableView::insertSectionBefore(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::insertSectionBefore(index, section, animation);
			unbindCollectionViewSource();
			collectionViewItems__->InsertAt(index, createUIElementsForSection(index));
			bindCollectionViewSource();
		}

		Controls::ListViewHeaderItem^ TableView::createDefaultHeader(const std::shared_ptr<Titanium::UI::TableViewSection>& section) 
		{
			Controls::ListViewHeaderItem^ header = ref new Controls::ListViewHeaderItem();
			auto headerText = ref new Controls::TextBlock();
			headerText->Text = Utility::ConvertUTF8String(section ? section->get_headerTitle() : get_headerTitle());
			headerText->FontSize = 28; // Change this?
			header->Content = headerText;
			return header;
		}

		Controls::ListViewHeaderItem^ TableView::createDefaultFooter(const std::shared_ptr<Titanium::UI::TableViewSection>& section)
		{
			Controls::ListViewHeaderItem^ footer = ref new Controls::ListViewHeaderItem();
			auto footerText = ref new Controls::TextBlock();
			footerText->Text = Utility::ConvertUTF8String(section ? section->get_footerTitle() : get_footerTitle());
			footerText->FontSize = 28; // Change this?
			footer->Content = footerText;
			return footer;
		}

		// Add as child view to make layout engine work
		void TableView::registerTableViewRowAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view)
		{
			auto layoutDelegate = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			Titanium::LayoutEngine::nodeAddChild(layoutDelegate->getLayoutNode(), view->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getLayoutNode());
		}

		// Remove child view 
		void TableView::unregisterTableViewRowAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view)
		{
			if (view == nullptr) {
				return;
			}
			const auto layout      = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			const auto view_layout = view->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			if (layout && view_layout) {
				Titanium::LayoutEngine::nodeRemoveChild(layout->getLayoutNode(), view_layout->getLayoutNode());
			}
		}

		void TableView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->filterEvents({ "click", "touchmove" });

			Titanium::UI::TableView::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			if (event_name == "click") {
				click_event__ = tableview__->ItemClick += ref new Controls::ItemClickEventHandler(
					[this, ctx](Platform::Object^ sender, Controls::ItemClickEventArgs^ e) {
					try {
						if (model__->empty()) {
							TITANIUM_LOG_DEBUG("TableView is clicked but there's no data");
							return;
						}

						const auto listview = safe_cast<Controls::ListView^>(sender);

						uint32_t selectedIndex;
						const auto found = listview->Items->IndexOf(e->ClickedItem, &selectedIndex);
						if (!found) return;

						const auto result = model__->searchRowBySelectedIndex(selectedIndex);

						if (result.found) {
							JSObject  eventArgs = ctx.CreateObject();
							eventArgs.SetProperty("sectionIndex", ctx.CreateNumber(result.sectionIndex));
							eventArgs.SetProperty("index", ctx.CreateNumber(result.rowIndex));

							const auto section = model__->getFilteredSectionAtIndex(result.sectionIndex);
							const auto row = section->get_rows().at(result.rowIndex);
							eventArgs.SetProperty("row", row->get_object());
							eventArgs.SetProperty("rowData", row->get_data());
							eventArgs.SetProperty("source", row->get_object());

							fireEvent("click", eventArgs);
						}
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error At TableView.click");
					}
				});
			} else if (event_name == "scroll") {
				// This means addEventListener is called after ListView.Loaded event.
				if (scrollview__) {
					registerScrollEvent();
				}
			} else if (event_name == "scrollend") {
				// This means addEventListener is called after ListView.Loaded event.
				if (scrollview__) {
					registerScrollendEvent();
				}
			} else if (event_name == "touchmove") {
				touchmove_event__ = tableview__->PointerMoved += ref new Input::PointerEventHandler([this](Platform::Object^, Input::PointerRoutedEventArgs^ e) {
					try {
						const auto ctx = get_context();
						JSObject  eventArgs = ctx.CreateObject();

						const auto position = e->GetCurrentPoint(tableview__)->Position;
						eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
						eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

						fireEvent("touchmove", eventArgs);
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error at TableView.touchmove");
					}
				});
			}
		}

		void TableView::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::disableEvent(event_name);

			if (event_name == "click") {
				tableview__->ItemClick -= click_event__;
			} else if (event_name == "scroll") {
				if (scrollview__) {
					scrollview__->ViewChanging -= scroll_event__;
				}
			} else if (event_name == "scrollend") {
				if (scrollview__) {
					scrollview__->ViewChanged -= scrollend_event__;
				}
			} else if (event_name == "touchmove") {
				tableview__->PointerMoved -= touchmove_event__;
			}
		}

		void TableView::registerScrollEvent()
		{
			scroll_event__ = scrollview__->ViewChanging += ref new EventHandler<Controls::ScrollViewerViewChangingEventArgs ^>([this](Platform::Object^ sender, Controls::ScrollViewerViewChangingEventArgs^ e) {
				try {
					const auto ctx = get_context();
					auto eventArgs = ctx.CreateObject();

					auto size = ctx.CreateObject();
					size.SetProperty("width", ctx.CreateNumber(scrollview__->ViewportWidth));
					size.SetProperty("height", ctx.CreateNumber(scrollview__->ViewportHeight));
					eventArgs.SetProperty("size", size);

					eventArgs.SetProperty("totalItemCount", ctx.CreateNumber(tableview__->Items->Size));

					fireEvent("scroll", eventArgs);
				} catch (...) {
					TITANIUM_LOG_DEBUG("Error at TableView.scroll");
				}
			});
		}

		void TableView::registerScrollendEvent()
		{
			scrollend_event__ = scrollview__->ViewChanged += ref new EventHandler<Controls::ScrollViewerViewChangedEventArgs ^>([this](Platform::Object^ sender, Controls::ScrollViewerViewChangedEventArgs^ e) {
				try {
					// Stop firing event when ScrollView didn't actually move
					if (oldScrollPosX__ != scrollview__->VerticalOffset || oldScrollPosY__ != scrollview__->HorizontalOffset) {
						const auto ctx = get_context();
						auto eventArgs = ctx.CreateObject();

						auto size = ctx.CreateObject();
						size.SetProperty("width", ctx.CreateNumber(scrollview__->ViewportWidth));
						size.SetProperty("height", ctx.CreateNumber(scrollview__->ViewportHeight));
						eventArgs.SetProperty("size", size);

						fireEvent("scrollend", eventArgs);

						oldScrollPosX__ = scrollview__->VerticalOffset;
						oldScrollPosY__ = scrollview__->HorizontalOffset;
					}
				} catch (...) {
					TITANIUM_LOG_DEBUG("Error at TableView.scrollend");
				}
			});
		}

		void TableView::bindCollectionViewSource()
		{
			collectionViewSource__->Source = collectionViewItems__;
		}

		void TableView::unbindCollectionViewSource()
		{
			collectionViewSource__->Source = ref new Vector<Platform::Object^>();
		}

		std::uint32_t TableView::getRowIndexInCollectionView(const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::uint32_t& rowIndex) TITANIUM_NOEXCEPT
		{
			return rowIndex + /* +1 to skip section header */ (section->hasHeader() ? 1 : 0);
		}

		void TableView::fireTableViewSectionEvent(const std::string& name, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewRow>& row, const std::uint32_t& rowIndex, const std::shared_ptr<Titanium::UI::TableViewRow>& old_row)
		{
			const std::uint32_t sectionIndex = model__->getSectionIndex(section);
			TITANIUM_ASSERT(collectionViewItems__->Size > sectionIndex);

			if (name == "append") {
				unbindCollectionViewSource();
				const auto rowIndexInCollectionView = getRowIndexInCollectionView(section, rowIndex);
				const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
				const auto rowContent = row->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
				TITANIUM_ASSERT(rowContent);
				if (views->Size > rowIndexInCollectionView) {
					views->InsertAt(rowIndexInCollectionView, rowContent);
				} else {
					views->Append(rowContent);
				}
				registerTableViewRowAsLayoutNode(row);
				bindCollectionViewSource();
			} else if (name == "remove") {
				unbindCollectionViewSource();
				const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
				views->RemoveAt(getRowIndexInCollectionView(section, rowIndex));
				unregisterTableViewRowAsLayoutNode(row);
				bindCollectionViewSource();
			} else if (name == "update") {
				TITANIUM_ASSERT(old_row != nullptr);
				// copy existing properties when given row is already added to section
				if (row->get_added()) {
					auto ctor   = get_context().CreateObject(JSExport<TitaniumWindows::UI::TableViewRow>::Class());
					auto new_row = ctor.CallAsConstructor().GetPrivate<TitaniumWindows::UI::TableViewRow>();
					new_row->applyProperties(row->get_data(), new_row->get_object());
					updateRow(rowIndex, new_row, nullptr);
				} else {
					unbindCollectionViewSource();
					unregisterTableViewRowAsLayoutNode(old_row);

					const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
					const auto rowContent = row->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
					views->SetAt(getRowIndexInCollectionView(section, rowIndex), rowContent);
					registerTableViewRowAsLayoutNode(row);
					bindCollectionViewSource();
				}
			} else {
				TITANIUM_LOG_WARN("TableView: Unknown TableViewSectionEvent: ", name);
			}

			Titanium::UI::TableView::fireTableViewSectionEvent(name, section, row, rowIndex, old_row);
		}

		void TableView::scrollToIndex(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			// On Windows the top value is interpreted as a row index
			const auto result = searchRowByIndex(index);

			if (result.found) {
				auto rows = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(result.sectionIndex));
				tableview__->ScrollIntoView(rows->GetAt(result.rowIndex));
			} else {
				TITANIUM_MODULE_LOG_WARN("TableView::scrollToIndex: Invalid row index ", index);
			}
		}

		void TableView::scrollToTop(const uint32_t& top, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			// On Windows the top value is interpreted as a row index
			scrollToIndex(top, animation);
		}

		void TableView::selectRow(const uint32_t& row) TITANIUM_NOEXCEPT
		{
			tableview__->SelectedIndex = row;
		}

		void TableView::deselectRow(const uint32_t& row) TITANIUM_NOEXCEPT
		{
			tableview__->SelectedIndex = row;
		}
	}  // namespace UI
}  // namespace TitaniumWindows