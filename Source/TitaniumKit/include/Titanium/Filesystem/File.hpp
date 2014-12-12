/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_FILESYSTEM_FILE_HPP_
#define _TITANIUM_FILESYSTEM_FILE_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Filesystem/Constants.hpp"
#include <vector>

namespace Titanium { namespace Filesystem {
  
  using namespace JavaScriptCoreCPP;
  
  /*!
   @class
   @discussion This is the Titanium.Filesystem.File module.
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Filesystem.File
   */
  class TITANIUMKIT_EXPORT File : public Module, public JSExport<File> {
    
  public:
    
    virtual bool get_executable() const TITANIUM_NOEXCEPT;
    virtual bool get_hidden() const TITANIUM_NOEXCEPT;
    virtual std::string get_name() const TITANIUM_NOEXCEPT;
    virtual std::string get_nativePath() const TITANIUM_NOEXCEPT;
    virtual JSValue get_parent() const TITANIUM_NOEXCEPT;
    virtual bool get_readonly() const TITANIUM_NOEXCEPT;
    virtual bool get_remoteBackup() const TITANIUM_NOEXCEPT;
    virtual unsigned get_size() const TITANIUM_NOEXCEPT;
    virtual bool get_symbolicLink() const TITANIUM_NOEXCEPT;
    virtual bool get_writable() const TITANIUM_NOEXCEPT;
    
    virtual bool append(const JSValue& data) TITANIUM_NOEXCEPT;
    virtual bool copy(const std::string& dest) TITANIUM_NOEXCEPT;
    virtual bool createDirectory() TITANIUM_NOEXCEPT;
    virtual bool createFile() TITANIUM_NOEXCEPT;
    virtual unsigned createTimestamp() TITANIUM_NOEXCEPT;
    virtual bool deleteDirectory(bool recursive) TITANIUM_NOEXCEPT;
    virtual bool deleteFile() TITANIUM_NOEXCEPT;
    virtual bool exists() TITANIUM_NOEXCEPT;
    virtual std::string extension() TITANIUM_NOEXCEPT;
    virtual std::vector<JSValue> getDirectoryListing() TITANIUM_NOEXCEPT;
    virtual bool isDirectory() TITANIUM_NOEXCEPT;
    virtual bool isFile() TITANIUM_NOEXCEPT;
    virtual unsigned modificationTimestamp() TITANIUM_NOEXCEPT;
    virtual bool move(const std::string& newpath) TITANIUM_NOEXCEPT;
    virtual JSValue open(const std::unordered_set<MODE>&) TITANIUM_NOEXCEPT;
    virtual JSValue read() TITANIUM_NOEXCEPT;
    virtual bool rename(const std::string& newname) TITANIUM_NOEXCEPT;
    virtual std::string resolve() TITANIUM_NOEXCEPT;
    virtual unsigned spaceAvailable() TITANIUM_NOEXCEPT;
    virtual bool write(const JSValue& data, bool append) TITANIUM_NOEXCEPT;

    File(const JSContext& js_context)                           TITANIUM_NOEXCEPT;
    File(const File&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~File()              = default;
    File(const File&)            = default;
    File& operator=(const File&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    File(File&&)                 = default;
    File& operator=(File&&)      = default;
#endif
    
    static void JSExportInitialize();
    
    virtual JSValue get_executable_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_hidden_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_name_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_nativePath_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_parent_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_readonly_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_remoteBackup_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_size_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_symbolicLink_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_writable_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    
    virtual JSValue getExecutable_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getHidden_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getName_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getNativePath_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getParent_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getReadonly_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getRemoteBackup_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getSize_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getSymbolicLink_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getWritable_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

    virtual JSValue append_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue copy_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue createDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue createFile_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue createTimestamp_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue deleteDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue deleteFile_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue exists_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue extension_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue getDirectoryListing_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue isDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue isFile_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue modificationTimestamp_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue move_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue open_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue read_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue rename_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue resolve_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue spaceAvailable_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
    virtual JSValue write_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

  };
}} // namespace Titanium { namespace Filesystem {

#endif // _TITANIUM_FILESYSTEM_FILE_HPP_
