/**
 * WindowsViewLayoutDelegate
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_WINDOWSVIEWLAYOUTDELEGATE_HPP_
#define _TITANIUMWINDOWS_UI_WINDOWSVIEWLAYOUTDELEGATE_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/ViewLayoutDelegate.hpp"
#include "LayoutEngine/LayoutEngine.hpp"
#include "Titanium/UI/View.hpp"

namespace Titanium
{
	class Blob;
}

namespace TitaniumWindows
{
	using namespace HAL;

	class TITANIUMWINDOWS_UI_EXPORT Platform_Object : public Titanium::Module, public JSExport<Platform_Object>
	{
	public:
		Platform_Object(const JSContext& ctx) TITANIUM_NOEXCEPT
			: Titanium::Module(ctx, "Platform.Object")
		{
		}

		virtual ~Platform_Object() = default;
		Platform_Object(const Platform_Object&) = default;
		Platform_Object& operator=(const Platform_Object&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Platform_Object(Platform_Object&&) = default;
		Platform_Object& operator=(Platform_Object&&) = default;
#endif
		::Platform::Object^ get_native_object() const TITANIUM_NOEXCEPT
		{
			return native_object__;
		}

		void set_native_object(::Platform::Object^ obj)
		{
			native_object__ = obj;
		}

	protected:
		::Platform::Object^ native_object__{ nullptr };
	};

	namespace UI
	{
		using namespace HAL;

		class TITANIUMWINDOWS_UI_EXPORT FrameworkElementWrapper : public Titanium::UI::View, public JSExport<FrameworkElementWrapper>
		{
		public:
			FrameworkElementWrapper(const JSContext& ctx) TITANIUM_NOEXCEPT;
			virtual ~FrameworkElementWrapper() = default;
			FrameworkElementWrapper(const FrameworkElementWrapper&) = default;
			FrameworkElementWrapper& operator=(const FrameworkElementWrapper&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			FrameworkElementWrapper(FrameworkElementWrapper&&) = default;
			FrameworkElementWrapper& operator=(FrameworkElementWrapper&&) = default;
#endif
			Windows::UI::Xaml::FrameworkElement^ getComponent() TITANIUM_NOEXCEPT
			{
				return element__;
			}

			void setComponent(Windows::UI::Xaml::FrameworkElement^ element) TITANIUM_NOEXCEPT;

			static void JSExportInitialize();

		protected:
			Windows::UI::Xaml::FrameworkElement^ element__{ nullptr };
		};

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
			virtual void add(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT override;
			virtual void remove(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT override;
			virtual void insertAt(const Titanium::UI::ViewInsertOrReplaceParams& params) TITANIUM_NOEXCEPT;
			virtual void replaceAt(const Titanium::UI::ViewInsertOrReplaceParams& params) TITANIUM_NOEXCEPT;

			virtual void animate(const std::shared_ptr<Titanium::UI::Animation>& animation, JSObject& callback, const JSObject& this_object) TITANIUM_NOEXCEPT override;

			virtual void ToImage(Windows::UI::Xaml::FrameworkElement^ component, JSObject& callback, const JSObject& this_object);
			virtual std::shared_ptr<Titanium::Blob> toImage(JSObject& callback, const bool& honorScaleFactor, const JSObject& this_object) TITANIUM_NOEXCEPT override;

			/*!
			@method

			@abstract backgroundImage : String

			@discussion Background image for the view, specified as a local file path or URL.

			Default: Default behavior when `backgroundImage` is unspecified depends on the type of view and the platform.

			For generic views, no image is used. For most controls (buttons, text fields, and so on), platform-specific default images are used.
			*/
			virtual void set_backgroundImage(const std::string& backgroundImage) TITANIUM_NOEXCEPT override;
			virtual void set_backgroundImage(const std::shared_ptr<Titanium::Blob>& backgroundImage) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract backgroundColor : String

			  @discussion Background color of the view, as a color name or hex triplet.

			  For information about color values, see the "Colors" section of Titanium.UI.

			  Default: Transparent
			*/
			virtual void set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract borderColor : String

			  @discussion Border color of the view, as a color name or hex triplet.

			  For information about color values, see the "Colors" section of Titanium.UI.

			  Default: Same as the normal background color of this view (Android, Mobile Web, Tizen), black (iOS).
			*/
			virtual void set_borderColor(const std::string& borderColor) TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract borderWidth : Number

			  @discussion Border width of the view.

			  Default: 0
			*/
			virtual void set_borderWidth(const uint32_t& borderWidth) TITANIUM_NOEXCEPT override;

			/*!
			@method

			@abstract borderRadius : Number

			@discussion Radius for the rounded corners of the view's border.

			Each corner is rounded using an arc of a circle.

			Default: 0
			*/
			virtual void set_borderRadius(const double& borderRadius) TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract bottom : Number/String

			  @discussion View's bottom position, in platform-specific units.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual void set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract center : Point

			  @discussion View's center position, in the parent view's coordinates.

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual void set_center(const Titanium::UI::Point& center) TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract enabled : Boolean

			  @discussion Determines whether the view is enabled.

			  Default: true
			*/
			virtual void set_touchEnabled(const bool& enabled) TITANIUM_NOEXCEPT override;

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
			virtual void set_height(const std::string& height) TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract layout : String

			  @discussion Specifies how the view positions its children. One of: 'composite', 'vertical', or 'horizontal'.
			*/
			virtual void set_layout(const std::string& layout) TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract left : Number/String

			  @discussion View's left position, in platform-specific units.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual void set_left(const std::string& left) TITANIUM_NOEXCEPT override;

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
			virtual void set_minHeight(const std::string& height) TITANIUM_NOEXCEPT override;

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
			virtual void set_minWidth(const std::string& width) TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract opacity : Number

			  @discussion Opacity of this view, from 0.0 (transparent) to 1.0 (opaque).

			  Default: 1.0 (opaque)
			*/
			virtual void set_opacity(const double& opacity) TITANIUM_NOEXCEPT override;

			virtual Titanium::UI::Dimension get_rect() const TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract right : Number/String

			  @discussion View's right position, in platform-specific units.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual void set_right(const std::string& right) TITANIUM_NOEXCEPT override;

			virtual Titanium::UI::Dimension get_size() const TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract top : Number/String

			  @discussion The view's top position.

			  This position is relative to the view's parent. Exact interpretation depends on the parent view's layout property. Can be either a float value or a dimension string (for example, '50%' or '10px').

			  This is an input property for specifying where the view should be positioned, and does not represent the view's calculated position.
			*/
			virtual void set_top(const std::string& top) TITANIUM_NOEXCEPT override;

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
			virtual void set_width(const std::string& width) TITANIUM_NOEXCEPT override;

			/*!
			@method

			@abstract zIndex : Number

			@discussion Z-index stack order position, relative to other sibling views.
			A view does not have a default z-index value, meaning that it is undefined by default. When this property is explicitly set,
			regardless of its value, it causes the view to be positioned in front of any sibling that has an undefined z-index.
			*/
			virtual void set_zIndex(const int32_t& zIndex) TITANIUM_NOEXCEPT override;

			/*!
			  @method

			  @abstract visible : Boolean

			  @discussion Determines whether the view is visible
			*/
			virtual void set_visible(const bool& visible) TITANIUM_NOEXCEPT override;

			/*!
			  @property
			  @abstract backgroundDisabledImage
			  @discussion Disabled background image for the view, specified as a local file path or URL.
			*/
			virtual void set_backgroundDisabledImage(const std::string& backgroundDisabledImage) TITANIUM_NOEXCEPT override;

			/*!
			@property
			@abstract backgroundDisabledColor
			@discussion Disabled background color of the view, as a color name or hex triplet.
			*/
			virtual void set_backgroundDisabledColor(const std::string& backgroundDisabledColor) TITANIUM_NOEXCEPT override;

			/*!
			  @property
			  @abstract backgroundFocusedColor
			  @discussion Focused background color of the view, as a color name or hex triplet.
			*/
			virtual void set_backgroundFocusedColor(const std::string& backgroundFocusedColor) TITANIUM_NOEXCEPT override;

			/*!
			  @property
			  @abstract backgroundFocusedImage
			  @discussion Focused background image for the view, specified as a local file path or URL.
			*/
			virtual void set_backgroundFocusedImage(const std::string& backgroundFocusedImage) TITANIUM_NOEXCEPT override;

			/*!
			@property
			@abstract backgroundSelectedColor
			@discussion Selected background color of the view, as a color name or hex triplet.
			*/
			virtual void set_backgroundSelectedColor(const std::string& backgroundSelectedColor) TITANIUM_NOEXCEPT override;

			/*!
			@property
			@abstract backgroundSelectedImage
			@discussion Selected background image url for the view, specified as a local file path or URL.
			*/
			virtual void set_backgroundSelectedImage(const std::string& backgroundSelectedImage) TITANIUM_NOEXCEPT override;

			/*!
			  @property
			  @abstract backgroundGradient
			  @discussion A background gradient for the view.
			*/
			virtual void set_backgroundGradient(const Titanium::UI::Gradient& backgroundGradient) TITANIUM_NOEXCEPT override;

			WindowsViewLayoutDelegate() TITANIUM_NOEXCEPT;
			virtual ~WindowsViewLayoutDelegate();

			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
			virtual void blur()  override;
			virtual void focus() override;

			// This filter out parent events which is going to be handled by children.
			// When you override enableEvent, make sure to call this before parent::enableEvent
			virtual void filterEvents(const std::vector<std::string>& events) TITANIUM_NOEXCEPT
			{
				filtered_events__.insert(filtered_events__.end(), events.begin(), events.end());
			}

			//
			// Windows-specific layout functions
			//
			virtual void onComponentLoaded(const Titanium::LayoutEngine::Rect&);
			virtual void onComponentSizeChange(const Titanium::LayoutEngine::Rect&);
			virtual void onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name);
			virtual void updateBackgroundGradient();

			virtual void setLayoutProperty(const Titanium::LayoutEngine::ValueName&, const std::string&, const std::shared_ptr<Titanium::LayoutEngine::LayoutProperties> = nullptr);

			virtual void setComponent(Windows::UI::Xaml::FrameworkElement^ component, Windows::UI::Xaml::Controls::Control^ underlying_control = nullptr, const bool& enableBorder = true);
			virtual void setComponent(Windows::UI::Xaml::FrameworkElement^ component, Windows::UI::Xaml::Controls::Control^ underlying_control, Windows::UI::Xaml::Controls::Border^ border);

			virtual Windows::UI::Xaml::FrameworkElement^ getEventComponent() const TITANIUM_NOEXCEPT
			{
				if (underlying_control__) {
					return underlying_control__;
				}
				return component__;
			}

			virtual Windows::UI::Xaml::FrameworkElement^ getComponent() const TITANIUM_NOEXCEPT
			{
				if (border__) {
					return border__;
				}
				return component__;
			}

			// We want to detect if component__ is a container (like Grid) and there's a underlying control.
			// We'll use this to set correct background and border.
			void setUnderlyingControl(Windows::UI::Xaml::Controls::Control^ control)
			{
				underlying_control__ = control;
			}

			//
			// Check if this component uses its own width
			//
			virtual bool shouldUseOwnWidth() const TITANIUM_NOEXCEPT;

			//
			// Check if this component uses its own height
			//
			virtual bool shouldUseOwnHeight() const TITANIUM_NOEXCEPT;

			virtual Titanium::LayoutEngine::Node* getLayoutNode() const TITANIUM_NOEXCEPT
			{
				return layout_node__;
			}

			virtual bool isLoaded() const TITANIUM_NOEXCEPT
			{
				return is_loaded__;
			}

			virtual void useOwnSize() TITANIUM_NOEXCEPT
			{
				use_own_size__ = true;
			}

			virtual void requestLayout(const bool& fire_event = false);

			// compute its fixed size when either width or height (not both) is Ti.UI.SIZE
			virtual Titanium::LayoutEngine::Rect computeRelativeSize(const double& x, const double& y,  const double& baseWidth, const double& baseHeight);

			static Windows::UI::Color ColorForName(const std::string& colorName);
			static Windows::UI::Color ColorForHexCode(const std::string& hexCode);

			virtual void setDefaultBackground();
			virtual void updateSelectedBackground();
			virtual void updateBackground(Windows::UI::Xaml::Media::Brush^);
			virtual void updateDisabledBackground();
			Windows::UI::Xaml::Media::Brush^ getBackground();

			virtual std::shared_ptr<Titanium::UI::View> rescueGetView(const JSObject& view) TITANIUM_NOEXCEPT override;
			virtual void fireSimplePositionEvent(const std::string& event_name, Windows::UI::Xaml::FrameworkElement^ sender, Windows::Foundation::Point position);
			virtual void firePostLayoutEvent();

			static Windows::UI::Xaml::Media::ImageBrush^ CreateImageBrushFromPath(const std::string& path);
			static Windows::UI::Xaml::Media::ImageBrush^ CreateImageBrushFromBitmapImage(Windows::UI::Xaml::Media::Imaging::BitmapImage^ image);
			static Windows::UI::Xaml::Media::ImageBrush^ CreateImageBrushFromBlob(const std::shared_ptr<Titanium::Blob>& blob);

#pragma warning(push)
#pragma warning(disable : 4251)
			std::vector<std::string> filtered_events__;
#pragma warning(pop)

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			Windows::UI::Xaml::Controls::Border^ border__    { nullptr };
			Windows::UI::Xaml::FrameworkElement^ component__ { nullptr };
			Windows::UI::Xaml::Controls::Control^ underlying_control__ { nullptr };

			Titanium::LayoutEngine::Node* layout_node__ { nullptr };

			bool postlayout_listening__{ false };

			Windows::Foundation::EventRegistrationToken size_change_event__;
			Windows::Foundation::EventRegistrationToken loaded_event__;
			Windows::Foundation::EventRegistrationToken update_background_event__;
			Windows::Foundation::EventRegistrationToken reset_background_event__;
			Windows::Foundation::EventRegistrationToken enabled_changed_event__;
			Windows::Foundation::EventRegistrationToken selected_event__;

			// Titanium event handlers
			Windows::Foundation::EventRegistrationToken click_event__;
			Windows::Foundation::EventRegistrationToken dblclick_event__;
			Windows::Foundation::EventRegistrationToken blur_event__;
			Windows::Foundation::EventRegistrationToken focus_event__;
			Windows::Foundation::EventRegistrationToken touchstart_event__;
			Windows::Foundation::EventRegistrationToken touchend_event__;
			Windows::Foundation::EventRegistrationToken touchcancel_event__;
			Windows::Foundation::EventRegistrationToken touchcancel_lost_event__;
			Windows::Foundation::EventRegistrationToken touchmove_event__;
			Windows::Foundation::EventRegistrationToken singletap_event__;
			Windows::Foundation::EventRegistrationToken doubletap_event__;
			Windows::Foundation::EventRegistrationToken longpress_event__;
			Windows::Foundation::EventRegistrationToken keypressed_event__;

			bool is_width_size__{false};
			bool is_height_size__{false};
			bool is_panel__{false};
			bool is_grid__{false};
			bool is_border__{false};
			bool is_control__{false};
			bool is_scrollview__ { false };
			bool is_button__{ false };
			bool is_loaded__{false};
			bool use_own_size__ { false };
			bool is_transforming_layout__ { false }; // true when animate() is transforming layout

			Titanium::LayoutEngine::Rect oldRect__;

			struct animate_call__ {
				std::shared_ptr<Titanium::UI::Animation> animation;
				JSObject callback;
				JSObject this_object;
			};
			std::vector<animate_call__> animate_queue__;

			Windows::UI::Xaml::Media::ImageBrush^ backgroundImageBrush__{ nullptr };
			Windows::UI::Xaml::Media::ImageBrush^ backgroundDisabledImageBrush__{ nullptr };
			Windows::UI::Xaml::Media::ImageBrush^ backgroundFocusedImageBrush__{ nullptr };
			Windows::UI::Xaml::Media::ImageBrush^ backgroundSelectedImageBrush__{ nullptr };

			Windows::UI::Xaml::Media::SolidColorBrush^ backgroundColorBrush__{ nullptr };
			Windows::UI::Xaml::Media::SolidColorBrush^ backgroundDisabledColorBrush__{ nullptr };
			Windows::UI::Xaml::Media::SolidColorBrush^ backgroundFocusedColorBrush__{ nullptr };
			Windows::UI::Xaml::Media::SolidColorBrush^ backgroundSelectedColorBrush__{ nullptr };
			Windows::UI::Xaml::Media::SolidColorBrush^ borderColorBrush__{ nullptr };
			Windows::UI::Xaml::Media::Brush^ previousBackgroundBrush__{ nullptr };

			Windows::UI::Xaml::Media::LinearGradientBrush^ backgroundLinearGradientBrush__{ nullptr };
#pragma warning(pop)

		};

	} // namespace UI
}  // namespace Titanium


#endif  // _TITANIUMWINDOWS_UI_WINDOWSVIEWLAYOUTDELEGATE_HPP_
