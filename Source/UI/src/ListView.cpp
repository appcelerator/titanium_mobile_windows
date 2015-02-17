/**
 * Titanium.UI.ListView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/ListView.hpp"
#include <collection.h>

namespace TitaniumWindows
{
	namespace UI
	{

		ListView::ListView(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::UI::ListView(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("ListView::ctor Initialize");

			listview__ = ref new Windows::UI::Xaml::Controls::ListView();

			collectionViewSource__ = ref new Windows::UI::Xaml::Data::CollectionViewSource();
			collectionViewItems__  = ref new ::Platform::Collections::Vector<::Platform::Object^>();
			collectionViewSource__->Source = collectionViewItems__;
			collectionViewSource__->IsSourceGrouped = true;

			auto binding = ref new Windows::UI::Xaml::Data::Binding();
			binding->Source = collectionViewSource__;
			Windows::UI::Xaml::Data::BindingOperations::SetBinding(listview__, Windows::UI::Xaml::Controls::ListView::ItemsSourceProperty, binding);

			setDefaultHeight(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
			setDefaultWidth(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));

			setComponent(listview__);
		}

		void ListView::JSExportInitialize() {
			JSExport<ListView>::SetClassVersion(1);
			JSExport<ListView>::SetParent(JSExport<Titanium::UI::ListView>::Class());
		}

		void ListView::sections_set_notify()
		{
			collectionViewItems__->Clear();
			
			for (int i = 0; i < get_sectionCount(); i++) {
				auto v = createSectionViewAt(i);
				auto group = ref new ::Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>();
				for (int j = 0; j < v.size(); j++) {
					group->Append(v.at(j).GetPrivate<TitaniumWindows::UI::ViewBase>()->getComponent()); // TIMOB-18422 FIXME
				}
				collectionViewItems__->Append(group);
			}
		}

	}  // namespace UI
}  // namespace TitaniumWindows