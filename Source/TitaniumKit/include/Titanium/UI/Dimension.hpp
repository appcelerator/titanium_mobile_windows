/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_DIMENSION_HPP_
#define _TITANIUM_UI_DIMENSION_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium { namespace UI {
	
	using namespace HAL;
	
	/*!
	 @class
	 
	 @discussion This is the Titanium Dimension.
	 
	 See http://docs.appcelerator.com/titanium/latest/#!/api/Dimension
	 */
	class TITANIUMKIT_EXPORT Dimension final : public JSExportObject, public JSExport<Dimension> {
		
	public:
		
		virtual std::uint32_t get_height() const										 TITANIUM_NOEXCEPT final;
		virtual void					set_height(const std::uint32_t height) TITANIUM_NOEXCEPT final;
		
		virtual std::uint32_t get_width() const											TITANIUM_NOEXCEPT final;
		virtual void					set_width(const std::uint32_t width)	 TITANIUM_NOEXCEPT final;
		
		virtual std::uint32_t get_x() const													TITANIUM_NOEXCEPT final;
		virtual void					set_x(const std::uint32_t x)					 TITANIUM_NOEXCEPT final;
		
		virtual std::uint32_t get_y() const													TITANIUM_NOEXCEPT final;
		virtual void					set_y(const std::uint32_t y)					 TITANIUM_NOEXCEPT final;
		
		Dimension(const JSContext& js_context)														 TITANIUM_NOEXCEPT;
		Dimension(const Dimension&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
		
		virtual ~Dimension()											= default;
		Dimension(const Dimension&)							 = default;
		Dimension& operator=(const Dimension&)		= default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Dimension(Dimension&&)										= default;
		Dimension& operator=(Dimension&&)				 = default;
#endif
		
		// TODO: The following functions can automatically be generated
		// from the YAML API docs.
		static void JSExportInitialize();

		JSValue getHeightArgumentValidator() const;
		bool		setHeightArgumentValidator(const JSValue& argument);
		JSValue getWidthArgumentValidator() const;
		bool		setWidthArgumentValidator(const JSValue& argument);
		JSValue getXArgumentValidator() const;
		bool		setXArgumentValidator(const JSValue& argument);
		JSValue getYArgumentValidator() const;
		bool		setYArgumentValidator(const JSValue& argument);
		
	private:
		
		std::uint32_t height__;
		std::uint32_t width__;
		std::uint32_t x__;
		std::uint32_t y__;
		
	};
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_DIMENSION_HPP_
