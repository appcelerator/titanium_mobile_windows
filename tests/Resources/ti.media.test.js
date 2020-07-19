/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2017 Axway, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
/* eslint-env mocha */
/* global Ti */
/* eslint no-unused-expressions: "off" */
'use strict';
var should = require('./utilities/assertions');

describe('Titanium.Media', function () {

	it('apiName', function () {
		var media = Ti.Media;
		should(media).have.readOnlyProperty('apiName').which.is.a.String;
		should(media.apiName).be.eql('Ti.Media');
	});

	it('Constants', function () {
		should(Ti.Media.CAMERA_FLASH_AUTO).not.be.undefined;
		should(Ti.Media.CAMERA_FLASH_OFF).not.be.undefined;
		should(Ti.Media.CAMERA_FLASH_ON).not.be.undefined;
		should(Ti.Media.CAMERA_FRONT).not.be.undefined;
		should(Ti.Media.CAMERA_REAR).not.be.undefined;
		should(Ti.Media.DEVICE_BUSY).not.be.undefined;
		should(Ti.Media.MEDIA_TYPE_PHOTO).not.be.undefined;
		should(Ti.Media.MEDIA_TYPE_VIDEO).not.be.undefined;
		should(Ti.Media.NO_CAMERA).not.be.undefined;
		should(Ti.Media.NO_VIDEO).not.be.undefined;
		should(Ti.Media.QUALITY_HIGH).not.be.undefined;
		should(Ti.Media.QUALITY_LOW).not.be.undefined;
		should(Ti.Media.QUALITY_IFRAME_1280x720).not.be.undefined;
		should(Ti.Media.UNKNOWN_ERROR).not.be.undefined;
		should(Ti.Media.VIDEO_CONTROL_DEFAULT).not.be.undefined;
		should(Ti.Media.VIDEO_CONTROL_EMBEDDED).not.be.undefined;
		should(Ti.Media.VIDEO_CONTROL_FULLSCREEN).not.be.undefined;
		should(Ti.Media.VIDEO_CONTROL_HIDDEN).not.be.undefined;
		should(Ti.Media.VIDEO_CONTROL_NONE).not.be.undefined;
		should(Ti.Media.VIDEO_FINISH_REASON_PLAYBACK_ENDED).not.be.undefined;
		should(Ti.Media.VIDEO_FINISH_REASON_PLAYBACK_ERROR).not.be.undefined;
		should(Ti.Media.VIDEO_FINISH_REASON_USER_EXITED).not.be.undefined;
		should(Ti.Media.VIDEO_LOAD_STATE_PLAYABLE).not.be.undefined;
		should(Ti.Media.VIDEO_LOAD_STATE_PLAYTHROUGH_OK).not.be.undefined;
		should(Ti.Media.VIDEO_LOAD_STATE_STALLED).not.be.undefined;
		should(Ti.Media.VIDEO_LOAD_STATE_UNKNOWN).not.be.undefined;
		should(Ti.Media.VIDEO_MEDIA_TYPE_AUDIO).not.be.undefined;
		should(Ti.Media.VIDEO_MEDIA_TYPE_NONE).not.be.undefined;
		should(Ti.Media.VIDEO_MEDIA_TYPE_VIDEO).not.be.undefined;
		should(Ti.Media.VIDEO_PLAYBACK_STATE_INTERRUPTED).not.be.undefined;
		should(Ti.Media.VIDEO_PLAYBACK_STATE_PAUSED).not.be.undefined;
		should(Ti.Media.VIDEO_PLAYBACK_STATE_PLAYING).not.be.undefined;
		should(Ti.Media.VIDEO_PLAYBACK_STATE_SEEKING_BACKWARD).not.be.undefined;
		should(Ti.Media.VIDEO_PLAYBACK_STATE_SEEKING_FORWARD).not.be.undefined;
		should(Ti.Media.VIDEO_PLAYBACK_STATE_STOPPED).not.be.undefined;
		should(Ti.Media.VIDEO_REPEAT_MODE_NONE).not.be.undefined;
		should(Ti.Media.VIDEO_REPEAT_MODE_ONE).not.be.undefined;
		should(Ti.Media.VIDEO_SCALING_ASPECT_FILL).not.be.undefined;
		should(Ti.Media.VIDEO_SCALING_ASPECT_FIT).not.be.undefined;
		should(Ti.Media.VIDEO_SCALING_MODE_FILL).not.be.undefined;
		should(Ti.Media.VIDEO_SCALING_NONE).not.be.undefined;
		should(Ti.Media.VIDEO_SOURCE_TYPE_FILE).not.be.undefined;
		should(Ti.Media.VIDEO_SOURCE_TYPE_STREAMING).not.be.undefined;
		should(Ti.Media.VIDEO_SOURCE_TYPE_UNKNOWN).not.be.undefined;
		should(Ti.Media.VIDEO_TIME_OPTION_NEAREST_KEYFRAME).not.be.undefined;
	});

	it.androidAndWindowsMissing('Constants iOS only', function () {
		should(Ti.Media.MEDIA_TYPE_LIVEPHOTO).not.be.undefined;
		should(Ti.Media.VIDEO_LOAD_STATE_FAILED).not.be.undefined;
		should(Ti.Media.VIDEO_SCALING_RESIZE).not.be.undefined;
		should(Ti.Media.VIDEO_SCALING_RESIZE_ASPECT).not.be.undefined;
		should(Ti.Media.VIDEO_SCALING_RESIZE_ASPECT_FILL).not.be.undefined;
	});

	it.iosMissing('Constants Android/Windows only', function () {
		should(Ti.Media.VIDEO_TIME_OPTION_CLOSEST_SYNC).not.be.undefined;
		should(Ti.Media.VIDEO_TIME_OPTION_NEXT_SYNC).not.be.undefined;
		should(Ti.Media.VIDEO_TIME_OPTION_PREVIOUS_SYNC).not.be.undefined;
	});

	it.androidMissing('Constants iOS/Windows only', function () {
		should(Ti.Media.AUDIO_FILEFORMAT_3GP2).not.be.undefined;
		should(Ti.Media.AUDIO_FILEFORMAT_3GPP).not.be.undefined;
		should(Ti.Media.AUDIO_FILEFORMAT_AIFF).not.be.undefined;
		should(Ti.Media.AUDIO_FILEFORMAT_AMR).not.be.undefined;
		should(Ti.Media.AUDIO_FILEFORMAT_CAF).not.be.undefined;
		should(Ti.Media.AUDIO_FILEFORMAT_MP3).not.be.undefined;
		should(Ti.Media.AUDIO_FILEFORMAT_MP4).not.be.undefined;
		should(Ti.Media.AUDIO_FILEFORMAT_MP4A).not.be.undefined;
		should(Ti.Media.AUDIO_FILEFORMAT_WAVE).not.be.undefined;
		should(Ti.Media.AUDIO_FORMAT_AAC).not.be.undefined;
		should(Ti.Media.AUDIO_FORMAT_ALAW).not.be.undefined;
		should(Ti.Media.AUDIO_FORMAT_APPLE_LOSSLESS).not.be.undefined;
		should(Ti.Media.AUDIO_FORMAT_ILBC).not.be.undefined;
		should(Ti.Media.AUDIO_FORMAT_IMA4).not.be.undefined;
		should(Ti.Media.AUDIO_FORMAT_LINEAR_PCM).not.be.undefined;
		should(Ti.Media.AUDIO_FORMAT_ULAW).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_CATEGORY_AMBIENT).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_CATEGORY_PLAYBACK).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_CATEGORY_PLAY_AND_RECORD).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_CATEGORY_RECORD).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_CATEGORY_SOLO_AMBIENT).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_OVERRIDE_ROUTE_NONE).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_OVERRIDE_ROUTE_SPEAKER).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_LINEIN).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_BUILTINMIC).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_HEADSETMIC).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_LINEOUT).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_HEADPHONES).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_BLUETOOTHA2DP).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_BUILTINRECEIVER).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_BUILTINSPEAKER).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_HDMI).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_AIRPLAY).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_BLUETOOTHHFP).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_USBAUDIO).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_BLUETOOTHLE).not.be.undefined;
		should(Ti.Media.AUDIO_SESSION_PORT_CARAUDIO).not.be.undefined;
		should(Ti.Media.CAMERA_AUTHORIZATION_AUTHORIZED).not.be.undefined;
		should(Ti.Media.CAMERA_AUTHORIZATION_DENIED).not.be.undefined;
		should(Ti.Media.CAMERA_AUTHORIZATION_RESTRICTED).not.be.undefined;
		should(Ti.Media.CAMERA_AUTHORIZATION_UNKNOWN).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_TYPE_ALL).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_TYPE_ANY_AUDIO).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_TYPE_AUDIOBOOK).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_TYPE_MUSIC).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_TYPE_PODCAST).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_GROUP_TITLE).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_GROUP_ALBUM).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_GROUP_ARTIST).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_GROUP_ALBUM_ARTIST).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_GROUP_COMPOSER).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_GROUP_GENRE).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_GROUP_PLAYLIST).not.be.undefined;
		should(Ti.Media.MUSIC_MEDIA_GROUP_PODCAST_TITLE).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_REPEAT_ALL).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_REPEAT_DEFAULT).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_REPEAT_NONE).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_REPEAT_ONE).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_SHUFFLE_ALBUMS).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_SHUFFLE_DEFAULT).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_SHUFFLE_NONE).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_SHUFFLE_SONGS).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_STATE_INTERRUPTED).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_STATE_PAUSED).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_STATE_PLAYING).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_STATE_SEEK_BACKWARD).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_STATE_SEEK_FORWARD).not.be.undefined;
		should(Ti.Media.MUSIC_PLAYER_STATE_STOPPED).not.be.undefined;
		should(Ti.Media.QUALITY_MEDIUM).not.be.undefined;
		should(Ti.Media.QUALITY_IFRAME_960x540).not.be.undefined;
		should(Ti.Media.VIDEO_TIME_OPTION_EXACT).not.be.undefined;
	});

	it('audioPlaying', function () {
		should(Ti.Media.audioPlaying).not.be.undefined;
		should(Ti.Media.audioPlaying).be.a.Boolean;
	});

	it('audioSessionCategory', function () {
		should(Ti.Media.audioSessionCategory).not.be.undefined;
		should(Ti.Media.audioSessionCategory).be.a.Number;
	});

	it('availableCameras', function () {
		should(Ti.Media.availableCameras).not.be.undefined;
		should(Ti.Media.availableCameras).be.an.Array;
	});

	it('availableCameraMediaTypes', function () {
		should(Ti.Media.availableCameraMediaTypes).not.be.undefined;
		should(Ti.Media.availableCameraMediaTypes).be.an.Array;
	});

	it('availablePhotoGalleryMediaTypes', function () {
		should(Ti.Media.availablePhotoGalleryMediaTypes).not.be.undefined;
		should(Ti.Media.availablePhotoGalleryMediaTypes).be.an.Array;
	});

	it('availablePhotoMediaTypes', function () {
		should(Ti.Media.availablePhotoMediaTypes).not.be.undefined;
		should(Ti.Media.availablePhotoMediaTypes).be.an.Array;
	});

	it('averageMicrophonePower', function () {
		should(Ti.Media.averageMicrophonePower).not.be.undefined;
		should(Ti.Media.averageMicrophonePower).be.a.Number;
	});

	it('cameraAuthorization', function () {
		should(Ti.Media.cameraAuthorization).not.be.undefined;
		should(Ti.Media.cameraAuthorization).be.a.Number;
	});

	it('cameraFlashMode', function () {
		should(Ti.Media.cameraFlashMode).not.be.undefined;
		should(Ti.Media.cameraFlashMode).be.a.Number;
	});

	it('canRecord', function () {
		should(Ti.Media.canRecord).not.be.undefined;
		should(Ti.Media.canRecord).be.a.Boolean;
	});

	it('isCameraSupported', function () {
		should(Ti.Media.isCameraSupported).not.be.undefined;
		should(Ti.Media.isCameraSupported).be.a.Boolean;
	});

	it('peakMicrophonePower', function () {
		should(Ti.Media.peakMicrophonePower).not.be.undefined;
		should(Ti.Media.peakMicrophonePower).be.a.Number;
	});

	it('volume', function () {
		should(Ti.Media.volume).not.be.undefined;
		should(Ti.Media.volume).be.a.Number;
	});

	it('beep', function () {
		should(Ti.Media.beep).not.be.undefined;
		should(Ti.Media.beep).be.a.Function;
	});

	it('hideCamera', function () {
		should(Ti.Media.hideCamera).not.be.undefined;
		should(Ti.Media.hideCamera).be.a.Function;
	});

	it('hideMusicLibrary', function () {
		should(Ti.Media.hideMusicLibrary).not.be.undefined;
		should(Ti.Media.hideMusicLibrary).be.a.Function;
	});

	it('isMediaTypeSupported', function () {
		should(Ti.Media.isMediaTypeSupported).not.be.undefined;
		should(Ti.Media.isMediaTypeSupported).be.a.Function;
	});

	it('openMusicLibrary', function () {
		should(Ti.Media.openMusicLibrary).not.be.undefined;
		should(Ti.Media.openMusicLibrary).be.a.Function;
	});

	it('openPhotoGallery', function () {
		should(Ti.Media.openPhotoGallery).not.be.undefined;
		should(Ti.Media.openPhotoGallery).be.a.Function;
	});

	it('saveToPhotoGallery', function () {
		should(Ti.Media.saveToPhotoGallery).not.be.undefined;
		should(Ti.Media.saveToPhotoGallery).be.a.Function;
	});

	it('showCamera', function () {
		should(Ti.Media.showCamera).not.be.undefined;
		should(Ti.Media.showCamera).be.a.Function;
	});

	it('queryMusicLibrary', function () {
		should(Ti.Media.queryMusicLibrary).not.be.undefined;
		should(Ti.Media.queryMusicLibrary).be.a.Function;
	});

	it('startMicrophoneMonitor', function () {
		should(Ti.Media.startMicrophoneMonitor).not.be.undefined;
		should(Ti.Media.startMicrophoneMonitor).be.a.Function;
	});

	it('stopMicrophoneMonitor', function () {
		should(Ti.Media.stopMicrophoneMonitor).not.be.undefined;
		should(Ti.Media.stopMicrophoneMonitor).be.a.Function;
	});

	it('takePicture', function () {
		should(Ti.Media.takePicture).not.be.undefined;
		should(Ti.Media.takePicture).be.a.Function;
	});

	it('startVideoCapture', function () {
		should(Ti.Media.startVideoCapture).not.be.undefined;
		should(Ti.Media.startVideoCapture).be.a.Function;
	});
	
	it('stopVideoCapture', function () {
		should(Ti.Media.stopVideoCapture).not.be.undefined;
		should(Ti.Media.stopVideoCapture).be.a.Function;
	});

	it('switchCamera', function () {
		should(Ti.Media.switchCamera).not.be.undefined;
		should(Ti.Media.switchCamera).be.a.Function;
	});

	it('takeScreenshot', function () {
		should(Ti.Media.takeScreenshot).not.be.undefined;
		should(Ti.Media.takeScreenshot).be.a.Function;
	});

	it('vibrate', function () {
		should(Ti.Media.vibrate).not.be.undefined;
		should(Ti.Media.vibrate).be.a.Function;
	});

	it('hasCameraPermissions', function () {
		should(Ti.Media.hasCameraPermissions).not.be.undefined;
		should(Ti.Media.hasCameraPermissions).be.a.Function;
	});

	it('hasAudioRecorderPermissions', function () {
		should(Ti.Media.hasAudioRecorderPermissions).not.be.undefined;
		should(Ti.Media.hasAudioRecorderPermissions).be.a.Function;
	});

	it('hasMusicLibraryPermissions', function () {
		should(Ti.Media.hasMusicLibraryPermissions).not.be.undefined;
		should(Ti.Media.hasMusicLibraryPermissions).be.a.Function;
	});

	it('hasPhotoGalleryPermissions', function () {
		should(Ti.Media.hasPhotoGalleryPermissions).not.be.undefined;
		should(Ti.Media.hasPhotoGalleryPermissions).be.a.Function;
	});

	it('requestCameraPermissions', function () {
		should(Ti.Media.requestCameraPermissions).not.be.undefined;
		should(Ti.Media.requestCameraPermissions).be.a.Function;
	});

	it('requestAudioRecorderPermissions', function () {
		should(Ti.Media.requestAudioRecorderPermissions).not.be.undefined;
		should(Ti.Media.requestAudioRecorderPermissions).be.a.Function;
	});

	it('createAudioPlayer', function () {
		should(Ti.Media.createAudioPlayer).not.be.undefined;
		should(Ti.Media.createAudioPlayer).be.a.Function;
	});

	it('createAudioRecorder', function () {
		should(Ti.Media.createAudioRecorder).not.be.undefined;
		should(Ti.Media.createAudioRecorder).be.a.Function;
	});

	it('createSound', function () {
		should(Ti.Media.createSound).not.be.undefined;
		should(Ti.Media.createSound).be.a.Function;
	});

	it('createVideoPlayer', function () {
		should(Ti.Media.createVideoPlayer).not.be.undefined;
		should(Ti.Media.createVideoPlayer).be.a.Function;
	});

	it.windowsMissing('Take Screenshot', function (finish) {
		// take a screenshot
		Ti.Media.takeScreenshot(function (image) {
			if (image && image.media) {
				finish();
			} else {
				finish(new Error('failed to obtain screenshot'));
			}
		});
	});

	it.android('previewImage', function () {
		should(Ti.Media.previewImage).not.be.undefined;
		should(Ti.Media.previewImage).be.a.Function;
	});

	// FIXME: java.lang.ClassCastException: byte[] cannot be cast to org.appcelerator.titanium.io.TiBaseFile
	// This assumes the TiBlob is from a file, but in this case it's not.
	// MediaModule.java needs to be updated to write to a temp file in this case,
	// like we do for EmailDialogProxy
	// it.android('preview image from screenshot', function (finish) {
	it.allBroken('preview image from screenshot', function (finish) {
		// take a screenshot
		Ti.Media.takeScreenshot(function (image) {
			if (image && image.media) {
				Ti.Media.previewImage({
					success: function () {
						finish();
					},
					error: function (e) {
						finish(e);
					},
					image: image
				});
			} else {
				finish(new Error('failed to obtain screenshot'));
			}
		});
	});

	// FIXME: Fails to write to file on CI machine
	// Presumably it's because we need to ask for storage permissions, which we can't do in a headless way
	// it.android('preview image read/write external storage', function (finish) {
	it.allBroken('preview image read/write external storage', function (finish) {
		// take a screenshot
		Ti.Media.takeScreenshot(function (image) {
			var tmp;
			if (image && image.media) {
				tmp = Ti.Filesystem.getFile(Ti.Filesystem.externalStorageDirectory, 'temp.png');

				// write to external storage
				tmp.write(image.media);

				// preview image from external storage
				Ti.Media.previewImage({
					success: function () {
						finish();
					},
					error: function (e) {
						finish(e);
					},
					image: tmp.read()
				});
			} else {
				finish(new Error('failed to obtain screenshot'));
			}
		});
	});

});
