/**
 * Global for Windows
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_GLOBALOBJECT_HPP_
#define _TITANIUMWINDOWS_GLOBALOBJECT_HPP_

#include "TitaniumWindows/detail/GlobalBase.hpp"

namespace TitaniumWindows {

using namespace JavaScriptCoreCPP;

/*!
  @class
  
  @discussion This is the Titanium GlobalObject implementation for
  Windows.
*/
class TITANIUMWINDOWS_GLOBAL_EXPORT GlobalObject final : public Titanium::GlobalObject, public JSExport < GlobalObject > {
	
public:
	
	std::string get_example_resource() const                              TITANIUM_NOEXCEPT;
	void        set_example_resource(const std::string& example_resource) TITANIUM_NOEXCEPT;
	
	
	GlobalObject(const JSContext& js_context)                                TITANIUM_NOEXCEPT;
	GlobalObject(const GlobalObject&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
	
	virtual ~GlobalObject() = default;
	GlobalObject(const GlobalObject&) = default;
	GlobalObject& operator=(const GlobalObject&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
	GlobalObject(GlobalObject&&)                 = default;
	GlobalObject& operator=(GlobalObject&&)      = default;
#endif
	
	static void JSExportInitialize();
	
protected:
	
	virtual std::string LoadResource(const std::string& moduleId) const TITANIUM_NOEXCEPT override final;
	virtual std::shared_ptr<Titanium::GlobalObject::Timer> CreateTimer(Callback_t callback, const std::chrono::milliseconds& interval) const TITANIUM_NOEXCEPT override final;
	
private:
	
	std::string example_resource__;
};

}  // namespace TitaniumWindows {

#endif // _TITANIUMWINDOWS_GLOBALOBJECT_HPP_
