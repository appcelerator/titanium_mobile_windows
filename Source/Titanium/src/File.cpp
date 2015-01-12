/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "File.hpp"
#include "Titanium/detail/TiBase.hpp"
#include <iostream>
#include <objbase.h>
#include <ppltasks.h>
#include <collection.h>
#include "Blob.hpp"

using namespace Windows::Storage;
using namespace Windows::Foundation::Collections;
using namespace concurrency;

namespace TitaniumWindows { namespace Filesystem {

  File::File(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::Filesystem::File(js_context) {
    TITANIUM_LOG_DEBUG("TitaniumWindows::Filesystem::File::ctor Initialize");
  }

  File::File(const File& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::Filesystem::File(rhs, arguments) {
    TITANIUM_LOG_DEBUG("TitaniumWindows::Filesystem::File::ctor CallAsConstructor");

    TITANIUM_ASSERT(!arguments.empty());
    TITANIUM_ASSERT(arguments.at(0).IsString());

    // this assumes we already joins the arguments with separater
    std::string name = static_cast<std::string>(arguments.at(0));

    const auto location = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
    // if this path is relative path, let's use application installed location path
    if (name.find(":\\") == std::string::npos) {
      path_ = TitaniumWindows::Utility::ConvertString(location) + "\\" + name;
    }
    else {
      path_ = name;
    }

    name_ = name;

    file_ = getFileFromPathSync(path_);
    if (file_ == nullptr) {
      folder_ = getFolderFromPathSync(path_);
    }
  }

  File::~File() {
    TITANIUM_LOG_DEBUG("TitaniumWindows::Filesystem::File::dtor");
  }

  void File::JSExportInitialize() {
    JSExport<File>::SetClassVersion(1);
    JSExport<File>::SetParent(JSExport<Titanium::Filesystem::File>::Class());
  }

  // Creates a directory at the path identified by this file object.
  bool File::createDirectory(const std::string& path) {
    auto separator = path.find_last_of("\\");
    const auto parent = path.substr(0, separator);
    const auto desiredName = path.substr(separator + 1);

    const auto folder = getFolderFromPathSync(parent);

    bool result = false;
    concurrency::event event;
    task<StorageFolder^>(folder->CreateFolderAsync(TitaniumWindows::Utility::ConvertString(desiredName))).then([&result, &event](task<StorageFolder^> task) {
      try {
        task.get();
        result = true;
      } catch (Platform::COMException^ ex) {
        TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
      }
      event.set();
    }, concurrency::task_continuation_context::use_arbitrary());
    event.wait();

    return result;
  }

  FileProperties::BasicProperties^ File::getStorageProperties(IStorageItem^ file) const {
    try {
      if (file == nullptr) {
        return nullptr;
      }
      FileProperties::BasicProperties^ properties = nullptr;
      concurrency::event event;
      task<FileProperties::BasicProperties^>(file->GetBasicPropertiesAsync()).then([&properties, &event](task<FileProperties::BasicProperties^> task) {
        try {
          properties = task.get();
        }
        catch (Platform::COMException^ ex) {
          TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
        }
        event.set();
      }, concurrency::task_continuation_context::use_arbitrary());
      event.wait();

      return properties;
    }
    catch (Platform::COMException^ ex) {
      TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
      return nullptr;
    }
  }

  Windows::Storage::StorageFolder^ File::getFolderFromPathSync(Platform::String^ filename) const {
    Windows::Storage::StorageFolder^ storageFolder = nullptr;
    concurrency::event event;
    task<StorageFolder ^>(Windows::Storage::StorageFolder::GetFolderFromPathAsync(filename)).then([&storageFolder, &event](task<StorageFolder^> task) {
      try {
        storageFolder = task.get();
      }
      catch (Platform::COMException^ ex) {
        storageFolder = nullptr;
      }
      event.set();
    }, concurrency::task_continuation_context::use_arbitrary());
    event.wait();

    return storageFolder;
  }

  Windows::Storage::StorageFile^ File::getFileFromPathSync(Platform::String^ filename) const {
    Windows::Storage::StorageFile^ storageFile = nullptr;
    concurrency::event event;
    task<StorageFile^>(Windows::Storage::StorageFile::GetFileFromPathAsync(filename)).then([&storageFile, &event](task<StorageFile^> task) {
      try {
        storageFile = task.get();
      }
      catch (Platform::COMException^ ex) {
        storageFile = nullptr;
      }
      event.set();
    }, concurrency::task_continuation_context::use_arbitrary());
    event.wait();

    return storageFile;
  }

  bool File::get_executable() const TITANIUM_NOEXCEPT {
    // Just return false here because Windows Runtime API doesn't
    // privide a way to get executable attribute
    return false;
  }
  bool File::get_hidden() const TITANIUM_NOEXCEPT {
    auto item = getStorageItem();
    if (item == nullptr) {
      return false;
    }
    using namespace Windows::Storage;
    return ((item->Attributes & FileAttributes::Normal) != FileAttributes::Normal);
  }
  std::string File::get_name() const TITANIUM_NOEXCEPT {
    return name_;
  }
  std::string File::get_nativePath() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_DEBUG("TitaniumWindows::File::get_nativePath");
    return path_;
  }
  JSValue File::get_parent() const TITANIUM_NOEXCEPT {
    const std::string path = path_;
    const std::string parent = path.substr(0, path.find_last_of("\\"));

    auto File = get_context().CreateObject(JSExport<Titanium::Filesystem::File>::Class());
    return File.CallAsConstructor(parent);
  }
  bool File::get_readonly() const TITANIUM_NOEXCEPT {
    auto item = getStorageItem();
    if (item == nullptr) {
      return false;
    }
    using namespace Windows::Storage;
    return ((item->Attributes & FileAttributes::ReadOnly) == FileAttributes::ReadOnly);
  }
  bool File::get_remoteBackup() const TITANIUM_NOEXCEPT {
    return false;
  }
  bool File::get_symbolicLink() const TITANIUM_NOEXCEPT {
    return false;
  }

  bool File::get_writable() const TITANIUM_NOEXCEPT {
    auto item = getStorageItem();
    if (item == nullptr) {
      return false;
    }
    using namespace Windows::Storage;
    return ((item->Attributes & FileAttributes::ReadOnly) != FileAttributes::ReadOnly);
  }

  unsigned File::get_size() const TITANIUM_NOEXCEPT {
    const auto prop = getStorageProperties(getStorageItem());
    if (prop == nullptr) {
      return 0;
    }
    else {
      return prop->Size;
    }
  }

  bool File::append(const JSValue& data) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::append: Unimplemented");
    return false;
  }

  bool File::copy(const std::string& destinationPath) TITANIUM_NOEXCEPT {
    // copy will never work for folder
    if (isFolder()) {
      return false;
    }

    auto fileToReplace = this->getFileFromPathSync(destinationPath);

    // if destination file is not found, create new file and try again
    if (fileToReplace == nullptr) {
      const bool created = createEmptyFile(destinationPath);
      if (created) {
        fileToReplace = getFileFromPathSync(destinationPath);
      }
      else {
        return false;
      }
    }

    concurrency::event event;
    bool result = false;
    task<void>(file_->CopyAndReplaceAsync(fileToReplace)).then([&result, &event](task<void> task) {
      try {
        task.get();
        result = true;
      }
      catch (Platform::COMException^ ex) {
        TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
      }
      event.set();
    }, concurrency::task_continuation_context::use_arbitrary());
    event.wait();

    return result;
  }

  bool File::createDirectory() TITANIUM_NOEXCEPT {
    const bool result = createDirectory(path_);
    if (result) {
      // because this creates new directory which didn't exit, update the folder_ member
      folder_ = getFolderFromPathSync(path_);
      file_ = nullptr;
    }
    return result;
  }
  bool File::createFile() TITANIUM_NOEXCEPT {
    const bool result = createEmptyFile(path_);
    if (result) {
      // because this creates new file which didn't exit, update the
      // file_ member
      file_ = getFileFromPathSync(TitaniumWindows::Utility::ConvertString(path_));
      folder_ = nullptr;
    }
    return result;
  }
  unsigned File::createTimestamp() TITANIUM_NOEXCEPT {
    auto item = getStorageItem();
    if (item == nullptr) {
      return 0;
    }
    else {
      return TitaniumWindows::Utility::GetMSecSinceEpoch(item->DateCreated);
    }
  }

  bool File::deleteDirectory(bool recursive) TITANIUM_NOEXCEPT {
    return deleteFile();
  }

  bool File::deleteFile() TITANIUM_NOEXCEPT {
    auto item = getStorageItem();
    if (item == nullptr) {
      return false;
    }
    bool result = false;
    concurrency::event event;
    task<void>(item->DeleteAsync()).then([&result, &event](task<void> task) {
      try {
        task.get();
        result = true;
      } catch (Platform::COMException^ ex) {
        TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
      }
      event.set();
    }, concurrency::task_continuation_context::use_arbitrary());
    event.wait();
    // release the file object because file is deleted
    if (result) {
      file_   = nullptr;
      folder_ = nullptr;
    }
    return result;
  
  }
  bool File::exists() TITANIUM_NOEXCEPT {
    return (getStorageItem() != nullptr);
  }

  std::string File::extension() TITANIUM_NOEXCEPT {
    const std::string path = path_;
    return path.substr(path.find_last_of(".") + 1);
  }
  std::vector<JSValue> File::getDirectoryListing() TITANIUM_NOEXCEPT {
    std::vector<JSValue> filenames;

    const auto ctx = get_context();

    // Get folders in folder
    concurrency::event folderEvent;
    task<IVectorView<StorageFolder^>^>(folder_->GetFoldersAsync()).then([&ctx, &filenames, &folderEvent](task<IVectorView<StorageFolder^>^> task) {
      try {
        auto folders = task.get();
        std::for_each(begin(folders), end(folders), [&ctx, &filenames](StorageFolder^ folder) {
          filenames.push_back(ctx.CreateString(TitaniumWindows::Utility::ConvertString(folder->Name)));
        });
      }
      catch (Platform::COMException^ ex) {
        TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
      }
      folderEvent.set();
    }, concurrency::task_continuation_context::use_arbitrary());
    folderEvent.wait();

    // Get files in folder
    concurrency::event fileEvent;
    task<IVectorView<StorageFile^>^>(folder_->GetFilesAsync()).then([&ctx, &filenames, &fileEvent](task<IVectorView<StorageFile^>^> task) {
      try {
        auto files = task.get();
        std::for_each(begin(files), end(files), [&ctx, &filenames](StorageFile^ file) {
          filenames.push_back(ctx.CreateString(TitaniumWindows::Utility::ConvertString(file->Name)));
        });
      }
      catch (Platform::COMException^ ex) {
        TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
      }
      fileEvent.set();
    }, concurrency::task_continuation_context::use_arbitrary());
    fileEvent.wait();

    return filenames;
  }

  bool File::isDirectory() TITANIUM_NOEXCEPT {
    auto item = getStorageItem();
    if (item == nullptr) {
      return false;
    }
    using namespace Windows::Storage;
    return ((item->Attributes & FileAttributes::Directory) == FileAttributes::Directory);
  }

  bool File::isFile() TITANIUM_NOEXCEPT {
    auto item = getStorageItem();
    if (item == nullptr) {
      return false;
    }
    using namespace Windows::Storage;
    return ((item->Attributes & FileAttributes::Directory) != FileAttributes::Directory);
  }
  unsigned File::modificationTimestamp() TITANIUM_NOEXCEPT {
    const auto prop = getStorageProperties(getStorageItem());
    if (prop == nullptr) {
      return 0;
    }
    else {
      return TitaniumWindows::Utility::GetMSecSinceEpoch(prop->DateModified);
    }
  }
  bool File::move(const std::string& newpath) TITANIUM_NOEXCEPT {
    // if this item is folder, call rename
    if (isFolder()) {
      return this->rename(newpath);
    }

    // make sure to create detination file before getting StorageFile
    // otherwise GetFileFromPathSync will return nullptr
    if (!createEmptyFile(newpath)) {
      return false;
    }

    // retrieve destination file
    StorageFile^ fileToReplace = getFileFromPathSync(TitaniumWindows::Utility::ConvertString(newpath));

    if (fileToReplace == nullptr) {
      return false;
    }

    bool result = false;
    concurrency::event event;
    task<void>(this->file_->MoveAndReplaceAsync(fileToReplace)).then([&result, &event](task<void> task) {
      try {
        task.get();
        result = true;
      }
      catch (Platform::COMException^ ex) {
        TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
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
  JSValue File::open(const std::unordered_set<Titanium::Filesystem::MODE>&) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::open: Unimplemented");
    return get_context().CreateNull();
  }
  JSValue File::read() TITANIUM_NOEXCEPT {
    if (file_ == nullptr) {
      return get_context().CreateNull();
    }
    auto Blob = get_context().CreateObject(JSExport<TitaniumWindows::Blob>::Class());
    auto blob = Blob.CallAsConstructor();
    auto blob_ptr = blob.GetPrivate<TitaniumWindows::Blob>();

    blob_ptr->construct(file_);

    return blob;
  }
  bool File::rename(const std::string& desiredName) TITANIUM_NOEXCEPT {
    auto item = getStorageItem();
    concurrency::event event;
    bool result = false;
    task<void>(item->RenameAsync(TitaniumWindows::Utility::ConvertString(desiredName))).then([&result, &event](task<void> task) {
      try {
        task.get();
        result = true;
      }
      catch (Platform::COMException^ ex) {
        TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
      }
      event.set();
    }, concurrency::task_continuation_context::use_arbitrary());
    event.wait();

    return result;
  }
  std::string File::resolve() TITANIUM_NOEXCEPT {
    return path_;
  }
  unsigned File::spaceAvailable() TITANIUM_NOEXCEPT {
    const auto prop = getStorageProperties(getStorageItem());
    const auto propertiesName = ref new Platform::Collections::Vector<Platform::String^>();
    propertiesName->Append("System.FreeSpace");
    uint64 freeSpace;
    concurrency::event event;
    task<IMap<Platform::String^, Platform::Object^>^>(prop->RetrievePropertiesAsync(propertiesName)).then([&freeSpace, &event](task<IMap<Platform::String^, Platform::Object^>^> task) {
      try {
        const auto extraProperties = task.get();
        freeSpace = (uint64)extraProperties->Lookup("System.FreeSpace");
      }
      catch (Platform::COMException^ ex) {
        TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
      }
      event.set();
    }, concurrency::task_continuation_context::use_arbitrary());
    event.wait();
    return freeSpace;
  }
  bool File::write(const JSValue& data, bool append) TITANIUM_NOEXCEPT {
    // if this item represents folder, write will never work
    if (isFolder()) {
      return false;
    }

    if (file_ == nullptr) {
      // create empty file, then retrieve StorageFile object
      if (!createEmptyFile(path_)) {
        return false;
      }
      file_ = getFileFromPathSync(TitaniumWindows::Utility::ConvertString(path_));
      if (file_ == nullptr) {
        return false;
      }
    }

    Streams::IBuffer^ buffer = nullptr;

    if (data.IsString()) {
      const auto content = static_cast<std::string>(data);
      buffer = getBufferFromString(content, append, file_);
    } else if (data.IsObject()) {
      JSObject obj = data;
      auto file = obj.GetPrivate<TitaniumWindows::Filesystem::File>();
      if (file) {
        auto content = file->getContent();
        buffer = getBufferFromBytes(&content[0], content.size(), append, file_);
      } else {
        auto blob = obj.GetPrivate<TitaniumWindows::Blob>();
        if (blob && blob->get_size() > 0) {
          buffer = getBufferFromBytes(&blob->getData()[0], blob->get_size(), append, file_);
        }
      }
    }

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
      }
      catch (Platform::COMException^ ex) {
        TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
      }
      event.set();
    }, concurrency::task_continuation_context::use_arbitrary());
    event.wait();

    return result;
  }

} }  // namespace TitaniumWindows { namespace Filesystem {

