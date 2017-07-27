/**
 * Titanium.UI.SearchBar for Windows
 *
 * Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_SEARCHBAR_HPP_
#define _TITANIUMWINDOWS_SEARCHBAR_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/SearchBar.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include <collection.h>

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class SearchBar
		  @ingroup Titanium.UI.SearchBar

		  @discussion This is the Titanium.UI.SearchBar implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT SearchBar final : public Titanium::UI::SearchBar, public JSExport<SearchBar>
		{

		public:
			TITANIUM_FUNCTION_UNIMPLEMENTED(add);
			TITANIUM_FUNCTION_UNIMPLEMENTED(remove);
			TITANIUM_PROPERTY_UNIMPLEMENTED(font);
			TITANIUM_PROPERTY_UNIMPLEMENTED(style);

			SearchBar(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~SearchBar();
			SearchBar(const SearchBar&)            = default;
			SearchBar& operator=(const SearchBar&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			SearchBar(SearchBar&&)                 = default;
			SearchBar& operator=(SearchBar&&)      = default;
#endif

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;
			static void JSExportInitialize();

			virtual std::string get_value() const TITANIUM_NOEXCEPT override;
			virtual void set_value(const std::string&) TITANIUM_NOEXCEPT override;

#if defined(IS_WINDOWS_10)
			// showCancel is only supported on Windows 10
			virtual void set_showCancel(const bool&) TITANIUM_NOEXCEPT override;
			virtual void updateCancelButtonVisibility(const bool&) TITANIUM_NOEXCEPT;
#endif

		private:
			Windows::UI::Xaml::Controls::Border^ border__;
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			Windows::UI::Xaml::Controls::AutoSuggestBox^ suggest_box__;
			Windows::Foundation::Collections::IObservableVector<::Platform::String^>^ suggestItems__;

#else
			// For Windows 8.1 Store
			Windows::UI::Xaml::Controls::SearchBox^ suggest_box__;
#endif

#if defined(IS_WINDOWS_10)
			bool delete_button_dirty__ { false };
			Windows::UI::Xaml::Controls::Button^ delete_button__;
#endif
		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_SEARCHBAR_HPP_
