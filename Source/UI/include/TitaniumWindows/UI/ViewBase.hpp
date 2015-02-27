/**
* Titanium.UI.ViewBase for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_VIEWBASE_HPP_
#define _TITANIUMWINDOWS_UI_VIEWBASE_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "Titanium/UI/Constants.hpp"
#include "LayoutEngine/LayoutEngine.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
#pragma warning(push)
#pragma warning(disable : 4275)
		class TITANIUMWINDOWS_UI_EXPORT ViewBase
		{
#pragma warning(pop)
		public:
			ViewBase();

			Titanium::LayoutEngine::Node* layout_node_;

			virtual void setComponent(Windows::UI::Xaml::FrameworkElement^ component);
			virtual Windows::UI::Xaml::FrameworkElement^ getComponent() const
			{
				return component_;
			}

			virtual void onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name);

			virtual Windows::UI::Xaml::FrameworkElement^ get_UIElement() const TITANIUM_NOEXCEPT;

			static Windows::UI::Color ColorForName(const std::string& colorName);
			static Windows::UI::Color ColorForHexCode(const std::string& hexCode);

		protected:
			void setLayoutProperty(const Titanium::LayoutEngine::ValueName&, const std::string&);

			virtual bool isWindow() const
			{
				return false;
			}

			virtual bool isLoaded() const
			{
				return is_loaded_;
			}

			virtual void onComponentLoaded(const Titanium::LayoutEngine::Rect&);
			virtual void onComponentSizeChange(const Titanium::LayoutEngine::Rect&);

			virtual void setLayout(const std::string& type);

			virtual std::string defaultHeight() const
			{
				return defaultHeight__;
			}

			virtual std::string defaultWidth() const
			{
				return defaultWidth__;
			}

			virtual void setDefaultHeight(const std::string& defaultHeight)
			{
				defaultHeight__ = defaultHeight;
			}

			virtual void setDefaultWidth(const std::string defaultWidth)
			{
				defaultWidth__ = defaultWidth;
			}

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string defaultWidth__;
			std::string defaultHeight__;

			Windows::Foundation::EventRegistrationToken size_change_event_;
			Windows::Foundation::EventRegistrationToken loaded_event_;

			bool is_width_size_{false};
			bool is_height_size_{false};
			bool is_panel_{false};
			bool is_control_{false};
			bool is_loaded_{false};

			Titanium::LayoutEngine::Rect oldRect;
#pragma warning(pop)

		public:
			Windows::UI::Xaml::FrameworkElement^ component_ { nullptr };
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  //  _TITANIUMWINDOWS_UI_VIEWBASE_HPP_
