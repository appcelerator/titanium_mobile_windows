/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Animation.TransitionCollection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_MEDIA_ANIMATION_TRANSITIONCOLLECTION_HPP_
#define _WINDOWS_UI_XAML_MEDIA_ANIMATION_TRANSITIONCOLLECTION_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Platform.Object.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT TransitionCollection : public ::Titanium::Platform::Object, public JSExport<TransitionCollection>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(Size);

			TITANIUM_FUNCTION_DEF(GetAt);
			TITANIUM_FUNCTION_DEF(GetView);
			TITANIUM_FUNCTION_DEF(IndexOf);
			TITANIUM_FUNCTION_DEF(SetAt);
			TITANIUM_FUNCTION_DEF(InsertAt);
			TITANIUM_FUNCTION_DEF(RemoveAt);
			TITANIUM_FUNCTION_DEF(Append);
			TITANIUM_FUNCTION_DEF(RemoveAtEnd);
			TITANIUM_FUNCTION_DEF(Clear);
			TITANIUM_FUNCTION_DEF(GetMany);
			TITANIUM_FUNCTION_DEF(ReplaceAll);
			TITANIUM_FUNCTION_DEF(First);

			TransitionCollection(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~TransitionCollection() = default;
			TransitionCollection(const TransitionCollection&) = default;
			TransitionCollection& operator=(const TransitionCollection&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TransitionCollection(TransitionCollection&&)                 = default;
			TransitionCollection& operator=(TransitionCollection&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Media::Animation::TransitionCollection^ unwrapWindows_UI_Xaml_Media_Animation_TransitionCollection() const;
			void wrap(::Windows::UI::Xaml::Media::Animation::TransitionCollection^ object);

		private:
			::Windows::UI::Xaml::Media::Animation::TransitionCollection^ unwrap() const;

		};

					} // namespace Animation
				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_MEDIA_ANIMATION_TRANSITIONCOLLECTION_HPP_
