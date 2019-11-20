/**
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Calendar.hpp"
#include "TitaniumWindows/Calendar/UserCalendar.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <ppltasks.h>
#include <concrt.h>
#include <collection.h>

#define CREATE_TITANIUM_CALENDAR(VARNAME, CTX, PARAMETERS) \
  static auto Calendar_ctor = CTX.CreateObject(); \
  static std::once_flag of; \
  std::call_once(of, [=] {\
  JSValue Titanium_property = CTX.get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue Parent_property = Titanium.GetProperty("Calendar"); \
  TITANIUM_ASSERT(Parent_property.IsObject()); \
  JSObject Calendar = static_cast<JSObject>(Parent_property); \
  JSValue Calendar_property = Calendar.GetProperty("Calendar"); \
  TITANIUM_ASSERT(Calendar_property.IsObject()); \
  Calendar_ctor = static_cast<JSObject>(Calendar_property); \
  });\
  JSObject VARNAME = Calendar_ctor.CallAsConstructor(); \
  Titanium::Module::applyProperties(PARAMETERS, VARNAME);

namespace TitaniumWindows
{
	using namespace Windows::ApplicationModel::Appointments;

	CalendarModule::CalendarModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::CalendarModule(js_context)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::CalendarModule::ctor");
	}

	void CalendarModule::JSExportInitialize()
	{
		JSExport<CalendarModule>::SetClassVersion(1);
		JSExport<CalendarModule>::SetParent(JSExport<Titanium::CalendarModule>::Class());
	}

	std::vector<std::shared_ptr<Titanium::Calendar::Alert>> CalendarModule::get_allAlerts() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("CalendarModule::get_allAlerts: Unimplemented");
		return std::vector<std::shared_ptr<Titanium::Calendar::Alert>>();
	}

	std::vector<std::shared_ptr<Titanium::Calendar::UserCalendar>> CalendarModule::get_allCalendars() const TITANIUM_NOEXCEPT
	{
		auto calendars = std::vector<std::shared_ptr<Titanium::Calendar::UserCalendar>>();

		if (appointmentStore__ == nullptr) {
			return calendars;
		}

		concurrency::event evt;
		concurrency::create_task(appointmentStore__->FindAppointmentCalendarsAsync(FindAppointmentCalendarsOptions::None))
			.then([this, &calendars, &evt](concurrency::task<Windows::Foundation::Collections::IVectorView<AppointmentCalendar^>^> task) {
			try {
				const auto cals = task.get();
				std::for_each(Windows::Foundation::Collections::begin(cals), Windows::Foundation::Collections::end(cals), [this, &calendars](AppointmentCalendar^ appointmentCalendar) {
					const auto ctx = get_context();
					auto parameters = ctx.CreateObject();
					CREATE_TITANIUM_CALENDAR(js_calendar, ctx, parameters);

					const auto calendar_ptr = js_calendar.GetPrivate<TitaniumWindows::Calendar::UserCalendar>();
					calendar_ptr->construct(appointmentStore__, appointmentCalendar);

					calendars.push_back(js_calendar.GetPrivate<Titanium::Calendar::UserCalendar>());
				});
			} catch (...) {
				// Do nothing
			}
			evt.set();
		}, concurrency::task_continuation_context::use_arbitrary());
		evt.wait();

		return calendars;
	}

	std::vector<std::shared_ptr<Titanium::Calendar::UserCalendar>> CalendarModule::get_allEditableCalendars() const TITANIUM_NOEXCEPT
	{
		return get_allCalendars();
	}

	std::vector<std::shared_ptr<Titanium::Calendar::UserCalendar>> CalendarModule::get_selectableCalendars() const TITANIUM_NOEXCEPT
	{
		return get_allCalendars();
	}

	std::shared_ptr<Titanium::Calendar::UserCalendar> CalendarModule::getDefaultCalendar() const TITANIUM_NOEXCEPT
	{
		if (appointmentStore__ == nullptr) {
			return nullptr;
		}

		AppointmentCalendar^ appointmentCalendar = nullptr;

		if (appointmentStore__) {
			concurrency::event evt;
			concurrency::create_task(appointmentStore__->FindAppointmentCalendarsAsync(FindAppointmentCalendarsOptions::None))
				.then([&appointmentCalendar, &evt](concurrency::task<Windows::Foundation::Collections::IVectorView<AppointmentCalendar^>^> task) {
				try {
					const auto calendars = task.get();
					if (calendars->Size > 0) {
						appointmentCalendar = calendars->GetAt(0);
					}
				} catch (...) {
					// Do nothing
				}
				evt.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			evt.wait();

			if (appointmentCalendar == nullptr) {
				return nullptr;
			}

			const auto ctx = get_context();
			auto parameters = ctx.CreateObject();
			CREATE_TITANIUM_CALENDAR(calendar, ctx, parameters);

			const auto calendar_ptr = calendar.GetPrivate<TitaniumWindows::Calendar::UserCalendar>();
			TITANIUM_ASSERT(calendar_ptr != nullptr);
			calendar_ptr->construct(appointmentStore__, appointmentCalendar);

			return calendar_ptr;
		}

		return nullptr;
	}

	std::shared_ptr<Titanium::Calendar::UserCalendar> CalendarModule::getCalendarById(const std::string& id) TITANIUM_NOEXCEPT
	{
		if (appointmentStore__ == nullptr) {
			return nullptr;
		}

		AppointmentCalendar^ appointmentCalendar = nullptr;
		concurrency::event evt;
		concurrency::create_task(appointmentStore__->GetAppointmentCalendarAsync(TitaniumWindows::Utility::ConvertUTF8String(id)))
			.then([&appointmentCalendar, &evt](concurrency::task<AppointmentCalendar^> task) {
			try {
				appointmentCalendar = task.get();
			} catch (...) {
				// Do nothing
			}
			evt.set();
		}, concurrency::task_continuation_context::use_arbitrary());
		evt.wait();

		if (appointmentCalendar == nullptr) {
			return nullptr;
		}

		const auto ctx = get_context();
		auto parameters = ctx.CreateObject();
		CREATE_TITANIUM_CALENDAR(calendar, ctx, parameters);

		const auto calendar_ptr = calendar.GetPrivate<TitaniumWindows::Calendar::UserCalendar>();
		TITANIUM_ASSERT(calendar_ptr != nullptr);
		calendar_ptr->construct(appointmentStore__, appointmentCalendar);

		return calendar_ptr;
	}

	bool CalendarModule::hasCalendarPermissions() TITANIUM_NOEXCEPT
	{
		// check previous state
		if (hasCalendarPermissions__) {
			return *hasCalendarPermissions__;
		}

		return false;
	}

	void CalendarModule::requestCalendarPermissions(JSObject& callback) TITANIUM_NOEXCEPT
	{
		using namespace Windows::Data::Xml::Dom;

		concurrency::task<Windows::Storage::StorageFile^>(Windows::ApplicationModel::Package::Current->InstalledLocation->GetFileAsync("AppxManifest.xml"))
			.then([](Windows::Storage::StorageFile^ file) {
			return concurrency::task<XmlDocument^>(XmlDocument::LoadFromFileAsync(file));
		}).then([this](XmlDocument^ doc) {
				const auto items = doc->GetElementsByTagName("rescap:Capability");
				for (unsigned int i = 0; i < items->Length; i++) {
					const auto node = items->GetAt(i);
					const auto name = static_cast<Platform::String^>(node->Attributes->GetNamedItem("Name")->NodeValue);
					if (name == "appointmentsSystem") {
						hasCalendarPermissions__ = true;
						break;
					}
				}
			return concurrency::create_task(AppointmentManager::RequestStoreAsync(AppointmentStoreAccessType::AllCalendarsReadWrite));
		}).then([this, callback](concurrency::task<AppointmentStore^> task) {
			const auto ctx = get_context();
			auto response = ctx.CreateObject();

			try {
				appointmentStore__ = task.get();

				calendarAuthorization__ = Titanium::Calendar::AUTHORIZATION::AUTHORIZED;

				response.SetProperty("code", ctx.CreateNumber(0));
				response.SetProperty("error", ctx.CreateString());
				response.SetProperty("success", ctx.CreateBoolean(true));

				auto cb = static_cast<JSObject>(callback);
				TITANIUM_ASSERT(cb.IsFunction());
				cb({ response }, get_object());
			} catch (...) {
				calendarAuthorization__ = Titanium::Calendar::AUTHORIZATION::DENIED;

				response.SetProperty("code", ctx.CreateNumber(-1));
				if (hasCalendarPermissions__) {
					response.SetProperty("error", ctx.CreateString(TitaniumWindows::Utility::ConvertString("Unable to get appointments store from system")));
				} else {
					response.SetProperty("error", ctx.CreateString(TitaniumWindows::Utility::ConvertString("appointmentsSystem rescap:Capability not set in tiapp.xml")));
				}
				response.SetProperty("success", ctx.CreateBoolean(false));

				auto cb = static_cast<JSObject>(callback);
				TITANIUM_ASSERT(cb.IsFunction());
				cb({ response }, get_object());
			}
		});
	}

}  // namespace TitaniumWindows
