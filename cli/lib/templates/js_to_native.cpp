<%
// TODO int64, uint64, single, char16
if (type == 'bool') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsBoolean(), "Expected boolean");
			auto <%= to_assign %> = static_cast<bool>(<%= argument_name %>);
<%
} else if (type == 'int32' || type == 'int16' || type == 'int') {
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
} else if (type == 'float32' || type == 'float64') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsNumber(), "Expected Number");
			auto <%= to_assign %> = static_cast<float>(static_cast<double>(<%= argument_name %>));
<%
} else if (type == 'string') {
-%> 
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsString(), "Expected String");
			auto <%= to_assign %> = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(<%= argument_name %>));
<%
} else if (type.indexOf('valuetype ') == 0) {
	// FIXME Handle primitive arrays of structs!
	var real_type_name = type.substring(10).trim();
	// May ask for reference to a type as an argument to a method, so let's drop the trailing & for now.
	if (real_type_name.lastIndexOf('&') == real_type_name.length - 1) {
		real_type_name = real_type_name.substring(0, real_type_name.length - 1);
	}
	var other_type = metadata[real_type_name];
	if (!other_type) {
		console.log("No metadata found for: " + real_type_name); // useful to know what type we need to pull into our stripped down metadata
	}
	var is_enum = (other_type && other_type.extends == '[mscorlib]System.Enum');
	var is_struct = (other_type && other_type.extends == '[mscorlib]System.ValueType');
	var windows_type_name = real_type_name.to_windows_name();

	if (is_struct) {
		// here we generate constructor args.
		// FIXME the matadata gives no indication if the struct has a constructor or not, or the arg order. So I don't think this will work properly!
		// Looks like we'll need to improve the metadata generator. But it also appears that for those not having constructors they can only be accessed
		// through read-only getters. So let's just hope this works well enough for now...
		var ctr_args = "";
		for (field_name in other_type.fields) {
			var field_type = other_type.fields[field_name].type;
			if (field_type == 'string') {
				ctr_args =+ "\"\", ";
			} else if (field_type == 'bool') {
				ctr_args += "false, ";
			} else {
				// assume number for any other type.
				ctr_args += "0, ";
			}
		}
		ctr_args = ctr_args.substring(0, ctr_args.length - 2); 
-%>
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsObject(), "Expected Object");
			auto object_<%= to_assign %> = static_cast<JSObject>(<%= argument_name %>);
			::<%= windows_type_name %> <%= to_assign %>;
			// Assign fields explicitly since we didn't use a constructor
<%
		for (field_name in other_type.fields) {
-%>
			auto object_<%= to_assign %>_<%= field_name %> = object_<%= to_assign %>.GetProperty("<%= field_name %>");<%- include('js_to_native.cpp', {type:  other_type.fields[field_name].type, metadata: metadata, to_assign: 'object_' + to_assign + '_' + field_name + '_', argument_name: 'object_' + to_assign + '_' + field_name}) -%>
			<%= to_assign %>.<%= field_name %> = object_<%= to_assign %>_<%= field_name %>_;
<%
		}
	} else if (is_enum) {
-%>
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsNumber(), "Expected Number");
			auto <%= to_assign %> = static_cast<::<%= real_type_name.replace(/\./g, '::') %>>(static_cast<int32_t>(<%= argument_name %>)); // TODO Look up enum in metadata to know what type it's value is? 
<%
	} else {
		// Has to be struct or enum or we have an issue!
		console.log("Got a valuetype that is neither struct nor enum: " + real_type_name);
	}
} else {
	//	It's a class. Assume we have a JSObject wrapping a native impl
	var full_type_name = type.trim().replace(/\./g, '::');
	if (full_type_name.indexOf('class ') == 0) {
		full_type_name = full_type_name.substring(6);
	}
	if (full_type_name == 'object' || full_type_name == '') {
		full_type_name = 'Platform::Object';
	}
-%>
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsObject(), "Expected Object");
			auto object_<%= to_assign %> = static_cast<JSObject>(<%= argument_name %>);
<%
	if (full_type_name.indexOf('[]') == full_type_name.length - 2) {
		// Strip off the [], then proceed knowing it's an array...
		full_type_name = full_type_name.substring(0, full_type_name.length - 2);
-%>
			TITANIUM_ASSERT(object_<%= to_assign %>.IsArray());
			const auto array_<%= to_assign %> = static_cast<JSArray>(object_<%= to_assign %>);
			auto items_<%= to_assign %> = array_<%= to_assign %>.GetPrivateItems<<%= full_type_name %>>(); // std::vector<std::shared_ptr<<%= full_type_name %>>
			auto <%= to_assign %> = ref new ::Platform::Array<::<%= full_type_name %>^>(items_<%= to_assign %>.size());
			for (size_t i = 0; i < items_<%= to_assign %>.size(); ++i) {
				items[i] = items_<%= to_assign %>.at(i)->unwrap<%= full_type_name.replace(/::/g, '_') %>();
			}
<%
	} else {
-%> 
			auto wrapper_<%= to_assign %> = object_<%= to_assign %>.GetPrivate<<%= full_type_name %>>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto <%= to_assign %> = wrapper_<%= to_assign %>->unwrap<%= full_type_name.replace(/::/g, '_') %>();
<%
	}
}
-%>