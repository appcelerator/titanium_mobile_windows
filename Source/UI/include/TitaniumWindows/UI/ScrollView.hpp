/**
* Titanium.UI.View for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_SCROLLVIEW_HPP_
#define _TITANIUMWINDOWS_UI_SCROLLVIEW_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/ScrollView.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		class ScrollView;

		class TITANIUMWINDOWS_UI_EXPORT ScrollViewLayoutDelegate : public WindowsViewLayoutDelegate
		{
		public:
			ScrollViewLayoutDelegate(ScrollView*, const JSObject&) TITANIUM_NOEXCEPT;
			virtual ~ScrollViewLayoutDelegate() = default;

			virtual void add(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT override;
			virtual void remove(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT override;
			virtual void removeAllChildren() TITANIUM_NOEXCEPT override;
			virtual void set_layout(const std::string& layout) TITANIUM_NOEXCEPT override;
			virtual void requestLayout(const bool& fire_event = false) override;

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			static JSFunction CreateClickCallback(const JSObject& contentView) TITANIUM_NOEXCEPT;
			ScrollView* scrollview__;
			JSObject contentView__;
			JSFunction clickCallback__;
#pragma warning(pop)
		};

		/*!
		  @class ScrollView
		  @ingroup Titanium.UI.ScrollView

		  @discussion This is the Titanium.UI.ScrollView implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ScrollView final : public Titanium::UI::ScrollView, public JSExport<ScrollView>
		{
		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(canCancelEvents);
			TITANIUM_PROPERTY_UNIMPLEMENTED(disableBounce);
			TITANIUM_PROPERTY_UNIMPLEMENTED(horizontalBounce);
			TITANIUM_PROPERTY_UNIMPLEMENTED(maxZoomScale);
			TITANIUM_PROPERTY_UNIMPLEMENTED(minZoomScale);
			TITANIUM_PROPERTY_UNIMPLEMENTED(scrollType);
			TITANIUM_PROPERTY_UNIMPLEMENTED(verticalBounce);
			TITANIUM_PROPERTY_UNIMPLEMENTED(zoomScale);
			TITANIUM_PROPERTY_UNIMPLEMENTED(decelerationRate);
			TITANIUM_PROPERTY_UNIMPLEMENTED(overScrollMode);
			TITANIUM_PROPERTY_UNIMPLEMENTED(scrollIndicatorStyle);

			ScrollView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ScrollView() = default;
			ScrollView(const ScrollView&) = default;
			ScrollView& operator=(const ScrollView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ScrollView(ScrollView&&) = default;
			ScrollView& operator=(ScrollView&&) = default;
#endif

			virtual void scrollTo(const double& x, const double& y) TITANIUM_NOEXCEPT override;
			virtual void scrollToBottom() TITANIUM_NOEXCEPT override;
			virtual void scrollToTop() TITANIUM_NOEXCEPT override;

			virtual std::string get_contentWidth() const TITANIUM_NOEXCEPT override;
			virtual std::string get_contentHeight() const TITANIUM_NOEXCEPT override;

			virtual void set_contentWidth(const std::string& width) TITANIUM_NOEXCEPT override;
			virtual void set_contentHeight(const std::string& height) TITANIUM_NOEXCEPT override;

			virtual bool get_scrollingEnabled() const TITANIUM_NOEXCEPT override;
			virtual void set_scrollingEnabled(const bool& enabled) TITANIUM_NOEXCEPT override;

			virtual bool get_showHorizontalScrollIndicator() const TITANIUM_NOEXCEPT override;
			virtual void set_showHorizontalScrollIndicator(const bool& enabled) TITANIUM_NOEXCEPT override;

			virtual bool get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT override;
			virtual void set_showVerticalScrollIndicator(const bool& enabled) TITANIUM_NOEXCEPT override;

			virtual void set_contentOffset(const Titanium::UI::Point& offset) TITANIUM_NOEXCEPT override;

			static void JSExportInitialize();
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

		private:
			Windows::UI::Xaml::Controls::Border^ border__;
			Windows::UI::Xaml::Controls::ScrollViewer^ scroll_viewer__;
			JSObject contentView__;

			Windows::Foundation::EventRegistrationToken click_event__;
			Windows::Foundation::EventRegistrationToken dragend_event__;
			Windows::Foundation::EventRegistrationToken dragstart_event__;
			Windows::Foundation::EventRegistrationToken scale_event__;
			Windows::Foundation::EventRegistrationToken scroll_event__;
			Windows::Foundation::EventRegistrationToken scrollend_event__;
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_SCROLLVIEW_HPP_
