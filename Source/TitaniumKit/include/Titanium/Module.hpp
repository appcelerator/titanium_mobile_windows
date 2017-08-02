/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_MODULE_HPP_
#define _TITANIUM_MODULE_HPP_

#include "Titanium/detail/TiBase.hpp"
#include <unordered_map>
#include <vector>

namespace Titanium
{
	using namespace HAL;

	namespace UI
	{
		class Window;
		class TabGroup;
	}

	/*!
	  @class

	  @discussion This is the Titanium Module.

	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium
	 */
	class TITANIUMKIT_EXPORT Module : public JSExportObject, public JSExport<Module>
	{
	public:

		/*!
		  @property
		  @abstract bubbleParent
		  @discussion Indicates if the proxy will bubble an event to its parent.
		*/
		TITANIUM_PROPERTY_IMPL_DEF(bool, bubbleParent);

		/*!
		  @property
		  @abstract apiName
		  @discussion The name of the API that this proxy corresponds to.
		*/
		TITANIUM_PROPERTY_IMPL_DEF(std::string, apiName);

		/*!
		  @method

		  @abstract addEventListener( name, callback ) : void

		  @discussion Adds the specified callback as an event listener for
		  the named event.

		  @param name Name of the event (String).

		  @param callback Callback function to invoke when the event is
		  fired (Function).

		  @result void
		*/
		virtual void addEventListener(const std::string& name, JSObject& callback, bool bubble = false) TITANIUM_NOEXCEPT final;

		/*!
		  @method

		  @abstract addEventListener( name, callback ) : void

		  @discussion Removes the specified callback as an event listener
		  for the named event.

		  Multiple listeners can be registered for the same event, so the
		  callback parameter is used to determine which listener to remove.

		  When adding a listener, you must save a reference to the callback
		  function in order to remove the listener later:

		  @param name Name of the event (String).

		  @param callback Callback function to invoke when the event is
		  fired (Function).

		  @result void
		*/
		virtual void removeEventListener(const std::string& name, JSObject& callback, bool bubble = false) TITANIUM_NOEXCEPT final;

		/*!
		  @method

		  @abstract applyProperties( props ) : void

		  @discussion Copy the enumerable properties from the given
		  JavaScript object to this JavaScript object.

		  @param props The JavaScript object to copy the properties from
		  (Dictionary).

		  @result void
		*/
		static void applyProperties(const JSObject& props, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		@method

		@abstract afterPropertiesSet() : void

		@discussion Invoked after all properties are supplied at constructor. 
		This method allows instance to perform initialization when all properties have been set.

		@result void
		*/
		virtual void afterPropertiesSet() TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract fireEvent( name, event ) : void

		  @discussion Fires a synthesized event to any registered
		  listeners.

		  @param name Name of the event (String).

		  @param event A dictionary of keys and values to add to the
		  Titanium.Event object sent to the listeners. (Dictionary).

		  @result void
		*/
		virtual void fireEvent(const std::string& name) TITANIUM_NOEXCEPT final;
		virtual void fireEvent(const std::string& name, const JSObject& event) TITANIUM_NOEXCEPT final;

		virtual JSObject getCtorProperties() const TITANIUM_NOEXCEPT final
		{
			return ctorProperties__;
		}

		Module(const JSContext&, const std::string& apiName = "Titanium.Proxy") TITANIUM_NOEXCEPT;
		virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

		virtual ~Module() TITANIUM_NOEXCEPT;  //= default;
		Module(const Module&) = default;
		Module& operator=(const Module&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Module(Module&&) = default;
		Module& operator=(Module&&) = default;
#endif

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.
		static void JSExportInitialize();
		static void ShowRedScreenOfDeath(const JSContext& js_context, const std::string& message) TITANIUM_NOEXCEPT;

		TITANIUM_PROPERTY_DEF(bubbleParent);
		TITANIUM_PROPERTY_READONLY_DEF(apiName);
		TITANIUM_PROPERTY_DEF(lifecycleContainer);

		TITANIUM_FUNCTION_DEF(getBubbleParent);
		TITANIUM_FUNCTION_DEF(setBubbleParent);
		TITANIUM_FUNCTION_DEF(getApiName);
		TITANIUM_FUNCTION_DEF(getLifecycleContainer);
		TITANIUM_FUNCTION_DEF(setLifecycleContainer);

		TITANIUM_FUNCTION_DEF(addEventListener);
		TITANIUM_FUNCTION_DEF(removeEventListener);
		TITANIUM_FUNCTION_DEF(applyProperties);
		TITANIUM_FUNCTION_DEF(fireEvent);

		virtual bool hasEventListener(const std::string& event_name) TITANIUM_NOEXCEPT;

		/*
		* Stop firing all events, especially used when module is closed/hidden.
		*/
		virtual void disableEvents() TITANIUM_NOEXCEPT
		{
			enableEvents__ = false;
		}

		virtual void enableEvents() TITANIUM_NOEXCEPT
		{
			enableEvents__ = true;
		}

	protected:
		/*!
		  @method

		  @abstract Notify Module subclasses that there are event listeners
		  for the event with the given name.

		  @param event_name Name of the event for which there are event
		  listeners.

		  @result void
		*/
		virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract Notify Module subclasses that there are no longer any
		  event listeners for the event with the given name. It is
		  guaranteed that the method enableEvent will have been called
		  before disableEvent.

		  @param event_name Name of the event for which there are no longer
		  any event listeners.

		  @result void
		*/
		virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT;

		template<typename T>
		std::shared_ptr<T> get_shared_ptr_for_module()
		{
			return get_object().GetPrivate<T>();
		}

		template<typename T>
		std::weak_ptr<T> get_weak_ptr_for_module()
		{
			return get_shared_ptr_for_module<T>();
		}

#pragma warning(push)
#pragma warning(disable : 4251)
		bool propertiesSet__{ false };
		bool bubbleParent__ { true };
		std::string apiName__;
		std::shared_ptr<Titanium::UI::Window> lifecycleContainerWindow__;
		std::shared_ptr<Titanium::UI::TabGroup> lifecycleContainerTabGroup__;

		std::unordered_map<std::string, std::vector<JSObject>> event_listener_map__;
		std::unordered_map<std::string, std::vector<JSObject>> event_bubble_map__;
		bool enableEvents__ { true };

		// Save constructor arguments so module can make copy of itself later on
		JSObject ctorProperties__;
#pragma warning(pop)
	private:
		static int eventListenerIndex(const std::vector<JSObject>& event_listener_list, const std::string& name, JSObject& callback) TITANIUM_NOEXCEPT;
	};
}  // namespace Titanium

#endif  // _TITANIUM_MODULE_HPP_
