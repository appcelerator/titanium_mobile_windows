/**
 * TitaniumKit Titanium.Media constants
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_MEDIA_CONSTANTS_HPP_
#define _TITANIUM_MEDIA_CONSTANTS_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	using namespace HAL;

	namespace Media
	{
		
		enum class AudioFileFormat
		{
			ThreeGP2,
			ThreeGPP,
			Aiff,
			Amr,
			Caf,
			Mp3,
			Mp4,
			Mp4a,
			Wave
		};
		
		enum class AudioFormat
		{
			Aac,
			Alaw,
			AppleLossless,
			Ilbc,
			Ima4,
			LinearPCM,
			Ulaw
		};

		enum class AudioSessionCategory 
		{
			Ambient,
			Playback,
			PlayAndRecord,
			Record,
			SoloAmbient
		};
		
		enum class AudioSessionOverrideRoute
		{
			None,
			Speaker
		};
		
		enum class AudioSessionPort
		{
			Airplay,
			BluetoothA2DP,
			BluetoothHFP,
			BluetoothLE,
			BuiltinMic,
			BuiltinReceiver,
			BuiltinSpeaker,
			CarAudio,
			Hdmi,
			HeadPhones,
			HeadSetMic,
			LineIn,
			LineOut,
			USBAudio
		};
		
		enum class CameraOption
		{
			Authorized,
			Denied,
			NotDetermined,
			Restricted,
			Front,
			Rear,
			FlashAuto,
			FlashOff,
			FlashOn
		};

		enum class State
		{
			DeviceBusy,
			NoCamera,
			NoVideo
		};

		enum class MediaType 
		{
			Photo,
			Video
		};
		
		enum class MusicMediaGroup
		{
			Album,
			AlbumArtist,
			Artist,
			Composer,
			Genre,
			Playlist,
			PodcastTitle,
			Title
		};

		enum class MusicMediaType
		{
			All       = 1 << 0,  // 1 << 0 == 1,
			AnyAudio  = 1 << 1,  // 1 << 0 == 2,
			AudioBook = 1 << 2,  // 1 << 0 == 4,
			Music     = 1 << 3,  // 1 << 0 == 8,
			Podcast   = 1 << 4,  // 1 << 0 == 16
		};
		
		enum class MusicPlayerRepeat
		{
			All,
			Default,
			None,
			One
		};
		
		enum class MusicPlayerShuffle
		{
			Albums,
			Default,
			None,
			Songs
		};
		
		enum class MusicPlayerState
		{
			Interrupted,
			Paused,
			Playing,
			SeekBackward,
			SeekForward,
			Stopped
		};
		
		enum class Quality
		{
			High,
			Low,
			Medium
		};
		
		enum class Error
		{
			Unknown
		};
		
		enum class VideoControlStyle
		{
			Default,
			Embedded,
			Fullscreen,
			Hidden,
			None,
			VolumeOnly
		};
		
		enum class VideoFinishReason
		{
			PlaybackEnded,
			PlaybackError,
			UserExited
		};
		
		enum class VideoLoadState
		{
			Playable,
			PlaythroughOK,
			Stalled,
			Unknown
		};
		
		enum class VideoMediaType
		{
			Audio  = 1 << 0,  // 1 << 0 == 1,
			None   = 1 << 1,  // 1 << 1 == 2,
			Video  = 1 << 2   // 1 << 2 == 4
		};
		
		enum class VideoPlaybackState
		{
			Interrupted,
			Paused,
			Playing,
			SeekingBackward,
			SeekingForward,
			Stopped
		};
		
		enum class VideoRepeatMode
		{
			None,
			One
		};
		
		enum class VideoScaling
		{
			AspectFill,
			AspectFit,
			ModeFill,
			None,
			Resize,
			ResizeAspect,
			ResizeAspectFill
		};
		
		enum class VideoSourceType
		{
			File,
			Streaming,
			Unknown
		};
		
		enum class VideoTimeOption
		{
			ClosestSync,
			Exact,
			NearestKeyframe,
			NextSync,
			PreviousSync
		};

		enum class AudioState
		{
			Buffering,
			Initialized,
			Paused,
			Playing,
			Starting,
			Stopped,
			Stopping,
			WaitingForData,
			WaitingForQueue
		};

		enum class RecordingState
		{
			Paused,
			Recording,
			Stopped
		};

		class TITANIUMKIT_EXPORT Constants final
		{
		public:
			static std::unordered_set<VideoMediaType> to_VideoMediaType(std::underlying_type<VideoMediaType>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<VideoMediaType>::type to_underlying_type(const std::unordered_set<VideoMediaType>&) TITANIUM_NOEXCEPT;
			static std::underlying_type<VideoMediaType>::type to_underlying_type(const VideoMediaType&) TITANIUM_NOEXCEPT;

			static std::unordered_set<MusicMediaType> to_MusicMediaType(std::underlying_type<MusicMediaType>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<MusicMediaType>::type to_underlying_type(const std::unordered_set<MusicMediaType>&) TITANIUM_NOEXCEPT;
			static std::underlying_type<MusicMediaType>::type to_underlying_type(const MusicMediaType&) TITANIUM_NOEXCEPT;

			static std::string to_string(const VideoScaling&) TITANIUM_NOEXCEPT;

		};


	} // namespace Media
} // namespace Titanium

// Provide a hash function so that a Media types can be stored in an
// unordered container.
namespace std
{
	template <>
	struct hash<Titanium::Media::VideoMediaType>
	{
		using argument_type = Titanium::Media::VideoMediaType;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Media::MusicMediaType>
	{
		using argument_type = Titanium::Media::MusicMediaType;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};
	
}



#endif // _TITANIUM_MEDIA_CONSTANTS_HPP_