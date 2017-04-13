<%
// This expects:
// to_assign: the name of the JS variable to assign the resulting object to
// type: the name of the type we're converting
// metadata: pointer to the full metadata
// argument_name: the name of the native variable we're converting from
// context_name: name of the JSContext var to use. typically 'context'

//	It's a class. Let's wrap the native item in our native wrapper for the defined type
type = type.trim();

if (type.indexOf('Windows.Foundation.IReference`1') == 0) {
	type = type.substring(type.indexOf('`1<') + 3, type.length - 1);
-%>
		JSValue <%= to_assign %> = <%- context_name %>.CreateNull();
		if (<%- argument_name %> != nullptr) {
			<%- include('native_to_js.cpp', {type: type, metadata: metadata, to_assign: argument_name + '_maybe', argument_name: argument_name + '->Value', context_name: context_name }) -%>
			<%= to_assign %> = <%- argument_name %>_maybe;
		}
<%
}
else if (type.indexOf('[]') == type.length - 2) { // 'primitive' array
	// Strip off the [], then proceed knowing it's an array...
	type = type.substring(0, type.length - 2);
-%>
			std::vector<JSValue> <%= to_assign %>_vector;
			for (size_t i = 0; i < <%- argument_name %>->Length; ++i) {
				<%- include('native_class_to_js.cpp', {type: type, metadata: metadata, to_assign: argument_name + '_tmp', argument_name: argument_name + '[i]', context_name: context_name }) -%>
				<%= to_assign %>_vector.push_back(<%- argument_name %>_tmp);
			}

			auto <%= to_assign %> = <%- context_name %>.CreateArray(<%= to_assign %>_vector);
<%
} else if (type.indexOf('.IVector') != -1) { // IVector/IVectorView
	// Pull out the internal type!
	type = type.substring(type.indexOf('`1<') + 3, type.length - 1);
-%>
			std::vector<JSValue> <%= to_assign %>_vector;
			for (uint32_t i = 0; i < <%= argument_name %>->Size; ++i) {
				auto current = <%- argument_name %>->GetAt(i);
				<%- include('native_to_js.cpp', {type: type, metadata: metadata, to_assign: argument_name + '_tmp', argument_name: 'current', context_name: context_name }) -%>
				<%= to_assign %>_vector.push_back(<%= argument_name %>_tmp);
			}

			auto <%= to_assign %> = <%- context_name %>.CreateArray(<%= to_assign %>_vector);
<%
} else  if (type.indexOf('.IIterator') != -1) { // IIterator
	// Pull out the internal type!
	type = type.substring(type.indexOf('`1<') + 3, type.length - 1);
-%>
			std::vector<JSValue> <%= to_assign %>_vector;
			while (<%- argument_name %>->HasCurrent) {
				<%- include('native_to_js.cpp', {type: type, metadata: metadata, to_assign: argument_name + '_tmp', argument_name: argument_name + '->Current', context_name: context_name }) -%>
				<%= to_assign %>_vector.push_back(<%- argument_name %>_tmp);
				<%- argument_name %>->MoveNext();
			}

			auto <%= to_assign %> = <%- context_name %>.CreateArray(<%= to_assign %>_vector);
<%
} else  if (type.indexOf('.IIterable') != -1) { // IIterable
	// Call First() method, then treat that as IIterator
	type = type.substring(type.indexOf('`1<') + 3, type.length - 1);
	type = 'Windows.Foundation.Collections.IIterator`1<' + type + '>';
-%>
			auto <%= to_assign %>_iter = <%- argument_name %>->First();
			<%- include('native_class_to_js.cpp', {type: type, metadata: metadata, to_assign: to_assign, argument_name: to_assign + '_iter', context_name: context_name }) -%>
<%
} else if (type.indexOf('.IKeyValuePair') != -1) { // IKeyValuePair
	// Pull out the internal type!
	type = type.substring(type.indexOf('`2<') + 3, type.length - 1);
	// Split the type in two using the comma
	var commaIndex = type.indexOf(',');
	var key_type_name = type.substring(0, commaIndex);
	var value_type_name = type.substring(commaIndex + 1);
	// Ideally we'd use a Map, but that's not in ECMAScript 5, it's in ES6!
-%>
			auto <%= to_assign %> = <%- context_name %>.CreateObject();
			<%- include('native_to_js.cpp', {type: key_type_name, metadata: metadata, to_assign: to_assign + '_key_tmp', argument_name: argument_name + '->Key', context_name: context_name }) -%>
			<%- include('native_to_js.cpp', {type: value_type_name, metadata: metadata, to_assign: to_assign + '_value_tmp', argument_name: argument_name + '->Value', context_name: context_name }) -%>
			<%= to_assign %>.SetProperty("key", <%= to_assign %>_key_tmp);
			<%= to_assign %>.SetProperty("value", <%= to_assign %>_value_tmp);
<%
} else if (type.indexOf('.IMap') != -1) { // IMap/IMapView
	// Pull out the internal types for key and value!
	type = type.substring(type.indexOf('`2<') + 3, type.length - 1);
	// Treat as equivalent of Iterable<IKeyValuePair<K,V>>
	type = 'Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<' + type + '>>';
-%>
<%- include('native_class_to_js.cpp', {type: type, metadata: metadata, to_assign: to_assign, argument_name: argument_name, context_name: context_name }) -%>
<%
} else { // normal class
-%>
			auto <%= to_assign %> = <%- context_name %>.CreateObject(JSExport<<%- type.replace(/\./g, '::') %>>::Class());
			auto <%= to_assign %>_wrapper = <%= to_assign %>.GetPrivate<<%- type.replace(/\./g, '::') %>>();
			<%= to_assign %>_wrapper->wrap(<%- argument_name %>);
<%
}
-%>