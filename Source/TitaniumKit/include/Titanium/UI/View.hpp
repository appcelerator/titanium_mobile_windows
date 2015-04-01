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
#include "Titanium/UI/Animation.hpp"
#include "Titanium/UI/ViewLayoutDelegate.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		class View;

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
			virtual void animate(JSObject& animation, JSObject& callback) TITANIUM_NOEXCEPT;

			View(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~View() TITANIUM_NOEXCEPT;  //= default;
			View(const View&) = default;
			View& operator=(const View&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			View(View&&) = default;
			View& operator=(View&&) = default;
#endif

			static void JSExportInitialize();

			TITANIUM_MODULE_FUNCTION_DEF(add);
			TITANIUM_MODULE_FUNCTION_DEF(animate);
			TITANIUM_MODULE_FUNCTION_DEF(hide);
			TITANIUM_MODULE_FUNCTION_DEF(show);
			
			TITANIUM_MODULE_PROPERTY_DEF(backgroundColor);
			TITANIUM_MODULE_PROPERTY_DEF(borderColor);
			TITANIUM_MODULE_PROPERTY_DEF(borderRadius);
			TITANIUM_MODULE_PROPERTY_DEF(borderWidth);
			TITANIUM_MODULE_PROPERTY_DEF(bottom);
			TITANIUM_MODULE_PROPERTY_DEF(center);
			TITANIUM_MODULE_PROPERTY_READONLY_DEF(children);
			TITANIUM_MODULE_PROPERTY_DEF(height);
			TITANIUM_MODULE_PROPERTY_DEF(layout);
			TITANIUM_MODULE_PROPERTY_DEF(left);
			TITANIUM_MODULE_PROPERTY_DEF(opacity);
			TITANIUM_MODULE_PROPERTY_READONLY_DEF(rect);
			TITANIUM_MODULE_PROPERTY_DEF(right);
			TITANIUM_MODULE_PROPERTY_READONLY_DEF(size);
			TITANIUM_MODULE_PROPERTY_DEF(tintColor);
			TITANIUM_MODULE_PROPERTY_DEF(touchEnabled);
			TITANIUM_MODULE_PROPERTY_DEF(visible);
			TITANIUM_MODULE_PROPERTY_DEF(top);
			TITANIUM_MODULE_PROPERTY_DEF(width);

			virtual void postInitialize(JSObject& this_object) override;
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;
			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;

			template<typename T>
			std::shared_ptr<T> getViewLayoutDelegate()
			{
				return std::dynamic_pointer_cast<T>(layoutDelegate__);
			}

		protected:
			template<typename T, typename U, typename... Us>
			void setLayoutDelegate(Us&&... constructor_arguments) TITANIUM_NOEXCEPT
			{
				layoutDelegate__ = std::make_shared<T>(std::forward<Us>(constructor_arguments)...);
				layoutEventDelegate__ = std::make_shared<U>(this);
				layoutDelegate__->setEventDelegate(layoutEventDelegate__);
				layoutDelegate__->postInitialize();
			}
			template<typename T, typename... Us>
			void setLayoutDelegate(Us&&... constructor_arguments) TITANIUM_NOEXCEPT
			{
				setLayoutDelegate<T, ViewLayoutEventDelegate>(std::forward<Us>(constructor_arguments)...);
			}
			void setLayoutDelegate() TITANIUM_NOEXCEPT
			{
				setLayoutDelegate<ViewLayoutDelegate, ViewLayoutEventDelegate>();
			}

#pragma warning(push)
#pragma warning(disable : 4251)
			std::shared_ptr<ViewLayoutEventDelegate> layoutEventDelegate__;
			std::shared_ptr<ViewLayoutDelegate> layoutDelegate__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_VIEW_HPP_
