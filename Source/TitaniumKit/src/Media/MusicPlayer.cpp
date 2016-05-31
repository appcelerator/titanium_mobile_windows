/**
 * TitaniumKit Titanium.Media.MusicPlayer
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Media/MusicPlayer.hpp"
#include "Titanium/Media/Item.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Media
	{

		MusicPlayer::MusicPlayer(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Media.MusicPlayer")
			, playbackState__(MusicPlayerState::Stopped)
			, repeatMode__(MusicPlayerRepeat::None)
			, shuffleMode__(MusicPlayerShuffle::None)
			, volume__(0)
		{
		}

		TITANIUM_PROPERTY_READWRITE(MusicPlayer, std::chrono::seconds, currentPlaybackTime)
		TITANIUM_PROPERTY_READ(MusicPlayer, std::shared_ptr<Item>, nowPlaying)
		TITANIUM_PROPERTY_READ(MusicPlayer, MusicPlayerState, playbackState)
		TITANIUM_PROPERTY_READWRITE(MusicPlayer, MusicPlayerRepeat, repeatMode)
		TITANIUM_PROPERTY_READWRITE(MusicPlayer, MusicPlayerShuffle, shuffleMode)
		TITANIUM_PROPERTY_READWRITE(MusicPlayer, double, volume)

		void MusicPlayer::pause() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("MusicPlayer::pause: Unimplemented");
		}

		void MusicPlayer::play() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("MusicPlayer::play: Unimplemented");
		}

		void MusicPlayer::seekBackward() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("MusicPlayer::seekBackward: Unimplemented");
		}

		void MusicPlayer::seekForward() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("MusicPlayer::seekForward: Unimplemented");
		}

		void MusicPlayer::setQueue(std::vector<std::shared_ptr<Item>> queues) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("MusicPlayer::setQueue: Unimplemented");
		}

		void MusicPlayer::skipToBeginning() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("MusicPlayer::skipToBeginning: Unimplemented");
		}

		void MusicPlayer::skipToNext() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("MusicPlayer::skipToNext: Unimplemented");
		}

		void MusicPlayer::skipToPrevious() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("MusicPlayer::skipToPrevious: Unimplemented");
		}

		void MusicPlayer::stop() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("MusicPlayer::stop: Unimplemented");
		}

		void MusicPlayer::stopSeeking() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("MusicPlayer::stopSeeking: Unimplemented");
		}

		void MusicPlayer::JSExportInitialize()
		{
			JSExport<MusicPlayer>::SetClassVersion(1);
			JSExport<MusicPlayer>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(MusicPlayer, currentPlaybackTime);
			TITANIUM_ADD_PROPERTY_READONLY(MusicPlayer, nowPlaying);
			TITANIUM_ADD_PROPERTY_READONLY(MusicPlayer, playbackState);
			TITANIUM_ADD_PROPERTY(MusicPlayer, repeatMode);
			TITANIUM_ADD_PROPERTY(MusicPlayer, shuffleMode);
			TITANIUM_ADD_PROPERTY(MusicPlayer, volume);

			TITANIUM_ADD_FUNCTION(MusicPlayer, pause);
			TITANIUM_ADD_FUNCTION(MusicPlayer, play);
			TITANIUM_ADD_FUNCTION(MusicPlayer, seekBackward);
			TITANIUM_ADD_FUNCTION(MusicPlayer, seekForward);
			TITANIUM_ADD_FUNCTION(MusicPlayer, setQueue);
			TITANIUM_ADD_FUNCTION(MusicPlayer, skipToBeginning);
			TITANIUM_ADD_FUNCTION(MusicPlayer, skipToNext);
			TITANIUM_ADD_FUNCTION(MusicPlayer, skipToPrevious);
			TITANIUM_ADD_FUNCTION(MusicPlayer, stop);
			TITANIUM_ADD_FUNCTION(MusicPlayer, stopSeeking);
			TITANIUM_ADD_FUNCTION(MusicPlayer, getCurrentPlaybackTime);
			TITANIUM_ADD_FUNCTION(MusicPlayer, setCurrentPlaybackTime);
			TITANIUM_ADD_FUNCTION(MusicPlayer, getNowPlaying);
			TITANIUM_ADD_FUNCTION(MusicPlayer, getPlaybackState);
			TITANIUM_ADD_FUNCTION(MusicPlayer, getRepeatMode);
			TITANIUM_ADD_FUNCTION(MusicPlayer, setRepeatMode);
			TITANIUM_ADD_FUNCTION(MusicPlayer, getShuffleMode);
			TITANIUM_ADD_FUNCTION(MusicPlayer, setShuffleMode);
			TITANIUM_ADD_FUNCTION(MusicPlayer, getVolume);
			TITANIUM_ADD_FUNCTION(MusicPlayer, setVolume);
		}

		TITANIUM_PROPERTY_GETTER_TIME(MusicPlayer, currentPlaybackTime)
		TITANIUM_PROPERTY_SETTER_TIME_SECONDS(MusicPlayer, currentPlaybackTime)
		TITANIUM_PROPERTY_GETTER_OBJECT(MusicPlayer, nowPlaying)
		TITANIUM_PROPERTY_GETTER_ENUM(MusicPlayer, playbackState)
		TITANIUM_PROPERTY_GETTER_ENUM(MusicPlayer, repeatMode)
		TITANIUM_PROPERTY_SETTER_ENUM(MusicPlayer, repeatMode, MusicPlayerRepeat)
		TITANIUM_PROPERTY_GETTER_ENUM(MusicPlayer, shuffleMode)
		TITANIUM_PROPERTY_SETTER_ENUM(MusicPlayer, shuffleMode, MusicPlayerShuffle)
		TITANIUM_PROPERTY_GETTER_DOUBLE(MusicPlayer, volume)
		TITANIUM_PROPERTY_SETTER_DOUBLE(MusicPlayer, volume)

		TITANIUM_FUNCTION(MusicPlayer, pause)
		{
			pause();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(MusicPlayer, play)
		{
			play();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(MusicPlayer, seekBackward)
		{
			seekBackward();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(MusicPlayer, seekForward)
		{
			seekForward();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(MusicPlayer, setQueue)
		{
			ENSURE_OBJECT_AT_INDEX(js_queue, 0);

			std::vector<std::shared_ptr<Item>> queues;

			const auto queue = js_queue.GetPrivate<Item>();

			if (queue != nullptr) {
				queues.push_back(queue);
			} else if (js_queue.IsArray()) {
				const auto js_array = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_queue));
				for (const auto v : js_array) {
					queues.push_back(static_cast<JSObject>(v).GetPrivate<Item>());
				}
			} else if (js_queue.HasProperty("items")) {
				// PlayerQueue
				const auto js_playerQueue = static_cast<JSObject>(js_queue.GetProperty("items"));
				if (js_playerQueue.IsArray()) {
					const auto js_array = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_playerQueue));
					for (const auto v : js_array) {
						queues.push_back(static_cast<JSObject>(v).GetPrivate<Item>());
					}
				}
			}

			setQueue(queues);

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(MusicPlayer, skipToBeginning)
		{
			skipToBeginning();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(MusicPlayer, skipToNext)
		{
			skipToNext();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(MusicPlayer, skipToPrevious)
		{
			skipToPrevious();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(MusicPlayer, stop)
		{
			stop();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(MusicPlayer, stopSeeking)
		{
			stopSeeking();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(MusicPlayer, getCurrentPlaybackTime, currentPlaybackTime)
		TITANIUM_FUNCTION_AS_SETTER(MusicPlayer, setCurrentPlaybackTime, currentPlaybackTime)
		TITANIUM_FUNCTION_AS_GETTER(MusicPlayer, getNowPlaying, nowPlaying)
		TITANIUM_FUNCTION_AS_GETTER(MusicPlayer, getPlaybackState, playbackState)
		TITANIUM_FUNCTION_AS_GETTER(MusicPlayer, getRepeatMode, repeatMode)
		TITANIUM_FUNCTION_AS_SETTER(MusicPlayer, setRepeatMode, repeatMode)
		TITANIUM_FUNCTION_AS_GETTER(MusicPlayer, getShuffleMode, shuffleMode)
		TITANIUM_FUNCTION_AS_SETTER(MusicPlayer, setShuffleMode, shuffleMode)
		TITANIUM_FUNCTION_AS_GETTER(MusicPlayer, getVolume, volume)
		TITANIUM_FUNCTION_AS_SETTER(MusicPlayer, setVolume, volume)

	} // namespace Media
} // namespace Titanium
