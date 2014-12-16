# LayoutEngine [![Build Status](https://magnum.travis-ci.com/appcelerator/titanium_mobile_windows.svg?token=SxTZxbWRYYpcfE9jALXb&branch=master)](https://magnum.travis-ci.com/appcelerator/titanium_mobile_windows)

LayoutEngine:  A C/C++ Engine that takes as input properties top, left, width and height and outputs the calculated values based on the layout rules (http://docs.appcelerator.com/titanium/latest/#!/guide/Layouts,_Positioning,_and_the_View_Hierarchy). 

## Quick Start

Run the gtest tests.


Here is [Main.cpp](examples/Main.cpp), a simple main program that sets up and fills in the structures used by the LayoutEngine then has the engine compute the display coordinates of a couple nodes. The the expected values are printed to standard out. 

Using and extending the code in Main.cpp is a good way to see how to interact with the engine. Once the input and output to and from the engine is well understood then an interface can be created that connects the native UI controls to the abstract calculations provided by the engine.


## Description

The LayoutEngine is a calculator and does not directly communicate with a platform's native UI controls. An interface is used between the LayoutEngine and native controls. This abstraction allows the same engine to be used on multiple C based platforms including iOS, BlackBerry, Windows and using the NDK Android.


## Project Goals

1. Create a cross platform Titanium layout engine.
2. The engine will be built as a standalone static library.
2. Ensure the engine is high-performance and stable.
3. The library's public API is 100% thoroughly documented.
4. The library comes with a suite of unit tests that covers a minimum of 80% of the API.


## Lessons Learned and Future Direction

Here are some valuable lessons we have learned during the development of the LayoutEngine library and possible areas of future exploration and R&D:

1. The engine by itself is nothing more then a parser and calculator. Much of the work is in hooking up the the engine to a native platform UI system. Expertise in how native controls are efficiently used is a prerequisite to making  good use the engine, or any layout engine for that matter.
2. More functionality could and should be moved into the engine to make creating the native UI interface easier.
3. Layout engines are complex beast and best modified by senior staff. Side effects are easily hidden.

## Contributors

The original design of the engine was done by Blain Hamon to address layout performance issues on iOS and MobileWeb. The Javascript (MobileWeb) implementation was ported by Russ McMahon using mostly C with some standard C++ container classes.
