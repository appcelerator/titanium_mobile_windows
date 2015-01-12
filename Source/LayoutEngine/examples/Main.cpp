/**
 * LayoutEngine
 * Author: Russell W. McMahon
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include <iostream>

#include "LayoutEngine/LayoutEngine.hpp"

int main(int argc, char** argv)
{
	std::cout << "Running main() from a desktop executable to show basic layout engine flow.c" << std::endl;

	// This sample shows a layout of 3 elements with fixed (not % or fill constants) values. The top level
	// element After processing
	// by the Layout Engine the node (e1, e2, e3) will have in the element->measuredX the actual absolute
	// postion to be used to postion the element on the display.

	// Element 1 - Top Level element does not need to be measured it acts as the bounds for the system
	// display.
	struct Titanium::LayoutEngine::LayoutProperties layoutProperties;
	Titanium::LayoutEngine::layoutPropertiesInitialize(&layoutProperties);
	struct Titanium::LayoutEngine::Element* e1 = new Titanium::LayoutEngine::Element();
	Titanium::LayoutEngine::elementInitialize(e1, Titanium::LayoutEngine::Horizontal);

	// Element 2
	layoutProperties.width.value = 50;
	layoutProperties.width.valueType = Titanium::LayoutEngine::Fixed;
	layoutProperties.height.value = 20;
	layoutProperties.height.valueType = Titanium::LayoutEngine::Fixed;
	struct Titanium::LayoutEngine::Element* e2 = new Titanium::LayoutEngine::Element();
	Titanium::LayoutEngine::elementInitialize(e2, Titanium::LayoutEngine::Composite);
	Titanium::LayoutEngine::measureNodeForHorizontalLayout(layoutProperties, e2);

	// Element 3
	layoutProperties.width.value = 50;
	layoutProperties.width.valueType = Titanium::LayoutEngine::Fixed;
	layoutProperties.height.value = 40;
	layoutProperties.height.valueType = Titanium::LayoutEngine::Fixed;
	struct Titanium::LayoutEngine::Element* e3 = new Titanium::LayoutEngine::Element();
	Titanium::LayoutEngine::elementInitialize(e3, Titanium::LayoutEngine::Composite);
	Titanium::LayoutEngine::measureNodeForHorizontalLayout(layoutProperties, e3);

	// Create the display tree. This example has Element 1 with two children but any graph of elements
	// would work as long as the graph has a single root.
	Titanium::LayoutEngine::addChildElement(e1, e2);
	Titanium::LayoutEngine::addChildElement(e1, e3);

	// Do the calculations based on the Titanium layout rules and return the elements with the measured values
	// returned.
	Titanium::LayoutEngine::doHorizontalLayout((*e1).children, 100, 100, false, false);

	std::clog << "Element 2 Top is: " << e2->measuredTop << std::endl;
	std::clog << "Element 2 Left is: " << e2->measuredLeft << std::endl;
	std::clog << "Element 2 Width is: " << e2->measuredWidth << std::endl;
	std::clog << "Element 2 Height is: " << e2->measuredHeight << std::endl;

	std::clog << "Element 3 Top is: " << e3->measuredTop << std::endl;
	std::clog << "Element 3 Left is: " << e3->measuredLeft << std::endl;
	std::clog << "Element 3 Width is: " << e3->measuredWidth << std::endl;
	std::clog << "Element 3 Height is: " << e3->measuredHeight << std::endl;

	return 0;
}
