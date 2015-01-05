/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_XML_HPP_
#define _TITANIUMWINDOWS_XML_HPP_

#include "TitaniumWindows/detail/XMLBase.hpp"

namespace TitaniumWindows {

  using namespace HAL;

  /*!
    @class

    @discussion This is the Titanium.XML implementation for Windows.
    */
  class TITANIUMWINDOWS_XML_EXPORT XML final : public Titanium::XML, public JSExport <XML> {

  public:

    XML(const JSContext& js_context) TITANIUM_NOEXCEPT;
    XML(const XML&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

    virtual ~XML();
    XML(const XML&)            = default;
    XML& operator=(const XML&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    XML(XML&&)                 = default;
    XML& operator=(XML&&)      = default;
#endif

    static void JSExportInitialize();

    virtual JSValue parseString_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT override;
    virtual JSValue serializeToString_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT override;

  protected:
    JSObject ti_xml;
  private:
	
  };

}  // namespace TitaniumWindows

#endif // _TITANIUMWINDOWS_XML_HPP_
