		TITANIUM_PROPERTY_SETTER(<%= base_name %>, <%= property_name %>)
		{<%- include('js_to_native.cpp', {type: properties[property_name]['returnType'], metadata: metadata, to_assign: 'value', argument_name: 'argument'}) -%>

			unwrap()-><%= property_name %> = value;
			return true;
		}
