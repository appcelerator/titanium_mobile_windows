<%
// This expects:
// to_assign: the name of the native variable to assign the resulting value to
// argument_name: the name of the JS variable we're converting from

if (type == 'bool') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsBoolean(), "Expected boolean");
			auto <%= to_assign %> = static_cast<bool>(<%= argument_name %>);
<%
} else if (type == 'int32' || type == 'int16' || type == 'int' || type == 'char') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsNumber(), "Expected Number");
			auto <%= to_assign %> = static_cast<int32_t>(<%= argument_name %>);
<%
} else if (type == 'uint32' || type == 'uint16' || type == 'uint8') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsNumber(), "Expected Number");
			auto <%= to_assign %> = static_cast<uint32_t>(<%= argument_name %>);
<%
} else if (type == 'double') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsNumber(), "Expected Number");
			auto <%= to_assign %> = static_cast<double>(<%= argument_name %>);
<%
} else if (type == 'uint64') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsNumber(), "Expected Number");
			auto <%= to_assign %> = static_cast<uint64>(static_cast<double>(<%= argument_name %>));
<%
} else if (type == 'int64') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsNumber(), "Expected Number");
			auto <%= to_assign %> = static_cast<int64>(static_cast<double>(<%= argument_name %>));
<%
} else if (type == 'float32' || type == 'float64') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsNumber(), "Expected Number");
			auto <%= to_assign %> = static_cast<float>(static_cast<double>(<%= argument_name %>));
<%
} else if (type == 'string' || type == 'Platform.String') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsString(), "Expected String");
			auto <%= to_assign %> = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(<%= argument_name %>));
<%
}
-%>