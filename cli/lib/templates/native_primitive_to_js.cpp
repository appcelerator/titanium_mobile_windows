<%
// This expects:
// to_assign: the name of the JS variable to assign the resulting object to
// argument_name: the name of the native variable we're converting from

// TODO int64, uint64, single, char16
if (type == 'bool') {
-%> 
			auto <%= to_assign %> = context.CreateBoolean(<%= argument_name %>); 
<%
} else if (type == 'int32' || type == 'uint32' || type == 'double') {
-%> 
			auto <%= to_assign %> = context.CreateNumber(<%= argument_name %>);
<%
} else if (type == 'uint16' || type == 'uint8') {
-%>
			auto <%= to_assign %> = context.CreateNumber(static_cast<uint32_t>(<%= argument_name %>));
<%
} else if (type == 'int16' || type == 'int') {
-%>
			auto <%= to_assign %> = context.CreateNumber(static_cast<int32_t>(<%= argument_name %>));
<%
} else if (type == 'string') {
-%> 
			auto <%= to_assign %> = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(<%= argument_name %>));
<%
} else if (type == 'float32' || type == 'float64' || type == 'int64') {
-%>
			auto <%= to_assign %> = context.CreateNumber(static_cast<double>(<%= argument_name %>));
<%
}
-%>