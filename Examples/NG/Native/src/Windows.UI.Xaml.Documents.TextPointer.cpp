/**
 * Windows Native Wrapper for Windows.UI.Xaml.Documents.TextPointer
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.Documents.TextPointer.hpp"
#include "Windows.UI.Xaml.FrameworkElement.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Documents
				{

		TextPointer::TextPointer(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("TextPointer::ctor");
		}

		void TextPointer::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("TextPointer::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Documents::TextPointer^ TextPointer::unwrapWindows_UI_Xaml_Documents_TextPointer() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Documents::TextPointer^>(wrapped__);
		}

		::Windows::UI::Xaml::Documents::TextPointer^ TextPointer::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Documents_TextPointer();
		}

		void TextPointer::wrap(::Windows::UI::Xaml::Documents::TextPointer^ object)
		{
			wrapped__ = object;
		}

		void TextPointer::JSExportInitialize()
		{
			JSExport<TextPointer>::SetClassVersion(1);
			JSExport<TextPointer>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(TextPointer, LogicalDirection);
			TITANIUM_ADD_PROPERTY_READONLY(TextPointer, Offset);
			TITANIUM_ADD_PROPERTY_READONLY(TextPointer, Parent);
			TITANIUM_ADD_PROPERTY_READONLY(TextPointer, VisualParent);
			TITANIUM_ADD_FUNCTION(TextPointer, GetCharacterRect);
			TITANIUM_ADD_FUNCTION(TextPointer, GetPositionAtOffset);
		}

		TITANIUM_PROPERTY_GETTER(TextPointer, LogicalDirection)
		{
			auto value = unwrap()->LogicalDirection;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value))); // FIXME What if the enum isn't an int based one?!

			return result;
		}

		TITANIUM_PROPERTY_GETTER(TextPointer, Offset)
		{
			auto value = unwrap()->Offset;
			auto context = get_context();
 
			auto result = context.CreateNumber(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(TextPointer, Parent)
		{
			auto value = unwrap()->Parent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyObject>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyObject>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(TextPointer, VisualParent)
		{
			auto value = unwrap()->VisualParent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::FrameworkElement>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::FrameworkElement>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(TextPointer, GetCharacterRect)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto direction = static_cast<::Windows::UI::Xaml::Documents::LogicalDirection>(static_cast<int32_t>(_0)); // TODO Look up enum in metadata to know what type it's value is? 

				auto method_result = unwrap()->GetCharacterRect(direction);

			auto result = context.CreateObject();


			auto method_result_X_ = context.CreateNumber(static_cast<double>(method_result.X));

			result.SetProperty("X", method_result_X_);



			auto method_result_Y_ = context.CreateNumber(static_cast<double>(method_result.Y));

			result.SetProperty("Y", method_result_Y_);



			auto method_result_Width_ = context.CreateNumber(static_cast<double>(method_result.Width));

			result.SetProperty("Width", method_result_Width_);



			auto method_result_Height_ = context.CreateNumber(static_cast<double>(method_result.Height));

			result.SetProperty("Height", method_result_Height_);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched TextPointer::GetCharacterRect with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(TextPointer, GetPositionAtOffset)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto offset = static_cast<int32_t>(_0);

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsNumber(), "Expected Number");
			auto direction = static_cast<::Windows::UI::Xaml::Documents::LogicalDirection>(static_cast<int32_t>(_1)); // TODO Look up enum in metadata to know what type it's value is? 

				auto method_result = unwrap()->GetPositionAtOffset(offset, direction);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Documents::TextPointer>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Documents::TextPointer>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched TextPointer::GetPositionAtOffset with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

				} // namespace Documents
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
