/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */


#include "Titanium/ApplicationBuilder.hpp"
#include "Titanium/Application.hpp"

#include "Titanium/GlobalString.hpp"
#include "Titanium/TiModule.hpp"
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

namespace Titanium
{
	ApplicationBuilder::ApplicationBuilder(const JSContext& js_context) TITANIUM_NOEXCEPT
		: js_context__(js_context),
		  global_object__(js_context__.get_global_object()),
		  global_string__(js_context__.CreateObject(JSExport<Titanium::GlobalString>::Class())),
		  ti__(js_context__.CreateObject(JSExport<Titanium::TiModule>::Class())),
		  ui__(js_context__.CreateObject(JSExport<Titanium::UIModule>::Class())),
		  api__(js_context__.CreateObject(JSExport<Titanium::API>::Class())),
		  buffer__(js_context__.CreateObject(JSExport<Titanium::Buffer>::Class())),
		  bufferstream__(js_context__.CreateObject(JSExport<Titanium::BufferStream>::Class())),
		  blobstream__(js_context__.CreateObject(JSExport<Titanium::BlobStream>::Class())),
		  iostream__(js_context__.CreateObject(JSExport<Titanium::IOStream>::Class())),
		  stream__(js_context__.CreateObject(JSExport<Titanium::Stream>::Class())),
		  locale__(js_context__.CreateObject(JSExport<Titanium::Locale>::Class())),
		  view__(js_context__.CreateObject(JSExport<Titanium::UI::View>::Class())),
		  codec__(js_context__.CreateObject(JSExport<Titanium::Codec::CodecModule>::Class())),
	      person__(js_context__.CreateObject(JSExport<Titanium::Contacts::Person>::Class())),
	      group__(js_context__.CreateObject(JSExport<Titanium::Contacts::Group>::Class())),
	      contacts__(js_context__.CreateObject(JSExport<Titanium::ContactsModule>::Class())),
		  clipboard__(js_context__.CreateObject(JSExport<Titanium::UI::Clipboard>::Class())),
		  textarea__(js_context__.CreateObject(JSExport<Titanium::UI::TextArea>::Class())),
		  notification__(js_context__.CreateObject(JSExport<Titanium::UI::Notification>::Class())),
		  twodmatrix__(js_context__.CreateObject(JSExport<Titanium::UI::TwoDMatrix>::Class())),
		  geolocation__(js_context__.CreateObject(JSExport<Titanium::GeolocationModule>::Class())),
		  switch__(js_context__.CreateObject(JSExport<Titanium::UI::Switch>::Class())),
		  utils__(js_context__.CreateObject(JSExport<Titanium::Utils>::Class())),
		  animation__(js_context__.CreateObject(JSExport<Titanium::UI::Animation>::Class())),
		  listsection__(js_context__.CreateObject(JSExport<Titanium::UI::ListSection>::Class())),
		  listview__(js_context__.CreateObject(JSExport<Titanium::UI::ListView>::Class())),
		  emaildialog__(js_context__.CreateObject(JSExport<Titanium::UI::EmailDialog>::Class())),
		  properties__(js_context__.CreateObject(JSExport<Titanium::App::Properties>::Class())),
		  app__(js_context__.CreateObject(JSExport<Titanium::AppModule>::Class())),
		  analytics__(js_context__.CreateObject(JSExport<Titanium::Analytics>::Class())),
		  window__(js_context__.CreateObject(JSExport<Titanium::UI::Window>::Class())),
		  button__(js_context__.CreateObject(JSExport<Titanium::UI::Button>::Class())),
		  alertDialog__(js_context__.CreateObject(JSExport<Titanium::UI::AlertDialog>::Class())),
		  imageview__(js_context__.CreateObject(JSExport<Titanium::UI::ImageView>::Class())),
		  label__(js_context__.CreateObject(JSExport<Titanium::UI::Label>::Class())),
		  slider__(js_context__.CreateObject(JSExport<Titanium::UI::Slider>::Class())),
		  scrollview__(js_context__.CreateObject(JSExport<Titanium::UI::ScrollView>::Class())),
		  textField__(js_context__.CreateObject(JSExport<Titanium::UI::TextField>::Class())),
		  platform__(js_context__.CreateObject(JSExport<Titanium::PlatformModule>::Class())),
		  accelerometer__(js_context__.CreateObject(JSExport<Titanium::Accelerometer>::Class())),
		  gesture__(js_context__.CreateObject(JSExport<Titanium::Gesture>::Class())),
		  blob__(js_context__.CreateObject(JSExport<Titanium::Blob>::Class())),
		  file__(js_context__.CreateObject(JSExport<Titanium::Filesystem::File>::Class())),
		  filesystem__(js_context__.CreateObject(JSExport<Titanium::FilesystemModule>::Class())),
		  filestream__(js_context__.CreateObject(JSExport<Titanium::Filesystem::FileStream>::Class())),
		  database__(js_context__.CreateObject(JSExport<Titanium::DatabaseModule>::Class())),
		  webview__(js_context__.CreateObject(JSExport<Titanium::UI::WebView>::Class())),
		  httpclient__(js_context__.CreateObject(JSExport<Titanium::Network::HTTPClient>::Class())),
		  cookie__(js_context__.CreateObject(JSExport<Titanium::Network::Cookie>::Class())),
		  network__(js_context__.CreateObject(JSExport<Titanium::NetworkModule>::Class())),
		  tcp__(js_context__.CreateObject(JSExport<Titanium::Network::Socket::TCP>::Class())),
		  udp__(js_context__.CreateObject(JSExport<Titanium::Network::Socket::UDP>::Class())),
		  media__(js_context__.CreateObject(JSExport<Titanium::MediaModule>::Class())),
		  audioplayer__(js_context__.CreateObject(JSExport<Titanium::Media::AudioPlayer>::Class())),
		  audiorecorder__(js_context__.CreateObject(JSExport<Titanium::Media::AudioRecorder>::Class())),
		  audioitem__(js_context__.CreateObject(JSExport<Titanium::Media::Item>::Class())),
		  musicplayer__(js_context__.CreateObject(JSExport<Titanium::Media::MusicPlayer>::Class())),
		  sound__(js_context__.CreateObject(JSExport<Titanium::Media::Sound>::Class())),
		  videoplayer__(js_context__.CreateObject(JSExport<Titanium::Media::VideoPlayer>::Class())),
		  xml__(js_context__.CreateObject(JSExport<Titanium::XML>::Class())),
		  map__(js_context__.CreateObject(JSExport<Titanium::MapModule>::Class())),
		  mapAnnotation__(js_context__.CreateObject(JSExport<Titanium::Map::Annotation>::Class())),
		  mapCamera__(js_context__.CreateObject(JSExport<Titanium::Map::Camera>::Class())),
		  mapRoute__(js_context__.CreateObject(JSExport<Titanium::Map::Route>::Class())),
		  mapView__(js_context__.CreateObject(JSExport<Titanium::Map::View>::Class())),
		  tab__(js_context__.CreateObject(JSExport<Titanium::UI::Tab>::Class())),
		  tabgroup__(js_context__.CreateObject(JSExport<Titanium::UI::TabGroup>::Class())),
		  tableview__(js_context__.CreateObject(JSExport<Titanium::UI::TableView>::Class())),
		  tableviewsection__(js_context__.CreateObject(JSExport<Titanium::UI::TableViewSection>::Class())),
		  tableviewrow__(js_context__.CreateObject(JSExport<Titanium::UI::TableViewRow>::Class())),
		  activityIndicator__(js_context__.CreateObject(JSExport<Titanium::UI::ActivityIndicator>::Class())),
		  activityIndicatorStyle__(js_context__.CreateObject(JSExport<Titanium::UI::ActivityIndicatorStyle>::Class())),
		  optionDialog__(js_context__.CreateObject(JSExport<Titanium::UI::OptionDialog>::Class())),
		  progressBar__(js_context__.CreateObject(JSExport<Titanium::UI::ProgressBar>::Class())),
		  scrollableView__(js_context__.CreateObject(JSExport<Titanium::UI::ScrollableView>::Class()))
	{
	}

	Application ApplicationBuilder::build()
	{
		ui__.SetProperty("2DMatrix", twodmatrix__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("ActivityIndicator", activityIndicator__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		ui__.SetProperty("ActivityIndicatorStyle", activityIndicatorStyle__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		ui__.SetProperty("AlertDialog", alertDialog__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("Animation", animation__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("Button", button__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("Clipboard", clipboard__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		ui__.SetProperty("EmailDialog", emaildialog__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("ImageView", imageview__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("Label", label__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("ListView", listview__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("ListSection", listsection__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("Notification", notification__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		ui__.SetProperty("OptionDialog", optionDialog__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		ui__.SetProperty("ProgressBar", progressBar__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		ui__.SetProperty("ScrollableView", scrollableView__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		ui__.SetProperty("ScrollView", scrollview__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("Slider", slider__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("Switch", switch__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("Tab",tab__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("TabGroup",tabgroup__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("TableView",tableview__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("TableViewSection", tableviewsection__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("TableViewRow", tableviewrow__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("TextArea", textarea__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		ui__.SetProperty("TextField", textField__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("View", view__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("WebView", webview__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		ui__.SetProperty("Window", window__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		
		filesystem__.SetProperty("File", file__);
		filesystem__.SetProperty("FileStream", filestream__);

		JSObject socket__ = js_context__.CreateObject(JSExport<Titanium::Network::SocketModule>::Class());
		socket__.SetProperty("TCP", tcp__);
		socket__.SetProperty("UDP", udp__);
		network__.SetProperty("Socket", socket__);
		network__.SetProperty("HTTPClient", httpclient__);
		network__.SetProperty("Cookie", cookie__);

		media__.SetProperty("AudioPlayer", audioplayer__);
		media__.SetProperty("AudioRecorder", audiorecorder__);
		media__.SetProperty("Item", audioitem__);
		media__.SetProperty("MusicPlayer", musicplayer__);
		media__.SetProperty("Sound", sound__);
		media__.SetProperty("VideoPlayer", videoplayer__);

		JSObject titanium = ti__;
		global_object__.SetProperty("Titanium", titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		global_object__.SetProperty("Ti", titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});

		titanium.SetProperty("API", api__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("UI", ui__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		titanium.SetProperty("Platform", platform__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Accelerometer", accelerometer__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Gesture", gesture__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Blob", blob__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Buffer", buffer__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("BufferStream", bufferstream__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("BlobStream", blobstream__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Codec", codec__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("IOStream", iostream__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Stream", stream__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		titanium.SetProperty("Filesystem", filesystem__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		titanium.SetProperty("Database", database__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Utils", utils__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Geolocation", geolocation__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		// App
		titanium.SetProperty("App", app__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		app__.SetProperty("Properties", properties__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});

		titanium.SetProperty("Network", network__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Analytics", analytics__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});

		titanium.SetProperty("Media", media__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});

		// Map
		titanium.SetProperty("Map", map__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		map__.SetProperty("Annotation", mapAnnotation__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		map__.SetProperty("Camera", mapCamera__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		map__.SetProperty("Route", mapRoute__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });
		map__.SetProperty("View", mapView__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		// XML
		titanium.SetProperty("XML", xml__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });

		// Titanium.String keeps a reference to Global.String module
		titanium.SetProperty("String", global_string__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });

		// Attach all Ti.String properties onto global String
		auto stringObj = static_cast<JSObject>(global_object__.GetProperty("String"));
		for (const auto& property_name : static_cast<std::vector<JSString>>(global_string__.GetPropertyNames())) {
			stringObj.SetProperty(property_name, global_string__.GetProperty(property_name));
		}

		// Locale
		titanium.SetProperty("Locale", locale__, { JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete });

		titanium.SetProperty("Contacts", contacts__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		contacts__.SetProperty("Group", group__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		contacts__.SetProperty("Person", person__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
JSString builtin_functions_script = R"js(
			  console = {};
			  console.log   = Ti.API.info;
			  console.info  = Ti.API.info;
			  console.warn  = Ti.API.warn;
			  console.error = Ti.API.error;
			  console.debug = Ti.API.debug;

			  // Create the global alert function
			  alert = function (_msg) {
				  Ti.UI.createAlertDialog({
					  title: 'Alert',
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
			)js";

		js_context__.JSEvaluateScript(builtin_functions_script);

		return Application(*this);
	}

	JSObject ApplicationBuilder::TiObject() const TITANIUM_NOEXCEPT
	{
		return ti__;
	}

	ApplicationBuilder& ApplicationBuilder::TiObject(const JSObject& ti) TITANIUM_NOEXCEPT
	{
		ti__ = ti;
		return *this;
	}

	JSObject ApplicationBuilder::GlobalString() const TITANIUM_NOEXCEPT
	{
		return global_string__;
	}

	ApplicationBuilder& ApplicationBuilder::GlobalString(const JSObject& global_string) TITANIUM_NOEXCEPT
	{
		global_string__ = global_string;
		return *this;
	}

	JSObject ApplicationBuilder::UIObject() const TITANIUM_NOEXCEPT
	{
		return ui__;
	}

	ApplicationBuilder& ApplicationBuilder::UIObject(const JSObject& ui) TITANIUM_NOEXCEPT
	{
		ui__ = ui;
		return *this;
	}

	JSObject ApplicationBuilder::APIObject() const TITANIUM_NOEXCEPT
	{
		return api__;
	}

	ApplicationBuilder& ApplicationBuilder::APIObject(const JSObject& api) TITANIUM_NOEXCEPT
	{
		api__ = api;
		return *this;
	}

	JSObject ApplicationBuilder::BufferObject() const TITANIUM_NOEXCEPT
	{
		return buffer__;
	}

	ApplicationBuilder& ApplicationBuilder::BufferObject(const JSObject& buffer) TITANIUM_NOEXCEPT
	{
		buffer__ = buffer;
		return *this;
	}

	JSObject ApplicationBuilder::BufferStreamObject() const TITANIUM_NOEXCEPT
	{
		return bufferstream__;
	}

	ApplicationBuilder& ApplicationBuilder::BufferStreamObject(const JSObject& bufferstream) TITANIUM_NOEXCEPT
	{
		bufferstream__ = bufferstream;
		return *this;
	}

	JSObject ApplicationBuilder::BlobStreamObject() const TITANIUM_NOEXCEPT
	{
		return blobstream__;
	}

	ApplicationBuilder& ApplicationBuilder::BlobStreamObject(const JSObject& blobstream) TITANIUM_NOEXCEPT
	{
		blobstream__ = blobstream;
		return *this;
	}
	
	JSObject ApplicationBuilder::IOStreamObject() const TITANIUM_NOEXCEPT
	{
		return iostream__;
	}

	ApplicationBuilder& ApplicationBuilder::IOStreamObject(const JSObject& iostream) TITANIUM_NOEXCEPT
	{
		iostream__ = iostream;
		return *this;
	}

	JSObject ApplicationBuilder::LocaleObject() const TITANIUM_NOEXCEPT
	{
		return locale__;
	}

	ApplicationBuilder& ApplicationBuilder::LocaleObject(const JSObject& locale) TITANIUM_NOEXCEPT
	{
		locale__ = locale;
		return *this;
	}

	JSObject ApplicationBuilder::ListViewObject() const TITANIUM_NOEXCEPT
	{
		return listview__;
	}

	ApplicationBuilder& ApplicationBuilder::ListViewObject(const JSObject& ListView) TITANIUM_NOEXCEPT
	{
		listview__ = ListView;
		return *this;
	}

	JSObject ApplicationBuilder::ListSectionObject() const TITANIUM_NOEXCEPT
	{
		return listsection__;
	}

	ApplicationBuilder& ApplicationBuilder::ListSectionObject(const JSObject& ListSection) TITANIUM_NOEXCEPT
	{
		listsection__ = ListSection;
		return *this;
	}

	JSObject ApplicationBuilder::AppObject() const TITANIUM_NOEXCEPT
	{
		return app__;
	}

	ApplicationBuilder& ApplicationBuilder::AppObject(const JSObject& App) TITANIUM_NOEXCEPT
	{
		app__ = App;
		return *this;
	}

	JSObject ApplicationBuilder::PropertiesObject() const TITANIUM_NOEXCEPT
	{
		return properties__;
	}

	ApplicationBuilder& ApplicationBuilder::PropertiesObject(const JSObject& Properties) TITANIUM_NOEXCEPT
	{
		properties__ = Properties;
		return *this;
	}

	JSObject ApplicationBuilder::AnalyticsObject() const TITANIUM_NOEXCEPT
	{
		return analytics__;
	}

	ApplicationBuilder& ApplicationBuilder::AnalyticsObject(const JSObject& analytics) TITANIUM_NOEXCEPT
	{
		analytics__ = analytics;
		return *this;
	}

	JSObject ApplicationBuilder::EmailDialogObject() const TITANIUM_NOEXCEPT
	{
		return emaildialog__;
	}

	ApplicationBuilder& ApplicationBuilder::EmailDialogObject(const JSObject& EmailDialog) TITANIUM_NOEXCEPT
	{
		emaildialog__ = EmailDialog;
		return *this;
	}

	JSObject ApplicationBuilder::AnimationObject() const TITANIUM_NOEXCEPT
	{
		return animation__;
	}

	ApplicationBuilder& ApplicationBuilder::AnimationObject(const JSObject& Animation) TITANIUM_NOEXCEPT
	{
		animation__ = Animation;
		return *this;
	}

	JSObject ApplicationBuilder::UtilsObject() const TITANIUM_NOEXCEPT
	{
		return utils__;
	}

	ApplicationBuilder& ApplicationBuilder::UtilsObject(const JSObject& Utils) TITANIUM_NOEXCEPT
	{
		utils__ = Utils;
		return *this;
	}

	JSObject ApplicationBuilder::SwitchObject() const TITANIUM_NOEXCEPT
	{
		return switch__;
	}

	ApplicationBuilder& ApplicationBuilder::SwitchObject(const JSObject& Switch) TITANIUM_NOEXCEPT
	{
		switch__ = Switch;
		return *this;
	}

	JSObject ApplicationBuilder::GeolocationObject() const TITANIUM_NOEXCEPT
	{
		return geolocation__;
	}

	ApplicationBuilder& ApplicationBuilder::GeolocationObject(const JSObject& Geolocation) TITANIUM_NOEXCEPT
	{
		geolocation__ = Geolocation;
		return *this;
	}

	JSObject ApplicationBuilder::TwoDMatrixObject() const TITANIUM_NOEXCEPT
	{
		return twodmatrix__;
	}

	ApplicationBuilder& ApplicationBuilder::TwoDMatrixObject(const JSObject& TwoDMatrix) TITANIUM_NOEXCEPT
	{
		twodmatrix__ = TwoDMatrix;
		return *this;
	}

	JSObject ApplicationBuilder::NotificationObject() const TITANIUM_NOEXCEPT
	{
		return notification__;
	}

	ApplicationBuilder& ApplicationBuilder::NotificationObject(const JSObject& Notification) TITANIUM_NOEXCEPT
	{
		notification__ = Notification;
		return *this;
	}

	JSObject ApplicationBuilder::TextAreaObject() const TITANIUM_NOEXCEPT
	{
		return textarea__;
	}

	ApplicationBuilder& ApplicationBuilder::TextAreaObject(const JSObject& TextArea) TITANIUM_NOEXCEPT
	{
		textarea__ = TextArea;
		return *this;
	}

	JSObject ApplicationBuilder::ClipboardObject() const TITANIUM_NOEXCEPT
	{
		return clipboard__;
	}

	ApplicationBuilder& ApplicationBuilder::ClipboardObject(const JSObject& Clipboard) TITANIUM_NOEXCEPT
	{
		clipboard__ = Clipboard;
		return *this;
	}

	JSObject ApplicationBuilder::CodecObject() const TITANIUM_NOEXCEPT
	{
		return codec__;
	}

	ApplicationBuilder& ApplicationBuilder::CodecObject(const JSObject& codec) TITANIUM_NOEXCEPT
	{
		codec__ = codec;
		return *this;
	}

	JSObject ApplicationBuilder::ContactsObject() const TITANIUM_NOEXCEPT
	{
		return contacts__;
	}

	ApplicationBuilder& ApplicationBuilder::ContactsObject(const JSObject& Contacts) TITANIUM_NOEXCEPT
	{
		contacts__ = Contacts;
		return *this;
	}

	JSObject ApplicationBuilder::GroupObject() const TITANIUM_NOEXCEPT
	{
		return group__;
	}

	ApplicationBuilder& ApplicationBuilder::GroupObject(const JSObject& Group) TITANIUM_NOEXCEPT
	{
		group__ = Group;
		return *this;
	}

	JSObject ApplicationBuilder::PersonObject() const TITANIUM_NOEXCEPT
	{
		return person__;
	}

	ApplicationBuilder& ApplicationBuilder::PersonObject(const JSObject& Person) TITANIUM_NOEXCEPT
	{
		person__ = Person;
		return *this;
	}

	JSObject ApplicationBuilder::ViewObject() const TITANIUM_NOEXCEPT
	{
		return view__;
	}

	ApplicationBuilder& ApplicationBuilder::ViewObject(const JSObject& View) TITANIUM_NOEXCEPT
	{
		view__ = View;
		return *this;
	}

	JSObject ApplicationBuilder::WindowObject() const TITANIUM_NOEXCEPT
	{
		return window__;
	}

	ApplicationBuilder& ApplicationBuilder::WindowObject(const JSObject& window) TITANIUM_NOEXCEPT
	{
		window__ = window;
		return *this;
	}

	JSObject ApplicationBuilder::ButtonObject() const TITANIUM_NOEXCEPT
	{
		return button__;
	}

	ApplicationBuilder& ApplicationBuilder::ButtonObject(const JSObject& button) TITANIUM_NOEXCEPT
	{
		button__ = button;
		return *this;
	}

	JSObject ApplicationBuilder::SliderObject() const TITANIUM_NOEXCEPT
	{
		return slider__;
	}

	ApplicationBuilder& ApplicationBuilder::SliderObject(const JSObject& slider) TITANIUM_NOEXCEPT
	{
		slider__ = slider;
		return *this;
	}

	JSObject ApplicationBuilder::AlertDialogObject() const TITANIUM_NOEXCEPT
	{
		return alertDialog__;
	}

	ApplicationBuilder& ApplicationBuilder::AlertDialogObject(const JSObject& alertDialog) TITANIUM_NOEXCEPT
	{
		alertDialog__ = alertDialog;
		return *this;
	}

	JSObject ApplicationBuilder::ImageViewObject() const TITANIUM_NOEXCEPT
	{
		return imageview__;
	}

	ApplicationBuilder& ApplicationBuilder::ImageViewObject(const JSObject& imageview) TITANIUM_NOEXCEPT
	{
		imageview__ = imageview;
		return *this;
	}

	JSObject ApplicationBuilder::LabelObject() const TITANIUM_NOEXCEPT
	{
		return label__;
	}

	ApplicationBuilder& ApplicationBuilder::LabelObject(const JSObject& label) TITANIUM_NOEXCEPT
	{
		label__ = label;
		return *this;
	}

	JSObject ApplicationBuilder::ScrollViewObject() const TITANIUM_NOEXCEPT
	{
		return scrollview__;
	}

	ApplicationBuilder& ApplicationBuilder::ScrollViewObject(const JSObject& view) TITANIUM_NOEXCEPT
	{
		scrollview__ = view;
		return *this;
	}

	JSObject ApplicationBuilder::TextFieldObject() const TITANIUM_NOEXCEPT
	{
		return textField__;
	}

	ApplicationBuilder& ApplicationBuilder::TextFieldObject(const JSObject& view) TITANIUM_NOEXCEPT
	{
		textField__ = view;
		return *this;
	}

	JSObject ApplicationBuilder::PlatformObject() const TITANIUM_NOEXCEPT
	{
		return platform__;
	}

	ApplicationBuilder& ApplicationBuilder::PlatformObject(const JSObject& platform) TITANIUM_NOEXCEPT
	{
		platform__ = platform;
		return *this;
	}

	JSObject ApplicationBuilder::AccelerometerObject() const TITANIUM_NOEXCEPT
	{
		return accelerometer__;
	}

	ApplicationBuilder& ApplicationBuilder::AccelerometerObject(const JSObject& accelerometer) TITANIUM_NOEXCEPT
	{
		accelerometer__ = accelerometer;
		return *this;
	}

	JSObject ApplicationBuilder::GestureObject() const TITANIUM_NOEXCEPT
	{
		return gesture__;
	}

	ApplicationBuilder& ApplicationBuilder::GestureObject(const JSObject& gesture) TITANIUM_NOEXCEPT
	{
		gesture__ = gesture;
		return *this;
	}

	JSObject ApplicationBuilder::BlobObject() const TITANIUM_NOEXCEPT
	{
		return blob__;
	}

	ApplicationBuilder& ApplicationBuilder::BlobObject(const JSObject& blob) TITANIUM_NOEXCEPT
	{
		blob__ = blob;
		return *this;
	}

	JSObject ApplicationBuilder::FileObject() const TITANIUM_NOEXCEPT
	{
		return file__;
	}

	ApplicationBuilder& ApplicationBuilder::FileObject(const JSObject& file) TITANIUM_NOEXCEPT
	{
		file__ = file;
		return *this;
	}

	JSObject ApplicationBuilder::FileStreamObject() const TITANIUM_NOEXCEPT
	{
		return filestream__;
	}

	ApplicationBuilder& ApplicationBuilder::FileStreamObject(const JSObject& filestream) TITANIUM_NOEXCEPT
	{
		filestream__ = filestream;
		return *this;
	}

	JSObject ApplicationBuilder::FilesystemObject() const TITANIUM_NOEXCEPT
	{
		return filesystem__;
	}
	
	ApplicationBuilder& ApplicationBuilder::FilesystemObject(const JSObject& filesystem) TITANIUM_NOEXCEPT
	{
		filesystem__ = filesystem;
		return *this;
	}

	JSObject ApplicationBuilder::DatabaseObject() const TITANIUM_NOEXCEPT
	{
		return database__;
	}

	ApplicationBuilder& ApplicationBuilder::DatabaseObject(const JSObject& database) TITANIUM_NOEXCEPT
	{
		database__ = database;
		return *this;
	}

	JSObject ApplicationBuilder::WebViewObject() const TITANIUM_NOEXCEPT
	{
		return webview__;
	}

	ApplicationBuilder& ApplicationBuilder::WebViewObject(const JSObject& webview) TITANIUM_NOEXCEPT
	{
		webview__ = webview;
		return *this;
	}

	JSObject ApplicationBuilder::HTTPClientObject() const TITANIUM_NOEXCEPT
	{
		return httpclient__;
	}

	ApplicationBuilder& ApplicationBuilder::HTTPClientObject(const JSObject& httpclient) TITANIUM_NOEXCEPT
	{
		httpclient__ = httpclient;
		return *this;
	}

	JSObject ApplicationBuilder::CookieObject() const TITANIUM_NOEXCEPT
	{
		return cookie__;
	}

	ApplicationBuilder& ApplicationBuilder::CookieObject(const JSObject& cookie) TITANIUM_NOEXCEPT
	{
		cookie__ = cookie;
		return *this;
	}

	JSObject ApplicationBuilder::NetworkObject() const TITANIUM_NOEXCEPT
	{
		return network__;
	}

	ApplicationBuilder& ApplicationBuilder::NetworkObject(const JSObject& network) TITANIUM_NOEXCEPT
	{
		network__ = network;
		return *this;
	}

	JSObject ApplicationBuilder::TCPObject() const TITANIUM_NOEXCEPT
	{
		return tcp__;
	}

	ApplicationBuilder& ApplicationBuilder::TCPObject(const JSObject& tcp) TITANIUM_NOEXCEPT
	{
		tcp__ = tcp;
		return *this;
	}

	JSObject ApplicationBuilder::UDPObject() const TITANIUM_NOEXCEPT
	{
		return udp__;
	}

	ApplicationBuilder& ApplicationBuilder::UDPObject(const JSObject& udp) TITANIUM_NOEXCEPT
	{
		udp__ = udp;
		return *this;
	}

	JSObject ApplicationBuilder::MediaObject() const TITANIUM_NOEXCEPT
	{
		return media__;
	}

	ApplicationBuilder& ApplicationBuilder::MediaObject(const JSObject& media) TITANIUM_NOEXCEPT
	{
		media__ = media;
		return *this;
	}

	JSObject ApplicationBuilder::AudioPlayerObject() const TITANIUM_NOEXCEPT
	{
		return audioplayer__;
	}

	ApplicationBuilder& ApplicationBuilder::AudioPlayerObject(const JSObject& player) TITANIUM_NOEXCEPT
	{
		audioplayer__ = player;
		return *this;
	}

	JSObject ApplicationBuilder::AudioRecorderObject() const TITANIUM_NOEXCEPT
	{
		return audiorecorder__;
	}

	ApplicationBuilder& ApplicationBuilder::AudioRecorderObject(const JSObject& recorder) TITANIUM_NOEXCEPT
	{
		audiorecorder__ = recorder;
		return *this;
	}

	JSObject ApplicationBuilder::AudioItemObject() const TITANIUM_NOEXCEPT
	{
		return audioitem__;
	}

	ApplicationBuilder& ApplicationBuilder::AudioItemObject(const JSObject& item) TITANIUM_NOEXCEPT
	{
		audioitem__ = item;
		return *this;
	}

	JSObject ApplicationBuilder::MusicPlayerObject() const TITANIUM_NOEXCEPT
	{
		return musicplayer__;
	}

	ApplicationBuilder& ApplicationBuilder::MusicPlayerObject(const JSObject& player) TITANIUM_NOEXCEPT
	{
		musicplayer__ = player;
		return *this;
	}

	JSObject ApplicationBuilder::SoundObject() const TITANIUM_NOEXCEPT
	{
		return sound__;
	}

	ApplicationBuilder& ApplicationBuilder::SoundObject(const JSObject& sound) TITANIUM_NOEXCEPT
	{
		sound__ = sound;
		return *this;
	}

	JSObject ApplicationBuilder::VideoPlayerObject() const TITANIUM_NOEXCEPT
	{
		return videoplayer__;
	}
	
	ApplicationBuilder& ApplicationBuilder::VideoPlayerObject(const JSObject& player) TITANIUM_NOEXCEPT
	{
		videoplayer__ = player;
		return *this;
	}

	JSObject ApplicationBuilder::XMLObject() const TITANIUM_NOEXCEPT
	{
		return xml__;
	}

	ApplicationBuilder& ApplicationBuilder::XMLObject(const JSObject& XML) TITANIUM_NOEXCEPT
	{
		xml__ = XML;
		return *this;
	}

	JSObject ApplicationBuilder::Tab() const TITANIUM_NOEXCEPT
	{
		return tab__;
	}

	ApplicationBuilder& ApplicationBuilder::Tab(const JSObject& view) TITANIUM_NOEXCEPT
	{
		tab__ = view;
		return *this;
	}

	JSObject ApplicationBuilder::TabGroup() const TITANIUM_NOEXCEPT
	{
		return tabgroup__;
	}

	ApplicationBuilder& ApplicationBuilder::TabGroup(const JSObject& view) TITANIUM_NOEXCEPT
	{
		tabgroup__ = view;
		return *this;
	}

	JSObject ApplicationBuilder::TableViewObject() const TITANIUM_NOEXCEPT
	{
		return tableview__;
	}

	ApplicationBuilder& ApplicationBuilder::TableViewObject(const JSObject& TableView) TITANIUM_NOEXCEPT
	{
		tableview__ = TableView;
		return *this;
	}

	JSObject ApplicationBuilder::TableViewSectionObject() const TITANIUM_NOEXCEPT
	{
		return tableviewsection__;
	}

	ApplicationBuilder& ApplicationBuilder::TableViewSectionObject(const JSObject& TableViewSection) TITANIUM_NOEXCEPT
	{
		tableviewsection__ = TableViewSection;
		return *this;
	}

	JSObject ApplicationBuilder::TableViewRowObject() const TITANIUM_NOEXCEPT
	{
		return tableviewrow__;
	}

	ApplicationBuilder& ApplicationBuilder::TableViewRowObject(const JSObject& TableViewRow) TITANIUM_NOEXCEPT
	{
		tableviewrow__ = TableViewRow;
		return *this;
	}

	JSObject ApplicationBuilder::MapObject() const TITANIUM_NOEXCEPT
	{
		return map__;
	}

	ApplicationBuilder& ApplicationBuilder::MapObject(const JSObject& Map) TITANIUM_NOEXCEPT
	{
		map__ = Map;
		return *this;
	}

	JSObject ApplicationBuilder::MapAnnotationObject() const TITANIUM_NOEXCEPT
	{
		return mapAnnotation__;
	}

	ApplicationBuilder& ApplicationBuilder::MapAnnotationObject(const JSObject& mapAnnotation) TITANIUM_NOEXCEPT
	{
		mapAnnotation__ = mapAnnotation;
		return *this;
	}

	JSObject ApplicationBuilder::MapCameraObject() const TITANIUM_NOEXCEPT
	{
		return mapCamera__;
	}

	ApplicationBuilder& ApplicationBuilder::MapCameraObject(const JSObject& mapCamera) TITANIUM_NOEXCEPT
	{
		mapCamera__ = mapCamera;
		return *this;
	}

	JSObject ApplicationBuilder::MapRouteObject() const TITANIUM_NOEXCEPT
	{
		return mapRoute__;
	}

	ApplicationBuilder& ApplicationBuilder::MapRouteObject(const JSObject& mapRoute) TITANIUM_NOEXCEPT
	{
		mapRoute__ = mapRoute;
		return *this;
	}

	JSObject ApplicationBuilder::MapViewObject() const TITANIUM_NOEXCEPT
	{
		return mapView__;
	}

	ApplicationBuilder& ApplicationBuilder::MapViewObject(const JSObject& mapView) TITANIUM_NOEXCEPT
	{
		mapView__ = mapView;
		return *this;
	}

	JSObject ApplicationBuilder::ActivityIndicatorObject() const TITANIUM_NOEXCEPT
	{
		return activityIndicator__;
	}

	ApplicationBuilder& ApplicationBuilder::ActivityIndicatorObject(const JSObject& value) TITANIUM_NOEXCEPT
	{
		activityIndicator__ = value;
		return *this;
	}

	JSObject ApplicationBuilder::ActivityIndicatorStyleObject() const TITANIUM_NOEXCEPT
	{
		return activityIndicatorStyle__;
	}

	ApplicationBuilder& ApplicationBuilder::ActivityIndicatorStyleObject(const JSObject& value) TITANIUM_NOEXCEPT
	{
		activityIndicatorStyle__ = value;
		return *this;
	}

	JSObject ApplicationBuilder::OptionDialogObject() const TITANIUM_NOEXCEPT
	{
		return optionDialog__;
	}

	ApplicationBuilder& ApplicationBuilder::OptionDialogObject(const JSObject& value) TITANIUM_NOEXCEPT
	{
		optionDialog__ = value;
		return *this;
	}

	JSObject ApplicationBuilder::ProgressBarObject() const TITANIUM_NOEXCEPT
	{
		return progressBar__;
	}

	ApplicationBuilder& ApplicationBuilder::ProgressBarObject(const JSObject& value) TITANIUM_NOEXCEPT
	{
		progressBar__ = value;
		return *this;
	}

	JSObject ApplicationBuilder::ScrollableViewObject() const TITANIUM_NOEXCEPT
	{
		return scrollableView__;
	}

	ApplicationBuilder& ApplicationBuilder::ScrollableViewObject(const JSObject& value) TITANIUM_NOEXCEPT
	{
		scrollableView__ = value;
		return *this;
	}

}  // namespace Titanium
