/**
 * Titanium.UI.SearchBar for Windows
 *
 * Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/SearchBar.hpp"
#include "Titanium/UI/TableViewRow.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace TitaniumWindows
{
	namespace UI
	{
		SearchBar::SearchBar(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::SearchBar(js_context)
		{
			TITANIUM_LOG_DEBUG("SearchBar::ctor Initialize");
		}

		SearchBar::~SearchBar()
		{
			TITANIUM_LOG_DEBUG("SearchBar::dtor");
		}

		void SearchBar::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) 
		{
			Titanium::UI::SearchBar::postCallAsConstructor(js_context, arguments);
			border__ = ref new Windows::UI::Xaml::Controls::Border();
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			suggest_box__  = ref new AutoSuggestBox();
			suggestItems__ = ref new Platform::Collections::Vector<Platform::String^>();
			suggest_box__->ItemsSource = suggestItems__;
#if defined(IS_WINDOWS_10)
			suggest_box__->QueryIcon = ref new SymbolIcon(Symbol::Find);
#endif
			suggest_box__->KeyUp += ref new KeyEventHandler([this](Platform::Object^ sender, KeyRoutedEventArgs^ e) {
				if (e->Key == Windows::System::VirtualKey::Enter && querySubmitted__) {
					querySubmitted__(TitaniumWindows::Utility::ConvertString(suggest_box__->Text));
				}
			});

			suggest_box__->TextChanged += ref new TypedEventHandler<AutoSuggestBox^, AutoSuggestBoxTextChangedEventArgs^>([this](AutoSuggestBox^ sender, AutoSuggestBoxTextChangedEventArgs^ e) {
				if (suggestionRequested__) {
					if (e->Reason == AutoSuggestionBoxTextChangeReason::SuggestionChosen) {
						return;
					}
					if (sender->Text->IsEmpty() && querySubmitted__) {
						querySubmitted__("");
						return;
					}
					const auto items = suggestionRequested__(TitaniumWindows::Utility::ConvertString(sender->Text));
					suggest_box__->ItemsSource = nullptr;
					suggestItems__->Clear();
					for (const auto item : items) {
						suggestItems__->Append(TitaniumWindows::Utility::ConvertString(item));
					}
					suggest_box__->ItemsSource = suggestItems__;
				}
			});
			suggest_box__->SuggestionChosen += ref new TypedEventHandler<AutoSuggestBox^, AutoSuggestBoxSuggestionChosenEventArgs^>([this](AutoSuggestBox^ sender, AutoSuggestBoxSuggestionChosenEventArgs^ e) {
				if (querySubmitted__) {
					querySubmitted__(TitaniumWindows::Utility::ConvertString(e->SelectedItem->ToString()));
				}
			});

#else
			// For Windows 8.1 Store App. Note that SearchBox is deprecated as of Windows 10.
			suggest_box__ = ref new SearchBox();
			suggest_box__->QuerySubmitted += ref new TypedEventHandler<SearchBox^, SearchBoxQuerySubmittedEventArgs^>([this](SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ e){
				if (querySubmitted__) {
					querySubmitted__(TitaniumWindows::Utility::ConvertString(sender->QueryText));
				}
			});
			suggest_box__->SuggestionsRequested += ref new TypedEventHandler<SearchBox^, SearchBoxSuggestionsRequestedEventArgs^>([this](SearchBox^ sender, SearchBoxSuggestionsRequestedEventArgs^ e){
				if (!sender->QueryText->IsEmpty() && suggestionRequested__) {
					const auto items = suggestionRequested__(TitaniumWindows::Utility::ConvertString(sender->QueryText));
					for (const auto item : items) {
						e->Request->SearchSuggestionCollection->AppendQuerySuggestion(TitaniumWindows::Utility::ConvertString(item));
					}
				}
			});
#endif
			border__->Child = suggest_box__;
			Titanium::UI::SearchBar::setLayoutDelegate<WindowsViewLayoutDelegate>();
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(border__, nullptr, border__);
		}

		void SearchBar::JSExportInitialize() 
		{
			JSExport<SearchBar>::SetClassVersion(1);
			JSExport<SearchBar>::SetParent(JSExport<Titanium::UI::SearchBar>::Class());
		}

		std::string SearchBar::get_value() const TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			return TitaniumWindows::Utility::ConvertUTF8String(suggest_box__->Text);
#else
			return TitaniumWindows::Utility::ConvertUTF8String(suggest_box__->QueryText);
#endif
		}

		void SearchBar::set_value(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::SearchBar::set_value(value);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			suggest_box__->Text = TitaniumWindows::Utility::ConvertUTF8String(value);
#else
			suggest_box__->QueryText = TitaniumWindows::Utility::ConvertUTF8String(value);
#endif
		}

		void SearchBar::set_hintText(const std::string& hintText) TITANIUM_NOEXCEPT
		{
			Titanium::UI::SearchBar::set_hintText(hintText);
			suggest_box__->PlaceholderText = TitaniumWindows::Utility::ConvertUTF8String(hintText);
		}

		std::string SearchBar::get_hintText() const TITANIUM_NOEXCEPT
		{
			return TitaniumWindows::Utility::ConvertUTF8String(suggest_box__->PlaceholderText);
		}
	}  // namespace UI
}  // namespace TitaniumWindows