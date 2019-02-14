/**
 * TitaniumKit Titanium.IOStream
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_IOSTREAM_HPP_
#define _TITANIUM_IOSTREAM_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Filesystem/Constants.hpp"

namespace Titanium
{
	using namespace HAL;

	class Buffer;
	struct ErrorResponse;

	/*!
	  @class
	  @discussion This is the Titanium IOStream Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.IOStream
	*/
	class TITANIUMKIT_EXPORT IOStream : public Module, public JSExport<IOStream>
	{

	public:

		/*!
		  @method
		  @abstract read
		  @discussion Reads data from this stream into a buffer.
		*/
		virtual std::int32_t read(const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length);

		/*!
		  @method
		  @abstract readAsync
		  @discussion Override this if subclass supports async operation
		*/
		virtual void readAsync(const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const ErrorResponse&, const std::int32_t&)>&);

		/*!
		  @method
		  @abstract readAllAsync
		  @discussion Override this if subclass supports async operation
		*/
		virtual void readAllAsync(const std::shared_ptr<Buffer>& buffer, const std::function<void(const ErrorResponse&, const std::shared_ptr<IOStream>& source)>&);

		/*!
		  @method
		  @abstract write
		  @discussion Writes data from a buffer to this stream.
		*/
		virtual std::uint32_t write(const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length);

		/*!
		  @method
		  @abstract writeAsync
		  @discussion Override this if subclass supports async operation
		*/
		virtual void writeAsync(const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const ErrorResponse&, const std::int32_t&)>&);

		/*!
		  @method
		  @abstract isWritable
		  @discussion Indicates whether this stream is writeable.
		*/
		virtual bool isWritable() TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract isReadable
		  @discussion Indicates whether this stream is readable.
		*/
		virtual bool isReadable() TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract close
		  @discussion Closes this stream.
		*/
		virtual void close();

		/*!
		  @method
		  @abstract set_mode
		  @discussion Set mode to open the stream in.
		*/
		virtual void set_modes(const std::unordered_set<Filesystem::MODE>& mode)
		{
			modes__ = mode;
		}

		/*!
		  @method
		  @abstract get_totalBytesProcessed
		  @discussion Get total bytes processed
		*/
		virtual std::uint32_t get_totalBytesProcessed() const 
		{
			return totalBytesProcessed__;
		}

		virtual std::uint32_t getAvailableBytesToRead(const std::shared_ptr<Buffer>& read_buffer, const std::shared_ptr<Buffer>& write_buffer, const std::uint32_t& read_offset, const std::uint32_t& write_offset, const std::uint32_t& length);

		IOStream(const JSContext&, const std::string& = "Titanium.IOStream") TITANIUM_NOEXCEPT;
		virtual ~IOStream()                  = default;
		IOStream(const IOStream&)            = default;
		IOStream& operator=(const IOStream&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		IOStream(IOStream&&)                 = default;
		IOStream& operator=(IOStream&&)      = default;
#endif

		static void JSExportInitialize();

		TITANIUM_FUNCTION_DEF(read);
		TITANIUM_FUNCTION_DEF(write);
		TITANIUM_FUNCTION_DEF(isWritable);
		TITANIUM_FUNCTION_DEF(isReadable);
		TITANIUM_FUNCTION_DEF(close);

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		std::unordered_set<Filesystem::MODE> modes__;
		std::uint32_t totalBytesProcessed__ { 0 };
#pragma warning(pop)
	};

} // namespace Titanium
#endif // _TITANIUM_IOSTREAM_HPP_