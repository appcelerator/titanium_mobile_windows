<% 
function getType(type, parameter) {
	var r = 'JSValue';
	if (type == 'Number') {
		r = 'double';
	} else if (type == 'Boolean') {
		r = 'bool';
	} else if (type == 'void') {
		r = 'void';
	} else if (type == 'String') {
		r = (parameter ? 'const std::string&' : 'std::string');
	}
	return r;
}
function getParameters(parameters) {
	var r = '';
	for (i in parameters) {
		if (parameters[i].name.length > 0) {
			r += getType(parameters[i].type, true) + ' ' + parameters[i].name;
			if (i < parameters.length-1) {
				r += ', ';
			}
		}
	}
	return r;
}
Array.prototype.contains = function(v){ return this.indexOf(v)>-1; };
-%>
/**
 * <%= module %> for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/<%= module_path %>.hpp"
#include "Titanium/detail/TiBase.hpp"

namespace TitaniumWindows
{
<% for (var i=1;i<module_classes.length-1;i++) { -%>
<%= Array(i + 1).join('\t') %>namespace <%= module_classes[i] %>
<%= Array(i + 1).join('\t') %>{
<% } -%>

		<%= namespace %>::<%= namespace %>(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::<%= full_namespace %>(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("<%= name %>::ctor Initialize");
		}

		void <%= namespace %>::JSExportInitialize() {
			JSExport<<%= namespace %>>::SetClassVersion(1);
			JSExport<<%= namespace %>>::SetParent(JSExport<Titanium::<%= full_namespace %>>::Class());
		}

<% for (i in data.properties) { -%>
<% var property = data.properties[i] -%>
<% if (property.__inherits == module && (property.platforms.contains('android') && property.platforms.contains('iphone'))) {-%>
		<%= getType(property.type) %> <%= namespace %>::<%= property.name %>() const TITANIUM_NOEXCEPT
		{
<% if (property.type == 'String') { -%>
			return <%= property.name %>__;
<% } else if (property.type == 'Boolean') { -%>
			return <%= property.name %>__;
<% } else if (property.type == 'Number') { -%>
			return <%= property.name %>__;
<% } else { -%>
			const auto script = "";
			return get_context().JSEvaluateScript(script);
<% } -%>
		}

<% } -%>
<% } -%>
<% for (i in data.methods) { -%>
<% var method = data.methods[i] -%>
<% if (method.__accessor != true && method.__inherits == module && (method.platforms.contains('android') && method.platforms.contains('iphone'))) {-%>
<% var parameters = ('parameters' in method ? getParameters(method.parameters) : '') -%>
<% var type = ('returns' in method ? method.returns[0].type : 'JSValue') -%>
		<%= getType(type) %> <%= namespace %>::<%= method.name %>(<%= parameters %>) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("<%= name %>.<%= method.name %> is not implemented yet");
<% if (type == 'String') { -%>
			return "";
<% } else if (type == 'Boolean') { -%>
			return false;
<% } else if (type == 'Number') { -%>
			return 0;
<% } else { -%>
			return get_context().CreateUndefined();
<% } -%>
		}

<% } -%>
<% } -%>
<% for (var i = module_classes.length - 2; i >= 1; i--) { -%>
<%= Array(i + 1).join('\t') %>}  // namespace <%= module_classes[i] %>
<% } -%>
}  // namespace TitaniumWindows
