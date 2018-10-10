/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_MEDIA_VIDEOPLAYER_HPP_
#define _TITANIUMWINDOWS_MEDIA_VIDEOPLAYER_HPP_

#include "TitaniumWindows_Media_EXPORT.h"
#include "Titanium/Media/VideoPlayer.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	namespace Media
	{
		/*!
	      @class VideoPlayer
	      @ingroup Titanium.Media.VideoPlayer

	      @discussion This is the Titanium.Media.VideoPlayer implementation for Windows.
	    */
		class TITANIUMWINDOWS_MEDIA_EXPORT VideoPlayer final : public Titanium::Media::VideoPlayer, public JSExport<VideoPlayer>
		{
		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(allowsAirPlay);
			TITANIUM_PROPERTY_UNIMPLEMENTED(contentURL);
			TITANIUM_PROPERTY_UNIMPLEMENTED(fullscreen);
			TITANIUM_PROPERTY_UNIMPLEMENTED(initialPlaybackTime);
			TITANIUM_PROPERTY_UNIMPLEMENTED(loadState);
			TITANIUM_PROPERTY_UNIMPLEMENTED(media);
			TITANIUM_PROPERTY_UNIMPLEMENTED(mediaControlStyle);
			TITANIUM_PROPERTY_UNIMPLEMENTED(mediaTypes);
			TITANIUM_PROPERTY_UNIMPLEMENTED(movieControlMode);
			TITANIUM_PROPERTY_UNIMPLEMENTED(naturalSize);
			TITANIUM_PROPERTY_UNIMPLEMENTED(scalingMode);
			TITANIUM_PROPERTY_UNIMPLEMENTED(sourceType);
			TITANIUM_PROPERTY_UNIMPLEMENTED(useApplicationAudioSession);
			TITANIUM_FUNCTION_UNIMPLEMENTED(cancelAllThumbnailImageRequests);
			TITANIUM_FUNCTION_UNIMPLEMENTED(release);
			TITANIUM_FUNCTION_UNIMPLEMENTED(requestThumbnailImagesAtTimes);
			TITANIUM_FUNCTION_UNIMPLEMENTED(setBackgroundView);
			TITANIUM_FUNCTION_UNIMPLEMENTED(thumbnailImageAtTime);

			virtual void pause() TITANIUM_NOEXCEPT override;
			virtual void play() TITANIUM_NOEXCEPT override;
			virtual void stop() TITANIUM_NOEXCEPT override;
			virtual void set_urls(const std::vector<std::string>& urls) TITANIUM_NOEXCEPT override;
			virtual void set_volume(const double& volume) TITANIUM_NOEXCEPT override;
			virtual void set_autoplay(const bool& autoplay) TITANIUM_NOEXCEPT override;
			virtual std::chrono::milliseconds get_duration() const TITANIUM_NOEXCEPT override;
			virtual std::chrono::milliseconds get_endPlaybackTime() const TITANIUM_NOEXCEPT override;
			virtual std::chrono::milliseconds get_currentPlaybackTime() const TITANIUM_NOEXCEPT override;
			virtual std::chrono::milliseconds get_playableDuration() const TITANIUM_NOEXCEPT override;

			VideoPlayer(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~VideoPlayer();
			VideoPlayer(const VideoPlayer&) = default;
			VideoPlayer& operator=(const VideoPlayer&) = default;
	#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			VideoPlayer(VideoPlayer&&) = default;
			VideoPlayer& operator=(VideoPlayer&&) = default;
	#endif

			static void JSExportInitialize();
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

		protected:
			Windows::UI::Xaml::Controls::MediaElement ^ player__;
			Windows::Foundation::EventRegistrationToken complete_event__;
			Windows::Foundation::EventRegistrationToken failed_event__;
		};

	} // namespace Media
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_MEDIA_VIDEOPLAYER_HPP_
