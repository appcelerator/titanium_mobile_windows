/**
 * TitaniumKit Titanium.Media.AudioPlayer
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Media/AudioPlayer.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Media
	{

		AudioPlayer::AudioPlayer(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Media.AudioPlayer")
			, state_buffering__(js_context.CreateNumber(static_cast<std::uint32_t>(AudioState::Buffering)))
			, state_initialized__(js_context.CreateNumber(static_cast<std::uint32_t>(AudioState::Initialized)))
			, state_paused__(js_context.CreateNumber(static_cast<std::uint32_t>(AudioState::Paused)))
			, state_playing__(js_context.CreateNumber(static_cast<std::uint32_t>(AudioState::Playing)))
			, state_starting__(js_context.CreateNumber(static_cast<std::uint32_t>(AudioState::Starting)))
			, state_stopped__(js_context.CreateNumber(static_cast<std::uint32_t>(AudioState::Stopped)))
			, state_stopping__(js_context.CreateNumber(static_cast<std::uint32_t>(AudioState::Stopping)))
			, state_waiting_for_data__(js_context.CreateNumber(static_cast<std::uint32_t>(AudioState::WaitingForData)))
			, state_waiting_for_queue__(js_context.CreateNumber(static_cast<std::uint32_t>(AudioState::WaitingForQueue)))
			, allowBackground__(false)
			, autoplay__(false)
			, bitRate__(0)
			, idle__(false)
			, paused__(false)
			, playing__(false)
			, state__(AudioState::Stopped)
			, url__("")
			, volume__(0)
			, waiting__(false)
			, bufferSize__(0)
		{
		}

		TITANIUM_PROPERTY_READWRITE(AudioPlayer, bool, allowBackground)
		TITANIUM_PROPERTY_READWRITE(AudioPlayer, bool, autoplay)
		TITANIUM_PROPERTY_READWRITE(AudioPlayer, std::uint32_t, bitRate)
		TITANIUM_PROPERTY_READ(AudioPlayer, std::chrono::milliseconds, duration)
		TITANIUM_PROPERTY_READ(AudioPlayer, bool, idle)
		TITANIUM_PROPERTY_READWRITE(AudioPlayer, bool, paused)
		TITANIUM_PROPERTY_READ(AudioPlayer, bool, playing)
		TITANIUM_PROPERTY_READ(AudioPlayer, std::chrono::milliseconds, progress)
		TITANIUM_PROPERTY_READ(AudioPlayer, AudioState, state)
		TITANIUM_PROPERTY_READWRITE(AudioPlayer, std::string, url)
		TITANIUM_PROPERTY_READWRITE(AudioPlayer, double, volume)
		TITANIUM_PROPERTY_READ(AudioPlayer, bool, waiting)
		TITANIUM_PROPERTY_READWRITE(AudioPlayer, std::uint32_t, bufferSize)
		TITANIUM_PROPERTY_READWRITE(AudioPlayer, std::chrono::milliseconds, time)

		bool AudioPlayer::isPaused() TITANIUM_NOEXCEPT
		{
			return (get_state() == AudioState::Paused);
		}

		bool AudioPlayer::isPlaying() TITANIUM_NOEXCEPT
		{
			return (get_state() == AudioState::Playing);
		}

		void AudioPlayer::pause() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("AudioPlayer::pause: Unimplemented");
		}

		void AudioPlayer::play() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("AudioPlayer::play: Unimplemented");
		}

		void AudioPlayer::release() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("AudioPlayer::release: Unimplemented");
		}

		void AudioPlayer::start() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("AudioPlayer::start: Unimplemented");
		}

		std::string AudioPlayer::stateDescription(const AudioState& state) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("AudioPlayer::stateDescription: Unimplemented");
			return "";
		}

		void AudioPlayer::stop() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("AudioPlayer::stop: Unimplemented");
		}

		void AudioPlayer::JSExportInitialize()
		{
			JSExport<AudioPlayer>::SetClassVersion(1);
			JSExport<AudioPlayer>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, STATE_BUFFERING);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, STATE_INITIALIZED);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, STATE_PAUSED);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, STATE_PLAYING);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, STATE_STARTING);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, STATE_STOPPED);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, STATE_STOPPING);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, STATE_WAITING_FOR_DATA);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, STATE_WAITING_FOR_QUEUE);
			TITANIUM_ADD_PROPERTY(AudioPlayer, allowBackground);
			TITANIUM_ADD_PROPERTY(AudioPlayer, autoplay);
			TITANIUM_ADD_PROPERTY(AudioPlayer, bitRate);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, duration);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, idle);
			TITANIUM_ADD_PROPERTY(AudioPlayer, paused);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, playing);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, progress);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, state);
			TITANIUM_ADD_PROPERTY(AudioPlayer, url);
			TITANIUM_ADD_PROPERTY(AudioPlayer, volume);
			TITANIUM_ADD_PROPERTY_READONLY(AudioPlayer, waiting);
			TITANIUM_ADD_PROPERTY(AudioPlayer, bufferSize);
			TITANIUM_ADD_PROPERTY(AudioPlayer, time);

			TITANIUM_ADD_FUNCTION(AudioPlayer, isPaused);
			TITANIUM_ADD_FUNCTION(AudioPlayer, isPlaying);
			TITANIUM_ADD_FUNCTION(AudioPlayer, pause);
			TITANIUM_ADD_FUNCTION(AudioPlayer, play);
			TITANIUM_ADD_FUNCTION(AudioPlayer, release);
			TITANIUM_ADD_FUNCTION(AudioPlayer, start);
			TITANIUM_ADD_FUNCTION(AudioPlayer, stateDescription);
			TITANIUM_ADD_FUNCTION(AudioPlayer, stop);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getAllowBackground);
			TITANIUM_ADD_FUNCTION(AudioPlayer, setAllowBackground);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getAutoplay);
			TITANIUM_ADD_FUNCTION(AudioPlayer, setAutoplay);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getBitRate);
			TITANIUM_ADD_FUNCTION(AudioPlayer, setBitRate);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getDuration);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getIdle);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getPaused);
			TITANIUM_ADD_FUNCTION(AudioPlayer, setPaused);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getPlaying);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getProgress);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getState);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getUrl);
			TITANIUM_ADD_FUNCTION(AudioPlayer, setUrl);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getVolume);
			TITANIUM_ADD_FUNCTION(AudioPlayer, setVolume);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getWaiting);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getBufferSize);
			TITANIUM_ADD_FUNCTION(AudioPlayer, setBufferSize);
			TITANIUM_ADD_FUNCTION(AudioPlayer, getTime);
			TITANIUM_ADD_FUNCTION(AudioPlayer, setTime);
		}


		TITANIUM_PROPERTY_GETTER(AudioPlayer, STATE_BUFFERING)
		{
			return state_buffering__;
		}

		TITANIUM_PROPERTY_GETTER(AudioPlayer, STATE_INITIALIZED)
		{
			return state_initialized__;
		}

		TITANIUM_PROPERTY_GETTER(AudioPlayer, STATE_PAUSED)
		{
			return state_paused__;
		}

		TITANIUM_PROPERTY_GETTER(AudioPlayer, STATE_PLAYING)
		{
			return state_playing__;
		}

		TITANIUM_PROPERTY_GETTER(AudioPlayer, STATE_STARTING)
		{
			return state_starting__;
		}

		TITANIUM_PROPERTY_GETTER(AudioPlayer, STATE_STOPPED)
		{
			return state_stopped__;
		}

		TITANIUM_PROPERTY_GETTER(AudioPlayer, STATE_STOPPING)
		{
			return state_stopping__;
		}

		TITANIUM_PROPERTY_GETTER(AudioPlayer, STATE_WAITING_FOR_DATA)
		{
			return state_waiting_for_data__;
		}

		TITANIUM_PROPERTY_GETTER(AudioPlayer, STATE_WAITING_FOR_QUEUE)
		{
			return state_waiting_for_queue__;
		}

		TITANIUM_PROPERTY_GETTER_BOOL(AudioPlayer, allowBackground)
		TITANIUM_PROPERTY_SETTER_BOOL(AudioPlayer, allowBackground)
		TITANIUM_PROPERTY_GETTER_BOOL(AudioPlayer, autoplay)
		TITANIUM_PROPERTY_SETTER_BOOL(AudioPlayer, autoplay)
		TITANIUM_PROPERTY_GETTER_UINT(AudioPlayer, bitRate)
		TITANIUM_PROPERTY_SETTER_UINT(AudioPlayer, bitRate)
		TITANIUM_PROPERTY_GETTER_BOOL(AudioPlayer, idle)
		TITANIUM_PROPERTY_GETTER_BOOL(AudioPlayer, paused)
		TITANIUM_PROPERTY_SETTER_BOOL(AudioPlayer, paused)
		TITANIUM_PROPERTY_GETTER_BOOL(AudioPlayer, playing)
		TITANIUM_PROPERTY_GETTER_STRING(AudioPlayer, url)
		TITANIUM_PROPERTY_SETTER_STRING(AudioPlayer, url)
		TITANIUM_PROPERTY_GETTER_DOUBLE(AudioPlayer, volume)
		TITANIUM_PROPERTY_SETTER_DOUBLE(AudioPlayer, volume)
		TITANIUM_PROPERTY_GETTER_BOOL(AudioPlayer, waiting)
		TITANIUM_PROPERTY_GETTER_UINT(AudioPlayer, bufferSize)
		TITANIUM_PROPERTY_SETTER_UINT(AudioPlayer, bufferSize)
		TITANIUM_PROPERTY_GETTER_TIME(AudioPlayer, time)
		TITANIUM_PROPERTY_SETTER_TIME(AudioPlayer, time)
		TITANIUM_PROPERTY_GETTER_ENUM(AudioPlayer, state)
		TITANIUM_PROPERTY_GETTER_TIME(AudioPlayer, duration)
		TITANIUM_PROPERTY_GETTER_TIME(AudioPlayer, progress)

		TITANIUM_FUNCTION(AudioPlayer, isPaused)
		{
			return get_context().CreateBoolean(isPaused());
		}

		TITANIUM_FUNCTION(AudioPlayer, isPlaying)
		{
			return get_context().CreateBoolean(isPlaying());
		}

		TITANIUM_FUNCTION(AudioPlayer, pause)
		{
			pause();
			return get_context().CreateUndefined();
		}
		TITANIUM_FUNCTION(AudioPlayer, play)
		{
			play();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(AudioPlayer, release)
		{
			release();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(AudioPlayer, start)
		{
			start();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(AudioPlayer, stateDescription)
		{
			ENSURE_UINT_AT_INDEX(state, 0);
			return get_context().CreateString(stateDescription(static_cast<AudioState>(state)));
		}

		TITANIUM_FUNCTION(AudioPlayer, stop)
		{
			stop();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getAllowBackground, allowBackground)
		TITANIUM_FUNCTION_AS_SETTER(AudioPlayer, setAllowBackground, allowBackground)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getAutoplay, autoplay)
		TITANIUM_FUNCTION_AS_SETTER(AudioPlayer, setAutoplay, autoplay)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getBitRate, bitRate)
		TITANIUM_FUNCTION_AS_SETTER(AudioPlayer, setBitRate, bitRate)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getDuration, duration)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getIdle, idle)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getPaused, paused)
		TITANIUM_FUNCTION_AS_SETTER(AudioPlayer, setPaused, paused)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getPlaying, playing)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getProgress, progress)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getState, state)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getUrl, url)
		TITANIUM_FUNCTION_AS_SETTER(AudioPlayer, setUrl, url)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getVolume, volume)
		TITANIUM_FUNCTION_AS_SETTER(AudioPlayer, setVolume, volume)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getWaiting, waiting)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getBufferSize, bufferSize)
		TITANIUM_FUNCTION_AS_SETTER(AudioPlayer, setBufferSize, bufferSize)
		TITANIUM_FUNCTION_AS_GETTER(AudioPlayer, getTime, time)
		TITANIUM_FUNCTION_AS_SETTER(AudioPlayer, setTime, time)

	} // namespace Media
} // namespace Titanium
