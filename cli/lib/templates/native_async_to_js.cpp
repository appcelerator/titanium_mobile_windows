<%
// This expects:
// to_assign: the name of the JS variable to assign the resulting object to
// type: the name of the return type we're converting
// metadata: pointer to the full metadata
// arguments: the arguments
// method_name: name of the method being invoked
// receiver: receiver of the method call
var captures = "";
//	It's a class. Let's wrap the native item in our native wrapper for the defined type
type = type.trim();
if (type.indexOf('class ') == 0) {
	type = type.substring(6); // strip off leading 'class '
}

function cleanUpTypeName(typeName) {
	var type = typeName.trim(),
		index = -1,
		count = '',
		collectionName = '',
		innerType = '';

	// primitives remain untouched
	if (type == 'bool' || type == 'int32' || type == 'uint32' || 
		type == 'double' || type == 'uint16' || type == 'uint8' ||
		type == 'int16' || type == 'int' || type == 'void' ||
		type == 'float32' || type == 'float64' || type == 'int64' ||
		type == 'int64' || type == 'uint64' || type == 'single' ||
		type == 'char16') {
			return type;
	}

	// remove prefixes
	if (type.indexOf('class ') == 0) {
		type = type.substring(6);
	}
	else if (type.indexOf('valuetype ') == 0) {
		return "::" + type.substring(10);
	}

	// handle "short names" for base types
	if (type == 'object') {
		return '::Platform.Object^';
	}
	else if (type == 'string') {
		return '::Platform.String^';
	}

	// complex type with generics?
	index = type.indexOf('`');
	if (index == -1) {
		return '::' + type + '^';
	}

	// templated type
	count = type.substring(index + 1, index + 2); // are there 1 or 2 templated args?
	collectionName = cleanUpTypeName(type.substring(0, index)); // grab the original type
	collectionName = collectionName.substring(0, collectionName.length - 1); // drop trailing ^
	if (count == '1') {
		// clean up single inner type
		innerType = cleanUpTypeName(type.substring(index + 3, type.length - 1)); // drop '`1<' and trailing '>'
	} else if (count == '2') {
		type = type.substring(index + 3, type.length - 1); // take the segment inside the template <>
		// split on ','
		index = type.indexOf(',');
		innerType = cleanUpTypeName(type.substring(0, index)) + ', ' +  cleanUpTypeName(type.substring(index + 1));
	}
	return collectionName + '<' + innerType + '>^';
}

if (type.indexOf('Windows.Foundation.IAsyncAction') == 0) {
	if (type.indexOf('WithProgress`1') != -1) {
		type = type.substring(type.indexOf('`1<') + 3, type.length - 1); // progress type!
	} else {
		type = 'void';
	}
}
// TODO IAsyncOperationWithProgress`2, just treat like IAsyncOperation with first type
else if (type.indexOf('Windows.Foundation.IAsyncOperation`1') == 0) {
	type = type.substring(type.indexOf('`1<') + 3, type.length - 1);
}

// capture all args by reference
for (var x = 0; x < method.args.length; x++) {
	captures += ", &" + method.args[x].name;
}
-%>
				JSFunctionCallback callback = [this, &context<%- captures %>](const std::vector<JSValue> arguments, JSObject& to) {
					auto resolve = std::make_shared<JSObject>(static_cast<JSObject>(arguments.at(0)));
					auto reject = std::make_shared<JSObject>(static_cast<JSObject>(arguments.at(1)));
					auto shared_cntxt = std::make_shared<JSContext>(context);
					concurrency::create_task(<%- receiver %><%= method.name %>(<%- arguments %>)).then([shared_cntxt, resolve, reject](concurrency::task<<%- cleanUpTypeName(type).replace(/\./g, '::') %>> t) {
						try {
<%
if (type == 'void') {
-%>
							t.get();
							TITANIUM_LOG_DEBUG("Success! Invoking resolve function");
							auto result = shared_cntxt->CreateUndefined();
<%
} else {
-%>
							auto native_results = t.get();
							TITANIUM_LOG_DEBUG("Success! Invoking resolve function");
							<%- include('native_to_js.cpp', {type: type, metadata: metadata, to_assign: 'result', argument_name: 'native_results', context_name: '(*shared_cntxt)' }) -%>
<%
}	
-%>
							(*resolve)(static_cast<JSValue>(result), *resolve);
							return;
						}
						catch (...) {
							TITANIUM_LOG_DEBUG("Failed. Invoking reject function");
							(*reject)(*reject);
						}
					});
					return context.CreateUndefined();
				};
				auto promise_func = context.CreateFunction(callback);
				auto promise_maker = context.CreateFunction("return new Promise(value);", { "value" });
				auto <%= to_assign %> = promise_maker(static_cast<JSValue>(promise_func), context.get_global_object());
