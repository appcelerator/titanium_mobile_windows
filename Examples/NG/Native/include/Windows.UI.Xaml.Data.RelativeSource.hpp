/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.RelativeSource
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DATA_RELATIVESOURCE_HPP_
#define _WINDOWS_UI_XAML_DATA_RELATIVESOURCE_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Data
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT RelativeSource : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<RelativeSource>
		{

		public:
			TITANIUM_PROPERTY_DEF(Mode);


			RelativeSource(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~RelativeSource() = default;
			RelativeSource(const RelativeSource&) = default;
			RelativeSource& operator=(const RelativeSource&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			RelativeSource(RelativeSource&&)                 = default;
			RelativeSource& operator=(RelativeSource&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Data::RelativeSource^ unwrapWindows_UI_Xaml_Data_RelativeSource() const;
			void wrap(::Windows::UI::Xaml::Data::RelativeSource^ object);

		private:
			::Windows::UI::Xaml::Data::RelativeSource^ unwrap() const;

		};

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DATA_RELATIVESOURCE_HPP_
