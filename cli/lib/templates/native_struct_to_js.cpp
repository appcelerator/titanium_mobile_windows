<%
// This expects:
// to_assign: the name of the JS variable to assign the resulting object to
// type: the _definition_ of the struct type from the metadata! Note that this differs from other partials that expect a type name for this variable!
// metadata: pointer to the full metadata
// argument_name: the name of the native variable we're converting from
// context_name: name of the JSContext var to use. typically 'context'

// TODO Handle arrays of structs!

// We need to hold onto copies of the original values.
// Recursive structs mean that to_assign, field_name and the temp var we assign to
// all those values get modifies after the sub-include here and before we get to the next chunk of the template where we use them!
var orig_to_assign = to_assign,
	orig_sub_assign = "",
	orig_field = "";
%>
			auto <%= to_assign %> = <%- context_name %>.CreateObject();<%
		for (field_name in type.fields) {
			orig_sub_assign = argument_name.replace(/\./g, '_') + '_' + field_name + '_';
			orig_field = field_name;
-%>
<%- include('native_to_js.cpp', {type: type.fields[field_name].type, metadata: metadata, to_assign: argument_name.replace(/\./g, '_') + '_' + field_name + '_', argument_name: argument_name + '.' + field_name, context_name: context_name }) -%>			<%= orig_to_assign %>.SetProperty("<%= orig_field %>", <%- orig_sub_assign %>);
<%
		}
-%>