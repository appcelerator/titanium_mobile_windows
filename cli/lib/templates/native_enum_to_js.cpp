<%#
// This expects:
// to_assign: the name of the JS variable to assign the resulting object to
// argument_name: the name of the native variable we're converting from
// context_name: name of the JSContext var to use. typically 'context'
%>
			auto <%= to_assign %> = <%- context_name %>.CreateNumber(static_cast<int32_t>(static_cast<int>(<%= argument_name %>))); // FIXME What if the enum isn't an int based one?!
