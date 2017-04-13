/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "WindowsNativeModuleLoader.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/UI/UIElement.hpp"

// INSERT_INCLUDES
#include "Platform.Object.hpp"
#include "Windows.Foundation.AsyncActionCompletedHandler.hpp"
#include "Windows.Foundation.Collections.IPropertySet.hpp"
#include "Windows.Foundation.IAsyncAction.hpp"
#include "Windows.Foundation.IWwwFormUrlDecoderEntry.hpp"
#include "Windows.Foundation.Uri.hpp"
#include "Windows.Foundation.WwwFormUrlDecoder.hpp"
#include "Windows.UI.Colors.hpp"
#include "Windows.UI.Core.CoreCursor.hpp"
#include "Windows.UI.Core.CoreDispatcher.hpp"
#include "Windows.UI.Core.CoreWindow.hpp"
#include "Windows.UI.Core.DispatchedHandler.hpp"
#include "Windows.UI.Core.IdleDispatchedHandler.hpp"
#include "Windows.UI.Core.IdleDispatchedHandlerArgs.hpp"
#include "Windows.UI.Xaml.Controls.AppBar.hpp"
#include "Windows.UI.Xaml.Controls.Canvas.hpp"
#include "Windows.UI.Xaml.Controls.ContentControl.hpp"
#include "Windows.UI.Xaml.Controls.Control.hpp"
#include "Windows.UI.Xaml.Controls.ControlTemplate.hpp"
#include "Windows.UI.Xaml.Controls.DataTemplateSelector.hpp"
#include "Windows.UI.Xaml.Controls.Frame.hpp"
#include "Windows.UI.Xaml.Controls.Page.hpp"
#include "Windows.UI.Xaml.Controls.Panel.hpp"
#include "Windows.UI.Xaml.Controls.TextBlock.hpp"
#include "Windows.UI.Xaml.Controls.UIElementCollection.hpp"
#include "Windows.UI.Xaml.Controls.UserControl.hpp"
#include "Windows.UI.Xaml.CreateDefaultValueCallback.hpp"
#include "Windows.UI.Xaml.Data.Binding.hpp"
#include "Windows.UI.Xaml.Data.BindingBase.hpp"
#include "Windows.UI.Xaml.Data.BindingExpression.hpp"
#include "Windows.UI.Xaml.Data.BindingExpressionBase.hpp"
#include "Windows.UI.Xaml.Data.IValueConverter.hpp"
#include "Windows.UI.Xaml.Data.RelativeSource.hpp"
#include "Windows.UI.Xaml.DataTemplate.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.DependencyPropertyChangedEventArgs.hpp"
#include "Windows.UI.Xaml.Documents.Inline.hpp"
#include "Windows.UI.Xaml.Documents.InlineCollection.hpp"
#include "Windows.UI.Xaml.Documents.TextElement.hpp"
#include "Windows.UI.Xaml.Documents.TextPointer.hpp"
#include "Windows.UI.Xaml.FrameworkElement.hpp"
#include "Windows.UI.Xaml.FrameworkTemplate.hpp"
#include "Windows.UI.Xaml.Input.Pointer.hpp"
#include "Windows.UI.Xaml.Media.Animation.NavigationTransitionInfo.hpp"
#include "Windows.UI.Xaml.Media.Animation.Transition.hpp"
#include "Windows.UI.Xaml.Media.Animation.TransitionCollection.hpp"
#include "Windows.UI.Xaml.Media.Brush.hpp"
#include "Windows.UI.Xaml.Media.CacheMode.hpp"
#include "Windows.UI.Xaml.Media.FontFamily.hpp"
#include "Windows.UI.Xaml.Media.GeneralTransform.hpp"
#include "Windows.UI.Xaml.Media.Geometry.hpp"
#include "Windows.UI.Xaml.Media.Projection.hpp"
#include "Windows.UI.Xaml.Media.RectangleGeometry.hpp"
#include "Windows.UI.Xaml.Media.SolidColorBrush.hpp"
#include "Windows.UI.Xaml.Media.Transform.hpp"
#include "Windows.UI.Xaml.Navigation.PageStackEntry.hpp"
#include "Windows.UI.Xaml.PropertyChangedCallback.hpp"
#include "Windows.UI.Xaml.PropertyMetadata.hpp"
#include "Windows.UI.Xaml.PropertyPath.hpp"
#include "Windows.UI.Xaml.ResourceDictionary.hpp"
#include "Windows.UI.Xaml.RoutedEvent.hpp"
#include "Windows.UI.Xaml.SetterBase.hpp"
#include "Windows.UI.Xaml.SetterBaseCollection.hpp"
#include "Windows.UI.Xaml.Style.hpp"
#include "Windows.UI.Xaml.TriggerBase.hpp"
#include "Windows.UI.Xaml.TriggerCollection.hpp"
#include "Windows.UI.Xaml.UIElement.hpp"
#include "Windows.UI.Xaml.Window.hpp"
// END_INCLUDES

// FIXME This will only work if we generate _all_ type wrappers and include them here. Otherwise we need to move this into the user's app and limit to those types used...

namespace TitaniumWindows
{
	using namespace HAL;

	WindowsNativeModuleLoader::WindowsNativeModuleLoader()
	{
	}

	WindowsNativeModuleLoader::~WindowsNativeModuleLoader()
	{
	}

	void WindowsNativeModuleLoader::registerValue(const JSContext& context, const std::string& name, const JSValue& value) const
	{
		// FIXME If we've already hung a value at this name, we shouldn't do any of this!
		auto global = context.get_global_object();
		// Split type/path by '.', then build up the namespaces!
		JSObject current_object = global;

		std::stringstream stream(name);
		std::string segment;
		std::vector<std::string> parts;
		while(std::getline(stream, segment, '.'))
		{
		   parts.push_back(segment);
		}
		for (size_t i = 0, len = parts.size(); i < len - 1; i++) {
			auto part = parts.at(i);

			if (!current_object.HasProperty(part)) {
				auto child_object = context.CreateObject();
				current_object.SetProperty(part, child_object);
				current_object = child_object;
			} else {
				auto current_value = current_object.GetProperty(part);
				TITANIUM_ASSERT(current_value.IsObject());
				current_object = static_cast<JSObject>(current_value);
			}
		}
		// hang the actual value at the end!
		current_object.SetProperty(parts.at(parts.size() - 1), value);
	}

	void WindowsNativeModuleLoader::registerEnums(const JSContext& context, const std::string& type_name) const
	{
		// INSERT_ENUMS
		if (type_name == "Windows.Foundation.AsyncActionCompletedHandler") {
			registerValue(context, "Windows.Foundation.AsyncStatus.Started", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::Foundation::AsyncStatus::Started))));
			registerValue(context, "Windows.Foundation.AsyncStatus.Error", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::Foundation::AsyncStatus::Error))));
			registerValue(context, "Windows.Foundation.AsyncStatus.Completed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::Foundation::AsyncStatus::Completed))));
			registerValue(context, "Windows.Foundation.AsyncStatus.Canceled", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::Foundation::AsyncStatus::Canceled))));
		}
		else if (type_name == "Windows.UI.Core.CoreCursor") {
			registerValue(context, "Windows.UI.Core.CoreCursorType.Wait", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::Wait))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.UpArrow", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::UpArrow))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.UniversalNo", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::UniversalNo))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.SizeWestEast", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::SizeWestEast))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.SizeNorthwestSoutheast", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::SizeNorthwestSoutheast))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.SizeNorthSouth", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::SizeNorthSouth))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.SizeNortheastSouthwest", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::SizeNortheastSouthwest))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.SizeAll", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::SizeAll))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.IBeam", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::IBeam))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.Help", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::Help))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.Hand", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::Hand))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.Custom", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::Custom))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.Cross", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::Cross))));
			registerValue(context, "Windows.UI.Core.CoreCursorType.Arrow", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreCursorType::Arrow))));
		}
		else if (type_name == "Windows.UI.Core.CoreDispatcher") {
			registerValue(context, "Windows.UI.Core.CoreProcessEventsOption.ProcessAllIfPresent", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreProcessEventsOption::ProcessAllIfPresent))));
			registerValue(context, "Windows.UI.Core.CoreProcessEventsOption.ProcessUntilQuit", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreProcessEventsOption::ProcessUntilQuit))));
			registerValue(context, "Windows.UI.Core.CoreProcessEventsOption.ProcessOneIfPresent", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreProcessEventsOption::ProcessOneIfPresent))));
			registerValue(context, "Windows.UI.Core.CoreProcessEventsOption.ProcessOneAndAllPending", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreProcessEventsOption::ProcessOneAndAllPending))));
			registerValue(context, "Windows.UI.Core.CoreDispatcherPriority.High", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreDispatcherPriority::High))));
			registerValue(context, "Windows.UI.Core.CoreDispatcherPriority.Normal", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreDispatcherPriority::Normal))));
			registerValue(context, "Windows.UI.Core.CoreDispatcherPriority.Low", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreDispatcherPriority::Low))));
			registerValue(context, "Windows.UI.Core.CoreDispatcherPriority.Idle", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreDispatcherPriority::Idle))));
		}
		else if (type_name == "Windows.UI.Core.CoreWindow") {
			registerValue(context, "Windows.UI.Core.CoreWindowFlowDirection.RightToLeft", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreWindowFlowDirection::RightToLeft))));
			registerValue(context, "Windows.UI.Core.CoreWindowFlowDirection.LeftToRight", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreWindowFlowDirection::LeftToRight))));
			registerValue(context, "Windows.UI.Core.CoreVirtualKeyStates.Locked", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreVirtualKeyStates::Locked))));
			registerValue(context, "Windows.UI.Core.CoreVirtualKeyStates.Down", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreVirtualKeyStates::Down))));
			registerValue(context, "Windows.UI.Core.CoreVirtualKeyStates.None", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Core::CoreVirtualKeyStates::None))));
			registerValue(context, "Windows.System.VirtualKey.GoHome", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::GoHome))));
			registerValue(context, "Windows.System.VirtualKey.Favorites", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Favorites))));
			registerValue(context, "Windows.System.VirtualKey.Search", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Search))));
			registerValue(context, "Windows.System.VirtualKey.Stop", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Stop))));
			registerValue(context, "Windows.System.VirtualKey.Refresh", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Refresh))));
			registerValue(context, "Windows.System.VirtualKey.GoForward", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::GoForward))));
			registerValue(context, "Windows.System.VirtualKey.GoBack", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::GoBack))));
			registerValue(context, "Windows.System.VirtualKey.RightMenu", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::RightMenu))));
			registerValue(context, "Windows.System.VirtualKey.LeftMenu", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::LeftMenu))));
			registerValue(context, "Windows.System.VirtualKey.RightControl", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::RightControl))));
			registerValue(context, "Windows.System.VirtualKey.LeftControl", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::LeftControl))));
			registerValue(context, "Windows.System.VirtualKey.RightShift", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::RightShift))));
			registerValue(context, "Windows.System.VirtualKey.LeftShift", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::LeftShift))));
			registerValue(context, "Windows.System.VirtualKey.Scroll", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Scroll))));
			registerValue(context, "Windows.System.VirtualKey.NumberKeyLock", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberKeyLock))));
			registerValue(context, "Windows.System.VirtualKey.F24", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F24))));
			registerValue(context, "Windows.System.VirtualKey.F23", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F23))));
			registerValue(context, "Windows.System.VirtualKey.F22", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F22))));
			registerValue(context, "Windows.System.VirtualKey.F21", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F21))));
			registerValue(context, "Windows.System.VirtualKey.F20", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F20))));
			registerValue(context, "Windows.System.VirtualKey.F19", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F19))));
			registerValue(context, "Windows.System.VirtualKey.F18", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F18))));
			registerValue(context, "Windows.System.VirtualKey.F17", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F17))));
			registerValue(context, "Windows.System.VirtualKey.F16", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F16))));
			registerValue(context, "Windows.System.VirtualKey.F15", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F15))));
			registerValue(context, "Windows.System.VirtualKey.F14", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F14))));
			registerValue(context, "Windows.System.VirtualKey.F13", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F13))));
			registerValue(context, "Windows.System.VirtualKey.F12", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F12))));
			registerValue(context, "Windows.System.VirtualKey.F11", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F11))));
			registerValue(context, "Windows.System.VirtualKey.F10", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F10))));
			registerValue(context, "Windows.System.VirtualKey.F9", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F9))));
			registerValue(context, "Windows.System.VirtualKey.F8", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F8))));
			registerValue(context, "Windows.System.VirtualKey.F7", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F7))));
			registerValue(context, "Windows.System.VirtualKey.F6", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F6))));
			registerValue(context, "Windows.System.VirtualKey.F5", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F5))));
			registerValue(context, "Windows.System.VirtualKey.F4", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F4))));
			registerValue(context, "Windows.System.VirtualKey.F3", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F3))));
			registerValue(context, "Windows.System.VirtualKey.F2", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F2))));
			registerValue(context, "Windows.System.VirtualKey.F1", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F1))));
			registerValue(context, "Windows.System.VirtualKey.Divide", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Divide))));
			registerValue(context, "Windows.System.VirtualKey.Decimal", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Decimal))));
			registerValue(context, "Windows.System.VirtualKey.Subtract", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Subtract))));
			registerValue(context, "Windows.System.VirtualKey.Separator", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Separator))));
			registerValue(context, "Windows.System.VirtualKey.Add", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Add))));
			registerValue(context, "Windows.System.VirtualKey.Multiply", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Multiply))));
			registerValue(context, "Windows.System.VirtualKey.NumberPad9", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberPad9))));
			registerValue(context, "Windows.System.VirtualKey.NumberPad8", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberPad8))));
			registerValue(context, "Windows.System.VirtualKey.NumberPad7", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberPad7))));
			registerValue(context, "Windows.System.VirtualKey.NumberPad6", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberPad6))));
			registerValue(context, "Windows.System.VirtualKey.NumberPad5", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberPad5))));
			registerValue(context, "Windows.System.VirtualKey.NumberPad4", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberPad4))));
			registerValue(context, "Windows.System.VirtualKey.NumberPad3", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberPad3))));
			registerValue(context, "Windows.System.VirtualKey.NumberPad2", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberPad2))));
			registerValue(context, "Windows.System.VirtualKey.NumberPad1", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberPad1))));
			registerValue(context, "Windows.System.VirtualKey.NumberPad0", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NumberPad0))));
			registerValue(context, "Windows.System.VirtualKey.Sleep", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Sleep))));
			registerValue(context, "Windows.System.VirtualKey.Application", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Application))));
			registerValue(context, "Windows.System.VirtualKey.RightWindows", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::RightWindows))));
			registerValue(context, "Windows.System.VirtualKey.LeftWindows", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::LeftWindows))));
			registerValue(context, "Windows.System.VirtualKey.Z", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Z))));
			registerValue(context, "Windows.System.VirtualKey.Y", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Y))));
			registerValue(context, "Windows.System.VirtualKey.X", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::X))));
			registerValue(context, "Windows.System.VirtualKey.W", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::W))));
			registerValue(context, "Windows.System.VirtualKey.V", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::V))));
			registerValue(context, "Windows.System.VirtualKey.U", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::U))));
			registerValue(context, "Windows.System.VirtualKey.T", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::T))));
			registerValue(context, "Windows.System.VirtualKey.S", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::S))));
			registerValue(context, "Windows.System.VirtualKey.R", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::R))));
			registerValue(context, "Windows.System.VirtualKey.Q", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Q))));
			registerValue(context, "Windows.System.VirtualKey.P", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::P))));
			registerValue(context, "Windows.System.VirtualKey.O", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::O))));
			registerValue(context, "Windows.System.VirtualKey.N", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::N))));
			registerValue(context, "Windows.System.VirtualKey.M", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::M))));
			registerValue(context, "Windows.System.VirtualKey.L", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::L))));
			registerValue(context, "Windows.System.VirtualKey.K", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::K))));
			registerValue(context, "Windows.System.VirtualKey.J", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::J))));
			registerValue(context, "Windows.System.VirtualKey.I", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::I))));
			registerValue(context, "Windows.System.VirtualKey.H", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::H))));
			registerValue(context, "Windows.System.VirtualKey.G", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::G))));
			registerValue(context, "Windows.System.VirtualKey.F", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::F))));
			registerValue(context, "Windows.System.VirtualKey.E", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::E))));
			registerValue(context, "Windows.System.VirtualKey.D", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::D))));
			registerValue(context, "Windows.System.VirtualKey.C", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::C))));
			registerValue(context, "Windows.System.VirtualKey.B", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::B))));
			registerValue(context, "Windows.System.VirtualKey.A", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::A))));
			registerValue(context, "Windows.System.VirtualKey.Number9", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Number9))));
			registerValue(context, "Windows.System.VirtualKey.Number8", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Number8))));
			registerValue(context, "Windows.System.VirtualKey.Number7", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Number7))));
			registerValue(context, "Windows.System.VirtualKey.Number6", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Number6))));
			registerValue(context, "Windows.System.VirtualKey.Number5", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Number5))));
			registerValue(context, "Windows.System.VirtualKey.Number4", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Number4))));
			registerValue(context, "Windows.System.VirtualKey.Number3", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Number3))));
			registerValue(context, "Windows.System.VirtualKey.Number2", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Number2))));
			registerValue(context, "Windows.System.VirtualKey.Number1", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Number1))));
			registerValue(context, "Windows.System.VirtualKey.Number0", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Number0))));
			registerValue(context, "Windows.System.VirtualKey.Help", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Help))));
			registerValue(context, "Windows.System.VirtualKey.Delete", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Delete))));
			registerValue(context, "Windows.System.VirtualKey.Insert", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Insert))));
			registerValue(context, "Windows.System.VirtualKey.Snapshot", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Snapshot))));
			registerValue(context, "Windows.System.VirtualKey.Execute", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Execute))));
			registerValue(context, "Windows.System.VirtualKey.Print", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Print))));
			registerValue(context, "Windows.System.VirtualKey.Select", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Select))));
			registerValue(context, "Windows.System.VirtualKey.Down", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Down))));
			registerValue(context, "Windows.System.VirtualKey.Right", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Right))));
			registerValue(context, "Windows.System.VirtualKey.Up", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Up))));
			registerValue(context, "Windows.System.VirtualKey.Left", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Left))));
			registerValue(context, "Windows.System.VirtualKey.Home", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Home))));
			registerValue(context, "Windows.System.VirtualKey.End", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::End))));
			registerValue(context, "Windows.System.VirtualKey.PageDown", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::PageDown))));
			registerValue(context, "Windows.System.VirtualKey.PageUp", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::PageUp))));
			registerValue(context, "Windows.System.VirtualKey.Space", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Space))));
			registerValue(context, "Windows.System.VirtualKey.ModeChange", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::ModeChange))));
			registerValue(context, "Windows.System.VirtualKey.Accept", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Accept))));
			registerValue(context, "Windows.System.VirtualKey.NonConvert", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::NonConvert))));
			registerValue(context, "Windows.System.VirtualKey.Convert", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Convert))));
			registerValue(context, "Windows.System.VirtualKey.Escape", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Escape))));
			registerValue(context, "Windows.System.VirtualKey.Kanji", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Kanji))));
			registerValue(context, "Windows.System.VirtualKey.Hanja", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Hanja))));
			registerValue(context, "Windows.System.VirtualKey.Final", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Final))));
			registerValue(context, "Windows.System.VirtualKey.Junja", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Junja))));
			registerValue(context, "Windows.System.VirtualKey.Hangul", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Hangul))));
			registerValue(context, "Windows.System.VirtualKey.Kana", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Kana))));
			registerValue(context, "Windows.System.VirtualKey.CapitalLock", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::CapitalLock))));
			registerValue(context, "Windows.System.VirtualKey.Pause", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Pause))));
			registerValue(context, "Windows.System.VirtualKey.Menu", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Menu))));
			registerValue(context, "Windows.System.VirtualKey.Control", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Control))));
			registerValue(context, "Windows.System.VirtualKey.Shift", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Shift))));
			registerValue(context, "Windows.System.VirtualKey.Enter", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Enter))));
			registerValue(context, "Windows.System.VirtualKey.Clear", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Clear))));
			registerValue(context, "Windows.System.VirtualKey.Tab", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Tab))));
			registerValue(context, "Windows.System.VirtualKey.Back", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Back))));
			registerValue(context, "Windows.System.VirtualKey.XButton2", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::XButton2))));
			registerValue(context, "Windows.System.VirtualKey.XButton1", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::XButton1))));
			registerValue(context, "Windows.System.VirtualKey.MiddleButton", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::MiddleButton))));
			registerValue(context, "Windows.System.VirtualKey.Cancel", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::Cancel))));
			registerValue(context, "Windows.System.VirtualKey.RightButton", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::RightButton))));
			registerValue(context, "Windows.System.VirtualKey.LeftButton", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::LeftButton))));
			registerValue(context, "Windows.System.VirtualKey.None", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::System::VirtualKey::None))));
		}
		else if (type_name == "Windows.UI.Xaml.Controls.Control") {
			registerEnums(context, "Windows.UI.Xaml.FrameworkElement");
			registerValue(context, "Windows.UI.Xaml.VerticalAlignment.Stretch", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::VerticalAlignment::Stretch))));
			registerValue(context, "Windows.UI.Xaml.VerticalAlignment.Bottom", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::VerticalAlignment::Bottom))));
			registerValue(context, "Windows.UI.Xaml.VerticalAlignment.Center", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::VerticalAlignment::Center))));
			registerValue(context, "Windows.UI.Xaml.VerticalAlignment.Top", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::VerticalAlignment::Top))));
			registerValue(context, "Windows.UI.Xaml.Input.KeyboardNavigationMode.Once", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::KeyboardNavigationMode::Once))));
			registerValue(context, "Windows.UI.Xaml.Input.KeyboardNavigationMode.Cycle", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::KeyboardNavigationMode::Cycle))));
			registerValue(context, "Windows.UI.Xaml.Input.KeyboardNavigationMode.Local", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::KeyboardNavigationMode::Local))));
			registerValue(context, "Windows.UI.Xaml.HorizontalAlignment.Stretch", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::HorizontalAlignment::Stretch))));
			registerValue(context, "Windows.UI.Xaml.HorizontalAlignment.Right", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::HorizontalAlignment::Right))));
			registerValue(context, "Windows.UI.Xaml.HorizontalAlignment.Center", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::HorizontalAlignment::Center))));
			registerValue(context, "Windows.UI.Xaml.HorizontalAlignment.Left", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::HorizontalAlignment::Left))));
			registerValue(context, "Windows.UI.Xaml.FocusState.Programmatic", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::FocusState::Programmatic))));
			registerValue(context, "Windows.UI.Xaml.FocusState.Keyboard", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::FocusState::Keyboard))));
			registerValue(context, "Windows.UI.Xaml.FocusState.Pointer", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::FocusState::Pointer))));
			registerValue(context, "Windows.UI.Xaml.FocusState.Unfocused", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::FocusState::Unfocused))));
			registerValue(context, "Windows.UI.Text.FontStyle.Italic", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStyle::Italic))));
			registerValue(context, "Windows.UI.Text.FontStyle.Oblique", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStyle::Oblique))));
			registerValue(context, "Windows.UI.Text.FontStyle.Normal", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStyle::Normal))));
			registerValue(context, "Windows.UI.Text.FontStretch.UltraExpanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::UltraExpanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.ExtraExpanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::ExtraExpanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.Expanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Expanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.SemiExpanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::SemiExpanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.Normal", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Normal))));
			registerValue(context, "Windows.UI.Text.FontStretch.SemiCondensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::SemiCondensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.Condensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Condensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.ExtraCondensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::ExtraCondensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.UltraCondensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::UltraCondensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.Undefined", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Undefined))));
		}
		else if (type_name == "Windows.UI.Xaml.Controls.Page") {
			registerEnums(context, "Windows.UI.Xaml.Controls.UserControl");
			registerValue(context, "Windows.UI.Xaml.Navigation.NavigationCacheMode.Enabled", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled))));
			registerValue(context, "Windows.UI.Xaml.Navigation.NavigationCacheMode.Required", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Navigation::NavigationCacheMode::Required))));
			registerValue(context, "Windows.UI.Xaml.Navigation.NavigationCacheMode.Disabled", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Navigation::NavigationCacheMode::Disabled))));
		}
		else if (type_name == "Windows.UI.Xaml.Controls.TextBlock") {
			registerEnums(context, "Windows.UI.Xaml.FrameworkElement");
			registerValue(context, "Windows.UI.Xaml.TextWrapping.WrapWholeWords", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextWrapping::WrapWholeWords))));
			registerValue(context, "Windows.UI.Xaml.TextWrapping.Wrap", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextWrapping::Wrap))));
			registerValue(context, "Windows.UI.Xaml.TextWrapping.NoWrap", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextWrapping::NoWrap))));
			registerValue(context, "Windows.UI.Xaml.TextTrimming.Clip", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextTrimming::Clip))));
			registerValue(context, "Windows.UI.Xaml.TextTrimming.WordEllipsis", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextTrimming::WordEllipsis))));
			registerValue(context, "Windows.UI.Xaml.TextTrimming.CharacterEllipsis", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextTrimming::CharacterEllipsis))));
			registerValue(context, "Windows.UI.Xaml.TextTrimming.None", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextTrimming::None))));
			registerValue(context, "Windows.UI.Xaml.TextReadingOrder.DetectFromContent", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextReadingOrder::DetectFromContent))));
			registerValue(context, "Windows.UI.Xaml.TextReadingOrder.Default", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextReadingOrder::Default))));
			registerValue(context, "Windows.UI.Xaml.TextLineBounds.Tight", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextLineBounds::Tight))));
			registerValue(context, "Windows.UI.Xaml.TextLineBounds.TrimToBaseline", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextLineBounds::TrimToBaseline))));
			registerValue(context, "Windows.UI.Xaml.TextLineBounds.TrimToCapHeight", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextLineBounds::TrimToCapHeight))));
			registerValue(context, "Windows.UI.Xaml.TextLineBounds.Full", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextLineBounds::Full))));
			registerValue(context, "Windows.UI.Xaml.TextAlignment.Justify", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextAlignment::Justify))));
			registerValue(context, "Windows.UI.Xaml.TextAlignment.Right", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextAlignment::Right))));
			registerValue(context, "Windows.UI.Xaml.TextAlignment.Left", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextAlignment::Left))));
			registerValue(context, "Windows.UI.Xaml.TextAlignment.Center", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::TextAlignment::Center))));
			registerValue(context, "Windows.UI.Xaml.OpticalMarginAlignment.TrimSideBearings", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::OpticalMarginAlignment::TrimSideBearings))));
			registerValue(context, "Windows.UI.Xaml.OpticalMarginAlignment.None", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::OpticalMarginAlignment::None))));
			registerValue(context, "Windows.UI.Xaml.LineStackingStrategy.BaselineToBaseline", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::LineStackingStrategy::BaselineToBaseline))));
			registerValue(context, "Windows.UI.Xaml.LineStackingStrategy.BlockLineHeight", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::LineStackingStrategy::BlockLineHeight))));
			registerValue(context, "Windows.UI.Xaml.LineStackingStrategy.MaxHeight", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::LineStackingStrategy::MaxHeight))));
			registerValue(context, "Windows.UI.Xaml.FocusState.Programmatic", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::FocusState::Programmatic))));
			registerValue(context, "Windows.UI.Xaml.FocusState.Keyboard", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::FocusState::Keyboard))));
			registerValue(context, "Windows.UI.Xaml.FocusState.Pointer", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::FocusState::Pointer))));
			registerValue(context, "Windows.UI.Xaml.FocusState.Unfocused", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::FocusState::Unfocused))));
			registerValue(context, "Windows.UI.Text.FontStyle.Italic", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStyle::Italic))));
			registerValue(context, "Windows.UI.Text.FontStyle.Oblique", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStyle::Oblique))));
			registerValue(context, "Windows.UI.Text.FontStyle.Normal", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStyle::Normal))));
			registerValue(context, "Windows.UI.Text.FontStretch.UltraExpanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::UltraExpanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.ExtraExpanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::ExtraExpanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.Expanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Expanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.SemiExpanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::SemiExpanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.Normal", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Normal))));
			registerValue(context, "Windows.UI.Text.FontStretch.SemiCondensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::SemiCondensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.Condensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Condensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.ExtraCondensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::ExtraCondensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.UltraCondensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::UltraCondensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.Undefined", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Undefined))));
		}
		else if (type_name == "Windows.UI.Xaml.Data.Binding") {
			registerEnums(context, "Windows.UI.Xaml.Data.BindingBase");
			registerValue(context, "Windows.UI.Xaml.Data.UpdateSourceTrigger.Explicit", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Data::UpdateSourceTrigger::Explicit))));
			registerValue(context, "Windows.UI.Xaml.Data.UpdateSourceTrigger.PropertyChanged", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Data::UpdateSourceTrigger::PropertyChanged))));
			registerValue(context, "Windows.UI.Xaml.Data.UpdateSourceTrigger.Default", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Data::UpdateSourceTrigger::Default))));
			registerValue(context, "Windows.UI.Xaml.Data.BindingMode.TwoWay", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Data::BindingMode::TwoWay))));
			registerValue(context, "Windows.UI.Xaml.Data.BindingMode.OneTime", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Data::BindingMode::OneTime))));
			registerValue(context, "Windows.UI.Xaml.Data.BindingMode.OneWay", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Data::BindingMode::OneWay))));
		}
		else if (type_name == "Windows.UI.Xaml.Data.RelativeSource") {
			registerEnums(context, "Windows.UI.Xaml.DependencyObject");
			registerValue(context, "Windows.UI.Xaml.Data.RelativeSourceMode.Self", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Data::RelativeSourceMode::Self))));
			registerValue(context, "Windows.UI.Xaml.Data.RelativeSourceMode.TemplatedParent", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Data::RelativeSourceMode::TemplatedParent))));
			registerValue(context, "Windows.UI.Xaml.Data.RelativeSourceMode.None", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Data::RelativeSourceMode::None))));
		}
		else if (type_name == "Windows.UI.Xaml.Documents.TextElement") {
			registerEnums(context, "Windows.UI.Xaml.DependencyObject");
			registerValue(context, "Windows.UI.Text.FontStyle.Italic", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStyle::Italic))));
			registerValue(context, "Windows.UI.Text.FontStyle.Oblique", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStyle::Oblique))));
			registerValue(context, "Windows.UI.Text.FontStyle.Normal", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStyle::Normal))));
			registerValue(context, "Windows.UI.Text.FontStretch.UltraExpanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::UltraExpanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.ExtraExpanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::ExtraExpanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.Expanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Expanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.SemiExpanded", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::SemiExpanded))));
			registerValue(context, "Windows.UI.Text.FontStretch.Normal", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Normal))));
			registerValue(context, "Windows.UI.Text.FontStretch.SemiCondensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::SemiCondensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.Condensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Condensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.ExtraCondensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::ExtraCondensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.UltraCondensed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::UltraCondensed))));
			registerValue(context, "Windows.UI.Text.FontStretch.Undefined", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Text::FontStretch::Undefined))));
		}
		else if (type_name == "Windows.UI.Xaml.Documents.TextPointer") {
			registerValue(context, "Windows.UI.Xaml.Documents.LogicalDirection.Forward", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Documents::LogicalDirection::Forward))));
			registerValue(context, "Windows.UI.Xaml.Documents.LogicalDirection.Backward", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Documents::LogicalDirection::Backward))));
		}
		else if (type_name == "Windows.UI.Xaml.FrameworkElement") {
			registerEnums(context, "Windows.UI.Xaml.UIElement");
			registerValue(context, "Windows.UI.Xaml.VerticalAlignment.Stretch", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::VerticalAlignment::Stretch))));
			registerValue(context, "Windows.UI.Xaml.VerticalAlignment.Bottom", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::VerticalAlignment::Bottom))));
			registerValue(context, "Windows.UI.Xaml.VerticalAlignment.Center", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::VerticalAlignment::Center))));
			registerValue(context, "Windows.UI.Xaml.VerticalAlignment.Top", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::VerticalAlignment::Top))));
			registerValue(context, "Windows.UI.Xaml.HorizontalAlignment.Stretch", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::HorizontalAlignment::Stretch))));
			registerValue(context, "Windows.UI.Xaml.HorizontalAlignment.Right", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::HorizontalAlignment::Right))));
			registerValue(context, "Windows.UI.Xaml.HorizontalAlignment.Center", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::HorizontalAlignment::Center))));
			registerValue(context, "Windows.UI.Xaml.HorizontalAlignment.Left", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::HorizontalAlignment::Left))));
			registerValue(context, "Windows.UI.Xaml.FlowDirection.RightToLeft", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::FlowDirection::RightToLeft))));
			registerValue(context, "Windows.UI.Xaml.FlowDirection.LeftToRight", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::FlowDirection::LeftToRight))));
			registerValue(context, "Windows.UI.Xaml.ElementTheme.Dark", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::ElementTheme::Dark))));
			registerValue(context, "Windows.UI.Xaml.ElementTheme.Light", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::ElementTheme::Light))));
			registerValue(context, "Windows.UI.Xaml.ElementTheme.Default", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::ElementTheme::Default))));
		}
		else if (type_name == "Windows.UI.Xaml.Input.Pointer") {
			registerValue(context, "Windows.Devices.Input.PointerDeviceType.Mouse", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::Devices::Input::PointerDeviceType::Mouse))));
			registerValue(context, "Windows.Devices.Input.PointerDeviceType.Pen", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::Devices::Input::PointerDeviceType::Pen))));
			registerValue(context, "Windows.Devices.Input.PointerDeviceType.Touch", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::Devices::Input::PointerDeviceType::Touch))));
		}
		else if (type_name == "Windows.UI.Xaml.UIElement") {
			registerEnums(context, "Windows.UI.Xaml.DependencyObject");
			registerValue(context, "Windows.UI.Xaml.Visibility.Collapsed", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Visibility::Collapsed))));
			registerValue(context, "Windows.UI.Xaml.Visibility.Visible", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Visibility::Visible))));
			registerValue(context, "Windows.UI.Xaml.Media.ElementCompositeMode.MinBlend", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Media::ElementCompositeMode::MinBlend))));
			registerValue(context, "Windows.UI.Xaml.Media.ElementCompositeMode.SourceOver", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Media::ElementCompositeMode::SourceOver))));
			registerValue(context, "Windows.UI.Xaml.Media.ElementCompositeMode.Inherit", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Media::ElementCompositeMode::Inherit))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.System", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::System))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.All", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::All))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.ScaleInertia", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::ScaleInertia))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.RotateInertia", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::RotateInertia))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.TranslateInertia", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::TranslateInertia))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.Scale", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::Scale))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.Rotate", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::Rotate))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.TranslateRailsY", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::TranslateRailsY))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.TranslateRailsX", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::TranslateRailsX))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.TranslateY", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::TranslateY))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.TranslateX", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::TranslateX))));
			registerValue(context, "Windows.UI.Xaml.Input.ManipulationModes.None", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::Windows::UI::Xaml::Input::ManipulationModes::None))));
		}
		// END_ENUMS
	}

	JSValue WindowsNativeModuleLoader::registerNativeModule(const JSContext& context, const std::string& path) const
	{
		JSObject instantiated = context.CreateObject();
		// TODO Use a std::map that we populate once and just check for a key with that name?
		// INSERT_SWITCH
		if (path == "Platform.Object") {
			instantiated = context.CreateObject(JSExport<::Titanium::Platform::Object>::Class());
		}
		else if (path == "Windows.Foundation.AsyncActionCompletedHandler") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::Foundation::AsyncActionCompletedHandler>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.Foundation.Collections.IPropertySet") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::Foundation::Collections::IPropertySet>::Class());
		}
		else if (path == "Windows.Foundation.IAsyncAction") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::Foundation::IAsyncAction>::Class());
		}
		else if (path == "Windows.Foundation.IWwwFormUrlDecoderEntry") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::Foundation::IWwwFormUrlDecoderEntry>::Class());
		}
		else if (path == "Windows.Foundation.Uri") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::Foundation::Uri>::Class());
		}
		else if (path == "Windows.Foundation.WwwFormUrlDecoder") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::Foundation::WwwFormUrlDecoder>::Class());
		}
		else if (path == "Windows.UI.Colors") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Colors>::Class());
		}
		else if (path == "Windows.UI.Core.CoreCursor") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Core::CoreCursor>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Core.CoreDispatcher") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Core::CoreDispatcher>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Core.CoreWindow") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Core::CoreWindow>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Core.DispatchedHandler") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Core::DispatchedHandler>::Class());
		}
		else if (path == "Windows.UI.Core.IdleDispatchedHandler") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Core::IdleDispatchedHandler>::Class());
		}
		else if (path == "Windows.UI.Core.IdleDispatchedHandlerArgs") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Core::IdleDispatchedHandlerArgs>::Class());
		}
		else if (path == "Windows.UI.Xaml.Controls.AppBar") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::AppBar>::Class());
		}
		else if (path == "Windows.UI.Xaml.Controls.Canvas") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::Canvas>::Class());
		}
		else if (path == "Windows.UI.Xaml.Controls.ContentControl") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::ContentControl>::Class());
		}
		else if (path == "Windows.UI.Xaml.Controls.Control") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::Control>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Xaml.Controls.ControlTemplate") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::ControlTemplate>::Class());
		}
		else if (path == "Windows.UI.Xaml.Controls.DataTemplateSelector") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::DataTemplateSelector>::Class());
		}
		else if (path == "Windows.UI.Xaml.Controls.Frame") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::Frame>::Class());
		}
		else if (path == "Windows.UI.Xaml.Controls.Page") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::Page>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Xaml.Controls.Panel") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::Panel>::Class());
		}
		else if (path == "Windows.UI.Xaml.Controls.TextBlock") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::TextBlock>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Xaml.Controls.UIElementCollection") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::UIElementCollection>::Class());
		}
		else if (path == "Windows.UI.Xaml.Controls.UserControl") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Controls::UserControl>::Class());
		}
		else if (path == "Windows.UI.Xaml.CreateDefaultValueCallback") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::CreateDefaultValueCallback>::Class());
		}
		else if (path == "Windows.UI.Xaml.Data.Binding") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Data::Binding>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Xaml.Data.BindingBase") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Data::BindingBase>::Class());
		}
		else if (path == "Windows.UI.Xaml.Data.BindingExpression") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Data::BindingExpression>::Class());
		}
		else if (path == "Windows.UI.Xaml.Data.BindingExpressionBase") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Data::BindingExpressionBase>::Class());
		}
		else if (path == "Windows.UI.Xaml.Data.IValueConverter") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Data::IValueConverter>::Class());
		}
		else if (path == "Windows.UI.Xaml.Data.RelativeSource") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Data::RelativeSource>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Xaml.DataTemplate") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::DataTemplate>::Class());
		}
		else if (path == "Windows.UI.Xaml.DependencyObject") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::DependencyObject>::Class());
		}
		else if (path == "Windows.UI.Xaml.DependencyProperty") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::DependencyProperty>::Class());
		}
		else if (path == "Windows.UI.Xaml.DependencyPropertyChangedEventArgs") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::DependencyPropertyChangedEventArgs>::Class());
		}
		else if (path == "Windows.UI.Xaml.Documents.Inline") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Documents::Inline>::Class());
		}
		else if (path == "Windows.UI.Xaml.Documents.InlineCollection") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Documents::InlineCollection>::Class());
		}
		else if (path == "Windows.UI.Xaml.Documents.TextElement") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Documents::TextElement>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Xaml.Documents.TextPointer") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Documents::TextPointer>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Xaml.FrameworkElement") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::FrameworkElement>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Xaml.FrameworkTemplate") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::FrameworkTemplate>::Class());
		}
		else if (path == "Windows.UI.Xaml.Input.Pointer") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Input::Pointer>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Xaml.Media.Animation.NavigationTransitionInfo") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.Animation.Transition") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::Animation::Transition>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.Animation.TransitionCollection") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::Animation::TransitionCollection>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.Brush") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::Brush>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.CacheMode") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::CacheMode>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.FontFamily") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::FontFamily>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.GeneralTransform") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::GeneralTransform>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.Geometry") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::Geometry>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.Projection") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::Projection>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.RectangleGeometry") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::RectangleGeometry>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.SolidColorBrush") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::SolidColorBrush>::Class());
		}
		else if (path == "Windows.UI.Xaml.Media.Transform") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Media::Transform>::Class());
		}
		else if (path == "Windows.UI.Xaml.Navigation.PageStackEntry") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Navigation::PageStackEntry>::Class());
		}
		else if (path == "Windows.UI.Xaml.PropertyChangedCallback") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::PropertyChangedCallback>::Class());
		}
		else if (path == "Windows.UI.Xaml.PropertyMetadata") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::PropertyMetadata>::Class());
		}
		else if (path == "Windows.UI.Xaml.PropertyPath") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::PropertyPath>::Class());
		}
		else if (path == "Windows.UI.Xaml.ResourceDictionary") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::ResourceDictionary>::Class());
		}
		else if (path == "Windows.UI.Xaml.RoutedEvent") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::RoutedEvent>::Class());
		}
		else if (path == "Windows.UI.Xaml.SetterBase") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::SetterBase>::Class());
		}
		else if (path == "Windows.UI.Xaml.SetterBaseCollection") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::SetterBaseCollection>::Class());
		}
		else if (path == "Windows.UI.Xaml.Style") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Style>::Class());
		}
		else if (path == "Windows.UI.Xaml.TriggerBase") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::TriggerBase>::Class());
		}
		else if (path == "Windows.UI.Xaml.TriggerCollection") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::TriggerCollection>::Class());
		}
		else if (path == "Windows.UI.Xaml.UIElement") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::UIElement>::Class());
			registerEnums(context, path);
		}
		else if (path == "Windows.UI.Xaml.Window") {
			instantiated = context.CreateObject(JSExport<::Titanium::Windows::UI::Xaml::Window>::Class());
		}
		else {
			return context.CreateUndefined();
		}
		// END_SWITCH

		registerValue(context, path, instantiated);

		return static_cast<JSValue>(instantiated);
	}

	JSObject WindowsNativeModuleLoader::wrapNativeUI(const JSContext& context, const JSObject& object)
	{
		auto ui_element_wrapper = object.GetPrivate<::Titanium::Windows::UI::Xaml::UIElement>();
		auto element = ui_element_wrapper->unwrapWindows_UI_Xaml_UIElement();
		auto wrapped = context.CreateObject(JSExport<::TitaniumWindows::UI::UIElement>::Class());
		// ok we have a wrapper View subclass, but we need to instantiate an instance as constructor!
		auto constructed = wrapped.CallAsConstructor();
		auto blah = constructed.GetPrivate<::TitaniumWindows::UI::UIElement>();
		blah->setComponent(dynamic_cast<Windows::UI::Xaml::FrameworkElement^>(element));
		return constructed;
	}

}  // namespace TitaniumWindows

