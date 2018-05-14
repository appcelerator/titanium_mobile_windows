/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Media.hpp"
#include "TitaniumWindows/Filesystem.hpp"
#include "Titanium/Filesystem/File.hpp"
#include "Titanium/Media/Constants.hpp"
#include "Titanium/Media/Item.hpp"
#include "Titanium/Media/CameraOptionsType.hpp"
#include "Titanium/Media/MediaQueryType.hpp"
#include "Titanium/UI/OpenWindowParams.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <windows.h>
#include <ppltasks.h>
#include <collection.h>
#include <concrt.h>
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/LogForwarder.hpp"
#include "TitaniumWindows/AppModule.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include "TitaniumWindows/Blob.hpp"

#define GET_TITANIUM_APP(VARNAME) \
  const auto ctx = get_context(); \
  JSValue Titanium_property = ctx.get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue App_property = Titanium.GetProperty("App"); \
  TITANIUM_ASSERT(App_property.IsObject()); \
  std::shared_ptr<TitaniumWindows::AppModule> VARNAME = static_cast<JSObject>(App_property).GetPrivate<TitaniumWindows::AppModule>();

#define GENERATE_TI_ERROR_RESPONSE(MESSAGE, VARNAME) \
Titanium::ErrorResponse VARNAME; \
VARNAME.code = -1; \
VARNAME.error = MESSAGE; \
VARNAME.success = false;

namespace TitaniumWindows
{
	using namespace Windows::Foundation;
	using namespace Windows::Storage;
	using namespace Windows::Storage::Pickers;
	using namespace Windows::Media;
	using namespace Windows::Media::Capture;
	using namespace Windows::Media::MediaProperties;
	using namespace Windows::Media::Devices;
	using namespace Windows::Devices::Enumeration;
	using namespace Windows::UI::Xaml;
	using namespace Windows::UI::Xaml::Controls;
	using namespace Platform::Collections;
	using namespace Windows::Foundation::Collections;
	using namespace Windows::Graphics::Display;
	using namespace Windows::Graphics::Imaging;
	using namespace Windows::Storage;
	using namespace Windows::Storage::Search;
	using namespace concurrency;

	JSFunction MediaModule::createFileOpenForPhotoGalleryFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT
	{
		return js_context.CreateFunction(R"JS(
			Ti.App.removeEventListener('windows.fileOpenFromPicker', this);
			Ti.Media._postOpenPhotoGallery(e.files);
		)JS", { "e" });
	}

	JSFunction MediaModule::createFileOpenForMusicLibraryFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT
	{
		return js_context.CreateFunction(R"JS(
			Ti.App.removeEventListener('windows.fileOpenFromPicker', this);
			Ti.Media._postOpenMusicLibrary(e.files);
		)JS", { "e" });
	}

	JSFunction MediaModule::createBeepFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT
	{
		// Play beep.wav under application directory
		return js_context.CreateFunction(R"JS(
			Ti.Media.createSound({url:'beep.wav'}).play();
		)JS");
	}

	void MediaModule::beep() TITANIUM_NOEXCEPT
	{
		js_beep__(get_object());
	}

	void MediaModule::openMusicLibrary(const Titanium::Media::MusicLibraryOptionsType& options) TITANIUM_NOEXCEPT
	{
		auto picker = ref new FileOpenPicker();
		picker->ViewMode = PickerViewMode::Thumbnail;
		picker->SuggestedStartLocation = PickerLocationId::MusicLibrary;
		//
		// https://msdn.microsoft.com/en-us/library/windows/apps/xaml/dn639127.aspx
		//
		picker->FileTypeFilter->Append(".qcp");
		picker->FileTypeFilter->Append(".wav");
		picker->FileTypeFilter->Append(".mp3");
		picker->FileTypeFilter->Append(".m4r");
		picker->FileTypeFilter->Append(".m4a");
		picker->FileTypeFilter->Append(".aac");
		picker->FileTypeFilter->Append(".amr");
		picker->FileTypeFilter->Append(".wma");
		picker->FileTypeFilter->Append(".3g2");
		picker->FileTypeFilter->Append(".3gp");
		picker->FileTypeFilter->Append(".mp4");
		picker->FileTypeFilter->Append(".wm");
		picker->FileTypeFilter->Append(".asf");
		picker->FileTypeFilter->Append(".3gpp");
		picker->FileTypeFilter->Append(".3gp2");
		picker->FileTypeFilter->Append(".mpa");
		picker->FileTypeFilter->Append(".adt");
		picker->FileTypeFilter->Append(".adts");
		picker->FileTypeFilter->Append(".pya");

		openMusicLibraryOptionsState__ = options;
		waitingForOpenMusicLibrary__ = true;

		if (options.allowMultipleSelections) {
			task<IVectorView<StorageFile^>^>(picker->PickMultipleFilesAsync()).then([this, options](task<IVectorView<StorageFile^>^> task) {
				try {
					std::vector<std::string> files;
					const auto storages = task.get();
					for (const auto file : storages) {
						files.push_back(TitaniumWindows::Utility::ConvertString(file->Path));
					}
					_postOpenMusicLibrary(files);
				} catch (Platform::Exception^ ex) {
					TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
				} catch (...) {
					TITANIUM_LOG_DEBUG("Unknown error while openMusicLibrary");
				}
			});
		} else {
			task<StorageFile^>(picker->PickSingleFileAsync()).then([this, options](task<StorageFile^> task) {
				try {
					std::vector<std::string> files;
					const auto file = task.get();
					if (file != nullptr) {
						files.push_back(TitaniumWindows::Utility::ConvertString(file->Path));
					}
					_postOpenMusicLibrary(files);
				} catch (Platform::Exception^ ex) {
					TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
				} catch (...) {
					TITANIUM_LOG_DEBUG("Unknown error while openMusicLibrary");
				}
			});
		}
	}

	std::shared_ptr<Titanium::Media::Item> getMediaItem(const JSContext& js_context, StorageFile^ file) 
	{
		std::shared_ptr<Titanium::Media::Item> item = js_context.CreateObject(JSExport<Titanium::Media::Item>::Class()).GetPrivate<Titanium::Media::Item>();
		concurrency::event event;
		concurrency::task<FileProperties::MusicProperties^>(file->Properties->GetMusicPropertiesAsync()).then([&js_context, &item, &event](concurrency::task<FileProperties::MusicProperties^> task) {
			try {
				const auto properties = task.get();

				item->set_artist(TitaniumWindows::Utility::ConvertString(properties->Artist));
				item->set_albumTitle(TitaniumWindows::Utility::ConvertString(properties->Album));
				item->set_composer(TitaniumWindows::Utility::ConvertString(properties->Composers));
				item->set_playbackDuration(TitaniumWindows::Utility::GetSec(properties->Duration));
				item->set_genre(TitaniumWindows::Utility::ConvertString(properties->Genre));
				item->set_rating(properties->Rating);
				item->set_title(TitaniumWindows::Utility::ConvertString(properties->Title));
				item->set_albumTrackNumber(properties->TrackNumber);
			} catch (Platform::Exception^ e) {
				TITANIUM_MODULE_LOG_WARN("MediaModule: Failed to get music properties: ", TitaniumWindows::Utility::ConvertString(e->Message));
			} catch (...) {
				TITANIUM_MODULE_LOG_WARN("MediaModule: Failed to get music properties");
			}
			event.set();
		});
		event.wait();

		return item;
	}

	std::vector<std::shared_ptr<Titanium::Media::Item>> MediaModule::getMusicProperties(const std::vector<std::string>& files) 
	{
		const auto ctx = get_context();
		std::vector<std::shared_ptr<Titanium::Media::Item>> items;
		for (const auto file : files) {
			concurrency::event event;
			task<StorageFile^>(StorageFile::GetFileFromPathAsync(TitaniumWindows::Utility::ConvertString(files.at(0)))).then([&items, &ctx, &event](task<StorageFile^> task) {
				try {
					items.push_back(getMediaItem(ctx, task.get()));
				} catch (Platform::Exception^ e) {
					TITANIUM_MODULE_LOG_WARN("MediaModule: Failed to access music file: ", TitaniumWindows::Utility::ConvertString(e->Message));
				} catch (...) {
					TITANIUM_MODULE_LOG_WARN("MediaModule: Failed to access music file");
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();
		}
		return items;
	}

	void MediaModule::_postOpenMusicLibrary(const std::vector<std::string>& files) TITANIUM_NOEXCEPT
	{
		if (!waitingForOpenMusicLibrary__) {
			TITANIUM_LOG_WARN("MediaModule::_postOpenMusicLibrary: Invalid state");
			return;
		}

		if (files.size() > 0) {
				Titanium::Media::MusicLibraryResponseType item;
				item.types = { Titanium::Media::MusicMediaType::Music };
				item.items = getMusicProperties(files);

				if (item.items.size() == 0) {
					GENERATE_TI_ERROR_RESPONSE("Failed to read music properties from file", error);
					openMusicLibraryOptionsState__.callbacks.onerror(error);
				} else {
					item.representative = item.items.at(0);
					openMusicLibraryOptionsState__.callbacks.onsuccess(item);
				}
		} else {
			// files.size() == 0 means FileOpenPicker is canceled
			GENERATE_TI_ERROR_RESPONSE("File picker is canceled", error);
			openMusicLibraryOptionsState__.callbacks.oncancel(error);
		}

		// reset state
		openMusicLibraryOptionsState__ = Titanium::Media::create_empty_MusicLibraryOptionsType(get_context());
		waitingForOpenMusicLibrary__ = false;
	}

	void MediaModule::openPhotoGallery(const Titanium::Media::PhotoGalleryOptionsType& options) TITANIUM_NOEXCEPT
	{
		auto picker = ref new FileOpenPicker();
		picker->ViewMode = PickerViewMode::Thumbnail;
		picker->SuggestedStartLocation = PickerLocationId::PicturesLibrary;
		//
		// https://msdn.microsoft.com/en-us/library/windows/apps/xaml/dn639127.aspx
		//
		picker->FileTypeFilter->Append(".jpeg");
		picker->FileTypeFilter->Append(".jpe");
		picker->FileTypeFilter->Append(".jpg");
		picker->FileTypeFilter->Append(".gif");
		picker->FileTypeFilter->Append(".tiff");
		picker->FileTypeFilter->Append(".tif");
		picker->FileTypeFilter->Append(".png");
		picker->FileTypeFilter->Append(".bmp");
		picker->FileTypeFilter->Append(".wdp");
		picker->FileTypeFilter->Append(".jxr");
		picker->FileTypeFilter->Append(".hdp");

		openPhotoGalleryOptionsState__ = options;
		waitingForOpenPhotoGallery__ = true;

		task<StorageFile^>(picker->PickSingleFileAsync()).then([this](task<StorageFile^> task) {
			try {
				std::vector<std::string> files;
				const auto file = task.get();
				if (file != nullptr) {
					files.push_back(TitaniumWindows::Utility::ConvertString(file->Path));
				}
				_postOpenPhotoGallery(files);
			} catch (Platform::Exception^ ex) {
				TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
			} catch (...) {
				TITANIUM_LOG_DEBUG("Unknown error while openPhotoGallery");
			}
		});
	}

	void MediaModule::_postOpenPhotoGallery(const std::vector<std::string>& files) TITANIUM_NOEXCEPT
	{
		if (!waitingForOpenPhotoGallery__) {
			TITANIUM_LOG_WARN("MediaModule::_postOpenPhotoGallery: Invalid state");
			return;
		}

		if (files.size() > 0) {
			const auto filename = files.at(0);
			if (!filename.empty()) {
				Titanium::Media::CameraMediaItemType item;
				item.code = 0;
				item.success = true;
				item.mediaType = Titanium::Media::MediaType::Photo;
				item.media_filename = filename;
				openPhotoGalleryOptionsState__.callbacks.onsuccess(item);
			} else {
				GENERATE_TI_ERROR_RESPONSE("Failed to load content from file", error);
				openPhotoGalleryOptionsState__.callbacks.onerror(error);
			}
		} else {
			// files.size() == 0 means FileOpenPicker is canceled
			GENERATE_TI_ERROR_RESPONSE("File picker is canceled", error);
			openPhotoGalleryOptionsState__.callbacks.oncancel(error);
		}

		// reset state
		openPhotoGalleryOptionsState__ = Titanium::Media::create_empty_PhotoGalleryOptionsType(get_context());
		waitingForOpenPhotoGallery__ = false;
	}

	void MediaModule::findCameraDevices()
	{
		if (cameraDevices__ == nullptr) {
			concurrency::event event;
			task<DeviceInformationCollection^>(DeviceInformation::FindAllAsync(DeviceClass::VideoCapture)).then([this, &event](task<DeviceInformationCollection^> task) {
				try {
					cameraDevices__ = task.get();
				} catch (Platform::Exception^ ex) {
					TITANIUM_LOG_WARN(TitaniumWindows::Utility::ConvertString(ex->Message));
				} catch (...) {
					TITANIUM_LOG_DEBUG("Unknown error while findCameraDevices");
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();
		}
	}

	bool MediaModule::isMediaTypeSupported(const std::string& source, const Titanium::Media::MediaType& type) TITANIUM_NOEXCEPT
	{
		if (source == "camera") {
			findCameraDevices();

			// Looks like there's no difference between "video" and "camera" in DeviceInformation...
			// Assuming "VideoCapture" device supports both camera and video. 
			return cameraDevices__->Size > 0;
		} else if (source == "photo") {
			// Does Photo Library support both picture and video? There's no way to query that.
			return true;
		}
		return false;
	}


	void MediaModule::saveToPhotoGallery(const std::shared_ptr<Titanium::Blob>& blob, JSValue callbacks) TITANIUM_NOEXCEPT
	{
		const auto ctx = get_context();

		auto onSuccess = ctx.CreateObject();
		auto onError = ctx.CreateObject();

		if (callbacks.IsObject()) {
			const auto callbacksObj = static_cast<JSObject>(callbacks);
			if (callbacksObj.HasProperty("success")) {
				const auto success = callbacksObj.GetProperty("success");
				if (success.IsObject()) {
					onSuccess = static_cast<JSObject>(success);
				}
			}
			if (callbacksObj.HasProperty("error")) {
				const auto error = callbacksObj.GetProperty("error");
				if (error.IsObject()) {
					onError = static_cast<JSObject>(error);
				}
			}
		}

		auto destinationPath = Windows::Storage::KnownFolders::PicturesLibrary->Path;

		// On Windows Store app, path for the PicturesLibrary may become nullptr.
		// Workaround there is to create empty file and retrieve path from it.
		if (destinationPath == nullptr) {
			concurrency::event evt;
			const auto desiredName = TitaniumWindows::Utility::ConvertString(blob->get_file() ? blob->get_file()->get_name() : std::string("photo.bmp"));
			concurrency::task<StorageFile^>(Windows::Storage::KnownFolders::PicturesLibrary->CreateFileAsync(desiredName,
				CreationCollisionOption::GenerateUniqueName)).then([&destinationPath, &evt](concurrency::task<StorageFile^> task) {
				try {
					destinationPath = task.get()->Path;
				} catch (...) {
					destinationPath = nullptr;
				}
				evt.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			evt.wait();
		}

		boolean result = false;
		std::string path = TitaniumWindows::Utility::ConvertString(destinationPath);

		if (blob->get_file()) {
			result = blob->get_file()->copy(path);
		} else {
			const auto js_filesystem = ctx.CreateObject(JSExport<Titanium::FilesystemModule>::Class()).CallAsConstructor();
			const auto filesystem_obj = static_cast<JSObject>(js_filesystem).CallAsConstructor();
			const auto filesystem = filesystem_obj.GetPrivate<Titanium::FilesystemModule>();
			const auto file = filesystem->getFile(ctx, path);
			result = file->write(blob, false);
		}
		if (result) {
			if (onSuccess.IsFunction()) {
				auto arg = ctx.CreateObject();
				arg.SetProperty("success", ctx.CreateBoolean(true));
				arg.SetProperty("code", ctx.CreateNumber(0));
				onSuccess({ arg }, get_object());
			}
		} else {
			if (onError.IsFunction()) {
				auto arg = ctx.CreateObject();
				arg.SetProperty("success", ctx.CreateBoolean(true));
				arg.SetProperty("code", ctx.CreateNumber(-1));
				arg.SetProperty("message", ctx.CreateString("Failed to save file to Pictures Library"));
				onError({ arg }, get_object());
			}
		}
	}

	void MediaModule::saveToPhotoGallery(const std::shared_ptr<Titanium::Filesystem::File>& file, JSValue callbacks) TITANIUM_NOEXCEPT
	{
		return saveToPhotoGallery(file->read(), callbacks);
	}

	void MediaModule::hideCamera() TITANIUM_NOEXCEPT
	{
		hideCamera(nullptr);
	}

	void MediaModule::hideCamera(std::function<void()> callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT_AND_THROW(cameraPreviewStarted__, "Camera is not visiable. Use showCamera() to show camera.");
		if (!cameraPreviewStarted__) {
			return;
		}
		concurrency::create_task(mediaCapture__->StopPreviewAsync()).then([this, callback](concurrency::task<void> stopTask) {
			try {
				stopTask.get();
			} catch (Platform::Exception^ e) {
				TITANIUM_MODULE_LOG_WARN("MediaModule: Failed to stop camera preview: ", TitaniumWindows::Utility::ConvertString(e->Message));
			} catch (...) {
				TITANIUM_MODULE_LOG_WARN("MediaModule: Failed to stop camera preview");
			}

			if (cameraOptionsState__.overlay) {
				const std::vector<JSValue> remove_args = { cameraOptionsState__.overlay->get_object() };
				auto window = static_cast<JSObject>(get_context().JSEvaluateScript("Ti.UI.currentWindow"));
				static_cast<JSObject>(window.GetProperty("remove"))(remove_args, window);
			}

			if (shouldRemoveRotationEvent__) {
				DisplayInformation::GetForCurrentView()->OrientationChanged -= camera_orientation_event__;
				shouldRemoveRotationEvent__ = false;
			}

			TitaniumWindows::Utility::RemoveViewFromCurrentWindow(captureElement__, [this, callback]() {
				// Close preview Window
				get_context().JSEvaluateScript("Ti.UI.currentWindow.close();");

				if (callback) {
					callback();
				}

				// Clear showCamera state
				cameraOptionsState__ = Titanium::Media::create_empty_CameraOptionsType(get_context());

				takingPictureState__ = nullptr;

				captureElement__->Source = nullptr;
				cameraPreviewStarted__ = false;
				delete(mediaCapture__.Get());
			});
		});
	}

	FileProperties::PhotoOrientation MediaModule::toPhotoOrientation()
	{
		if (isFrontCameraSelected__) {
			switch (DisplayInformation::GetForCurrentView()->CurrentOrientation)
			{
			case DisplayOrientations::Portrait:
				return FileProperties::PhotoOrientation::Rotate90;
			case DisplayOrientations::Landscape:
				return FileProperties::PhotoOrientation::Rotate180;
			case DisplayOrientations::PortraitFlipped:
				return FileProperties::PhotoOrientation::Rotate270;
			case DisplayOrientations::LandscapeFlipped:
			default:
				return FileProperties::PhotoOrientation::Normal;
			}
		} else {
			switch (DisplayInformation::GetForCurrentView()->CurrentOrientation)
			{
			case DisplayOrientations::Portrait:
				return FileProperties::PhotoOrientation::Rotate270;
			case DisplayOrientations::LandscapeFlipped:
				return FileProperties::PhotoOrientation::Rotate180;
			case DisplayOrientations::PortraitFlipped:
				return FileProperties::PhotoOrientation::Rotate90;
			case DisplayOrientations::Landscape:
			default:
				return FileProperties::PhotoOrientation::Normal;
			}
		}
	}

	std::uint32_t MediaModule::orientationToDegrees()
	{
		switch (DisplayInformation::GetForCurrentView()->CurrentOrientation) {
		case DisplayOrientations::Portrait:
			return 90;
		case DisplayOrientations::LandscapeFlipped:
			return 180;
		case DisplayOrientations::PortraitFlipped:
			return 270;
		case DisplayOrientations::Landscape:
		default:
			return 0;
		}
	}

	void MediaModule::updatePreviewOrientation()
	{
		// Set rotation for preview
		const GUID RotationKey = { 0xC380465D, 0x2271, 0x428C, { 0x9B, 0x83, 0xEC, 0xEA, 0x3B, 0x4A, 0x85, 0xC1 } };
		const auto props = mediaCapture__->VideoDeviceController->GetMediaStreamProperties(Windows::Media::Capture::MediaStreamType::VideoPreview);
		props->Properties->Insert(RotationKey, orientationToDegrees());
		mediaCapture__->SetEncodingPropertiesAsync(Windows::Media::Capture::MediaStreamType::VideoPreview, props, nullptr);
	}

	void MediaModule::showDefaultCamera(const Titanium::Media::CameraOptionsType& options) TITANIUM_NOEXCEPT
	{
		auto cameraCaptureUI = ref new CameraCaptureUI();

		const auto isVideoSelected = std::find(options.mediaTypes.begin(), options.mediaTypes.end(), Titanium::Media::MediaType::Video) != options.mediaTypes.end();
		CameraCaptureUIMode captureMode;

		if (isVideoSelected) {
			// Setup video settings
			cameraCaptureUI->VideoSettings->Format = CameraCaptureUIVideoFormat::Mp4;
			if (options.videoMaximumDuration.count() > 0) {
				cameraCaptureUI->VideoSettings->MaxDurationInSeconds = static_cast<float>(std::chrono::duration_cast<std::chrono::seconds>(options.videoMaximumDuration).count());
			}
			if (options.videoQuality == Titanium::Media::Quality::High) {
				cameraCaptureUI->VideoSettings->MaxResolution = CameraCaptureUIMaxVideoResolution::HighDefinition;
			} else if (options.videoQuality == Titanium::Media::Quality::Medium) {
				cameraCaptureUI->VideoSettings->MaxResolution = CameraCaptureUIMaxVideoResolution::StandardDefinition;
			} else if (options.videoQuality == Titanium::Media::Quality::Low) {
				cameraCaptureUI->VideoSettings->MaxResolution = CameraCaptureUIMaxVideoResolution::LowDefinition;
			}
			captureMode = CameraCaptureUIMode::Video;
		} else {
			if (options.photoAspectRatio.width > 0 && options.photoAspectRatio.height > 0) {
				cameraCaptureUI->PhotoSettings->CroppedAspectRatio = Size(static_cast<float>(options.photoAspectRatio.width), static_cast<float>(options.photoAspectRatio.height));
			} else {
				cameraCaptureUI->PhotoSettings->CroppedAspectRatio = Size(4, 3);
			}
			captureMode = CameraCaptureUIMode::Photo;
		}

		concurrency::create_task(cameraCaptureUI->CaptureFileAsync(captureMode)).then([options, isVideoSelected, this](concurrency::task<StorageFile^> task) {
			try {
				auto fromFile = task.get();
				if (fromFile != nullptr) {
					if (options.saveToPhotoGallery) {
						const auto createFile = isVideoSelected ? 
							KnownFolders::VideosLibrary->CreateFileAsync("TiMediaVideo.mp4", CreationCollisionOption::GenerateUniqueName) : 
							KnownFolders::CameraRoll->CreateFileAsync("TiMediaPhoto.jpg", CreationCollisionOption::GenerateUniqueName);
						// CameraCaptureUI saves video/picture into temporary folder. Let's move it to video/photo library then.
						concurrency::task<StorageFile^>(createFile).then([fromFile, isVideoSelected, options](concurrency::task<Windows::Storage::StorageFile^> task) {
							try {
								auto toFile = task.get();
								concurrency::create_task(fromFile->MoveAndReplaceAsync(toFile)).then([toFile, isVideoSelected, options](concurrency::task<void> task) {
									try {
										task.get();
										Titanium::Media::CameraMediaItemType item;
										item.mediaType = isVideoSelected ? Titanium::Media::MediaType::Video : Titanium::Media::MediaType::Photo;
										item.media_filename = TitaniumWindows::Utility::ConvertString(toFile->Path);
										options.callbacks.onsuccess(item);
									} catch (Platform::Exception^ e) {
										GENERATE_TI_ERROR_RESPONSE(TitaniumWindows::Utility::ConvertString(e->Message), error);
										options.callbacks.onerror(error);
									} catch (...) {
										GENERATE_TI_ERROR_RESPONSE("Unknown error", error);
										options.callbacks.onerror(error);
									}
								});
							} catch (Platform::Exception^ e) {
								GENERATE_TI_ERROR_RESPONSE(TitaniumWindows::Utility::ConvertString(e->Message), error);
								options.callbacks.onerror(error);
							} catch (...) {
								GENERATE_TI_ERROR_RESPONSE("Unknown error", error);
								options.callbacks.onerror(error);
							}
						});
					} else {
						Titanium::Media::CameraMediaItemType item;
						item.mediaType = isVideoSelected ? Titanium::Media::MediaType::Video : Titanium::Media::MediaType::Photo;
						item.media_filename = TitaniumWindows::Utility::ConvertUTF8String(fromFile->Path);
						options.callbacks.onsuccess(item);
					}
				} else {
					// This indicates camera capture is cancelled
					GENERATE_TI_ERROR_RESPONSE("Camera capture is canceled", error);
					options.callbacks.oncancel(error);
				}
			} catch (Platform::Exception^ e) {
				GENERATE_TI_ERROR_RESPONSE(TitaniumWindows::Utility::ConvertString(e->Message), error);
				options.callbacks.onerror(error);
			} catch (...) {
				GENERATE_TI_ERROR_RESPONSE("Unknown error", error);
				options.callbacks.onerror(error);
			}
		});
	}

	void MediaModule::focus(const Titanium::Media::CameraOptionsType& options, const bool& reportError) TITANIUM_NOEXCEPT
	{
		concurrency::create_task(mediaCapture__->VideoDeviceController->FocusControl->UnlockAsync()).then([this, options, reportError](concurrency::task<void> task) {
			try {
				task.get();
				const auto settings = ref new FocusSettings();
				settings->AutoFocusRange = AutoFocusRange::Normal;
				settings->Mode = FocusMode::Auto;
				settings->WaitForFocus = true;
				settings->DisableDriverFallback = false;
				mediaCapture__->VideoDeviceController->FocusControl->Configure(settings);
				mediaCapture__->VideoDeviceController->FocusControl->FocusAsync();
			} catch (Platform::Exception^ e) {
				if (reportError) {
					GENERATE_TI_ERROR_RESPONSE(TitaniumWindows::Utility::ConvertString(e->Message), error);
					options.callbacks.onerror(error);
				}
			} catch (...) {
				if (reportError) {
					GENERATE_TI_ERROR_RESPONSE("Unknown error", error);
					options.callbacks.onerror(error);
				}
			}
		});
	}

	void MediaModule::showCamera(const Titanium::Media::CameraOptionsType& options) TITANIUM_NOEXCEPT
	{

		cameraOptionsState__ = options;
		// If There's no overlay on Windows 10 (Mobile), let's use CameraCaptureUI.
		if (options.overlay == nullptr) {
			showDefaultCamera(options);
			return;
		}

		if (cameraPreviewStarted__) {
			TITANIUM_MODULE_LOG_WARN("Failed to showCamera(): Camera is already visible.");
			return;
		}

		TITANIUM_ASSERT_AND_THROW(!screenCaptureStarted__, "Can't be used during screen capture.");

		const auto isVideoSelected = std::find(options.mediaTypes.begin(), options.mediaTypes.end(), Titanium::Media::MediaType::Video) != options.mediaTypes.end();

		findCameraDevices();
		mediaCapture__ = ref new MediaCapture();
		auto settings = ref new MediaCaptureInitializationSettings();
		// If not capturing video, don't require audio. This way we don't need "microphone" capability to take a picture
		if (!isVideoSelected) {
			settings->AudioDeviceId = "";
			settings->StreamingCaptureMode = StreamingCaptureMode::Video;
		} else {
			settings->StreamingCaptureMode = StreamingCaptureMode::AudioAndVideo;
		}

		// Indicate if front camera is selected
		isFrontCameraSelected__ = false;

		// set default camera
		Platform::String^ defaultCameraId = nullptr;
		for (auto camera : cameraDevices__) {
			const auto name = TitaniumWindows::Utility::ConvertString(camera->Name);
			const auto isFrontCamera = name.find("Front") != std::string::npos;
			const auto isBackCamera = (name.find("Back") != std::string::npos) || (name.find("Rear") != std::string::npos);

			if ((options.whichCamera == Titanium::Media::CameraOption::Front && isFrontCamera) ||
				(options.whichCamera == Titanium::Media::CameraOption::Rear && isBackCamera)) {
				defaultCameraId = camera->Id;
				isFrontCameraSelected__ = isFrontCamera && options.whichCamera == Titanium::Media::CameraOption::Front;
				break;
			}
			if (camera->IsDefault || isBackCamera) {
				defaultCameraId = camera->Id;
				isFrontCameraSelected__ = isFrontCamera && options.whichCamera == Titanium::Media::CameraOption::Front;
			}
		}
		if (defaultCameraId) {
			settings->VideoDeviceId = defaultCameraId;
		}

		// For tap-to-focus
		captureElement__->Tapped += ref new Input::TappedEventHandler([this, options](Platform::Object^ sender, Input::TappedRoutedEventArgs^ e) {
			// Don't fire onerror callback on tap-to-focus
			focus(options, false);
		});

		if (options.autorotate) {
			camera_orientation_event__ = DisplayInformation::GetForCurrentView()->OrientationChanged += 
				ref new TypedEventHandler<DisplayInformation^, Platform::Object^>([this](DisplayInformation^ sender, Platform::Object^ args) {
				updatePreviewOrientation();

				const auto currentBounds = Windows::UI::Xaml::Window::Current->Bounds;
				captureElement__->Width = currentBounds.Width;
				captureElement__->Height = currentBounds.Height;
			});
			shouldRemoveRotationEvent__ = true;
		}

		concurrency::create_task(mediaCapture__->InitializeAsync(settings)).then([options, this](concurrency::task<void> initTask) {
			try {
				initTask.get();
				auto mediaCapture = mediaCapture__.Get();
				captureElement__->Source = mediaCapture;
				this->cameraPreviewStarted__ = true;

				if (isFrontCameraSelected__) {
					mediaCapture__->SetPreviewRotation(VideoRotation::Clockwise180Degrees);
				}

				concurrency::create_task(mediaCapture->StartPreviewAsync()).then([options, this](concurrency::task<void> previewTask) {
					try {
						updatePreviewOrientation();

						previewTask.get();
					} catch (Platform::Exception^ e) {
						GENERATE_TI_ERROR_RESPONSE("Ti.Media.showCamera() failed to start preview: " + TitaniumWindows::Utility::ConvertString(e->Message), error);
						options.callbacks.onerror(error);
					} catch (...) {
						GENERATE_TI_ERROR_RESPONSE("Ti.Media.showCamera() failed to start preview", error);
						options.callbacks.onerror(error);
					}
				});
			} catch (Platform::Exception^ e) {
				GENERATE_TI_ERROR_RESPONSE("Ti.Media.showCamera() failed to initialize capture device: " + TitaniumWindows::Utility::ConvertString(e->Message), error);
				options.callbacks.onerror(error);
			} catch (...) {
				GENERATE_TI_ERROR_RESPONSE("Ti.Media.showCamera() failed to initialize capture device", error);
				options.callbacks.onerror(error);
			}
		});

		if (options.overlay) {
			// Open new Window, and add camera preview on _postShowCamera()
			auto window = static_cast<JSObject>(get_context().JSEvaluateScript(
				R"js(
				  (function(global) {
				    var win = Ti.UI.createWindow({backgroundColor:'transparent'});
				     win.addEventListener('open', function() {
				       Ti.Media._postShowCamera();
					 });
					return win;
				  })(this);
				)js"
			));
			static_cast<JSObject>(window.GetProperty("open"))(window);
		}
	}

	void MediaModule::_postShowCamera() TITANIUM_NOEXCEPT
	{
		TitaniumWindows::Utility::SetViewForCurrentWindow(captureElement__, camera_navigated_event__, /* visible */ true, /* fullscreen */ true);

		if (cameraOptionsState__.overlay) {
			// Add overlay view to new Window. Running on UI thread to make sure it's done on UI thread after SetViewForCurrentWindow.
			TitaniumWindows::Utility::RunOnUIThread([this]() {
				auto window = static_cast<JSObject>(get_context().JSEvaluateScript("Ti.UI.currentWindow;"));
				const std::vector<JSValue> add_args = { cameraOptionsState__.overlay->get_object() };
				static_cast<JSObject>(window.GetProperty("add"))(add_args, window);
			});
		}
	}

	void MediaModule::fireMediaVolumeEvent(const SoundLevel& level) 
	{
		// There's only three level on Windows: Muted, Low and Full.
		// TODO: Find reasonable number for volume. Right now it's mapped to Muted=0, Low=0.5 and Full=1.
		const auto ctx = get_context();
		auto obj = ctx.CreateObject();
		switch (level) {
		case SoundLevel::Muted:
			obj.SetProperty("volume", ctx.CreateNumber(0));
			break;
		case SoundLevel::Low:
			obj.SetProperty("volume", ctx.CreateNumber(0.5));
			break;
		case SoundLevel::Full:
			obj.SetProperty("volume", ctx.CreateNumber(1));
			break;
		default:
			TITANIUM_MODULE_LOG_WARN("MediaModule: Unknown volume");
			obj.SetProperty("volume", ctx.CreateNumber(0));
			break;
		}
		fireEvent("volume", obj);
	}

	void MediaModule::startMicrophoneMonitor() TITANIUM_NOEXCEPT
	{
		SystemMediaTransportControls^ systemMediaControls = SystemMediaTransportControls::GetForCurrentView();
		audioMonitoring_token__ = systemMediaControls->PropertyChanged += ref new TypedEventHandler<SystemMediaTransportControls^, SystemMediaTransportControlsPropertyChangedEventArgs^>([this](SystemMediaTransportControls^ sender, SystemMediaTransportControlsPropertyChangedEventArgs^ e) {
			switch (e->Property) {
			case SystemMediaTransportControlsProperty::SoundLevel:
				fireMediaVolumeEvent(sender->SoundLevel);
				break;
			default:
				break;
			}
		});
	}

	void MediaModule::stopMicrophoneMonitor() TITANIUM_NOEXCEPT
	{
		SystemMediaTransportControls^ systemMediaControls = SystemMediaTransportControls::GetForCurrentView();
		systemMediaControls->PropertyChanged -= audioMonitoring_token__;
	}

	void MediaModule::takePicture() TITANIUM_NOEXCEPT
	{
		takingPictureState__ = ref new TakingPictureState();
		takingPictureState__->orientation = toPhotoOrientation();

		auto instream = ref new Streams::InMemoryRandomAccessStream();

		// TODO: Provide an API to customize capture settings
		ImageEncodingProperties^ properties = ImageEncodingProperties::CreateJpeg();
		concurrency::create_task(mediaCapture__->CapturePhotoToStreamAsync(properties, instream)).then([instream]() {
			return concurrency::create_task(BitmapDecoder::CreateAsync(instream));
		}).then([this](BitmapDecoder^ decoder) {
			takingPictureState__->decoder = decoder;
			// CreationCollisionOption::GenerateUniqueName generates unique name such as "TiMediaPhoto (2).jpg"
			if (cameraOptionsState__.saveToPhotoGallery) {
				return KnownFolders::CameraRoll->CreateFileAsync("TiMediaPhoto.jpg", CreationCollisionOption::GenerateUniqueName);
			} else {
				return Windows::Storage::ApplicationData::Current->TemporaryFolder->CreateFileAsync("TiMediaPhoto.jpg", CreationCollisionOption::GenerateUniqueName);
			}
		}).then([this](StorageFile^ file) {
			takingPictureState__->file = file;
			return concurrency::create_task(takingPictureState__->file->OpenAsync(FileAccessMode::ReadWrite));
		}).then([this](Streams::IRandomAccessStream^ outstream) {
			takingPictureState__->outstream = outstream;
			return concurrency::create_task(BitmapEncoder::CreateForTranscodingAsync(outstream, takingPictureState__->decoder));
		}).then([this](BitmapEncoder^ encoder) {
			takingPictureState__->encoder = encoder;
			auto properties = ref new BitmapPropertySet();
			properties->Insert("System.Photo.Orientation", ref new BitmapTypedValue((unsigned short)takingPictureState__->orientation, Windows::Foundation::PropertyType::UInt16));
			return concurrency::create_task(takingPictureState__->encoder->BitmapProperties->SetPropertiesAsync(properties));
		}).then([this]() {
			return concurrency::create_task(takingPictureState__->encoder->FlushAsync());
		}).then([this](){
			return concurrency::create_task(takingPictureState__->outstream->FlushAsync());
		}).then([this](bool) {
			try {
				const auto media_filename = takingPictureState__->file->Path;

				// reset state
				takingPictureState__->decoder = nullptr;
				takingPictureState__->encoder = nullptr;
				takingPictureState__->outstream = nullptr;
				takingPictureState__->file    = nullptr;

				// autohide
				if (cameraOptionsState__.autohide) {
					// make sure to fire success callback after camera window is closed
					this->hideCamera([this, media_filename]() {
						if (cameraOptionsState__.callbacks.success.IsObject()) {
							Titanium::Media::CameraMediaItemType item;
							item.mediaType = Titanium::Media::MediaType::Photo;
							item.media_filename = TitaniumWindows::Utility::ConvertUTF8String(media_filename);

							cameraOptionsState__.callbacks.onsuccess(item);
						}
					});
				} else  if (cameraOptionsState__.callbacks.success.IsObject()) {
					Titanium::Media::CameraMediaItemType item;
					item.mediaType = Titanium::Media::MediaType::Photo;
					item.media_filename = TitaniumWindows::Utility::ConvertUTF8String(media_filename);

					cameraOptionsState__.callbacks.onsuccess(item);
				}

			} catch (Platform::Exception^ e) {
				TitaniumWindows::Utility::RunOnUIThread([this, e]() {
					if (cameraOptionsState__.callbacks.error.IsObject()) {
						GENERATE_TI_ERROR_RESPONSE("MediaModule: Failure on start taking photo: " + TitaniumWindows::Utility::ConvertString(e->Message), error);
						cameraOptionsState__.callbacks.onerror(error);
					}
				});
			} catch (...) {
				TitaniumWindows::Utility::RunOnUIThread([this]() {
					if (cameraOptionsState__.callbacks.error.IsObject()) {
						GENERATE_TI_ERROR_RESPONSE("MediaModule: Failure on start taking photo", error);
						cameraOptionsState__.callbacks.onerror(error);
					}
				});
			}
		});
	}

	void MediaModule::startVideoCapture() TITANIUM_NOEXCEPT
	{
		concurrency::task<StorageFile^>(KnownFolders::VideosLibrary->CreateFileAsync("TiMediaVideo.mp4", CreationCollisionOption::GenerateUniqueName)).then([this](concurrency::task<StorageFile^> fileTask) {
			try {
				auto file = fileTask.get();

				// TODO: Provide an API to customize capture settings
				auto properties = MediaEncodingProfile::CreateMp4(VideoEncodingQuality::Auto);
				concurrency::create_task(mediaCapture__->StartRecordToStorageFileAsync(properties, file)).then([this, file](concurrency::task<void> recordTask) {
					try {
						recordTask.get();
					} catch (Platform::Exception^ e) {
						const auto message = TitaniumWindows::Utility::ConvertString(e->Message);
						TITANIUM_MODULE_LOG_WARN("MediaModule: Failure on start taking video: ", message);
					} catch (...) {
						TITANIUM_MODULE_LOG_WARN("MediaModule: Failure on start taking video");
					}
				});
			} catch (Platform::Exception^ e) {
				const auto message = TitaniumWindows::Utility::ConvertString(e->Message);
				TITANIUM_MODULE_LOG_WARN("MediaModule: Failure on start taking video: ", message);
			} catch (...) {
				TITANIUM_MODULE_LOG_WARN("MediaModule: Failure on start taking video");
			}
		});
	}

	void MediaModule::stopVideoCapture() TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT_AND_THROW(cameraPreviewStarted__, "Camera is not visiable. Use showCamera() to show camera.");
		concurrency::create_task(mediaCapture__->StopRecordAsync()).then([this](concurrency::task<void> stopTask) {
			try {
				stopTask.get();
			} catch (Platform::Exception^ e) {
				TITANIUM_MODULE_LOG_WARN("MediaModule: Failed to stop camera preview: ", TitaniumWindows::Utility::ConvertString(e->Message));
			} catch (...) {
				TITANIUM_MODULE_LOG_WARN("MediaModule: Failed to stop camera preview");
			}
		});
	}

	void MediaModule::takeScreenshotDone(JSObject callback, const std::string& file, const bool& hasError)
	{
		clearScreenshotResources();

		const auto ctx = get_context();
		auto eventArg = ctx.CreateObject();
		if (hasError) {
			eventArg.SetProperty("media", ctx.CreateNull());
		} else {
			// read file and get blob.
			eventArg.SetProperty("media", TitaniumWindows::Utility::GetTiBlobForFile(ctx, file));
		}
		callback({ eventArg }, get_object());
	}

	void MediaModule::clearScreenshotResources()
	{
		if (screenCaptureStarted__) {
			delete(mediaCapture__.Get());
			screenCaptureStarted__ = false;
		}
	}

	// Create new storage and start capturing!
	void MediaModule::takeScreenshotToFile(JSObject callback)
	{
		// CreationCollisionOption::GenerateUniqueName generates unique name such as "TiMediaScreenCapture (2).jpg"
		concurrency::task<StorageFile^>(KnownFolders::PicturesLibrary->CreateFileAsync("TiMediaScreenCapture.jpg", CreationCollisionOption::GenerateUniqueName)).then([this, callback](concurrency::task<StorageFile^> fileTask) {
			try {
				auto file = fileTask.get();

				// TODO: Provide an API to customize capture settings
				ImageEncodingProperties^ properties = ImageEncodingProperties::CreateJpeg();
				concurrency::create_task(mediaCapture__->CapturePhotoToStorageFileAsync(properties, file)).then([this, file, callback](concurrency::task<void> recordTask) {
					try {
						recordTask.get();
						takeScreenshotDone(callback, TitaniumWindows::Utility::ConvertString(file->Path), false);
					} catch (Platform::Exception^ e) {
						const auto message = TitaniumWindows::Utility::ConvertString(e->Message);
						TITANIUM_MODULE_LOG_WARN("MediaModule: Failure on start capturing screen: ", message);
						takeScreenshotDone(callback);
					} catch (...) {
						TITANIUM_MODULE_LOG_WARN("MediaModule: Failure on start capturing screen");
						takeScreenshotDone(callback);
					}
				});
			} catch (Platform::Exception^ e) {
				const auto message = TitaniumWindows::Utility::ConvertString(e->Message);
				TITANIUM_MODULE_LOG_WARN("MediaModule: Failure on start capturing screen: ", message);
				takeScreenshotDone(callback);
			} catch (...) {
				TITANIUM_MODULE_LOG_WARN("MediaModule: Failure on start capturing screen");
				takeScreenshotDone(callback);
			}
		});
	}

	void MediaModule::takeScreenshot(JSValue callback_value) TITANIUM_NOEXCEPT
	{
		TITANIUM_MODULE_LOG_WARN("MediaModule::takeScreenshot: Unimplemented");
	}

	void MediaModule::vibrate(std::vector<std::chrono::milliseconds> pattern) TITANIUM_NOEXCEPT
	{
		TITANIUM_MODULE_LOG_WARN("MediaModule::vibrate: Not supported");
	}

	bool MediaModule::hasCameraPermissions() TITANIUM_NOEXCEPT
	{
		bool result = false;
		using namespace Windows::Data::Xml::Dom;

		concurrency::event event;
		task<StorageFile^>(Windows::ApplicationModel::Package::Current->InstalledLocation->GetFileAsync("AppxManifest.xml")).then([&event, &result, this](task<StorageFile^> fileTask) {
			try {
				task<XmlDocument^>(XmlDocument::LoadFromFileAsync(fileTask.get())).then([&event, &result, this](task<XmlDocument^> docTask) {
					try {
						const auto doc = docTask.get();
						const auto items = doc->GetElementsByTagName("DeviceCapability");
						for (unsigned int i = 0; i < items->Length; i++) {
							const auto node = items->GetAt(i);
							const auto name = static_cast<Platform::String^>(node->Attributes->GetNamedItem("Name")->NodeValue);
							if (name == "webcam") {
								result = true;
								break;
							}
						}
					} catch (...) {
					}
					event.set();
				}, concurrency::task_continuation_context::use_arbitrary());
			} catch (...) {
				result = true;
				event.set();
			}
		}, concurrency::task_continuation_context::use_arbitrary());
		event.wait();

		return result;
	}

	void MediaModule::requestCameraPermissions(JSValue callback) TITANIUM_NOEXCEPT
	{
		// not compatible with Windows 8.1/10
		// currently, it is not possible to request camera permissions
		const auto ctx = get_context();
		JSObject response = ctx.CreateObject();

		if (hasCameraPermissions()) {
			response.SetProperty("code", ctx.CreateNumber(0));
			response.SetProperty("error", ctx.CreateString());
			response.SetProperty("success", ctx.CreateBoolean(true));
		} else {
			response.SetProperty("code", ctx.CreateNumber(-1));
			response.SetProperty("error", ctx.CreateString(TitaniumWindows::Utility::ConvertString("webcam DeviceCapability not set in tiapp.xml")));
			response.SetProperty("success", ctx.CreateBoolean(false));
		}

		auto cb = static_cast<JSObject>(callback);
		TITANIUM_ASSERT(cb.IsFunction());
		cb({ response }, get_object());
	}

	MediaModule::MediaModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::MediaModule(js_context)
		, js_beep__(createBeepFunction(js_context))
		, fileOpenForMusicLibraryCallback__(createFileOpenForMusicLibraryFunction(js_context))
		, fileOpenForPhotoGalleryCallback__(createFileOpenForPhotoGalleryFunction(js_context))
		, cameraOptionsState__(Titanium::Media::create_empty_CameraOptionsType(js_context))
		, openPhotoGalleryOptionsState__(Titanium::Media::create_empty_PhotoGalleryOptionsType(js_context))
		, openMusicLibraryOptionsState__(Titanium::Media::create_empty_MusicLibraryOptionsType(js_context))
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::MediaModule::ctor Initialize");
		vibrate_timers__ = ref new Vector<DispatcherTimer^>();
		captureElement__ = ref new CaptureElement();
		captureElement__->Stretch = Media::Stretch::Fill;
	}

	MediaModule::~MediaModule()
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::MediaModule::dtor");
	}

	void MediaModule::JSExportInitialize()
	{
		JSExport<MediaModule>::SetClassVersion(1);
		JSExport<MediaModule>::SetParent(JSExport<Titanium::MediaModule>::Class());
		TITANIUM_ADD_FUNCTION(MediaModule, _postOpenPhotoGallery);
		TITANIUM_ADD_FUNCTION(MediaModule, _postOpenMusicLibrary);
		TITANIUM_ADD_FUNCTION(MediaModule, _postShowCamera);
	}

	TITANIUM_FUNCTION(MediaModule, _postOpenPhotoGallery)
	{
		ENSURE_ARGUMENT_INDEX(0);
		const auto argument = arguments.at(0);
		ENSURE_STRING_ARRAY(argument, files);

		_postOpenPhotoGallery(files);

		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, _postOpenMusicLibrary) 
	{
		ENSURE_ARGUMENT_INDEX(0);
		const auto argument = arguments.at(0);
		ENSURE_STRING_ARRAY(argument, files);

		_postOpenMusicLibrary(files);

		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(MediaModule, _postShowCamera)
	{
		_postShowCamera();
		return get_context().CreateUndefined();
	}

	void MediaModule::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		Titanium::Module::enableEvent(event_name);
	}

	void MediaModule::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		Titanium::Module::disableEvent(event_name);
	}
}
