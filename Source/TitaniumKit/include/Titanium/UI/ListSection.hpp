/**
 * TitaniumKit Titanium.UI.ListSection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_LISTSECTION_HPP_
#define _TITANIUM_UI_LISTSECTION_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UIModule.hpp"
#include "Titanium/UI/ListViewAnimationProperties.hpp"

namespace Titanium
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @struct
		  @discussion An abstract datatype for specifying an item data.
  		  This is an abstract type. Any object meeting this description can be used where this type is used.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/ListDataItem
		*/
		struct ListDataItem {
			// Contains key-value pairs of properties and values that are applied to the ListItem.
			std::unordered_map<std::string, JSValue> properties;
			// Template ID configured with the ListView.templates property
			std::string templateId;
			// Contains key-value pairs of properties and values that are applied to the custom property binding
			std::unordered_map<std::string, JSValue> bindings;
		};

		// Convert JSObject into ListDataItem
		ListDataItem js_to_ListDataItem(const JSObject& object);
		JSObject ListDataItem_to_js(const JSContext& js_context, const ListDataItem& item);

		/*!
		  @class
		  @discussion This is the Titanium ListSection Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.ListSection
		*/
		class TITANIUMKIT_EXPORT ListSection : public Module, public JSExport<ListSection>
		{

		public:

			/*!
			  @property
			  @abstract footerTitle
			  @discussion Title of this section footer.
			*/
			virtual std::string get_footerTitle() const TITANIUM_NOEXCEPT;
			virtual void set_footerTitle(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract footerView
			  @discussion View to use for this section footer.
			*/
			virtual JSValue get_footerView() const TITANIUM_NOEXCEPT;
			virtual void set_footerView(const JSValue& value) TITANIUM_NOEXCEPT;
			virtual void footerView_set_notify(View& view); // for subclass

			/*!
			  @property
			  @abstract headerTitle
			  @discussion Title of this section header.
			*/
			virtual std::string get_headerTitle() const TITANIUM_NOEXCEPT;
			virtual void set_headerTitle(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract headerView
			  @discussion View to use for this section header.
			*/
			virtual JSValue get_headerView() const TITANIUM_NOEXCEPT;
			virtual void set_headerView(const JSValue& value) TITANIUM_NOEXCEPT;
			virtual void headerView_set_notify(View& view); // for subclass

			/*!
			  @property
			  @abstract items
			  @discussion Items of this list section.
			*/
			virtual std::vector<ListDataItem> get_items() const TITANIUM_NOEXCEPT;
			virtual void set_items(const std::vector<ListDataItem>& items) TITANIUM_NOEXCEPT;
			virtual void items_set_notify(size_t index, size_t count); // for subclass

			/*!
			  @method
			  @abstract setItems
			  @discussion Sets the data entries in the list section.
			*/
			virtual void setItems(const std::vector<ListDataItem>& dataItems, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract appendItems
			  @discussion Appends the data entries to the end of the list section.
			*/
			virtual void appendItems(const std::vector<ListDataItem>& dataItems, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract insertItemsAt
			  @discussion Inserts data entries to the list section at the specified index.
			*/
			virtual void insertItemsAt(uint32_t itemIndex, const std::vector<ListDataItem>& dataItems, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract replaceItemsAt
			  @discussion Removes count entries from the list section at the specified index,then inserts data entries to the list section at the same index.
			*/
			virtual void replaceItemsAt(uint32_t index, uint32_t count, const std::vector<ListDataItem>& dataItems, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract deleteItemsAt
			  @discussion Removes count entries from the list section at the specified index.
			*/
			virtual void deleteItemsAt(uint32_t itemIndex, uint32_t count, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract getItemAt
			  @discussion Returns the item entry from the list view at the specified index.
			*/
			virtual ListDataItem getItemAt(uint32_t itemIndex) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract updateItemAt
			  @discussion Updates an item at the specified index.
			*/
			virtual void updateItemAt(uint32_t index, const ListDataItem& dataItem, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT;

			ListSection(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~ListSection() = default;
			ListSection(const ListSection&) = default;
			ListSection& operator=(const ListSection&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ListSection(ListSection&&)                 = default;
			ListSection& operator=(ListSection&&)      = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_get_footerTitle() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_footerTitle(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_footerView() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_footerView(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_headerTitle() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_headerTitle(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_headerView() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_headerView(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_items() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_items(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setItems(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_appendItems(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_insertItemsAt(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_replaceItemsAt(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_deleteItemsAt(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getItemAt(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_updateItemAt(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getFooterTitle(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setFooterTitle(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getFooterView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setFooterView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getHeaderTitle(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setHeaderTitle(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getHeaderView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setHeaderView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getItems(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string footerTitle__;
			std::string headerTitle__;
			JSValue footerView__;
			JSValue headerView__;
			std::vector<ListDataItem> items__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_LISTSECTION_HPP_