/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.DataTemplateSelector
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_DATATEMPLATESELECTOR_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_DATATEMPLATESELECTOR_HPP_

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
				namespace Controls
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT DataTemplateSelector : public ::Titanium::Platform::Object, public JSExport<DataTemplateSelector>
		{

		public:

			TITANIUM_FUNCTION_DEF(SelectTemplate);

			DataTemplateSelector(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~DataTemplateSelector() = default;
			DataTemplateSelector(const DataTemplateSelector&) = default;
			DataTemplateSelector& operator=(const DataTemplateSelector&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			DataTemplateSelector(DataTemplateSelector&&)                 = default;
			DataTemplateSelector& operator=(DataTemplateSelector&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::DataTemplateSelector^ unwrapWindows_UI_Xaml_Controls_DataTemplateSelector() const;
			void wrap(::Windows::UI::Xaml::Controls::DataTemplateSelector^ object);

		private:
			::Windows::UI::Xaml::Controls::DataTemplateSelector^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_DATATEMPLATESELECTOR_HPP_
