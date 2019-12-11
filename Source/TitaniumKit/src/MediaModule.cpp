/**
 * TitaniumKit Titanium.Media
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/MediaModule.hpp"
#include "Titanium/Filesystem/File.hpp"
#include "Titanium/Media/Item.hpp"
#include "Titanium/Media/MusicLibraryOptionsType.hpp"
#include "Titanium/Media/PhotoGalleryOptionsType.hpp"
#include "Titanium/Media/MediaQueryType.hpp"
#include "Titanium/Media/CameraOptionsType.hpp"
#include "Titanium/Media/PreviewImageOptions.hpp"
#include "Titanium/detail/TiImpl.hpp"

#define CREATE_TITANIUM_MEDIA(NAME) \
  static auto NAME##_ctor = this_object; \
  static std::once_flag of; \
  std::call_once(of, [=] {\
  JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue Media_property = Titanium.GetProperty("Media"); \
  TITANIUM_ASSERT(Media_property.IsObject()); \
  JSObject Media = static_cast<JSObject>(Media_property); \
  JSValue NAME##_property = Media.GetProperty(#NAME); \
  TITANIUM_ASSERT(NAME##_property.IsObject()); \
  NAME##_ctor = static_cast<JSObject>(NAME##_property); \
  }); \
  auto NAME##_obj = NAME##_ctor.CallAsConstructor(); \
  Titanium::Module::applyProperties(parameters, NAME##_obj); \
  return NAME##_obj;


namespace Titanium
{

	MediaModule::MediaModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Module(js_context, "Ti.Media")
		, appMusicPlayer__(get_context().CreateNull())
		, audioPlaying__(false)
		, audioSessionCategory__(Media::AudioSessionCategory::Playback)
		, averageMicrophonePower__(0)
		, cameraFlashMode__(Media::CameraOption::FlashAuto)
		, canRecord__(false)
		, isCameraSupported__(false)
		, peakMicrophonePower__(0)
		, systemMusicPlayer__(get_context().CreateNull())
		, volume__(0)
	{
	}

	TITANIUM_PROPERTY_READ(MediaModule, bool, audioPlaying)
	TITANIUM_PROPERTY_READWRITE(MediaModule, Media::AudioSessionCategory, audioSessionCategory)
	TITANIUM_PROPERTY_READ(MediaModule, std::vector<Media::CameraOption>, availableCameras)
	TITANIUM_PROPERTY_READWRITE(MediaModule, std::vector<Media::MediaType>, availableCameraMediaTypes)
	TITANIUM_PROPERTY_READWRITE(MediaModule, std::vector<Media::MediaType>, availablePhotoGalleryMediaTypes)
	TITANIUM_PROPERTY_READWRITE(MediaModule, std::vector<Media::MediaType>, availablePhotoMediaTypes)
	TITANIUM_PROPERTY_READWRITE(MediaModule, double, averageMicrophonePower)
	TITANIUM_PROPERTY_READ(MediaModule, double, peakMicrophonePower)
	TITANIUM_PROPERTY_READWRITE(MediaModule, Media::CameraOption, cameraFlashMode)
	TITANIUM_PROPERTY_READ(MediaModule, bool, canRecord)
	TITANIUM_PROPERTY_READ(MediaModule, Media::RouteDescription, currentRoute)
	TITANIUM_PROPERTY_READ(MediaModule, bool, isCameraSupported)
	TITANIUM_PROPERTY_READ(MediaModule, double, volume)

	void MediaModule::beep() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::beep: Unimplemented");
	}

	void MediaModule::hideCamera() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::hideCamera: Unimplemented");
	}

	void MediaModule::hideMusicLibrary() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::hideMusicLibrary: Unimplemented");
	}

	bool MediaModule::isMediaTypeSupported(const std::string& source, const Media::MediaType& type) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::isMediaTypeSupported: Unimplemented");
		return false;
	}

	void MediaModule::openMusicLibrary(const Media::MusicLibraryOptionsType& options) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::openMusicLibrary: Unimplemented");
	}

	void MediaModule::openPhotoGallery(const Media::PhotoGalleryOptionsType& options) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::openPhotoGallery: Unimplemented");
	}

	void MediaModule::previewImage(const std::unordered_map<std::string, Media::PreviewImageOptions>& options) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::previewImage: Unimplemented");
	}

	void MediaModule::saveToPhotoGallery(const std::shared_ptr<Titanium::Blob>& blob, JSValue callbacks) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::saveToPhotoGallery: Unimplemented");
	}

	void MediaModule::saveToPhotoGallery(const std::shared_ptr<Titanium::Filesystem::File>& file, JSValue callbacks) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::saveToPhotoGallery: Unimplemented");
	}

	void MediaModule::setOverrideAudioRoute(const Media::AudioSessionOverrideRoute& route) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::setOverrideAudioRoute: Unimplemented");
	}

	void MediaModule::showCamera(const Media::CameraOptionsType& options) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::showCamera: Unimplemented");
	}

	std::vector<std::shared_ptr<Media::Item>> MediaModule::queryMusicLibrary(const Media::MediaQueryType& query) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::queryMusicLibrary: Unimplemented");
		return std::vector<std::shared_ptr<Media::Item>>();
	}

	void MediaModule::startMicrophoneMonitor() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::startMicrophoneMonitor: Unimplemented");
	}

	void MediaModule::stopMicrophoneMonitor() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::stopMicrophoneMonitor: Unimplemented");
	}

	void MediaModule::takePicture() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::takePicture: Unimplemented");
	}

	void MediaModule::startVideoCapture() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::startVideoCapture: Unimplemented");
	}

	void MediaModule::stopVideoCapture() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::stopVideoCapture: Unimplemented");
	}

	void MediaModule::switchCamera(const Media::CameraOption& camera) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::switchCamera: Unimplemented");
	}

	void MediaModule::takeScreenshot(JSValue callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::takeScreenshot: Unimplemented");
	}

	void MediaModule::vibrate(std::vector<std::chrono::milliseconds> pattern) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::vibrate: Unimplemented");
	}

	void MediaModule::requestAuthorization(JSValue callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::requestAuthorization: Unimplemented");
	}

	bool MediaModule::hasCameraPermissions() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::hasCameraPermissions: Unimplemented");
		return false;
	}

	void MediaModule::requestCameraPermissions(JSValue callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("MediaModule::requestCameraPermissions: Unimplemented");
	}

	void MediaModule::JSExportInitialize()
	{
		JSExport<MediaModule>::SetClassVersion(1);
		JSExport<MediaModule>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AudioPlayer);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AudioRecorder);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, Item);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MusicPlayer);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, Sound);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VideoPlayer);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FILEFORMAT_3GP2);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FILEFORMAT_3GPP);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FILEFORMAT_AIFF);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FILEFORMAT_AMR);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FILEFORMAT_CAF);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FILEFORMAT_MP3);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FILEFORMAT_MP4);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FILEFORMAT_MP4A);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FILEFORMAT_WAVE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FORMAT_AAC);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FORMAT_ALAW);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FORMAT_APPLE_LOSSLESS);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FORMAT_ILBC);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FORMAT_IMA4);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FORMAT_LINEAR_PCM);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_FORMAT_ULAW);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_CATEGORY_AMBIENT);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_CATEGORY_PLAYBACK);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_CATEGORY_PLAY_AND_RECORD);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_CATEGORY_RECORD);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_CATEGORY_SOLO_AMBIENT);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_OVERRIDE_ROUTE_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_OVERRIDE_ROUTE_SPEAKER);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_LINEIN);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_BUILTINMIC);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_HEADSETMIC);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_LINEOUT);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_HEADPHONES);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_BLUETOOTHA2DP);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_BUILTINRECEIVER);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_BUILTINSPEAKER);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_HDMI);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_AIRPLAY);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_BLUETOOTHHFP);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_USBAUDIO);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_BLUETOOTHLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, AUDIO_SESSION_PORT_CARAUDIO);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, CAMERA_FLASH_AUTO);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, CAMERA_FLASH_OFF);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, CAMERA_FLASH_ON);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, CAMERA_FRONT);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, CAMERA_REAR);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, DEVICE_BUSY);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MEDIA_TYPE_PHOTO);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MEDIA_TYPE_VIDEO);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_TYPE_ALL);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_TYPE_ANY_AUDIO);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_TYPE_AUDIOBOOK);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_TYPE_MUSIC);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_TYPE_PODCAST);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_GROUP_TITLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_GROUP_ALBUM);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_GROUP_ARTIST);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_GROUP_ALBUM_ARTIST);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_GROUP_COMPOSER);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_GROUP_GENRE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_GROUP_PLAYLIST);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_MEDIA_GROUP_PODCAST_TITLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_REPEAT_ALL);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_REPEAT_DEFAULT);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_REPEAT_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_REPEAT_ONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_SHUFFLE_ALBUMS);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_SHUFFLE_DEFAULT);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_SHUFFLE_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_SHUFFLE_SONGS);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_STATE_INTERRUPTED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_STATE_PAUSED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_STATE_PLAYING);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_STATE_SEEK_BACKWARD);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_STATE_SEEK_FORWARD);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, MUSIC_PLAYER_STATE_STOPPED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, NO_CAMERA);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, NO_VIDEO);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, QUALITY_HIGH);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, QUALITY_LOW);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, QUALITY_MEDIUM);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, UNKNOWN_ERROR);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_CONTROL_DEFAULT);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_CONTROL_EMBEDDED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_CONTROL_FULLSCREEN);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_CONTROL_HIDDEN);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_CONTROL_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_FINISH_REASON_PLAYBACK_ENDED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_FINISH_REASON_PLAYBACK_ERROR);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_FINISH_REASON_USER_EXITED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_LOAD_STATE_PLAYABLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_LOAD_STATE_PLAYTHROUGH_OK);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_LOAD_STATE_STALLED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_LOAD_STATE_UNKNOWN);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_MEDIA_TYPE_AUDIO);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_MEDIA_TYPE_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_MEDIA_TYPE_VIDEO);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_PLAYBACK_STATE_INTERRUPTED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_PLAYBACK_STATE_PAUSED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_PLAYBACK_STATE_PLAYING);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_PLAYBACK_STATE_SEEKING_BACKWARD);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_PLAYBACK_STATE_SEEKING_FORWARD);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_PLAYBACK_STATE_STOPPED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_REPEAT_MODE_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_REPEAT_MODE_ONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_SCALING_ASPECT_FILL);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_SCALING_ASPECT_FIT);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_SCALING_MODE_FILL);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_SCALING_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_SCALING_RESIZE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_SCALING_RESIZE_ASPECT);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_SCALING_RESIZE_ASPECT_FILL);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_SOURCE_TYPE_FILE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_SOURCE_TYPE_STREAMING);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_SOURCE_TYPE_UNKNOWN);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_TIME_OPTION_EXACT);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_TIME_OPTION_NEAREST_KEYFRAME);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_TIME_OPTION_CLOSEST_SYNC);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_TIME_OPTION_NEXT_SYNC);
		TITANIUM_ADD_CONSTANT_PROPERTY(MediaModule, VIDEO_TIME_OPTION_PREVIOUS_SYNC);
		TITANIUM_ADD_PROPERTY_READONLY(MediaModule, appMusicPlayer);
		TITANIUM_ADD_PROPERTY_READONLY(MediaModule, audioPlaying);
		TITANIUM_ADD_PROPERTY(MediaModule, audioSessionCategory);
		TITANIUM_ADD_PROPERTY_READONLY(MediaModule, availableCameras);
		TITANIUM_ADD_PROPERTY(MediaModule, availableCameraMediaTypes);
		TITANIUM_ADD_PROPERTY(MediaModule, availablePhotoGalleryMediaTypes);
		TITANIUM_ADD_PROPERTY(MediaModule, availablePhotoMediaTypes);
		TITANIUM_ADD_PROPERTY(MediaModule, averageMicrophonePower);
		TITANIUM_ADD_PROPERTY(MediaModule, cameraFlashMode);
		TITANIUM_ADD_PROPERTY_READONLY(MediaModule, canRecord);
		TITANIUM_ADD_PROPERTY_READONLY(MediaModule, currentRoute);
		TITANIUM_ADD_PROPERTY_READONLY(MediaModule, isCameraSupported);
		TITANIUM_ADD_PROPERTY_READONLY(MediaModule, peakMicrophonePower);
		TITANIUM_ADD_PROPERTY_READONLY(MediaModule, systemMusicPlayer);
		TITANIUM_ADD_PROPERTY_READONLY(MediaModule, volume);

		TITANIUM_ADD_FUNCTION(MediaModule, beep);
		TITANIUM_ADD_FUNCTION(MediaModule, hideCamera);
		TITANIUM_ADD_FUNCTION(MediaModule, hideMusicLibrary);
		TITANIUM_ADD_FUNCTION(MediaModule, isMediaTypeSupported);
		TITANIUM_ADD_FUNCTION(MediaModule, openMusicLibrary);
		TITANIUM_ADD_FUNCTION(MediaModule, openPhotoGallery);
		TITANIUM_ADD_FUNCTION(MediaModule, previewImage);
		TITANIUM_ADD_FUNCTION(MediaModule, saveToPhotoGallery);
		TITANIUM_ADD_FUNCTION(MediaModule, setOverrideAudioRoute);
		TITANIUM_ADD_FUNCTION(MediaModule, showCamera);
		TITANIUM_ADD_FUNCTION(MediaModule, queryMusicLibrary);
		TITANIUM_ADD_FUNCTION(MediaModule, startMicrophoneMonitor);
		TITANIUM_ADD_FUNCTION(MediaModule, stopMicrophoneMonitor);
		TITANIUM_ADD_FUNCTION(MediaModule, takePicture);
		TITANIUM_ADD_FUNCTION(MediaModule, startVideoCapture);
		TITANIUM_ADD_FUNCTION(MediaModule, stopVideoCapture);
		TITANIUM_ADD_FUNCTION(MediaModule, switchCamera);
		TITANIUM_ADD_FUNCTION(MediaModule, takeScreenshot);
		TITANIUM_ADD_FUNCTION(MediaModule, vibrate);
		TITANIUM_ADD_FUNCTION(MediaModule, requestAuthorization);
		TITANIUM_ADD_FUNCTION(MediaModule, requestAudioRecorderPermissions);
		TITANIUM_ADD_FUNCTION(MediaModule, hasCameraPermissions);
		TITANIUM_ADD_FUNCTION(MediaModule, requestCameraPermissions);
		TITANIUM_ADD_FUNCTION(MediaModule, createAudioPlayer);
		TITANIUM_ADD_FUNCTION(MediaModule, createAudioRecorder);
		TITANIUM_ADD_FUNCTION(MediaModule, createSound);
		TITANIUM_ADD_FUNCTION(MediaModule, createVideoPlayer);
		TITANIUM_ADD_FUNCTION(MediaModule, getAppMusicPlayer);
		TITANIUM_ADD_FUNCTION(MediaModule, getAudioPlaying);
		TITANIUM_ADD_FUNCTION(MediaModule, getAudioSessionCategory);
		TITANIUM_ADD_FUNCTION(MediaModule, setAudioSessionCategory);
		TITANIUM_ADD_FUNCTION(MediaModule, getAvailableCameras);
		TITANIUM_ADD_FUNCTION(MediaModule, getAvailableCameraMediaTypes);
		TITANIUM_ADD_FUNCTION(MediaModule, setAvailableCameraMediaTypes);
		TITANIUM_ADD_FUNCTION(MediaModule, getAvailablePhotoGalleryMediaTypes);
		TITANIUM_ADD_FUNCTION(MediaModule, setAvailablePhotoGalleryMediaTypes);
		TITANIUM_ADD_FUNCTION(MediaModule, getAvailablePhotoMediaTypes);
		TITANIUM_ADD_FUNCTION(MediaModule, setAvailablePhotoMediaTypes);
		TITANIUM_ADD_FUNCTION(MediaModule, getAverageMicrophonePower);
		TITANIUM_ADD_FUNCTION(MediaModule, setAverageMicrophonePower);
		TITANIUM_ADD_FUNCTION(MediaModule, getCameraFlashMode);
		TITANIUM_ADD_FUNCTION(MediaModule, setCameraFlashMode);
		TITANIUM_ADD_FUNCTION(MediaModule, getCanRecord);
		TITANIUM_ADD_FUNCTION(MediaModule, getCurrentRoute);
		TITANIUM_ADD_FUNCTION(MediaModule, getIsCameraSupported);
		TITANIUM_ADD_FUNCTION(MediaModule, getPeakMicrophonePower);
		TITANIUM_ADD_FUNCTION(MediaModule, getSystemMusicPlayer);
		TITANIUM_ADD_FUNCTION(MediaModule, getVolume);
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FILEFORMAT_3GP2)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFileFormat::ThreeGP2));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FILEFORMAT_3GPP)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFileFormat::ThreeGPP));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FILEFORMAT_AIFF)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFileFormat::Aiff));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FILEFORMAT_AMR)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFileFormat::Amr));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FILEFORMAT_CAF)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFileFormat::Caf));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FILEFORMAT_MP3)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFileFormat::Mp3));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FILEFORMAT_MP4)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFileFormat::Mp4));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FILEFORMAT_MP4A)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFileFormat::Mp4a));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FILEFORMAT_WAVE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFileFormat::Wave));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FORMAT_AAC)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFormat::Aac));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FORMAT_ALAW)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFormat::Alaw));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FORMAT_APPLE_LOSSLESS)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFormat::AppleLossless));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FORMAT_ILBC)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFormat::Ilbc));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FORMAT_IMA4)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFormat::Ima4));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_FORMAT_LINEAR_PCM)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFormat::LinearPCM));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule,  AUDIO_FORMAT_ULAW)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioFormat::Ulaw));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_CATEGORY_AMBIENT)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionCategory::Ambient));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_CATEGORY_PLAYBACK)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionCategory::Playback));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_CATEGORY_PLAY_AND_RECORD)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionCategory::PlayAndRecord));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_CATEGORY_RECORD)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionCategory::Record));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_CATEGORY_SOLO_AMBIENT)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionCategory::SoloAmbient));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_OVERRIDE_ROUTE_NONE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionOverrideRoute::None));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_OVERRIDE_ROUTE_SPEAKER)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionOverrideRoute::Speaker));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_LINEIN)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::LineIn));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_BUILTINMIC)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::BuiltinMic));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_HEADSETMIC)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::HeadSetMic));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_LINEOUT)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::LineOut));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_HEADPHONES)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::HeadPhones));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_BLUETOOTHA2DP)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::BluetoothA2DP));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_BUILTINRECEIVER)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::BuiltinReceiver));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_BUILTINSPEAKER)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::BuiltinSpeaker));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_HDMI)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::Hdmi));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_AIRPLAY)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::Airplay));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_BLUETOOTHHFP)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::BluetoothHFP));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_USBAUDIO)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::USBAudio));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_BLUETOOTHLE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::BluetoothLE));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AUDIO_SESSION_PORT_CARAUDIO)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::AudioSessionPort::CarAudio));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, CAMERA_FLASH_AUTO)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::CameraOption::FlashAuto));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, CAMERA_FLASH_OFF)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::CameraOption::FlashOff));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, CAMERA_FLASH_ON)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::CameraOption::FlashOn));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, CAMERA_FRONT)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::CameraOption::Front));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, CAMERA_REAR)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::CameraOption::Rear));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, DEVICE_BUSY)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::State::DeviceBusy));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MEDIA_TYPE_PHOTO)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MediaType::Photo));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MEDIA_TYPE_VIDEO)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MediaType::Video));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_TYPE_ALL)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaType::All));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_TYPE_ANY_AUDIO)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaType::AnyAudio));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_TYPE_AUDIOBOOK)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaType::AudioBook));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_TYPE_MUSIC)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaType::Music));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_TYPE_PODCAST)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaType::Podcast));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_GROUP_TITLE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaGroup::Title));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_GROUP_ALBUM)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaGroup::Album));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_GROUP_ARTIST)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaGroup::Artist));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_GROUP_ALBUM_ARTIST)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaGroup::AlbumArtist));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_GROUP_COMPOSER)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaGroup::Composer));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_GROUP_GENRE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaGroup::Genre));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_GROUP_PLAYLIST)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaGroup::Playlist));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_MEDIA_GROUP_PODCAST_TITLE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicMediaGroup::PodcastTitle));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_REPEAT_ALL)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerRepeat::All));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_REPEAT_DEFAULT)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerRepeat::Default));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_REPEAT_NONE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerRepeat::None));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_REPEAT_ONE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerRepeat::One));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_SHUFFLE_ALBUMS)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerShuffle::Albums));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_SHUFFLE_DEFAULT)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerShuffle::Default));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_SHUFFLE_NONE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerShuffle::None));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_SHUFFLE_SONGS)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerShuffle::Songs));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_STATE_INTERRUPTED)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerState::Interrupted));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_STATE_PAUSED)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerState::Paused));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_STATE_PLAYING)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerState::Playing));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_STATE_SEEK_BACKWARD)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerState::SeekBackward));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_STATE_SEEK_FORWARD)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerState::SeekForward));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MUSIC_PLAYER_STATE_STOPPED)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::MusicPlayerState::Stopped));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, NO_CAMERA)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::State::NoCamera));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, NO_VIDEO)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::State::NoVideo));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, QUALITY_HIGH)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::Quality::High));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, QUALITY_LOW)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::Quality::Low));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, QUALITY_MEDIUM)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::Quality::Medium));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, UNKNOWN_ERROR)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::Error::Unknown));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_CONTROL_DEFAULT)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoControlStyle::Default));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_CONTROL_EMBEDDED)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoControlStyle::Embedded));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_CONTROL_FULLSCREEN)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoControlStyle::Fullscreen));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_CONTROL_HIDDEN)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoControlStyle::Hidden));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_CONTROL_NONE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoControlStyle::None));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_FINISH_REASON_PLAYBACK_ENDED)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoFinishReason::PlaybackEnded));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_FINISH_REASON_PLAYBACK_ERROR)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoFinishReason::PlaybackError));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_FINISH_REASON_USER_EXITED)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoFinishReason::UserExited));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_LOAD_STATE_PLAYABLE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoLoadState::Playable));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_LOAD_STATE_PLAYTHROUGH_OK)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoLoadState::PlaythroughOK));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_LOAD_STATE_STALLED)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoLoadState::Stalled));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_LOAD_STATE_UNKNOWN)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoLoadState::Unknown));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_MEDIA_TYPE_AUDIO)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoMediaType::Audio));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_MEDIA_TYPE_NONE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoMediaType::None));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_MEDIA_TYPE_VIDEO)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoMediaType::Video));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_PLAYBACK_STATE_INTERRUPTED)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoPlaybackState::Interrupted));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_PLAYBACK_STATE_PAUSED)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoPlaybackState::Paused));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_PLAYBACK_STATE_PLAYING)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoPlaybackState::Playing));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_PLAYBACK_STATE_SEEKING_BACKWARD)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoPlaybackState::SeekingBackward));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_PLAYBACK_STATE_SEEKING_FORWARD)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoPlaybackState::SeekingForward));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_PLAYBACK_STATE_STOPPED)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoPlaybackState::Stopped));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_REPEAT_MODE_NONE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoRepeatMode::None));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_REPEAT_MODE_ONE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoRepeatMode::One));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_SCALING_ASPECT_FILL)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoScaling::AspectFill));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_SCALING_ASPECT_FIT)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoScaling::AspectFit));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_SCALING_MODE_FILL)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoScaling::ModeFill));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_SCALING_NONE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoScaling::None));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_SCALING_RESIZE)
	{
		return get_context().CreateString(Media::Constants::to_string(Media::VideoScaling::Resize));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_SCALING_RESIZE_ASPECT)
	{
		return get_context().CreateString(Media::Constants::to_string(Media::VideoScaling::ResizeAspect));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_SCALING_RESIZE_ASPECT_FILL)
	{
		return get_context().CreateString(Media::Constants::to_string(Media::VideoScaling::ResizeAspectFill));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_SOURCE_TYPE_FILE)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoSourceType::File));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_SOURCE_TYPE_STREAMING)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoSourceType::Streaming));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_SOURCE_TYPE_UNKNOWN)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoSourceType::Unknown));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_TIME_OPTION_EXACT)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoTimeOption::Exact));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_TIME_OPTION_NEAREST_KEYFRAME)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoTimeOption::NearestKeyframe));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_TIME_OPTION_CLOSEST_SYNC)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoTimeOption::ClosestSync));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_TIME_OPTION_NEXT_SYNC)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoTimeOption::NextSync));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VIDEO_TIME_OPTION_PREVIOUS_SYNC)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(Media::VideoTimeOption::PreviousSync));
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AudioPlayer)
	{
		return get_context().CreateObject(audioPlayer__);
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, AudioRecorder)
	{
		return get_context().CreateObject(audioRecorder__);
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, Item)
	{
		return get_context().CreateObject(item__);
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, MusicPlayer)
	{
		return get_context().CreateObject(musicPlayer__);
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, Sound)
	{
		return get_context().CreateObject(sound__);
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, VideoPlayer)
	{
		return get_context().CreateObject(videoPlayer__);
	}

	MediaModule& MediaModule::AudioPlayerClass(const JSClass& player) TITANIUM_NOEXCEPT
	{
		audioPlayer__ = player;
		return *this;
	}

	MediaModule& MediaModule::AudioRecorderClass(const JSClass& recorder) TITANIUM_NOEXCEPT
	{
		audioRecorder__ = recorder;
		return *this;
	}

	MediaModule& MediaModule::ItemClass(const JSClass& item) TITANIUM_NOEXCEPT
	{
		item__ = item;
		return *this;
	}

	MediaModule& MediaModule::MusicPlayerClass(const JSClass& player) TITANIUM_NOEXCEPT
	{
		musicPlayer__ = player;
		return *this;
	}

	MediaModule& MediaModule::SoundClass(const JSClass& sound) TITANIUM_NOEXCEPT
	{
		sound__ = sound;
		return *this;
	}

	MediaModule& MediaModule::VideoPlayerClass(const JSClass& player) TITANIUM_NOEXCEPT
	{
		videoPlayer__ = player;
		return *this;
	}
	TITANIUM_PROPERTY_GETTER(MediaModule, appMusicPlayer)
	{
		return appMusicPlayer__;
	}

	TITANIUM_PROPERTY_GETTER_BOOL(MediaModule, audioPlaying)
	TITANIUM_PROPERTY_GETTER_ENUM(MediaModule, audioSessionCategory)
	TITANIUM_PROPERTY_SETTER_ENUM(MediaModule, audioSessionCategory, Media::AudioSessionCategory)

	TITANIUM_PROPERTY_GETTER(MediaModule, availableCameras)
	{
		const auto ctx = get_context();
		std::vector<JSValue> values;
		for (auto v : availableCameras__) {
			values.push_back(ctx.CreateNumber(static_cast<std::uint32_t>(v)));
		}
		return ctx.CreateArray(values);
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, availableCameraMediaTypes)
	{
		const auto ctx = get_context();
		std::vector<JSValue> values;
		for (auto v : availableCameraMediaTypes__) {
			values.push_back(ctx.CreateNumber(static_cast<std::uint32_t>(v)));
		}
		return ctx.CreateArray(values);
	}

	TITANIUM_PROPERTY_SETTER(MediaModule, availableCameraMediaTypes)
	{
		ENSURE_ARRAY(argument, js_array);

		std::vector<Media::MediaType> types;
		const auto js_types = static_cast<std::vector<JSValue>>(js_array);
		for (const auto v : js_types) {
			types.push_back(static_cast<Media::MediaType>(static_cast<std::uint32_t>(v)));
		}
		set_availableCameraMediaTypes(types);
		return true;
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, availablePhotoGalleryMediaTypes)
	{
		const auto ctx = get_context();
		std::vector<JSValue> values;
		for (auto v : availablePhotoGalleryMediaTypes__) {
			values.push_back(ctx.CreateNumber(static_cast<std::uint32_t>(v)));
		}
		return ctx.CreateArray(values);
	}

	TITANIUM_PROPERTY_SETTER(MediaModule, availablePhotoGalleryMediaTypes)
	{
		ENSURE_ARRAY(argument, js_array);

		std::vector<Media::MediaType> types;
		const auto js_types = static_cast<std::vector<JSValue>>(js_array);
		for (const auto v : js_types) {
			types.push_back(static_cast<Media::MediaType>(static_cast<std::uint32_t>(v)));
		}
		set_availablePhotoGalleryMediaTypes(types);
		return true;
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, availablePhotoMediaTypes)
	{
		const auto ctx = get_context();
		std::vector<JSValue> values;
		for (auto v : availablePhotoMediaTypes__) {
			values.push_back(ctx.CreateNumber(static_cast<std::uint32_t>(v)));
		}
		return ctx.CreateArray(values);
	}

	TITANIUM_PROPERTY_SETTER(MediaModule, availablePhotoMediaTypes)
	{
		ENSURE_ARRAY(argument, js_array);

		std::vector<Media::MediaType> types;
		const auto js_types = static_cast<std::vector<JSValue>>(js_array);
		for (const auto v : js_types) {
			types.push_back(static_cast<Media::MediaType>(static_cast<std::uint32_t>(v)));
		}
		set_availablePhotoMediaTypes(types);
		return true;
	}

	TITANIUM_PROPERTY_GETTER_DOUBLE(MediaModule, averageMicrophonePower)
	TITANIUM_PROPERTY_SETTER_DOUBLE(MediaModule, averageMicrophonePower)
	TITANIUM_PROPERTY_GETTER_ENUM(MediaModule, cameraFlashMode)
	TITANIUM_PROPERTY_SETTER_ENUM(MediaModule, cameraFlashMode, Media::CameraOption)
	TITANIUM_PROPERTY_GETTER_BOOL(MediaModule, canRecord)
	TITANIUM_PROPERTY_GETTER_STRUCT(MediaModule, currentRoute, RouteDescription)
	TITANIUM_PROPERTY_GETTER_BOOL(MediaModule, isCameraSupported)
	TITANIUM_PROPERTY_GETTER_DOUBLE(MediaModule, volume)

	TITANIUM_PROPERTY_GETTER(MediaModule, systemMusicPlayer)
	{
		return systemMusicPlayer__;
	}

	TITANIUM_FUNCTION(MediaModule, beep)
	{
		beep();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, hideCamera)
	{
		hideCamera();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, hideMusicLibrary)
	{
		hideMusicLibrary();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, isMediaTypeSupported)
	{
		ENSURE_ARGUMENT_INDEX(1);
		ENSURE_STRING_AT_INDEX(source, 0);
		ENSURE_ENUM_AT_INDEX(type, 1, Media::MediaType);

		return get_context().CreateBoolean(isMediaTypeSupported(source, type));
	}

	TITANIUM_FUNCTION(MediaModule, openMusicLibrary)
	{
		ENSURE_OBJECT_AT_INDEX(options, 0);

		openMusicLibrary(Media::js_to_MusicLibraryOptionsType(options));
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, openPhotoGallery)
	{
		ENSURE_OBJECT_AT_INDEX(options, 0);

		openPhotoGallery(Media::js_to_PhotoGalleryOptionsType(options));
		return get_context().CreateUndefined();
	}

	TITANIUM_PROPERTY_GETTER(MediaModule, peakMicrophonePower)
	{
		return get_context().CreateNumber(get_peakMicrophonePower());
	}

	TITANIUM_FUNCTION(MediaModule, previewImage)
	{
		ENSURE_OBJECT_AT_INDEX(js_options, 0);

		std::unordered_map<std::string, Media::PreviewImageOptions> options;

		for (const auto& name : static_cast<std::vector<JSString>>(js_options.GetPropertyNames())) {
			options.emplace(name, Media::js_to_PreviewImageOptions(static_cast<JSObject>(js_options.GetProperty(name))));
		}

		previewImage(options);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, saveToPhotoGallery)
	{
		ENSURE_ARGUMENT_INDEX(1);
		ENSURE_OBJECT_AT_INDEX(media, 0);
		ENSURE_OBJECT_AT_INDEX(callbacks, 1);

		const auto blob = media.GetPrivate<Titanium::Blob>();
		const auto file = media.GetPrivate<Titanium::Filesystem::File>();
		if (blob) {
			saveToPhotoGallery(blob, callbacks);
		} else if (file) {
			saveToPhotoGallery(file, callbacks);
		} else {
			TITANIUM_LOG_ERROR("invalid object, expected type Titanium.Blob/Titanium.Filesystem.File");
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, setOverrideAudioRoute)
	{
		ENSURE_UINT_AT_INDEX(route, 0);

		setOverrideAudioRoute(static_cast<Media::AudioSessionOverrideRoute>(route));
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, showCamera)
	{
		ENSURE_OBJECT_AT_INDEX(options, 0);
		showCamera(Media::js_to_CameraOptionsType(options));
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, queryMusicLibrary)
	{
		ENSURE_OBJECT_AT_INDEX(query, 0);

		std::vector<JSValue> js_results;
		const auto results = queryMusicLibrary(Media::js_to_MediaQueryType(query));
		for (const auto result : results) {
			js_results.push_back(result->get_object());
		}
		return get_context().CreateArray(js_results);
	}

	TITANIUM_FUNCTION(MediaModule, startMicrophoneMonitor)
	{
		startMicrophoneMonitor();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, stopMicrophoneMonitor)
	{
		stopMicrophoneMonitor();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, takePicture)
	{
		takePicture();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, startVideoCapture)
	{
		startVideoCapture();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, stopVideoCapture)
	{
		stopVideoCapture();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, switchCamera)
	{
		ENSURE_UINT_AT_INDEX(camera, 0);
		switchCamera(static_cast<Media::CameraOption>(camera));
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, takeScreenshot)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(callback, 0);
		takeScreenshot(callback);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, vibrate)
	{
		ENSURE_ARRAY_AT_INDEX(js_pattern, 0);
		const auto js_pattern_array = static_cast<std::vector<JSValue>>(js_pattern);
		std::vector<std::chrono::milliseconds> patterns;
		for (const auto v : js_pattern_array) {
			patterns.push_back(std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<std::uint32_t>(v))));
		}
		vibrate(patterns);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, requestAuthorization)
	{
		ENSURE_OBJECT_AT_INDEX(callback, 0);
		requestAuthorization(callback);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, requestAudioRecorderPermissions)
	{
		ENSURE_OBJECT_AT_INDEX(callback, 0);
		requestAuthorization(callback);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, hasCameraPermissions)
	{
		return get_context().CreateBoolean(hasCameraPermissions());
	}

	TITANIUM_FUNCTION(MediaModule, requestCameraPermissions)
	{
		ENSURE_OBJECT_AT_INDEX(callback, 0);
		requestCameraPermissions(callback);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, createAudioPlayer)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_MEDIA(AudioPlayer);
	}

	TITANIUM_FUNCTION(MediaModule, createAudioRecorder)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_MEDIA(AudioRecorder);
	}

	TITANIUM_FUNCTION(MediaModule, createSound)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_MEDIA(Sound);
	}

	TITANIUM_FUNCTION(MediaModule, createVideoPlayer)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_MEDIA(VideoPlayer);
	}

	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getAppMusicPlayer, appMusicPlayer)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getAudioPlaying, audioPlaying)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getAudioSessionCategory, audioSessionCategory)
	TITANIUM_FUNCTION_AS_SETTER(MediaModule, setAudioSessionCategory, audioSessionCategory)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getAvailableCameras, availableCameras)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getAvailableCameraMediaTypes, availableCameraMediaTypes)
	TITANIUM_FUNCTION_AS_SETTER(MediaModule, setAvailableCameraMediaTypes, availableCameraMediaTypes)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getAvailablePhotoGalleryMediaTypes, availablePhotoGalleryMediaTypes)
	TITANIUM_FUNCTION_AS_SETTER(MediaModule, setAvailablePhotoGalleryMediaTypes, availablePhotoGalleryMediaTypes)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getAvailablePhotoMediaTypes, availablePhotoMediaTypes)
	TITANIUM_FUNCTION_AS_SETTER(MediaModule, setAvailablePhotoMediaTypes, availablePhotoMediaTypes)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getAverageMicrophonePower, averageMicrophonePower)
	TITANIUM_FUNCTION_AS_SETTER(MediaModule, setAverageMicrophonePower, averageMicrophonePower)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getCameraFlashMode, cameraFlashMode)
	TITANIUM_FUNCTION_AS_SETTER(MediaModule, setCameraFlashMode, cameraFlashMode)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getCanRecord, canRecord)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getCurrentRoute, currentRoute)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getIsCameraSupported, isCameraSupported)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getPeakMicrophonePower, peakMicrophonePower)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getSystemMusicPlayer, systemMusicPlayer)
	TITANIUM_FUNCTION_AS_GETTER(MediaModule, getVolume, volume)

} // namespace Titanium
