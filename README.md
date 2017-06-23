# Titanium Mobile Windows

> Titanium Mobile Windows is the Titanium platform support for the Microsoft Windows 8.1 Store and Phone platforms.

[![Build Status](https://jenkins.appcelerator.org/buildStatus/icon?job=titanium-sdk/titanium_mobile_windows/master)](https://jenkins.appcelerator.org/job/titanium-sdk/job/titanium_mobile_windows/job/master/)

Table of Contents
=================

  * [Getting Started](#getting-started)
    * [Requirements](#requirements)
      * [Windows](#windows)
      * [OS X](#os-x)
  * [Quick Start](#quick-start)
  * [Module Development](#module-development)
  * [TitaniumKit Development](#titaniumkit-development)
    * [How to Help](#how-to-help)
      * [Ti-mocha Tests](#ti-mocha-tests)
      * [Generate Proxy Stubs](#generate-proxy-stubs)
  * [Contributing](#contributing)
  * [Legal](#legal)

## Getting Started

### Requirements

:warning: Windows 8.1 app development requires *Windows 8.1*, with a *Hyper-V* capable system (for phone emulators) - see the [system requirements listing from MSDN](https://msdn.microsoft.com/en-us/library/windows/apps/ff626524%28v=vs.105%29.aspx) for more details.

### Windows

Step 1. Install [Visual Studio 2013 Update 4 (or higher)](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx) - Community, Professional, Premium or Ultimate. *Not* Express. Currently Visual Studio 2015 is not supported [[AC-290]](https://jira.appcelerator.org/browse/AC-290).

Step 2. Install the [Windows Phone 8.1 emulators](https://dev.windows.com/en-us/develop/download-phone-sdk). Note that this can be done through Visual Studio 2013 as well.

Step 3. Install [Node](https://nodejs.org/download/).

Step 4. Install latest Titanium CLI

```bash
npm -g install git://github.com/appcelerator/titanium.git
ti sdk install -b master -d
```

If you are planning to develop TitaniumKit, set up module development environment with following steps.

Step 5.

```bash
cd YOUR_WORKSPACE
git clone https://github.com/appcelerator/titanium_mobile_windows.git
cd titanium_mobile_windows
git submodule init
git submodule update
```

Step 6. Run the setup.js Node script included in this repository in cmd.exe or Powershell:

```bash
cd Tools\Scripts
npm install .
node setup.js
```

The script should download any necessary development libraries and set the appropriate environment variables for you. Restart your command prompt, then you may proceed to the [TitaniumKit Development](#titaniumkit_development) section to generate an example app to use as a development base.

### OS X

If you are planning to develop TitaniumKit, set up module development environment with following steps.

Step 1. Install Xcode 6

Step 2. Install cmake using either `sudo port install cmake` or `sudo brew install cmake`.

Step 3. Install boost using either `sudo port install boost` or `sudo brew install boost`.

Step 4. Download our pre-compiled version of Google Test [gtest-1.7.0-osx.zip (3 MB)](http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-osx.zip), unzip anywhere (the location doesn't matter) and set the environment variable GTEST_ROOT to where you unzipped it.

Just run the following commands from your bash prompt to setup your development environment for Google Test before proceeding:

```bash
$ curl -O http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-osx.zip
$ unzip gtest-1.7.0-osx.zip
```

Please note that while you may do HAL and TitaniumKit builds and development work on the mac, you will not be able to do any Windows Platform development or generate apps/examples (as documented in [TitaniumKit Development](#titaniumkit_development)).

## Quick Start

```bash
cd YOUR_WORKSPACE
ti create -p windows -t app
cd YOUR_APP_DIRECTORY
ti build --platform windows --target wp-emulator --device-id 8-1-1 --win-publisher-id XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
```

## Module Development

```bash
cd YOUR_WORKSPACE
ti create -p windows -t module
cd YOUR_MODULE_NAME/windows
ti build --platform windows --target wp-emulator --device-id 8-1-1 --win-publisher-id XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
```

## TitaniumKit Development

After installing the prerequisites you should try to build our
reference app NG. We recommend performing out-of-source builds,
so to do this run the script Scripts/generate_project.js from any
directory of your choosing as long as it is not within the
titanium_mobile_windows git repo. A good place might be
`C:\Users\<user name>\Documents`. For example:

```bash
# If you have not yet run the following from the prerequisite installation steps above, please do:
cd Tools\Scripts
npm install .
# Now go to directory where you'd like project generated
cd "${HOME}/Documents"
# Generates a project from our included NG example
node "${HOME}/Documents/GitHub/titanium_mobile_windows/Tools/Scripts/generate_project.js" new NG
# Now open the project in Visual Studio for development
start NG.WindowsPhone.Win32/NG.sln
```

:warning: By default Visual Studio 2013 will prompt you to break at handled and unhandled exceptions. During startup of our framework and examples, a number of handled exceptions may occur related to finding files or establishing a connection to the CLI logger. When they occur, uncheck the checkmark box and click the *Continue* button. Further launches of the app should no longer display a dialog to break at these handled exceptions.

### How to Help

We could always use a helping hand or two. If you're looking for how to get started helping out the project here are a few suggestions.

#### Generate Proxy Stubs
We've included a node script that will use the Titanium documentation to generate stub implementations of a proxy up in the TitaniumKit layer and the Windows implementation subclasses. To invoke it, please try:

```bash
cd Tools\Scripts\module_generator
npm install .
node generator.js
```

#### Ti-Mocha Tests

We'd love to have broader APi coverage in our ti-mocha test suite, or have the existing suite improved. It's also a great place to see tests we're skipping due to bugs or missing implementations/feature.
  - The tests live under Examples/NMocha/src/Assets. You can edit an existing suite to add more tests, or write new test suites. We use the naming format ti._proxy.name_.test.js and then add a require statement to the app.js file.
  - Even if you're not on Windows, you can submit changes to the tests in a PR and our build machine will build and run the tests, giving the results as a comment to the PR.
  - To run the mocha test suite locally under a Windows Phone emulator:
```bash
# If you have not yet run the following from the prerequisite installation steps above, please do:
cd Tools\Scripts
npm install .
# Now go to directory where you'd like project generated
cd "${HOME}/Documents"
# Generates a project from our included NMocha example
node "${HOME}/Documents/GitHub/titanium_mobile_windows/Tools/Scripts/generate_project.js" new NMocha
# Now open the project in Visual Studio for development
NMocha.WindowsPhone.Win32/NMocha.sln
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

[You can digitally sign the CLA](https://cla.appcelerator.com/) online. Please
indicate your email address in your first pull request so that we can
make sure that will locate your CLA.  Once you've submitted it, you no
longer need to send one for subsequent submissions.

## Legal

Appcelerator is a registered trademark of Appcelerator, Inc. Titanium is a registered trademark of Appcelerator, Inc.  Please see the LEGAL information about using our trademarks, privacy policy, terms of usage and other legal information at [http://www.appcelerator.com/legal](http://www.appcelerator.com/legal).
