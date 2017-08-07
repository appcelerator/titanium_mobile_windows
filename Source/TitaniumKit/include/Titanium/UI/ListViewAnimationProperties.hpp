/**
 * TitaniumKit ListViewAnimationProperties
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_LISTVIEWANIMATIONPROPERTIES_HPP_
#define _TITANIUM_UI_LISTVIEWANIMATIONPROPERTIES_HPP_

#include "Titanium/detail/TiBase.hpp"
#include "Titanium/Module.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @struct
		  @discussion This is the ListViewAnimationProperties.
		  Extend this struct to implement platform-specific properties like animation style.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/ListViewAnimationProperties
		*/
		class TITANIUMKIT_EXPORT ListViewAnimationProperties : public Module, public JSExport<ListViewAnimationProperties>
		{
		public:
			virtual bool get_animated() const TITANIUM_NOEXCEPT;
			virtual void set_animated(const bool& animated) TITANIUM_NOEXCEPT;
			virtual std::uint32_t get_position() const TITANIUM_NOEXCEPT;
			virtual void set_position(const std::uint32_t& position) TITANIUM_NOEXCEPT;

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments);

			ListViewAnimationProperties(const JSContext&) TITANIUM_NOEXCEPT;
			
			virtual ~ListViewAnimationProperties() = default;
			ListViewAnimationProperties(const ListViewAnimationProperties&) = default;
			ListViewAnimationProperties& operator=(const ListViewAnimationProperties&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ListViewAnimationProperties(ListViewAnimationProperties&&) = default;
			ListViewAnimationProperties& operator=(ListViewAnimationProperties&&) = default;
#endif
			
			static void JSExportInitialize();
		protected:
			bool animated__ {true};
			std::uint32_t position__ { 0 };
		};
		
	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_LISTVIEWANIMATIONPROPERTIES_HPP_
