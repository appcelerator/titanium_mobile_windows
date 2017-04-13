<%
var event_name = methods[0].name.substring(7), // drop "remove_"
	type = methods[0].args[0].type;
-%>
			if (event_name == "<%= event_name %>") {
				unwrap()-><%= event_name %> -= <%= event_name %>_token__;
				return;
			}
