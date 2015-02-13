/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_BLOB_HPP_
#define _TITANIUMWINDOWS_BLOB_HPP_

#include "detail/BlobBase.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	namespace BlobModule
	{
		enum class TYPE {
			IMAGE = 0,
			FILE = 1,
			DATA = 2
		};
	}

	/*!
	  @class

	  @discussion This is the Titanium.Blob implementation for Windows.
    */
	class TITANIUMWINDOWS_EXPORT Blob final : public Titanium::Blob, public JSExport<Blob>
	{
	public:
		virtual std::vector<unsigned char> getData() TITANIUM_NOEXCEPT override;
		::Platform::Guid getImageEncoder();

		void construct(Windows::Storage::StorageFile^ file);
		virtual void construct(std::vector<unsigned char> data) TITANIUM_NOEXCEPT override;

		Blob(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

		virtual ~Blob();
		Blob(const Blob&) = default;
		Blob& operator=(const Blob&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Blob(Blob&&) = default;
		Blob& operator=(Blob&&) = default;
#endif

		static void JSExportInitialize();

		virtual unsigned get_length() const TITANIUM_NOEXCEPT override;
		virtual JSValue get_file() const TITANIUM_NOEXCEPT override;
		virtual unsigned get_height() const TITANIUM_NOEXCEPT override;
		virtual std::string get_mimeType() const TITANIUM_NOEXCEPT override;
		virtual std::string get_nativePath() const TITANIUM_NOEXCEPT override;
		virtual unsigned get_size() const TITANIUM_NOEXCEPT override;
		virtual std::string get_text() const TITANIUM_NOEXCEPT override;
		virtual unsigned get_width() const TITANIUM_NOEXCEPT override;
		virtual void append(std::shared_ptr<Titanium::Blob>&) TITANIUM_NOEXCEPT override;

	protected:
	private:
#pragma warning(push)
#pragma warning(disable : 4251)
		std::string path_;
		std::string mimetype_;
		unsigned width_;
		unsigned height_;
		BlobModule::TYPE type_;
		std::vector<unsigned char> data_;
#pragma warning(pop)
	};

}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_BLOB_HPP_
