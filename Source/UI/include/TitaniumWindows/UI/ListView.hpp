/**
 * Titanium.UI.ListView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_LISTVIEW_HPP_
#define _TITANIUMWINDOWS_UI_LISTVIEW_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/ListView.hpp"
#include <collection.h>
#include <tuple>

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;

		class View;

		/*!
		  @class ListView
		  @ingroup Titanium.UI.ListView

		  @discussion This is the Titanium.UI.ListView implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ListView final : public Titanium::UI::ListView, public JSExport<ListView>
		{
		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(headerView);
			TITANIUM_PROPERTY_UNIMPLEMENTED(footerView);
			TITANIUM_PROPERTY_UNIMPLEMENTED(searchView);
			TITANIUM_PROPERTY_UNIMPLEMENTED(showVerticalScrollIndicator);
			TITANIUM_PROPERTY_UNIMPLEMENTED(separatorColor);
			TITANIUM_FUNCTION_UNIMPLEMENTED(scrollToItem);
			TITANIUM_FUNCTION_UNIMPLEMENTED(setMarker);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderWidth);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderRadius);

			virtual void appendSection(const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void deleteSectionAt(const uint32_t& sectionIndex, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void insertSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void replaceSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;

			ListView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ListView();
			ListView(const ListView&)            = default;
			ListView& operator=(const ListView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ListView(ListView&&)                 = default;
			ListView& operator=(ListView&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void set_searchText(const std::string& searchText) TITANIUM_NOEXCEPT;
			virtual void set_sections(const std::vector<std::shared_ptr <Titanium::UI::ListSection>>& sections) TITANIUM_NOEXCEPT override;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

			virtual void fireListSectionEvent(const std::string& name, const std::shared_ptr<Titanium::UI::ListSection>& section, const std::uint32_t& itemIndex = 0, const std::uint32_t& itemCount = 0, const std::uint32_t& affectedRows = 0) override;

			::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>^ createUIElementsForSection(const std::uint32_t& sectionIndex) TITANIUM_NOEXCEPT;

			void resetListViewDataBinding();
			void clearListViewData();

		private:
			void registerListViewItemAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view);
			void unregisterListViewItemAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view);
			void appendListViewItemForSection(const std::shared_ptr<TitaniumWindows::UI::View>& view, ::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>^ group);
			void insertListViewItemForSection(const std::shared_ptr<TitaniumWindows::UI::View>& view, ::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>^ group, const std::uint32_t& index);
			// Search for section index and item index. Returns {sectionIndex, itemIndex}
			std::tuple<std::uint32_t, std::int32_t> searchFromSelectedIndex(const std::uint32_t& selectedIndex);
			void bindCollectionViewSource();
			void unbindCollectionViewSource();

			// hide header view
			void hideHeaderView(const std::uint32_t& sectionIndex);

			// restore header view as it may be hidden according to the results
			void restoreHeaderViewIfNecessary(const std::uint32_t& sectionIndex);

			Windows::UI::Xaml::Controls::ListView^ listview__;
			Windows::UI::Xaml::Data::CollectionViewSource^ collectionViewSource__;

			// This is the "view" of the underlying list view items that is shown in the UI. It may be filtered from set_searchText
			Windows::Foundation::Collections::IObservableVector<::Platform::Object^>^ collectionViewItems__;

#pragma warning(push)
#pragma warning(disable : 4251)
			bool is_filtering__ { false };

			std::vector<Windows::UI::Xaml::UIElement^> unfiltered_headers__;
			std::vector<std::vector<Titanium::UI::ListDataItem>> unfiltered_sectionItems__;
			std::vector<std::shared_ptr<Titanium::UI::View>> headerViews__;
			std::vector<std::shared_ptr<Titanium::UI::View>> footerViews__;
#pragma warning(pop)

			Windows::Foundation::EventRegistrationToken itemclick_event__;

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_UI_LISTVIEW_HPP_