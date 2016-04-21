/**
* Titanium.API for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/API.hpp"

namespace TitaniumWindows
{
	API::API(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::API(js_context) 
		, logger__(std::make_shared<LogForwarder>())
	{

	}

	API::~API() TITANIUM_NOEXCEPT
	{

	}

	void API::log(const std::string& message) const TITANIUM_NOEXCEPT
	{
		logger__->log(message);
	}

	void API::JSExportInitialize() 
	{
		JSExport<API>::SetClassVersion(1);
		JSExport<API>::SetParent(JSExport<Titanium::API>::Class());
	}

	void API::postInitialize(JSObject& this_object) 
	{
		logger__->connect();
	}

}  // namespace TitaniumWindows
