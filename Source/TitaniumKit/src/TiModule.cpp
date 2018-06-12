/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/TiModule.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/GlobalString.hpp"
#include "Titanium/UIModule.hpp"
#include "Titanium/Codec.hpp"
#include "Titanium/Contacts/Person.hpp"
#include "Titanium/Contacts/Group.hpp"
#include "Titanium/Contacts.hpp"
#include "Titanium/UI/Clipboard.hpp"
#include "Titanium/API.hpp"
#include "Titanium/Locale.hpp"
#include "Titanium/UI/View.hpp"
#include "Titanium/UI/TextArea.hpp"
#include "Titanium/UI/Notification.hpp"
#include "Titanium/UI/2DMatrix.hpp"
#include "Titanium/GeolocationModule.hpp"
#include "Titanium/UI/Switch.hpp"
#include "Titanium/Utils.hpp"
#include "Titanium/UI/Animation.hpp"
#include "Titanium/UI/ListSection.hpp"
#include "Titanium/UI/ListView.hpp"
#include "Titanium/UI/EmailDialog.hpp"
#include "Titanium/App/Properties.hpp"
#include "Titanium/App.hpp"
#include "Titanium/Analytics.hpp"
#include "Titanium/IOStream.hpp"
#include "Titanium/Buffer.hpp"
#include "Titanium/BufferStream.hpp"
#include "Titanium/BlobStream.hpp"
#include "Titanium/Stream.hpp"
#include "Titanium/UI/Window.hpp"
#include "Titanium/UI/Button.hpp"
#include "Titanium/UI/AlertDialog.hpp"
#include "Titanium/UI/ImageView.hpp"
#include "Titanium/UI/Label.hpp"
#include "Titanium/UI/Picker.hpp"
#include "Titanium/UI/PickerRow.hpp"
#include "Titanium/UI/PickerColumn.hpp"
#include "Titanium/UI/Slider.hpp"
#include "Titanium/UI/ScrollView.hpp"
#include "Titanium/UI/Tab.hpp"
#include "Titanium/UI/TabGroup.hpp"
#include "Titanium/UI/TextField.hpp"
#include "Titanium/PlatformModule.hpp"
#include "Titanium/Accelerometer.hpp"
#include "Titanium/Gesture.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/Filesystem/File.hpp"
#include "Titanium/Filesystem/FileStream.hpp"
#include "Titanium/FilesystemModule.hpp"
#include "Titanium/DatabaseModule.hpp"
#include "Titanium/UI/WebView.hpp"
#include "Titanium/Network/HTTPClient.hpp"
#include "Titanium/Network/Cookie.hpp"
#include "Titanium/NetworkModule.hpp"
#include "Titanium/Network/Socket.hpp"
#include "Titanium/Network/Socket/TCP.hpp"
#include "Titanium/Network/Socket/UDP.hpp"
#include "Titanium/MediaModule.hpp"
#include "Titanium/Media/AudioPlayer.hpp"
#include "Titanium/Media/AudioRecorder.hpp"
#include "Titanium/Media/Item.hpp"
#include "Titanium/Media/MusicPlayer.hpp"
#include "Titanium/Media/Sound.hpp"
#include "Titanium/Media/VideoPlayer.hpp"
#include "Titanium/XML.hpp"
#include "Titanium/MapModule.hpp"
#include "Titanium/Map/Annotation.hpp"
#include "Titanium/Map/Camera.hpp"
#include "Titanium/Map/Route.hpp"
#include "Titanium/Map/View.hpp"
#include "Titanium/UI/TableView.hpp"
#include "Titanium/UI/TableViewSection.hpp"
#include "Titanium/UI/TableViewRow.hpp"
#include "Titanium/UI/ActivityIndicator.hpp"
#include "Titanium/UI/ActivityIndicatorStyle.hpp"
#include "Titanium/UI/OptionDialog.hpp"
#include "Titanium/UI/ProgressBar.hpp"
#include "Titanium/UI/ScrollableView.hpp"
#include "Titanium/UI/SearchBar.hpp"
#include "Titanium/UI/AttributedString.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium
{
	TiModule::TiModule(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context, "Ti"),
		  global_string__(JSExport<Titanium::GlobalString>::Class()),
		  ui__(JSExport<Titanium::UIModule>::Class()),
		  api__(JSExport<Titanium::API>::Class()),
		  buffer__(JSExport<Titanium::Buffer>::Class()),
		  bufferstream__(JSExport<Titanium::BufferStream>::Class()),
		  blobstream__(JSExport<Titanium::BlobStream>::Class()),
		  iostream__(JSExport<Titanium::IOStream>::Class()),
		  stream__(JSExport<Titanium::Stream>::Class()),
		  locale__(JSExport<Titanium::Locale>::Class()),
		  view__(JSExport<Titanium::UI::View>::Class()),
		  codec__(JSExport<Titanium::Codec::CodecModule>::Class()),
	      person__(JSExport<Titanium::Contacts::Person>::Class()),
	      group__(JSExport<Titanium::Contacts::Group>::Class()),
	      contacts__(JSExport<Titanium::ContactsModule>::Class()),
		  clipboard__(JSExport<Titanium::UI::Clipboard>::Class()),
		  textarea__(JSExport<Titanium::UI::TextArea>::Class()),
		  notification__(JSExport<Titanium::UI::Notification>::Class()),
		  twodmatrix__(JSExport<Titanium::UI::TwoDMatrix>::Class()),
		  geolocation__(JSExport<Titanium::GeolocationModule>::Class()),
		  switch__(JSExport<Titanium::UI::Switch>::Class()),
		  utils__(JSExport<Titanium::Utils>::Class()),
		  animation__(JSExport<Titanium::UI::Animation>::Class()),
		  listsection__(JSExport<Titanium::UI::ListSection>::Class()),
		  listview__(JSExport<Titanium::UI::ListView>::Class()),
		  emaildialog__(JSExport<Titanium::UI::EmailDialog>::Class()),
		  properties__(JSExport<Titanium::App::Properties>::Class()),
		  app__(JSExport<Titanium::AppModule>::Class()),
		  analytics__(JSExport<Titanium::Analytics>::Class()),
		  window__(JSExport<Titanium::UI::Window>::Class()),
		  button__(JSExport<Titanium::UI::Button>::Class()),
		  alertDialog__(JSExport<Titanium::UI::AlertDialog>::Class()),
		  imageview__(JSExport<Titanium::UI::ImageView>::Class()),
		  label__(JSExport<Titanium::UI::Label>::Class()),
		  slider__(JSExport<Titanium::UI::Slider>::Class()),
		  scrollview__(JSExport<Titanium::UI::ScrollView>::Class()),
		  textField__(JSExport<Titanium::UI::TextField>::Class()),
		  platform__(JSExport<Titanium::PlatformModule>::Class()),
		  accelerometer__(JSExport<Titanium::Accelerometer>::Class()),
		  gesture__(JSExport<Titanium::Gesture>::Class()),
		  blob__(JSExport<Titanium::Blob>::Class()),
		  file__(JSExport<Titanium::Filesystem::File>::Class()),
		  filesystem__(JSExport<Titanium::FilesystemModule>::Class()),
		  filestream__(JSExport<Titanium::Filesystem::FileStream>::Class()),
		  database__(JSExport<Titanium::DatabaseModule>::Class()),
		  webview__(JSExport<Titanium::UI::WebView>::Class()),
		  httpclient__(JSExport<Titanium::Network::HTTPClient>::Class()),
		  cookie__(JSExport<Titanium::Network::Cookie>::Class()),
		  network__(JSExport<Titanium::NetworkModule>::Class()),
		  tcp__(JSExport<Titanium::Network::Socket::TCP>::Class()),
		  udp__(JSExport<Titanium::Network::Socket::UDP>::Class()),
		  media__(JSExport<Titanium::MediaModule>::Class()),
		  audioplayer__(JSExport<Titanium::Media::AudioPlayer>::Class()),
		  audiorecorder__(JSExport<Titanium::Media::AudioRecorder>::Class()),
		  audioitem__(JSExport<Titanium::Media::Item>::Class()),
		  musicplayer__(JSExport<Titanium::Media::MusicPlayer>::Class()),
		  sound__(JSExport<Titanium::Media::Sound>::Class()),
		  videoplayer__(JSExport<Titanium::Media::VideoPlayer>::Class()),
		  xml__(JSExport<Titanium::XML>::Class()),
		  map__(JSExport<Titanium::MapModule>::Class()),
		  mapAnnotation__(JSExport<Titanium::Map::Annotation>::Class()),
		  mapCamera__(JSExport<Titanium::Map::Camera>::Class()),
		  mapRoute__(JSExport<Titanium::Map::Route>::Class()),
		  mapView__(JSExport<Titanium::Map::View>::Class()),
		  tab__(JSExport<Titanium::UI::Tab>::Class()),
		  tabgroup__(JSExport<Titanium::UI::TabGroup>::Class()),
		  tableview__(JSExport<Titanium::UI::TableView>::Class()),
		  tableviewsection__(JSExport<Titanium::UI::TableViewSection>::Class()),
		  tableviewrow__(JSExport<Titanium::UI::TableViewRow>::Class()),
		  activityIndicator__(JSExport<Titanium::UI::ActivityIndicator>::Class()),
		  activityIndicatorStyle__(JSExport<Titanium::UI::ActivityIndicatorStyle>::Class()),
		  optionDialog__(JSExport<Titanium::UI::OptionDialog>::Class()),
		  progressBar__(JSExport<Titanium::UI::ProgressBar>::Class()),
		  picker__(JSExport<Titanium::UI::Picker>::Class()),
		  pickerrow__(JSExport<Titanium::UI::PickerRow>::Class()),
		  pickercolumn__(JSExport<Titanium::UI::PickerColumn>::Class()),
		  scrollableView__(JSExport<Titanium::UI::ScrollableView>::Class()),
		  searchBar__(JSExport<Titanium::UI::SearchBar>::Class()),
		  attributedString__(JSExport<Titanium::UI::AttributedString>::Class()),
	      userAgent__(js_context.CreateString())
	{
		TITANIUM_LOG_DEBUG("TiModule:: ctor ", this);
	}

	void TiModule::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
	{
		HAL_LOG_DEBUG("TiModule:: postCallAsConstructor ", this);
	}

	void TiModule::JSExportInitialize()
	{
		JSExport<TiModule>::SetClassVersion(1);
		JSExport<TiModule>::SetParent(JSExport<Module>::Class());
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, version);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, buildDate);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, buildHash);

		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Accelerometer);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Analytics);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, API);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, App);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Blob);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, BlobStream);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Buffer);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, BufferStream);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Codec);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Contacts);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Database);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Filesystem);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Geolocation);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Gesture);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, IOStream);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Locale);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Map);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Media);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Network);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Platform);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Stream);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, UI);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, Utils);
		TITANIUM_ADD_CONSTANT_PROPERTY(TiModule, XML);

		TITANIUM_ADD_PROPERTY(TiModule, userAgent);
		TITANIUM_ADD_FUNCTION(TiModule, getVersion);
		TITANIUM_ADD_FUNCTION(TiModule, getBuildDate);
		TITANIUM_ADD_FUNCTION(TiModule, getBuildHash);
		TITANIUM_ADD_FUNCTION(TiModule, getUserAgent);
		TITANIUM_ADD_FUNCTION(TiModule, setUserAgent);
		TITANIUM_ADD_FUNCTION(TiModule, createBuffer);
	}

	JSObject TiModule::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		return static_cast<JSObject>(Titanium_property);
	}

	std::string TiModule::version() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("TiModule::version: Unimplemented");
		return "";
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Accelerometer)
	{
		return get_context().CreateObject(accelerometer__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Analytics)
	{
		return get_context().CreateObject(analytics__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, API)
	{
		return get_context().CreateObject(api__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, App)
	{
		auto app = get_context().CreateObject(app__);
		auto app_ptr = app.GetPrivate<Titanium::AppModule>();
		app_ptr->PropertiesClass(properties__);
		return app;
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Blob)
	{
		return get_context().CreateObject(blob__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, BlobStream)
	{
		return get_context().CreateObject(blobstream__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Buffer)
	{
		return get_context().CreateObject(buffer__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, BufferStream)
	{
		return get_context().CreateObject(bufferstream__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Codec)
	{
		return get_context().CreateObject(codec__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Contacts)
	{
		auto contacts = get_context().CreateObject(contacts__);
		auto contacts_ptr = contacts.GetPrivate<Titanium::ContactsModule>();
		contacts_ptr->GroupClass(group__).PersonClass(person__);
		return contacts;
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Database)
	{
		return get_context().CreateObject(database__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Filesystem)
	{
		auto fs = get_context().CreateObject(filesystem__);
		auto fs_ptr = fs.GetPrivate<Titanium::FilesystemModule>();

		fs_ptr->FileClass(file__).FileStreamClass(filestream__);

		return fs;
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Geolocation)
	{
		return get_context().CreateObject(geolocation__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Gesture)
	{
		return get_context().CreateObject(gesture__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, IOStream)
	{
		return get_context().CreateObject(iostream__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Locale)
	{
		return get_context().CreateObject(locale__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Map)
	{
		auto map = get_context().CreateObject(map__);
		auto map_ptr = map.GetPrivate<Titanium::MapModule>();
		map_ptr->AnnotationClass(mapAnnotation__).
			CameraClass(mapCamera__).
			RouteClass(mapRoute__).
			ViewClass(mapView__);
		return  map;
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Media)
	{
		auto media = get_context().CreateObject(media__);
		auto media_ptr = media.GetPrivate<Titanium::MediaModule>();
		media_ptr->AudioPlayerClass(audioplayer__).
			AudioRecorderClass(audiorecorder__).
			ItemClass(audioitem__).
			MusicPlayerClass(musicplayer__).
			SoundClass(sound__).
			VideoPlayerClass(videoplayer__);
		return media;
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Network)
	{
		const auto ctx = get_context();
		auto network = ctx.CreateObject(network__);
		auto network_ptr = network.GetPrivate<Titanium::NetworkModule>();

		network_ptr->HTTPClientClass(httpclient__).CookieClass(cookie__);

		// Create socket instance here, just like ApplicationBuilder does
		auto socket = ctx.CreateObject(JSExport<Titanium::Network::SocketModule>::Class());
		auto socket_ptr = socket.GetPrivate<Titanium::Network::SocketModule>();
		socket_ptr->TCPClass(tcp__).UDPClass(udp__);
		network.SetProperty("Socket", socket);

		return network;
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Platform)
	{
		return get_context().CreateObject(platform__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Stream)
	{
		return get_context().CreateObject(stream__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, UI)
	{
		auto ui = get_context().CreateObject(ui__);
		auto ui_ptr = ui.GetPrivate<Titanium::UIModule>();

		ui_ptr->ListViewClass(listview__).
			ListSectionClass(listsection__).
			EmailDialogClass(emaildialog__).
			AnimationClass(animation__).
			SwitchClass(switch__).
			TwoDMatrixClass(twodmatrix__).
			NotificationClass(notification__).
			TextAreaClass(textarea__).
			ClipboardClass(clipboard__).
			PickerClass(picker__).
			PickerColumnClass(pickercolumn__).
			PickerRowClass(pickerrow__).
			ViewClass(view__).
			WindowClass(window__).
			ButtonClass(button__).
			ImageViewClass(imageview__).
			LabelClass(label__).
			SliderClass(slider__).
			AlertDialogClass(alertDialog__).
			ScrollViewClass(scrollview__).
			TextFieldClass(textField__).
			WebViewClass(webview__).
			Tab(tab__).
			TabGroup(tabgroup__).
			TableViewClass(tableview__).
			TableViewSectionClass(tableviewsection__).
			TableViewRowClass(tableviewrow__).
			ActivityIndicatorClass(activityIndicator__).
			ActivityIndicatorStyleClass(activityIndicatorStyle__).
			OptionDialogClass(optionDialog__).
			ProgressBarClass(progressBar__).
			ScrollableViewClass(scrollableView__).
			SearchBarClass(searchBar__).
			AttributedStringClass(attributedString__);

		return ui;
	}

	TITANIUM_PROPERTY_GETTER(TiModule, Utils)
	{
		return get_context().CreateObject(utils__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, XML)
	{
		return get_context().CreateObject(xml__);
	}

	TITANIUM_PROPERTY_GETTER(TiModule, version)
	{
		return get_context().CreateString(version());
	}

	TITANIUM_FUNCTION(TiModule, getVersion)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<TiModule>();
		return object_ptr->js_get_version();
	}

	std::string TiModule::buildDate() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("TiModule::buildDate: Unimplemented");
		return "";
	}

	TITANIUM_PROPERTY_GETTER(TiModule, buildDate)
	{
		return get_context().CreateString(buildDate());
	}

	TITANIUM_FUNCTION(TiModule, getBuildDate)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<TiModule>();
		return object_ptr->js_get_buildDate();
	}

	std::string TiModule::buildHash() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("TiModule::buildHash: Unimplemented");
		return "";
	}

	void TiModule::build() TITANIUM_NOEXCEPT
	{
		const auto ctx = get_context();

		auto global_object = ctx.get_global_object();
		auto global_string = ctx.CreateObject(global_string__);
		auto titanium = get_object();

		global_object.SetProperty("Titanium", titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		global_object.SetProperty("Ti", titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});

		// Attach all Ti.String properties onto global String
		auto stringObj = static_cast<JSObject>(global_object.GetProperty("String"));
		for (const auto& property_name : static_cast<std::vector<JSString>>(global_string.GetPropertyNames())) {
			stringObj.SetProperty(property_name, global_string.GetProperty(property_name));
		}

		// Titanium.String keeps a reference to Global.String module
		titanium.SetProperty("String", global_string, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });

		JSString builtin_functions_script = R"js(
			try {
				console = {};
				console._times = {};
				console.log   = Ti.API.info;
				console.info  = Ti.API.info;
				console.warn  = Ti.API.warn;
				console.error = Ti.API.error;
				console.debug = Ti.API.debug;
				console.time = function (label) {
					if (console._times[label]) {
						console.warn('Label "' + label + '" already exists');
						return;
					}
					if (!label) {
						label = 'default';
					}
					console._times[label] = Date.now();
				};
				console.timeEnd = function (label) {
					if (!label) {
						label = 'default';
					}
					var startTime = console._times[label];
					if (!startTime) {
						console.warn('Label "' + label + '" does not exist');
						return;
					}
					var duration = Date.now() - startTime;
					console.log(label + ': ' + duration + 'ms');
					delete console._times[label];
				};
			

				// Create the global alert function
				alert = function (_msg) {
					Ti.UI.createAlertDialog({
						title: '',
						message: _msg + ''
					}).show();
				};

				// Load _app_info_.json
				Ti.App._loadAppInfo();
				// Load _app_props_.json
				Ti.App.Properties._loadAppProperties();

				// Let's set up our user agent in JS, way easier this way...
				Ti.userAgent = 'Appcelerator Titanium/' + Ti.version + ' (' + Ti.Platform.model + '/' + Ti.Platform.version + '; ' + Ti.Platform.osname + '; ' + Ti.Platform.locale + ';)';

				Ti.Network.encodeURIComponent = encodeURIComponent;
				Ti.Network.decodeURIComponent = decodeURIComponent;

				// Start analytics
				Ti.Analytics._start();

				L = Ti.Locale.getString;
			} catch (E) {
				Ti.API.error("Failed to initialize Titanium: " + E.toString());
			}
			)js";

		get_context().JSEvaluateScript(builtin_functions_script);
	}

	TiModule& TiModule::GlobalString(const JSClass& global_string) TITANIUM_NOEXCEPT
	{
		global_string__ = global_string;
		return *this;
	}

	TiModule& TiModule::UIClass(const JSClass& ui) TITANIUM_NOEXCEPT
	{
		ui__ = ui;
		return *this;
	}

	TiModule& TiModule::APIClass(const JSClass& api) TITANIUM_NOEXCEPT
	{
		api__ = api;
		return *this;
	}

	TiModule& TiModule::BufferClass(const JSClass& buffer) TITANIUM_NOEXCEPT
	{
		buffer__ = buffer;
		return *this;
	}

	TiModule& TiModule::BufferStreamClass(const JSClass& bufferstream) TITANIUM_NOEXCEPT
	{
		bufferstream__ = bufferstream;
		return *this;
	}

	TiModule& TiModule::BlobStreamClass(const JSClass& blobstream) TITANIUM_NOEXCEPT
	{
		blobstream__ = blobstream;
		return *this;
	}

	TiModule& TiModule::IOStreamClass(const JSClass& iostream) TITANIUM_NOEXCEPT
	{
		iostream__ = iostream;
		return *this;
	}

	TiModule& TiModule::LocaleClass(const JSClass& locale) TITANIUM_NOEXCEPT
	{
		locale__ = locale;
		return *this;
	}

	TiModule& TiModule::ListViewClass(const JSClass& ListView) TITANIUM_NOEXCEPT
	{
		listview__ = ListView;
		return *this;
	}

	TiModule& TiModule::ListSectionClass(const JSClass& ListSection) TITANIUM_NOEXCEPT
	{
		listsection__ = ListSection;
		return *this;
	}

	TiModule& TiModule::AppClass(const JSClass& App) TITANIUM_NOEXCEPT
	{
		app__ = App;
		return *this;
	}

	TiModule& TiModule::PropertiesClass(const JSClass& Properties) TITANIUM_NOEXCEPT
	{
		properties__ = Properties;
		return *this;
	}

	TiModule& TiModule::AnalyticsClass(const JSClass& analytics) TITANIUM_NOEXCEPT
	{
		analytics__ = analytics;
		return *this;
	}

	TiModule& TiModule::EmailDialogClass(const JSClass& EmailDialog) TITANIUM_NOEXCEPT
	{
		emaildialog__ = EmailDialog;
		return *this;
	}

	TiModule& TiModule::AnimationClass(const JSClass& Animation) TITANIUM_NOEXCEPT
	{
		animation__ = Animation;
		return *this;
	}

	TiModule& TiModule::UtilsClass(const JSClass& Utils) TITANIUM_NOEXCEPT
	{
		utils__ = Utils;
		return *this;
	}

	TiModule& TiModule::SwitchClass(const JSClass& Switch) TITANIUM_NOEXCEPT
	{
		switch__ = Switch;
		return *this;
	}

	TiModule& TiModule::GeolocationClass(const JSClass& Geolocation) TITANIUM_NOEXCEPT
	{
		geolocation__ = Geolocation;
		return *this;
	}


	TiModule& TiModule::TwoDMatrixClass(const JSClass& TwoDMatrix) TITANIUM_NOEXCEPT
	{
		twodmatrix__ = TwoDMatrix;
		return *this;
	}

	TiModule& TiModule::NotificationClass(const JSClass& Notification) TITANIUM_NOEXCEPT
	{
		notification__ = Notification;
		return *this;
	}

	TiModule& TiModule::TextAreaClass(const JSClass& TextArea) TITANIUM_NOEXCEPT
	{
		textarea__ = TextArea;
		return *this;
	}

	TiModule& TiModule::ClipboardClass(const JSClass& Clipboard) TITANIUM_NOEXCEPT
	{
		clipboard__ = Clipboard;
		return *this;
	}

	TiModule& TiModule::CodecClass(const JSClass& codec) TITANIUM_NOEXCEPT
	{
		codec__ = codec;
		return *this;
	}

	TiModule& TiModule::ContactsClass(const JSClass& Contacts) TITANIUM_NOEXCEPT
	{
		contacts__ = Contacts;
		return *this;
	}

	TiModule& TiModule::GroupClass(const JSClass& Group) TITANIUM_NOEXCEPT
	{
		group__ = Group;
		return *this;
	}

	TiModule& TiModule::PersonClass(const JSClass& Person) TITANIUM_NOEXCEPT
	{
		person__ = Person;
		return *this;
	}

	TiModule& TiModule::ViewClass(const JSClass& View) TITANIUM_NOEXCEPT
	{
		view__ = View;
		return *this;
	}

	TiModule& TiModule::WindowClass(const JSClass& window) TITANIUM_NOEXCEPT
	{
		window__ = window;
		return *this;
	}

	TiModule& TiModule::ButtonClass(const JSClass& button) TITANIUM_NOEXCEPT
	{
		button__ = button;
		return *this;
	}

	TiModule& TiModule::SliderClass(const JSClass& slider) TITANIUM_NOEXCEPT
	{
		slider__ = slider;
		return *this;
	}

	TiModule& TiModule::AlertDialogClass(const JSClass& alertDialog) TITANIUM_NOEXCEPT
	{
		alertDialog__ = alertDialog;
		return *this;
	}

	TiModule& TiModule::ImageViewClass(const JSClass& imageview) TITANIUM_NOEXCEPT
	{
		imageview__ = imageview;
		return *this;
	}

	TiModule& TiModule::LabelClass(const JSClass& label) TITANIUM_NOEXCEPT
	{
		label__ = label;
		return *this;
	}

	TiModule& TiModule::ScrollViewClass(const JSClass& view) TITANIUM_NOEXCEPT
	{
		scrollview__ = view;
		return *this;
	}

	TiModule& TiModule::TextFieldClass(const JSClass& view) TITANIUM_NOEXCEPT
	{
		textField__ = view;
		return *this;
	}

	TiModule& TiModule::PlatformClass(const JSClass& platform) TITANIUM_NOEXCEPT
	{
		platform__ = platform;
		return *this;
	}

	TiModule& TiModule::AccelerometerClass(const JSClass& accelerometer) TITANIUM_NOEXCEPT
	{
		accelerometer__ = accelerometer;
		return *this;
	}

	TiModule& TiModule::GestureClass(const JSClass& gesture) TITANIUM_NOEXCEPT
	{
		gesture__ = gesture;
		return *this;
	}

	TiModule& TiModule::BlobClass(const JSClass& blob) TITANIUM_NOEXCEPT
	{
		blob__ = blob;
		return *this;
	}

	TiModule& TiModule::FileClass(const JSClass& file) TITANIUM_NOEXCEPT
	{
		file__ = file;
		return *this;
	}

	TiModule& TiModule::FileStreamClass(const JSClass& filestream) TITANIUM_NOEXCEPT
	{
		filestream__ = filestream;
		return *this;
	}

	TiModule& TiModule::FilesystemClass(const JSClass& filesystem) TITANIUM_NOEXCEPT
	{
		filesystem__ = filesystem;
		return *this;
	}

	TiModule& TiModule::DatabaseClass(const JSClass& database) TITANIUM_NOEXCEPT
	{
		database__ = database;
		return *this;
	}

	TiModule& TiModule::WebViewClass(const JSClass& webview) TITANIUM_NOEXCEPT
	{
		webview__ = webview;
		return *this;
	}

	TiModule& TiModule::HTTPClientClass(const JSClass& httpclient) TITANIUM_NOEXCEPT
	{
		httpclient__ = httpclient;
		return *this;
	}

	TiModule& TiModule::CookieClass(const JSClass& cookie) TITANIUM_NOEXCEPT
	{
		cookie__ = cookie;
		return *this;
	}

	TiModule& TiModule::NetworkClass(const JSClass& network) TITANIUM_NOEXCEPT
	{
		network__ = network;
		return *this;
	}

	TiModule& TiModule::TCPClass(const JSClass& tcp) TITANIUM_NOEXCEPT
	{
		tcp__ = tcp;
		return *this;
	}

	TiModule& TiModule::UDPClass(const JSClass& udp) TITANIUM_NOEXCEPT
	{
		udp__ = udp;
		return *this;
	}

	TiModule& TiModule::MediaClass(const JSClass& media) TITANIUM_NOEXCEPT
	{
		media__ = media;
		return *this;
	}

	TiModule& TiModule::AudioPlayerClass(const JSClass& player) TITANIUM_NOEXCEPT
	{
		audioplayer__ = player;
		return *this;
	}

	TiModule& TiModule::AudioRecorderClass(const JSClass& recorder) TITANIUM_NOEXCEPT
	{
		audiorecorder__ = recorder;
		return *this;
	}

	TiModule& TiModule::AudioItemClass(const JSClass& item) TITANIUM_NOEXCEPT
	{
		audioitem__ = item;
		return *this;
	}

	TiModule& TiModule::MusicPlayerClass(const JSClass& player) TITANIUM_NOEXCEPT
	{
		musicplayer__ = player;
		return *this;
	}

	TiModule& TiModule::SoundClass(const JSClass& sound) TITANIUM_NOEXCEPT
	{
		sound__ = sound;
		return *this;
	}

	TiModule& TiModule::VideoPlayerClass(const JSClass& player) TITANIUM_NOEXCEPT
	{
		videoplayer__ = player;
		return *this;
	}

	TiModule& TiModule::XMLClass(const JSClass& XML) TITANIUM_NOEXCEPT
	{
		xml__ = XML;
		return *this;
	}

	TiModule& TiModule::Tab(const JSClass& view) TITANIUM_NOEXCEPT
	{
		tab__ = view;
		return *this;
	}

	TiModule& TiModule::TabGroup(const JSClass& view) TITANIUM_NOEXCEPT
	{
		tabgroup__ = view;
		return *this;
	}

	TiModule& TiModule::TableViewClass(const JSClass& TableView) TITANIUM_NOEXCEPT
	{
		tableview__ = TableView;
		return *this;
	}

	TiModule& TiModule::TableViewSectionClass(const JSClass& TableViewSection) TITANIUM_NOEXCEPT
	{
		tableviewsection__ = TableViewSection;
		return *this;
	}

	TiModule& TiModule::TableViewRowClass(const JSClass& TableViewRow) TITANIUM_NOEXCEPT
	{
		tableviewrow__ = TableViewRow;
		return *this;
	}

	TiModule& TiModule::MapClass(const JSClass& Map) TITANIUM_NOEXCEPT
	{
		map__ = Map;
		return *this;
	}

	TiModule& TiModule::MapAnnotationClass(const JSClass& mapAnnotation) TITANIUM_NOEXCEPT
	{
		mapAnnotation__ = mapAnnotation;
		return *this;
	}

	TiModule& TiModule::MapCameraClass(const JSClass& mapCamera) TITANIUM_NOEXCEPT
	{
		mapCamera__ = mapCamera;
		return *this;
	}

	TiModule& TiModule::MapRouteClass(const JSClass& mapRoute) TITANIUM_NOEXCEPT
	{
		mapRoute__ = mapRoute;
		return *this;
	}

	TiModule& TiModule::MapViewClass(const JSClass& mapView) TITANIUM_NOEXCEPT
	{
		mapView__ = mapView;
		return *this;
	}

	TiModule& TiModule::ActivityIndicatorClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		activityIndicator__ = value;
		return *this;
	}

	TiModule& TiModule::ActivityIndicatorStyleClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		activityIndicatorStyle__ = value;
		return *this;
	}

	TiModule& TiModule::OptionDialogClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		optionDialog__ = value;
		return *this;
	}

	TiModule& TiModule::ProgressBarClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		progressBar__ = value;
		return *this;
	}

	TiModule& TiModule::PickerClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		picker__ = value;
		return *this;
	}

	TiModule& TiModule::PickerRowClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		pickerrow__ = value;
		return *this;
	}

	TiModule& TiModule::PickerColumnClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		pickercolumn__ = value;
		return *this;
	}

	TiModule& TiModule::ScrollableViewClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		scrollableView__ = value;
		return *this;
	}

	TiModule& TiModule::SearchBarClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		searchBar__ = value;
		return *this;
	}

	TiModule& TiModule::AttributedStringClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		attributedString__ = value;
		return *this;
	}

	TITANIUM_PROPERTY_GETTER(TiModule, buildHash)
	{
		return get_context().CreateString(buildHash());
	}

	TITANIUM_FUNCTION(TiModule, getBuildHash)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<TiModule>();
		return object_ptr->js_get_buildHash();
	}

	TITANIUM_PROPERTY_GETTER(TiModule, userAgent)
	{
		return get_context().CreateString(userAgent__);
	}

	TITANIUM_FUNCTION(TiModule, getUserAgent)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<TiModule>();
		return object_ptr->js_get_userAgent();
	}

	TITANIUM_FUNCTION(TiModule, setUserAgent)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<TiModule>();

		object_ptr->js_set_userAgent(arguments.at(0));

		return get_context().CreateUndefined();
	}

	void TiModule::setUserAgent(const std::string& userAgent) TITANIUM_NOEXCEPT
	{
		userAgent__ = userAgent;
	}

	TITANIUM_PROPERTY_SETTER(TiModule, userAgent)
	{
		setUserAgent(static_cast<std::string>(argument));
		return true;
	}

	TITANIUM_FUNCTION(TiModule, createBuffer)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);

		JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());
		JSObject Titanium = static_cast<JSObject>(Titanium_property);
		JSValue Buffer_property = Titanium.GetProperty("Buffer");
		TITANIUM_ASSERT(Buffer_property.IsObject());
		JSObject Buffer = static_cast<JSObject>(Buffer_property);
		auto Buffer_obj = Buffer.CallAsConstructor(parameters);
		Titanium::Module::applyProperties(parameters, Buffer_obj);

		return Buffer_obj;
	}

}  // namespace Titanium
