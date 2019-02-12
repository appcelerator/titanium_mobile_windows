/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Media/AudioRecorder.hpp"
#include <windows.h>
#include <ppltasks.h>
#include <concrt.h>
#include "TitaniumWindows/LogForwarder.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/Filesystem/File.hpp"

namespace TitaniumWindows
{
	namespace Media
	{
		using namespace Windows::Media;
		using namespace Windows::Media::Capture;
		using namespace Windows::Media::MediaProperties;
		using namespace Windows::Storage;

		AudioRecorder::AudioRecorder(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Media::AudioRecorder(js_context),
			encodingProfile__(MediaEncodingProfile::CreateM4a(AudioEncodingQuality::Auto))
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Media::AudioRecorder::ctor Initialize");
		}

		AudioRecorder::~AudioRecorder()
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Media::AudioRecorder::dtor");
		}

		void AudioRecorder::JSExportInitialize()
		{
			JSExport<AudioRecorder>::SetClassVersion(1);
			JSExport<AudioRecorder>::SetParent(JSExport<Titanium::Media::AudioRecorder>::Class());
		}

		void AudioRecorder::set_format(const Titanium::Media::AudioFileFormat& format) TITANIUM_NOEXCEPT
		{
			switch (format) {
				case Titanium::Media::AudioFileFormat::Mp4a:
					encodingProfile__ = MediaEncodingProfile::CreateM4a(AudioEncodingQuality::Auto);
					break;
				case Titanium::Media::AudioFileFormat::Mp3:
					encodingProfile__ = MediaEncodingProfile::CreateMp3(AudioEncodingQuality::Auto);
					break;
				case Titanium::Media::AudioFileFormat::Wave:
					encodingProfile__ = MediaEncodingProfile::CreateWav(AudioEncodingQuality::Auto);
					break;
				default:
					TITANIUM_MODULE_LOG_WARN("AudioRecorder: Unsupported audio format");
					return;
			}
			Titanium::Media::AudioRecorder::set_format(format);
		}

		void AudioRecorder::start() TITANIUM_NOEXCEPT
		{
			mediaCapture__ = ref new MediaCapture();
			recordFile__ = nullptr;

			const auto settings = ref new MediaCaptureInitializationSettings();
			settings->StreamingCaptureMode = StreamingCaptureMode::Audio;
			settings->MediaCategory = MediaCategory::Other;
			settings->AudioProcessing = AudioProcessing::Default;

			concurrency::create_task(mediaCapture__->InitializeAsync()).then(
				[=](concurrency::task<void> initTask) {
					try {
						initTask.get();
						const auto mediaCapture = mediaCapture__.Get();

						mediaCapture->RecordLimitationExceeded += ref new RecordLimitationExceededEventHandler(
							[=](MediaCapture^ sender) {
								TITANIUM_MODULE_LOG_WARN("AudioRecorder: Stopping, exceeding max record duration");
								try {
									stop();
								} catch (...) {
									TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to stop");
								}
							}
						);
						mediaCapture->Failed += ref new MediaCaptureFailedEventHandler(
							[=](MediaCapture^ sender, MediaCaptureFailedEventArgs^ e) {
							TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to capture audio: ", TitaniumWindows::Utility::ConvertString(e->Message));
								try {
									stop();
								} catch (...) {
									TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to stop");
								}
							});
					} catch (Platform::Exception ^ e) {
						TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to initialize audio capture device: ", TitaniumWindows::Utility::ConvertString(e->Message));
					} catch (...) {
						TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to initialize audio capture device");
					}

					std::string fileName = "AudioRecording";
					switch (format__) {
						default:
						case Titanium::Media::AudioFileFormat::Mp4a:
							fileName += ".mp4";
							break;
						case Titanium::Media::AudioFileFormat::Mp3:
							fileName += ".mp3";
							break;
						case Titanium::Media::AudioFileFormat::Wave:
							fileName += ".wav";
							break;
					}
					return KnownFolders::MusicLibrary->CreateFileAsync(TitaniumWindows::Utility::ConvertString(fileName), CreationCollisionOption::GenerateUniqueName);
				}
			).then([=](concurrency::task<StorageFile^> fileTask) {
					try {
						recordFile__ = fileTask.get();
						concurrency::create_task(mediaCapture__->StartRecordToStorageFileAsync(encodingProfile__, recordFile__)).then(
							[=](concurrency::task<void> recordTask) {
								try {
									recordTask.get();
									state__ = Titanium::Media::RecordingState::Recording;
								} catch (Platform::Exception^ e) {
									TITANIUM_LOG_ERROR("AudioRecorder: Recording failed: ", TitaniumWindows::Utility::ConvertString(e->Message));
								} catch (...) {
									TITANIUM_LOG_ERROR("AudioRecorder: Recording failed");
								}
							}
						);
					} catch (Platform::Exception^ e) {
						TITANIUM_LOG_ERROR("AudioRecorder: Recording failed: ", TitaniumWindows::Utility::ConvertString(e->Message));
					} catch (...) {
						TITANIUM_LOG_ERROR("AudioRecorder: Recording failed");
					}
				}
			);

		}

		std::shared_ptr<Titanium::Filesystem::File> AudioRecorder::stop() TITANIUM_NOEXCEPT
		{
			if (state__ == Titanium::Media::RecordingState::Recording) {
				concurrency::create_task(mediaCapture__->StopRecordAsync()).then(
					[=](concurrency::task<void> recordTask) {
						try {
							recordTask.get();
							state__ = Titanium::Media::RecordingState::Stopped;
							delete(mediaCapture__.Get());
						} catch (Platform::Exception ^e) {
							TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to stop recording: ", TitaniumWindows::Utility::ConvertString(e->Message));
						} catch (...) {
							TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to stop recording");
						}
					}
				);
			} else {
				try {
					if (mediaCapture__.Get()) {
						delete(mediaCapture__.Get());
					}
				} catch (Platform::Exception ^e) {
					TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to stop audio capture device: ", TitaniumWindows::Utility::ConvertString(e->Message));
				} catch (...) {
					TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to stop audio capture device");
				}
			}

			// save recording to file
			if (recordFile__ != nullptr) {
				const auto titanium_js = get_context().get_global_object().GetProperty("Titanium");
				TITANIUM_ASSERT(titanium_js.IsObject());
				const auto titanium_obj = static_cast<JSObject>(titanium_js);

				const auto filesystem_js = titanium_obj.GetProperty("Filesystem");
				TITANIUM_ASSERT(filesystem_js.IsObject());
				const auto filesystem_obj = static_cast<JSObject>(filesystem_js);

				const auto getFile_js = filesystem_obj.GetProperty("getFile");
				TITANIUM_ASSERT(getFile_js.IsObject());
				auto getFile = static_cast<JSObject>(getFile_js);

				const std::vector<JSValue> args = { get_context().CreateString(TitaniumWindows::Utility::ConvertString(recordFile__->Path)) };
				const auto file = getFile(args, getFile);
				if (file.IsObject()) {
					return static_cast<JSObject>(file).GetPrivate<Titanium::Filesystem::File>();
				}
			}
			return nullptr;
		}

		void AudioRecorder::pause() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			if (state__ == Titanium::Media::RecordingState::Recording) {
				concurrency::create_task(mediaCapture__->PauseRecordAsync(Windows::Media::Devices::MediaCapturePauseBehavior::RetainHardwareResources)).then(
					[=](concurrency::task<void> pauseTask) {
						try {
							pauseTask.get();
							state__ = Titanium::Media::RecordingState::Paused;
						} catch (Platform::Exception ^e) {
							TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to pause recording: ", TitaniumWindows::Utility::ConvertString(e->Message));
						} catch (...) {
							TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to pause recording");
						}
					}
				);
			}
#else
			TITANIUM_MODULE_LOG_WARN("AudioRecorder::pause: Unsupported on this version of Windows");
#endif
		}

		void AudioRecorder::resume() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			if (state__ == Titanium::Media::RecordingState::Paused) {
				concurrency::create_task(mediaCapture__->ResumeRecordAsync()).then(
					[=](concurrency::task<void> resumeTask) {
						try {
							resumeTask.get();
							state__ = Titanium::Media::RecordingState::Recording;
						} catch (Platform::Exception ^e) {
							TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to resume recording: ", TitaniumWindows::Utility::ConvertString(e->Message));
						} catch (...) {
							TITANIUM_MODULE_LOG_WARN("AudioRecorder: Failed to resume recording");
						}
					}
				);
			}
#else
			TITANIUM_MODULE_LOG_WARN("AudioRecorder::resume: Unsupported on this version of Windows");
#endif
		}
	}
}
