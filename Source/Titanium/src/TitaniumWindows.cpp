/**
 * Titanium for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/TitaniumWindows.hpp"
#include "Titanium/Application.hpp"
#include "TitaniumWindows/TiModule.hpp"
#include "TitaniumWindows/UIModule.hpp"
#include "TitaniumWindows/Contacts/Person.hpp"
#include "TitaniumWindows/Contacts/Group.hpp"
#include "TitaniumWindows/Contacts.hpp"
#include "TitaniumWindows/UI/Clipboard.hpp"
#include "TitaniumWindows/API.hpp"
#include "TitaniumWindows/AppModule.hpp"
#include "TitaniumWindows/Codec.hpp"
#include "TitaniumWindows/Locale.hpp"
#include "TitaniumWindows/Platform.hpp"
#include "TitaniumWindows/Gesture.hpp"
#include "TitaniumWindows/Geolocation.hpp"
#include "TitaniumWindows/Accelerometer.hpp"
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/TextArea.hpp"
#include "TitaniumWindows/UI/Notification.hpp"
#include "TitaniumWindows/UI/Switch.hpp"
#include "TitaniumWindows/Utils.hpp"
#include "TitaniumWindows/App/Properties.hpp"
#include "TitaniumWindows/UI/EmailDialog.hpp"
#include "TitaniumWindows/UI/Window.hpp"
#include "TitaniumWindows/UI/Button.hpp"
#include "TitaniumWindows/UI/AlertDialog.hpp"
#include "TitaniumWindows/UI/ImageView.hpp"
#include "TitaniumWindows/UI/Label.hpp"
#include "TitaniumWindows/UI/ScrollView.hpp"
#include "TitaniumWindows/UI/SearchBar.hpp"
#include "TitaniumWindows/UI/Slider.hpp"
#include "TitaniumWindows/UI/TextField.hpp"
#include "TitaniumWindows/UI/ListView.hpp"
#include "TitaniumWindows/Blob.hpp"
#include "TitaniumWindows/Filesystem.hpp"
#include "TitaniumWindows/File.hpp"
#include "TitaniumWindows/Network.hpp"
#include "TitaniumWindows/Network/HTTPClient.hpp"
#include "TitaniumWindows/UI/WebView.hpp"
#include "TitaniumWindows/Map/View.hpp"
#include "TitaniumWindows/Map/Annotation.hpp"
#include "TitaniumWindows/UI/Tab.hpp"
#include "TitaniumWindows/UI/TabGroup.hpp"
#include "TitaniumWindows/UI/TableView.hpp"
#include "TitaniumWindows/UI/TableViewRow.hpp"
#include "TitaniumWindows/UI/ActivityIndicator.hpp"
#include "TitaniumWindows/UI/OptionDialog.hpp"
#include "TitaniumWindows/UI/Picker.hpp"
#include "TitaniumWindows/UI/PickerRow.hpp"
#include "TitaniumWindows/UI/PickerColumn.hpp"
#include "TitaniumWindows/UI/ProgressBar.hpp"
#include "TitaniumWindows/UI/ScrollableView.hpp"
#include "TitaniumWindows/Media.hpp"
#include "TitaniumWindows/Media/AudioPlayer.hpp"
#include "TitaniumWindows/Media/AudioRecorder.hpp"
#include "TitaniumWindows/Media/MusicPlayer.hpp"
#include "TitaniumWindows/Media/VideoPlayer.hpp"
#include "TitaniumWindows/Media/Sound.hpp"
#include "TitaniumWindows/Media/Item.hpp"
#include "TitaniumWindows/GlobalObject.hpp"
#include "TitaniumWindows/GlobalString.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiImpl.hpp"

#include <Windows.h>
#include <collection.h>
#include <vector>

#define GET_TITANIUM_APP(VARNAME) \
  JSValue Titanium_property = js_context__.get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue App_property = Titanium.GetProperty("App"); \
  TITANIUM_ASSERT(App_property.IsObject()); \
  std::shared_ptr<Titanium::AppModule> VARNAME = static_cast<JSObject>(App_property).GetPrivate<Titanium::AppModule>();

namespace TitaniumWindows
{
	using namespace HAL;
	using namespace Windows::ApplicationModel::Activation;

	Application::Application() : js_context__(js_context_group__.CreateContext(JSExport<TitaniumWindows::GlobalObject>::Class()))
	{
	}

	Application::Application(::Platform::String^ seed) : Application::Application()
	{
		auto js_global = js_context__.get_global_object();
		auto global = js_global.GetPrivate<TitaniumWindows::GlobalObject>();
		TITANIUM_ASSERT(global != nullptr);
		global->setSeed(seed);
	}

	Application::~Application()
	{
	}

	void Application::OnLaunched(LaunchActivatedEventArgs ^ args)
	{
		UnhandledException += ref new Windows::UI::Xaml::UnhandledExceptionEventHandler(this, &Application::OnUnhandledException);

		auto titanium = js_context__.CreateObject(JSExport<TitaniumWindows::TiModule>::Class());
		auto titanium_ptr = titanium.GetPrivate<TitaniumWindows::TiModule>();

		titanium_ptr->GlobalString(JSExport<TitaniumWindows::GlobalString>::Class())
			.UIClass(JSExport<TitaniumWindows::UIModule>::Class())
			.APIClass(JSExport<TitaniumWindows::API>::Class())
			.AppClass(JSExport<TitaniumWindows::AppModule>::Class())
			.CodecClass(JSExport<TitaniumWindows::Codec>::Class())
			.LocaleClass(JSExport<TitaniumWindows::Locale>::Class())
			.PlatformClass(JSExport<TitaniumWindows::Platform>::Class())
			.GestureClass(JSExport<TitaniumWindows::Gesture>::Class())
			.GeolocationClass(JSExport<TitaniumWindows::Geolocation>::Class())
			.AccelerometerClass(JSExport<TitaniumWindows::Accelerometer>::Class())
			.ViewClass(JSExport<TitaniumWindows::UI::View>::Class())
			.PersonClass(JSExport<TitaniumWindows::Contacts::Person>::Class())
			.GroupClass(JSExport<TitaniumWindows::Contacts::Group>::Class())
			.ContactsClass(JSExport<TitaniumWindows::ContactsModule>::Class())
			.ClipboardClass(JSExport<TitaniumWindows::UI::Clipboard>::Class())
			.TextAreaClass(JSExport<TitaniumWindows::UI::TextArea>::Class())
			.NotificationClass(JSExport<TitaniumWindows::UI::Notification>::Class())
			.SwitchClass(JSExport<TitaniumWindows::UI::Switch>::Class())
			.UtilsClass(JSExport<TitaniumWindows::Utils>::Class())
			.PropertiesClass(JSExport<TitaniumWindows::App::Properties>::Class())
			.EmailDialogClass(JSExport<TitaniumWindows::UI::EmailDialog>::Class())
			.WindowClass(JSExport<TitaniumWindows::UI::Window>::Class())
			.ButtonClass(JSExport<TitaniumWindows::UI::Button>::Class())
			.AlertDialogClass(JSExport<TitaniumWindows::UI::AlertDialog>::Class())
			.ImageViewClass(JSExport<TitaniumWindows::UI::ImageView>::Class())
			.LabelClass(JSExport<TitaniumWindows::UI::Label>::Class())
			.ScrollViewClass(JSExport<TitaniumWindows::UI::ScrollView>::Class())
			.SearchBarClass(JSExport<TitaniumWindows::UI::SearchBar>::Class())
			.SliderClass(JSExport<TitaniumWindows::UI::Slider>::Class())
			.TextFieldClass(JSExport<TitaniumWindows::UI::TextField>::Class())
			.ListViewClass(JSExport<TitaniumWindows::UI::ListView>::Class())
			.BlobClass(JSExport<TitaniumWindows::Blob>::Class())
			.FilesystemClass(JSExport<TitaniumWindows::FilesystemModule>::Class())
			.FileClass(JSExport<TitaniumWindows::Filesystem::File>::Class())
			.NetworkClass(JSExport<TitaniumWindows::NetworkModule>::Class())
			.HTTPClientClass(JSExport<TitaniumWindows::Network::HTTPClient>::Class())
			.WebViewClass(JSExport<TitaniumWindows::UI::WebView>::Class())
			.MapViewClass(JSExport<TitaniumWindows::Map::View>::Class())
			.MapAnnotationClass(JSExport<TitaniumWindows::Map::Annotation>::Class())
			.Tab(JSExport<TitaniumWindows::UI::Tab>::Class())
			.TabGroup(JSExport<TitaniumWindows::UI::TabGroup>::Class())
			.TableViewClass(JSExport<TitaniumWindows::UI::TableView>::Class())
			.TableViewRowClass(JSExport<TitaniumWindows::UI::TableViewRow>::Class())
			.ActivityIndicatorClass(JSExport<TitaniumWindows::UI::ActivityIndicator>::Class())
			.OptionDialogClass(JSExport<TitaniumWindows::UI::OptionDialog>::Class())
			.PickerClass(JSExport<TitaniumWindows::UI::Picker>::Class())
			.PickerRowClass(JSExport<TitaniumWindows::UI::PickerRow>::Class())
			.PickerColumnClass(JSExport<TitaniumWindows::UI::PickerColumn>::Class())
			.ProgressBarClass(JSExport<TitaniumWindows::UI::ProgressBar>::Class())
			.ScrollableViewClass(JSExport<TitaniumWindows::UI::ScrollableView>::Class())
			.MediaClass(JSExport<TitaniumWindows::MediaModule>::Class())
			.AudioItemClass(JSExport<TitaniumWindows::Media::Item>::Class())
			.AudioPlayerClass(JSExport<TitaniumWindows::Media::AudioPlayer>::Class())
			.AudioRecorderClass(JSExport<TitaniumWindows::Media::AudioRecorder>::Class())
			.SoundClass(JSExport<TitaniumWindows::Media::Sound>::Class())
			.MusicPlayerClass(JSExport<TitaniumWindows::Media::MusicPlayer>::Class())
			.VideoPlayerClass(JSExport<TitaniumWindows::Media::VideoPlayer>::Class()).build();

		application__ = std::make_shared<Titanium::Application>(js_context__);

		const auto js_context_ref = reinterpret_cast<std::intptr_t>(static_cast<JSContextRef>(js_context__));
		auto preloaded = TitaniumModulePreload(js_context_ref);
		auto js_preloaded_modules = js_context__.CreateObject();
		if (preloaded) {
			js_preloaded_modules = JSObject(js_context__, reinterpret_cast<JSObjectRef>(TitaniumModulePreload(js_context_ref)));
		}

		// store all preloaded native modules
		std::unordered_map<std::string, JSValue> preloaded_modules;
		for (const auto& property_name : static_cast<std::vector<JSString>>(js_preloaded_modules.GetPropertyNames())) {
			preloaded_modules.emplace(property_name, js_preloaded_modules.GetProperty(property_name));
		}

		// store all supported native module names
		std::vector<std::string> native_module_names;
		const auto rt_native_module_names = TitaniumModuleNames(js_context_ref);
		if (rt_native_module_names) {
			for (auto v : rt_native_module_names) {
				native_module_names.push_back(TitaniumWindows::Utility::ConvertString(v));
			}
		}

		// registerNativeModuleRequireHook will be called for "non-preloaded" modules
		auto global = js_context__.get_global_object().GetPrivate<TitaniumWindows::GlobalObject>();
		global->registerNativeModuleRequireHook(native_module_names, preloaded_modules, [js_context_ref, this](const std::string& moduleId) {
			const auto js_value_ptr = TitaniumModuleRequire(js_context_ref, TitaniumWindows::Utility::ConvertString(moduleId));
			auto result = JSValue(js_context__, reinterpret_cast<JSValueRef>(js_value_ptr));
			return result;
		});

		Suspending += ref new Windows::UI::Xaml::SuspendingEventHandler(this, &Application::OnSuspending);
		Resuming += ref new Windows::Foundation::EventHandler<::Platform::Object^>(this, &Application::OnResuming);

		// TODO Hook the native ui unwrap stuff on the instance of Titanium::UI::View?
		JSValue Titanium_property = js_context__.get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue UI_property = Titanium.GetProperty("UI");
		TITANIUM_ASSERT(UI_property.IsObject());  // precondition
		JSObject UI = static_cast<JSObject>(UI_property);

		JSValue View_property = UI.GetProperty("View");
		TITANIUM_ASSERT(View_property.IsObject());  // precondition
		JSObject View = static_cast<JSObject>(View_property);

		auto win_view_static = View.GetPrivate<TitaniumWindows::UI::View>();
		win_view_static->registerNativeUIWrapHook([js_context_ref, this](const JSContext& context, const JSObject& object) {
			const auto js_object_ref = reinterpret_cast<std::intptr_t>(static_cast<JSObjectRef>(object));
			const auto js_context_ref = reinterpret_cast<std::intptr_t>(static_cast<JSContextRef>(context));
			const auto js_object_ptr = UnwrapNativeUIElement(js_context_ref, js_object_ref);
			auto result = JSObject(context, reinterpret_cast<JSObjectRef>(js_object_ptr));
			return result;
		});

		// #if _DEBUG
		//  if (IsDebuggerPresent()) {
		//    DebugSettings -> EnableFrameRateCounter = true;
		//  }
		// #endif

		auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame ^>(Windows::UI::Xaml::Window::Current->Content);
		// Do not repeat initialization when the Window already has content,
		// just ensure that the window is active.
		if (rootFrame == nullptr) {
			rootFrame = ref new Windows::UI::Xaml::Controls::Frame();

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
			// This code is for Windows phone apps only. Remove the turnstile
			// navigation for startup.
			if (rootFrame->ContentTransitions != nullptr) {
				transitions__ = ref new Windows::UI::Xaml::Media::Animation::TransitionCollection();
				for (auto transition : rootFrame->ContentTransitions) {
					transitions__->Append(transition);
				}
			}

			rootFrame->ContentTransitions = nullptr;
			first_navigated_token__ = rootFrame->Navigated += ref new Windows::UI::Xaml::Navigation::NavigatedEventHandler(this, &Application::RootFrame_FirstNavigated);
#endif

			if (rootFrame->Content == nullptr) {
				TITANIUM_LOG_DEBUG("MDL: rootFrame -> Content == nullptr");
			}

			// Create a Frame to act as the navigation context and associate
			// it with a SuspensionManager key.

			// TODO: Change this value to a cache size that is appropriate for
			// your application.
			rootFrame->CacheSize = 1;

			if (args->PreviousExecutionState ==ApplicationExecutionState::Terminated) {
				// TODO: Restore the saved session state only when appropriate,
				// scheduling the final launch steps after the restore is
				// complete.
			}

			// Place the frame in the current Window.
			Windows::UI::Xaml::Window::Current->Content = rootFrame;
			application__->Run("/app");
		}

		// Ensure the current Window is active.
		Windows::UI::Xaml::Window::Current->Activate();
	}

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
	// This code is for Windows phone apps only. Restore the content
	// transitions after the application has launched.
	void Application::RootFrame_FirstNavigated(::Platform::Object ^ sender, Windows::UI::Xaml::Navigation::NavigationEventArgs ^ e)
	{
		auto rootFrame = safe_cast<Windows::UI::Xaml::Controls::Frame ^>(sender);

		Windows::UI::Xaml::Media::Animation::TransitionCollection ^ newTransitions;
		if (transitions__ == nullptr) {
			newTransitions = ref new Windows::UI::Xaml::Media::Animation::TransitionCollection();
			newTransitions->Append(ref new Windows::UI::Xaml::Media::Animation::NavigationThemeTransition());
		} else {
			newTransitions = transitions__;
		}

		rootFrame->ContentTransitions = newTransitions;
		rootFrame->Navigated -= first_navigated_token__;
	}
#endif

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
	void Application::OnActivated(IActivatedEventArgs^ args) 
	{
		Windows::UI::Xaml::Application::OnActivated(args);

		//
		// Check if app is re-activated from *AndContinue task.
		// https://msdn.microsoft.com/en-us/library/windows/apps/xaml/dn614994.aspx
		//
		const auto continuationEventArgs = dynamic_cast<IContinuationActivatedEventArgs^>(args);
		if (continuationEventArgs != nullptr) {
			GET_TITANIUM_APP(App);

			// Restored from file picker and fire "windows.fileOpenFromPicker" event
			const auto fileOpenPickerEventArgs = dynamic_cast<FileOpenPickerContinuationEventArgs^>(continuationEventArgs);
			if (fileOpenPickerEventArgs != nullptr) {
				auto event_object = js_context__.CreateObject();
				const auto files = fileOpenPickerEventArgs->Files;
				std::vector<JSValue> js_files;
				for (auto file : fileOpenPickerEventArgs->Files) {
					js_files.push_back(js_context__.CreateString(TitaniumWindows::Utility::ConvertString(file->Path)));
				}
				event_object.SetProperty("files", js_context__.CreateArray(js_files));
				App->fireEvent("windows.fileOpenFromPicker", event_object);
			}
		}
	}
#endif

	void Application::OnUnhandledException(Object^ sender, Windows::UI::Xaml::UnhandledExceptionEventArgs^ arg)
	{
#if defined _DEBUG
		if (IsDebuggerPresent()) {
			__debugbreak();
		}
#endif
		// say we've handled this one. this allows our FATAL write to complete.
		arg->Handled = true;

		const auto store = ApplicationData::Current->LocalFolder;
		concurrency::create_task(store->CreateFileAsync("crash.log", CreationCollisionOption::GenerateUniqueName)).then([arg](concurrency::task<StorageFile^> task) {
			try {
				const auto file = task.get();
				HResult exc = arg->Exception;
				FileIO::WriteTextAsync(file, "Message: " + arg->Message + "\nHRESULT: " + exc.Value + "\nToString(): " + arg->ToString() + "\ntype: " + arg->GetType()->FullName);
			} catch (...) {
				// Just to make sure we don't throw another exception
			}
		});

		Titanium::Module::ShowRedScreenOfDeath(js_context__, TitaniumWindows::Utility::ConvertString(arg->Message));
	}

	void Application::OnResuming(Object ^sender, Object ^args) 
	{
		// shorthand to indicate we're in background
		js_context__.JSEvaluateScript("Ti.App.Windows.BackgroundService.suspended = false;");

		// Since we only have "resuming" event, we fires both resume and resumed event.
		GET_TITANIUM_APP(App);
		App->fireEvent("resume");
		App->fireEvent("resumed");
	}

	void Application::OnSuspending(Object ^ sender, Windows::ApplicationModel::SuspendingEventArgs ^ e)
	{
		auto deferral = e->SuspendingOperation->GetDeferral();

		// shorthand to indicate we're in background
		js_context__.JSEvaluateScript("Ti.App.Windows.BackgroundService.suspended = true;");
		js_context__.JSEvaluateScript("Ti.Analytics._receivedResponse = false");

		// Since we only have "suspending" event, we fires both pause and paused event.
		GET_TITANIUM_APP(App);
		App->fireEvent("pause");
		App->fireEvent("paused");

		// wait for Ti.Analytics to receive a response
		auto retry_count = 0;
		while (static_cast<bool>(js_context__.JSEvaluateScript("!Ti.Analytics._receivedResponse"))) {
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			retry_count++;

			// wait for a maximum of 3000ms
			if (retry_count > 15) {
				break;
			}
		}

		deferral->Complete();
	}

}  // namespace TitaniumWindows
