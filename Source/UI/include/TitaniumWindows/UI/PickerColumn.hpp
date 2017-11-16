/**
* Titanium.UI.PickerColumn for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_PICKERCOLUMN_HPP_
#define _TITANIUMWINDOWS_UI_PICKERCOLUMN_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/PickerColumn.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class PickerColumn
		  @ingroup Titanium.UI.PickerColumn

		  @discussion This is the Titanium.UI.PickerColumn implementation for
		  Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT PickerColumn final : public Titanium::UI::PickerColumn, public JSExport<PickerColumn>
		{
		public:
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderRadius);

			PickerColumn(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~PickerColumn();
			PickerColumn(const PickerColumn&) = default;
			PickerColumn& operator=(const PickerColumn&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			PickerColumn(PickerColumn&&) = default;
			PickerColumn& operator=(PickerColumn&&) = default;
#endif

			static void JSExportInitialize();
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void afterPropertiesSet() TITANIUM_NOEXCEPT override;
			virtual void addRow(const std::shared_ptr<Titanium::UI::PickerRow>& row) TITANIUM_NOEXCEPT override;
			virtual void removeRow(const std::shared_ptr<Titanium::UI::PickerRow>& row) TITANIUM_NOEXCEPT override;
			virtual std::shared_ptr<Titanium::UI::PickerRow> get_selectedRow() const TITANIUM_NOEXCEPT override;
			virtual void set_selectedRow(const std::shared_ptr<Titanium::UI::PickerRow>&) TITANIUM_NOEXCEPT override;
			virtual void set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT override;
			virtual void reload() TITANIUM_NOEXCEPT override;

			Windows::UI::Xaml::Controls::ComboBox^ getComponent() const TITANIUM_NOEXCEPT
			{
				return picker__;
			}

		private:
			void refreshRows() TITANIUM_NOEXCEPT;

#pragma warning(push)
#pragma warning(disable : 4251)
			Windows::UI::Xaml::Controls::ComboBox^ picker__;
#pragma warning(pop)
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_PICKERCOLUMN_HPP_
