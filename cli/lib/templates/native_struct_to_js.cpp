<%#
// This expects:
// to_assign: the name of the JS variable to assign the resulting object to
// type: the _definition_ of the struct type from the metadata! Note that this differs from other partials that expect a type name for this variable!
// metadata: pointer to the full metadata
// argument_name: the name of the native variable we're converting from

// TODO Handle arrays of structs!
%>
			auto <%= to_assign %> = context.CreateObject();<%
		for (field_name in type.fields) {
-%>
<%- include('native_to_js.cpp', {type: type.fields[field_name].type, metadata: metadata, to_assign: argument_name + '_' + field_name + '_', argument_name: argument_name + '.' + field_name }) -%>			<%= to_assign %>.SetProperty("<%= field_name %>", <%= argument_name %>_<%= field_name %>_);
<%
		}
-%>