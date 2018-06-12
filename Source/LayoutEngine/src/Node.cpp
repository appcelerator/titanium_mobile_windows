/**
 * LayoutEngine
 * Author: Russell W. McMahon
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "LayoutEngine/LayoutEngine.hpp"

#include <string.h>

namespace Titanium
{
	namespace LayoutEngine
	{
		void nodeAddChild(struct Node* parent, struct Node* child)
		{
			if (child->parent) {
				nodeRemoveChild(child->parent, child);
			}

			child->parent = parent;
			if (parent->lastChild) {
				child->prev = parent->lastChild;
				parent->lastChild->next = child;
			} else {
				parent->firstChild = child;
			}
			parent->lastChild = child;

			addChildElement(&parent->element, &child->element);
		}

		void nodeRemoveChild(struct Node* parent, struct Node* child)
		{
			if (child->parent != parent) {
				return;
			}

			child->parent = nullptr;
			if (child->prev) {
				child->prev->next = child->next;
			} else {
				parent->firstChild = child->next;
			}
			if (child->next) {
				child->next->prev = child->prev;
			} else {
				parent->lastChild = child->prev;
			}

			child->next = nullptr;

			removeChildElement(&parent->element, &child->element);
		}

		void nodeInsertChildAt(struct Node* parent, struct Node* child, unsigned int index) 
		{
			if (child->parent) {
				nodeRemoveChild(child->parent, child);
			}

			child->parent = parent;

			// find target node
			unsigned int node_index = 0;
			auto node = parent->firstChild;
			while (node) {
				if (node_index == index) {
					break;
				}
				node = node->next;
				node_index++;
			}

			if (node_index == index) {
				// reset node link
				child->prev = node->prev;
				child->next = node;
				child->next->prev = child;
				if (child->prev) {
					child->prev->next = child;
				}
				if (index == 0) {
					parent->firstChild = child;
				}
				insertChildElementAt(&parent->element, &child->element, index);
			} else {
				nodeAddChild(parent, child);
			}
		}

		struct Node* nodeRequestLayout(struct Node* node)
		{
			while (node->parent != nullptr) {
				node = node->parent;
			}
			return node;
		}

		static void measureNodes(enum LayoutType type, struct Node* node)
		{
			while (node) {
				measureNode(type, &node->properties, &node->element);

				if (node->firstChild) {
					measureNodes(node->element.layoutType, node->firstChild);
				}

				node = node->next;
			}
		}

		static void invokeLayoutCallback(struct Node* node)
		{
			if (node->onLayout) {
				node->onLayout(node);
			}

			struct Node* child = node->firstChild;
			while (child) {
				invokeLayoutCallback(child);
				child = child->next;
			}
		}

		void nodeLayout(struct Node* root)
		{
			if (!root->firstChild) {
				return;
			}

			// Pass 1 - Measure any invalidated child nodes.
			measureNodes(root->element.layoutType, root->firstChild);

			// Pass 2 - Layout out children.
			layoutNode(&root->element,
			           root->element.measuredWidth,
			           root->element.measuredHeight,
			           false,
			           false);

			// Pass 3 - Invoke post layout callbacks.
			invokeLayoutCallback(root);
		}
	} // namespace LayoutEngine
} // namespace Titanium
