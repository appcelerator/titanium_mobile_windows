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
#include "TitaniumWindows/WindowsTiImpl.hpp"
#include "TitaniumWindows/UI/Windows/ViewHelper.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Xaml::Controls;
		using namespace Windows::UI::Xaml;
		using namespace Windows::Foundation;

		void WindowsPickerLayoutDelegate::onComponentSizeChange(const Titanium::LayoutEngine::Rect& rect)
		{
			WindowsViewLayoutDelegate::onComponentSizeChange(rect);
			const auto parent = dynamic_cast<Grid^>(component__);

			// This should not happen but just in case
			if (parent == nullptr || parent->Children->Size == 0) {
				return;
			}

			const auto picker = parent->Children->GetAt(0);
			if (picker) {
				const auto plain = dynamic_cast<Grid^>(picker);
				const auto date  = dynamic_cast<DatePicker^>(picker);
				const auto time  = dynamic_cast<TimePicker^>(picker);

				if (plain) {
					const auto children = plain->Children;
					for (std::size_t i = 0; i < children->Size; i++) {
						const auto child = dynamic_cast<ComboBox^>(children->GetAt(i));
						if (child) {
							// each child should have same width if picker has multiple columns
							child->MinWidth = rect.width / children->Size;
						}
					}
				} else if (date) {
					date->MinWidth = rect.width;
				} else if (time) {
					time->MinWidth = rect.width;
				}
			}
		}

		Picker::Picker(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::Picker(js_context)
		{
			TITANIUM_LOG_DEBUG("Picker::ctor ", this);
		}

		Picker::~Picker() 
		{
			TITANIUM_LOG_DEBUG("Picker::dtor ", this);
			unregisterChangeEvents();
		}

		void Picker::unregisterChangeEvents()
		{
			if (plainPicker__) {
				for (std::uint32_t i = 0; i < columns__.size(); i++) {
					const auto column = std::dynamic_pointer_cast<TitaniumWindows::UI::PickerColumn>(columns__[i]);
					const auto picker = column->getComponent();
					if (change_events__.size() > i) {
						picker->SelectionChanged -= change_events__.at(i);
					}
				}
				change_events__.clear();
			}
		}

		void Picker::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Picker::postCallAsConstructor(js_context, arguments);
			Titanium::UI::Picker::setLayoutDelegate<WindowsPickerLayoutDelegate>();

			parent__ = ref new Windows::UI::Xaml::Controls::Grid();
			parent__->VerticalAlignment = VerticalAlignment::Stretch;
			parent__->HorizontalAlignment = HorizontalAlignment::Stretch;

			getViewLayoutDelegate<WindowsPickerLayoutDelegate>()->setComponent(parent__, nullptr, false);
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
				getViewLayoutDelegate<WindowsPickerLayoutDelegate>()->setStyleComponent(plainPicker__);
			} else if (type__ == Titanium::UI::PICKER_TYPE::DATE) {
				datePicker__  = ref new Windows::UI::Xaml::Controls::DatePicker();
				datePicker__->HorizontalAlignment = HorizontalAlignment::Stretch;
				datePicker__->VerticalAlignment = VerticalAlignment::Stretch;

				// Adding Grid in Grid just to make border properties work. Otherwise it crashes for no reason
				const auto border = ref new Windows::UI::Xaml::Controls::Grid();
				border->Children->Append(datePicker__);
				border->SetColumn(datePicker__, 0);
				border->SetRow(datePicker__, 0);

				parent__->Children->Append(border);
				parent__->SetColumn(border, 0);
				parent__->SetRow(border, 0);

				getViewLayoutDelegate<WindowsPickerLayoutDelegate>()->setStyleComponent(datePicker__);
			} else if (type__ == Titanium::UI::PICKER_TYPE::TIME) {
				timePicker__  = ref new Windows::UI::Xaml::Controls::TimePicker();
				timePicker__->HorizontalAlignment = HorizontalAlignment::Stretch;
				timePicker__->VerticalAlignment = VerticalAlignment::Stretch;

				// Adding Grid in Grid just to make border properties work. Otherwise it crashes for no reason
				const auto border = ref new Windows::UI::Xaml::Controls::Grid();
				border->Children->Append(timePicker__);
				border->SetColumn(timePicker__, 0);
				border->SetRow(timePicker__, 0);

				parent__->Children->Append(border);
				parent__->SetColumn(border, 0);
				parent__->SetRow(border, 0);

				getViewLayoutDelegate<WindowsPickerLayoutDelegate>()->setStyleComponent(timePicker__);
			}

			// update UI
			set_value(value__);
			set_maxDate(maxDate__);
			set_minDate(minDate__);
			set_columns(columns__);
			set_font(font__);
		}

		void Picker::set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Picker::set_font(font);
			if (plainPicker__) {
				for (const auto column : columns__) {
					column->set_font(font);
				}
			} else if (datePicker__) {
				TitaniumWindows::UI::ViewHelper::SetFont<Windows::UI::Xaml::Controls::DatePicker^>(get_context(), datePicker__, font);
			} else if (timePicker__) {
				TitaniumWindows::UI::ViewHelper::SetFont<Windows::UI::Xaml::Controls::TimePicker^>(get_context(), timePicker__, font);
			}
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
			addColumns(columns);
			Titanium::UI::Picker::add_columns(columns);
		}

		void Picker::set_columns(const std::vector<std::shared_ptr<Titanium::UI::PickerColumn>>& columns) TITANIUM_NOEXCEPT
		{
			if (plainPicker__) {
				plainPicker__->Children->Clear();
				addColumns(columns);
			}
			Titanium::UI::Picker::set_columns(columns);
		}

		void Picker::addColumns(const std::vector<std::shared_ptr<Titanium::UI::PickerColumn>>& columns)
		{
			if (type__ == Titanium::UI::PICKER_TYPE::PLAIN) {
				unregisterChangeEvents();
				for (std::uint32_t i = 0; i < columns.size(); i++) {
					const auto column = std::dynamic_pointer_cast<TitaniumWindows::UI::PickerColumn>(columns[i]);
					const auto picker = column->getComponent();

					plainPicker__->Children->Append(picker);

					const auto cdef = ref new ColumnDefinition();
					cdef->Width = GridLengthHelper::FromValueAndType(1.0, GridUnitType::Star); // <RowDefinition Height="*"/>
					plainPicker__->ColumnDefinitions->Append(cdef);
					plainPicker__->SetColumn(picker, (plainPicker__->Children->Size - 1));
					plainPicker__->SetRow(picker, 0);

					column->set_font(get_font());

					change_events__.push_back(picker->SelectionChanged += ref new SelectionChangedEventHandler([column, i, this](Platform::Object^ sender, SelectionChangedEventArgs^ e) {
						TITANIUM_EXCEPTION_CATCH_START{
							const auto picker = static_cast<ComboBox^>(sender);
							const auto rowIndex = picker->SelectedIndex;
							const auto ctx = get_context();
							JSObject  eventArgs = ctx.CreateObject();
							if (rowIndex >= 0 && column->get_rowCount() > static_cast<std::uint32_t>(rowIndex)) {
								eventArgs.SetProperty("rowIndex", ctx.CreateNumber(rowIndex));
								eventArgs.SetProperty("row", column->get_rows().at(rowIndex)->get_object());
							}
							eventArgs.SetProperty("columnIndex", ctx.CreateNumber(i));
							eventArgs.SetProperty("column", column->get_object());
							eventArgs.SetProperty("selectedValue", ctx.CreateArray(getSelectedJSValues()));
							fireEvent("change", eventArgs);
						} TITANIUMWINDOWS_EXCEPTION_CATCH_END
					}));

				}
			} else {
				TITANIUM_MODULE_LOG_WARN("Picker::add: Unable to modify columns. This only works with plain picker");
			}
		}

		void Picker::add_rows(const std::vector<std::shared_ptr<Titanium::UI::PickerRow>>& rows) TITANIUM_NOEXCEPT
		{
			if (type__ == Titanium::UI::PICKER_TYPE::PLAIN) {
				std::shared_ptr<Titanium::UI::PickerColumn> column;
				const bool newColumn = (columns__.size() == 0);
				if (newColumn) {
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
				if (newColumn) {
					add_columns({ column });
				}
			}
		}

		std::vector<JSValue> Picker::getSelectedJSValues() 
		{
			const auto ctx = get_context();

			std::vector<JSValue> values;
			for (const auto c : columns__) {
				const auto column = std::dynamic_pointer_cast<TitaniumWindows::UI::PickerColumn>(c);
				const auto selectedRow = column->get_selectedRow();
				if (selectedRow) {
					values.push_back(ctx.CreateString(selectedRow->get_title()));
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
				if (datePicker__) {
					change_event__ = datePicker__->DateChanged += ref new EventHandler<DatePickerValueChangedEventArgs^>([this](Platform::Object^ sender, DatePickerValueChangedEventArgs^ e) {
						TITANIUM_EXCEPTION_CATCH_START {
							value__ = TitaniumWindows::Utility::GetDateTime(datePicker__->Date);
							const auto ctx = get_context();
							JSObject  eventArgs = ctx.CreateObject();
							eventArgs.SetProperty("value", js_get_value());
							fireEvent("change", eventArgs);
						} TITANIUMWINDOWS_EXCEPTION_CATCH_END
					});
				} else if (timePicker__) {
					change_event__ = timePicker__->TimeChanged += ref new EventHandler<TimePickerValueChangedEventArgs^>([this](Platform::Object^ sender, TimePickerValueChangedEventArgs^ e) {
						TITANIUM_EXCEPTION_CATCH_START {
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
						} TITANIUMWINDOWS_EXCEPTION_CATCH_END
					});
				}
			}
		}

		void Picker::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Picker::disableEvent(event_name);

			if (event_name == "change") {
				if (datePicker__) {
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
