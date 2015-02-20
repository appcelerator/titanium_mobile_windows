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

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		class View;

		using NativeChildPtr_t = std::shared_ptr<Titanium::UI::View>;
		using NativeChildrenList_t = std::vector<NativeChildPtr_t>;

		/*!
		  @class

		  @discussion This is the Titanium UI View.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.View
		*/
		class TITANIUMKIT_EXPORT View : public Module, public JSExport<View>
		{
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

			  @abstract animate( animation, callback ) : void

			  @discussion Animates this view.

			  The Animation object or dictionary passed to this method defines the end state for the animation, the duration of the animation, and other properties.

			  Note that if you use animate to move a view, the view's actual position is changed, but its layout properties, such as top, left, center and so on are not changed--these reflect the original values set by the user, not the actual position of the view.

			  The rect property can be used to determine the actual size and position of the view. Note that on Mobile Web and Tizen, the rect property is not updated after animation. This is a known issue TIMOB-8930.

			  @param animation : Titanium.UI.Animation/Dictionary<Titanium.UI.Animation>
			  Either a dictionary of animation properties or an Animation object.

			  @param callback : Callback<Object>
			  Function to be invoked upon completion of the animation.

			  @result void
			*/
			virtual void animate(const JSObject& animation, JSObject& callback) TITANIUM_NOEXCEPT;

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

			/*!
			  @method

			  @abstract backgroundColor : String

			  @discussion Background color of the view, as a color name or hex triplet.

			  For information about color values, see the "Colors" section of Titanium.UI.

			  Default: Transparent
			*/
			virtual std::string get_backgroundColor() const TITANIUM_NOEXCEPT final;
			virtual void set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract borderColor : String

			  @discussion Border color of the view, as a color name or hex triplet.

			  For information about color values, see the "Colors" section of Titanium.UI.

			  Default: Same as the normal background color of this view (Android, Mobile Web, Tizen), black (iOS).
			*/
			virtual std::string get_borderColor() const TITANIUM_NOEXCEPT final;
			virtual void set_borderColor(const std::string& borderColor) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract borderRadius : Number

			  @discussion Radius for the rounded corners of the view's border.

			  Each corner is rounded using an arc of a circle.

			  Default: 0
			*/
			virtual uint32_t get_borderRadius() const TITANIUM_NOEXCEPT final;
			virtual void set_borderRadius(const uint32_t& borderRadius) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract borderWidth : Number

			  @discussion Border width of the view.

			  Default: 0
			*/
			virtual uint32_t get_borderWidth() const TITANIUM_NOEXCEPT final;
			virtual void set_borderWidth(const uint32_t& borderWidth) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract opacity : Number

			  @discussion Opacity of this view, from 0.0 (transparent) to 1.0 (opaque).

			  Default: 1.0 (opaque)
			*/
			virtual double get_opacity() const TITANIUM_NOEXCEPT final;
			virtual void set_opacity(const double& opacity) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract tintColor : String

			  @discussion The view's tintColor. This property is applicable on iOS 7 and greater.

			  This property is a direct correspondant of the tintColor property of UIView on iOS. If no value is specified, the tintColor of the View is inherited from its superview.
			*/
			virtual std::string get_tintColor() const TITANIUM_NOEXCEPT final;
			virtual void set_tintColor(const std::string& tintColor) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract touchEnabled : Boolean

			  @discussion Determines whether view should receive touch events.

			  If false, will forward the events to peers.

			  Default: true
			*/
			virtual bool get_touchEnabled() const TITANIUM_NOEXCEPT final;
			virtual void set_touchEnabled(const bool& touchEnabled) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract visible : Boolean

			  @discussion Determines whether the view is visible.

			  Default: true
			*/
			virtual bool get_visible() const TITANIUM_NOEXCEPT final;
			virtual void set_visible(const bool& visible) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract top : Number/String

			  @discussion The view's top position.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual std::string get_top() const TITANIUM_NOEXCEPT final;
			virtual void set_top(const std::string& top) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract left : Number/String

			  @discussion View's left position, in platform-specific units.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual std::string get_left() const TITANIUM_NOEXCEPT final;
			virtual void set_left(const std::string& left) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract bottom : Number/String

			  @discussion View's bottom position, in platform-specific units.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual std::string get_bottom() const TITANIUM_NOEXCEPT final;
			virtual void set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract right : Number/String

			  @discussion View's right position, in platform-specific units.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual std::string get_right() const TITANIUM_NOEXCEPT final;
			virtual void set_right(const std::string& right) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract center : Point

			  @discussion View's center position, in the parent view's coordinates.

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual JSObject get_center() const TITANIUM_NOEXCEPT final;
			virtual void set_center(const JSObject& center) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract width : Number/String

			  @discussion View's width, in platform-specific units.

			  Defaults to: If undefined, defaults to either Titanium.UI.FILL or Titanium.UI.SIZE depending on the view. See "View Types and Default Layout Behavior" in Transitioning to the New UI Layout System.

			  Can be either a float value or a dimension string (for example, '50%' or '40dp'). Can also be one of the following special values:

			  Titanium.UI.SIZE. The view should size itself to fit its contents.
			  Titanium.UI.FILL. The view should size itself to fill its parent.
			  'auto'. Represents the default sizing behavior for a given type of view. The use of 'auto' is deprecated, and should be replaced with the SIZE or FILL constants if it is necessary to set the view's behavior explicitly.
			  On Mobile Web and Tizen, 'auto' always selects SIZE behavior.

			  This is an input property for specifying the view's width dimension. To determine the view's size once rendered, use the rect or size properties.

			  This property can be assigned the following constants:

			  Titanium.UI.FILL
			  Titanium.UI.SIZE
			*/
			virtual std::string get_width() const TITANIUM_NOEXCEPT final;
			virtual void set_width(const std::string& width) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract height : Number/String

			  @discussion View height, in platform-specific units.

			  Defaults to: If undefined, defaults to either Titanium.UI.FILL or Titanium.UI.SIZE depending on the view. See "View Types and Default Layout Behavior" in Transitioning to the New UI Layout System.

			  Can be either a float value or a dimension string (for example, '50%' or '40dp'). Can also be one of the following special values:

			  Titanium.UI.SIZE. The view should size itself to fit its contents.
			  Titanium.UI.FILL. The view should size itself to fill its parent.
			  'auto'. Represents the default sizing behavior for a given type of view. The use of 'auto' is deprecated, and should be replaced with the SIZE or FILL constants if it is necessary to set the view's behavior explicitly.

			  On Mobile Web and Tizen, 'auto' always selects SIZE behavior.
			  This is an input property for specifying the view's height dimension. To determine the view's size once rendered, use the rect or size properties.

			  This property can be assigned the following constants:

			  Titanium.UI.FILL
			  Titanium.UI.SIZE
			*/
			virtual std::string get_height() const TITANIUM_NOEXCEPT final;
			virtual void set_height(const std::string& height) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract layout : String

			  @discussion Specifies how the view positions its children. One of: 'composite', 'vertical', or 'horizontal'.
			*/
			virtual std::string get_layout() const TITANIUM_NOEXCEPT final;
			virtual void set_layout(const std::string& height) TITANIUM_NOEXCEPT;

			View(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~View() TITANIUM_NOEXCEPT;  //= default;
			View(const View&) = default;
			View& operator=(const View&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			View(View&&) = default;
			View& operator=(View&&) = default;
#endif

			// TODO: The following functions can automatically be generated
			// from the YAML API docs.
			static void JSExportInitialize();

			virtual JSValue js_add(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_animate(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_hide(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_show(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_backgroundColor() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_backgroundColor(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_borderColor() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_borderColor(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_borderRadius() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_borderRadius(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_borderWidth() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_borderWidth(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_opacity() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_opacity(const JSValue& argument) TITANIUM_NOEXCEPT final;
			
			virtual JSValue js_get_tintColor() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_tintColor(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_touchEnabled() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_touchEnabled(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_visible() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_visible(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_top() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_top(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_left() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_left(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_bottom() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_bottom(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_right() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_right(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual bool js_set_center(const JSValue& argument) TITANIUM_NOEXCEPT final;
			
			virtual JSValue js_get_width() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_width(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_height() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_height(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_layout() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_layout(const JSValue& argument) TITANIUM_NOEXCEPT final;

		protected:
			virtual NativeChildrenList_t get_native_children() const TITANIUM_NOEXCEPT final;

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			JSArray children__;
			std::string backgroundColor__;
			std::string borderColor__;
			uint32_t borderRadius__;
			uint32_t borderWidth__;
			double opacity__;
			std::string top__;
			std::string left__;
			std::string bottom__;
			std::string right__;
			JSObject center__;
			std::string width__;
			std::string height__;
			std::string layout__;
			std::string tintColor__;
			bool touchEnabled__;
			bool visible__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_VIEW_HPP_
