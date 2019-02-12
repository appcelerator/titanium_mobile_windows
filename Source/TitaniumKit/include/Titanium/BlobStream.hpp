/**
 * TitaniumKit Titanium.BlobStream
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_BLOBSTREAM_HPP_
#define _TITANIUM_BLOBSTREAM_HPP_

#include "Titanium/IOStream.hpp"

namespace Titanium
{
	using namespace HAL;

	class Blob;
	struct ErrorResponse;

	/*!
	  @class
	  @discussion This is the Titanium BlobStream Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.BlobStream
	*/
	class TITANIUMKIT_EXPORT BlobStream : public IOStream, public JSExport<BlobStream>
	{

	public:

		/*!
		  @method
		  @abstract read
		  @discussion Reads data from this stream into a buffer.
		*/
		virtual std::int32_t read(const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length) override;
		virtual void readAllAsync(const std::shared_ptr<Buffer>& buffer, const std::function<void(const ErrorResponse&, const std::shared_ptr<IOStream>& source)>&) override;

		/*!
		  @method
		  @abstract write
		  @discussion Writes data from a buffer to this stream.
		*/
		virtual std::uint32_t write(const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length) override;

		/*!
		  @method
		  @abstract close
		  @discussion Closes this stream.
		*/
		virtual void close() override;

		/*!
		  @method
		  @abstract construct
		  @discussion Set Blob for this stream
		*/
		virtual void construct(const std::shared_ptr<Blob>& blob);

		BlobStream(const JSContext&) TITANIUM_NOEXCEPT;
		virtual ~BlobStream()                    = default;
		BlobStream(const BlobStream&)            = default;
		BlobStream& operator=(const BlobStream&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		BlobStream(BlobStream&&)                 = default;
		BlobStream& operator=(BlobStream&&)      = default;
#endif

		static void JSExportInitialize();

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		std::shared_ptr<Blob> blob__;
#pragma warning(pop)
	};

} // namespace Titanium
#endif // _TITANIUM_BLOBSTREAM_HPP_