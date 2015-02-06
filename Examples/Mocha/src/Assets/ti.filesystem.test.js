/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe('filesystem', function () {
    // Check if applicationDirectory exists and make sure it does not throw exception
    it('applicationDirectory', function (finish) {
        should(function () {
            should(Ti.Filesystem.applicationDirectory).not.be.undefined;
            should(Ti.Filesystem.applicationDirectory).be.a.String;
            // make sure it is read-only value
            var value = Ti.Filesystem.applicationDirectory;
            Ti.Filesystem.applicationDirectory = 'try_to_overwrite_READONLY_value';
            should(Ti.Filesystem.applicationDirectory).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if applicationDataDirectory exists and make sure it does not throw exception
    it('applicationDataDirectory', function (finish) {
        should(function () {
            should(Ti.Filesystem.applicationDataDirectory).not.be.undefined;
            should(Ti.Filesystem.applicationDataDirectory).be.a.String;
            // make sure it is read-only value
            var value = Ti.Filesystem.applicationDataDirectory;
            Ti.Filesystem.applicationDataDirectory = 'try_to_overwrite_READONLY_value';
            should(Ti.Filesystem.applicationDataDirectory).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if resourcesDirectory exists and make sure it does not throw exception
    it('resourcesDirectory', function (finish) {
        should(function () {
            should(Ti.Filesystem.resourcesDirectory).not.be.undefined;
            should(Ti.Filesystem.resourcesDirectory).be.a.String;
            // make sure it is read-only value
            var value = Ti.Filesystem.resourcesDirectory;
            Ti.Filesystem.resourcesDirectory = 'try_to_overwrite_READONLY_value';
            should(Ti.Filesystem.resourcesDirectory).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if resRawDirectory exists and make sure it does not throw exception
    it('resRawDirectory', function (finish) {
        if (Ti.Platform.osname == 'android') {
            should(function () {
                should(Ti.Filesystem.resRawDirectory).not.be.undefined;
                should(Ti.Filesystem.resRawDirectory).be.a.String;
                // make sure it is read-only value
                var value = Ti.Filesystem.resRawDirectory;
                Ti.Filesystem.resRawDirectory = 'try_to_overwrite_READONLY_value';
                should(Ti.Filesystem.resRawDirectory).be.eql(value);
            }).not.throw();
        } else {
            should(Ti.Filesystem.resRawDirectory).be.undefined;
        }
        finish();
    });
    // On Windows Runtime, applicationSupportDirectory may return null if app doesn't have permission
    // although it should not throw exception
    it('applicationSupportDirectory', function (finish) {
        if (Ti.Platform.osname != 'android') {
            should(function () {
                should(Ti.Filesystem.applicationSupportDirectory).not.be.undefined;
                if (Ti.Filesystem.applicationSupportDirectory != null) {
                    should(Ti.Filesystem.applicationSupportDirectory).be.a.String;
                }
                // make sure it is read-only value
                var value = Ti.Filesystem.applicationSupportDirectory;
                Ti.Filesystem.applicationSupportDirectory = 'try_to_overwrite_READONLY_value';
                should(Ti.Filesystem.applicationSupportDirectory).be.eql(value);
            }).not.throw();
            finish();
        }
    });
    // On Windows Runtime, externalStorageDirectory may return null if app doesn't have permission
    // although it should not throw exception
    it('externalStorageDirectory', function (finish) {
        if (Ti.Platform.osname != 'iphone' && Ti.Platform.osname != 'ipad') {
            should(function () {
                should(Ti.Filesystem.externalStorageDirectory).not.be.undefined;
                if (Ti.Filesystem.externalStorageDirectory != null) {
                    should(Ti.Filesystem.externalStorageDirectory).be.a.String;
                }
                // make sure it is read-only value
                var value = Ti.Filesystem.externalStorageDirectory;
                Ti.Filesystem.externalStorageDirectory = 'try_to_overwrite_READONLY_value';
                should(Ti.Filesystem.externalStorageDirectory).be.eql(value);
            }).not.throw();
            finish();
        }
    });
    // Check if applicationCacheDirectory exists and make sure it does not throw exception
    it('applicationCacheDirectory', function (finish) {
        should(function () {
            // Windows Store app doesn't support cache directory
            if (Ti.Platform.osname == 'windowsstore') {
                should(Ti.Filesystem.applicationCacheDirectory).be.undefined;
            } else {
                should(Ti.Filesystem.applicationCacheDirectory).not.be.undefined;
                should(Ti.Filesystem.applicationCacheDirectory).be.a.String;
                // make sure it is read-only value
                var value = Ti.Filesystem.applicationCacheDirectory;
                Ti.Filesystem.applicationCacheDirectory = 'try_to_overwrite_READONLY_value';
                should(Ti.Filesystem.applicationCacheDirectory).be.eql(value);
            }
        }).not.throw();
        finish();
    });
    // Check if tempDirectory exists and make sure it does not throw exception
    it('tempDirectory', function (finish) {
        should(function () {
            should(Ti.Filesystem.tempDirectory).not.be.undefined;
            should(Ti.Filesystem.tempDirectory).be.a.String;
            // make sure it is read-only value
            var value = Ti.Filesystem.tempDirectory;
            Ti.Filesystem.tempDirectory = 'try_to_overwrite_READONLY_value';
            should(Ti.Filesystem.tempDirectory).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if separator exists and make sure it does not throw exception
    it('separator', function (finish) {
        should(function () {
            should(Ti.Filesystem.separator).not.be.undefined;
            should(Ti.Filesystem.separator).be.a.String;
            if (Ti.Platform.osname == 'windowsstore' || Ti.Platform.osname == 'windowsphone') {
                should(Ti.Filesystem.separator).be.eql('\\');
            } else {
                should(Ti.Filesystem.separator).be.eql('/');
            }
            // make sure it is read-only value
            var value = Ti.Filesystem.separator;
            Ti.Filesystem.separator = 'try_to_overwrite_READONLY_value';
            should(Ti.Filesystem.separator).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if lineEnding exists and make sure it does not throw exception
    it('lineEnding', function (finish) {
        should(function () {
            should(Ti.Filesystem.lineEnding).not.be.undefined;
            should(Ti.Filesystem.lineEnding).be.a.String;
            if (Ti.Platform.osname == 'windowsstore' || Ti.Platform.osname == 'windowsphone') {
                should(Ti.Filesystem.lineEnding).be.eql('\r\n');
            } else {
                should(Ti.Filesystem.lineEnding).be.eql('\n');
            }
            // make sure it is read-only value
            var value = Ti.Filesystem.lineEnding;
            Ti.Filesystem.lineEnding = 'try_to_overwrite_READONLY_value';
            should(Ti.Filesystem.lineEnding).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if MODE_APPEND exists and make sure it does not throw exception
    it('MODE_APPEND', function (finish) {
        should(function () {
            should(Ti.Filesystem.MODE_APPEND).not.be.undefined;
            should(Ti.Filesystem.MODE_APPEND).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Filesystem.MODE_APPEND;
            Ti.Filesystem.MODE_APPEND = 'try_to_overwrite_READONLY_value';
            should(Ti.Filesystem.MODE_APPEND).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if MODE_READ exists and make sure it does not throw exception
    it('MODE_READ', function (finish) {
        should(function () {
            should(Ti.Filesystem.MODE_READ).not.be.undefined;
            should(Ti.Filesystem.MODE_READ).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Filesystem.MODE_READ;
            Ti.Filesystem.MODE_READ = 'try_to_overwrite_READONLY_value';
            should(Ti.Filesystem.MODE_READ).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if MODE_WRITE exists and make sure it does not throw exception
    it('MODE_WRITE', function (finish) {
        should(function () {
            should(Ti.Filesystem.MODE_WRITE).not.be.undefined;
            should(Ti.Filesystem.MODE_WRITE).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Filesystem.MODE_WRITE;
            Ti.Filesystem.MODE_WRITE = 'try_to_overwrite_READONLY_value';
            should(Ti.Filesystem.MODE_WRITE).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if getFile exists and make sure it does not throw exception
    it('getFile', function (finish) {
        should(Ti.Filesystem.getFile).not.be.undefined;
        should(Ti.Filesystem.getFile).be.a.Function;
        var file = Ti.Filesystem.getFile('app.js');
        should(file).be.an.Object;
        finish();
    });
    // Check if openStream exists
    it.skip('openStream', function (finish) {
        should(Ti.Filesystem.openStream).not.be.undefined;
        should(Ti.Filesystem.openStream).be.a.Function;
        var stream = Ti.Filesystem.openStream(Ti.Filesystem.MODE_READ, 'app.js');
        should(stream).be.an.Object;
        stream.close();
        finish();
    });
    // Check if createTempDirectory exists and make sure it does not throw exception
    it('createTempDirectory', function (finish) {
        should(Ti.Filesystem.createTempDirectory).not.be.undefined;
        should(Ti.Filesystem.createTempDirectory).be.a.Function;
        var dir = Ti.Filesystem.createTempDirectory();
        should.exist(dir);
        should.exist(dir.name);
        should(dir.exists()).be.true;
        should(dir.deleteDirectory()).be.true;
        should(dir.exists()).be.false;
        finish();
    });
    // Check if createTempFile exists and make sure it does not throw exception
    it('createTempFile', function (finish) {
        should(Ti.Filesystem.createTempFile).not.be.undefined;
        should(Ti.Filesystem.createTempFile).be.a.Function;
        var file = Ti.Filesystem.createTempFile();
        should(file).be.an.Object;
        should(file.name).be.a.String;
        should(file.exists()).be.true;
        should(file.deleteFile()).be.true;
        should(file.exists()).be.false;
        finish();
    });
    // TIMOB-10107
    it.skip('multiLingualFilename', function(finish) {
        var msg = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, '網上廣東話輸入法.txt');
        should(msg.write('Appcelerator', true)).be.true;
        should(msg.exists()).be.true;
        should(msg.deleteFile()).be.true;
        should(msg.exists()).be.false;
        finish();
    });
    //TIMOB-14364
    it("setRemoteBackup", function (finish) {
        if ("iphone" === Ti.Platform.osname || "ipad" === Ti.Platform.osname) {
            should(function () {
                Titanium.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory).setRemoteBackup(false);
            }).not.throw();
            finish();
        } else {
            finish();
        }
    });
    // Check if name exists and returns string
    it('File_name', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.name).not.be.undefined;
        should(file.name).be.a.String;
        should(file.name).be.eql('app.js');
        // make sure it is read-only value
        var value = file.name;
        file.name = 'try_to_overwrite_READONLY_value';
        should(file.name).be.eql(value);
        finish();
    });
    // Check if nativePath exists and returns string
    it('File_nativePath', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.nativePath).not.be.undefined;
        should(file.nativePath).be.a.String;
        // make sure it is read-only value
        var value = file.nativePath;
        file.nativePath = 'try_to_overwrite_READONLY_value';
        should(file.nativePath).be.eql(value);
        finish();
    });
    // Check if resolve exists and returns string
    it('File_resolve', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.resolve).not.be.undefined;
        should(file.resolve).be.a.Function;
        var value = file.resolve();
        should(value).not.be.undefined;
        should(value).be.a.String;
        // On Windows, it returns native path
        if (Ti.Platform.osname == 'windowsstore' || Ti.Platform.osname == 'windowsphone') {
            should(value).be.eql(file.nativePath);
        }
        finish();
    });
    // Check if executable exists and returns boolean
    it('File_executable', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.executable).not.be.undefined;
        should(file.executable).be.a.Boolean;
        // make sure it is read-only value
        var value = file.executable;
        file.executable = 'try_to_overwrite_READONLY_value';
        should(file.executable).be.eql(value);
        finish();
    });
    // Check if hidden exists and returns boolean
    it('File_hidden', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.hidden).not.be.undefined;
        should(file.hidden).be.a.Boolean;
        // make sure it is read-only value
        var value = file.hidden;
        file.hidden = 'try_to_overwrite_READONLY_value';
        should(file.hidden).be.eql(value);
        finish();
    });
    // Check if readonly exists and returns boolean
    it('File_readonly', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.readonly).not.be.undefined;
        should(file.readonly).be.a.Boolean;
        // make sure it is read-only value
        var value = file.readonly;
        file.readonly = 'try_to_overwrite_READONLY_value';
        should(file.readonly).be.eql(value);
        finish();
    });
    // Check if writable exists and returns boolean
    it('File_writable', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.writable).not.be.undefined;
        should(file.writable).be.a.Boolean;
        // make sure it is read-only value
        var value = file.writable;
        file.writable = 'try_to_overwrite_READONLY_value';
        should(file.writable).be.eql(value);
        finish();
    });
    // Check if symbolicLink exists and returns boolean
    it('File_symbolicLink', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.symbolicLink).not.be.undefined;
        should(file.symbolicLink).be.a.Boolean;
        // make sure it is read-only value
        var value = file.symbolicLink;
        file.symbolicLink = 'try_to_overwrite_READONLY_value';
        should(file.symbolicLink).be.eql(value);
        finish();
    });
    // Check if parent exists and returns String/Ti.File
    it('File_parent', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.parent).not.be.undefined;
        // On Android, it returns Ti.File. Otherwise returns String
        if (Ti.Platform.osname == 'android') {
            should(file.parent).be.an.Object;
        } else {
            should(file.parent).be.a.String;
        }
        // make sure it is read-only value
        var value = file.parent;
        file.parent = 'try_to_overwrite_READONLY_value';
        should(file.parent).be.eql(value);
        finish();
    });
    // Check if size exists and returns number
    it('File_size', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.size).not.be.undefined;
        should(file.size).be.a.Number;
        should(file.size > 0).be.true;
        // make sure it is read-only value
        var value = file.size;
        file.size = 'try_to_overwrite_READONLY_value';
        should(file.size).be.eql(value);
        finish();
    });
    // exists should return true if file exists
    it('exists', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.exists()).be.true;
        finish();
    });
    // exists should return false if file is not there
    it('not_exists', function (finish) {
        var file = Ti.Filesystem.getFile('appp.js');
        should(file.exists()).be.false;
        finish();
    });
    // isFile should return true if file exists
    it('isFile', function(finish) {
        var file = Ti.Filesystem.getFile('app.js');
        should(file.exists()).be.true;
        should(file.isFile()).be.true;
        finish();
    });
    // isFile should return false if file is not there
    it('isFile_not_exist', function (finish) {
        var file = Ti.Filesystem.getFile('appp.js');
        should(file.exists()).be.false;
        should(file.isFile()).be.false;
        finish();
    });
    // isFile should return false if file points to directory
    it('isFile_toDirectory', function (finish) {
        var dir = Ti.Filesystem.getFile(Ti.Filesystem.applicationDirectory);
        should(dir.isFile()).be.false;
        finish();
    });
    // isDirectory should return true if file points to directory
    it('isDirectory', function (finish) {
        var dir = Ti.Filesystem.getFile(Ti.Filesystem.applicationDirectory);
        should(dir.isDirectory()).be.true;
        finish();
    });
    // isDirectory should return false if file points to file
    it('isDirectory_toFile', function (finish) {
        var dir = Ti.Filesystem.getFile('app.js');
        should(dir.isDirectory()).be.false;
        finish();
    });
    // isDirectory should return false if file is not there
    it('isDirectory_not_exist', function (finish) {
        var dir = Ti.Filesystem.getFile('appp.js');
        should(dir.isDirectory()).be.false;
        finish();
    });

    // createTimestamp should return number
    it('File_createTimestamp', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        var create_date = file.createTimestamp();
        should(create_date).be.a.Number;
        should(create_date > 0).be.true;
        finish();
    });

    // modificationTimestamp should return number
    it('File_modificationTimestamp', function (finish) {
        var file = Ti.Filesystem.getFile('app.js');
        var mod_date = file.modificationTimestamp();
        should(mod_date).be.a.Number;
        should(mod_date > 0).be.true;
        finish();
    });

    // createDirectory and deleteDirectory
    it('create_and_deleteDirectory', function (finish) {
        var newDir = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'mydir');
        should(newDir.exists()).be.false;
        newDir.createDirectory();
        should(newDir.exists()).be.true;
        newDir.deleteDirectory();
        should(newDir.exists()).be.false;
        finish();
    });

    // createFile and deleteFile
    it('createFile_and_deleteFile', function (finish) {
        var newFile = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'myfile');
        should(newFile.exists()).be.false;
        newFile.createFile();
        should(newFile.exists()).be.true;
        newFile.deleteFile();
        should(newFile.exists()).be.false;
        finish();
    });

    // File.read
    it('File_read', function (finish) {
        var newFile = Ti.Filesystem.getFile(Ti.Filesystem.applicationDirectory, 'app.js');
        should(newFile.exists()).be.true;
        var blob = newFile.read();
        should(blob).be.an.Object;
        should(blob.size > 0).be.true;
        should(blob.text.length > 0).be.true;
        finish();
    });

    // File.write from String
    it('File_write_String', function (finish) {
        var msg = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'write_test.txt');
        should(msg.write('Appcelerator', false)).be.true;
        should(msg.exists()).be.true;

        var blob = msg.read();
        should(blob).be.an.Object;
        should(blob.size > 0).be.true;
        should(blob.text.length > 0).be.true;
        should(blob.text).be.eql('Appcelerator');

        should(msg.deleteFile()).be.true;
        should(msg.exists()).be.false;
        finish();
    });

    // File.write from String (append)
    it('File_write_String_append', function (finish) {
        var msg = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'write_test.txt');
        should(msg.write('Appcelerator', false)).be.true;
        should(msg.exists()).be.true;

        should(msg.write('Appcelerator', true)).be.true;

        var blob = msg.read();
        should(blob).be.an.Object;
        should(blob.size > 0).be.true;
        should(blob.text.length > 0).be.true;
        should(blob.text).be.eql('AppceleratorAppcelerator');

        should(msg.deleteFile()).be.true;
        should(msg.exists()).be.false;
        finish();
    });

    // File.write from File
    it('File_write_File', function (finish) {
        var from = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'write_test.txt');
        should(from.write('Appcelerator', false)).be.true;
        should(from.exists()).be.true;

        var to = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'write_test_to.txt');
        should(to.write(from, false)).be.true;
        should(to.exists()).be.true;

        var blob = to.read();
        should(blob).be.an.Object;
        should(blob.size > 0).be.true;
        should(blob.text.length > 0).be.true;
        should(blob.text).be.eql('Appcelerator');

        should(from.deleteFile()).be.true;
        should(from.exists()).be.false;
        should(to.deleteFile()).be.true;
        should(to.exists()).be.false;

        finish();
    });

    // File.write from File (append)
    it('File_write_File_append', function (finish) {
        var from = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'write_test.txt');
        should(from.write('Appcelerator', false)).be.true;
        should(from.exists()).be.true;

        var to = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'write_test_to.txt');
        should(to.write('Appcelerator', false)).be.true;
        should(to.exists()).be.true;

        should(to.write(from, true)).be.true;

        var blob = to.read();
        should(blob).be.an.Object;
        should(blob.size > 0).be.true;
        should(blob.text.length > 0).be.true;
        should(blob.text).be.eql('AppceleratorAppcelerator');

        should(from.deleteFile()).be.true;
        should(from.exists()).be.false;
        should(to.deleteFile()).be.true;
        should(to.exists()).be.false;

        finish();
    });

    // File.write from Blob
    it('File_write_Blob', function (finish) {
        var from = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'write_test.txt');
        should(from.write('Appcelerator', false)).be.true;
        should(from.exists()).be.true;

        var to = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'write_test_to.txt');
        should(to.write(from.read(), false)).be.true;
        should(to.exists()).be.true;

        var blob = to.read();
        should(blob).be.an.Object;
        should(blob.size > 0).be.true;
        should(blob.text.length > 0).be.true;
        should(blob.text).be.eql('Appcelerator');

        should(from.deleteFile()).be.true;
        should(from.exists()).be.false;
        should(to.deleteFile()).be.true;
        should(to.exists()).be.false;

        finish();
    });

    // File.write from Blob (append)
    it('File_write_Blob_append', function (finish) {
        var from = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'write_test.txt');
        should(from.write('Appcelerator', false)).be.true;
        should(from.exists()).be.true;

        var to = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, 'write_test_to.txt');
        should(to.write('Appcelerator', false)).be.true;
        should(to.exists()).be.true;

        should(to.write(from.read(), true)).be.true;

        var blob = to.read();
        should(blob).be.an.Object;
        should(blob.size > 0).be.true;
        should(blob.text.length > 0).be.true;
        should(blob.text).be.eql('AppceleratorAppcelerator');

        should(from.deleteFile()).be.true;
        should(from.exists()).be.false;
        should(to.deleteFile()).be.true;
        should(to.exists()).be.false;

        finish();
    });

    // File.open
    it.skip('File_open', function (finish) {
        var newFile = Ti.Filesystem.getFile(Ti.Filesystem.applicationDirectory, 'app.js');
        should(newFile.exists()).be.true;
        var stream = newFile.open();
        should(stream).be.an.Object;
        stream.close();
        finish();
    });

    // File.spaceAvailable
    it('File_spaceAvailable', function (finish) {
        var file = Ti.Filesystem.getFile(Ti.Filesystem.applicationDirectory, 'app.js');
        should(file.exists()).be.true;
        var space = file.spaceAvailable();
        should(space).be.a.Number;
        should(space > 0).be.true;
        finish();
    });

    // File.copy
    it('File_copy', function (finish) {
        var file = Ti.Filesystem.getFile(Ti.Filesystem.applicationDirectory, 'app.js');
        should(file.exists()).be.true;
        var newpath = Ti.Filesystem.applicationDataDirectory + Ti.Filesystem.separator + 'app.js';
        should(file.copy(newpath)).be.true;
        var dest = Ti.Filesystem.getFile(newpath);
        should(dest.exists()).be.true;
        should(dest.deleteFile()).be.true;
        should(dest.exists()).be.false;
        finish();
    });

    // File copy and move
    it('File_copy_move', function (finish) {
        var file = Ti.Filesystem.getFile(Ti.Filesystem.applicationDirectory, 'app.js');
        should(file.exists()).be.true;

        var dest1 = Ti.Filesystem.applicationDataDirectory + Ti.Filesystem.separator + 'app.js';
        var dest2 = Ti.Filesystem.applicationDataDirectory + Ti.Filesystem.separator + 'appp.js';

        should(file.copy(dest1)).be.a.Boolean;

        var copy = Ti.Filesystem.getFile(dest1);
        should(copy.exists()).be.true;
        should(copy.move(dest2)).be.a.true;
        should(copy.exists()).be.false;
        var move = Ti.Filesystem.getFile(dest2);
        should(move.exists()).be.true;
        should(move.deleteFile()).be.true;
        should(move.exists()).be.false;

        finish();
    });

    // Directory listing
    it('File_directoryListing', function (finish) {
        var dir = Ti.Filesystem.getFile(Ti.Filesystem.applicationDirectory);
        should(dir.exists()).be.true;
        should(dir.getDirectoryListing).be.a.Function;
        var files = dir.getDirectoryListing();
        should(files).be.an.Array;
        finish();
    });

});
