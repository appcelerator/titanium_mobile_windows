/**
 * Titanium.UI.ListView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_LISTVIEW_HPP_
#define _TITANIUMWINDOWS_UI_LISTVIEW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;
		using ListSection_shared_ptr_t = std::shared_ptr <Titanium::UI::ListSection>;

		/*!
		@class ListViewItem

		@discussion This class represents item in ListView which is used for mapping ListView item with index and view
		*/
		ref class ListViewItem {
		public:
			property Windows::UI::Xaml::UIElement^ View
			{
				Windows::UI::Xaml::UIElement^ get() {
					return view__;
				}
				void set(Windows::UI::Xaml::UIElement^ value) {
					view__ = value;
				}
			}
			property uint32_t SectionIndex
			{
				uint32_t get() {
					return sectionIndex__;
				}
				void set(uint32_t value) {
					sectionIndex__ = value;
				}
			}
			property uint32_t ItemIndex
			{
				uint32_t get() {
					return itemIndex__;
				}
				void set(uint32_t value) {
					itemIndex__ = value;
				}
			}
			property bool isHeader
			{
				bool get() {
					return isHeader__;
				}
				void set(bool value) {
					isHeader__ = value;
				}
			}

		private:
			Windows::UI::Xaml::UIElement^ view__;
			uint32_t sectionIndex__;
			uint32_t itemIndex__;
			bool isHeader__;
		};

		/*!
		  @class

		  @discussion This is the Titanium.UI.ListView implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ListView final : public Titanium::UI::ListView, public JSExport<ListView>
		{
		public:
			ListView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ListView()                  = default;
			ListView(const ListView&)            = default;
			ListView& operator=(const ListView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ListView(ListView&&)                 = default;
			ListView& operator=(ListView&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void set_searchText(const std::string& searchText) TITANIUM_NOEXCEPT;
			virtual void set_sections(const std::vector<ListSection_shared_ptr_t>& sections) TITANIUM_NOEXCEPT override;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

		private:
			Windows::UI::Xaml::Controls::ListView^ listview__;
			Windows::UI::Xaml::Data::CollectionViewSource^ collectionViewSource__;
			// This is the "view" of the underlying list view items that is shown in the UI. It may be filtered from set_searchText
			Windows::Foundation::Collections::IObservableVector<Platform::Object^>^ collectionViewItems__;

			// Section and item index mapping. This is the _full_ listing of the underlying data
			Windows::Foundation::Collections::IVector<ListViewItem^>^ listViewItems__;

			Windows::Foundation::EventRegistrationToken click_event__;

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_UI_LISTVIEW_HPP_