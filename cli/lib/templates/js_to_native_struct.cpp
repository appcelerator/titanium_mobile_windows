<%
// This expects:
// to_assign: the name of the native variable to assign the resulting object to
// type: the _definition_ of the struct type from the metadata! Note that this differs from other partials that expect a type name for this variable!
// metadata: pointer to the full metadata
// argument_name: the name of the JS variable we're converting from

-%>
			TITANIUM_ASSERT_AND_THROW(<%= argument_name %>.IsObject(), "Expected Object");
			auto object_<%= to_assign %> = static_cast<JSObject>(<%= argument_name %>);
<%
// For every other struct we've run into, assigning fields works fine
// GridLength doesn't so we need to use the constructor
if (type.name != 'Windows.UI.Xaml.GridLength') {
-%>
			::<%= type.name.to_windows_name() %> <%= to_assign %>;
			// Assign fields explicitly since we didn't use a constructor
<%
}

// Convert all the field values to native
for (field_name in type.fields) {
-%>
			auto object_<%= to_assign %>_<%= field_name %> = object_<%= to_assign %>.GetProperty("<%= field_name %>");<%- include('js_to_native.cpp', {type:  type.fields[field_name].type, metadata: metadata, to_assign: 'object_' + to_assign + '_' + field_name + '_', argument_name: 'object_' + to_assign + '_' + field_name}) -%>
<%
	// assign the value to the struct field
	if (type.name != 'Windows.UI.Xaml.GridLength') {
-%>
			<%= to_assign %>.<%= field_name %> = object_<%= to_assign %>_<%= field_name %>_;
<%
	}
}

// FIXME This is a hack to use constructor because fields are read-only. We should add constructor info to metadata!
if (type.name == 'Windows.UI.Xaml.GridLength') {
-%>
			::<%= type.name.to_windows_name() %> <%= to_assign %>(object_<%= to_assign %>_Value_, object_<%= to_assign %>_GridUnitType_);
<%
}
-%>