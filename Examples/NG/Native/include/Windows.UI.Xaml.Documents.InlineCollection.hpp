/**
 * Windows Native Wrapper for Windows.UI.Xaml.Documents.InlineCollection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DOCUMENTS_INLINECOLLECTION_HPP_
#define _WINDOWS_UI_XAML_DOCUMENTS_INLINECOLLECTION_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Platform.Object.hpp"

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


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT InlineCollection : public ::Titanium::Platform::Object, public JSExport<InlineCollection>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(Size);

			TITANIUM_FUNCTION_DEF(GetAt);
			TITANIUM_FUNCTION_DEF(GetView);
			TITANIUM_FUNCTION_DEF(IndexOf);
			TITANIUM_FUNCTION_DEF(SetAt);
			TITANIUM_FUNCTION_DEF(InsertAt);
			TITANIUM_FUNCTION_DEF(RemoveAt);
			TITANIUM_FUNCTION_DEF(Append);
			TITANIUM_FUNCTION_DEF(RemoveAtEnd);
			TITANIUM_FUNCTION_DEF(Clear);
			TITANIUM_FUNCTION_DEF(GetMany);
			TITANIUM_FUNCTION_DEF(ReplaceAll);
			TITANIUM_FUNCTION_DEF(First);

			InlineCollection(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~InlineCollection() = default;
			InlineCollection(const InlineCollection&) = default;
			InlineCollection& operator=(const InlineCollection&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			InlineCollection(InlineCollection&&)                 = default;
			InlineCollection& operator=(InlineCollection&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Documents::InlineCollection^ unwrapWindows_UI_Xaml_Documents_InlineCollection() const;
			void wrap(::Windows::UI::Xaml::Documents::InlineCollection^ object);

		private:
			::Windows::UI::Xaml::Documents::InlineCollection^ unwrap() const;

		};

				} // namespace Documents
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DOCUMENTS_INLINECOLLECTION_HPP_
