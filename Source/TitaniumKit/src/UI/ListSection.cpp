/**
 * TitaniumKit Titanium.UI.ListSection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ListSection.hpp"

namespace Titanium
{
	namespace UI
	{

		// TODO: move to utility class
		static std::unordered_map<std::string, JSValue> js_to_dictionary(const JSObject& js_dictionary) 
		{
			std::unordered_map<std::string, JSValue> dictionary;
			for (const auto& name : static_cast<std::vector<JSString>>(js_dictionary.GetPropertyNames())) {
				dictionary.emplace(name, js_dictionary.GetProperty(name));
			}
			return dictionary;
		}

		static JSObject dictionary_to_js(const JSContext& js_context, const std::unordered_map<std::string, JSValue>& dictionary) 
		{
			auto js_dictionary = js_context.CreateObject();
			for (auto kv : dictionary) {
				js_dictionary.SetProperty(kv.first, kv.second);
			}
			return js_dictionary;
		}

		ListDataItem js_to_ListDataItem(const JSObject& object)
		{
			ListDataItem item;

			auto properties = object.GetProperty("properties");
			if (properties.IsObject()) {
				item.properties = js_to_dictionary(static_cast<JSObject>(properties));
			} else {
				TITANIUM_LOG_WARN("Failed to process ListDataItem.properties: Not a JSObject");
			}
			item.templateId = static_cast<std::string>(object.GetProperty("template"));

			// collect all binding properties
			for (const auto& name : static_cast<std::vector<JSString>>(object.GetPropertyNames())) {
				if (name == "properties" || name == "templates") {
					continue;
				}
				item.bindings.emplace(name, object.GetProperty(name));
			}
			return item;
		}

		JSObject ListDataItem_to_js(const JSContext& js_context, const ListDataItem& item)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("template", js_context.CreateString(item.templateId));
			object.SetProperty("properties", dictionary_to_js(js_context, item.properties));
			for (auto kv : item.bindings) {
				object.SetProperty(kv.first, kv.second);
			}
			return object;
		}

		static std::vector<ListDataItem> js_to_ListDataItem_array(const JSObject& js_array)
		{
			std::vector<ListDataItem> items;
			const auto length = static_cast<uint32_t>(js_array.GetProperty("length"));
			for (uint32_t i = 0; i < length; i++) {
				auto value = js_array.GetProperty(i);
				if (value.IsObject()) {
					items.push_back(js_to_ListDataItem(static_cast<JSObject>(value)));
				} else {
					TITANIUM_LOG_WARN("Failed to process ListDataItem: Not a JSObject");
				}
			}
			return items;
		}

		static JSValue ListDataItem_array_to_js(const JSContext& js_context, const std::vector<ListDataItem>& items)
		{
			std::vector<JSValue> js_items;
			for (auto & item : items) {
				js_items.push_back(ListDataItem_to_js(js_context, item));
			}
			return js_context.CreateArray(js_items);
		}

		ListSection::ListSection(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context, arguments),
			footerTitle__(""),
			headerTitle__(""),
			headerView__(js_context.CreateNull()),
			footerView__(js_context.CreateNull())
		{
		}

		std::string ListSection::get_footerTitle() const TITANIUM_NOEXCEPT
		{
			return footerTitle__;
		}

		void ListSection::set_footerTitle(const std::string& value) TITANIUM_NOEXCEPT
		{
			footerTitle__ = value;
		}

		JSValue ListSection::get_footerView() const TITANIUM_NOEXCEPT
		{
			return footerView__;
		}

		void ListSection::set_footerView(const JSValue& value) TITANIUM_NOEXCEPT
		{
			footerView__ = value;
			if (footerView__.IsObject()) {
				auto view = static_cast<JSObject>(footerView__).GetPrivate<Titanium::UI::View>();
				if (view != nullptr) {
					footerView_set_notify(*view);
				}
			}
		}

		std::string ListSection::get_headerTitle() const TITANIUM_NOEXCEPT
		{
			return headerTitle__;
		}

		void ListSection::set_headerTitle(const std::string& value) TITANIUM_NOEXCEPT
		{
			headerTitle__ = value;
		}

		JSValue ListSection::get_headerView() const TITANIUM_NOEXCEPT
		{
			return headerView__;
		}

		void ListSection::set_headerView(const JSValue& value) TITANIUM_NOEXCEPT
		{
			headerView__ = value;
			
			if (headerView__.IsObject()) {
				auto view = static_cast<JSObject>(headerView__).GetPrivate<Titanium::UI::View>();
				if (view != nullptr) {
					headerView_set_notify(*view);
				}
			}
		}

		std::vector<ListDataItem> ListSection::get_items() const TITANIUM_NOEXCEPT
		{
			return items__;
		}

		void ListSection::set_items(const std::vector<ListDataItem>& value) TITANIUM_NOEXCEPT
		{
			items__ = value;
			items_set_notify(0, items__.size());
		}

		void ListSection::setItems(const std::vector<ListDataItem>& dataItems, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT
		{
			set_items(dataItems);
		}

		void ListSection::appendItems(const std::vector<ListDataItem>& dataItems, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT
		{
			items__.insert(items__.end(), dataItems.begin(), dataItems.end());
			items_set_notify(items__.size(), dataItems.size());
		}

		void ListSection::insertItemsAt(uint32_t index, const std::vector<ListDataItem>& dataItems, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT
		{
			items__.insert(items__.begin() + index, dataItems.begin(), dataItems.end());
			items_set_notify(index, dataItems.size());
		}

		void ListSection::replaceItemsAt(uint32_t index, uint32_t count, const std::vector<ListDataItem>& dataItems, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT
		{
			items__.erase (items__.begin() + index, items__.begin() + index + count);
			items__.insert(items__.begin() + index, dataItems.begin(), dataItems.end());
			items_set_notify(index, dataItems.size());
		}

		void ListSection::deleteItemsAt(uint32_t index, uint32_t count, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT
		{
			items__.erase (items__.begin() + index, items__.begin() + index + count);
			items_set_notify(index, count);
		}

		ListDataItem ListSection::getItemAt(uint32_t index) TITANIUM_NOEXCEPT
		{
			return items__.at(index);
		}

		void ListSection::updateItemAt(uint32_t index, const ListDataItem& dataItem, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT
		{
			items__.at(index) = dataItem;
			items_set_notify(index, 1);
		}

		void ListSection::items_set_notify(size_t index, size_t count)
		{
			// for subclass
		}

		void ListSection::headerView_set_notify(View& view)
		{
			// for subclass
		}

		void ListSection::footerView_set_notify(View& view)
		{
			// for subclass
		}
		
		void ListSection::JSExportInitialize() {
			JSExport<ListSection>::SetClassVersion(1);
			JSExport<ListSection>::SetParent(JSExport<Module>::Class());

			JSExport<ListSection>::AddValueProperty("footerTitle", std::mem_fn(&ListSection::js_get_footerTitle), std::mem_fn(&ListSection::js_set_footerTitle));
			JSExport<ListSection>::AddValueProperty("footerView", std::mem_fn(&ListSection::js_get_footerView),   std::mem_fn(&ListSection::js_set_footerView));
			JSExport<ListSection>::AddValueProperty("headerTitle", std::mem_fn(&ListSection::js_get_headerTitle), std::mem_fn(&ListSection::js_set_headerTitle));
			JSExport<ListSection>::AddValueProperty("headerView", std::mem_fn(&ListSection::js_get_headerView),   std::mem_fn(&ListSection::js_set_headerView));
			JSExport<ListSection>::AddValueProperty("items", std::mem_fn(&ListSection::js_get_items),             std::mem_fn(&ListSection::js_set_items));

			JSExport<ListSection>::AddFunctionProperty("appendItems", std::mem_fn(&ListSection::js_appendItems));
			JSExport<ListSection>::AddFunctionProperty("insertItemsAt", std::mem_fn(&ListSection::js_insertItemsAt));
			JSExport<ListSection>::AddFunctionProperty("replaceItemsAt", std::mem_fn(&ListSection::js_replaceItemsAt));
			JSExport<ListSection>::AddFunctionProperty("deleteItemsAt", std::mem_fn(&ListSection::js_deleteItemsAt));
			JSExport<ListSection>::AddFunctionProperty("getItemAt", std::mem_fn(&ListSection::js_getItemAt));
			JSExport<ListSection>::AddFunctionProperty("updateItemAt", std::mem_fn(&ListSection::js_updateItemAt));
			JSExport<ListSection>::AddFunctionProperty("getFooterTitle", std::mem_fn(&ListSection::js_getFooterTitle));
			JSExport<ListSection>::AddFunctionProperty("setFooterTitle", std::mem_fn(&ListSection::js_setFooterTitle));
			JSExport<ListSection>::AddFunctionProperty("getFooterView", std::mem_fn(&ListSection::js_getFooterView));
			JSExport<ListSection>::AddFunctionProperty("setFooterView", std::mem_fn(&ListSection::js_setFooterView));
			JSExport<ListSection>::AddFunctionProperty("getHeaderTitle", std::mem_fn(&ListSection::js_getHeaderTitle));
			JSExport<ListSection>::AddFunctionProperty("setHeaderTitle", std::mem_fn(&ListSection::js_setHeaderTitle));
			JSExport<ListSection>::AddFunctionProperty("getHeaderView", std::mem_fn(&ListSection::js_getHeaderView));
			JSExport<ListSection>::AddFunctionProperty("setHeaderView", std::mem_fn(&ListSection::js_setHeaderView));
			JSExport<ListSection>::AddFunctionProperty("getItems", std::mem_fn(&ListSection::js_getItems));
			JSExport<ListSection>::AddFunctionProperty("setItems", std::mem_fn(&ListSection::js_setItems));
		}

		JSValue ListSection::js_get_footerTitle() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_footerTitle());
		}

		bool ListSection::js_set_footerTitle(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_footerTitle(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListSection::js_get_footerView() const TITANIUM_NOEXCEPT
		{
			return get_footerView();
		}

		bool ListSection::js_set_footerView(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			if (!argument.IsObject()) {
				return false;
			}
			set_footerView(argument);
			return true;
		}

		JSValue ListSection::js_get_headerTitle() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_headerTitle());
		}

		bool ListSection::js_set_headerTitle(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_headerTitle(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListSection::js_get_headerView() const TITANIUM_NOEXCEPT
		{
			return get_headerView();
		}

		bool ListSection::js_set_headerView(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			if (!argument.IsObject()) {
				return false;
			}
			set_headerView(argument);
			return true;
		}

		JSValue ListSection::js_get_items() const TITANIUM_NOEXCEPT
		{
			return ListDataItem_array_to_js(get_context(), get_items());
		}

		bool ListSection::js_set_items(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			if (!argument.IsObject()) {
				return false;
			}
			const auto items = static_cast<JSObject>(argument);
			if (!items.IsArray()) {
				return false;
			}
			set_items(js_to_ListDataItem_array(items));
			return true;
		}

		JSValue ListSection::js_setItems(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				ListViewAnimationProperties animation;
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());

				const auto dataItems = js_to_ListDataItem_array(static_cast<JSObject>(_0));

				if (arguments.size() >= 2) {
					const auto _1 = arguments.at(1);
					if (_1.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_1));
					}
				}
				setItems(dataItems, animation);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_appendItems(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				ListViewAnimationProperties animation;
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				const auto dataItems = js_to_ListDataItem_array(static_cast<JSObject>(_0));

				if (arguments.size() >= 2) {
					const auto _1 = arguments.at(1);
					if (_1.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_1));
					}
				}
				appendItems(dataItems, animation);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_insertItemsAt(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 2) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsObject());

				ListViewAnimationProperties animation;
				const auto itemIndex = static_cast<uint32_t>(_0);
				const auto dataItems = js_to_ListDataItem_array(static_cast<JSObject>(_1));

				if (arguments.size() >= 3) {
					const auto _2 = arguments.at(2);
					if (_2.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_2));
					}
				}
				insertItemsAt(itemIndex, dataItems, animation);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_replaceItemsAt(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 3) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsNumber());
				const auto _2 = arguments.at(2);
				TITANIUM_ASSERT(_2.IsObject());

				ListViewAnimationProperties animation;
				const auto index = static_cast<uint32_t>(_0);
				const auto count = static_cast<uint32_t>(_1);
				const auto dataItems = js_to_ListDataItem_array(static_cast<JSObject>(_2));

				if (arguments.size() >= 4) {
					const auto _3 = arguments.at(3);
					if (_3.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_3));
					}
				}

				replaceItemsAt(index, count, dataItems, animation);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_deleteItemsAt(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ListSection.deleteItemsAt is not implemented yet");

			if (arguments.size() >= 2) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsNumber());

				ListViewAnimationProperties animation;
				const auto itemIndex = static_cast<uint32_t>(_0);
				const auto count = static_cast<uint32_t>(_1);

				if (arguments.size() >= 3) {
					const auto _2 = arguments.at(2);
					if (_2.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_2));
					}
				}
				deleteItemsAt(itemIndex, count, animation);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_getItemAt(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto itemIndex = static_cast<uint32_t>(_0);
				return ListDataItem_to_js(get_context(), getItemAt(itemIndex));
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_updateItemAt(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 2) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsObject());

				ListViewAnimationProperties animation;
				const auto index    = static_cast<double>(_0);
				const auto dataItem = js_to_ListDataItem(static_cast<JSObject>(_1));

				if (arguments.size() >= 3) {
					const auto _2 = arguments.at(2);
					if (_2.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_2));
					}
				}

				updateItemAt(index, dataItem, animation);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_getFooterTitle(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_footerTitle();
		}

		JSValue ListSection::js_setFooterTitle(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_footerTitle(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_getFooterView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_footerView();
		}

		JSValue ListSection::js_setFooterView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_footerView(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_getHeaderTitle(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_headerTitle();
		}

		JSValue ListSection::js_setHeaderTitle(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_headerTitle(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_getHeaderView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_headerView();
		}

		JSValue ListSection::js_setHeaderView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_headerView(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue ListSection::js_getItems(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_items();
		}

	} // namespace UI
} // namespace Titanium