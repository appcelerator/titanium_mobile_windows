/**
 * Titanium.UI.Notification for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_NOTIFICATION_HPP_
#define _TITANIUMWINDOWS_UI_NOTIFICATION_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/Notification.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.Notification implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT Notification final : public Titanium::UI::Notification, public JSExport<Notification>
		{

		public:
			
			Notification(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~Notification()                      = default;
			Notification(const Notification&)            = default;
			Notification& operator=(const Notification&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Notification(Notification&&)                 = default;
			Notification& operator=(Notification&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void show() TITANIUM_NOEXCEPT override;
		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_UI_NOTIFICATION_HPP_