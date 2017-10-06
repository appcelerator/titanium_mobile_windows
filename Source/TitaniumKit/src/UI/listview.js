/**
 * Titanium.UI.ListView module.
 *
 * @module listview
 *
 * @copyright
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var LISTVIEW_LIST_ITEM_TEMPLATE_DEFAULT = {
	childTemplates: [
		{
			type: 'Ti.UI.ImageView',
			bindId: 'image',
			properties: {
				left: 0, top: 0
			}
		},
		{
			type: 'Ti.UI.Label', 
			bindId: 'text',
			properties: {
				color: 'white',
				left: 0, top: 0,
			}
		}
	]
}; 

//Recursive function that process childTemplates and append corresponding proxy constructors to
//property 'constructor'. I.e: type: "Titanium.UI.Label" -> constructor: LabelProxy constructor
function processTemplates(template) {
	lookupCreateFunction(template);

	if (!template.hasOwnProperty('childTemplates')) return;

	var childTemplates = template.childTemplates;
	if (childTemplates === void 0 || childTemplates === null) return;

	for (var i = 0; i < childTemplates.length; i++) {
		lookupCreateFunction(childTemplates[i]);
		processTemplates(childTemplates[i]);
	}
}

function lookupCreateFunction(template) {
	if (template.createView === void 0) {
		var proxyType = template.type;
		if (proxyType !== void 0) {
			var func = lookup(proxyType);
			template.createView = func;
		} else {
			template.createView = Ti.UI.createView;
			if (template.properties === void 0) {
				template.properties = {top:0, left:0, width:Ti.UI.FILL, height:Ti.UI.SIZE};
			}
		}
	}
}

//convert name of UI elements into a constructor function.
//I.e: lookup("Titanium.UI.Label") returns Titanium.UI.createLabel function
function lookup(name) {
	var lastDotIndex = name.lastIndexOf('.');
	var proxy = global;
	var names = name.substring(0, lastDotIndex).split('.');
	for (var i = 0; i < names.length; i++) {
		var property = names[i];
		if (property in proxy) {
			proxy = proxy[property];
		} else {
			return;
		}
	}
	var proxyName = name.slice(lastDotIndex + 1);
	return proxy['create' + proxyName];
}

function ensureLoadTemplates(listview) {
	// prepare default template
	if (!listview.templates[Ti.UI.LIST_ITEM_TEMPLATE_DEFAULT]) {
		listview.templates[Ti.UI.LIST_ITEM_TEMPLATE_DEFAULT] = LISTVIEW_LIST_ITEM_TEMPLATE_DEFAULT;

		for (var binding in listview.templates) {
			processTemplates(listview.templates[binding]);
		}
	}
}

// Create item views from section
function createSectionView(listview, section) {
	section.listview = listview;
	listview.templates = listview.templates || [];
	listview.defaultItemTemplate = listview.defaultItemTemplate || Ti.UI.LIST_ITEM_TEMPLATE_DEFAULT;

	ensureLoadTemplates(listview);

	var views = [];
	var items = section.items;
	for (var i = 0; i < items.length; i++) {
		views.push(createSectionItemAt(listview, section, items[i]));
	}
	return views;
}

function createSectionItemView(listview, item, template, parent) {
	var options = template.properties;
	if (options === void 0) {
		options = {top:0, left:0, width:Ti.UI.SIZE, height:Ti.UI.SIZE};
	}

	if (template.createView === void 0) {
		processTemplates(template);
	}

	var view = template.createView(options);

	if (template.bindId !== void 0) {
		view.bindId = template.bindId;
	}

	// add event listeners
	for (var event in template.events) {
		view.addEventListener(event, template.events[event]);
	}

	// hook click and fire listview event with bindId
	view.addEventListener('click', function() {
		// check if other view already processes the event
		if (listview._itemclick_section_) {
			// set bindId and forward the event again
			listview.fireEvent('itemclick', {
				bindId:       listview._itemclick_bindId_ ? listview._itemclick_bindId_ : view.bindId,
				itemId:       listview._itemclick_itemId_,
				section:      listview._itemclick_section_,
				sectionIndex: listview._itemclick_sectionIndex_,
				itemIndex:    listview._itemclick_itemIndex_
			});
			// make sure to delete event properties so we can detect it's processed
			delete listview._itemclick_bindId_;
			delete listview._itemclick_itemId_;
			delete listview._itemclick_section_;
			delete listview._itemclick_sectionIndex_;
			delete listview._itemclick_itemIndex_;
		}
	});

	if (template.bindId !== void 0 && item[template.bindId] !== void 0) {
		view.applyProperties(item[template.bindId]);
	} else if (item.properties !== void 0) {
		if (options.height === void 0 && item.properties.height === void 0) {
			item.properties.height = Ti.UI.SIZE;
		}
		// builtin template has different format
		if (template.type == 'Ti.UI.Label') {
			item.properties.text = item.properties.title;
			view.applyProperties(item.properties);
		} else {
			view.applyProperties(item.properties);
		}
	}
	if (template.childTemplates !== void 0 && Array.isArray(template.childTemplates)) {
		for (var i = 0; i < template.childTemplates.length; i++) {
			createSectionItemView(listview, item, template.childTemplates[i], view);
		}
	}
	if (parent !== void 0) {
		parent.add(view);
	}
	return view;
}

// Create list item for custom template
function createSectionItemAt(listview, section, item) {
	var template = listview.templates[listview.defaultItemTemplate];
	if (item.template !== void 0 && listview.templates[item.template] !== void 0 ) {
		template = listview.templates[item.template];
	}
	return createSectionItemView(listview, item, template);
}

this.exports = {};
this.exports.createSectionItemAt = createSectionItemAt;
this.exports.createSectionView = createSectionView;
this.exports.processTemplates  = processTemplates;
