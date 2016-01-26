/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/MediaModule.hpp"
#include "Titanium/Media/AudioPlayer.hpp"
#include "Titanium/Media/AudioRecorder.hpp"
#include "Titanium/Media/Item.hpp"
#include "Titanium/Media/MusicPlayer.hpp"
#include "Titanium/Media/Sound.hpp"
#include "Titanium/Media/VideoPlayer.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class MediaTests : public testing::Test
{
protected:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}

	JSContextGroup js_context_group;
};

TEST_F(MediaTests, BasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto Media = js_context.CreateObject(JSExport<Titanium::MediaModule>::Class());

	XCTAssertTrue(Media.HasProperty("AUDIO_FILEFORMAT_3GP2"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FILEFORMAT_3GPP"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FILEFORMAT_AIFF"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FILEFORMAT_AMR"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FILEFORMAT_CAF"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FILEFORMAT_MP3"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FILEFORMAT_MP4"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FILEFORMAT_MP4A"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FILEFORMAT_WAVE"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FORMAT_AAC"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FORMAT_ALAW"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FORMAT_APPLE_LOSSLESS"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FORMAT_ILBC"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FORMAT_IMA4"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FORMAT_LINEAR_PCM"));
	XCTAssertTrue(Media.HasProperty("AUDIO_FORMAT_ULAW"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_CATEGORY_AMBIENT"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_CATEGORY_PLAYBACK"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_CATEGORY_PLAY_AND_RECORD"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_CATEGORY_RECORD"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_CATEGORY_SOLO_AMBIENT"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_OVERRIDE_ROUTE_NONE"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_OVERRIDE_ROUTE_SPEAKER"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_LINEIN"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_BUILTINMIC"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_HEADSETMIC"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_LINEOUT"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_HEADPHONES"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_BLUETOOTHA2DP"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_BUILTINRECEIVER"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_BUILTINSPEAKER"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_HDMI"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_AIRPLAY"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_BLUETOOTHHFP"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_USBAUDIO"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_BLUETOOTHLE"));
	XCTAssertTrue(Media.HasProperty("AUDIO_SESSION_PORT_CARAUDIO"));
	XCTAssertTrue(Media.HasProperty("CAMERA_FLASH_AUTO"));
	XCTAssertTrue(Media.HasProperty("CAMERA_FLASH_OFF"));
	XCTAssertTrue(Media.HasProperty("CAMERA_FLASH_ON"));
	XCTAssertTrue(Media.HasProperty("CAMERA_FRONT"));
	XCTAssertTrue(Media.HasProperty("CAMERA_REAR"));
	XCTAssertTrue(Media.HasProperty("DEVICE_BUSY"));
	XCTAssertTrue(Media.HasProperty("MEDIA_TYPE_PHOTO"));
	XCTAssertTrue(Media.HasProperty("MEDIA_TYPE_VIDEO"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_TYPE_ALL"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_TYPE_ANY_AUDIO"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_TYPE_AUDIOBOOK"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_TYPE_MUSIC"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_TYPE_PODCAST"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_GROUP_TITLE"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_GROUP_ALBUM"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_GROUP_ARTIST"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_GROUP_ALBUM_ARTIST"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_GROUP_COMPOSER"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_GROUP_GENRE"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_GROUP_PLAYLIST"));
	XCTAssertTrue(Media.HasProperty("MUSIC_MEDIA_GROUP_PODCAST_TITLE"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_REPEAT_ALL"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_REPEAT_DEFAULT"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_REPEAT_NONE"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_REPEAT_ONE"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_SHUFFLE_ALBUMS"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_SHUFFLE_DEFAULT"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_SHUFFLE_NONE"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_SHUFFLE_SONGS"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_STATE_INTERRUPTED"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_STATE_PAUSED"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_STATE_PLAYING"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_STATE_SEEK_BACKWARD"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_STATE_SEEK_FORWARD"));
	XCTAssertTrue(Media.HasProperty("MUSIC_PLAYER_STATE_STOPPED"));
	XCTAssertTrue(Media.HasProperty("NO_CAMERA"));
	XCTAssertTrue(Media.HasProperty("NO_VIDEO"));
	XCTAssertTrue(Media.HasProperty("QUALITY_HIGH"));
	XCTAssertTrue(Media.HasProperty("QUALITY_LOW"));
	XCTAssertTrue(Media.HasProperty("QUALITY_MEDIUM"));
	XCTAssertTrue(Media.HasProperty("UNKNOWN_ERROR"));
	XCTAssertTrue(Media.HasProperty("VIDEO_CONTROL_DEFAULT"));
	XCTAssertTrue(Media.HasProperty("VIDEO_CONTROL_EMBEDDED"));
	XCTAssertTrue(Media.HasProperty("VIDEO_CONTROL_FULLSCREEN"));
	XCTAssertTrue(Media.HasProperty("VIDEO_CONTROL_HIDDEN"));
	XCTAssertTrue(Media.HasProperty("VIDEO_CONTROL_NONE"));
	XCTAssertTrue(Media.HasProperty("VIDEO_FINISH_REASON_PLAYBACK_ENDED"));
	XCTAssertTrue(Media.HasProperty("VIDEO_FINISH_REASON_PLAYBACK_ERROR"));
	XCTAssertTrue(Media.HasProperty("VIDEO_FINISH_REASON_USER_EXITED"));
	XCTAssertTrue(Media.HasProperty("VIDEO_LOAD_STATE_PLAYABLE"));
	XCTAssertTrue(Media.HasProperty("VIDEO_LOAD_STATE_PLAYTHROUGH_OK"));
	XCTAssertTrue(Media.HasProperty("VIDEO_LOAD_STATE_STALLED"));
	XCTAssertTrue(Media.HasProperty("VIDEO_LOAD_STATE_UNKNOWN"));
	XCTAssertTrue(Media.HasProperty("VIDEO_MEDIA_TYPE_AUDIO"));
	XCTAssertTrue(Media.HasProperty("VIDEO_MEDIA_TYPE_NONE"));
	XCTAssertTrue(Media.HasProperty("VIDEO_MEDIA_TYPE_VIDEO"));
	XCTAssertTrue(Media.HasProperty("VIDEO_PLAYBACK_STATE_INTERRUPTED"));
	XCTAssertTrue(Media.HasProperty("VIDEO_PLAYBACK_STATE_PAUSED"));
	XCTAssertTrue(Media.HasProperty("VIDEO_PLAYBACK_STATE_PLAYING"));
	XCTAssertTrue(Media.HasProperty("VIDEO_PLAYBACK_STATE_SEEKING_BACKWARD"));
	XCTAssertTrue(Media.HasProperty("VIDEO_PLAYBACK_STATE_SEEKING_FORWARD"));
	XCTAssertTrue(Media.HasProperty("VIDEO_PLAYBACK_STATE_STOPPED"));
	XCTAssertTrue(Media.HasProperty("VIDEO_REPEAT_MODE_NONE"));
	XCTAssertTrue(Media.HasProperty("VIDEO_REPEAT_MODE_ONE"));
	XCTAssertTrue(Media.HasProperty("VIDEO_SCALING_ASPECT_FILL"));
	XCTAssertTrue(Media.HasProperty("VIDEO_SCALING_ASPECT_FIT"));
	XCTAssertTrue(Media.HasProperty("VIDEO_SCALING_MODE_FILL"));
	XCTAssertTrue(Media.HasProperty("VIDEO_SCALING_NONE"));
	XCTAssertTrue(Media.HasProperty("VIDEO_SOURCE_TYPE_FILE"));
	XCTAssertTrue(Media.HasProperty("VIDEO_SOURCE_TYPE_STREAMING"));
	XCTAssertTrue(Media.HasProperty("VIDEO_SOURCE_TYPE_UNKNOWN"));
	XCTAssertTrue(Media.HasProperty("VIDEO_TIME_OPTION_EXACT"));
	XCTAssertTrue(Media.HasProperty("VIDEO_TIME_OPTION_NEAREST_KEYFRAME"));
	XCTAssertTrue(Media.HasProperty("VIDEO_TIME_OPTION_CLOSEST_SYNC"));
	XCTAssertTrue(Media.HasProperty("VIDEO_TIME_OPTION_NEXT_SYNC"));
	XCTAssertTrue(Media.HasProperty("VIDEO_TIME_OPTION_PREVIOUS_SYNC"));
	XCTAssertTrue(Media.HasProperty("appMusicPlayer"));
	XCTAssertTrue(Media.HasProperty("audioPlaying"));
	XCTAssertTrue(Media.HasProperty("audioSessionCategory"));
	XCTAssertTrue(Media.HasProperty("availableCameras"));
	XCTAssertTrue(Media.HasProperty("availableCameraMediaTypes"));
	XCTAssertTrue(Media.HasProperty("availablePhotoGalleryMediaTypes"));
	XCTAssertTrue(Media.HasProperty("availablePhotoMediaTypes"));
	XCTAssertTrue(Media.HasProperty("averageMicrophonePower"));
	XCTAssertTrue(Media.HasProperty("cameraFlashMode"));
	XCTAssertTrue(Media.HasProperty("canRecord"));
	XCTAssertTrue(Media.HasProperty("currentRoute"));
	XCTAssertTrue(Media.HasProperty("isCameraSupported"));
	XCTAssertTrue(Media.HasProperty("peakMicrophonePower"));
	XCTAssertTrue(Media.HasProperty("systemMusicPlayer"));
	XCTAssertTrue(Media.HasProperty("volume"));
	XCTAssertTrue(Media.HasProperty("beep"));
	XCTAssertTrue(Media.HasProperty("hideCamera"));
	XCTAssertTrue(Media.HasProperty("hideMusicLibrary"));
	XCTAssertTrue(Media.HasProperty("isMediaTypeSupported"));
	XCTAssertTrue(Media.HasProperty("openMusicLibrary"));
	XCTAssertTrue(Media.HasProperty("openPhotoGallery"));
	XCTAssertTrue(Media.HasProperty("previewImage"));
	XCTAssertTrue(Media.HasProperty("saveToPhotoGallery"));
	XCTAssertTrue(Media.HasProperty("setOverrideAudioRoute"));
	XCTAssertTrue(Media.HasProperty("showCamera"));
	XCTAssertTrue(Media.HasProperty("queryMusicLibrary"));
	XCTAssertTrue(Media.HasProperty("startMicrophoneMonitor"));
	XCTAssertTrue(Media.HasProperty("stopMicrophoneMonitor"));
	XCTAssertTrue(Media.HasProperty("takePicture"));
	XCTAssertTrue(Media.HasProperty("startVideoCapture"));
	XCTAssertTrue(Media.HasProperty("stopVideoCapture"));
	XCTAssertTrue(Media.HasProperty("switchCamera"));
	XCTAssertTrue(Media.HasProperty("takeScreenshot"));
	XCTAssertTrue(Media.HasProperty("vibrate"));
	XCTAssertTrue(Media.HasProperty("requestAuthorization"));
	XCTAssertTrue(Media.HasProperty("createAudioPlayer"));
	XCTAssertTrue(Media.HasProperty("createAudioRecorder"));
	XCTAssertTrue(Media.HasProperty("getAppMusicPlayer"));
	XCTAssertTrue(Media.HasProperty("getAudioPlaying"));
	XCTAssertTrue(Media.HasProperty("getAudioSessionCategory"));
	XCTAssertTrue(Media.HasProperty("setAudioSessionCategory"));
	XCTAssertTrue(Media.HasProperty("getAvailableCameras"));
	XCTAssertTrue(Media.HasProperty("getAvailableCameraMediaTypes"));
	XCTAssertTrue(Media.HasProperty("setAvailableCameraMediaTypes"));
	XCTAssertTrue(Media.HasProperty("getAvailablePhotoGalleryMediaTypes"));
	XCTAssertTrue(Media.HasProperty("setAvailablePhotoGalleryMediaTypes"));
	XCTAssertTrue(Media.HasProperty("getAvailablePhotoMediaTypes"));
	XCTAssertTrue(Media.HasProperty("setAvailablePhotoMediaTypes"));
	XCTAssertTrue(Media.HasProperty("getAverageMicrophonePower"));
	XCTAssertTrue(Media.HasProperty("setAverageMicrophonePower"));
	XCTAssertTrue(Media.HasProperty("getCameraFlashMode"));
	XCTAssertTrue(Media.HasProperty("setCameraFlashMode"));
	XCTAssertTrue(Media.HasProperty("getCanRecord"));
	XCTAssertTrue(Media.HasProperty("getCurrentRoute"));
	XCTAssertTrue(Media.HasProperty("getIsCameraSupported"));
	XCTAssertTrue(Media.HasProperty("getPeakMicrophonePower"));
	XCTAssertTrue(Media.HasProperty("getSystemMusicPlayer"));
	XCTAssertTrue(Media.HasProperty("getVolume"));
}

TEST_F(MediaTests, AudioPlayerBasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto AudioPlayer = js_context.CreateObject(JSExport<Titanium::Media::AudioPlayer>::Class());

	XCTAssertTrue(AudioPlayer.HasProperty("STATE_BUFFERING"));
	XCTAssertTrue(AudioPlayer.HasProperty("STATE_INITIALIZED"));
	XCTAssertTrue(AudioPlayer.HasProperty("STATE_PAUSED"));
	XCTAssertTrue(AudioPlayer.HasProperty("STATE_PLAYING"));
	XCTAssertTrue(AudioPlayer.HasProperty("STATE_STARTING"));
	XCTAssertTrue(AudioPlayer.HasProperty("STATE_STOPPED"));
	XCTAssertTrue(AudioPlayer.HasProperty("STATE_STOPPING"));
	XCTAssertTrue(AudioPlayer.HasProperty("STATE_WAITING_FOR_DATA"));
	XCTAssertTrue(AudioPlayer.HasProperty("STATE_WAITING_FOR_QUEUE"));
	XCTAssertTrue(AudioPlayer.HasProperty("allowBackground"));
	XCTAssertTrue(AudioPlayer.HasProperty("autoplay"));
	XCTAssertTrue(AudioPlayer.HasProperty("bitRate"));
	XCTAssertTrue(AudioPlayer.HasProperty("duration"));
	XCTAssertTrue(AudioPlayer.HasProperty("idle"));
	XCTAssertTrue(AudioPlayer.HasProperty("paused"));
	XCTAssertTrue(AudioPlayer.HasProperty("playing"));
	XCTAssertTrue(AudioPlayer.HasProperty("progress"));
	XCTAssertTrue(AudioPlayer.HasProperty("state"));
	XCTAssertTrue(AudioPlayer.HasProperty("url"));
	XCTAssertTrue(AudioPlayer.HasProperty("volume"));
	XCTAssertTrue(AudioPlayer.HasProperty("waiting"));
	XCTAssertTrue(AudioPlayer.HasProperty("bufferSize"));
	XCTAssertTrue(AudioPlayer.HasProperty("time"));

	XCTAssertTrue(AudioPlayer.HasProperty("isPaused"));
	XCTAssertTrue(AudioPlayer.HasProperty("isPlaying"));
	XCTAssertTrue(AudioPlayer.HasProperty("pause"));
	XCTAssertTrue(AudioPlayer.HasProperty("play"));
	XCTAssertTrue(AudioPlayer.HasProperty("release"));
	XCTAssertTrue(AudioPlayer.HasProperty("start"));
	XCTAssertTrue(AudioPlayer.HasProperty("stateDescription"));
	XCTAssertTrue(AudioPlayer.HasProperty("stop"));
	XCTAssertTrue(AudioPlayer.HasProperty("getAllowBackground"));
	XCTAssertTrue(AudioPlayer.HasProperty("setAllowBackground"));
	XCTAssertTrue(AudioPlayer.HasProperty("getAutoplay"));
	XCTAssertTrue(AudioPlayer.HasProperty("setAutoplay"));
	XCTAssertTrue(AudioPlayer.HasProperty("getBitRate"));
	XCTAssertTrue(AudioPlayer.HasProperty("setBitRate"));
	XCTAssertTrue(AudioPlayer.HasProperty("getDuration"));
	XCTAssertTrue(AudioPlayer.HasProperty("getIdle"));
	XCTAssertTrue(AudioPlayer.HasProperty("getPaused"));
	XCTAssertTrue(AudioPlayer.HasProperty("setPaused"));
	XCTAssertTrue(AudioPlayer.HasProperty("getPlaying"));
	XCTAssertTrue(AudioPlayer.HasProperty("getProgress"));
	XCTAssertTrue(AudioPlayer.HasProperty("getState"));
	XCTAssertTrue(AudioPlayer.HasProperty("getUrl"));
	XCTAssertTrue(AudioPlayer.HasProperty("setUrl"));
	XCTAssertTrue(AudioPlayer.HasProperty("getVolume"));
	XCTAssertTrue(AudioPlayer.HasProperty("setVolume"));
	XCTAssertTrue(AudioPlayer.HasProperty("getWaiting"));
	XCTAssertTrue(AudioPlayer.HasProperty("getBufferSize"));
	XCTAssertTrue(AudioPlayer.HasProperty("setBufferSize"));
	XCTAssertTrue(AudioPlayer.HasProperty("getTime"));
	XCTAssertTrue(AudioPlayer.HasProperty("setTime"));
}

TEST_F(MediaTests, AudioRecorderBasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto AudioRecorder = js_context.CreateObject(JSExport<Titanium::Media::AudioRecorder>::Class());

	XCTAssertTrue(AudioRecorder.HasProperty("compression"));
	XCTAssertTrue(AudioRecorder.HasProperty("format"));
	XCTAssertTrue(AudioRecorder.HasProperty("paused"));
	XCTAssertTrue(AudioRecorder.HasProperty("recording"));
	XCTAssertTrue(AudioRecorder.HasProperty("stopped"));

	XCTAssertTrue(AudioRecorder.HasProperty("pause"));
	XCTAssertTrue(AudioRecorder.HasProperty("resume"));
	XCTAssertTrue(AudioRecorder.HasProperty("start"));
	XCTAssertTrue(AudioRecorder.HasProperty("stop"));
	XCTAssertTrue(AudioRecorder.HasProperty("getCompression"));
	XCTAssertTrue(AudioRecorder.HasProperty("setCompression"));
	XCTAssertTrue(AudioRecorder.HasProperty("getFormat"));
	XCTAssertTrue(AudioRecorder.HasProperty("setFormat"));
	XCTAssertTrue(AudioRecorder.HasProperty("getPaused"));
	XCTAssertTrue(AudioRecorder.HasProperty("getRecording"));
	XCTAssertTrue(AudioRecorder.HasProperty("getStopped"));
}

TEST_F(MediaTests, AudioItemBasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto Item = js_context.CreateObject(JSExport<Titanium::Media::Item>::Class());

	XCTAssertTrue(Item.HasProperty("albumArtist"));
	XCTAssertTrue(Item.HasProperty("albumTitle"));
	XCTAssertTrue(Item.HasProperty("albumTrackCount"));
	XCTAssertTrue(Item.HasProperty("albumTrackNumber"));
	XCTAssertTrue(Item.HasProperty("artist"));
	XCTAssertTrue(Item.HasProperty("artwork"));
	XCTAssertTrue(Item.HasProperty("composer"));
	XCTAssertTrue(Item.HasProperty("discCount"));
	XCTAssertTrue(Item.HasProperty("discNumber"));
	XCTAssertTrue(Item.HasProperty("genre"));
	XCTAssertTrue(Item.HasProperty("isCompilation"));
	XCTAssertTrue(Item.HasProperty("lyrics"));
	XCTAssertTrue(Item.HasProperty("mediaType"));
	XCTAssertTrue(Item.HasProperty("playCount"));
	XCTAssertTrue(Item.HasProperty("playbackDuration"));
	XCTAssertTrue(Item.HasProperty("podcastTitle"));
	XCTAssertTrue(Item.HasProperty("rating"));
	XCTAssertTrue(Item.HasProperty("skipCount"));
	XCTAssertTrue(Item.HasProperty("title"));

	XCTAssertTrue(Item.HasProperty("getAlbumArtist"));
	XCTAssertTrue(Item.HasProperty("getAlbumTitle"));
	XCTAssertTrue(Item.HasProperty("getAlbumTrackCount"));
	XCTAssertTrue(Item.HasProperty("getAlbumTrackNumber"));
	XCTAssertTrue(Item.HasProperty("getArtist"));
	XCTAssertTrue(Item.HasProperty("getArtwork"));
	XCTAssertTrue(Item.HasProperty("getComposer"));
	XCTAssertTrue(Item.HasProperty("getDiscCount"));
	XCTAssertTrue(Item.HasProperty("getDiscNumber"));
	XCTAssertTrue(Item.HasProperty("getGenre"));
	XCTAssertTrue(Item.HasProperty("getIsCompilation"));
	XCTAssertTrue(Item.HasProperty("getLyrics"));
	XCTAssertTrue(Item.HasProperty("getMediaType"));
	XCTAssertTrue(Item.HasProperty("getPlayCount"));
	XCTAssertTrue(Item.HasProperty("getPlaybackDuration"));
	XCTAssertTrue(Item.HasProperty("getPodcastTitle"));
	XCTAssertTrue(Item.HasProperty("getRating"));
	XCTAssertTrue(Item.HasProperty("getSkipCount"));
	XCTAssertTrue(Item.HasProperty("getTitle"));
}

TEST_F(MediaTests, MusicPlayerBasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto MusicPlayer = js_context.CreateObject(JSExport<Titanium::Media::MusicPlayer>::Class());

	XCTAssertTrue(MusicPlayer.HasProperty("currentPlaybackTime"));
	XCTAssertTrue(MusicPlayer.HasProperty("nowPlaying"));
	XCTAssertTrue(MusicPlayer.HasProperty("playbackState"));
	XCTAssertTrue(MusicPlayer.HasProperty("repeatMode"));
	XCTAssertTrue(MusicPlayer.HasProperty("shuffleMode"));
	XCTAssertTrue(MusicPlayer.HasProperty("volume"));

	XCTAssertTrue(MusicPlayer.HasProperty("pause"));
	XCTAssertTrue(MusicPlayer.HasProperty("play"));
	XCTAssertTrue(MusicPlayer.HasProperty("seekBackward"));
	XCTAssertTrue(MusicPlayer.HasProperty("seekForward"));
	XCTAssertTrue(MusicPlayer.HasProperty("setQueue"));
	XCTAssertTrue(MusicPlayer.HasProperty("skipToBeginning"));
	XCTAssertTrue(MusicPlayer.HasProperty("skipToNext"));
	XCTAssertTrue(MusicPlayer.HasProperty("skipToPrevious"));
	XCTAssertTrue(MusicPlayer.HasProperty("stop"));
	XCTAssertTrue(MusicPlayer.HasProperty("stopSeeking"));
	XCTAssertTrue(MusicPlayer.HasProperty("getCurrentPlaybackTime"));
	XCTAssertTrue(MusicPlayer.HasProperty("setCurrentPlaybackTime"));
	XCTAssertTrue(MusicPlayer.HasProperty("getNowPlaying"));
	XCTAssertTrue(MusicPlayer.HasProperty("getPlaybackState"));
	XCTAssertTrue(MusicPlayer.HasProperty("getRepeatMode"));
	XCTAssertTrue(MusicPlayer.HasProperty("setRepeatMode"));
	XCTAssertTrue(MusicPlayer.HasProperty("getShuffleMode"));
	XCTAssertTrue(MusicPlayer.HasProperty("setShuffleMode"));
	XCTAssertTrue(MusicPlayer.HasProperty("getVolume"));
	XCTAssertTrue(MusicPlayer.HasProperty("setVolume"));
}

TEST_F(MediaTests, SoundBasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto Sound = js_context.CreateObject(JSExport<Titanium::Media::Sound>::Class());

	XCTAssertTrue(Sound.HasProperty("STATE_BUFFERING"));
	XCTAssertTrue(Sound.HasProperty("STATE_INITIALIZED"));
	XCTAssertTrue(Sound.HasProperty("STATE_PAUSED"));
	XCTAssertTrue(Sound.HasProperty("STATE_PLAYING"));
	XCTAssertTrue(Sound.HasProperty("STATE_STARTING"));
	XCTAssertTrue(Sound.HasProperty("STATE_STOPPED"));
	XCTAssertTrue(Sound.HasProperty("STATE_STOPPING"));
	XCTAssertTrue(Sound.HasProperty("STATE_WAITING_FOR_DATA"));
	XCTAssertTrue(Sound.HasProperty("STATE_WAITING_FOR_QUEUE"));
	XCTAssertTrue(Sound.HasProperty("allowBackground"));
	XCTAssertTrue(Sound.HasProperty("duration"));
	XCTAssertTrue(Sound.HasProperty("looping"));
	XCTAssertTrue(Sound.HasProperty("paused"));
	XCTAssertTrue(Sound.HasProperty("playing"));
	XCTAssertTrue(Sound.HasProperty("time"));
	XCTAssertTrue(Sound.HasProperty("url"));
	XCTAssertTrue(Sound.HasProperty("volume"));

	XCTAssertTrue(Sound.HasProperty("isLooping"));
	XCTAssertTrue(Sound.HasProperty("isPaused"));
	XCTAssertTrue(Sound.HasProperty("isPlaying"));
	XCTAssertTrue(Sound.HasProperty("pause"));
	XCTAssertTrue(Sound.HasProperty("play"));
	XCTAssertTrue(Sound.HasProperty("release"));
	XCTAssertTrue(Sound.HasProperty("reset"));
	XCTAssertTrue(Sound.HasProperty("setLooping"));
	XCTAssertTrue(Sound.HasProperty("setPaused"));
	XCTAssertTrue(Sound.HasProperty("stop"));
	XCTAssertTrue(Sound.HasProperty("getDuration"));
	XCTAssertTrue(Sound.HasProperty("getTime"));
	XCTAssertTrue(Sound.HasProperty("setTime"));
	XCTAssertTrue(Sound.HasProperty("getUrl"));
	XCTAssertTrue(Sound.HasProperty("setUrl"));
	XCTAssertTrue(Sound.HasProperty("getVolume"));
	XCTAssertTrue(Sound.HasProperty("setVolume"));
}

TEST_F(MediaTests, VideoPlayerBasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto VideoPlayer = js_context.CreateObject(JSExport<Titanium::Media::VideoPlayer>::Class());

	XCTAssertTrue(VideoPlayer.HasProperty("allowsAirPlay"));
	XCTAssertTrue(VideoPlayer.HasProperty("autoplay"));
	XCTAssertTrue(VideoPlayer.HasProperty("contentURL"));
	XCTAssertTrue(VideoPlayer.HasProperty("currentPlaybackTime"));
	XCTAssertTrue(VideoPlayer.HasProperty("duration"));
	XCTAssertTrue(VideoPlayer.HasProperty("endPlaybackTime"));
	XCTAssertTrue(VideoPlayer.HasProperty("fullscreen"));
	XCTAssertTrue(VideoPlayer.HasProperty("initialPlaybackTime"));
	XCTAssertTrue(VideoPlayer.HasProperty("loadState"));
	XCTAssertTrue(VideoPlayer.HasProperty("media"));
	XCTAssertTrue(VideoPlayer.HasProperty("mediaControlStyle"));
	XCTAssertTrue(VideoPlayer.HasProperty("mediaTypes"));
	XCTAssertTrue(VideoPlayer.HasProperty("movieControlMode"));
	XCTAssertTrue(VideoPlayer.HasProperty("naturalSize"));
	XCTAssertTrue(VideoPlayer.HasProperty("playableDuration"));
	XCTAssertTrue(VideoPlayer.HasProperty("playbackState"));
	XCTAssertTrue(VideoPlayer.HasProperty("playing"));
	XCTAssertTrue(VideoPlayer.HasProperty("repeatMode"));
	XCTAssertTrue(VideoPlayer.HasProperty("scalingMode"));
	XCTAssertTrue(VideoPlayer.HasProperty("sourceType"));
	XCTAssertTrue(VideoPlayer.HasProperty("url"));
	XCTAssertTrue(VideoPlayer.HasProperty("useApplicationAudioSession"));
	XCTAssertTrue(VideoPlayer.HasProperty("volume"));

	XCTAssertTrue(VideoPlayer.HasProperty("cancelAllThumbnailImageRequests"));
	XCTAssertTrue(VideoPlayer.HasProperty("pause"));
	XCTAssertTrue(VideoPlayer.HasProperty("play"));
	XCTAssertTrue(VideoPlayer.HasProperty("release"));
	XCTAssertTrue(VideoPlayer.HasProperty("requestThumbnailImagesAtTimes"));
	XCTAssertTrue(VideoPlayer.HasProperty("setBackgroundView"));
	XCTAssertTrue(VideoPlayer.HasProperty("stop"));
	XCTAssertTrue(VideoPlayer.HasProperty("thumbnailImageAtTime"));
	XCTAssertTrue(VideoPlayer.HasProperty("getAllowsAirPlay"));
	XCTAssertTrue(VideoPlayer.HasProperty("setAllowsAirPlay"));
	XCTAssertTrue(VideoPlayer.HasProperty("getAutoplay"));
	XCTAssertTrue(VideoPlayer.HasProperty("setAutoplay"));
	XCTAssertTrue(VideoPlayer.HasProperty("getContentURL"));
	XCTAssertTrue(VideoPlayer.HasProperty("setContentURL"));
	XCTAssertTrue(VideoPlayer.HasProperty("getCurrentPlaybackTime"));
	XCTAssertTrue(VideoPlayer.HasProperty("setCurrentPlaybackTime"));
	XCTAssertTrue(VideoPlayer.HasProperty("getDuration"));
	XCTAssertTrue(VideoPlayer.HasProperty("setDuration"));
	XCTAssertTrue(VideoPlayer.HasProperty("getEndPlaybackTime"));
	XCTAssertTrue(VideoPlayer.HasProperty("setEndPlaybackTime"));
	XCTAssertTrue(VideoPlayer.HasProperty("getFullscreen"));
	XCTAssertTrue(VideoPlayer.HasProperty("setFullscreen"));
	XCTAssertTrue(VideoPlayer.HasProperty("getInitialPlaybackTime"));
	XCTAssertTrue(VideoPlayer.HasProperty("setInitialPlaybackTime"));
	XCTAssertTrue(VideoPlayer.HasProperty("getLoadState"));
	XCTAssertTrue(VideoPlayer.HasProperty("setMedia"));
	XCTAssertTrue(VideoPlayer.HasProperty("getMediaControlStyle"));
	XCTAssertTrue(VideoPlayer.HasProperty("setMediaControlStyle"));
	XCTAssertTrue(VideoPlayer.HasProperty("getMediaTypes"));
	XCTAssertTrue(VideoPlayer.HasProperty("setMediaTypes"));
	XCTAssertTrue(VideoPlayer.HasProperty("getMovieControlMode"));
	XCTAssertTrue(VideoPlayer.HasProperty("setMovieControlMode"));
	XCTAssertTrue(VideoPlayer.HasProperty("getNaturalSize"));
	XCTAssertTrue(VideoPlayer.HasProperty("setNaturalSize"));
	XCTAssertTrue(VideoPlayer.HasProperty("getPlayableDuration"));
	XCTAssertTrue(VideoPlayer.HasProperty("getPlaybackState"));
	XCTAssertTrue(VideoPlayer.HasProperty("getPlaying"));
	XCTAssertTrue(VideoPlayer.HasProperty("getRepeatMode"));
	XCTAssertTrue(VideoPlayer.HasProperty("setRepeatMode"));
	XCTAssertTrue(VideoPlayer.HasProperty("getScalingMode"));
	XCTAssertTrue(VideoPlayer.HasProperty("setScalingMode"));
	XCTAssertTrue(VideoPlayer.HasProperty("getSourceType"));
	XCTAssertTrue(VideoPlayer.HasProperty("setSourceType"));
	XCTAssertTrue(VideoPlayer.HasProperty("getUrl"));
	XCTAssertTrue(VideoPlayer.HasProperty("setUrl"));
	XCTAssertTrue(VideoPlayer.HasProperty("getUseApplicationAudioSession"));
	XCTAssertTrue(VideoPlayer.HasProperty("setUseApplicationAudioSession"));
	XCTAssertTrue(VideoPlayer.HasProperty("getVolume"));
	XCTAssertTrue(VideoPlayer.HasProperty("setVolume"));
}