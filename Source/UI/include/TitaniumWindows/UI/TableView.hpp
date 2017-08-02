/**
 * Titanium.UI.TableView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_TABLEVIEW_HPP_
#define _TITANIUMWINDOWS_TABLEVIEW_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/TableView.hpp"
#include <collection.h>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class TableView
		  @ingroup Titanium.UI.TableView

		  @discussion This is the Titanium.UI.TableView implementation for Windows.
		*/
#pragma warning(push)
#pragma warning(disable : 4275)
		class TITANIUMWINDOWS_UI_EXPORT TableView final : public Titanium::UI::TableView, public JSExport<TableView>
		{
#pragma warning(pop)
		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(allowsSelection);
			TITANIUM_PROPERTY_UNIMPLEMENTED(allowsSelectionDuringEditing);
			TITANIUM_PROPERTY_UNIMPLEMENTED(filterAttribute);
			TITANIUM_PROPERTY_UNIMPLEMENTED(filterAnchored);
			TITANIUM_PROPERTY_UNIMPLEMENTED(filterCaseInsensitive);
			TITANIUM_PROPERTY_UNIMPLEMENTED(maxRowHeight);
			TITANIUM_PROPERTY_UNIMPLEMENTED(minRowHeight);
			TITANIUM_PROPERTY_UNIMPLEMENTED(rowHeight);

			TableView(const JSContext&) TITANIUM_NOEXCEPT;
			virtual ~TableView();
			TableView(const TableView&)            = default;
			TableView& operator=(const TableView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TableView(TableView&&)                 = default;
			TableView& operator=(TableView&&)      = default;
#endif
			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

			virtual void set_sections(const std::vector<std::shared_ptr<Titanium::UI::TableViewSection>>& sections) TITANIUM_NOEXCEPT override;
			virtual void set_data(const std::vector<JSObject>& data) TITANIUM_NOEXCEPT override;
			virtual void set_separatorColor(const std::string& color) TITANIUM_NOEXCEPT override;
			virtual void set_headerView(const std::shared_ptr<Titanium::UI::View>&) TITANIUM_NOEXCEPT override;
			virtual void set_headerTitle(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_search(const std::shared_ptr<Titanium::UI::SearchBar>&) TITANIUM_NOEXCEPT override;

			virtual void appendSection(const std::vector<std::shared_ptr<Titanium::UI::TableViewSection>>& sections, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void querySubmitted(const std::string& query) override;

			virtual void updateSection(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void deleteSection(const uint32_t& section, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void insertSectionAfter(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void insertSectionBefore(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;

			virtual void scrollToIndex(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void scrollToTop(const uint32_t& top, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void selectRow(const uint32_t& row) TITANIUM_NOEXCEPT override;
			virtual void deselectRow(const uint32_t& row) TITANIUM_NOEXCEPT override;


			virtual void createEmptyTableViewSection() override;
			virtual void createTableSectionUIElements() TITANIUM_NOEXCEPT;

			virtual void afterPropertiesSet() TITANIUM_NOEXCEPT;

		private:
			static Windows::UI::Xaml::Controls::ScrollViewer^ GetScrollView(Windows::UI::Xaml::DependencyObject^ obj);

			void bindCollectionViewSource();
			void unbindCollectionViewSource();

			::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>^ createUIElementsForSection(const std::uint32_t& sectionIndex) TITANIUM_NOEXCEPT;
			Windows::UI::Xaml::Controls::ListViewHeaderItem^ createDefaultHeader(const std::shared_ptr<Titanium::UI::TableViewSection>& seciton = nullptr);
			Windows::UI::Xaml::Controls::ListViewHeaderItem^ createDefaultFooter(const std::shared_ptr<Titanium::UI::TableViewSection>& seciton = nullptr);
			void registerTableViewRowAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view);
			void unregisterTableViewRowAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view);

			// Receive all events fired from TableViewSection.
			// Subclass may override this to catch changes for section.
			virtual void fireTableViewSectionEvent(const std::string& name, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewRow>& row, const std::uint32_t& rowIndex, const std::shared_ptr<Titanium::UI::TableViewRow>& old_row) override;

			void unregisterSectionLayoutNode(const std::shared_ptr<Titanium::UI::TableViewSection>& section);
			void unregisterSections();
			void clearTableData();
			void resetTableDataBinding();
			std::uint32_t getRowIndexInCollectionView(const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::uint32_t& rowIndex) TITANIUM_NOEXCEPT;
			void setTableHeader();
			void setTableFooter();

			void registerScrollEvent();
			void registerScrollendEvent();

			Windows::UI::Xaml::Controls::Grid^ parent__;
			Windows::UI::Xaml::Controls::ListView^ tableview__;
			Windows::UI::Xaml::Controls::ScrollViewer^ scrollview__;
			Windows::UI::Xaml::Data::CollectionViewSource^ collectionViewSource__;
			Windows::Foundation::Collections::IObservableVector<::Platform::Object^>^ collectionViewItems__;
			Windows::UI::Xaml::Media::Brush^ separatorBrush__;

			Windows::Foundation::EventRegistrationToken click_event__;
			Windows::Foundation::EventRegistrationToken loaded_event__;
			Windows::Foundation::EventRegistrationToken scroll_event__;
			Windows::Foundation::EventRegistrationToken scrollend_event__;
			Windows::Foundation::EventRegistrationToken touchmove_event__;
			
			double oldScrollPosX__ { -1 };
			double oldScrollPosY__ { -1 };
#pragma warning(push)
#pragma warning(disable : 4251)

#pragma warning(pop)

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_TABLEVIEW_HPP_