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
String.prototype.repeat=function(x){return (new Array(x+1)).join(this);}
-%>
/**
 * <%= module %> for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_<%= name_upper %>_HPP_
#define _TITANIUMWINDOWS_<%= name_upper %>_HPP_

<% if (!sub_class) { -%>
#include "TitaniumWindows/detail/<%= module_path %>Base.hpp"
<% } else { -%>
#include "<%= '../'.repeat(module_classes.length-2) %>detail/<%= module_parent %>Base.hpp"
<% } -%>

namespace TitaniumWindows
{
<% for (var i=1;i<module_classes.length-1;i++) { -%>
	namespace <%= module_classes[i] %>
	{
<% } -%>

		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.<%= full_namespace.replace(/::/g,'.') %> implementation for Windows.
		*/
		class TITANIUMWINDOWS_<%= module_parent.toUpperCase() %>_EXPORT <%= namespace %> final : public Titanium::<%= full_namespace %>, public JSExport<<%= namespace %>>
		{

		public:
			<%= namespace %>(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~<%= namespace %>()                  = default;
			<%= namespace %>(const <%= namespace %>&)            = default;
			<%= namespace %>& operator=(const <%= namespace %>&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			<%= namespace %>(<%= namespace %>&&)                 = default;
			<%= namespace %>& operator=(<%= namespace %>&&)      = default;
#endif

			static void JSExportInitialize();

		private:

<% for (i in data.properties) { -%>
<% var property = data.properties[i] -%>
<% if (property.__inherits == module && (property.platforms.contains('android') && property.platforms.contains('iphone'))) {-%>
			virtual <%= getType(property.type) %> <%= property.name %>() const TITANIUM_NOEXCEPT;
<% } -%>
<% } -%>

<% for (i in data.methods) { -%>
<% var method = data.methods[i] -%>
<% if (method.__accessor != true && method.__inherits == module && (method.platforms.contains('android') && method.platforms.contains('iphone'))) {-%>
<% var parameters = ('parameters' in method ? getParameters(method.parameters) : '') -%>
<% var type = ('returns' in method ? method.returns[0].type : 'JSValue') -%>
			virtual <%= getType(type) %> <%= method.name -%>(<%= parameters %>) TITANIUM_NOEXCEPT;
<% } -%>
<% } -%>

		};
<% for (var i=1;i<module_classes.length-1;i++) { -%>
	}  // namespace <%= module_classes[i] %>
<% } -%>
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_<%= name_upper %>_HPP_
