<%#
// This expects:
// to_assign: the name of the native variable to assign the resulting object to
// type: the name of the type we're converting
// argument_name: the name of the JS variable we're converting from
%>
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsNumber(), "Expected Number");
			auto <%= to_assign %> = static_cast<::<%= type.replace(/\./g, '::') %>>(static_cast<int32_t>(<%= argument_name %>)); // TODO Look up enum in metadata to know what type it's value is? 
