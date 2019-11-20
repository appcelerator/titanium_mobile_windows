/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_TIMODULE_HPP_
#define _TITANIUM_TIMODULE_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class
	  @discussion This is the top-level Titanium Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium
	*/
	class TITANIUMKIT_EXPORT TiModule : public Module, public JSExport<TiModule>
	{
	public:
		virtual std::string version() const TITANIUM_NOEXCEPT;
		virtual std::string buildDate() const TITANIUM_NOEXCEPT;
		virtual std::string buildHash() const TITANIUM_NOEXCEPT;

		virtual void setUserAgent(const std::string&) TITANIUM_NOEXCEPT final;

		TiModule(const JSContext&) TITANIUM_NOEXCEPT;
		virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

		virtual ~TiModule() = default;
		TiModule(const TiModule&) = default;
		TiModule& operator=(const TiModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		TiModule(TiModule&&) = default;
		TiModule& operator=(TiModule&&) = default;
#endif

		static void JSExportInitialize();
		static JSObject GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT;

		TITANIUM_PROPERTY_READONLY_DEF(version);

		TITANIUM_PROPERTY_READONLY_DEF(Accelerometer);
		TITANIUM_PROPERTY_READONLY_DEF(Analytics);
		TITANIUM_PROPERTY_READONLY_DEF(API);
		TITANIUM_PROPERTY_READONLY_DEF(App);
		TITANIUM_PROPERTY_READONLY_DEF(Blob);
		TITANIUM_PROPERTY_READONLY_DEF(BlobStream);
		TITANIUM_PROPERTY_READONLY_DEF(Buffer);
		TITANIUM_PROPERTY_READONLY_DEF(BufferStream);
		TITANIUM_PROPERTY_READONLY_DEF(Calendar);
		TITANIUM_PROPERTY_READONLY_DEF(Codec);
		TITANIUM_PROPERTY_READONLY_DEF(Contacts);
		TITANIUM_PROPERTY_READONLY_DEF(Database);
		TITANIUM_PROPERTY_READONLY_DEF(FileStream);
		TITANIUM_PROPERTY_READONLY_DEF(Filesystem);
		TITANIUM_PROPERTY_READONLY_DEF(Geolocation);
		TITANIUM_PROPERTY_READONLY_DEF(Gesture);
		TITANIUM_PROPERTY_READONLY_DEF(IOStream);
		TITANIUM_PROPERTY_READONLY_DEF(Locale);
		TITANIUM_PROPERTY_READONLY_DEF(Map);
		TITANIUM_PROPERTY_READONLY_DEF(Media);
		TITANIUM_PROPERTY_READONLY_DEF(Network);
		TITANIUM_PROPERTY_READONLY_DEF(Platform);
		TITANIUM_PROPERTY_READONLY_DEF(Stream);
		TITANIUM_PROPERTY_READONLY_DEF(UI);
		TITANIUM_PROPERTY_READONLY_DEF(Utils);
		TITANIUM_PROPERTY_READONLY_DEF(XML);

		TITANIUM_PROPERTY_READONLY_DEF(buildDate);
		TITANIUM_PROPERTY_READONLY_DEF(buildHash);
		TITANIUM_PROPERTY_DEF(userAgent);
		TITANIUM_FUNCTION_DEF(getVersion);
		TITANIUM_FUNCTION_DEF(getBuildDate);
		TITANIUM_FUNCTION_DEF(getBuildHash);
		TITANIUM_FUNCTION_DEF(getUserAgent);
		TITANIUM_FUNCTION_DEF(setUserAgent);
		TITANIUM_FUNCTION_DEF(createBuffer);

		TiModule& GlobalString(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& UIClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& APIClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ListViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ListSectionClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& AppClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& PropertiesClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& AnalyticsClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& LocaleClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& EmailDialogClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& AnimationClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& UtilsClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& SwitchClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& GeolocationClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& Matrix2DClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& Matrix3DClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& NotificationClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& TextAreaClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ClipboardClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& BufferClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& StreamClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& BufferStreamClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& BlobStreamClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& IOStreamClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& FileStreamClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& CodecClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& PickerClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& PickerColumnClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& PickerRowClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ContactsClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& GroupClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& PersonClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& WindowClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ButtonClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ImageViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& LabelClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& SliderClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& AlertDialogClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ScrollViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& TextFieldClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& PlatformClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& AccelerometerClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& GestureClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& BlobClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& FileClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& FilesystemClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& DatabaseClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& WebViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& HTTPClientClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& CookieClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& NetworkClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& TCPClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& UDPClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& MediaClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& AudioPlayerClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& AudioRecorderClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& AudioItemClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& MusicPlayerClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& SoundClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& VideoPlayerClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& XMLClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& Tab(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& TabGroup(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& TableViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& TableViewSectionClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& TableViewRowClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& MapClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& MapViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& MapAnnotationClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& MapCameraClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& MapRouteClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ActivityIndicatorClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ActivityIndicatorStyleClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& OptionDialogClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ProgressBarClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& ScrollableViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& SearchBarClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& AttributedStringClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& CalendarClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& CalendarEventClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& CalendarAlertClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& CalendarAttendeeClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& CalendarRecurrenceRuleClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& CalendarReminderClass(const JSClass&) TITANIUM_NOEXCEPT;
		TiModule& CalendarCalendarClass(const JSClass&) TITANIUM_NOEXCEPT;

		void build() TITANIUM_NOEXCEPT;
	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		std::string userAgent__;

		JSClass global_string__;
		JSClass ti__;
		JSClass ui__;
		JSClass api__;
		JSClass locale__;
		JSClass view__;
		JSClass pickerrow__;
		JSClass pickercolumn__;
		JSClass picker__;
		JSClass codec__;
		JSClass stream__;
		JSClass filestream__;
		JSClass iostream__;
		JSClass bufferstream__;
		JSClass blobstream__;
		JSClass buffer__;
		JSClass person__;
		JSClass group__;
		JSClass contacts__;
		JSClass clipboard__;
		JSClass textarea__;
		JSClass notification__;
		JSClass matrix2d__;
		JSClass matrix3d__;
		JSClass geolocation__;
		JSClass switch__;
		JSClass utils__;
		JSClass animation__;
		JSClass listsection__;
		JSClass listview__;
		JSClass emaildialog__;
		JSClass properties__;
		JSClass app__;
		JSClass analytics__;
		JSClass window__;
		JSClass button__;
		JSClass alertDialog__;
		JSClass imageview__;
		JSClass label__;
		JSClass slider__;
		JSClass scrollview__;
		JSClass textField__;
		JSClass platform__;
		JSClass accelerometer__;
		JSClass gesture__;
		JSClass blob__;
		JSClass file__;
		JSClass filesystem__;
		JSClass database__;
		JSClass webview__;
		JSClass httpclient__;
		JSClass cookie__;
		JSClass network__;
		JSClass tcp__;
		JSClass udp__;
		JSClass media__;
		JSClass audioplayer__;
		JSClass audiorecorder__;
		JSClass audioitem__;
		JSClass musicplayer__;
		JSClass sound__;
		JSClass videoplayer__;
		JSClass xml__;
		JSClass tab__;
		JSClass tabgroup__;
		JSClass tableview__;
		JSClass tableviewsection__;
		JSClass tableviewrow__;
		JSClass map__;
		JSClass mapAnnotation__;
		JSClass mapCamera__;
		JSClass mapRoute__;
		JSClass mapView__;
		JSClass activityIndicator__;
		JSClass activityIndicatorStyle__;
		JSClass optionDialog__;
		JSClass progressBar__;
		JSClass scrollableView__;
		JSClass searchBar__;
		JSClass attributedString__;
		JSClass calendar__;
		JSClass calendarAlert__;
		JSClass calendarAttendee__;
		JSClass calendarEvent__;
		JSClass calendarRecurrenceRule__;
		JSClass calendarReminder__;
		JSClass calendarCalendar__;

#pragma warning(pop)

	};

}  // namespace Titanium

#endif  // _TITANIUM_TIMODULE_HPP_
