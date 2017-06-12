/**
 * TitaniumKit Titanium.UI.ListView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_LISTVIEW_HPP_
#define _TITANIUM_UI_LISTVIEW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/ListSection.hpp"
#include "Titanium/UI/ListViewMarkerProps.hpp"
#include "Titanium/UI/ListModel.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <vector>
#include <unordered_map>
#include <tuple>

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		class ListViewAnimationProperties;
		class SearchBar;

		/*!
		  @class
		  @discussion This is the Titanium.UI.ListView Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.ListView
		*/
		class TITANIUMKIT_EXPORT ListView : public View, public JSExport<ListView>
		{

		public:

			/*!
			  @property
			  @abstract sections
			  @discussion Sections of this list.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::shared_ptr<ListSection>>, sections);

			/*
			 * Create views for the section at given index
			 */
			template<typename T>
			std::vector<std::shared_ptr<T>> createSectionViewAt(const uint32_t& index)
			{
				// lazy loading
				loadJS();
				
				std::vector<std::shared_ptr<T>> items;
				const std::vector<JSValue> args { get_object(), model__->getSectionAtIndex(index)->get_object() };
				JSValue result = sectionViewCreateFunction__(args, ti_listview_exports__);
				TITANIUM_ASSERT(result.IsObject());
				auto js_items = static_cast<JSObject>(result);
				TITANIUM_ASSERT(js_items.IsArray());
				
				const auto length = static_cast<uint32_t>(js_items.GetProperty("length"));
				for (uint32_t i = 0; i < length; i++) {
					items.push_back(static_cast<JSObject>(js_items.GetProperty(i)).GetPrivate<T>());
				}
				
				return items;
			}

			template<typename T>
			std::shared_ptr<T> createSectionItemViewAt(const std::uint32_t& sectionIndex, const uint32_t& itemIndex) {
				loadJS();
				const auto section = model__->getSectionAtIndex(sectionIndex);
				const auto item = section->getItemAt(itemIndex);			
				const std::vector<JSValue> args { get_object(), section->get_object(), ListDataItem_to_js(get_context(), item) };
				JSValue js_view = sectionViewItemCreateFunction__(args, ti_listview_exports__);
				TITANIUM_ASSERT(js_view.IsObject());
				return static_cast<JSObject>(js_view).GetPrivate<T>();
			}

			/*!
			  @property
			  @abstract footerTitle
			  @discussion List view footer title.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, footerTitle);

			/*!
			  @property
			  @abstract headerTitle
			  @discussion List view header title.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, headerTitle);
			
			/*!
			 @property
			 @abstract footerView
			 @discussion List view footer as a view that will be rendered instead of a label.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<View>, footerView);
			
			/*!
			 @property
			 @abstract headerView
			 @discussion List view header as a view that will be rendered instead of a label.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<View>, headerView);
			
			/*!
			 @property
			 @abstract searchView
			 @discussion Search field to use for the list view.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<SearchBar>, searchView);

			/*!
			  @property
			  @abstract searchText
			  @discussion The string to use as the search parameter.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, searchText);

			/*!
			  @property
			  @abstract caseInsensitiveSearch
			  @discussion Determines if the search performed is case insensitive.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, caseInsensitiveSearch);

			/*!
			  @property
			  @abstract sectionCount
			  @discussion Number of sections in this list view.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(uint32_t, sectionCount);

			/*!
			  @property
			  @abstract showVerticalScrollIndicator
			  @discussion Determines whether this list view displays a vertical scroll indicator.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, showVerticalScrollIndicator);

			/*!
			  @property
			  @abstract separatorColor
			  @discussion Separator line color between rows, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, separatorColor);

			/*!
			  @property
			  @abstract defaultItemTemplate
			  @discussion Sets the default template for list data items that do not specify the `template` property.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, defaultItemTemplate);

			/*!
			  @method
			  @abstract scrollToItem
			  @discussion Scrolls to a specific item.
			*/
			virtual void scrollToItem(const uint32_t& sectionIndex, const uint32_t& itemIndex, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract appendSection
			  @discussion Appends a single section or an array of sections to the end of the list.
			*/
			virtual void appendSection(const std::vector<std::shared_ptr<ListSection>>& section, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract deleteSectionAt
			  @discussion Deletes an existing section.
			*/
			virtual void deleteSectionAt(const uint32_t& sectionIndex, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract insertSectionAt
			  @discussion Inserts a section or an array of sections at a specific index.
			*/
			virtual void insertSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<ListSection>>& section, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract replaceSectionAt
			  @discussion Replaces an existing section.
			*/
			virtual void replaceSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<ListSection>>& section, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract setMarker
			  @discussion Sets a reference item in the list view.
			*/
			virtual void setMarker(const ListViewMarkerProps& marker) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract addMarker
			  @discussion Adds a reference item in the list view.
			*/
			virtual void addMarker(const ListViewMarkerProps& marker) TITANIUM_NOEXCEPT;

			ListView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ListView() = default;
			ListView(const ListView&) = default;
			ListView& operator=(const ListView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ListView(ListView&&)                 = default;
			ListView& operator=(ListView&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(sections);
			TITANIUM_PROPERTY_DEF(footerTitle);
			TITANIUM_PROPERTY_DEF(headerTitle);
			TITANIUM_PROPERTY_DEF(searchText);
			TITANIUM_PROPERTY_DEF(footerView);
			TITANIUM_PROPERTY_DEF(headerView);
			TITANIUM_PROPERTY_DEF(searchView);
			TITANIUM_PROPERTY_DEF(caseInsensitiveSearch);
			TITANIUM_PROPERTY_READONLY_DEF(sectionCount);
			TITANIUM_PROPERTY_DEF(showVerticalScrollIndicator);
			TITANIUM_PROPERTY_DEF(separatorColor);
			TITANIUM_PROPERTY_DEF(defaultItemTemplate);

			TITANIUM_FUNCTION_DEF(scrollToItem);
			TITANIUM_FUNCTION_DEF(appendSection);
			TITANIUM_FUNCTION_DEF(deleteSectionAt);
			TITANIUM_FUNCTION_DEF(insertSectionAt);
			TITANIUM_FUNCTION_DEF(replaceSectionAt);
			TITANIUM_FUNCTION_DEF(addMarker);
			TITANIUM_FUNCTION_DEF(setMarker);
			TITANIUM_FUNCTION_DEF(getTemplates);
			TITANIUM_FUNCTION_DEF(setTemplates);
			TITANIUM_FUNCTION_DEF(getSections);
			TITANIUM_FUNCTION_DEF(setSections);
			TITANIUM_FUNCTION_DEF(getFooterTitle);
			TITANIUM_FUNCTION_DEF(setFooterTitle);
			TITANIUM_FUNCTION_DEF(getFooterView);
			TITANIUM_FUNCTION_DEF(setFooterView);
			TITANIUM_FUNCTION_DEF(getHeaderTitle);
			TITANIUM_FUNCTION_DEF(setHeaderTitle);
			TITANIUM_FUNCTION_DEF(getHeaderView);
			TITANIUM_FUNCTION_DEF(setHeaderView);
			TITANIUM_FUNCTION_DEF(getSearchView);
			TITANIUM_FUNCTION_DEF(setSearchView);
			TITANIUM_FUNCTION_DEF(getSearchText);
			TITANIUM_FUNCTION_DEF(setSearchText);
			TITANIUM_FUNCTION_DEF(getCaseInsensitiveSearch);
			TITANIUM_FUNCTION_DEF(setCaseInsensitiveSearch);
			TITANIUM_FUNCTION_DEF(getSectionCount);
			TITANIUM_FUNCTION_DEF(getShowVerticalScrollIndicator);
			TITANIUM_FUNCTION_DEF(setShowVerticalScrollIndicator);
			TITANIUM_FUNCTION_DEF(getSeparatorColor);
			TITANIUM_FUNCTION_DEF(setSeparatorColor);
			TITANIUM_FUNCTION_DEF(getDefaultItemTemplate);
			TITANIUM_FUNCTION_DEF(setDefaultItemTemplate);

			void loadJS();

			// Receive all events fired from ListSection.
			// Subclass may override this to catch changes for section.
			virtual void fireListSectionEvent(const std::string& name, const std::shared_ptr<ListSection>& section, const std::uint32_t& itemIndex = 0, const std::uint32_t& itemCount = 0, const std::uint32_t& affectedRows = 0);

			/*!
			@method
			@abstract querySubmitted
			@discussion Occurs when the user submits a search query
			*/
			virtual void querySubmitted(const std::string& query);

			/*!
			@method
			@abstract suggestionRequested
			@discussion Occurs when app needs to provide new suggestions
			*/
			virtual std::vector<std::string> suggestionRequested(const std::string& query);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::shared_ptr<ListModel<ListSection>> model__;
			std::string footerTitle__;
			std::string headerTitle__;
			std::shared_ptr<View> footerView__;
			std::shared_ptr<View> headerView__;
			std::shared_ptr<SearchBar> searchView__;
			std::string searchText__;
			bool caseInsensitiveSearch__ { false };
			bool showVerticalScrollIndicator__;
			std::string separatorColor__;
			std::string defaultItemTemplate__;
			std::vector<ListViewMarkerProps> markers__;

			JSObject ti_listview_exports__;
			JSObject sectionViewCreateFunction__;
			JSObject sectionViewItemCreateFunction__;
			JSObject listviewAnimationProperties_ctor__;
#pragma warning(pop)
		};
	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_LISTVIEW_HPP_