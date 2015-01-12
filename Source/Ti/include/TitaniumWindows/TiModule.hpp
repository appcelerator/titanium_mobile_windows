/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_TIMODULE_HPP_
#define _TITANIUMWINDOWS_TIMODULE_HPP_

#include "TitaniumWindows/detail/TiModuleBase.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class

	  @discussion This is the top-level Titanium module implementation for Windows.
	  */
	class TITANIUMWINDOWS_TI_EXPORT TiModule final : public Titanium::TiModule, public JSExport<TiModule>
	{
	   public:
		TiModule(const JSContext& js_context) TITANIUM_NOEXCEPT;
		TiModule(const TiModule&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

		virtual ~TiModule();
		TiModule(const TiModule&) = default;
		TiModule& operator=(const TiModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		TiModule(TiModule&&) = default;
		TiModule& operator=(TiModule&&) = default;
#endif

		static void JSExportInitialize();

	   protected:
		virtual std::string version() const TITANIUM_NOEXCEPT override final;
		virtual std::string buildDate() const TITANIUM_NOEXCEPT override final;
		virtual std::string buildHash() const TITANIUM_NOEXCEPT override final;

	   private:
	};

}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_TIMODULE_HPP_
