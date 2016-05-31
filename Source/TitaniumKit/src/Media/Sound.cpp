/**
 * TitaniumKit Titanium.Media.Sound
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Media/Sound.hpp"
#include "Titanium/Media/Constants.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Media
	{

		Sound::Sound(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Media.Sound")
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
			, looping__(false)
			, paused__(false)
			, playing__(false)
			, url__("")
			, volume__(0.0)
		{
		}

		TITANIUM_PROPERTY_READWRITE(Sound, bool, allowBackground)
		TITANIUM_PROPERTY_READ(Sound, double, duration)
		TITANIUM_PROPERTY_READWRITE(Sound, bool, looping)
		TITANIUM_PROPERTY_READ(Sound, bool, playing)
		TITANIUM_PROPERTY_READWRITE(Sound, std::chrono::milliseconds, time)
		TITANIUM_PROPERTY_READWRITE(Sound, std::string, url)
		TITANIUM_PROPERTY_READWRITE(Sound, double, volume)

		TITANIUM_PROPERTY_READ(Sound, bool, paused)
		void Sound::set_paused(const bool& paused) TITANIUM_NOEXCEPT
		{
			if (paused) {
				pause();
			} else {
				play();
			}
		}
		bool Sound::isLooping() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Sound::isLooping: Unimplemented");
			return false;
		}

		bool Sound::isPaused() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Sound::isPaused: Unimplemented");
			return false;
		}

		bool Sound::isPlaying() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Sound::isPlaying: Unimplemented");
			return false;
		}

		void Sound::pause() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Sound::pause: Unimplemented");
		}

		void Sound::play() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Sound::play: Unimplemented");
		}

		void Sound::release() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Sound::release: Unimplemented");
		}

		void Sound::reset() TITANIUM_NOEXCEPT
		{
			this->set_time(std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(0)));
		}

		void Sound::stop() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Sound::stop: Unimplemented");
		}

		void Sound::JSExportInitialize()
		{
			JSExport<Sound>::SetClassVersion(1);
			JSExport<Sound>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(Sound, STATE_BUFFERING);
			TITANIUM_ADD_PROPERTY_READONLY(Sound, STATE_INITIALIZED);
			TITANIUM_ADD_PROPERTY_READONLY(Sound, STATE_PAUSED);
			TITANIUM_ADD_PROPERTY_READONLY(Sound, STATE_PLAYING);
			TITANIUM_ADD_PROPERTY_READONLY(Sound, STATE_STARTING);
			TITANIUM_ADD_PROPERTY_READONLY(Sound, STATE_STOPPED);
			TITANIUM_ADD_PROPERTY_READONLY(Sound, STATE_STOPPING);
			TITANIUM_ADD_PROPERTY_READONLY(Sound, STATE_WAITING_FOR_DATA);
			TITANIUM_ADD_PROPERTY_READONLY(Sound, STATE_WAITING_FOR_QUEUE);
			TITANIUM_ADD_PROPERTY(Sound, allowBackground);
			TITANIUM_ADD_PROPERTY_READONLY(Sound, duration);
			TITANIUM_ADD_PROPERTY(Sound, looping);
			TITANIUM_ADD_PROPERTY(Sound, paused);
			TITANIUM_ADD_PROPERTY_READONLY(Sound, playing);
			TITANIUM_ADD_PROPERTY(Sound, time);
			TITANIUM_ADD_PROPERTY(Sound, url);
			TITANIUM_ADD_PROPERTY(Sound, volume);

			TITANIUM_ADD_FUNCTION(Sound, isLooping);
			TITANIUM_ADD_FUNCTION(Sound, isPaused);
			TITANIUM_ADD_FUNCTION(Sound, isPlaying);
			TITANIUM_ADD_FUNCTION(Sound, pause);
			TITANIUM_ADD_FUNCTION(Sound, play);
			TITANIUM_ADD_FUNCTION(Sound, release);
			TITANIUM_ADD_FUNCTION(Sound, reset);
			TITANIUM_ADD_FUNCTION(Sound, setLooping);
			TITANIUM_ADD_FUNCTION(Sound, setPaused);
			TITANIUM_ADD_FUNCTION(Sound, stop);
			TITANIUM_ADD_FUNCTION(Sound, getDuration);
			TITANIUM_ADD_FUNCTION(Sound, getTime);
			TITANIUM_ADD_FUNCTION(Sound, setTime);
			TITANIUM_ADD_FUNCTION(Sound, getUrl);
			TITANIUM_ADD_FUNCTION(Sound, setUrl);
			TITANIUM_ADD_FUNCTION(Sound, getVolume);
			TITANIUM_ADD_FUNCTION(Sound, setVolume);
		}

		TITANIUM_PROPERTY_GETTER(Sound, STATE_BUFFERING)
		{
			return state_buffering__;
		}

		TITANIUM_PROPERTY_GETTER(Sound, STATE_INITIALIZED)
		{
			return state_initialized__;
		}

		TITANIUM_PROPERTY_GETTER(Sound, STATE_PAUSED)
		{
			return state_paused__;
		}

		TITANIUM_PROPERTY_GETTER(Sound, STATE_PLAYING)
		{
			return state_playing__;
		}

		TITANIUM_PROPERTY_GETTER(Sound, STATE_STARTING)
		{
			return state_starting__;
		}

		TITANIUM_PROPERTY_GETTER(Sound, STATE_STOPPED)
		{
			return state_stopped__;
		}

		TITANIUM_PROPERTY_GETTER(Sound, STATE_STOPPING)
		{
			return state_stopping__;
		}

		TITANIUM_PROPERTY_GETTER(Sound, STATE_WAITING_FOR_DATA)
		{
			return state_waiting_for_data__;
		}

		TITANIUM_PROPERTY_GETTER(Sound, STATE_WAITING_FOR_QUEUE)
		{
			return state_waiting_for_queue__;
		}

		TITANIUM_PROPERTY_GETTER_BOOL(Sound, allowBackground)
		TITANIUM_PROPERTY_SETTER_BOOL(Sound, allowBackground)
		TITANIUM_PROPERTY_GETTER_DOUBLE(Sound, duration)
		TITANIUM_PROPERTY_GETTER_BOOL(Sound, looping)
		TITANIUM_PROPERTY_SETTER_BOOL(Sound, looping)
		TITANIUM_PROPERTY_GETTER_BOOL(Sound, paused)
		TITANIUM_PROPERTY_SETTER_BOOL(Sound, paused)
		TITANIUM_PROPERTY_GETTER_BOOL(Sound, playing)
		TITANIUM_PROPERTY_GETTER_TIME(Sound, time)
		TITANIUM_PROPERTY_SETTER_TIME(Sound, time)
		TITANIUM_PROPERTY_GETTER_STRING(Sound, url)
		TITANIUM_PROPERTY_SETTER_STRING(Sound, url)
		TITANIUM_PROPERTY_GETTER_DOUBLE(Sound, volume)
		TITANIUM_PROPERTY_SETTER_DOUBLE(Sound, volume)

		TITANIUM_FUNCTION(Sound, isLooping)
		{
			return get_context().CreateBoolean(isLooping());
		}
		TITANIUM_FUNCTION(Sound, isPaused)
		{
			return get_context().CreateBoolean(isPaused());
		}
		TITANIUM_FUNCTION(Sound, isPlaying)
		{
			return get_context().CreateBoolean(isPlaying());
		}
		TITANIUM_FUNCTION(Sound, pause)
		{
			pause();
			return get_context().CreateUndefined();
		}
		TITANIUM_FUNCTION(Sound, play)
		{
			play();
			return get_context().CreateUndefined();
		}
		TITANIUM_FUNCTION(Sound, release)
		{
			release();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Sound, reset)
		{
			reset();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Sound, stop)
		{
			stop();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(Sound, getDuration, duration)
		TITANIUM_FUNCTION_AS_GETTER(Sound, getTime, time)
		TITANIUM_FUNCTION_AS_SETTER(Sound, setTime, time)
		TITANIUM_FUNCTION_AS_GETTER(Sound, getUrl, url)
		TITANIUM_FUNCTION_AS_SETTER(Sound, setUrl, url)
		TITANIUM_FUNCTION_AS_GETTER(Sound, getVolume, volume)
		TITANIUM_FUNCTION_AS_SETTER(Sound, setVolume, volume)
		TITANIUM_FUNCTION_AS_GETTER(Sound, getLooping, looping)
		TITANIUM_FUNCTION_AS_SETTER(Sound, setLooping, looping)
		TITANIUM_FUNCTION_AS_GETTER(Sound, getPaused, paused)
		TITANIUM_FUNCTION_AS_SETTER(Sound, setPaused, paused)

	} // namespace Media
} // namespace Titanium
