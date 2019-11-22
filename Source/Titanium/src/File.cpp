/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/File.hpp"
#include "TitaniumWindows/Blob.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <ppltasks.h>
#include <concrt.h>
#include <collection.h>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/predicate.hpp>

using namespace Windows::Storage;
using namespace Windows::Foundation::Collections;
using namespace concurrency;
using TitaniumWindows::Utility::RunOnUIThread;

namespace TitaniumWindows
{
	namespace Filesystem
	{
		File::File(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Titanium::Filesystem::File(js_context)
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Filesystem::File::ctor");
		}

		// Creates a file at the path identified by this file object.
		bool File::createEmptyFile(const std::string& path)
		{
			try {
				auto separator = path.find_last_of("\\");

				if (separator == std::string::npos) {
					return false;
				}

				const auto folder = getFolderFromPathSync(path.substr(0, separator));
				if (folder) {
					const auto filename = TitaniumWindows::Utility::ConvertUTF8String(path.substr(separator + 1, path.size() - separator - 1));
					bool status = false;
					concurrency::event evt;
					concurrency::create_task(folder->CreateFileAsync(filename)).then([&evt, path, &status](concurrency::task<Windows::Storage::StorageFile^> task) {
						try {
							task.get();
							status = true;
						} catch (...) {
							TITANIUM_LOG_WARN("Unable to create file for ", path);
						}
						evt.set();
					}, concurrency::task_continuation_context::use_arbitrary());
					evt.wait();
					return status;
				}
			} catch (...) {
				TITANIUM_LOG_WARN("Unable to get a folder for ", path);
			}
			return false;
		}

		std::string File::normalizePath(const std::string& path)
		{
			// this assumes we already joined the arguments with separator
			std::string name = static_cast<std::string>(path);
			// Convert "/" to "\\"
			std::replace(name.begin(), name.end(), '/', '\\');
			// remove duplicate separators!
			boost::algorithm::replace_all(name, "\\\\", "\\");
			// remove leading ./
			if (boost::starts_with(name, ".\\")) {
				boost::algorithm::replace_first(name, ".\\", "");
			}
			// remove leading /
			if (boost::starts_with(name, "\\")) {
				boost::algorithm::replace_first(name, "\\", "");
			}
			return name;
		}

		std::string File::filename(const std::string& path)
		{
			size_t seperator = path.find_last_of("\\");
			if (seperator != std::string::npos) {
				return path.substr(seperator + 1, path.size() - seperator - 1);
			}
			return path;
		}

		void File::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
			// TODO: if argument is empty, we assume it's called from initializer.
			if (arguments.empty()) {
				return;
			}

			TITANIUM_ASSERT(arguments.size() > 0);
			TITANIUM_ASSERT(arguments.at(0).IsString());

			// this assumes we already joined the arguments with separator
			std::string name = normalizePath(static_cast<std::string>(arguments.at(0)));

			// if this path is relative path, let's use application installed location path
			if (name.find(":\\") == std::string::npos) {
				static const auto location = TitaniumWindows::Utility::ConvertUTF8String(Windows::ApplicationModel::Package::Current->InstalledLocation->Path);
				path_ = location + "\\" + name;
			} else {
				path_ = name;
			}

			// obtain filename
			name_ = filename(name);

			file_ = getFileFromPathSync(path_);
			if (file_ == nullptr) {
				try {
					folder_ = getFolderFromPathSync(path_);
				}
				catch (Platform::AccessDeniedException^ e) {
					denied_ = true;
				}
			}
		}

		File::~File()
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Filesystem::File::dtor");
		}

		void File::JSExportInitialize()
		{
			JSExport<File>::SetClassVersion(1);
			JSExport<File>::SetParent(JSExport<Titanium::Filesystem::File>::Class());
		}

		// Creates a directory at the path identified by this file object.
		bool File::createDirectory(const std::string& path)
		{
			auto separator = path.find_last_of("\\");
			const auto parent = path.substr(0, separator);
			const auto desiredName = path.substr(separator + 1);

			// Folder may exist but we are denied access to it. How do we create the subfolder then?
			try {
				const auto folder = getFolderFromPathSync(parent);
				bool result = false;
				concurrency::event event;
				task<StorageFolder^>(folder->CreateFolderAsync(TitaniumWindows::Utility::ConvertUTF8String(desiredName))).then([&result, &event, this](task<StorageFolder^> task) {
						try {
							task.get();
							result = true;
						} catch (Platform::Exception^ ex) {
							TITANIUM_API_LOG_WARN(TitaniumWindows::Utility::ConvertString(ex->Message));
						} catch (...) {
							TITANIUM_API_LOG_WARN("Unknown error while createDirectory");
						}
						event.set();
					},
					concurrency::task_continuation_context::use_arbitrary());
				event.wait();

				return result;
			} catch (Platform::AccessDeniedException^ e) {
				TITANIUM_API_LOG_WARN("createDirectory: Denied access to parent folder ", parent);
			} catch (Platform::Exception^ ex) {
				TITANIUM_API_LOG_WARN(TitaniumWindows::Utility::ConvertString(ex->Message));
			} catch (...) {
				TITANIUM_API_LOG_WARN("Unknown error while createDirectory");
			}
			return false;
		}

		FileProperties::BasicProperties^ File::getStorageProperties(IStorageItem^ file) const
		{
			try {
				if (file == nullptr) {
					return nullptr;
				}
				FileProperties::BasicProperties^ properties = nullptr;
				concurrency::event event;
				task<FileProperties::BasicProperties^>(file->GetBasicPropertiesAsync()).then([&properties, &event](task<FileProperties::BasicProperties^> task) {
						try {
							properties = task.get();
						} catch (Platform::Exception^ ex) {
							TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
						} catch (...) {
							TITANIUM_LOG_DEBUG("Unknown error while getStorageProperties");
						}
						event.set();
					},
					concurrency::task_continuation_context::use_arbitrary());
				event.wait();

				return properties;
			} catch (Platform::Exception^ ex) {
				TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
			} catch (...) {
				TITANIUM_LOG_DEBUG("Unknown error while getStorageProperties");
			}
			return nullptr;
		}

		Windows::Storage::StorageFolder^ File::getFolderFromPathSync(Platform::String^ filename) const
		{
			Windows::Storage::StorageFolder^ storageFolder = nullptr;
			bool denied = false;
			concurrency::event event;
			task<StorageFolder^>(Windows::Storage::StorageFolder::GetFolderFromPathAsync(filename)).then([&storageFolder, &denied, &event](task<StorageFolder^> task) {
					try {
						storageFolder = task.get();
					} catch (Platform::AccessDeniedException^ e) {
						denied = true;
					} catch (Platform::Exception^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					} catch (...) {
						TITANIUM_LOG_DEBUG("Unknown error while getFolderFromPathSync");
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			if (denied) {
				throw ref new Platform::AccessDeniedException();
			}
			return storageFolder;
		}

		Windows::Storage::StorageFile^ File::getFileFromPathSync(Platform::String^ filename) const
		{
			Windows::Storage::StorageFile^ storageFile = nullptr;
			concurrency::event event;
			task<StorageFile^>(Windows::Storage::StorageFile::GetFileFromPathAsync(filename)).then([&storageFile, &event](task<StorageFile^> task) {
					try {
						storageFile = task.get();
					} catch (Platform::Exception^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					} catch (...) {
						TITANIUM_LOG_DEBUG("Unknown error while getFileFromPathSync");
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return storageFile;
		}

		bool File::get_executable() const TITANIUM_NOEXCEPT
		{
			// Just return false here because Windows Runtime API doesn't
			// provide a way to get executable attribute
			return false;
		}

		bool File::get_hidden() const TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}
			using namespace Windows::Storage;
			return ((item->Attributes & FileAttributes::Normal) != FileAttributes::Normal);
		}

		std::string File::get_name() const TITANIUM_NOEXCEPT
		{
			return name_;
		}

		std::string File::get_nativePath() const TITANIUM_NOEXCEPT
		{
			if (folder_) {
				return path_ + (boost::algorithm::ends_with(path_, "\\") ? "" : "\\");
			}
			return path_;
		}

		std::shared_ptr<Titanium::Filesystem::File> File::get_parent() const TITANIUM_NOEXCEPT
		{
			const std::string path = path_;
			const std::string parent = path.substr(0, path.find_last_of("\\"));

			static JSObject File = get_context().CreateObject();
			static std::once_flag of;
			std::call_once(of, [=] {
				JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
				TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
				JSObject Titanium = static_cast<JSObject>(Titanium_property);

				JSValue FS_property = Titanium.GetProperty("Filesystem");
				TITANIUM_ASSERT(FS_property.IsObject());  // precondition
				JSObject FS = static_cast<JSObject>(FS_property);

				JSValue File_property = FS.GetProperty("File");
				TITANIUM_ASSERT(File_property.IsObject());  // precondition
				File = static_cast<JSObject>(File_property);
			});

			return File.CallAsConstructor(parent).GetPrivate<Titanium::Filesystem::File>();
		}

		bool File::get_readonly() const TITANIUM_NOEXCEPT
		{
			return !get_writable();
		}

		bool File::get_remoteBackup() const TITANIUM_NOEXCEPT
		{
			return false;
		}

		bool File::get_symbolicLink() const TITANIUM_NOEXCEPT
		{
			return false;
		}

		bool File::get_writable() const TITANIUM_NOEXCEPT
		{
			if (denied_) {
				return false;
			}
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}
			using namespace Windows::Storage;
			return ((item->Attributes & FileAttributes::ReadOnly) != FileAttributes::ReadOnly);
		}

		std::uint64_t File::get_size() const TITANIUM_NOEXCEPT
		{
			const auto prop = getStorageProperties(getStorageItem());
			if (prop == nullptr) {
				return 0;
			} else {
				return prop->Size;
			}
		}

		bool File::copy(const std::string& destinationPath) TITANIUM_NOEXCEPT
		{
			// copy will never work for folder
			if (isFolder()) {
				return false;
			}
			// FIXME Need to normalize the path like we do in constructor!
			auto path = normalizePath(destinationPath);
			auto fileToReplace = this->getFileFromPathSync(path);

			// if destination file is not found, create new file and try again
			if (fileToReplace == nullptr) {
				const bool created = createEmptyFile(path);
				if (created) {
					fileToReplace = getFileFromPathSync(path);
				} else {
					return false;
				}
			}

			concurrency::event event;
			bool result = false;
			create_task(file_->CopyAndReplaceAsync(fileToReplace)).then([&result, &event](task<void> task) {
					try {
						task.get();
						result = true;
					} catch (Platform::Exception^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					} catch (...) {
						TITANIUM_LOG_DEBUG("Unknown error while copy");
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return result;
		}

		bool File::createDirectory() TITANIUM_NOEXCEPT
		{
			// check that parent exists, and if not, create it first!
			auto parent = get_parent();
			if (parent == nullptr) {
				return false;
			}
			if (!parent->exists() && !parent->createDirectory()) {
				return false;
			}
			const bool result = createDirectory(path_);
			if (result) {
				// because this creates new directory which didn't exist, update the folder_ member
				folder_ = getFolderFromPathSync(path_);
				file_ = nullptr;
			}
			return result;
		}

		bool File::createFile() TITANIUM_NOEXCEPT
		{
			const bool result = createEmptyFile(path_);
			if (result) {
				// because this creates new file which didn't exist, update the
				// file_ member
				file_ = getFileFromPathSync(path_);
				folder_ = nullptr;
			}
			return result;
		}

		std::chrono::milliseconds File::createTimestamp() TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return std::chrono::milliseconds(0);
			} else {
				return TitaniumWindows::Utility::GetMSecSinceEpoch(item->DateCreated);
			}
		}

		bool File::deleteFile() TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}

			bool result = false;
			concurrency::event event;
			create_task(item->DeleteAsync()).then([&result, &event](task<void> task) {
				try {
					task.get();
					result = true;
				} catch (Platform::Exception^ ex) {
					TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
				} catch (...) {
					TITANIUM_LOG_DEBUG("Unknown error while deleteFile");
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();
			// release the file object because file is deleted
			if (result) {
				file_ = nullptr;
				folder_ = nullptr;
			}
			return result;
		}

		bool File::exists() TITANIUM_NOEXCEPT
		{
			return denied_ || (getStorageItem() != nullptr);
		}

		std::string File::extension() TITANIUM_NOEXCEPT
		{
			const std::string path = path_;
			return path.substr(path.find_last_of(".") + 1);
		}

		std::vector<std::string> File::getDirectoryListing() TITANIUM_NOEXCEPT
		{
			std::vector<std::string> filenames;
			if (isFile() || !exists()) {
				return filenames;
			}

			// Get folders in folder
			concurrency::event folderEvent;
			create_task(folder_->GetFoldersAsync()).then([&filenames, &folderEvent](task<IVectorView<StorageFolder^>^> task) {
					try {
						auto folders = task.get();
						std::for_each(begin(folders), end(folders), [&filenames](StorageFolder^ folder) {
							filenames.push_back(TitaniumWindows::Utility::ConvertUTF8String(folder->Name));
						});
					} catch (Platform::Exception^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					} catch (...) {
						TITANIUM_LOG_DEBUG("Unknown error while getDirectoryListing");
					}
					folderEvent.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			folderEvent.wait();

			// Get files in folder
			concurrency::event fileEvent;
			create_task(folder_->GetFilesAsync()).then([&filenames, &fileEvent](task<IVectorView<StorageFile^>^> task) {
					try {
						auto files = task.get();
						std::for_each(begin(files), end(files), [&filenames](StorageFile^ file) {
							filenames.push_back(TitaniumWindows::Utility::ConvertUTF8String(file->Name));
						});
					} catch (Platform::Exception^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					} catch (...) {
						TITANIUM_LOG_DEBUG("Unknown error while getDirectoryListing");
					}
					fileEvent.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			fileEvent.wait();

			return filenames;
		}

		bool File::isDirectory() TITANIUM_NOEXCEPT
		{
			if (denied_) {
				return true;
			}
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}
			using namespace Windows::Storage;
			return ((item->Attributes & FileAttributes::Directory) == FileAttributes::Directory);
		}

		bool File::isFile() TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}
			using namespace Windows::Storage;
			return ((item->Attributes & FileAttributes::Directory) != FileAttributes::Directory);
		}

		std::chrono::milliseconds File::modificationTimestamp() TITANIUM_NOEXCEPT
		{
			const auto prop = getStorageProperties(getStorageItem());
			if (prop == nullptr) {
				return std::chrono::milliseconds(0);
			} else {
				return TitaniumWindows::Utility::GetMSecSinceEpoch(prop->DateModified);
			}
		}

		bool File::move(const std::string& newpath) TITANIUM_NOEXCEPT
		{
			auto path = normalizePath(newpath);

			// if this item is folder, call rename
			if (isFolder()) {
				return this->rename(path);
			}

			// make sure to create detination file before getting StorageFile
			// otherwise GetFileFromPathSync will return nullptr
			if (!createEmptyFile(path)) {
				return false;
			}

			// retrieve destination file
			StorageFile^ fileToReplace = getFileFromPathSync(path);

			if (fileToReplace == nullptr) {
				return false;
			}

			bool result = false;
			concurrency::event event;
			create_task(this->file_->MoveAndReplaceAsync(fileToReplace)).then([&result, &event](task<void> task) {
					try {
						task.get();
						result = true;
					} catch (Platform::Exception^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					} catch (...) {
						TITANIUM_LOG_DEBUG("Unknown error while move");
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			// release the file object because file is deleted
			if (result) {
				file_ = nullptr;
				folder_ = nullptr;
			}

			return result;
		}

		std::shared_ptr<Titanium::Blob> File::read() TITANIUM_NOEXCEPT
		{
			if (file_ == nullptr) {
				return nullptr;
			}
			auto Blob = get_context().CreateObject(JSExport<TitaniumWindows::Blob>::Class());
			auto blob = Blob.CallAsConstructor();
			auto blob_ptr = blob.GetPrivate<TitaniumWindows::Blob>();

			blob_ptr->construct(file_);

			return blob.GetPrivate<Titanium::Blob>();
		}

		bool File::rename(const std::string& desiredName) TITANIUM_NOEXCEPT
		{
			auto path = normalizePath(desiredName);
			auto item = getStorageItem();
			concurrency::event event;
			bool result = false;
			create_task(item->RenameAsync(TitaniumWindows::Utility::ConvertUTF8String(path))).then([&result, &event](task<void> task) {
					try {
						task.get();
						result = true;
					} catch (Platform::Exception^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					} catch (...) {
						TITANIUM_LOG_DEBUG("Unknown error while rename");
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return result;
		}

		std::string File::resolve() TITANIUM_NOEXCEPT
		{
			return path_;
		}

		std::uint64_t File::spaceAvailable() TITANIUM_NOEXCEPT
		{
			const auto prop = getStorageProperties(getStorageItem());
			const auto propertiesName = ref new Platform::Collections::Vector<Platform::String^>();
			propertiesName->Append("System.FreeSpace");
			std::uint64_t freeSpace = 0;
			concurrency::event event;
			task<IMap<Platform::String^, Platform::Object^>^>(prop->RetrievePropertiesAsync(propertiesName)).then([&freeSpace, &event](task<IMap<Platform::String^, Platform::Object^>^> task) {
					try {
						const auto extraProperties = task.get();
						freeSpace = (std::uint64_t)extraProperties->Lookup("System.FreeSpace");
					} catch (Platform::Exception^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					} catch (...) {
						TITANIUM_LOG_DEBUG("Unknown error while spaceAvailable");
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();
			return freeSpace;
		}

		bool File::prepareWrite() 
		{
			// if this item represents folder, write will never work
			if (isFolder()) {
				TITANIUM_LOG_WARN("File::write: Can't write to directory");
				return false;
			}

			if (file_ == nullptr) {
				// create empty file, then retrieve StorageFile object
				if (!createEmptyFile(path_)) {
					TITANIUM_LOG_WARN("File::write: Can't write to file");
					return false;
				}
				file_ = getFileFromPathSync(path_);
				if (file_ == nullptr) {
					TITANIUM_LOG_WARN("File::write: Can't get file");
					return false;
				}
			}
			return true;
		}

		bool File::write(const std::string& data, const bool& append) TITANIUM_NOEXCEPT
		{
			if (!prepareWrite()) {
				return false;
			}

			return write(getBufferFromString(data, append, file_));
		}

		bool File::write(const std::shared_ptr<Titanium::Blob>& data, const bool& append) TITANIUM_NOEXCEPT
		{
			if (!prepareWrite()) {
				return false;
			}

			if (data->get_size() > 0) {
				return write(getBufferFromBytes(&data->getData()[0], data->get_size(), append, file_));
			} else {
				return write(ref new Streams::Buffer(0));
			}
		}

		bool File::write(const std::shared_ptr<Titanium::Filesystem::File>& data, const bool& append) TITANIUM_NOEXCEPT
		{
			if (!prepareWrite()) {
				return false;
			}

			auto content = data->getContent();
			if (content.size() > 0) {
				return write(getBufferFromBytes(&content[0], content.size(), append, file_));
			} else {
				return write(ref new Streams::Buffer(0));
			}
		}

		bool File::write(Streams::IBuffer^ buffer)
		{
			if (buffer == nullptr) {
				TITANIUM_LOG_DEBUG("Can't get content from Ti.Filesystem.File.write(content)");
				return false;
			}

			bool result = false;
			concurrency::event event;
			task<void>(FileIO::WriteBufferAsync(file_, buffer)).then([&result, &event](task<void> task) {
					try {
						task.get();
						result = true;
					} catch (Platform::Exception^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					} catch (...) {
						TITANIUM_LOG_DEBUG("Unknown error while write");
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return result;
		}

		std::vector<std::uint8_t> File::getContent() const TITANIUM_NOEXCEPT
		{
			return TitaniumWindows::Utility::GetContentFromFile(file_);
		}

		std::vector<std::uint8_t> File::readBytes(const std::uint32_t& offset, const std::uint32_t& length) const 
		{
			using namespace Windows::Storage::Streams;

			std::vector<std::uint8_t> data;

			try {
				concurrency::event evt;
				task<IRandomAccessStreamWithContentType^>(file_->OpenReadAsync()).then([offset, length, &data, &evt](task<IRandomAccessStreamWithContentType ^> task) {
					try {
						const auto stream = task.get();
						const auto buffer = ref new Buffer(length);
						stream->Seek(offset);
						concurrency::task<IBuffer^>(stream->ReadAsync(buffer, buffer->Capacity, InputStreamOptions::Partial)).then([&data, &evt](concurrency::task<IBuffer^> task) {
							try {
								const auto buffer = task.get();
								data = TitaniumWindows::Utility::GetContentFromBuffer(buffer);
							} catch (Platform::Exception^ ex) {
								TITANIUM_LOG_WARN(TitaniumWindows::Utility::ConvertString(ex->Message));
							} catch (...) {
								TITANIUM_LOG_WARN("Unknown error while readBytes");
							}
							evt.set();
						}, concurrency::task_continuation_context::use_arbitrary());
					} catch (Platform::Exception^ ex) {
						TITANIUM_LOG_WARN(TitaniumWindows::Utility::ConvertString(ex->Message));
						evt.set();
					} catch (...) {
						TITANIUM_LOG_WARN("Unknown error while readBytes");
						evt.set();
					}
				}, concurrency::task_continuation_context::use_arbitrary());
				evt.wait();
			} catch (Platform::Exception^ ex) {
				TITANIUM_LOG_WARN(TitaniumWindows::Utility::ConvertString(ex->Message));
			} catch (...) {
				TITANIUM_LOG_WARN("Unknown error while readBytes");
			}

			return data;
		}

		void File::readBytesAsync(const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const Titanium::ErrorResponse&, const std::vector<std::uint8_t>&)>& callback) const
		{
			using namespace Windows::Storage::Streams;

			try {
				task<IRandomAccessStreamWithContentType^>(file_->OpenReadAsync()).then([offset, length, callback](task<IRandomAccessStreamWithContentType ^> task) {
					try {
						const auto stream = task.get();
						const auto buffer = ref new Buffer(length);
						stream->Seek(offset);
						concurrency::task<IBuffer^>(stream->ReadAsync(buffer, buffer->Capacity, InputStreamOptions::Partial)).then([callback](concurrency::task<IBuffer^> task) {
							try {
								RunOnUIThread([task, callback]() {
									const Titanium::ErrorResponse errorResponse;
									const auto buffer = task.get();
									callback(errorResponse, TitaniumWindows::Utility::GetContentFromBuffer(buffer));
								});
							} catch (Platform::COMException^ ex) {
								RunOnUIThread([ex, callback]() {
									callback(TitaniumWindows::Utility::GetTiErrorResponse(ex), std::vector<std::uint8_t>());
								});
							} catch (Platform::Exception^ ex) {
								RunOnUIThread([ex, callback]() {
									callback(TitaniumWindows::Utility::GetTiErrorResponse(ex), std::vector<std::uint8_t>());
								});
							} catch (...) {
								RunOnUIThread([callback]() {
									callback(TitaniumWindows::Utility::GetTiErrorResponse("Unknown error"), std::vector<std::uint8_t>());
								});
							}
						});
					} catch (Platform::COMException^ ex) {
						RunOnUIThread([ex, callback]() {
							callback(TitaniumWindows::Utility::GetTiErrorResponse(ex), std::vector<std::uint8_t>());
						});
					} catch (Platform::Exception^ ex) {
						RunOnUIThread([ex, callback]() {
							callback(TitaniumWindows::Utility::GetTiErrorResponse(ex), std::vector<std::uint8_t>());
						});
					} catch (...) {
						RunOnUIThread([callback]() {
							callback(TitaniumWindows::Utility::GetTiErrorResponse("Unknown error"), std::vector<std::uint8_t>());
						});
					}
				});
			} catch (Platform::COMException^ ex) {
				RunOnUIThread([ex, callback]() {
					callback(TitaniumWindows::Utility::GetTiErrorResponse(ex), std::vector<std::uint8_t>());
				});
			} catch (Platform::Exception^ ex) {
				RunOnUIThread([ex, callback]() {
					callback(TitaniumWindows::Utility::GetTiErrorResponse(ex), std::vector<std::uint8_t>());
				});
			} catch (...) {
				RunOnUIThread([callback]() {
					callback(TitaniumWindows::Utility::GetTiErrorResponse("Unknown error"), std::vector<std::uint8_t>());
				});
			}
		}

		void File::readAllBytesAsync(const std::function<void(const Titanium::ErrorResponse&, const std::vector<std::uint8_t>&)>& callback) const 
		{
			using namespace Windows::Storage::Streams;

			concurrency::task<IBuffer^>(FileIO::ReadBufferAsync(file_)).then([callback](concurrency::task<IBuffer ^ > task) {
				try {
					RunOnUIThread([task, callback]() {
						const Titanium::ErrorResponse errorResponse;
						const auto buffer = task.get();
						callback(errorResponse, TitaniumWindows::Utility::GetContentFromBuffer(buffer));
					});
				} catch (Platform::COMException^ ex) {
					RunOnUIThread([ex, callback]() {
						callback(TitaniumWindows::Utility::GetTiErrorResponse(ex), std::vector<std::uint8_t>());
					});
				} catch (Platform::Exception^ ex) {
					RunOnUIThread([ex, callback]() {
						callback(TitaniumWindows::Utility::GetTiErrorResponse(ex), std::vector<std::uint8_t>());
					});
				} catch (...) {
					RunOnUIThread([callback]() {
						callback(TitaniumWindows::Utility::GetTiErrorResponse("Unknown error"), std::vector<std::uint8_t>());
					});
				}
			});
		}

		bool File::write(const std::vector<std::uint8_t>& data, const std::uint32_t& offset, const std::uint32_t& length, const bool& append)
		{
			if (!prepareWrite()) {
				return false;
			}
			auto read_data = const_cast<std::vector<std::uint8_t>&>(data);
			return write(getBufferFromBytes(&read_data[offset], length, append, file_));
		}

		void File::writeAsync(const std::vector<std::uint8_t>& data, const std::uint32_t& offset, const std::uint32_t& length, const bool& append, const std::function<void(const Titanium::ErrorResponse&, const uint32_t&)>& callback)
		{
			if (!prepareWrite()) {
				RunOnUIThread([callback]() {
					Titanium::ErrorResponse error;
					error.code = -1;
					error.success = false;
					error.error = "File::writeAsync: Failed to get file instance";
					callback(error, 0);
				});
				return;
			}
			auto read_data = const_cast<std::vector<std::uint8_t>&>(data);
			const auto buffer = getBufferFromBytes(&read_data[offset], length, append, file_);
			task<void>(FileIO::WriteBufferAsync(file_, buffer)).then([length, callback](task<void> task) {
				try {
					task.get();
					RunOnUIThread([length, callback]() {
						const Titanium::ErrorResponse error;
						callback(error, length);
					});
				} catch (Platform::COMException^ ex) {
					RunOnUIThread([ex, callback]() {
						callback(TitaniumWindows::Utility::GetTiErrorResponse(ex), 0);
					});
				} catch (Platform::Exception^ ex) {
					RunOnUIThread([ex, callback]() {
						callback(TitaniumWindows::Utility::GetTiErrorResponse(ex), 0);
					});
				} catch (...) {
					RunOnUIThread([callback]() {
						callback(TitaniumWindows::Utility::GetTiErrorResponse("Unknown error"), 0);
					});
				}
			});

		}

	} // namespace Filesystem
} // namespace TitaniumWindows
