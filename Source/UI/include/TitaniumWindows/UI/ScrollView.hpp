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

		class TITANIUMWINDOWS_UI_EXPORT ScrollViewLayoutDelegate : public WindowsViewLayoutDelegate
		{
		public:
			ScrollViewLayoutDelegate(const std::shared_ptr<WindowsViewLayoutDelegate>&) TITANIUM_NOEXCEPT;
			virtual ~ScrollViewLayoutDelegate() = default;

			virtual void add(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT override;
			virtual void set_layout(const std::string& layout) TITANIUM_NOEXCEPT override;
		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::shared_ptr<WindowsViewLayoutDelegate> contentView__;
#pragma warning(pop)
		};

		/*!
		  @class

		  @discussion This is the Titanium.UI.ScrollView implementation for
		  Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ScrollView final : public Titanium::UI::ScrollView, public JSExport<ScrollView>
		{
		public:
			ScrollView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ScrollView() = default;
			ScrollView(const ScrollView&) = default;
			ScrollView& operator=(const ScrollView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ScrollView(ScrollView&&) = default;
			ScrollView& operator=(ScrollView&&) = default;
#endif

			virtual void scrollTo(double x, double y) TITANIUM_NOEXCEPT override;
			virtual void scrollToBottom() TITANIUM_NOEXCEPT override;

			virtual std::string get_contentWidth() const TITANIUM_NOEXCEPT override;
			virtual std::string get_contentHeight() const TITANIUM_NOEXCEPT override;

			virtual void set_contentWidth(const double& width) TITANIUM_NOEXCEPT override;
			virtual void set_contentHeight(const double& height) TITANIUM_NOEXCEPT override;

			virtual bool get_scrollingEnabled() const TITANIUM_NOEXCEPT override;
			virtual void set_scrollingEnabled(const bool& enabled) TITANIUM_NOEXCEPT override;

			virtual bool get_showHorizontalScrollIndicator() const TITANIUM_NOEXCEPT override;
			virtual void set_showHorizontalScrollIndicator(const bool& enabled) TITANIUM_NOEXCEPT override;

			virtual bool get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT override;
			virtual void set_showVerticalScrollIndicator(const bool& enabled) TITANIUM_NOEXCEPT override;

			static void JSExportInitialize();
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

		private:
			Windows::UI::Xaml::Controls::ScrollViewer^ scroll_viewer__;
			JSObject contentView__;
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_SCROLLVIEW_HPP_
