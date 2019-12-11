/**
 * TitaniumKit Titanium.Stream
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Stream.hpp"
#include "Titanium/IOStream.hpp"
#include "Titanium/Buffer.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/BufferStream.hpp"
#include "Titanium/BlobStream.hpp"

#define CREATE_TITANIUM_BUFFER(NAME) \
  const auto NAME##_ctor = get_context().JSEvaluateScript("Ti.Buffer"); \
  TITANIUM_ASSERT(NAME##_ctor.IsObject()); \
  const auto NAME = static_cast<JSObject>(NAME##_ctor).CallAsConstructor();

namespace Titanium
{
	const std::uint32_t Stream::DEFAULT_CHUNK_SIZE(1024);

	CreateStreamArgs js_to_CreateStreamArgs(const JSObject& object)
	{
		CreateStreamArgs args;

		if (object.HasProperty("mode")) {
			args.modes = Titanium::Filesystem::Constants::to_MODE(static_cast<std::underlying_type<Titanium::Filesystem::MODE>::type>(object.GetProperty("mode")));
		} else {
			args.modes.insert(Filesystem::MODE::READ);
		}
		if (object.HasProperty("source")) {
			const auto source_property = object.GetProperty("source");
			if (source_property.IsObject()) {
				const auto source = static_cast<JSObject>(source_property);
				const auto blob  =  source.GetPrivate<Blob>();
				const auto buffer = source.GetPrivate<Buffer>();
				if (blob) {
					args.blob_source = blob;
				} else if (buffer) {
					args.buffer_source = buffer;
				}
			}
		}

		return args;
	}

	JSObject CreateStreamArgs_to_js(const JSContext& js_context, const CreateStreamArgs& params)
	{
		auto object = js_context.CreateObject();

		object.SetProperty("mode", js_context.CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(params.modes)));

		if (params.blob_source) {
			object.SetProperty("source", params.blob_source->get_object());
		} else if (params.buffer_source) {
			object.SetProperty("source", params.buffer_source->get_object());
		}
		return object;
	}

	JSFunction Stream::createPromisifyFunction(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		const std::string script = R"JS(
			return function(value) {
				new Promise(function(resolve){ resolve(value); }).then(callback);
			};
		)JS";
		return js_context.CreateFunction(script, { JSString("callback") });
	}

	Stream::Stream(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Module(js_context, "Ti.Stream")
		, promisifyFunc__(createPromisifyFunction(js_context))
		, MODE_READ__(js_context.CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::READ)))
		, MODE_WRITE__(js_context.CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::WRITE)))
		, MODE_APPEND__(js_context.CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::APPEND)))
	{

	}

	/*
	 * Returns Titanium.BufferStream or Titanium.BlobStream depending on whether a Buffer or Blob is provided as the source property in params.
	*/
	std::shared_ptr<IOStream> Stream::createStream(const CreateStreamArgs& params) TITANIUM_NOEXCEPT
	{
		if (params.blob_source) {
			const auto blobStream_ctor = get_context().JSEvaluateScript("Ti.BlobStream");
			TITANIUM_ASSERT(blobStream_ctor.IsObject());
			const auto blobStream = static_cast<JSObject>(blobStream_ctor).CallAsConstructor();
			const auto blobStream_ptr = blobStream.GetPrivate<BlobStream>();
			if (params.modes.find(Filesystem::MODE::READ) == params.modes.end()) {
				HAL::detail::ThrowRuntimeError("Titanium::Stream::createStream", "Invalid argument for Stream.createStream, mode should be READ for BlobStream.");
			}
			blobStream_ptr->set_modes(params.modes);
			blobStream_ptr->construct(params.blob_source);
			return std::dynamic_pointer_cast<IOStream>(blobStream_ptr);
		} else if (params.buffer_source) {
			const auto bufferStream_ctor = get_context().JSEvaluateScript("Ti.BufferStream");
			TITANIUM_ASSERT(bufferStream_ctor.IsObject());
			const auto bufferStream = static_cast<JSObject>(bufferStream_ctor).CallAsConstructor();
			const auto bufferStream_ptr = bufferStream.GetPrivate<BufferStream>();
			bufferStream_ptr->set_modes(params.modes);
			bufferStream_ptr->construct(params.buffer_source);
			return std::dynamic_pointer_cast<IOStream>(bufferStream_ptr);
		}
		return nullptr;
	}

	void Stream::read(const std::shared_ptr<IOStream>& sourceStream, const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length, JSObject resultsCallback) TITANIUM_NOEXCEPT
	{
		if (buffer->get_length() < offset + length) {
			JSObject e = get_context().CreateObject();
			e.SetProperty("bytesProcessed", get_context().CreateNumber(-1));
			e.SetProperty("success", get_context().CreateBoolean(false));
			e.SetProperty("code", get_context().CreateNumber(-1));
			e.SetProperty("error", get_context().CreateString("Stream::read: Invalid offset or length"));
			e.SetProperty("source", sourceStream->get_object());

			const std::vector<JSValue> args { e };
			static_cast<JSObject>(resultsCallback)(args, get_object());
			return;
		}
		sourceStream->readAsync(buffer, offset, length, [this, sourceStream, resultsCallback](const ErrorResponse& error, const std::int32_t& bytesRead) {
			JSObject e = get_context().CreateObject();
			e.SetProperty("bytesProcessed", get_context().CreateNumber(bytesRead));
			e.SetProperty("success", get_context().CreateBoolean(error.success));
			e.SetProperty("code", get_context().CreateNumber(error.code));
			e.SetProperty("error", get_context().CreateString(error.error));
			e.SetProperty("source", sourceStream->get_object());

			const std::vector<JSValue> args { e };
			static_cast<JSObject>(resultsCallback)(args, get_object());
		});
	}

	std::shared_ptr<Buffer> Stream::readAll(const std::shared_ptr<IOStream>& sourceStream, const std::shared_ptr<Buffer>& write_buffer, JSObject resultsCallback) TITANIUM_NOEXCEPT
	{
		CREATE_TITANIUM_BUFFER(read_buffer_object);
		const auto read_buffer = read_buffer_object.GetPrivate<Buffer>();
		read_buffer->set_length(DEFAULT_CHUNK_SIZE);

		if (write_buffer != nullptr && resultsCallback.IsFunction()) {
			//
			// read operation takes place asynchronously, and results are passed to callback.
			//
			const auto callback = [this, resultsCallback](const ErrorResponse& error, const std::shared_ptr<IOStream>& sourceStream) {
				JSObject e = get_context().CreateObject();
				e.SetProperty("source", sourceStream->get_object());
				e.SetProperty("bytesProcessed", get_context().CreateNumber(sourceStream->get_totalBytesProcessed()));
				e.SetProperty("success", get_context().CreateBoolean(error.success));
				e.SetProperty("code", get_context().CreateNumber(error.code));
				e.SetProperty("error", get_context().CreateString(error.error));

				const std::vector<JSValue> args { e };
				static_cast<JSObject>(resultsCallback)(args, get_object());
			};

			// Start reading
			sourceStream->readAllAsync(write_buffer, callback);

			return nullptr;
		} else {
			// Create new Buffer for write operation
			CREATE_TITANIUM_BUFFER(write_buffer_object);
			auto new_write_buffer = write_buffer_object.GetPrivate<Buffer>();

			std::int32_t bytesRead = 0;
			while ((bytesRead = sourceStream->read(read_buffer, 0, read_buffer->get_length())) != -1) {
				new_write_buffer->append(read_buffer, 0, bytesRead);
				read_buffer->clear();
			}

			return new_write_buffer;
		}
	}

	void Stream::write(const std::shared_ptr<IOStream>& outputStream, const std::shared_ptr<Buffer>& buffer, const uint32_t& offset, const uint32_t& length, JSObject resultsCallback) TITANIUM_NOEXCEPT
	{
		outputStream->writeAsync(buffer, offset, length, [this, resultsCallback](const ErrorResponse& error, const std::int32_t& bytesWritten) {
			JSObject e = get_context().CreateObject();
			e.SetProperty("bytesProcessed", get_context().CreateNumber(bytesWritten));
			e.SetProperty("success", get_context().CreateBoolean(error.success));
			e.SetProperty("code", get_context().CreateNumber(error.code));
			e.SetProperty("error", get_context().CreateString(error.error));

			const std::vector<JSValue> args { e };
			static_cast<JSObject>(resultsCallback)(args, get_object());
		});
	}

	std::uint32_t Stream::writeStream(const std::shared_ptr<IOStream>& inputStream, const std::shared_ptr<IOStream>& outputStream, const uint32_t& maxChunkSize, JSObject resultsCallback) TITANIUM_NOEXCEPT
	{
		CREATE_TITANIUM_BUFFER(buffer_object);
		const auto read_buffer = buffer_object.GetPrivate<Buffer>();
		read_buffer->set_length(maxChunkSize);

		const std::function<void(const ErrorResponse&, const std::int32_t&)> callback = [this, &callback, inputStream, outputStream, read_buffer, maxChunkSize, resultsCallback](const ErrorResponse& error, const std::int32_t& bytesRead) {
			if (bytesRead < 0) {
				JSObject e = get_context().CreateObject();
				e.SetProperty("fromStream", inputStream->get_object());
				e.SetProperty("toStream",   outputStream->get_object());
				e.SetProperty("bytesProcessed", get_context().CreateNumber(outputStream->get_totalBytesProcessed()));
				e.SetProperty("success", get_context().CreateBoolean(error.success));
				e.SetProperty("code", get_context().CreateNumber(error.code));
				e.SetProperty("error", get_context().CreateString(error.error));

				const std::vector<JSValue> args { e };
				static_cast<JSObject>(resultsCallback)(args, get_object());
			} else {
				outputStream->write(read_buffer, 0, bytesRead);
				read_buffer->clear();
				inputStream->readAsync(read_buffer, 0, maxChunkSize, callback);
			}
		};

		if (resultsCallback.IsFunction()) {
			inputStream->readAsync(read_buffer, 0, maxChunkSize, callback);
		} else {
			std::int32_t bytesRead = 0;
			while ((bytesRead = inputStream->read(read_buffer, 0, maxChunkSize)) != -1) {
				if (outputStream->write(read_buffer, 0, bytesRead) == 0) {
					break;
				}
				read_buffer->clear();
			}
			return outputStream->get_totalBytesProcessed();
		}

		return 0;
	}

	void Stream::pump(const std::shared_ptr<IOStream>& inputStream, JSObject handler, const uint32_t& maxChunkSize, const bool& isAsync) TITANIUM_NOEXCEPT
	{
		CREATE_TITANIUM_BUFFER(buffer_object);
		const auto read_buffer = buffer_object.GetPrivate<Buffer>();
		read_buffer->set_length(maxChunkSize);

		const auto callback = [=](const ErrorResponse& error, const std::int32_t& bytesRead) {
			JSObject e = get_context().CreateObject();
			e.SetProperty("buffer", buffer_object);
			e.SetProperty("source", inputStream->get_object());
			e.SetProperty("bytesProcessed", get_context().CreateNumber(bytesRead > 0 ? bytesRead : -1));
			e.SetProperty("totalBytesProcessed", get_context().CreateNumber(inputStream->get_totalBytesProcessed()));
			e.SetProperty("success", get_context().CreateBoolean(error.success));
			e.SetProperty("code", get_context().CreateNumber(error.code));
			e.SetProperty("error", get_context().CreateString(error.error));

			const std::vector<JSValue> args { e };
			static_cast<JSObject>(handler)(args, get_object());

			if (bytesRead > 0) {
				pump(inputStream, handler, maxChunkSize, isAsync);
			}
		};

		if (isAsync) {
			inputStream->readAsync(read_buffer, 0, maxChunkSize, callback);
		} else {
			ErrorResponse error;
			callback(error, inputStream->read(read_buffer, 0, maxChunkSize));
		}
	}

	void Stream::JSExportInitialize()
	{
		JSExport<Stream>::SetClassVersion(1);
		JSExport<Stream>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_PROPERTY_READONLY(Stream, MODE_APPEND);
		TITANIUM_ADD_PROPERTY_READONLY(Stream, MODE_READ);
		TITANIUM_ADD_PROPERTY_READONLY(Stream, MODE_WRITE);
		TITANIUM_ADD_FUNCTION(Stream, createStream);
		TITANIUM_ADD_FUNCTION(Stream, read);
		TITANIUM_ADD_FUNCTION(Stream, readAll);
		TITANIUM_ADD_FUNCTION(Stream, write);
		TITANIUM_ADD_FUNCTION(Stream, writeStream);
		TITANIUM_ADD_FUNCTION(Stream, pump);
	}

	TITANIUM_FUNCTION(Stream, read)
	{
		ENSURE_ARGUMENT_INDEX(1);
		ENSURE_OBJECT_AT_INDEX(source_object, 0);
		ENSURE_OBJECT_AT_INDEX(buffer_object, 1);

		//
		// read(sourceStream, buffer, [offset], [length], resultsCallback)
		//
		const auto write_buffer = buffer_object.GetPrivate<Buffer>();
		const auto source_stream = source_object.GetPrivate<IOStream>();

		if (source_stream == nullptr) {
			HAL::detail::ThrowRuntimeError("Titanium::Stream::read", "Titanium::Stream::read: Invalid source specified");
		} else if (!source_stream->isReadable()) {
			HAL::detail::ThrowRuntimeError("Titanium::Stream::read", "Titanium::Stream::read: Cannot read from source");
		}

		if (arguments.at(2).IsObject()) {
			ENSURE_OBJECT_AT_INDEX(resultsCallback, 2);
			// Ensure callback is always done with Promise-like async manner
			const std::vector<JSValue> pargs = { resultsCallback };
			resultsCallback = static_cast<JSObject>(promisifyFunc__(pargs, get_object()));
			read(source_stream, write_buffer, 0, write_buffer->get_length(), resultsCallback);
		} else {
			ENSURE_ARGUMENT_INDEX(4);
			ENSURE_UINT_AT_INDEX(offset, 2);
			ENSURE_UINT_AT_INDEX(length, 3);
			ENSURE_OBJECT_AT_INDEX(resultsCallback, 4);
			// Ensure callback is always done with Promise-like async manner
			const std::vector<JSValue> pargs = { resultsCallback };
			resultsCallback = static_cast<JSObject>(promisifyFunc__(pargs, get_object()));
			read(source_stream, write_buffer, offset, length, resultsCallback);
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Stream, readAll)
	{
		ENSURE_OBJECT_AT_INDEX(source_object, 0);
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(buffer_object, 1);
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(resultsCallback, 2);

		const auto source_stream = source_object.GetPrivate<IOStream>();

		if (source_stream == nullptr) {
			HAL::detail::ThrowRuntimeError("Titanium::Stream::readAll", "Titanium::Stream::readAll: Invalid source specified");
		} else if (!source_stream->isReadable()) {
			HAL::detail::ThrowRuntimeError("Titanium::Stream::readAll", "Titanium::Stream::readAll: Cannot read from source");
		}

		if (resultsCallback.IsFunction()) {
			// Ensure callback is always done with Promise-like async manner
			const std::vector<JSValue> pargs = { resultsCallback };
			resultsCallback = static_cast<JSObject>(promisifyFunc__(pargs, get_object()));
		}

		const auto result = readAll(source_stream, buffer_object.GetPrivate<Buffer>(), resultsCallback);
		if (result) {
			return result->get_object();
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Stream, write)
	{
		ENSURE_ARGUMENT_INDEX(1);
		ENSURE_OBJECT_AT_INDEX(output_object, 0);
		ENSURE_OBJECT_AT_INDEX(buffer_object, 1);

		//
		// write(outputStream, buffer, [offset], [length], resultsCallback)
		//
		const auto read_buffer = buffer_object.GetPrivate<Buffer>();
		const auto output_stream = output_object.GetPrivate<IOStream>();

		if (read_buffer == nullptr || output_stream == nullptr) {
			HAL::detail::ThrowRuntimeError("Titanium::Stream::write", "Titanium::Stream::write: Invalid arguments");
		} else if (!output_stream->isWritable()) {
			HAL::detail::ThrowRuntimeError("Titanium::Stream::write", "Titanium::Stream::write: Cannot write to the stream");
		}

		ENSURE_ARGUMENT_INDEX(2);
		if (arguments.at(2).IsObject()) {
			ENSURE_OBJECT_AT_INDEX(resultsCallback, 2);
			// Ensure callback is always done with Promise-like async manner
			const std::vector<JSValue> pargs = { resultsCallback };
			resultsCallback = static_cast<JSObject>(promisifyFunc__(pargs, get_object()));
			write(output_stream, read_buffer, 0, read_buffer->get_length(), resultsCallback);
		} else {
			ENSURE_ARGUMENT_INDEX(4);
			ENSURE_UINT_AT_INDEX(offset, 2);
			ENSURE_UINT_AT_INDEX(length, 3);
			ENSURE_OBJECT_AT_INDEX(resultsCallback, 4);
			// Ensure callback is always done with Promise-like async manner
			const std::vector<JSValue> pargs = { resultsCallback };
			resultsCallback = static_cast<JSObject>(promisifyFunc__(pargs, get_object()));
			write(output_stream, read_buffer, offset, length, resultsCallback);
		}

		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Stream, writeStream)
	{
		ENSURE_ARGUMENT_INDEX(2);
		ENSURE_OBJECT_AT_INDEX(input_object, 0);
		ENSURE_OBJECT_AT_INDEX(output_object, 1);
		ENSURE_UINT_AT_INDEX(maxChunkSize, 2);
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(resultsCallback, 3);

		const auto input_stream  = input_object.GetPrivate<IOStream>();
		const auto output_stream = output_object.GetPrivate<IOStream>();

		if (input_stream == nullptr || output_stream == nullptr) {
			HAL::detail::ThrowRuntimeError("Titanium::Stream:writeStream", "Stream::writeStream: Invalid arguments");
		} else if (!input_stream->isReadable()) {
			HAL::detail::ThrowRuntimeError("Titanium::Stream:writeStream", "Stream::writeStream: Cannot read from input stream");
		} else if (!output_stream->isWritable()) {
			HAL::detail::ThrowRuntimeError("Titanium::Stream:writeStream", "Stream::writeStream: Cannot write to the stream");
		}

		if (resultsCallback.IsFunction()) {
			// Ensure callback is always done with Promise-like async manner
			const std::vector<JSValue> pargs = { resultsCallback };
			resultsCallback = static_cast<JSObject>(promisifyFunc__(pargs, get_object()));
		}

		const auto result = writeStream(input_stream, output_stream, maxChunkSize, resultsCallback);

		if (resultsCallback.IsFunction()) {
			return get_context().CreateUndefined();
		} else {
			return get_context().CreateNumber(result);
		}
	}

	TITANIUM_FUNCTION(Stream, pump)
	{
		ENSURE_ARGUMENT_INDEX(2);
		ENSURE_OBJECT_AT_INDEX(inputStream, 0);
		ENSURE_OBJECT_AT_INDEX(handler, 1);
		ENSURE_UINT_AT_INDEX(maxChunkSize, 2);
		ENSURE_OPTIONAL_BOOL_AT_INDEX(isAsync, 3, true);

		const auto inputStream_ptr = inputStream.GetPrivate<IOStream>();
		if (inputStream_ptr != nullptr && inputStream_ptr->isReadable() && handler.IsFunction()) {
			// Ensure callback is always done with Promise-like async manner
			const std::vector<JSValue> pargs = { handler };
			handler = static_cast<JSObject>(promisifyFunc__(pargs, get_object()));
			pump(inputStream_ptr, handler, maxChunkSize, isAsync);
		} else {
			HAL::detail::ThrowRuntimeError("Titanium::Stream:pump", "Stream::pump: Invalid arguments");
		}

		return get_context().CreateUndefined();
	}

	TITANIUM_PROPERTY_GETTER(Stream, MODE_APPEND)
	{
		return MODE_APPEND__;
	}

	TITANIUM_PROPERTY_GETTER(Stream, MODE_READ)
	{
		return MODE_READ__;
	}

	TITANIUM_PROPERTY_GETTER(Stream, MODE_WRITE)
	{
		return MODE_WRITE__;
	}

	TITANIUM_FUNCTION(Stream, createStream)
	{
		ENSURE_OBJECT_AT_INDEX(params, 0);
		const auto stream = createStream(js_to_CreateStreamArgs(params));
		if (stream) {
			return stream->get_object();
		} else {
			return get_context().CreateNull();
		}
	}
} // namespace Titanium
