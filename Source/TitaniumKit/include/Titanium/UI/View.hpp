/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_VIEW_HPP_
#define _TITANIUM_UI_VIEW_HPP_

#include "Titanium/Module.hpp"
#include <vector>
#include <memory>

namespace Titanium { namespace UI {
	
	using namespace HAL;
	
	class View;
	
	using NativeChildPtr_t		 = std::shared_ptr<Titanium::UI::View>;
	using NativeChildrenList_t = std::vector<NativeChildPtr_t>;
	
	/*!
	 @class
	 
	 @discussion This is the Titanium UI View.
	 
	 See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.View
	 */
	class TITANIUMKIT_EXPORT View : public Module, public JSExport<View> {
		
	public:
		
		/*!
		 @method
		 
		 @abstract add( view ) : void
		 
		 @discussion Adds a child to this view's hierarchy. The child view
		 is added as the last child in this view's hierarchy.
		 
		 @param view View to add to this view's
		 hierarchy. (Titanium.UI.View)
		 
		 @result void
		 */
		virtual void add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT;

	/*!
	@method

	@abstract hide() : void

	@discussion Hides the view and it's chldren in the view's hierarchy.

	@param 

	@result void
	*/
	virtual void hide(JSObject& this_object) TITANIUM_NOEXCEPT;

	/*!
	@method

	@abstract show() : void

	@discussion Causes the view and the view's hierarchy to be displayed. 

	@param 

	@result void
	*/
	virtual void show(JSObject& this_object) TITANIUM_NOEXCEPT;

		
		virtual JSArray get_children() const TITANIUM_NOEXCEPT final;
		
		virtual JSValue get_backgroundColor() const												 TITANIUM_NOEXCEPT final;
		virtual void		set_backgroundColor(const JSValue& backgroundColor) TITANIUM_NOEXCEPT final;
		
		virtual JSValue get_top() const																		 TITANIUM_NOEXCEPT final;
		virtual void		set_top(const JSValue& top)												 TITANIUM_NOEXCEPT final;
		
		virtual JSValue get_left() const																		TITANIUM_NOEXCEPT final;
		virtual void		set_left(const JSValue& left)											 TITANIUM_NOEXCEPT final;
		
		virtual JSValue get_bottom() const																	TITANIUM_NOEXCEPT final;
		virtual void		set_bottom(const JSValue& bottom)									 TITANIUM_NOEXCEPT final;
		
		virtual JSValue get_right() const																	 TITANIUM_NOEXCEPT final;
		virtual void		set_right(const JSValue& right)										 TITANIUM_NOEXCEPT final;
		
		virtual JSObject get_center() const																 TITANIUM_NOEXCEPT final;
		virtual void		 set_center(const JSObject& center)								 TITANIUM_NOEXCEPT final;

		virtual JSValue get_width() const																	 TITANIUM_NOEXCEPT final;
		virtual void		set_width(const JSValue& width)										 TITANIUM_NOEXCEPT final;
		
		virtual JSValue get_height() const																	TITANIUM_NOEXCEPT final;
		virtual void		set_height(const JSValue& height)									 TITANIUM_NOEXCEPT final;

	virtual JSValue get_layout() const																	TITANIUM_NOEXCEPT final;
	virtual void		set_layout(const JSValue& height)									 TITANIUM_NOEXCEPT final;
		
		View(const JSContext& js_context)												TITANIUM_NOEXCEPT;
		View(const View&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
		
		virtual ~View() TITANIUM_NOEXCEPT;//= default;
		View(const View&)						= default;
		View& operator=(const View&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		View(View&&)								 = default;
		View& operator=(View&&)			= default;
#endif
		
		// TODO: The following functions can automatically be generated
		// from the YAML API docs.
		static void JSExportInitialize();
		
	virtual JSValue addArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
	virtual JSValue hideArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
	virtual JSValue showArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

		// Base classes must implement this method. This is the minimum
		// functionality that you should perform:
		//
		// TITANIUM_ASSERT(argument.IsString());
		// bool result = false;
		// const std::string backgroundColor = static_cast<std::string>(argument);
		// Set the native view's background color to backgroundColor.
		// set_backgroundColor(argument);
		// result = true;
		// return result;
		virtual bool setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;
		
		// Base classes must implement this method. This is the minimum
		// functionality that you should perform:
		//
		// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
		// bool result = false;
		// const std::string top = static_cast<std::string>(argument);
		// Set the native view's position.
		// set_top(argument);
		// result = true;
		// return result;
		virtual bool setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;
		
		// Base classes must implement this method. This is the minimum
		// functionality that you should perform:
		//
		// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
		// bool result = false;
		// const std::string left = static_cast<std::string>(argument);
		// Set the native view's position.
		// set_left(argument);
		// result = true;
		// return result;
		virtual bool setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;
		
		// Base classes must implement this method. This is the minimum
		// functionality that you should perform:
		//
		// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
		// bool result = false;
		// const std::string bottom = static_cast<std::string>(argument);
		// Set the native view's position.
		// set_bottom(argument);
		// result = true;
		// return result;
		virtual bool setBottomArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;
		
		// Base classes must implement this method. This is the minimum
		// functionality that you should perform:
		//
		// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
		// bool result = false;
		// const std::string right = static_cast<std::string>(argument);
		// Set the native view's position.
		// set_right(argument);
		// result = true;
		// return result;
		virtual bool setRightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;
		
		// Base classes must implement this method. This is the minimum
		// functionality that you should perform:
		//
		// TITANIUM_ASSERT(argument.IsObject();
		// bool result = false;
		// JSObject center = argument;
		// TITANIUM_ASSERT(center.HasProperty("x");
		// TITANIUM_ASSERT(center.HasProperty("y");
		// const std::string x = static_cast<std::string>(center.GetProperty("x"));
		// const std::string y = static_cast<std::string>(center.GetProperty("y"));
		// Set the native view's position.
		// set_center(center);
		// result = true;
		// return result;
		virtual bool setCenterArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;
		
		// Base classes must implement this method. This is the minimum
		// functionality that you should perform:
		//
		// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
		// bool result = false;
		// const std::string width = static_cast<std::string>(argument);
		// Set the native view's position.
		// set_width(argument);
		// result = true;
		// return result;
		virtual bool setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;
		
		// Base classes must implement this method. This is the minimum
		// functionality that you should perform:
		//
		// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
		// bool result = false;
		// const std::string height = static_cast<std::string>(argument);
		// Set the native view's position.
		// set_height(argument);
		// result = true;
		// return result;
		virtual bool setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;

	// Base classes must implement this method. This is the minimum
	// functionality that you should perform:
	//
	// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
	// bool result = false;
	// const std::string height = static_cast<std::string>(argument);
	// Set the native view's layout type.
	// set_layout(argument);
	// result = true;
	// return result;
	virtual bool setLayoutArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;

	protected:
		
		virtual NativeChildrenList_t get_native_children() const TITANIUM_NOEXCEPT final;
		
	private:
		
		JSArray	children__;
		JSValue	backgroundColor__;
		JSValue	top__;
		JSValue	left__;
		JSValue	bottom__;
		JSValue	right__;
		JSObject center__;
		JSValue	width__;
		JSValue	height__;
	JSValue	layout__;
		
	};
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_VIEW_HPP_
