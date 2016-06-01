/**
 * TitaniumKit Titanium.Media.VideoPlayer
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Media/VideoPlayer.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Media
	{

		using namespace Titanium::UI;

		VideoPlayer::VideoPlayer(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.Media.VideoPlayer")
			, allowsAirPlay__(false)
			, autoplay__(true)
			, contentURL__("")
			, fullscreen__(false)
			, initialPlaybackTime__(0)
			, loadState__(VideoLoadState::Unknown)
			, mediaControlStyle__(VideoControlStyle::Default)
			, movieControlMode__(VideoControlStyle::Default)
			, playbackState__(VideoPlaybackState::Stopped)
			, playing__(false)
			, repeatMode__(VideoRepeatMode::None)
			, scalingMode__(VideoScaling::None)
			, sourceType__(VideoSourceType::Unknown)
			, useApplicationAudioSession__(true)
			, volume__(1)
		{
		}

		TITANIUM_PROPERTY_READWRITE(VideoPlayer, bool, allowsAirPlay)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, bool, autoplay)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, std::string, contentURL)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, std::chrono::milliseconds, currentPlaybackTime)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, std::chrono::milliseconds, duration)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, std::chrono::milliseconds, endPlaybackTime)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, bool, fullscreen)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, std::chrono::milliseconds, initialPlaybackTime)
		TITANIUM_PROPERTY_READ(VideoPlayer, VideoLoadState, loadState);
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, std::shared_ptr<Titanium::Blob>, media)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, VideoControlStyle, mediaControlStyle)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, std::unordered_set<VideoMediaType>, mediaTypes)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, VideoControlStyle, movieControlMode)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, Dimension, naturalSize)
		TITANIUM_PROPERTY_READ(VideoPlayer, std::chrono::milliseconds, playableDuration)
		TITANIUM_PROPERTY_READ(VideoPlayer, VideoPlaybackState, playbackState)
		TITANIUM_PROPERTY_READ(VideoPlayer, bool, playing)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, VideoRepeatMode, repeatMode)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, VideoScaling, scalingMode)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, VideoSourceType, sourceType)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, std::vector<std::string>, urls)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, bool, useApplicationAudioSession)
		TITANIUM_PROPERTY_READWRITE(VideoPlayer, double, volume)

		void VideoPlayer::cancelAllThumbnailImageRequests() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("VideoPlayer::cancelAllThumbnailImageRequests: Unimplemented");
		}

		void VideoPlayer::pause() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("VideoPlayer::pause: Unimplemented");
		}

		void VideoPlayer::play() TITANIUM_NOEXCEPT
		{
			// set initial playback time when video has been stopped
			if (get_playbackState() == VideoPlaybackState::Stopped) {
				set_currentPlaybackTime(get_initialPlaybackTime());
			}
		}

		void VideoPlayer::release() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("VideoPlayer::release: Unimplemented");
		}

		void VideoPlayer::requestThumbnailImagesAtTimes(std::vector<std::chrono::seconds> times, const VideoTimeOption& option, JSValue callback) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("VideoPlayer::requestThumbnailImagesAtTimes: Unimplemented");
		}

		void VideoPlayer::setBackgroundView(std::shared_ptr<View> view) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("VideoPlayer::setBackgroundView: Unimplemented");
		}

		void VideoPlayer::stop() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("VideoPlayer::stop: Unimplemented");
		}

		std::shared_ptr<Titanium::Blob> VideoPlayer::thumbnailImageAtTime(const std::chrono::seconds& time, const VideoTimeOption& option) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("VideoPlayer::thumbnailImageAtTime: Unimplemented");
			return nullptr;
		}

		void VideoPlayer::JSExportInitialize()
		{
			JSExport<VideoPlayer>::SetClassVersion(1);
			JSExport<VideoPlayer>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(VideoPlayer, allowsAirPlay);
			TITANIUM_ADD_PROPERTY(VideoPlayer, autoplay);
			TITANIUM_ADD_PROPERTY(VideoPlayer, contentURL);
			TITANIUM_ADD_PROPERTY(VideoPlayer, currentPlaybackTime);
			TITANIUM_ADD_PROPERTY(VideoPlayer, duration);
			TITANIUM_ADD_PROPERTY(VideoPlayer, endPlaybackTime);
			TITANIUM_ADD_PROPERTY(VideoPlayer, fullscreen);
			TITANIUM_ADD_PROPERTY(VideoPlayer, initialPlaybackTime);
			TITANIUM_ADD_PROPERTY_READONLY(VideoPlayer, loadState);
			TITANIUM_ADD_PROPERTY(VideoPlayer, media);
			TITANIUM_ADD_PROPERTY(VideoPlayer, mediaControlStyle);
			TITANIUM_ADD_PROPERTY(VideoPlayer, mediaTypes);
			TITANIUM_ADD_PROPERTY(VideoPlayer, movieControlMode);
			TITANIUM_ADD_PROPERTY(VideoPlayer, naturalSize);
			TITANIUM_ADD_PROPERTY_READONLY(VideoPlayer, playableDuration);
			TITANIUM_ADD_PROPERTY_READONLY(VideoPlayer, playbackState);
			TITANIUM_ADD_PROPERTY_READONLY(VideoPlayer, playing);
			TITANIUM_ADD_PROPERTY(VideoPlayer, repeatMode);
			TITANIUM_ADD_PROPERTY(VideoPlayer, scalingMode);
			TITANIUM_ADD_PROPERTY(VideoPlayer, sourceType);
			TITANIUM_ADD_PROPERTY(VideoPlayer, url);
			TITANIUM_ADD_PROPERTY(VideoPlayer, useApplicationAudioSession);
			TITANIUM_ADD_PROPERTY(VideoPlayer, volume);

			TITANIUM_ADD_FUNCTION(VideoPlayer, cancelAllThumbnailImageRequests);
			TITANIUM_ADD_FUNCTION(VideoPlayer, pause);
			TITANIUM_ADD_FUNCTION(VideoPlayer, play);
			TITANIUM_ADD_FUNCTION(VideoPlayer, release);
			TITANIUM_ADD_FUNCTION(VideoPlayer, requestThumbnailImagesAtTimes);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setBackgroundView);
			TITANIUM_ADD_FUNCTION(VideoPlayer, stop);
			TITANIUM_ADD_FUNCTION(VideoPlayer, thumbnailImageAtTime);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getAllowsAirPlay);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setAllowsAirPlay);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getAutoplay);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setAutoplay);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getContentURL);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setContentURL);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getCurrentPlaybackTime);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setCurrentPlaybackTime);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getDuration);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setDuration);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getEndPlaybackTime);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setEndPlaybackTime);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getFullscreen);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setFullscreen);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getInitialPlaybackTime);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setInitialPlaybackTime);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getLoadState);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setMedia);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getMediaControlStyle);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setMediaControlStyle);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getMediaTypes);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setMediaTypes);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getMovieControlMode);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setMovieControlMode);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getNaturalSize);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setNaturalSize);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getPlayableDuration);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getPlaybackState);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getPlaying);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getRepeatMode);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setRepeatMode);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getScalingMode);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setScalingMode);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getSourceType);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setSourceType);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getUrl);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setUrl);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getUseApplicationAudioSession);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setUseApplicationAudioSession);
			TITANIUM_ADD_FUNCTION(VideoPlayer, getVolume);
			TITANIUM_ADD_FUNCTION(VideoPlayer, setVolume);
		}

		TITANIUM_PROPERTY_GETTER_BOOL(VideoPlayer, allowsAirPlay)
		TITANIUM_PROPERTY_SETTER_BOOL(VideoPlayer, allowsAirPlay)
		TITANIUM_PROPERTY_GETTER_BOOL(VideoPlayer, autoplay)
		TITANIUM_PROPERTY_SETTER_BOOL(VideoPlayer, autoplay)
		TITANIUM_PROPERTY_GETTER_STRING(VideoPlayer, contentURL)
		TITANIUM_PROPERTY_SETTER_STRING(VideoPlayer, contentURL)
		TITANIUM_PROPERTY_GETTER_TIME(VideoPlayer, currentPlaybackTime)
		TITANIUM_PROPERTY_SETTER_TIME(VideoPlayer, currentPlaybackTime)
		TITANIUM_PROPERTY_GETTER_TIME(VideoPlayer, duration)
		TITANIUM_PROPERTY_SETTER_TIME(VideoPlayer, duration)
		TITANIUM_PROPERTY_GETTER_TIME(VideoPlayer, endPlaybackTime)
		TITANIUM_PROPERTY_SETTER_TIME(VideoPlayer, endPlaybackTime)
		TITANIUM_PROPERTY_GETTER_BOOL(VideoPlayer, fullscreen)
		TITANIUM_PROPERTY_SETTER_BOOL(VideoPlayer, fullscreen)
		TITANIUM_PROPERTY_GETTER_TIME(VideoPlayer, initialPlaybackTime)
		TITANIUM_PROPERTY_SETTER_TIME(VideoPlayer, initialPlaybackTime)
		TITANIUM_PROPERTY_GETTER_OBJECT(VideoPlayer, media)
		TITANIUM_PROPERTY_SETTER_OBJECT(VideoPlayer, media, Titanium::Blob)
		TITANIUM_PROPERTY_GETTER_ENUM(VideoPlayer, mediaControlStyle)
		TITANIUM_PROPERTY_SETTER_ENUM(VideoPlayer, mediaControlStyle, VideoControlStyle)

		TITANIUM_PROPERTY_GETTER(VideoPlayer, mediaTypes)
		{
			return get_context().CreateNumber(Constants::to_underlying_type(get_mediaTypes()));
		}

		TITANIUM_PROPERTY_SETTER(VideoPlayer, mediaTypes)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_mediaTypes(Constants::to_VideoMediaType(static_cast<std::underlying_type<VideoMediaType>::type>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER_ENUM(VideoPlayer, movieControlMode)
		TITANIUM_PROPERTY_SETTER_ENUM(VideoPlayer, movieControlMode, VideoControlStyle)
		TITANIUM_PROPERTY_GETTER_STRUCT(VideoPlayer, naturalSize, Dimension)
		TITANIUM_PROPERTY_SETTER_STRUCT(VideoPlayer, naturalSize, Dimension)

		TITANIUM_PROPERTY_GETTER_BOOL(VideoPlayer, playing)
		TITANIUM_PROPERTY_GETTER_ENUM(VideoPlayer, repeatMode)
		TITANIUM_PROPERTY_SETTER_ENUM(VideoPlayer, repeatMode, VideoRepeatMode)
		TITANIUM_PROPERTY_GETTER_ENUM(VideoPlayer, scalingMode)
		TITANIUM_PROPERTY_SETTER_ENUM(VideoPlayer, scalingMode, VideoScaling)
		TITANIUM_PROPERTY_GETTER_ENUM(VideoPlayer, sourceType)
		TITANIUM_PROPERTY_SETTER_ENUM(VideoPlayer, sourceType, VideoSourceType)

		TITANIUM_PROPERTY_GETTER(VideoPlayer, url)
		{
			const auto ctx = get_context();
			const auto urls = get_urls();

			if (urls.size() == 0) {
				return ctx.CreateNull();
			} else if (urls.size() == 1) {
				return ctx.CreateString(urls.at(0));
			} else {
				std::vector<JSValue> js_urls;
				for (const auto v : urls) {
					js_urls.push_back(ctx.CreateString(v));
				}
				return ctx.CreateArray(js_urls);
			}
		}

		TITANIUM_PROPERTY_SETTER(VideoPlayer, url)
		{
			std::vector<std::string> urls;

			if (argument.IsString()) {
				urls.push_back(static_cast<std::string>(argument));
			} else if (argument.IsObject()) {
				const auto js_object = static_cast<JSObject>(argument);
				if (js_object.IsArray()) {
					const auto js_array = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_object));
					for (const auto v : js_array) {
						urls.push_back(static_cast<std::string>(v));
					}
				} else {
					TITANIUM_LOG_WARN("Could not convert VideoPlayer.url");
				}
			}

			set_urls(urls);

			return true;
		}

		TITANIUM_PROPERTY_GETTER_BOOL(VideoPlayer, useApplicationAudioSession)
		TITANIUM_PROPERTY_SETTER_BOOL(VideoPlayer, useApplicationAudioSession)
		TITANIUM_PROPERTY_GETTER_DOUBLE(VideoPlayer, volume)
		TITANIUM_PROPERTY_SETTER_DOUBLE(VideoPlayer, volume)
		TITANIUM_PROPERTY_GETTER_ENUM(VideoPlayer, loadState)
		TITANIUM_PROPERTY_GETTER_ENUM(VideoPlayer, playbackState)
		TITANIUM_PROPERTY_GETTER_TIME(VideoPlayer, playableDuration)

		TITANIUM_FUNCTION(VideoPlayer, cancelAllThumbnailImageRequests)
		{
			cancelAllThumbnailImageRequests();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(VideoPlayer, pause)
		{
			pause();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(VideoPlayer, play)
		{
			play();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(VideoPlayer, release)
		{
			release();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(VideoPlayer, requestThumbnailImagesAtTimes)
		{
			ENSURE_ARRAY_AT_INDEX(js_array, 0);
			ENSURE_UINT_AT_INDEX(option, 1);
			ENSURE_OBJECT_AT_INDEX(callback, 2);

			const auto js_times =static_cast<std::vector<JSValue>>(js_array);
			std::vector<std::chrono::seconds> times;

			for (const auto v : js_times) {
				times.push_back(std::chrono::seconds(static_cast<std::chrono::seconds::rep>(static_cast<std::uint32_t>(v))));
			}

			requestThumbnailImagesAtTimes(times, static_cast<VideoTimeOption>(option), callback);

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(VideoPlayer, setBackgroundView)
		{
			ENSURE_OBJECT_AT_INDEX(view, 0);
			setBackgroundView(view.GetPrivate<View>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(VideoPlayer, stop)
		{
			stop();
			return get_context().CreateUndefined();
		}
		TITANIUM_FUNCTION(VideoPlayer, thumbnailImageAtTime)
		{
			ENSURE_TIME_AT_INDEX(time, 0);
			ENSURE_UINT_AT_INDEX(option, 1);

			const auto blob = thumbnailImageAtTime(time, static_cast<VideoTimeOption>(option));
			if (blob != nullptr) {
				return blob->get_object();
			} else {
				return get_context().CreateNull();
			}
		}

		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getAllowsAirPlay, allowsAirPlay)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setAllowsAirPlay, allowsAirPlay)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getAutoplay, autoplay)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setAutoplay, autoplay)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getContentURL, contentURL)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setContentURL, contentURL)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getCurrentPlaybackTime, currentPlaybackTime)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setCurrentPlaybackTime, currentPlaybackTime)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getDuration, duration)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setDuration, duration)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getEndPlaybackTime, endPlaybackTime)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setEndPlaybackTime, endPlaybackTime)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getFullscreen, fullscreen)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setFullscreen, fullscreen)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getInitialPlaybackTime, initialPlaybackTime)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setInitialPlaybackTime, initialPlaybackTime)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getLoadState, loadState)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setMedia, media)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getMediaControlStyle, mediaControlStyle)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setMediaControlStyle, mediaControlStyle)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getMediaTypes, mediaTypes)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setMediaTypes, mediaTypes)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getMovieControlMode, movieControlMode)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setMovieControlMode, movieControlMode)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getNaturalSize, naturalSize)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setNaturalSize, naturalSize)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getPlayableDuration, playableDuration)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getPlaybackState, playbackState)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getPlaying, playing)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getRepeatMode, repeatMode)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setRepeatMode, repeatMode)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getScalingMode, scalingMode)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setScalingMode, scalingMode)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getSourceType, sourceType)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setSourceType, sourceType)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getUrl, url)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setUrl, url)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getUseApplicationAudioSession, useApplicationAudioSession)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setUseApplicationAudioSession, useApplicationAudioSession)
		TITANIUM_FUNCTION_AS_GETTER(VideoPlayer, getVolume, volume)
		TITANIUM_FUNCTION_AS_SETTER(VideoPlayer, setVolume, volume)

	} // namespace Media
} // namespace Titanium
