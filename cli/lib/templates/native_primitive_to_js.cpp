<%
// This expects:
// to_assign: the name of the JS variable to assign the resulting object to
// argument_name: the name of the native variable we're converting from
// context_name: name of the JSContext var to use. typically 'context'

if (type == 'bool') {
-%> 
			auto <%= to_assign %> = <%- context_name %>.CreateBoolean(<%- argument_name %>); 
<%
} else if (type == 'int32' || type == 'uint32' || type == 'double') {
-%> 
			auto <%= to_assign %> = <%- context_name %>.CreateNumber(<%- argument_name %>);
<%
} else if (type == 'uint16' || type == 'uint8') {
-%>
			auto <%= to_assign %> = <%- context_name %>.CreateNumber(static_cast<uint32_t>(<%- argument_name %>));
<%
} else if (type == 'int16' || type == 'int' || type == 'char') {
-%>
			auto <%= to_assign %> = <%- context_name %>.CreateNumber(static_cast<int32_t>(<%- argument_name %>));
<%
} else if (type == 'string') {
-%> 
			auto <%= to_assign %> = <%- context_name %>.CreateString(TitaniumWindows::Utility::ConvertUTF8String(<%- argument_name %>));
<%
} else if (type == 'float32' || type == 'float64' || type == 'int64' || type == 'uint64') {
-%>
			auto <%= to_assign %> = <%- context_name %>.CreateNumber(static_cast<double>(<%- argument_name %>));
<%
}
-%>