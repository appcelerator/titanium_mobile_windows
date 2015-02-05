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

#ifndef _TITANIUM_<%= name_upper %>_HPP_
#define _TITANIUM_<%= name_upper %>_HPP_

#include "Titanium/Module.hpp"

<% for (var i = 0; i < module_classes.length - 1; i++) { -%>
<%= Array(i + 1).join('\t') %>namespace <%= module_classes[i] %>
<%= Array(i + 1).join('\t') %>{
<% } -%>

		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium <%= name %> Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.<%= full_namespace.replace(/::/g,'.') %>
		*/
		class TITANIUMKIT_EXPORT <%= namespace %> : public Module, public JSExport<<%= namespace %>>
		{

		public:
<% for (i in data.properties) { -%>
<% var property = data.properties[i] -%>
<% if (property.__inherits == module && (property.platforms.contains('android') && property.platforms.contains('iphone'))) { -%>

			/*!
			  @property
			  @abstract <%= property.name %>
			  @discussion <%= property.summary.replace(/\n/g,'') %>
			*/
<% if (property.type == 'Number' && property.permission == 'read-only') { -%>
<% property.isJS = true -%>
			virtual JSValue <%= property.name %>() const TITANIUM_NOEXCEPT final;
<% } else { -%>
			virtual <%= getType(property.type) %> <%= property.name %>() const TITANIUM_NOEXCEPT;
<% } -%>
<% } -%>
<% } -%>
<% for (i in data.methods) { -%>
<% var method = data.methods[i] -%>
<% if (method.__accessor != true && method.__inherits == module && (method.platforms.contains('android') && method.platforms.contains('iphone'))) {-%>

			/*!
			  @method
			  @abstract <%= method.name %>
			  @discussion <%= method.summary.replace(/\n/g,'') %>
			*/
<% var parameters = ('parameters' in method ? getParameters(method.parameters) : '') -%>
<% var type = ('returns' in method ? method.returns[0].type : 'JSValue') -%>
			virtual <%= getType(type) %> <%= method.name -%>(<%= parameters %>) TITANIUM_NOEXCEPT;
<% } -%>
<% } -%>

			<%= namespace %>(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~<%= namespace %>() = default;
			<%= namespace %>(const <%= namespace %>&) = default;
			<%= namespace %>& operator=(const <%= namespace %>&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			<%= namespace %>(<%= namespace %>&&)                 = default;
			<%= namespace %>& operator=(<%= namespace %>&&)      = default;
#endif

			static void JSExportInitialize();

<% for (i in data.properties) { -%>
<% var property = data.properties[i] -%>
<% if (!property.isJS && property.__inherits == module && (property.platforms.contains('android') && property.platforms.contains('iphone'))) {-%>
			virtual JSValue js_<%= property.name %>() const TITANIUM_NOEXCEPT final;
<% } -%>
<% } -%>
<% for (i in data.methods) { -%>
<% var method = data.methods[i] -%>
<% if (method.__inherits == module && (method.platforms.contains('android') && method.platforms.contains('iphone'))) {-%>
			virtual JSValue js_<%= method.name %>(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
<% } -%>
<% } -%>

<% if (data.properties.length > 0) { -%>
			protected:
#pragma warning(push)
#pragma warning(disable : 4251)
<% for (i in data.properties) { -%>
<% var property = data.properties[i] -%>
<% if (!property.isJS && property.__inherits == module && (property.platforms.contains('android') && property.platforms.contains('iphone'))) {-%>
				<%= getType(property.type) %> <%= property.name %>__;
<% } -%>
<% } -%>
#pragma warning(pop)
<% } -%>
		};

<% for (var i = module_classes.length - 2; i>= 0; i--) { -%>
<%= Array(i + 1).join('\t') %>} // namespace <%= module_classes[i] %>
<% } -%>
#endif // _TITANIUM_<%= name_upper %>_HPP_
