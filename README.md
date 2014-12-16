[![Build Status](https://magnum.travis-ci.com/appcelerator/titanium_mobile_windows.svg?token=SxTZxbWRYYpcfE9jALXb&branch=master)](https://magnum.travis-ci.com/appcelerator/titanium_mobile_windows)

# Titanium Mobile Windows

Titanium Mobile Windows is the Titanium platform support for the Microsoft Windows 8.1 Store and Phone platforms.

## Prerequisites

```bash
git clone https://github.com/appcelerator/titanium_mobile_windows.git
pushd titanium_mobile_windows
git submodule init
git submodule update
```

### Windows

Step 1. Install Visual Studio 2013

Step 2. Install this version of [CMake](https://cmakems.codeplex.com/releases/view/126914) in order to generate VS 2013 project files.

Step 3. Install [64-bit Cygwin](http://cygwin.com/setup-x86_64.exe).

* Choose the mirror http://mirrors.kernel.org which we have measured is at least 100x faster than the default selected mirror.
* Select both ```curl``` and ```unzip``` in addition to the defaults.

Step 4. Install JavascriptCore

Download our pre-compiled version of JavascriptCore [JavaScriptCore-Windows-1411436814.zip (276 MB)](http://timobile.appcelerator.com.s3.amazonaws.com/jscore/JavaScriptCore-Windows-1411436814.zip), unzip anywhere (the location doesn't matter) and set the environment variable JavaScriptCore_HOME to where you unzipped it.

Just run the following commands from your Cygwin bash prompt to setup your development environment for JavaScriptCore_HOME before
proceeding:

```bash
$ curl -O http://timobile.appcelerator.com.s3.amazonaws.com/jscore/JavaScriptCore-Windows-1411436814.zip
$ unzip JavaScriptCore-Windows-1411436814.zip
```

step 5. Install Google Test

Download our pre-compiled version of Google Test [gtest-1.7.0-windows.zip (3 MB)](http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-windows.zip), unzip anywhere (the location doesn't matter) and set the environment variable GTEST_ROOT to where you unzipped it.

Just run the following commands from your Cygwin bash prompt to setup your development environment for Google Test before proceeding:

```bash
$ curl -O http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-windows.zip
$ unzip gtest-1.7.0-windows.zip
```

Step 6. Install Boost

Microsoft officially supports and encourages the use of the Boost C++ open source library for Windows Store and Windows Phone apps, and they have contributed a great deal of open source code to the Boost project. Please read the Microsoft article [Using Boost Libraries in Windows Store and Phone Applications](http://blogs.msdn.com/b/vcblog/archive/2014/07/18/using-boost-libraries-in-windows-store-and-phone-applications.aspx) and follow their instructions.

Microsoft instructs us to create the folders named WPSDK\WP81 under the VC Visual Studio installation directory, `C:\Program Files
(x86)\Microsoft Visual Studio 12.0\VC\`, and copy their [phone setup script files](http://blogs.msdn.com/cfs-file.ashx/__key/communityserver-components-postattachments/00-10-54-33-32/BoostSample-.zip) to it. This has been verified to work well with our CMake build infrastructure.

After following Microsoft's instructions, define the environment variable `BOOST_ROOT` to point to where you cloned the boost git repository and add it to your `PATH`. If you are using PowerShell something like the following works:
```
setx.exe BOOST_ROOT $env:HOME\Documents\GitHub\boost
$env:Path += ";$env:BOOST_ROOT";
cd $env:BOOST_ROOT\libs\thread\build
b2 toolset=msvc-12.0 link=static windows-api=store
b2 toolset=msvc-12.0 link=static windows-api=phone
```

Step 7. Install SQLite

Download our pre-compiled version of SQLite [SQLite-Windows-1415143965334.zip (8 MB)](http://timobile.appcelerator.com.s3.amazonaws.com/SQLite-Windows-1415143965334.zip), unzip anywhere (the location doesn't matter) and set the environment variable SQLite_HOME to where you unzipped it.

Just run the following commands from your Cygwin bash prompt to setup your development environment for SQLite_HOME before proceeding:

```bash
$ curl -O http://timobile.appcelerator.com.s3.amazonaws.com/SQLite-Windows-1415143965334.zip
$ unzip SQLite-Windows-1415143965334.zip
```

### OS X

Step 1. Install Xcode 6

Step 2. Install cmake using either `sudo port install cmake` or `sudo brew install cmake`.

Step 3. Install boost using either `sudo port install boost` or `sudo brew install boost`.

Step 4. Download our pre-compiled version of Google Test [gtest-1.7.0-osx.zip (3 MB)](http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-osx.zip), unzip anywhere (the location doesn't matter) and set the environment variable GTEST_ROOT to where you unzipped it.

Just run the following commands from your bash prompt to setup your development environment for Google Test before proceeding:

```bash
$ curl -O http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-osx.zip
$ unzip gtest-1.7.0-osx.zip
```

## Getting Started

After installing the prerequisites you should try to build our
reference app NG. We recommend performing out-of-source builds,
so to do this run the script Scripts/generate_vs_project.sh from any
directory of your choosing as long as it is not within the
titanium_mobile_windows git repo. A good place might be
`C:\Users\<user name>\Documents\Visual Studio 2013`. For example:

```bash
pushd "${HOME}/Documents/Visual Studio 2013/"
"${HOME}/Documents/GitHub/titanium_mobile_windows/Tools/Scripts/generate_vs_project.sh" NG
cygstart NG.WindowsPhone.Win32/NG.sln
```

## Contributing

Titanium is an open source project.  Titanium wouldn't be where it is
now without contributions by the community. Please consider forking
this repo to improve, enhance or fix issues. If you feel like the
community will benefit from your fork, please open a pull request.

To protect the interests of the Titanium contributors, Appcelerator,
customers and end users we require contributors to sign a Contributors
License Agreement (CLA) before we pull the changes into the main
repository. Our CLA is simple and straightforward - it requires that
the contributions you make to any Appcelerator open source project are
properly licensed and that you have the legal authority to make those
changes. This helps us significantly reduce future legal risk for
everyone involved. It is easy, helps everyone, takes only a few
minutes, and only needs to be completed once.

[You can digitally sign the CLA](http://bit.ly/app_cla) online. Please
indicate your email address in your first pull request so that we can
make sure that will locate your CLA.  Once you've submitted it, you no
longer need to send one for subsequent submissions.


## Legal

Titanium Mobile Windows is developed by Appcelerator and the community
and is Copyright (c) 2012-2014 by Appcelerator, Inc. All Rights
Reserved.

Titanium Mobile Windows is made available under the Apache Public
License, version 2.  See the
[LICENSE](https://github.com/appcelerator/titanium_mobile_windows/blob/master/LICENSE)
file for more information.

