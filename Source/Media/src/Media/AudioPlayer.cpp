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
#include "Titanium/MediaModule.hpp"

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
				
				const auto media =  static_cast<JSObject>(ctx.JSEvaluateScript("Ti.Media")).GetPrivate<Titanium::MediaModule>();
				media->set_audioPlaying(playing__);

				auto event_arg = ctx.CreateObject();
				event_arg.SetProperty("state", js_get_state());
				fireEvent("change", event_arg);
			});
		}

		void AudioPlayer::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) 
		{
			Titanium::Media::AudioPlayer::postCallAsConstructor(js_context, arguments);

			player__ = ref new MediaPlayer();
			player__->AudioCategory = Windows::Media::Playback::MediaPlayerAudioCategory::Media;
			player__->AutoPlay = false;
			player__->IsLoopingEnabled = false;
			player__->PlaybackSession->PlaybackStateChanged += ref new TypedEventHandler<MediaPlaybackSession^, Platform::Object^>(
				[=](MediaPlaybackSession^ sender, Platform::Object^ e) {
					switch (player__->PlaybackSession->PlaybackState) {
					case MediaPlaybackState::Buffering:
							state__ = Titanium::Media::AudioState::Buffering;
							break;
						case MediaPlaybackState::Paused:
							state__ = Titanium::Media::AudioState::Paused;
							break;
						case MediaPlaybackState::Playing:
							state__ = Titanium::Media::AudioState::Playing;
							break;
						case MediaPlaybackState::Opening:
							state__ = Titanium::Media::AudioState::Starting;
							break;
					}
					stateChanged();
				}
			);
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

		std::chrono::milliseconds AudioPlayer::get_time() const TITANIUM_NOEXCEPT
		{
			if (player__) {
				return TitaniumWindows::Utility::GetMSec(player__->PlaybackSession->Position);
			}
			return std::chrono::milliseconds(0);
		}

		void AudioPlayer::set_url(const std::string& url) TITANIUM_NOEXCEPT
		{
			Titanium::Media::AudioPlayer::set_url(url);
			auto uri = TitaniumWindows::Utility::GetUriFromPath(url);
			player__->Source = Windows::Media::Core::MediaSource::CreateFromUri(uri);
		}

		void AudioPlayer::pause() TITANIUM_NOEXCEPT
		{
			player__->Pause();
		}

		void AudioPlayer::play() TITANIUM_NOEXCEPT
		{
			player__->Play();
		}

		void AudioPlayer::start() TITANIUM_NOEXCEPT
		{
			player__->Play();
		}

		void AudioPlayer::stop() TITANIUM_NOEXCEPT
		{
			// since there is no Stop(), reset position
			auto position = Windows::Foundation::TimeSpan();
			position.Duration = 0;

			player__->Pause();
			player__->PlaybackSession->Position = position;
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
				complete_event__ = player__->MediaEnded += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
					[=](MediaPlayer^ sender, Platform::Object^ e) {
						mediaEnded();
					}
				);
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
				failed_event__ = player__->MediaFailed += ref new TypedEventHandler<MediaPlayer^, MediaPlayerFailedEventArgs^>(
					[=](MediaPlayer^ sender, MediaPlayerFailedEventArgs^ e) {
						mediaFailed();
					}
				);
			}
		}

		void AudioPlayer::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::Media::AudioPlayer::disableEvent(event_name);
			if (event_name == "complete") {
				player__->MediaEnded -= complete_event__;
			} else if (event_name == "error") {
				player__->MediaFailed -= failed_event__;
			}
		}
	}
}
