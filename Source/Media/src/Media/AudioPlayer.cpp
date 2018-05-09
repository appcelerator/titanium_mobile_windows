/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Media/AudioPlayer.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
using namespace Windows::Media::Playback;
#endif
using namespace Windows::Foundation;
using TitaniumWindows::Utility::RunOnUIThread;

namespace TitaniumWindows
{
	namespace Media
	{
		AudioPlayer::AudioPlayer(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Media::AudioPlayer(js_context)
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Media::AudioPlayer::ctor Initialize");
		}

		AudioPlayer::~AudioPlayer()
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Media::AudioPlayer::dtor");
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			BackgroundMediaPlayer::Shutdown();
#endif
		}

		void AudioPlayer::JSExportInitialize()
		{
			JSExport<AudioPlayer>::SetClassVersion(1);
			JSExport<AudioPlayer>::SetParent(JSExport<Titanium::Media::AudioPlayer>::Class());
		}

		void AudioPlayer::stateChanged() TITANIUM_NOEXCEPT
		{
			RunOnUIThread([this]() {
				playing__ = isPlaying();
				paused__ = isPaused();
				volume__ = player__->Volume;
				waiting__ = (get_state() == Titanium::Media::AudioState::Buffering);

				const auto ctx = get_context();
				auto event_arg = ctx.CreateObject();
				event_arg.SetProperty("state", js_get_state());
				fireEvent("change", event_arg);
			});
		}

		void AudioPlayer::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) 
		{
			Titanium::Media::AudioPlayer::postCallAsConstructor(js_context, arguments);

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			// allow background audio on WindowsStore apps
			// this still requires Package.appxmanifest background task
			auto controls = Windows::Media::SystemMediaTransportControls::GetForCurrentView();
			controls->IsPlayEnabled = true;
			controls->IsPauseEnabled = true;
#endif

			player__ = ref new MediaElement();
#pragma warning(push)
#pragma warning(disable : 4973)
			// Note: BackgroundCapableMedia is deprecated in Windows 10
			player__->AudioCategory = AudioCategory::BackgroundCapableMedia;
#pragma warning(pop)
			player__->AreTransportControlsEnabled = true;
			player__->Visibility = Windows::UI::Xaml::Visibility::Collapsed; // Hide UI
			player__->AutoPlay = false;
			player__->IsLooping = false;
			player__->CurrentStateChanged += ref new RoutedEventHandler(
				[=](Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
					switch (player__->CurrentState) {
						case MediaElementState::Buffering:
							state__ = Titanium::Media::AudioState::Buffering;
							break;
						case MediaElementState::Paused:
							state__ = Titanium::Media::AudioState::Paused;
							break;
						case MediaElementState::Playing:
							state__ = Titanium::Media::AudioState::Playing;
							break;
						case MediaElementState::Stopped:
							state__ = Titanium::Media::AudioState::Stopped;
							break;
					}
					stateChanged();
				}
			);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			background_player__ = BackgroundMediaPlayer::Current;
			background_player__->AutoPlay = false;
			background_player__->CurrentStateChanged += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
				[=](MediaPlayer^ sender, Platform::Object^ e) {
					switch (background_player__->CurrentState) {
						case MediaPlayerState::Buffering:
							state__ = Titanium::Media::AudioState::Buffering;
							break;
						case MediaPlayerState::Paused:
							state__ = Titanium::Media::AudioState::Paused;
							break;
						case MediaPlayerState::Playing:
							state__ = Titanium::Media::AudioState::Playing;
							break;
						case MediaPlayerState::Stopped:
							state__ = Titanium::Media::AudioState::Stopped;
							break;
					}
					TitaniumWindows::Utility::RunOnUIThread([=]{
						stateChanged();
					});
				}
			);
#endif

			// Add "hidden" MediaElement UI onto current Window, because it doesn't work when it is not on the UI.
			// This is little bit tricky because this proxy is not kind of View and then you can't use Titanium's layout engine. 
			TitaniumWindows::Utility::SetHiddenViewForCurrentWindow(player__, navigated_event__);
		}

		void AudioPlayer::set_volume(const double& volume) TITANIUM_NOEXCEPT
		{
			Titanium::Media::AudioPlayer::set_volume(volume);
			player__->Volume = volume;
		}

		void AudioPlayer::set_paused(const bool& paused) TITANIUM_NOEXCEPT
		{
			Titanium::Media::AudioPlayer::set_paused(paused);
			if (paused) {
				pause();
			} else {
				play();
			}
		}

		void AudioPlayer::set_allowBackground(const bool& allowBackground) TITANIUM_NOEXCEPT
		{
			Titanium::Media::AudioPlayer::set_allowBackground(allowBackground);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			if (get_playing()) {
				if (allowBackground) {
					background_player__->Position = player__->Position;
					player__->Pause();
					background_player__->Play();
				} else {
					player__->Position = background_player__->Position;
					background_player__->Pause();
					player__->Play();
				}
			}
#endif
		}

		std::chrono::milliseconds AudioPlayer::get_time() const TITANIUM_NOEXCEPT
		{
			if (player__) {
				return TitaniumWindows::Utility::GetMSec(player__->Position);
			}
			return std::chrono::milliseconds(0);
		}

		void AudioPlayer::set_url(const std::string& url) TITANIUM_NOEXCEPT
		{
			Titanium::Media::AudioPlayer::set_url(url);
			auto uri = TitaniumWindows::Utility::GetUriFromPath(url);
			player__->Source = uri;
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			background_player__->SetUriSource(uri);
#endif
		}

		void AudioPlayer::pause() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			if (get_allowBackground()) {
				background_player__->Pause();
			} else {
				player__->Pause();
			}
#else
			player__->Pause();
#endif
		}

		void AudioPlayer::play() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			if (get_allowBackground()) {
				background_player__->Play();
			} else {
				player__->Play();
			}
#else
			player__->Play();
#endif
		}

		void AudioPlayer::start() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			if (get_allowBackground()) {
				background_player__->Play();
			} else {
				player__->Play();
			}
#else
			player__->Play();
#endif
		}

		void AudioPlayer::stop() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			if (get_allowBackground()) {
				background_player__->Pause();

				// since there is no Stop(), reset position
				auto position = Windows::Foundation::TimeSpan();
				position.Duration = 0;
				background_player__->Position = position;
			} else {
				player__->Stop();
			}
#else
			player__->Stop();
#endif
		}

		void AudioPlayer::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::Media::AudioPlayer::enableEvent(event_name);
			if (event_name == "complete") {
				const auto mediaEnded = [=] {
					RunOnUIThread([this]() {
						const auto ctx = get_context();
						auto event_arg = ctx.CreateObject();
						event_arg.SetProperty("success", ctx.CreateBoolean(true));
						event_arg.SetProperty("code", ctx.CreateNumber(0));
						fireEvent("complete", event_arg);
					});
				};
				complete_event__ = player__->MediaEnded += ref new RoutedEventHandler(
					[=](Platform::Object^ sender, RoutedEventArgs^ e) {
						mediaEnded();
					}
				);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
				background_complete_event__ = background_player__->MediaEnded += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
					[=](MediaPlayer^ sender, Platform::Object^ e){
						mediaEnded();
					}
				);
#endif
			} else if (event_name == "error") {
				const auto mediaFailed = [=] {
					RunOnUIThread([this]() {
						const auto ctx = get_context();
						auto event_arg = ctx.CreateObject();
						event_arg.SetProperty("success", ctx.CreateBoolean(true));
						event_arg.SetProperty("code", ctx.CreateNumber(0));
						fireEvent("complete", event_arg);
					});
				};
				failed_event__ = player__->MediaFailed += ref new ExceptionRoutedEventHandler(
					[=](Platform::Object^ sender, ExceptionRoutedEventArgs^ e) {
						mediaFailed();
					}
				);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
				background_failed_event__ = background_player__->MediaFailed += ref new TypedEventHandler<MediaPlayer^, MediaPlayerFailedEventArgs^>(
					[=](MediaPlayer^ sender, MediaPlayerFailedEventArgs^ e) {
						mediaFailed();
					}
				);
#endif
			}
		}

		void AudioPlayer::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::Media::AudioPlayer::disableEvent(event_name);
			if (event_name == "complete") {
				player__->MediaEnded -= complete_event__;
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
				background_player__->MediaEnded -= background_complete_event__;
#endif
			} else if (event_name == "error") {
				player__->MediaFailed -= failed_event__;
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
				background_player__->MediaFailed -= background_failed_event__;
#endif
			}
		}
	}
}
