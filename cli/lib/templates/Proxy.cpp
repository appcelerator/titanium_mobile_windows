<%
String.prototype.to_windows_name = function() {
	return this.replace(/\./g, '::');
};

var full_name = name;
var namespaces = ['Titanium'];
namespaces = namespaces.concat(full_name.split('.'));
var base_name = namespaces[namespaces.length - 1];
var underscore_name = full_name.replace(/\./g, '_');
var name_upper = underscore_name.toUpperCase();
var windows_name = full_name.to_windows_name();
var unique_methods = {}; // name to array of overloads

var parent_name = "Titanium::Platform::Object";
if (parent && parent.indexOf('[mscorlib]') != 0) {
	parent_name = parent.trim();
}

// Set up overloaded constructors!
if (methods) {
	for (var i = 0; i < methods.length; i++) {
		var method = methods[i];
		var overloads = [];
		// skip property methods
		if (method.name.indexOf('get_') == 0 || method.name.indexOf('put_') == 0) {
				continue;
		}
		// Skip non-public methods
		if (method.attributes.indexOf("public") == -1) {
			continue;
		}
		// For now skip store only methods
		// FIXME Guard with #ifdef!
		if (method.api && method.api == 'store') {
			continue;
		}

		// skip methods return async ops until we implement a Promise equivalent wrapper
		if (method.returnType.indexOf('.IAsync') != -1 && method.returnType.indexOf('Progress') != -1) {
			continue;
		}

		// Combine overloaded methods...
		overloads = unique_methods[method.name] || [];
		overloads.unshift(method);
		unique_methods[method.name] = overloads;
	}
}


// gather all the types referenced in this file! We calculated this already in stub.js (assuming we set seeds)
var types_to_include = dependencies || [full_name];
// sort and de-dupe
types_to_include = types_to_include.sort();
types_to_include = types_to_include.filter(function(elem, pos) {
    return types_to_include.indexOf(elem) == pos;
});
-%>
/**
 * Windows Native Wrapper for <%= full_name %>
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
<%
if (types_to_include.indexOf('Windows.UI.Xaml.UIElement') != -1) {
-%>
#include "Titanium/UI/View.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
<%
}
for (var i = 0; i < types_to_include.length; i++) {
	var type_name = types_to_include[i],
		index = type_name.indexOf('`');
	if (index != -1) { // strip off templated portion of name!
		type_name = type_name.substring(0, index);
	}

	// HACK, skip the types we auto-convert to JSArrays/JSObjects...
	if (type_name == 'Windows.Foundation.Collections.IIterator' ||
		type_name == 'Windows.Foundation.Collections.IIterable' ||
		type_name == 'Windows.Foundation.Collections.IVector' ||
		type_name == 'Windows.Foundation.Collections.IVectorView' ||
		type_name == 'Windows.Foundation.Collections.IMap' ||
		type_name == 'Windows.Foundation.Collections.IMapView' ||
		type_name == 'Windows.Foundation.Collections.IKeyValuePair' ||
		type_name.indexOf('.IAsync') != -1) {
		continue;
	}
	// Skip enums and structs
	var other_type = metadata[type_name];
	if (!other_type || (other_type['extends'] && 
		(other_type['extends'].indexOf("[mscorlib]System.Enum") == 0 ||
		other_type['extends'].indexOf("[mscorlib]System.ValueType") == 0))) {
		continue;	
	}
-%>
#include "<%= type_name %>.hpp"
<%
}
-%>

#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <collection.h>

<% for (var i = 0; i < namespaces.length - 1; i++) { -%>
<%= Array(i + 1).join('\t') %>namespace <%= namespaces[i] %>
<%= Array(i + 1).join('\t') %>{
<% } -%>

		<%= base_name %>::<%= base_name %>(const JSContext& js_context) TITANIUM_NOEXCEPT
			: <%= parent_name.to_windows_name() %>(js_context)
		{
			TITANIUM_LOG_DEBUG("<%= base_name %>::ctor");
		}

		void <%= base_name %>::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("<%= base_name %>::postCallAsConstructor ", this);
<%
if (unique_methods['.ctor']) {
	// FIXME Combine with common code from function.cpp!
	var arguments = "",
		arg,
		type,
		as_param,
		method,
		methods = unique_methods[".ctor"];

	// FIXME We should be smarter about dispatching to overloads. Arg count alone isn't enough. We need to distinguish types too!
	for (var i = 0; i < methods.length; i++) {
		arguments = "";
		method = methods[i];

-%>
			if (arguments.size() == <%= method.args.length %>) {
<%
		// Build up our arguments!
		for (var x = 0; x < method.args.length; x++) {
			arg = method.args[x];
			type = arg.type;
			as_param = arg.name;
			if (arg.inout == "out") {
				if (type.indexOf('[]') == type.length - 2) { // it's an array!
					// Don't prepend with &, and don't mess up the type name, since it won't have a trailing &
				} else {
					as_param = "&" + as_param;
					type = type.substring(0, type.length - 1); // drop & from type we pass along to conversion
				}
			}
			arguments += as_param + ", ";
-%>
				auto _<%= x %> = arguments.at(<%= x %>);<%- include('js_to_native.cpp', {type: type, metadata: metadata, to_assign: arg.name, argument_name: '_' + x}) -%>
<%
		}

		// Chop off trailing ", " in arg list
		if (method.args.length > 0) {
			arguments = arguments.substring(0, arguments.length - 2);
		}
%>
				wrapped__ = ref new ::<%= windows_name %>(<%- arguments %>);
			}
<%
	}
}
%>
		}

		::<%= windows_name %>^ <%= base_name %>::unwrap<%= underscore_name %>() const
		{
			return dynamic_cast<::<%= windows_name %>^>(wrapped__);
		}

		::<%= windows_name %>^ <%= base_name %>::unwrap() const
		{
			return unwrap<%= underscore_name %>();
		}

		void <%= base_name %>::wrap(::<%= windows_name %>^ object)
		{
			wrapped__ = object;
		}

		void <%= base_name %>::JSExportInitialize()
		{
			JSExport<<%= base_name %>>::SetClassVersion(1);
			JSExport<<%= base_name %>>::SetParent(JSExport<<%= parent_name.to_windows_name() %>>::Class());

<%
// properties
for (property_name in properties) {
	// FIXME handle phone-only APIs!
	if (properties[property_name].api && properties[property_name].api == 'store') {
-%>
#if WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP
<%
	}
	if (properties[property_name]['setter']) {
-%>
			TITANIUM_ADD_PROPERTY(<%= base_name %>, <%= property_name %>);
<%
	} else {
-%>
			TITANIUM_ADD_PROPERTY_READONLY(<%= base_name %>, <%= property_name %>);
<%	}
	if (properties[property_name].api) {
-%>
#endif
<%
	}
}
// Methods
if (methods) {
	for (method_name in unique_methods) {
		if (method_name == ".ctor" || method_name.indexOf('add_') == 0 || method_name.indexOf('remove_') == 0) {
				continue;
		}

		// FIXME handle phone-only APIs!
		if (unique_methods[method_name][0].api && unique_methods[method_name][0].api == 'store') {
-%>
#if WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP
<%
		}
-%>
			TITANIUM_ADD_FUNCTION(<%= base_name %>, <%= method_name %>);
<%
		if (unique_methods[method_name][0].api) {
-%>
#endif
<%
		}
	}
}
-%>
		}

<%
for (property_name in properties) {
	// FIXME handle phone-only APIs!
	if (properties[property_name].api && properties[property_name].api == 'store') {
-%>
#if WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP
<%
	}
	if (properties[property_name]['setter']) { -%>
<%- include('setter.cpp', {base_name: base_name}) %>
<%  
	} -%>
<%- include('getter.cpp', {base_name: base_name}) %>
<%
	if (properties[property_name].api) {
-%>
#endif
<%
	}
} // End Properties
// Methods
if (methods) {
	for (method_name in unique_methods) {
		var methods = unique_methods[method_name];
		var method = methods[0];
		if (method.name == '.ctor' || method.name.indexOf('add_') == 0 || method.name.indexOf('remove_') == 0) {
			continue;
		}

-%>
<%- include('function.cpp', {full_name: full_name, base_name: base_name, methods: methods}) %>
<%
	}
}
-%>
		void <%= base_name %>::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			<%- parent_name.to_windows_name() %>::enableEvent(event_name);

			const JSContext context = this->get_context();
<%
// Event handlers!
if (methods) {
	for (method_name in unique_methods) {
		var methods = unique_methods[method_name];
		var method = methods[0];
		if (method.name.indexOf('add_') == 0) {
-%>
<%- include('add_event_handler.cpp', {full_name: full_name, base_name: base_name, methods: methods}) %>
<%
		}
	}
}
-%>
		}

		void <%= base_name %>::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			<%- parent_name.to_windows_name() %>::disableEvent(event_name);

			const JSContext context = this->get_context();
<%
// Event handlers!
if (methods) {
	for (method_name in unique_methods) {
		var methods = unique_methods[method_name];
		var method = methods[0];
		if (method.name.indexOf('remove_') == 0) {
-%>
<%- include('remove_event_handler.cpp', {full_name: full_name, base_name: base_name, methods: methods}) %>
<%
		}
	}
}
-%>
		}
<%
for (var i = namespaces.length - 2; i>= 0; i--) {
-%>
<%= Array(i + 1).join('\t') %>} // namespace <%= namespaces[i] %>
<% 
}
-%>
