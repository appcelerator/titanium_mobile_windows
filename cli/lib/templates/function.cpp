<%
if (methods[0].api && methods[0].api == 'store') {
-%>
#if WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP
<%
}
-%>
		TITANIUM_FUNCTION(<%= base_name %>, <%= methods[0].name %>)
		{
			auto context = get_context();
<%
// FIXME What if function is static?!
var arguments = "",
	arg,
	type,
	as_param,
	method,
	receiver = "unwrap()->";

// FIXME We should be smarter about dispatching to overloads. Arg count alone isn't enough. We need to distinguish types too!
for (var i = 0; i < methods.length; i++) {
	arguments = "";
	method = methods[i];

-%>
			if (arguments.size() == <%= method.args.length %>) {
<%
	// Build up our arguments!
	for (var x = 0; x < method.args.length; x++) {
		arg = method.args[x];
		type = arg.type;
		as_param = arg.name;
		if (arg.inout == "out") {
			if (type.indexOf('[]') == type.length - 2) { // it's an array!
				// Don't prepend with &, and don't mess up the type name, since it won't have a trailing &
			} else {
				as_param = "&" + as_param;
				type = type.substring(0, type.length - 1); // drop & from type we pass along to conversion
			}
		}
		arguments += as_param + ", ";
-%>
				auto _<%= x %> = arguments.at(<%= x %>);<%- include('js_to_native.cpp', {type: type, metadata: metadata, to_assign: arg.name, argument_name: '_' + x}) -%>

<%
	}

	// Chop off trailing ", "
	if (method.args.length > 0) {
		arguments = arguments.substring(0, arguments.length - 2);
	}

	// Is this a static method or an instance method?
	if (method.attributes.indexOf('static') != -1) {
		receiver = "::" + full_name.replace(/\./g, '::') + "::";
	} else {
		receiver = "unwrap()->";
	}

	// Now invoke the method and return the result!
	if (method.returnType == 'void') {
-%>
				<%- receiver %><%= method.name %>(<%- arguments %>);
				return context.CreateUndefined(); 
<%
	} else if (method.returnType.indexOf('.IAsync') != -1) {
-%>
				<%- include('native_async_to_js.cpp', {type: method.returnType, metadata: metadata, to_assign: 'result', argument_name: 'method_result', arguments: arguments, receiver: receiver, method_name: method.name, method: method}) -%>
				return result;
<%
	} else {
-%>
				auto method_result = <%- receiver %><%= method.name %>(<%- arguments %>);<%- include('native_to_js.cpp', {type: method.returnType, metadata: metadata, to_assign: 'result', argument_name: 'method_result', context_name: 'context'}) -%>
<%
		// If we had "out" parameters, we now need to assign the values back to the JS Objects before returning result!

		for (var x = 0; x < method.args.length; x++) {
			arg = method.args[x];
			type = arg.type;
			if (arg.inout == "out") {
				if (type.indexOf('[]') == -1) { // Not an array...
					type = type.substring(0, type.length - 1); // drop & from type we pass along to conversion
				}
				// FIXME This assumes int32, uint32, double. We need to handle other types!
				// I've seen string, Point struct, float32, IMapView<K,V>, Rect struct, TabAlignment, TabLeader, JsonArray
-%>
<%- include('native_to_js.cpp', {type: type, metadata: metadata, to_assign: 'out_' + x, argument_name: arg.name, context_name: 'context'}) %>
				_<%= x %> = out_<%= x %>;
<%
			}
		}
-%>
				return result;
<%
	}
-%>
			}

<%
}
-%>
			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched <%= base_name %>::<%= methods[0].name %> with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}
<%
if (methods[0].api) {
-%>
#endif
<%
}
-%>
