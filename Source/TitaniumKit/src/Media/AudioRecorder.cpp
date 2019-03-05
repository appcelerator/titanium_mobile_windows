/**
 * TitaniumKit Titanium.Media.AudioRecorder
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Media/AudioRecorder.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Media
	{

		AudioRecorder::AudioRecorder(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Media.AudioRecorder")
			, compression__(AudioFormat::LinearPCM)
			, format__(AudioFileFormat::Caf)
			, state__(RecordingState::Stopped)
		{
		}

		TITANIUM_PROPERTY_READWRITE(AudioRecorder, AudioFormat, compression)
		TITANIUM_PROPERTY_READWRITE(AudioRecorder, AudioFileFormat, format)

		bool AudioRecorder::get_paused() const TITANIUM_NOEXCEPT
		{
			return (state__ == RecordingState::Paused);
		}

		bool AudioRecorder::get_recording() const TITANIUM_NOEXCEPT
		{
			return (state__ == RecordingState::Recording);
		}

		bool AudioRecorder::get_stopped() const TITANIUM_NOEXCEPT
		{
			return (state__ == RecordingState::Stopped);
		}

		void AudioRecorder::pause() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("AudioRecorder::pause: Unimplemented");
		}

		void AudioRecorder::resume() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("AudioRecorder::resume: Unimplemented");
		}

		void AudioRecorder::start() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("AudioRecorder::start: Unimplemented");
		}

		std::shared_ptr<Titanium::Filesystem::File> AudioRecorder::stop() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("AudioRecorder::stop: Unimplemented");
			return nullptr;
		}

		void AudioRecorder::JSExportInitialize()
		{
			JSExport<AudioRecorder>::SetClassVersion(1);
			JSExport<AudioRecorder>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(AudioRecorder, compression);
			TITANIUM_ADD_PROPERTY(AudioRecorder, format);
			TITANIUM_ADD_PROPERTY_READONLY(AudioRecorder, paused);
			TITANIUM_ADD_PROPERTY_READONLY(AudioRecorder, recording);
			TITANIUM_ADD_PROPERTY_READONLY(AudioRecorder, stopped);

			TITANIUM_ADD_FUNCTION(AudioRecorder, pause);
			TITANIUM_ADD_FUNCTION(AudioRecorder, resume);
			TITANIUM_ADD_FUNCTION(AudioRecorder, start);
			TITANIUM_ADD_FUNCTION(AudioRecorder, stop);
			TITANIUM_ADD_FUNCTION(AudioRecorder, getCompression);
			TITANIUM_ADD_FUNCTION(AudioRecorder, setCompression);
			TITANIUM_ADD_FUNCTION(AudioRecorder, getFormat);
			TITANIUM_ADD_FUNCTION(AudioRecorder, setFormat);
			TITANIUM_ADD_FUNCTION(AudioRecorder, getPaused);
			TITANIUM_ADD_FUNCTION(AudioRecorder, getRecording);
			TITANIUM_ADD_FUNCTION(AudioRecorder, getStopped);
		}

		TITANIUM_PROPERTY_GETTER_ENUM(AudioRecorder, compression)
		TITANIUM_PROPERTY_SETTER_ENUM(AudioRecorder, compression, AudioFormat)
		TITANIUM_PROPERTY_GETTER_ENUM(AudioRecorder, format)
		TITANIUM_PROPERTY_SETTER_ENUM(AudioRecorder, format, AudioFileFormat)
		TITANIUM_PROPERTY_GETTER_BOOL(AudioRecorder, paused)
		TITANIUM_PROPERTY_GETTER_BOOL(AudioRecorder, recording)
		TITANIUM_PROPERTY_GETTER_BOOL(AudioRecorder, stopped)

		TITANIUM_FUNCTION(AudioRecorder, pause)
		{
			pause();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(AudioRecorder, resume)
		{
			resume();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(AudioRecorder, start)
		{
			start();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(AudioRecorder, stop)
		{
			const auto file = stop();
			if (file != nullptr) {
				return file->get_object();
			} else {
				return get_context().CreateNull();
			}
		}

		TITANIUM_FUNCTION_AS_GETTER(AudioRecorder, getCompression, compression)
		TITANIUM_FUNCTION_AS_SETTER(AudioRecorder, setCompression, compression)
		TITANIUM_FUNCTION_AS_GETTER(AudioRecorder, getFormat, format)
		TITANIUM_FUNCTION_AS_SETTER(AudioRecorder, setFormat, format)
		TITANIUM_FUNCTION_AS_GETTER(AudioRecorder, getPaused, paused)
		TITANIUM_FUNCTION_AS_GETTER(AudioRecorder, getRecording, recording)
		TITANIUM_FUNCTION_AS_GETTER(AudioRecorder, getStopped, stopped)

	} // namespace Media
} // namespace Titanium
