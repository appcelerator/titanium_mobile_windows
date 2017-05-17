/**
 * Windows specific macros for implementation
 *
 * Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_WINDOWSTIIMPL_HPP_
#define _TITANIUMWINDOWS_WINDOWSTIIMPL_HPP_

#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/Utility.hpp"


#define TITANIUMWINDOWS_EXCEPTION_SHOW_REDSCREEN(EX, CTX) \
    std::ostringstream os; \
    os << "Runtime Error: " << TitaniumWindows::Utility::ConvertString(EX->Message); \
    Titanium::Module::ShowRedScreenOfDeath(CTX, os.str()); \

#define TITANIUMWINDOWS_EXCEPTION_CATCH_END_CTX(CTX) \
catch (::Platform::Exception^ ex) { \
	TITANIUMWINDOWS_EXCEPTION_SHOW_REDSCREEN(ex, CTX); \
} TITANIUM_EXCEPTION_CATCH_END_CTX(CTX)

#define TITANIUMWINDOWS_EXCEPTION_CATCH_END TITANIUMWINDOWS_EXCEPTION_CATCH_END_CTX(get_context())

#endif  // _TITANIUMWINDOWS_WINDOWSTIIMPL_HPP_
