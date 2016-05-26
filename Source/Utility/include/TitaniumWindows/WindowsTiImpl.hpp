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

#define TITANIUMWINDOWS_EXCEPTION_CATCH_END \
catch (::Platform::COMException^ ex) { \
    std::ostringstream os; \
    os << "Runtime Error: " << TitaniumWindows::Utility::ConvertString(ex->Message); \
    Titanium::Module::ShowRedScreenOfDeath(get_context(), os.str()); \
} TITANIUM_EXCEPTION_CATCH_END

#endif  // _TITANIUMWINDOWS_WINDOWSTIIMPL_HPP_
