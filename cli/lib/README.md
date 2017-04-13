# Native Type Wrappers

Table of Contents
=================

  * [Description](#description)
  * [How to Generate types](#how-to-generate-types)
  * [Using native types in JS code](#using-native-types-in-js-code)
  * [Details](#details)
  * [Alternative Approaches](#alternative-approaches)

## Description
This is a set of node scripts and EJS templates that will generate native type wrappers to expose the Windows API to the JavaScript engine on top of HAL. Right now, it is a partially manual process. At the top of the stub.js file, there is a "seeds" variable holding the set of types you reference directly in your app (NG example in the steps above). That script will then look at the metadata to expand out the full set of types required by looking at dependencies, and then will generate wrapper classes for each type under the Source\Titanium module. It will also generate a few special blocks of code:
- The set of #includes to use in Source\Titanium\src\WindowsNativeModuleLoader.cpp
- Blocks of code for loading the native type wrappers when they are required, inside Source\Titanium\src\WindowsNativeModuleLoader.cpp
- The set of #includes and cast implementation in Source\Titanium\src\Platform.Object.cpp

## How to Generate types
```bat
cd titanium_mobile_windows\Tools\Scripts\metadata_stubber
npm install .
node stub.js
cd C:\Users\username\Documents
node C:\path\to\titanium_mobile_windows\Tools\Scripts\generate_project.rb new NG
NG.WindowsPhone.Win32\NG.sln
```
The final command will open the generated solution in Visual Studio for you, from there you can build and launch the app in an emulator or on a device.

## Using native types in JS code
Native types are used in your app by using require:
```javascript
var Window = require('Windows.UI.Xaml.Window'),
	TextBlock = require('Windows.UI.Xaml.Controls.TextBlock'),
	label = new TextBlock();

// set up label
label.Text = 'Loading, please wait.';
label.TextAlignment = Windows.UI.Xaml.TextAlignment.Right;
label.VerticalAlignment = Windows.UI.Xaml.VerticalAlignment.Top;
label.HorizontalAlignment = Windows.UI.Xaml.HorizontalAlignment.Right;
label.FontSize = 60;

Windows.Current.Content = label;
```

## Details
We hook native type loading off of require calls. If we are unable to load a file using all the typical search paths and the module id looks like the name of a native Windows type, we will attempt to load the native type wrapper set up by the scripts above. (This does allow for using JS override implementations that would get loaded in preference to the native wrapper).
Loading of native types through require is done by registering a NativeModuleLoader subclass on the global. Right now, the classes and the hook are all generated in the TitaniumWindows module. Ideally this would be hooked into the build process of the user's app and we could crawl the app for native requires pre-build to generate our listing of "seed" types and generate all the wrappers and hook in the user's app.

Please note that this approach is very similar to our Windows Hyperloop approach - we statically generate native code at build time to handle the mapping of native APIs. This approach involves no special syntax, but suffers from issues of bloating the app with the native wrappers.
