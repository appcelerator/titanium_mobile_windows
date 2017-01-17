/**
 * ListModel
 *
 * Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#ifndef _TITANIUM_LISTMODEL_HPP_
#define _TITANIUM_LISTMODEL_HPP_

#include "Titanium/detail/TiBase.hpp"
#include <vector>
#include <tuple>

namespace Titanium
{
	namespace UI
	{
		/*!
		  @struct
		  @discussion Used to store search results for TableView/ListView
		*/
		struct ListRowSearchResult
		{
			bool found { false };
			std::uint32_t sectionIndex { 0 };
			std::uint32_t rowIndex { 0 };
		};

		/*!
		  @class
		  @discussion This is the model for TableView/ListView
		*/
		template<typename T>
		class ListModel
		{
		public:

			ListModel(const bool& hasHeader = true) TITANIUM_NOEXCEPT
			{
				hasHeader__ = hasHeader;
			}

			/*!
			  @method
			  @abstract searchRowBySelectedIndex
			  @discussion Locate row and section from selected index
			*/
			ListRowSearchResult searchRowBySelectedIndex(const std::uint32_t& selectedIndex) const TITANIUM_NOEXCEPT
			{
				ListRowSearchResult result;

				// If this model is filtered, we need to search for the "original" data.
				// In this case there's only one section
				if (isSaved()) {
					const auto filteredIndex = selectedIndex - (hasHeader__ ? 1 : 0);
					if (saved_positions__.size() > filteredIndex) {
						// Search index from the saved position
						const auto pos = saved_positions__.at(filteredIndex);
						result.found = true;
						result.sectionIndex = std::get<0>(pos);
						result.rowIndex = std::get<1>(pos);
					}
					return result;
				}

				std::uint32_t sectionIndex = 0;
				std::uint32_t totalItemCount = offset__;

				for (sectionIndex = 0; sectionIndex < sections__.size(); sectionIndex++) {
					const auto section = sections__.at(sectionIndex);
					const auto itemCount = section->get_itemCount();
					const auto rowCountIncludingHeader = itemCount + (section->hasHeader() ? 1 : 0) + (section->hasFooter() ? 1 : 0);
					totalItemCount += rowCountIncludingHeader;
					if (totalItemCount <= selectedIndex) {
						// we just count the total item
						continue;
					} else if (section->hasHeader() && selectedIndex == 0) {
						// that's a first header
						break;
					} else if (section->hasHeader() && totalItemCount == selectedIndex) {
						// this indicates header is selected
						sectionIndex++;
						break;
					} else {
						// this indicates selected index is in this section
						result.rowIndex = selectedIndex - (totalItemCount - rowCountIncludingHeader) - (section->hasHeader() ? 1 : 0);
						if (result.rowIndex >= itemCount) {
							if (section->hasFooter()) {
								// this indicates footer is selected
								break;
							}
						} else {
							result.found = true;
							break;
						}
					}
				}

				result.sectionIndex = sectionIndex;
				return result;
			}

			/*!
			  @method
			  @abstract save
			  @discussion Save model data
			*/
			void save() TITANIUM_NOEXCEPT
			{
				saved_sections__ = sections__;
				saved_positions__.clear();
			}

			/*!
			  @method
			  @abstract save_positions
			  @discussion Save original position for filtered items
			  @param saved_positions Maps filtered index to original position: row index -> (section index, row index)
			*/
			void save_positions(const std::vector<std::tuple<size_t, size_t>> saved_positions) TITANIUM_NOEXCEPT
			{
				saved_positions__ = saved_positions;
			}

			/*!
			  @method
			  @abstract isSaved
			  @discussion Determines if model is saved
			*/
			bool isSaved() const TITANIUM_NOEXCEPT
			{
				return !saved_sections__.empty();
			}

			/*!
			  @method
			  @abstract restore
			  @discussion Restore saved model
			*/
			void restore() TITANIUM_NOEXCEPT
			{
				sections__ = saved_sections__;
				saved_sections__ = std::vector<std::shared_ptr<T>>();
				saved_positions__.clear();
			}

			/*!
			  @method
			  @abstract empty
			  @discussion Determines if model is empty
			*/
			bool empty()
			{
				return sections__.empty();
			}

			/*!
			  @method
			  @abstract clear
			  @discussion Clear model data
			*/
			void clear() TITANIUM_NOEXCEPT
			{
				sections__.clear();
				saved_sections__.clear();
				saved_positions__.clear();
			}

			/*!
			  @method
			  @abstract set_section
			  @discussion Set model data
			*/
			void set_sections(const std::vector<std::shared_ptr<T>>& sections) TITANIUM_NOEXCEPT
			{
				sections__ = sections;
			}

			/*!
			  @method
			  @abstract get_section
			  @discussion Get model data
			*/
			std::vector<std::shared_ptr<T>> get_sections() const TITANIUM_NOEXCEPT
			{
				return sections__;
			}

			/*!
			  @method
			  @abstract get_sectionCount
			  @discussion Get number of sections
			*/
			std::uint32_t get_sectionCount()
			{
				return static_cast<std::uint32_t>(sections__.size());
			}

			/*!
			  @method
			  @abstract get_savedSectionCount
			  @discussion Get number of saved sections
			*/
			std::uint32_t get_savedSectionCount()
			{
				return static_cast<std::uint32_t>(saved_sections__.size());
			}

			/*!
			  @method
			  @abstract get_saved_sections
			  @discussion Get saved model
			*/
			std::vector<std::shared_ptr<T>> get_saved_sections() const TITANIUM_NOEXCEPT
			{
				return saved_sections__;
			}

			/*!
			  @method
			  @abstract first
			  @discussion Get first item
			*/
			std::shared_ptr<T> first() const TITANIUM_NOEXCEPT
			{
				return sections__.at(0);
			}

			/*!
			  @method
			  @abstract appendSection
			  @discussion Appends an array of sections to the end of the list.
			*/
			void appendSection(const std::vector<std::shared_ptr<T>>& sections) TITANIUM_NOEXCEPT
			{
				for (const auto section : sections) {
					sections__.push_back(section);
				}
			}

			/*!
			  @method
			  @abstract appendSection
			  @discussion Appends a single section to the end of the list.
			*/
			void appendSection(const std::shared_ptr<T>& section) TITANIUM_NOEXCEPT
			{
				sections__.push_back(section);
			}

			/*!
			  @method
			  @abstract deleteSectionAt
			  @discussion Deletes an existing section.
			*/
			void deleteSectionAt(const uint32_t& sectionIndex) TITANIUM_NOEXCEPT
			{
				sections__.erase(sections__.begin() + sectionIndex);
			}

			/*!
			  @method
			  @abstract insertSectionAt
			  @discussion Inserts a section or an array of sections at a specific index.
			*/
			void insertSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<T>>& section) TITANIUM_NOEXCEPT
			{
				sections__.insert(sections__.begin() + sectionIndex, section.begin(), section.end());
			}

			/*!
			  @method
			  @abstract insertSectionBefore
			  @discussion Inserts a section or an array of sections before a specific index.
			*/
			void insertSectionBefore(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<T>>& section) TITANIUM_NOEXCEPT
			{
				insertSectionAt(sectionIndex, section);
			}

			/*!
			  @method
			  @abstract insertSectionAfter
			  @discussion Inserts a section or an array of sections after a specific index.
			*/
			void insertSectionAfter(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<T>>& section) TITANIUM_NOEXCEPT
			{
				sections__.insert(sections__.begin() + sectionIndex + 1, section.begin(), section.end());
			}

			/*!
			  @method
			  @abstract updateSection
			  @discussion Update section at a specific index.
			*/
			void updateSection(const uint32_t& sectionIndex, const std::shared_ptr<T>& section) TITANIUM_NOEXCEPT
			{
				sections__.at(sectionIndex) = section;
			}

			/*!
			  @method
			  @abstract replaceSectionAt
			  @discussion Replaces an existing section.
			*/
			void replaceSectionAt(const uint32_t& sectionIndex, const std::vector<std::shared_ptr<T>>& sections) TITANIUM_NOEXCEPT
			{
				sections__.erase(sections__.begin() + sectionIndex, sections__.begin() + sectionIndex + sections.size());
				sections__.insert(sections__.begin() + sectionIndex, sections.begin(), sections.end());
			}

			/*!
			  @method
			  @abstract getSectionAtIndex
			  @discussion Get section at a specific index
			*/
			std::shared_ptr<T> getSectionAtIndex(const uint32_t& sectionIndex) const TITANIUM_NOEXCEPT
			{
				TITANIUM_ASSERT(sections__.size() > sectionIndex);
				return sections__.at(sectionIndex);
			}

			/*!
			  @method
			  @abstract getFilteredSectionAtIndex
			  @discussion Get section at a specific index. Returns "original" data when it's filtered
			*/
			std::shared_ptr<T> getFilteredSectionAtIndex(const uint32_t& sectionIndex) const TITANIUM_NOEXCEPT
			{
				if (isSaved()) {
					TITANIUM_ASSERT(saved_sections__.size() > sectionIndex);
					return saved_sections__.at(sectionIndex);
				}
				return getSectionAtIndex(sectionIndex);
			}

			/*!
			  @method
			  @abstract getSectionIndex
			  @discussion Return section index from section
			*/
			std::int32_t getSectionIndex(const std::shared_ptr<T>& section) const TITANIUM_NOEXCEPT
			{
				const auto pos = std::find(sections__.begin(), sections__.end(), section);
				if (pos == sections__.end()) {
					return -1;
				}
				return std::distance(sections__.begin(), pos);
			}

			/*!
			  @method
			  @abstract set_offset
			  @discussion Set offset to search index
			*/
			void set_offset(const std::uint32_t& offset) TITANIUM_NOEXCEPT
			{
				offset__ = offset;
			}

		protected:
			std::uint32_t offset__ { 0 };
			std::vector<std::shared_ptr<T>> saved_sections__;
			std::vector<std::shared_ptr<T>> sections__;
			bool hasHeader__;

			// For storing original position for filtered items
			std::vector<std::tuple<size_t, size_t>> saved_positions__;
		};
 	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_LISTMODEL_HPP_
