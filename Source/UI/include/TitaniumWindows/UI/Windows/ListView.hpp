/**
* Windows.ListView
*
* Copyright (c) 2017 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#ifndef _TITANIUMWINDOWS_WINDOWS_LISTVIEW_HPP_
#define _TITANIUMWINDOWS_WINDOWS_LISTVIEW_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "Titanium/UI/ListView.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		// Use WindowsXaml namespace instead of "Windows" because it screws entire namespace in UI...
		namespace WindowsXaml
		{
			using namespace HAL;

			/*!
			@class

			@discussion This is the Titanium.UI.Windows.ListView implementation
			*/
			class TITANIUMWINDOWS_UI_EXPORT ListView final : public Titanium::UI::ListView, public JSExport<ListView>
			{

			public:
				ListView(const JSContext&) TITANIUM_NOEXCEPT;

				virtual ~ListView() = default;
				ListView(const ListView&) = default;
				ListView& operator=(const ListView&) = default;
		#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
				ListView(ListView&&) = default;
				ListView& operator=(ListView&&) = default;
		#endif

				static void JSExportInitialize();

				virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

				virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
				virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

				virtual void appendSection(const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
				virtual void deleteSectionAt(const uint32_t& sectionIndex, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
				virtual void insertSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
				virtual void replaceSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<Titanium::UI::ListSection>>& section, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;
				virtual void fireListSectionEvent(const std::string& name, const std::shared_ptr<Titanium::UI::ListSection>& section, const std::uint32_t& itemIndex = 0, const std::uint32_t& itemCount = 0, const std::uint32_t& affectedRows = 0) override;
				virtual void scrollToItem(const uint32_t& sectionIndex, const uint32_t& itemIndex, const std::shared_ptr<Titanium::UI::ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT override;

				virtual void set_searchText(const std::string& searchText) TITANIUM_NOEXCEPT override;
				virtual void set_searchView(const std::shared_ptr<Titanium::UI::SearchBar>&) TITANIUM_NOEXCEPT override;
				virtual void set_sections(const std::vector<std::shared_ptr <Titanium::UI::ListSection>>& sections) TITANIUM_NOEXCEPT override;
				virtual void set_defaultItemTemplate(const std::string&) TITANIUM_NOEXCEPT override;

			private:
				void resetData();
				ListViewModel::DataTemplateModel^ createDataModel(const Titanium::UI::ListDataItem item);
				ListViewModel::DataTemplateModelCollection^ createSectionModel(const std::shared_ptr<Titanium::UI::ListSection>& section);

				Windows::UI::Xaml::Data::CollectionViewSource^ collectionViewSource__;
				Windows::Foundation::Collections::IObservableVector<ListViewModel::DataTemplateModelCollection^>^ collectionViewItems__;

				Windows::UI::Xaml::Controls::Grid^ parent__;
				Windows::UI::Xaml::Controls::ListView^ listview__;

				Platform::String^ defaultItemTemplate__    { "defaultItemTemplate" };
				Platform::String^ defaultGroupStyle__      { "defaultItemTemplateGroupStyle" };
				Platform::String^ listViewItemTemplateUri__{ "ms-appx:///ListViewItemTemplate.xaml" };

		#pragma warning(push)
		#pragma warning(disable : 4251)
				Windows::Foundation::EventRegistrationToken itemclick_event__;
		#pragma warning(pop)
			};
		} // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_WINDOWS_LISTVIEW_HPP_
