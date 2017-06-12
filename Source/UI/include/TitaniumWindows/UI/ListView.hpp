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

			TITANIUM_PROPERTY_UNIMPLEMENTED(showVerticalScrollIndicator);
			TITANIUM_PROPERTY_UNIMPLEMENTED(separatorColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderWidth);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderRadius);

			virtual void appendSection(const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void deleteSectionAt(const uint32_t& sectionIndex, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void insertSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void replaceSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
			virtual void scrollToItem(const uint32_t& sectionIndex, const uint32_t& itemIndex, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;

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
			virtual void set_searchView(const std::shared_ptr<Titanium::UI::SearchBar>&) TITANIUM_NOEXCEPT override;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

			virtual void fireListSectionEvent(const std::string& name, const std::shared_ptr<Titanium::UI::ListSection>& section, const std::uint32_t& itemIndex = 0, const std::uint32_t& itemCount = 0, const std::uint32_t& affectedRows = 0) override;

			::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>^ createUIElementsForSection(const std::uint32_t& sectionIndex) TITANIUM_NOEXCEPT;

			void resetListViewDataBinding();
			void clearListViewData();

		private:
			static Windows::UI::Xaml::Controls::ScrollViewer^ GetScrollView(Windows::UI::Xaml::DependencyObject^ obj);

			void unregisterSectionLayoutNode(const std::shared_ptr<Titanium::UI::ListSection>& section);
			void registerListViewItemAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view);
			void unregisterListViewItemAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view);
			void appendListViewItemForSection(const std::shared_ptr<TitaniumWindows::UI::View>& view, ::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>^ group);
			void insertListViewItemForSection(const std::shared_ptr<TitaniumWindows::UI::View>& view, ::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>^ group, const std::uint32_t& index);
			void bindCollectionViewSource();
			void unbindCollectionViewSource();

			void updateScrollParams(const JSContext& ctx, JSObject params);
			void registerScrollstartEvent();
			void registerScrollingEvent();
			void registerScrollendEvent();
			void registerMarkerEvent();
			void checkMarkers();

			Windows::UI::Xaml::Controls::Grid^ parent__;
			Windows::UI::Xaml::Controls::ListView^ listview__;
			Windows::UI::Xaml::Data::CollectionViewSource^ collectionViewSource__;
			Windows::UI::Xaml::Controls::ScrollViewer^ scrollview__;

			// This is the "view" of the underlying list view items that is shown in the UI. It may be filtered from set_searchText
			Windows::Foundation::Collections::IObservableVector<::Platform::Object^>^ collectionViewItems__;

			double oldScrollPosX__{ -1 };
			double oldScrollPosY__{ -1 };
			bool scrollstop__ { true };

#pragma warning(push)
#pragma warning(disable : 4251)
			Windows::Foundation::EventRegistrationToken itemclick_event__;
			Windows::Foundation::EventRegistrationToken loaded_event__;
			Windows::Foundation::EventRegistrationToken scrollstart_event__;
			Windows::Foundation::EventRegistrationToken scrolling_event__;
			Windows::Foundation::EventRegistrationToken scrollend_event__;
			Windows::Foundation::EventRegistrationToken marker_event__;

#pragma warning(pop)

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_UI_LISTVIEW_HPP_