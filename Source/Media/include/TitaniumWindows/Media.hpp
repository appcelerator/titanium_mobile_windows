/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_MEDIAMODULE_HPP_
#define _TITANIUMWINDOWS_MEDIAMODULE_HPP_

#include "TitaniumWindows_Media_EXPORT.h"
#include "Titanium/MediaModule.hpp"
#include "Titanium/Media/CameraOptionsType.hpp"
#include "Titanium/Media/PhotoGalleryOptionsType.hpp"
#include "Titanium/Media/MusicLibraryOptionsType.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "Titanium/UI/View.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include <agile.h>
#include <collection.h>

namespace TitaniumWindows
{
	using namespace HAL;

	ref class TakingPictureState sealed
	{
	internal:
		Windows::Storage::StorageFile^ file;
		Windows::Graphics::Imaging::BitmapDecoder^ decoder;
		Windows::Graphics::Imaging::BitmapEncoder^ encoder;
		Windows::Storage::Streams::IRandomAccessStream^ outstream;
		Windows::Storage::FileProperties::PhotoOrientation orientation;
	};

	/*!
	  @class MediaModule
	  @ingroup Titanium.Media

	  @discussion This is the Titanium.Media implementation for Windows.
	*/
	class TITANIUMWINDOWS_MEDIA_EXPORT MediaModule final : public Titanium::MediaModule, public JSExport<MediaModule>
	{
	public:

		TITANIUM_FUNCTION_UNIMPLEMENTED(hideMusicLibrary);
		TITANIUM_FUNCTION_UNIMPLEMENTED(previewImage);
		TITANIUM_FUNCTION_UNIMPLEMENTED(setOverrideAudioRoute);
		TITANIUM_FUNCTION_UNIMPLEMENTED(switchCamera);
		TITANIUM_FUNCTION_UNIMPLEMENTED(queryMusicLibrary);

		/*!
		  @method
		  @abstract beep
		  @discussion Plays a device beep notification.
		*/
		virtual void beep() TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract hideCamera
		  @discussion Hides the device camera UI.
		*/
		virtual void hideCamera() TITANIUM_NOEXCEPT override;
		virtual void hideCamera(std::function<void()>) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract isMediaTypeSupported
		  @discussion Returns `true` if the source supports the specified media type.
		*/
		virtual bool isMediaTypeSupported(const std::string& source, const Titanium::Media::MediaType& type) TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract openMusicLibrary
		  @discussion Shows the music library and allows the user to select one or more tracks.
		*/
		virtual void openMusicLibrary(const Titanium::Media::MusicLibraryOptionsType& options) TITANIUM_NOEXCEPT override;
		virtual void _postOpenMusicLibrary(const std::vector<std::string>& files) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract openPhotoGallery
		  @discussion Opens the photo gallery image picker.
		*/
		virtual void openPhotoGallery(const Titanium::Media::PhotoGalleryOptionsType& options) TITANIUM_NOEXCEPT override;
		virtual void _postOpenPhotoGallery(const std::vector<std::string>& files) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract saveToPhotoGallery
		  @discussion Saves media to the device's photo gallery / camera roll.
		*/
		virtual void saveToPhotoGallery(const std::shared_ptr<Titanium::Filesystem::File>& media, JSValue callbacks) TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract showCamera
		  @discussion Shows the camera.
		*/
		virtual void showCamera(const Titanium::Media::CameraOptionsType& options) TITANIUM_NOEXCEPT override;
		virtual void _postShowCamera() TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract startMicrophoneMonitor
		  @discussion Starts monitoring the microphone sound level.
		*/
		virtual void startMicrophoneMonitor() TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract stopMicrophoneMonitor
		  @discussion Stops monitoring the microphone sound level.
		*/
		virtual void stopMicrophoneMonitor() TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract takePicture
		  @discussion Uses the device camera to capture a photo.
		*/
		virtual void takePicture() TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract startVideoCapture
		  @discussion Starts video capture using the camera specified.
		*/
		virtual void startVideoCapture() TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract stopVideoCapture
		  @discussion Stops video capture using the camera specified.
		*/
		virtual void stopVideoCapture() TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract takeScreenshot
		  @discussion Takes a screen shot of the visible UI on the device.
		*/
		virtual void takeScreenshot(JSValue callback) TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract vibrate
		  @discussion Makes the device vibrate.
		*/
		virtual void vibrate(std::vector<std::chrono::milliseconds> pattern) TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract hasCameraPermissions
		  @discussion Returns true if the app has camera access.
		*/
		virtual bool hasCameraPermissions() TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract requestCameraPermissions
		  @discussion Requests for camera access.
		*/
		virtual void requestCameraPermissions(JSValue callback) TITANIUM_NOEXCEPT override;

		MediaModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~MediaModule();
		MediaModule(const MediaModule&) = default;
		MediaModule& operator=(const MediaModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		MediaModule(MediaModule&&) = default;
		MediaModule& operator=(MediaModule&&) = default;
#endif

		static void JSExportInitialize();

		virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
		virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

		void fireMediaVolumeEvent(const Windows::Media::SoundLevel& level);

		TITANIUM_FUNCTION_DEF(_postOpenPhotoGallery);
		TITANIUM_FUNCTION_DEF(_postOpenMusicLibrary);
		TITANIUM_FUNCTION_DEF(_postShowCamera);

	protected:

		JSFunction createFileOpenForMusicLibraryFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT;
		JSFunction createFileOpenForPhotoGalleryFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT;
		JSFunction createBeepFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT;
		void takeScreenshotDone(JSObject callback, const std::string& file = "", const bool& hasError = true);
		void clearScreenshotResources();
		void takeScreenshotToFile(JSObject callback);

		void focus(const Titanium::Media::CameraOptionsType&, const bool& reportError = true) TITANIUM_NOEXCEPT;

#if !defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
		void showDefaultCamera(const Titanium::Media::CameraOptionsType& options) TITANIUM_NOEXCEPT;
#endif

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
		void updatePreviewOrientation();
#endif
		void findCameraDevices();
		Windows::Storage::FileProperties::PhotoOrientation toPhotoOrientation();
		std::uint32_t orientationToDegrees();

		std::vector<std::shared_ptr<Titanium::Media::Item>> getMusicProperties(const std::vector<std::string>& files);

#pragma warning(push)
#pragma warning(disable : 4251)
		Windows::Foundation::EventRegistrationToken audioMonitoring_token__;
		bool waitingForOpenMusicLibrary__ { false };
		bool waitingForOpenPhotoGallery__ { false };
		bool isFrontCameraSelected__{ false };
		Titanium::Media::PhotoGalleryOptionsType openPhotoGalleryOptionsState__;
		Titanium::Media::MusicLibraryOptionsType openMusicLibraryOptionsState__;
		JSFunction js_beep__;
		Windows::Devices::Enumeration::DeviceInformationCollection^ cameraDevices__{ nullptr };
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
		Titanium::Media::CameraOptionsTypeCallbacks cameraCallbacks__;
		std::shared_ptr<Titanium::UI::View> cameraOverlay__;
		bool screenCaptureStarted__{ false };
		bool cameraPreviewStarted__ { false };
		bool shouldHideAfterTakingShot__{ false };
		bool shouldRemoveRotationEvent__{ false };
		JSFunction fileOpenForMusicLibraryCallback__;
		JSFunction fileOpenForPhotoGalleryCallback__;
		::Platform::Agile<Windows::Media::Capture::MediaCapture> mediaCapture__;
		::Platform::Collections::Vector<Windows::UI::Xaml::DispatcherTimer^>^ vibrate_timers__;
		Windows::UI::Xaml::Controls::CaptureElement^ captureElement__;
		Windows::Foundation::EventRegistrationToken camera_navigated_event__;
		Windows::Foundation::EventRegistrationToken camera_orientation_event__;
		TakingPictureState^ takingPictureState__;
#endif
#pragma warning(pop)
	};

}  

#endif  // _TITANIUMWINDOWS_MEDIAMODULE_HPP_
