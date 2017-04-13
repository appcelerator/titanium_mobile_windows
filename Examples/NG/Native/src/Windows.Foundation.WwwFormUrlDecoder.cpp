/**
 * Windows Native Wrapper for Windows.Foundation.WwwFormUrlDecoder
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.Foundation.IWwwFormUrlDecoderEntry.hpp"
#include "Windows.Foundation.WwwFormUrlDecoder.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace Foundation
		{

		WwwFormUrlDecoder::WwwFormUrlDecoder(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("WwwFormUrlDecoder::ctor");
		}

		void WwwFormUrlDecoder::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("WwwFormUrlDecoder::postCallAsConstructor ", this);
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto query = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));

				wrapped__ = ref new ::Windows::Foundation::WwwFormUrlDecoder(query);
			}

		}

		::Windows::Foundation::WwwFormUrlDecoder^ WwwFormUrlDecoder::unwrapWindows_Foundation_WwwFormUrlDecoder() const
		{
			return dynamic_cast<::Windows::Foundation::WwwFormUrlDecoder^>(wrapped__);
		}

		::Windows::Foundation::WwwFormUrlDecoder^ WwwFormUrlDecoder::unwrap() const
		{
			return unwrapWindows_Foundation_WwwFormUrlDecoder();
		}

		void WwwFormUrlDecoder::wrap(::Windows::Foundation::WwwFormUrlDecoder^ object)
		{
			wrapped__ = object;
		}

		void WwwFormUrlDecoder::JSExportInitialize()
		{
			JSExport<WwwFormUrlDecoder>::SetClassVersion(1);
			JSExport<WwwFormUrlDecoder>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(WwwFormUrlDecoder, Size);
			TITANIUM_ADD_FUNCTION(WwwFormUrlDecoder, GetFirstValueByName);
			TITANIUM_ADD_FUNCTION(WwwFormUrlDecoder, First);
			TITANIUM_ADD_FUNCTION(WwwFormUrlDecoder, GetAt);
			TITANIUM_ADD_FUNCTION(WwwFormUrlDecoder, IndexOf);
			TITANIUM_ADD_FUNCTION(WwwFormUrlDecoder, GetMany);
		}

		TITANIUM_PROPERTY_GETTER(WwwFormUrlDecoder, Size)
		{
			auto value = unwrap()->Size;
			auto context = get_context();
 
			auto result = context.CreateNumber(value);

			return result;
		}

		TITANIUM_FUNCTION(WwwFormUrlDecoder, GetFirstValueByName)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto name = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));

				auto method_result = unwrap()->GetFirstValueByName(name);
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(method_result));

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched WwwFormUrlDecoder::GetFirstValueByName with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(WwwFormUrlDecoder, First)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->First();

			std::vector<JSValue> result_vector;
			while (method_result->HasCurrent) {
				

			auto method_result_tmp = context.CreateObject(JSExport<Windows::Foundation::IWwwFormUrlDecoderEntry>::Class());
			auto method_result_tmp_wrapper = method_result_tmp.GetPrivate<Windows::Foundation::IWwwFormUrlDecoderEntry>();
			method_result_tmp_wrapper->wrap(method_result->Current);


        		result_vector.push_back(method_result_tmp);
        		method_result->MoveNext();
			}

			auto result = get_context().CreateArray(result_vector);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched WwwFormUrlDecoder::First with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(WwwFormUrlDecoder, GetAt)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				auto method_result = unwrap()->GetAt(index);

			auto result = context.CreateObject(JSExport<Windows::Foundation::IWwwFormUrlDecoderEntry>::Class());
			auto result_wrapper = result.GetPrivate<Windows::Foundation::IWwwFormUrlDecoderEntry>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched WwwFormUrlDecoder::GetAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(WwwFormUrlDecoder, IndexOf)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_0);
 
			auto wrapper_value = object_value.GetPrivate<Windows::Foundation::IWwwFormUrlDecoderEntry>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_Foundation_IWwwFormUrlDecoderEntry();

				auto _1 = arguments.at(1); 
			TITANIUM_ASSERT_AND_THROW(_1.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_1);

				auto method_result = unwrap()->IndexOf(value, &index);
 
			auto result = context.CreateBoolean(method_result); 


 
			auto out_1 = context.CreateNumber(index);

				_1 = out_1;
				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched WwwFormUrlDecoder::IndexOf with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(WwwFormUrlDecoder, GetMany)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto startIndex = static_cast<uint32_t>(_0);

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_items = static_cast<JSObject>(_1);

			TITANIUM_ASSERT(object_items.IsArray());
			const auto array_items = static_cast<JSArray>(object_items);
			auto items_items = array_items.GetPrivateItems<Windows::Foundation::IWwwFormUrlDecoderEntry>(); // std::vector<std::shared_ptr<Windows::Foundation::IWwwFormUrlDecoderEntry>
			auto items = ref new ::Platform::Array<::Windows::Foundation::IWwwFormUrlDecoderEntry^>(items_items.size());
			for (size_t i = 0; i < items_items.size(); ++i) {
				items[i] = items_items.at(i)->unwrapWindows_Foundation_IWwwFormUrlDecoderEntry();
			}

				auto method_result = unwrap()->GetMany(startIndex, items);
 
			auto result = context.CreateNumber(method_result);



			std::vector<JSValue> out_1_vector;
			for (size_t i = 0; i < items->Length; ++i) {
				
			auto items_tmp = context.CreateObject(JSExport<Windows::Foundation::IWwwFormUrlDecoderEntry>::Class());
			auto items_tmp_wrapper = items_tmp.GetPrivate<Windows::Foundation::IWwwFormUrlDecoderEntry>();
			items_tmp_wrapper->wrap(items[i]);
		
        		out_1_vector.push_back(items_tmp);
			}

			auto out_1 = get_context().CreateArray(out_1_vector);

				_1 = out_1;
				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched WwwFormUrlDecoder::GetMany with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		} // namespace Foundation
	} // namespace Windows
} // namespace Titanium
