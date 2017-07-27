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

using namespace Windows::UI::Xaml;
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
			showCancel__ = true; // native default
		}

		SearchBar::~SearchBar()
		{
			TITANIUM_LOG_DEBUG("SearchBar::dtor");
		}

#if defined(IS_WINDOWS_10)
		static TextBox^ GetTextBox(DependencyObject^ root)
		{
			const auto count = Media::VisualTreeHelper::GetChildrenCount(root);
			for (int i = 0; i < count; i++) {
				const auto child = Media::VisualTreeHelper::GetChild(root, i);
				const auto textbox = dynamic_cast<TextBox^>(child);
				if (textbox) {
					return textbox;
				} else {
					return GetTextBox(child);
				}
			}
			return nullptr;
		}

		void SearchBar::updateCancelButtonVisibility(const bool& show) TITANIUM_NOEXCEPT
		{
			// if no one touches showCancel property, we don't want to use our hack
			// because native implementation should be faster and safer.
			if (!delete_button_dirty__) return;

			const auto visible = suggest_box__->Text->IsEmpty() ? false : show;
			if (delete_button__) {
				delete_button__->MaxHeight  = visible ? HUGE_VAL : 0;
				delete_button__->MaxWidth   = visible ? HUGE_VAL : 0;
				delete_button__->Visibility = visible ? Visibility::Visible : Visibility::Collapsed;
			}
		}

		void SearchBar::set_showCancel(const bool& show) TITANIUM_NOEXCEPT
		{
			Titanium::UI::SearchBar::set_showCancel(show);
			delete_button_dirty__ = true; // indicate we need to use our hack
			updateCancelButtonVisibility(show);
		}
#endif

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

			// Since VisualTreeHelper is only available after Loaded event is fired, we need to update the visual state then.
			suggest_box__->Loaded += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				const auto textbox = GetTextBox(suggest_box__);
				if (textbox && Media::VisualTreeHelper::GetChildrenCount(textbox) > 0) {
					//
					// assuming the first component appeared in the TextBox is Grid that includes the button
					//
					const auto grid = dynamic_cast<Grid^>(Media::VisualTreeHelper::GetChild(textbox, 0));
					if (grid) {
						const auto count = Media::VisualTreeHelper::GetChildrenCount(grid);
						for (auto i = 0; i < count; i++) {
							//
							// assuming the first button appeared in the Grid is the "DeleteButton"
							//
							const auto button = dynamic_cast<Button^>(Media::VisualTreeHelper::GetChild(grid, i));
							if (button) {
								delete_button__ = button;
								return;
							}
						}
					}
				}
			});

			// Each time text has changed, you need to update the visibility of the DeleteButton
			suggest_box__->KeyDown += ref new Windows::UI::Xaml::Input::KeyEventHandler([this](Platform::Object^, KeyRoutedEventArgs^) {
				updateCancelButtonVisibility(get_showCancel());
			});
			// Hide the DeleteButton whenever SearchBar lost focus, 
			suggest_box__->LostFocus += ref new Windows::UI::Xaml::RoutedEventHandler([this](Platform::Object^, RoutedEventArgs^) {
				updateCancelButtonVisibility(false);
			});
			// Resture DeleteButton status when we got focus
			suggest_box__->GotFocus += ref new Windows::UI::Xaml::RoutedEventHandler([this](Platform::Object^, RoutedEventArgs^) {
				updateCancelButtonVisibility(get_showCancel());
			});
#endif
			suggest_box__->KeyUp += ref new KeyEventHandler([this](Platform::Object^ sender, KeyRoutedEventArgs^ e) {
#if defined(IS_WINDOWS_10)
				updateCancelButtonVisibility(get_showCancel());
#endif
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
					suggestItems__->Clear();
					for (const auto item : items) {
						suggestItems__->Append(TitaniumWindows::Utility::ConvertString(item));
					}
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

	}  // namespace UI
}  // namespace TitaniumWindows