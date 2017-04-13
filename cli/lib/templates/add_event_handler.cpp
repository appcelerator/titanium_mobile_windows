<%
// TODO We need to assert that there is one argument, that it's an object and a function. It's our callback
// TODO We then need to hook an event handler like so:

var event_name = methods[0].name.substring(4), // drop "add_"
	handler_type_name = methods[0].args[0].type,
	handler_type,
	invoke_method,
	event_type_name = "",
	event_type,
	parameters = ""; // Build up the list of paremeters that the handler needs!
if (handler_type_name.indexOf('class ') == 0) {
	handler_type_name = handler_type_name.substring(6); // strip off leading 'class '
}
// handle special common handler types:
if (handler_type_name.indexOf("Windows.Foundation.EventHandler`1") == 0) {
	var inner = handler_type_name.substring(34, handler_type_name.length - 1); // grab inner type
	if (inner == 'object') {
		inner = 'Platform.Object';
	}
	if (inner.indexOf("class ") == 0) {
		inner = inner.substring(6); // drop off "class "
	}
	handler_type_name = "Windows.Foundation.EventHandler<::";
	handler_type_name += inner;
	handler_type_name += "^>";
	event_type_name = inner;
	parameters = "::Platform::Object^ sender, ::" + inner.replace(/\./g, '::') + "^ e";
} else if (handler_type_name.indexOf("Windows.Foundation.TypedEventHandler`2") == 0) {
	var inner = handler_type_name.substring(handler_type_name.indexOf('`2<') + 3, handler_type_name.length - 1),
		sender = inner.substring(0, inner.indexOf(',')),
		result = inner.substring(inner.indexOf(',') + 1);
	if (sender.indexOf("class ") == 0) {
		sender = sender.substring(6); // drop off "class "
	}
	if (sender == 'object') {
		sender = 'Platform.Object';
	}
	if (result.indexOf("class ") == 0) {
		result = result.substring(6); // drop off "class "
	}
	if (result == 'object') {
		result = 'Platform.Object';
	}
	handler_type_name = "Windows.Foundation.TypedEventHandler<::";
	handler_type_name += sender;
	handler_type_name += "^, ::";
	handler_type_name += result;
	handler_type_name += "^>";

	event_type_name = result;

	parameters = "::" + sender.replace(/\./g, '::') + "^ sender, ::" + result.replace(/\./g, '::') + "^ e";
} else {
	// Dedicated event handler delegate type
	handler_type = metadata[handler_type_name]; // grab handler type from metadata

	// Find the Invoke method in handler_type.methods!
	// FIXME Use nicer JS to find it!
	for (var i = 0; i < handler_type.methods.length; i++) {
		var method = handler_type.methods[i];
		if (method.name == "Invoke") {
			invoke_method = method;
			break;
		}
	}

	// loop through the arguments and turn them into parameters
	for (var x = 0; x < invoke_method.args.length; x++) {
		var arg = invoke_method.args[x],
			arg_type = arg.type;
		// Normalize type name FIXME We have code like this all over the place!
		if (arg_type == 'object') {
			arg_type = "Platform.Object";
		}
		if (arg_type.indexOf("class ") == 0) {
			arg_type = arg_type.substring(6); // drop off "class "
		}
		// FIXME What if arg_type starts with 'valuetype '?
		event_type_name = arg_type;
		parameters += "::" + arg_type.replace(/\./g, '::') + "^ " + arg.name + ", ";
	}
	if (parameters.length > 0) {
		parameters = parameters.substring(0, parameters.length - 2); // Drop trailing ", "
	}

}

// Pull the metadata for the actual event object
event_type = metadata[event_type_name];
-%>
			if (event_name == "<%= event_name %>") {
				<%= event_name %>_token__ = unwrap()-><%= event_name %> += ref new ::<%- handler_type_name.replace(/\./g, '::') %>([context, this](<%- parameters %>) {
					auto eventArgs = context.CreateObject();
					// TODO Convert the args and pass them to event object we pass to callback!
<%
// FIXME If we couldn't find the event type, we won't be forwarding on the event data properly!
if (event_type) {
	for (property_name in event_type.properties) {
		if (event_type.properties[property_name]['setter']) {
-%>	
					auto <%= property_name %>_orig = e-><%= property_name %>;
					<%- include('native_to_js.cpp', {type: event_type.properties[property_name].returnType, metadata: metadata, to_assign: property_name + '_', argument_name: property_name + '_orig', context_name: 'context' }) -%>
					eventArgs.SetProperty("<%= property_name %>", <%= property_name %>_);
<%
		}
	}
}
-%>
					this->fireEvent("<%= event_name %>", eventArgs);
				});
				return;
			}
