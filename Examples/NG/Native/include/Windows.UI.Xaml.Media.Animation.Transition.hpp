/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Animation.Transition
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_MEDIA_ANIMATION_TRANSITION_HPP_
#define _WINDOWS_UI_XAML_MEDIA_ANIMATION_TRANSITION_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Media
				{
					namespace Animation
					{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT Transition : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<Transition>
		{

		public:


			Transition(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Transition() = default;
			Transition(const Transition&) = default;
			Transition& operator=(const Transition&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Transition(Transition&&)                 = default;
			Transition& operator=(Transition&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Media::Animation::Transition^ unwrapWindows_UI_Xaml_Media_Animation_Transition() const;
			void wrap(::Windows::UI::Xaml::Media::Animation::Transition^ object);

		private:
			::Windows::UI::Xaml::Media::Animation::Transition^ unwrap() const;

		};

					} // namespace Animation
				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_MEDIA_ANIMATION_TRANSITION_HPP_
