/**
 * TitaniumKit Titanium.Media.AudioRecorder
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_MEDIA_AUDIORECORDER_HPP_
#define _TITANIUM_MEDIA_AUDIORECORDER_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Media/Constants.hpp"

namespace Titanium
{
	namespace Filesystem
	{
		class File;
	}

	namespace Media
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium AudioRecorder Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Media.AudioRecorder
		*/
		class TITANIUMKIT_EXPORT AudioRecorder : public Module, public JSExport<AudioRecorder>
		{

		public:

			/*!
			  @property
			  @abstract compression
			  @discussion Audio compression to be used for the recording.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(AudioFormat, compression);

			/*!
			  @property
			  @abstract format
			  @discussion Audio format to be used for the recording.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(AudioFileFormat, format);

			/*!
			  @property
			  @abstract paused
			  @discussion Indicates if the audio recorder is paused.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(bool, paused);

			/*!
			  @property
			  @abstract recording
			  @discussion Indicates if the audio recorder is recording.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(bool, recording);

			/*!
			  @property
			  @abstract stopped
			  @discussion Indicates if the audio recorder is stopped.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(bool, stopped);

			/*!
			  @method
			  @abstract pause
			  @discussion Pauses the current audio recording.
			*/
			virtual void pause() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract resume
			  @discussion Resumes a paused recording.
			*/
			virtual void resume() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract start
			  @discussion Starts an audio recording.
			*/
			virtual void start() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract stop
			  @discussion Stops the current audio recording and returns the recorded audio file.
			*/
			virtual std::shared_ptr<Titanium::Filesystem::File> stop() TITANIUM_NOEXCEPT;

			AudioRecorder(const JSContext&) TITANIUM_NOEXCEPT;
			virtual ~AudioRecorder()                       = default;
			AudioRecorder(const AudioRecorder&)            = default;
			AudioRecorder& operator=(const AudioRecorder&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			AudioRecorder(AudioRecorder&&)                 = default;
			AudioRecorder& operator=(AudioRecorder&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(compression);
			TITANIUM_PROPERTY_DEF(format);
			TITANIUM_PROPERTY_READONLY_DEF(paused);
			TITANIUM_PROPERTY_READONLY_DEF(recording);
			TITANIUM_PROPERTY_READONLY_DEF(stopped);

			TITANIUM_FUNCTION_DEF(pause);
			TITANIUM_FUNCTION_DEF(resume);
			TITANIUM_FUNCTION_DEF(start);
			TITANIUM_FUNCTION_DEF(stop);
			TITANIUM_FUNCTION_DEF(getCompression);
			TITANIUM_FUNCTION_DEF(setCompression);
			TITANIUM_FUNCTION_DEF(getFormat);
			TITANIUM_FUNCTION_DEF(setFormat);
			TITANIUM_FUNCTION_DEF(getPaused);
			TITANIUM_FUNCTION_DEF(getRecording);
			TITANIUM_FUNCTION_DEF(getStopped);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			AudioFormat compression__;
			AudioFileFormat format__;
			RecordingState state__;
#pragma warning(pop)
		};

	} // namespace Media
} // namespace Titanium
#endif // _TITANIUM_MEDIA_AUDIORECORDER_HPP_