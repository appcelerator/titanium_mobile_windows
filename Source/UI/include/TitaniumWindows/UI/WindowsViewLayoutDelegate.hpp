/**
 * WindowsViewLayoutDelegate
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_WINDOWSVIEWLAYOUTDELEGATE_HPP_
#define _TITANIUMWINDOWS_UI_WINDOWSVIEWLAYOUTDELEGATE_HPP_

#include "Titanium/UI/ViewLayoutDelegate.hpp"
#include "Titanium/UI/Constants.hpp"
#include "Titanium/UI/Point.hpp"
#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "LayoutEngine/LayoutEngine.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		class TITANIUMWINDOWS_UI_EXPORT WindowsViewLayoutDelegate : public Titanium::UI::ViewLayoutDelegate
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
			virtual void add(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT;

			virtual void animate(const JSObject& animation, JSObject& callback, const JSObject& this_object) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract hide() : void

			  @discussion Hides the view and it's chldren in the view's hierarchy.

			  @param 

			  @result void
			*/
			virtual void hide() TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract show() : void

			  @discussion Causes the view and the view's hierarchy to be displayed. 

			  @param 

			  @result void
			*/
			virtual void show() TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract backgroundColor : String

			  @discussion Background color of the view, as a color name or hex triplet.

			  For information about color values, see the "Colors" section of Titanium.UI.

			  Default: Transparent
			*/
			virtual void set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract borderColor : String

			  @discussion Border color of the view, as a color name or hex triplet.

			  For information about color values, see the "Colors" section of Titanium.UI.

			  Default: Same as the normal background color of this view (Android, Mobile Web, Tizen), black (iOS).
			*/
			virtual void set_borderColor(const std::string& borderColor) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract borderRadius : Number

			  @discussion Radius for the rounded corners of the view's border.

			  Each corner is rounded using an arc of a circle.

			  Default: 0
			*/
			virtual void set_borderRadius(const uint32_t& borderRadius) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract borderWidth : Number

			  @discussion Border width of the view.

			  Default: 0
			*/
			virtual void set_borderWidth(const uint32_t& borderWidth) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract bottom : Number/String

			  @discussion View's bottom position, in platform-specific units.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual void set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract center : Point

			  @discussion View's center position, in the parent view's coordinates.

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual void set_center(const Titanium::UI::Point& center) TITANIUM_NOEXCEPT;

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
			virtual void set_height(const std::string& height) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract layout : String

			  @discussion Specifies how the view positions its children. One of: 'composite', 'vertical', or 'horizontal'.
			*/
			virtual void set_layout(const std::string& layout) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract left : Number/String

			  @discussion View's left position, in platform-specific units.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual void set_left(const std::string& left) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract height : Number/String

			  @discussion View minimum height, in platform-specific units.

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
			virtual void set_minHeight(const std::string& height) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract minWidth : Number/String

			  @discussion View's minimum width, in platform-specific units.

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
			virtual void set_minWidth(const std::string& width) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract opacity : Number

			  @discussion Opacity of this view, from 0.0 (transparent) to 1.0 (opaque).

			  Default: 1.0 (opaque)
			*/
			virtual void set_opacity(const double& opacity) TITANIUM_NOEXCEPT;

			virtual Titanium::UI::Dimension get_rect() const TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract right : Number/String

			  @discussion View's right position, in platform-specific units.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual void set_right(const std::string& right) TITANIUM_NOEXCEPT;

			virtual Titanium::UI::Dimension get_size() const TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract tintColor : String

			  @discussion The view's tintColor. This property is applicable on iOS 7 and greater.

			  This property is a direct correspondant of the tintColor property of UIView on iOS. If no value is specified, the tintColor of the View is inherited from its superview.
			*/
			virtual void set_tintColor(const std::string& tintColor) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract top : Number/String

			  @discussion The view's top position.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual void set_top(const std::string& top) TITANIUM_NOEXCEPT;
			
			/*!
			  @method

			  @abstract touchEnabled : Boolean

			  @discussion Determines whether view should receive touch events.

			  If false, will forward the events to peers.

			  Default: true
			*/
			virtual void set_touchEnabled(const bool& touchEnabled) TITANIUM_NOEXCEPT;

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
			virtual void set_width(const std::string& width) TITANIUM_NOEXCEPT;

			WindowsViewLayoutDelegate() TITANIUM_NOEXCEPT;
			virtual ~WindowsViewLayoutDelegate() = default;

			virtual void postInitialize() TITANIUM_NOEXCEPT override;
			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

			//
			// Windows-specific layout functions
			//
			virtual void onComponentLoaded(const Titanium::LayoutEngine::Rect&);
			virtual void onComponentSizeChange(const Titanium::LayoutEngine::Rect&);
			virtual void onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name);

			virtual void setLayoutProperty(const Titanium::LayoutEngine::ValueName&, const std::string&);
			virtual void setComponent(Windows::UI::Xaml::FrameworkElement^ component);
			virtual Windows::UI::Xaml::FrameworkElement^ getComponent() const TITANIUM_NOEXCEPT
			{
				return component__;
			}

			virtual Titanium::LayoutEngine::Node* getLayoutNode() const TITANIUM_NOEXCEPT
			{
				return layout_node__;
			}	

			virtual bool isLoaded() const TITANIUM_NOEXCEPT
			{
				return is_loaded__;
			}

			virtual void requestLayout(bool fire_event = false);

			// compute its fixed size when either width or height (not both) is Ti.UI.SIZE
			virtual Titanium::LayoutEngine::Rect computeRelativeSize(const double& x, const double& y,  const double& baseWidth, const double& baseHeight);
 
			static Windows::UI::Color ColorForName(const std::string& colorName);
			static Windows::UI::Color ColorForHexCode(const std::string& hexCode);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			Windows::UI::Xaml::FrameworkElement^ component__ { nullptr };

			Titanium::LayoutEngine::Node* layout_node__;

			bool postlayout_listening__{ false };
			Windows::Foundation::EventRegistrationToken size_change_event__;
			Windows::Foundation::EventRegistrationToken loaded_event__;
			Windows::Foundation::EventRegistrationToken focus_event__;

			bool is_width_size__{false};
			bool is_height_size__{false};
			bool is_panel__{false};
			bool is_control__{false};
			bool is_loaded__{false};

			Titanium::LayoutEngine::Rect oldRect__;
#pragma warning(pop)

		};

	} // namespace UI
}  // namespace Titanium


#endif  // _TITANIUMWINDOWS_UI_WINDOWSVIEWLAYOUTDELEGATE_HPP_
