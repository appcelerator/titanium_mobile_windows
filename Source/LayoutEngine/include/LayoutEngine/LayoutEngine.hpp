/**
 * LayoutEngine
 * Author: Russell W. McMahon
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _LAYOUTENGINE_LAYOUTENGINE_HPP_
#define _LAYOUTENGINE_LAYOUTENGINE_HPP_

#include <math.h>
#include <vector>
#include <string>

#define FLAG_INVALID 0x01     // Node layout properties have been updated since last layout pass.
#define FLAG_REQ_LAYOUT 0x02  // Layout has been request for this node and its children.

namespace Titanium
{
	namespace LayoutEngine
	{
		struct Rect
		{
			double width = 0;
			double height = 0;
			double x = 0;
			double y = 0;
		};

		enum LayoutType
		{
			Composite = 0,
			Horizontal,
			Vertical
		};

		enum ElementAlignment
		{
			Start = 0,
			Center,
			End
		};

		struct ComputedSize
		{
			double width = 0;
			double height = 0;
		};

		struct ThreeCoefficients
		{
			double x1 = NAN;
			double x2 = NAN;
			double x3 = NAN;
		};

		struct FourCoefficients
		{
			double x1 = NAN;
			double x2 = NAN;
			double x3 = NAN;
			double x4 = NAN;
		};

		struct LayoutCoefficients
		{
			struct ThreeCoefficients width;
			struct ThreeCoefficients minWidth;
			struct ThreeCoefficients sandboxWidth;
			struct ThreeCoefficients height;
			struct ThreeCoefficients minHeight;
			struct ThreeCoefficients sandboxHeight;
			struct ThreeCoefficients left;
			struct FourCoefficients top;
		};

		struct Element
		{
			std::vector<struct Element*> children;
			struct LayoutCoefficients layoutCoefficients;
			struct ComputedSize computedSize;
			double measuredSandboxWidth = 0;
			double measuredSandboxHeight = 0;
			double measuredWidth = 0;
			double measuredHeight = 0;
			double measuredLeft = 0;
			double measuredTop = 0;
			double borderRightWidth = 0;
			double borderTopWidth = 0;
			double borderBottomWidth = 0;
			double borderLeftWidth = 0;
			enum LayoutType layoutType = LayoutType::Composite;
			enum ElementAlignment defaultRowAlignment = ElementAlignment::Center;
			enum ElementAlignment defaultHorizontalAlignment = ElementAlignment::Center;
			enum ElementAlignment defaultVerticalAlignment = ElementAlignment::Center;
			double measuredRunningHeight = 0;
			double measuredRunningWidth = 0;
			double measuredRowHeight = 0;
			bool childrenLaidOut = false;
		};

		enum ValueName
		{
			Top = 0,
			Bottom,
			Left,
			Right,
			Width,
			MinWidth,
			Height,
			MinHeight,
			CenterX,
			CenterY
		};

		enum ValueType
		{ 
			Fill = 1,
			Size = 2,
			Percent = 3,
			Defer = 4,
			Auto = 5,
			Fixed = 0,
			None = -1
		};

		struct InputProperty
		{
			ValueName name;
			std::string value;
		};

		struct LayoutProp
		{
			// fill = UI.FILL, size = UI.SIZE, percent = values containing %, fixed = everything else
			enum ValueType valueType = ValueType::None;
			double value = 0;
		};

		struct LayoutProperties
		{
			struct LayoutProp top;
			struct LayoutProp bottom;
			struct LayoutProp left;
			struct LayoutProp right;
			struct LayoutProp width;
			struct LayoutProp minWidth;
			struct LayoutProp height;
			struct LayoutProp minHeight;
			struct LayoutProp centerX;
			struct LayoutProp centerY;
			enum ValueType defaultWidthType;
			enum ValueType defaultHeightType;
		};

		bool isNaN(double);
		ComputedSize layoutNode(struct Element*, double, double, bool, bool);
		void measureNode(enum LayoutType type, struct LayoutProperties* properties, struct Element* element);
		void elementInitialize(struct Element*, enum LayoutType);
		struct ComputedSize doCompositeLayout(std::vector<struct Element*>, double, double, bool, bool);
		void measureNodeForCompositeLayout(struct LayoutProperties, struct Element*);
		struct ComputedSize doHorizontalLayout(std::vector<struct Element*>, double, double, bool, bool);
		void measureNodeForHorizontalLayout(struct LayoutProperties, struct Element*);
		void layoutPropertiesInitialize(struct LayoutProperties*);
		void populateLayoutProperties(struct InputProperty, struct LayoutProperties*, double, const std::string&);
		struct ComputedSize doVerticalLayout(std::vector<struct Element*>, double, double, bool, bool);
		void measureNodeForVerticalLayout(struct LayoutProperties, struct Element*);
		double parseUnitValue(const std::string& value, enum ValueType valueType, double ppi, const std::string& defaultUnits);

		struct Node
		{
			struct Node* parent = nullptr;
			struct Node* prev = nullptr, *next = nullptr;
			struct Node* firstChild = nullptr, *lastChild = nullptr;
			struct Element element;
			struct LayoutProperties properties;
			//int flags = FLAG_INVALID;
			std::string name;
			void (*onLayout)(struct Node*) = nullptr;
			void* data = nullptr;
		};

		//void nodeInitialize(struct Node* node);
		//void nodeSetLayoutType(struct Node* node, const char* type);
		void addChildElement(Element* parent, Element* child);
		void removeChildElement(struct Element* parent, struct Element* child);
		void insertChildElementAt(Element* parent, Element* child, unsigned int index);
		void nodeAddChild(struct Node* parent, struct Node* child);
		void nodeRemoveChild(struct Node* parent, struct Node* child);
		void nodeInsertChildAt(struct Node* parent, struct Node* child, unsigned int index);
		struct Node* nodeRequestLayout(struct Node* node);
		void nodeLayout(struct Node* root);

		inline Rect RectMake(double x, double y, double width, double height)
		{
			Rect rect;
			rect.x = x;
			rect.y = y;
			rect.width = width;
			rect.height = height;
			return rect;
		}

		inline bool RectIsEmpty(Rect rect)
		{
			return rect.x == 0 && rect.y == 0 && rect.width == 0 && rect.height == 0;
		}
		inline bool RectIsEqualToRect(Rect rect1, Rect rect2)
		{
			return rect1.x == rect2.x && rect1.y == rect2.y && rect1.width == rect2.width && rect1.height == rect2.height;
		}
	} // namespace LayoutEngine
} // namespace Titanium

#endif  // _LAYOUTENGINE_LAYOUTENGINE_HPP_
