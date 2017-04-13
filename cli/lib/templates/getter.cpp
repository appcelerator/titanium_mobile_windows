		TITANIUM_PROPERTY_GETTER(<%= base_name %>, <%= property_name %>)
		{
			auto value = unwrap()-><%= property_name %>;
			auto context = get_context();
<%- include('native_to_js.cpp', {type: properties[property_name]['returnType'], metadata: metadata, to_assign: 'result', argument_name: 'value', context_name: 'context'}) -%>
			return result;
		}
