/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Media/Sound.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include "TitaniumWindows/Utility.hpp"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using TitaniumWindows::Utility::RunOnUIThread;

namespace TitaniumWindows
{
	namespace Media {
		Sound::Sound(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Media::Sound(js_context) {
			TITANIUM_LOG_DEBUG("TitaniumWindows::Media::Sound::ctor Initialize");
		}

		Sound::~Sound()
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Media::Sound::dtor");
		}

		void Sound::JSExportInitialize()
		{
			JSExport<Sound>::SetClassVersion(1);
			JSExport<Sound>::SetParent(JSExport<Titanium::Media::Sound>::Class());
		}

		void Sound::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) 
		{
			Titanium::Media::Sound::postCallAsConstructor(js_context, arguments);
			player__ = ref new Windows::UI::Xaml::Controls::MediaElement();
			player__->AudioCategory = AudioCategory::SoundEffects;
			player__->AreTransportControlsEnabled = true;
			player__->Visibility = Windows::UI::Xaml::Visibility::Collapsed; // Hide UI
			player__->AutoPlay = false;
			player__->IsLooping = false;
			player__->CurrentStateChanged += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				looping__ = isLooping();
				playing__ = isPlaying();
				paused__ = isPaused();
				volume__ = player__->Volume;
				duration__ = static_cast<double>(TitaniumWindows::Utility::GetMSec(player__->NaturalDuration.TimeSpan).count());

				const auto ctx = get_context();
				auto event_arg = ctx.CreateObject();

				switch (player__->CurrentState) {
				case MediaElementState::Buffering:
					event_arg.SetProperty("state", state_buffering__);
					break;
				case MediaElementState::Paused:
					event_arg.SetProperty("state", state_paused__);
					break;
				case MediaElementState::Playing:
					event_arg.SetProperty("state", state_playing__);
					break;
				case MediaElementState::Stopped:
					event_arg.SetProperty("state", state_stopped__);
					break;
				case MediaElementState::Opening:
					break;
				case MediaElementState::Closed:
					break;
				}

				RunOnUIThread([this, event_arg]() {
					fireEvent("change", event_arg);
				});
			});

			// Add "hidden" MediaElement UI onto current Window, because it doesn't work when it is not on the UI.
			// This is little bit tricky because this proxy is not kind of View and then you can't use Titanium's layout engine. 
			TitaniumWindows::Utility::SetHiddenViewForCurrentWindow(player__, navigated_event__);
		}

		void Sound::set_volume(const double& volume) TITANIUM_NOEXCEPT
		{
			Titanium::Media::Sound::set_volume(volume);
			player__->Volume = volume;
		}

		std::chrono::milliseconds Sound::get_time() const TITANIUM_NOEXCEPT
		{
			if (player__) {
			return TitaniumWindows::Utility::GetMSec(player__->Position);
			}
			return std::chrono::milliseconds(0);
		}

		void Sound::set_url(const std::string& url) TITANIUM_NOEXCEPT
		{
			player__->Source = TitaniumWindows::Utility::GetUriFromPath(url);
		}

		void Sound::set_looping(const bool& looping) TITANIUM_NOEXCEPT
		{
			Titanium::Media::Sound::set_looping(looping);
			player__->IsLooping = looping;
		}

		bool Sound::isLooping() TITANIUM_NOEXCEPT
		{
			return player__->IsLooping;
		}

		bool Sound::isPaused() TITANIUM_NOEXCEPT
		{
			return player__->CurrentState == MediaElementState::Paused;
		}

		bool Sound::isPlaying() TITANIUM_NOEXCEPT
		{
			return player__->CurrentState == MediaElementState::Playing;
		}

		void Sound::pause() TITANIUM_NOEXCEPT
		{
			player__->Pause();
		}

		void Sound::play() TITANIUM_NOEXCEPT
		{
			player__->Play();
		}

		void Sound::stop() TITANIUM_NOEXCEPT
		{
			player__->Stop();
		}

		void Sound::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::Media::Sound::enableEvent(event_name);

			if (event_name == "complete") {
				complete_event__ = player__->MediaEnded += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
					RunOnUIThread([this]() {
						const auto ctx = get_context();
						auto event_arg = ctx.CreateObject();
						event_arg.SetProperty("success", ctx.CreateBoolean(true));
						event_arg.SetProperty("code", ctx.CreateNumber(0));
						fireEvent("complete", event_arg);
					});
				});
			} else if (event_name == "error") {
				failed_event__ = player__->MediaFailed += ref new ExceptionRoutedEventHandler([this](Platform::Object^ sender, ExceptionRoutedEventArgs^ e) {
					RunOnUIThread([this, e]() {
						const auto ctx = get_context();
						auto event_arg = ctx.CreateObject();
						event_arg.SetProperty("message", ctx.CreateString(TitaniumWindows::Utility::ConvertString(e->ErrorMessage)));
						event_arg.SetProperty("success", ctx.CreateBoolean(false));
						event_arg.SetProperty("code", ctx.CreateNumber(TitaniumWindows::Utility::GetHResultErrorCode(e->ErrorMessage, -1)));
						fireEvent("error", event_arg);
					});
				});
			}
		}

		void Sound::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::Media::Sound::disableEvent(event_name);
			if (event_name == "complete") {
				player__->MediaEnded -= complete_event__;
			} else if (event_name == "error") {
				player__->MediaFailed -= failed_event__;
			}
		}
	}
}
