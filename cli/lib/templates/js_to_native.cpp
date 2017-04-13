<%
// This expects:
// to_assign: the name of the native variable to assign the resulting object to
// type: the name of the type we're converting
// metadata: pointer to the full metadata
// argument_name: the name of the JS variable we're converting from

// This is the metho which determines which specific sub-template should be used for this type conversion.
// Is it a primitive? enum? struct? guid? class of some sort?

type = type.trim(); // strip off extra space
if (type == 'Platform.String') {
	type = 'string';
}
if (type == '' || type == 'object') {
	type = 'Platform.Object';
-%>
<%- include('js_to_native_class.cpp', {type: type, metadata: metadata, to_assign: to_assign, argument_name: argument_name}) -%>
<%
}
else if (type.indexOf('class ') == 0) {
	type = type.substring(6); // strip off leading 'class '
-%>
<%- include('js_to_native_class.cpp', {type: type, metadata: metadata, to_assign: to_assign, argument_name: argument_name}) -%>
<%
}
// primitives
else if (type == 'bool' ||
		type == 'char' ||
		type == 'int64' ||
		type == 'int32' ||
		type == 'int16' ||
		type == 'int' ||
		type == 'uint64' ||
		type == 'uint32' ||
		type == 'uint16' ||
		type == 'uint8' ||
		type == 'float64' ||
		type == 'float32' ||
		type == 'double' ||
		type == 'string' ||
		type == 'Platform.String') {
-%>
<%- include('js_to_native_primitive.cpp', {to_assign: to_assign, argument_name: argument_name}) -%>
<%
} else {
	// may start with 'valuetype '
	if (type.indexOf('valuetype ') == 0) {
		type = type.substring(10).trim(); // strip off leading 'valuetype '
	}

	// Now look it up in the metadata
	var type_definition = metadata[type];
	if (!type_definition) {
		// FIXME If we see it's a complex type, don't spit out this warning? i.e. Windows.Foundation.Collections.IKeyValuePair`2<object,object>
		console.log("No metadata found for: " + type); // useful to know what type we need to pull into our stripped down metadata
	}
	if (type_definition && type_definition.extends == '[mscorlib]System.Enum')
	{
-%>
<%- include('js_to_native_enum.cpp', {to_assign: to_assign, argument_name: argument_name}) -%>
<%
	}
	else if (type_definition && type_definition.extends == '[mscorlib]System.ValueType') {
-%>
<%- include('js_to_native_struct.cpp', {type: type_definition, metadata: metadata, to_assign: to_assign, argument_name: argument_name}) -%>
<%
	}
	else if (type_definition && type_definition.extends == '[mscorlib]System.Guid') {
		console.log("We don't know how to handle Guid yet!")
	} else {
		// assume class!
-%>
<%- include('js_to_native_class.cpp', {type: type, metadata: metadata, to_assign: to_assign, argument_name: argument_name}) -%>
<%
	}
}
-%>