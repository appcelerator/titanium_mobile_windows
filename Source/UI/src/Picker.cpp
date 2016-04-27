/**
* Titanium.UI.Picker for Windows
*
* Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Picker.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/PickerColumn.hpp"
#include "Titanium/UI/PickerRow.hpp"
#include "TitaniumWindows/UI/PickerRow.hpp"
#include "TitaniumWindows/UI/PickerColumn.hpp"
#include <windows.h>
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/LogForwarder.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Xaml::Controls;
		using namespace Windows::UI::Xaml;
		using namespace Windows::Foundation;

		Picker::Picker(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::Picker(js_context)
		{
			TITANIUM_LOG_DEBUG("Picker::ctor ", this);
		}

		Picker::~Picker() 
		{
			TITANIUM_LOG_DEBUG("Picker::dtor ", this);
		}

		void Picker::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Picker::postCallAsConstructor(js_context, arguments);
			Titanium::UI::Picker::setLayoutDelegate<WindowsViewLayoutDelegate>();

			parent__ = ref new Windows::UI::Xaml::Controls::Grid();

			// Fill width
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForWidth(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(parent__);
		}

		void Picker::afterPropertiesSet() TITANIUM_NOEXCEPT
		{
			Titanium::UI::Picker::afterPropertiesSet();

			// Create new picker container
			if (type__ == Titanium::UI::PICKER_TYPE::PLAIN) {
				plainPicker__  = ref new Windows::UI::Xaml::Controls::Grid();
				parent__->Children->Append(plainPicker__);
				parent__->SetColumn(plainPicker__, 0);
				parent__->SetRow(plainPicker__, 0);
			} else if (type__ == Titanium::UI::PICKER_TYPE::DATE) {
				datePicker__  = ref new Windows::UI::Xaml::Controls::DatePicker();
				parent__->Children->Append(datePicker__);
				parent__->SetColumn(datePicker__, 0);
				parent__->SetRow(datePicker__, 0);
			} else if (type__ == Titanium::UI::PICKER_TYPE::TIME) {
				timePicker__  = ref new Windows::UI::Xaml::Controls::TimePicker();
				parent__->Children->Append(timePicker__);
				parent__->SetColumn(timePicker__, 0);
				parent__->SetRow(timePicker__, 0);
			}

			// update UI
			set_value(value__);
			set_maxDate(maxDate__);
			set_minDate(minDate__);
			set_columns(columns__);

		}

		void Picker::set_value(const boost::optional<std::chrono::system_clock::time_point>& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Picker::set_value(value);
			if (!value) {
				return;
			}
			if (datePicker__) {
				datePicker__->Date = TitaniumWindows::Utility::GetDateTime(*value__);
			} else if (timePicker__) {
				timePicker__->Time = TitaniumWindows::Utility::ExtractTime(*value__);
			}
		}

		void Picker::set_maxDate(const boost::optional<std::chrono::system_clock::time_point>& maxDate) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Picker::set_maxDate(maxDate);
			if (!maxDate) {
				return;
			}
			if (datePicker__) {
				datePicker__->MaxYear = TitaniumWindows::Utility::GetDateTime(*maxDate__);
			}
		}

		void Picker::set_minDate(const boost::optional<std::chrono::system_clock::time_point>& minDate) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Picker::set_minDate(minDate);
			if (!minDate) {
				return;
			}
			if (datePicker__) {
				datePicker__->MinYear = TitaniumWindows::Utility::GetDateTime(*minDate__);
			}
		}

		void Picker::set_type(const Titanium::UI::PICKER_TYPE& type) TITANIUM_NOEXCEPT
		{
			// Remove existing picker
			if (parent__->Children->Size > 0) {
				parent__->Children->RemoveAt(0);
			}

			if (type__ == Titanium::UI::PICKER_TYPE::PLAIN) {
				plainPicker__  = nullptr;
			} else if (type__ == Titanium::UI::PICKER_TYPE::DATE) {
				datePicker__ = nullptr;
			} else if (type__ == Titanium::UI::PICKER_TYPE::TIME) {
				timePicker__ = nullptr;
			}

			// Update property
			Titanium::UI::Picker::set_type(type);
		}

		void Picker::add_columns(const std::vector<std::shared_ptr<Titanium::UI::PickerColumn>>& columns) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Picker::add_columns(columns);
			createColumns(columns);
		}

		void Picker::set_columns(const std::vector<std::shared_ptr<Titanium::UI::PickerColumn>>& columns) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Picker::set_columns(columns);
			if (plainPicker__) {
				plainPicker__->Children->Clear();
				createColumns(columns);
			}
		}

		void Picker::createColumns(const std::vector<std::shared_ptr<Titanium::UI::PickerColumn>>& columns)
		{
			if (type__ == Titanium::UI::PICKER_TYPE::PLAIN) {
				for (const auto c : columns) {
					const auto column = std::dynamic_pointer_cast<TitaniumWindows::UI::PickerColumn>(c);
					const auto picker = column->getComponent();

					column->refreshRows();

					plainPicker__->Children->Append(picker);

					const auto cdef = ref new ColumnDefinition();
					cdef->Width = GridLengthHelper::FromValueAndType(1.0, GridUnitType::Star); // <RowDefinition Height="*"/>
					plainPicker__->ColumnDefinitions->Append(cdef);
					plainPicker__->SetColumn(picker, (plainPicker__->Children->Size - 1));
					plainPicker__->SetRow(picker, 0);
				}
			} else {
				TITANIUM_MODULE_LOG_WARN("Picker::add: Unable to modify columns. This only works with plain picker");
			}
		}

		void Picker::add_rows(const std::vector<std::shared_ptr<Titanium::UI::PickerRow>>& rows) TITANIUM_NOEXCEPT
		{
			if (type__ == Titanium::UI::PICKER_TYPE::PLAIN) {
				std::shared_ptr<Titanium::UI::PickerColumn> column;
				if (columns__.size() == 0) {
					// Create new column if no column is created
					auto Column_ctor = get_context().CreateObject(JSExport<TitaniumWindows::UI::PickerColumn>::Class());
					column = Column_ctor.CallAsConstructor().GetPrivate<TitaniumWindows::UI::PickerColumn>();
				} else {
					// Add to existing column
					column = columns__.at(0);
				}
				for (const auto row : rows) {
					column->addRow(row);
				}
				add_columns({ column });
			}
		}

		std::vector<JSValue> Picker::getSelectedJSValues() 
		{
			const auto ctx = get_context();

			std::vector<JSValue> values;
			for (const auto c : columns__) {
				const auto column = std::dynamic_pointer_cast<TitaniumWindows::UI::PickerColumn>(c);
				const auto picker = column->getComponent();
				const auto item = picker->SelectedItem;
				if (item) {
					const auto value = TitaniumWindows::Utility::ConvertUTF8String(static_cast<TextBlock^>(item)->Text);
					values.push_back(ctx.CreateString(value));
				} else {
					values.push_back(ctx.CreateNull());
				}
			}
			return values;
		}

		void Picker::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Picker::enableEvent(event_name);
			if (event_name == "change") {

				if (plainPicker__) {
					for (size_t columnIndex = 0; columnIndex < columns__.size(); columnIndex++) {
						const auto column = std::dynamic_pointer_cast<TitaniumWindows::UI::PickerColumn>(columns__.at(columnIndex));
						const auto picker = column->getComponent();
						change_events__.push_back(picker->SelectionChanged += ref new SelectionChangedEventHandler([column, columnIndex, this](Platform::Object^ sender, SelectionChangedEventArgs^ e) {
							const auto picker = static_cast<ComboBox^>(sender);
							const auto rowIndex = picker->SelectedIndex;
							const auto ctx = get_context();
							TITANIUM_ASSERT(column->get_rowCount() > rowIndex);
							JSObject  eventArgs = ctx.CreateObject();
							eventArgs.SetProperty("columnIndex", ctx.CreateNumber(columnIndex));
							eventArgs.SetProperty("rowIndex", ctx.CreateNumber(rowIndex));
							eventArgs.SetProperty("column", column->get_object());
							eventArgs.SetProperty("row", column->get_rows().at(rowIndex)->get_object());
							eventArgs.SetProperty("selectedValue", ctx.CreateArray(getSelectedJSValues()));
							fireEvent("change", eventArgs);
						}));
					}
				} else if (datePicker__) {
					change_event__ = datePicker__->DateChanged += ref new EventHandler<DatePickerValueChangedEventArgs^>([this](Platform::Object^ sender, DatePickerValueChangedEventArgs^ e) {
						value__ = TitaniumWindows::Utility::GetDateTime(datePicker__->Date);
						const auto ctx = get_context();
						JSObject  eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("value", js_get_value());
						fireEvent("change", eventArgs);
					});
				} else if (timePicker__) {
					change_event__ = timePicker__->TimeChanged += ref new EventHandler<TimePickerValueChangedEventArgs^>([this](Platform::Object^ sender, TimePickerValueChangedEventArgs^ e) {
						if (value__) {
							// extract time based on value__ when value__ is available
							value__ = TitaniumWindows::Utility::ExtractTime(*value__, timePicker__->Time);
						} else {
							// extract time based on beginning of epoch date
							value__ = TitaniumWindows::Utility::ExtractTime(std::chrono::time_point<std::chrono::system_clock>(std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(0))), timePicker__->Time);
						}
						const auto ctx = get_context();
						JSObject  eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("value", js_get_value());
						fireEvent("change", eventArgs);
					});
				}
			}
		}

		void Picker::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Picker::disableEvent(event_name);

			if (event_name == "change") {
				if (plainPicker__) {
					for (size_t columnIndex = 0; columnIndex < columns__.size(); columnIndex++) {
						const auto column = std::dynamic_pointer_cast<TitaniumWindows::UI::PickerColumn>(columns__.at(columnIndex));
						const auto picker = column->getComponent();
						picker->SelectionChanged -= change_events__.at(columnIndex);
					}
					change_events__.clear();
				} else if (datePicker__) {
					datePicker__->DateChanged -= change_event__;
				} else if (timePicker__) {
					timePicker__->TimeChanged -= change_event__;
				}
			}
		}

		void Picker::JSExportInitialize()
		{
			JSExport<Picker>::SetClassVersion(1);
			JSExport<Picker>::SetParent(JSExport<Titanium::UI::Picker>::Class());
		}

	} // namespace UI
} // namespace TitaniumWindows
