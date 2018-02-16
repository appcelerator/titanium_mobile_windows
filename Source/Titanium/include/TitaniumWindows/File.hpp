/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_FILE_HPP_
#define _TITANIUMWINDOWS_FILE_HPP_

#include "TitaniumWindows_EXPORT.h"
#include "Titanium/Filesystem/File.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace Filesystem
	{
		using namespace HAL;

		/*!
		  @class File
		  @ingroup Titanium.Filesystem.File

		  @discussion This is the Titanium.Filesystem.File implementation for Windows.
		*/
		class TITANIUMWINDOWS_EXPORT File final : public Titanium::Filesystem::File, public JSExport<File>
		{
		public:
			TITANIUM_PROPERTY_UNIMPLEMENTED(executable);
			TITANIUM_PROPERTY_UNIMPLEMENTED(remoteBackup);
			TITANIUM_PROPERTY_UNIMPLEMENTED(symbolicLink);

			virtual bool get_executable() const TITANIUM_NOEXCEPT override;
			virtual bool get_hidden() const TITANIUM_NOEXCEPT override;
			virtual std::string get_name() const TITANIUM_NOEXCEPT override;
			virtual std::string get_nativePath() const TITANIUM_NOEXCEPT override;
			virtual std::shared_ptr<Titanium::Filesystem::File> get_parent() const TITANIUM_NOEXCEPT override;
			virtual bool get_readonly() const TITANIUM_NOEXCEPT override;
			virtual bool get_remoteBackup() const TITANIUM_NOEXCEPT override;
			virtual std::uint64_t get_size() const TITANIUM_NOEXCEPT override;
			virtual bool get_symbolicLink() const TITANIUM_NOEXCEPT override;
			virtual bool get_writable() const TITANIUM_NOEXCEPT override;

			virtual bool copy(const std::string& dest) TITANIUM_NOEXCEPT override;
			virtual bool createDirectory() TITANIUM_NOEXCEPT override;
			virtual bool createFile() TITANIUM_NOEXCEPT override;
			virtual std::chrono::milliseconds createTimestamp() TITANIUM_NOEXCEPT override;
			virtual bool deleteFile() TITANIUM_NOEXCEPT override;
			virtual bool exists() TITANIUM_NOEXCEPT override;
			virtual std::string extension() TITANIUM_NOEXCEPT override;
			virtual std::vector<std::string> getDirectoryListing() TITANIUM_NOEXCEPT override;
			virtual bool isDirectory() TITANIUM_NOEXCEPT override;
			virtual bool isFile() TITANIUM_NOEXCEPT override;
			virtual std::chrono::milliseconds modificationTimestamp() TITANIUM_NOEXCEPT override;
			virtual bool move(const std::string& newpath) TITANIUM_NOEXCEPT override;
			virtual std::shared_ptr<Titanium::Blob> read() TITANIUM_NOEXCEPT override;
			virtual bool rename(const std::string& newname) TITANIUM_NOEXCEPT override;
			virtual std::string resolve() TITANIUM_NOEXCEPT override;
			virtual std::uint64_t spaceAvailable() TITANIUM_NOEXCEPT override;
			virtual bool write(const std::string& data, const bool& append) TITANIUM_NOEXCEPT override;
			virtual bool write(const std::shared_ptr<Titanium::Blob>& data, const bool& append) TITANIUM_NOEXCEPT override;
			virtual bool write(const std::shared_ptr<Titanium::Filesystem::File>& data, const bool& append) TITANIUM_NOEXCEPT override;
			virtual bool write(const std::vector<std::uint8_t>& data, const std::uint32_t& offset, const std::uint32_t& length, const bool& append) override;
			virtual void writeAsync(const std::vector<std::uint8_t>& data, const std::uint32_t& offset, const std::uint32_t& length, const bool& append, const std::function<void(const Titanium::ErrorResponse&, const uint32_t&)>&) override;
			virtual std::vector<std::uint8_t> readBytes(const std::uint32_t& offset, const std::uint32_t& length) const override;
			virtual void readBytesAsync(const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const Titanium::ErrorResponse&, const std::vector<std::uint8_t>&)>&) const override;
			virtual void readAllBytesAsync(const std::function<void(const Titanium::ErrorResponse&, const std::vector<std::uint8_t>&)>&) const override;

			File(const JSContext&) TITANIUM_NOEXCEPT;

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual ~File();
			File(const File&) = default;
			File& operator=(const File&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			File(File&&) = default;
			File& operator=(File&&) = default;
#endif

			static void JSExportInitialize();

			virtual std::vector<std::uint8_t> getContent() const TITANIUM_NOEXCEPT override;

		protected:
		private:
			bool prepareWrite();
			bool write(Windows::Storage::Streams::IBuffer^ buffer);
			bool createDirectory(const std::string& desiredName);

			std::string normalizePath(const std::string& path);
			std::string filename(const std::string& path);

			// Creates a file at the path identified by this file object.
			bool File::createEmptyFile(const std::string& path)
			{
				std::ofstream outfile(path, std::ofstream::out);
				bool fail = outfile.fail();
				outfile.close();
				return !fail;
			}

			bool isFolder() const
			{
				return folder_ != nullptr;
			}

			Windows::Storage::IStorageItem^ getStorageItem() const
			{
				if (file_ == nullptr && folder_ == nullptr) {
					return nullptr;
				}
				if (isFolder()) {
					return folder_;
				}
				return file_;
			}

			Windows::Storage::FileProperties::BasicProperties^ getStorageProperties(Windows::Storage::IStorageItem^ file) const;

			// Get StorageFolder from path. Returns nullptr if access denied or
			// there's no such file.
			Windows::Storage::StorageFolder^ getFolderFromPathSync(::Platform::String^ filename) const;

			Windows::Storage::StorageFolder^ getFolderFromPathSync(const std::string& filename) const
			{
				return getFolderFromPathSync(TitaniumWindows::Utility::ConvertString(filename));
			}

			// Get StorageFile from path. Returns nullptr if access denied or
			// there's no such file.
			Windows::Storage::StorageFile^ getFileFromPathSync(::Platform::String^ filename) const;

			Windows::Storage::StorageFile^ getFileFromPathSync(const std::string& filename) const
			{
				return getFileFromPathSync(TitaniumWindows::Utility::ConvertString(filename));
			}

			Windows::Storage::Streams::IBuffer^ getBufferFromBytes(std::uint8_t* data, std::size_t size, bool append, Windows::Storage::StorageFile^ appendingFile) {
				using namespace Windows::Storage;
				const auto writer = ref new Streams::DataWriter(ref new Streams::InMemoryRandomAccessStream());
				if (append) {
					writeContentFromFile(writer, appendingFile);
				}
				writer->WriteBytes(::Platform::ArrayReference<std::uint8_t>(data, size));
				return writer->DetachBuffer();
			}

			Windows::Storage::Streams::IBuffer^ getBufferFromString(const std::string& string, bool append, Windows::Storage::StorageFile^ appendingFile) {
				using namespace Windows::Storage;
				const auto writer = ref new Streams::DataWriter(ref new Streams::InMemoryRandomAccessStream());
				if (append) {
					writeContentFromFile(writer, appendingFile);
				}
				writer->WriteString(TitaniumWindows::Utility::ConvertUTF8String(string));
				return writer->DetachBuffer();
			}

			std::size_t writeContentFromFile(Windows::Storage::Streams::DataWriter^ writer, Windows::Storage::StorageFile^ file)
			{
				auto content = TitaniumWindows::Utility::GetContentFromFile(file);
				if (content.size() > 0) {
					writer->WriteBytes(::Platform::ArrayReference<std::uint8_t>(&content[0], content.size()));
				}
				return content.size();
			}

#pragma warning(push)
#pragma warning(disable : 4251)
			std::string name_;
			std::string path_;
#pragma warning(pop)
			bool denied_ { false }; // Folder may exist, but we are denied access!

			// We need both file and folder because Windows Runtime
			// distinguishes it.
			Windows::Storage::StorageFile^ file_;
			Windows::Storage::StorageFolder^ folder_;
		};
	} // namespace Filesystem
}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_FILE_HPP_
