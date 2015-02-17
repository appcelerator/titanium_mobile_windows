/**
 * Titanium.UI.ListView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_LISTVIEW_HPP_
#define _TITANIUMWINDOWS_UI_LISTVIEW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.ListView implementation for Windows.
		*/
// Silence 4275 about ViewBase for now. We need to merge View and ViewBase and then remove this pragma! TIMOB-18422
#pragma warning(push)
#pragma warning(disable : 4275)
		class TITANIUMWINDOWS_UI_EXPORT ListView final : public Titanium::UI::ListView, public JSExport<ListView>, public ViewBase
		{
#pragma warning(pop)
		public:
			ListView(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~ListView()                  = default;
			ListView(const ListView&)            = default;
			ListView& operator=(const ListView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ListView(ListView&&)                 = default;
			ListView& operator=(ListView&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void sections_set_notify() override;

		private:
			Windows::UI::Xaml::Controls::ListView^ listview__;
			Windows::UI::Xaml::Data::CollectionViewSource^ collectionViewSource__;
			Windows::Foundation::Collections::IObservableVector<Platform::Object^>^ collectionViewItems__;			
		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_UI_LISTVIEW_HPP_