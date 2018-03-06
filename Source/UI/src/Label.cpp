/**
* Titanium.UI.Label for Windows
*
* Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Label.hpp"
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/UI/Windows/ViewHelper.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/AttributedString.hpp"
#include "Titanium/UI/Font.hpp"
#include <unordered_map>
#include <tuple>
#include <cmath>
#include <regex>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Documents;
		using namespace Windows::UI::Text;

		Label::Label(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::Label(js_context)
		{
			TITANIUM_LOG_DEBUG("Label::ctor ", this);
		}

		Label::~Label() 
		{
			TITANIUM_LOG_DEBUG("Label::dtor ", this);
		}

		void Label::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Label::postCallAsConstructor(js_context, arguments);
			
			// Note: TextAlignment and VerticalAlignment does not work without parent container!
			border__ = ref new Controls::Border();
			label__ = ref new Windows::UI::Xaml::Controls::TextBlock();

			// default color inspection
			const auto currentBrush = dynamic_cast<Media::SolidColorBrush^>(label__->Foreground);
			if (currentBrush) {
				defaultForegroundColor__ = currentBrush->Color;
			}

			Titanium::UI::Label::setLayoutDelegate<WindowsViewLayoutDelegate>();

			label__->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
			label__->TextTrimming = Windows::UI::Xaml::TextTrimming::None;
			label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
			label__->FontSize = DefaultFontSize;

			// TIMOB-19048: max size is set to screen size by default
			const auto current = Windows::UI::Xaml::Window::Current;
			if (current) {
				label__->MaxWidth = current->Bounds.Width;
				label__->MaxHeight = current->Bounds.Height;
			}

			border__->SizeChanged += ref new Windows::UI::Xaml::SizeChangedEventHandler([this](Platform::Object^, Windows::UI::Xaml::SizeChangedEventArgs^ e) {
				try {
					if (border__->Parent) {
						const auto panel = dynamic_cast<FrameworkElement^>(border__->Parent);
						if (panel) {
							//
							// TIMOB-25385: Workaround: Skip limiting Label size when parent view is TableViewRow
							// because table view row doesn't return property width on the event for some reason.
							//
							auto skipResizing = false;
							const auto parent = get_parent();
							if (parent && parent->get_apiName() == "Ti.UI.TableViewRow") {
								skipResizing = true;
							}
							const auto layout = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
							const auto width  = panel->ActualWidth;
							const auto height = panel->ActualHeight;
							if (width > 0) {
								if (!skipResizing) {
									label__->MaxWidth = width;
								}
								if (!layout->get_right().empty()) {
									const auto ppi = WindowsViewLayoutDelegate::ComputePPI(Titanium::LayoutEngine::ValueName::Width);
									const auto rightPadding = Titanium::LayoutEngine::parseUnitValue(layout->get_right(), Titanium::LayoutEngine::ValueType::Fixed, ppi, "px");
									if (width > rightPadding) {
										label__->MaxWidth -= rightPadding;
									}
								}
							}
							if (height > 0) {
								if (!skipResizing) {
									label__->MaxHeight = height;
								}
								if (!layout->get_bottom().empty()) {
									const auto ppi = WindowsViewLayoutDelegate::ComputePPI(Titanium::LayoutEngine::ValueName::Height);
									const auto bottomPadding = Titanium::LayoutEngine::parseUnitValue(layout->get_height(), Titanium::LayoutEngine::ValueType::Fixed, ppi, "px");
									if (height > bottomPadding) {
										label__->MaxHeight -= bottomPadding;
									}
								}
							}
							
							if (previousSize__.width != width || previousSize__.height != height) {
								need_measure__ = true;
								previousSize__.width = width;
								previousSize__.height = height;
							}
						}
					}

					if (propertiesSet__) {
						measureDesiredSize();
					}
				} catch (...) {
					TITANIUM_LOG_DEBUG("Unknown error at Label::SizeChanged");
				}
			});

			border__->Child = label__;

			const auto layout = getViewLayoutDelegate<WindowsViewLayoutDelegate>();

			layout->set_defaultHeight(Titanium::UI::LAYOUT::SIZE);
			layout->set_defaultWidth(Titanium::UI::LAYOUT::SIZE);
			layout->set_autoLayoutForHeight(Titanium::UI::LAYOUT::SIZE);
			layout->set_autoLayoutForWidth(Titanium::UI::LAYOUT::SIZE);

			// Label handles its size
			layout->useOwnSize();
			layout->setStyleComponent(label__);
			layout->setComponent(border__, nullptr, border__);
		}

		void Label::JSExportInitialize()
		{
			JSExport<Label>::SetClassVersion(1);
			JSExport<Label>::SetParent(JSExport<Titanium::UI::Label>::Class());
		}

		void Label::set_color(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_color(colorName);
			const auto color_obj = WindowsViewLayoutDelegate::ColorForName(colorName, defaultForegroundColor__);
			label__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
		}

		void Label::set_text(const std::string& text) TITANIUM_NOEXCEPT
		{
			set_text(text, true);
		}

		void Label::set_text(const std::string& text, const bool resize) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_text(text);

			if (get_attributedString()) {
				set_attributedString(get_attributedString());
			} else if (!get_autoLink().empty()) {
				set_autoLink(get_autoLink());
			} else {
				label__->Text = TitaniumWindows::Utility::ConvertUTF8String(text);
			}

			need_measure__ = true;

			if (propertiesSet__) {
				measureDesiredSize();
			}
		}

		void Label::set_autoLink(const std::unordered_set<Titanium::UI::AUTOLINK>& autoLink) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_autoLink(autoLink);
			label__->Inlines->Clear();

			const auto enableALL = autoLink.find(Titanium::UI::AUTOLINK::ALL)  != autoLink.end();
			const auto enableURL = autoLink.find(Titanium::UI::AUTOLINK::URLS) != autoLink.end();

			const auto root = ref new Span();

			std::regex url_pattern(
				R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)",
				std::regex::extended
			);
			std::list<std::string> blocks;
			boost::split(blocks, get_text(), boost::is_any_of(" "));

			std::smatch url_matches;
			BOOST_FOREACH(std::string text, blocks) {

				const auto run = ref new Run();
				run->Text = TitaniumWindows::Utility::ConvertUTF8String(text);

				if ((enableALL || enableURL) && std::regex_search(text, url_matches, url_pattern) && !url_matches.str(1).empty()) {
					auto hyperlink = ref new Hyperlink();
					hyperlink->NavigateUri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertUTF8String(text));
					hyperlink->Inlines->Append(run);
					root->Inlines->Append(hyperlink);
				} else {
					root->Inlines->Append(run);
				}

				const auto space = ref new Run();
				space->Text = " ";
				root->Inlines->Append(space);
			};

			label__->Inlines->Append(root);
		}

		void Label::measureDesiredSize() TITANIUM_NOEXCEPT
		{
			if (!need_measure__) return;

			// TIMOB-23305: Measure desired size for this text and resize parent container accordingly.
			Windows::Foundation::Size desiredSize{ static_cast<float>(label__->MaxWidth), static_cast<float>(label__->MaxHeight) };
			label__->Measure(desiredSize);

			const auto layout = getViewLayoutDelegate<WindowsViewLayoutDelegate>();

			// minimumFontSize decreases the fontsize of the text to fit the width. This enables single-line mode. Only works with minimumFontSize > 0
			const auto minimumFontSize = get_minimumFontSize();
			const auto measuredWidth = layout->getLayoutNode()->element.measuredWidth;
			if (minimumFontSize > 0 && measuredWidth > 0) {
				auto previousFontSize = label__->FontSize;
				while (previousFontSize > minimumFontSize && minimumFontSize > 1.0 && measuredWidth < label__->ActualWidth) {
					previousFontSize -= 0.1;
					label__->FontSize = previousFontSize;
					label__->Measure(desiredSize);
				}
			}

			const auto width = layout->get_width();
			const auto height = layout->get_height();
			const auto TI_UI_SIZE = Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE);
			if ((width.empty() || width == TI_UI_SIZE || width == "auto") && layout->canUseSizeWidth()) {
				layout->fixWidth(label__->ActualWidth + border__->BorderThickness.Left + border__->BorderThickness.Right + 1 /* Border needs this margin */ );
				layout->requestLayout();
			}
			if ((height.empty() || height == TI_UI_SIZE || height == "auto") && layout->canUseSizeHeight()) {
				layout->fixHeight(label__->ActualHeight + border__->BorderThickness.Top + border__->BorderThickness.Bottom + 1 /* Border needs this margin */ );
				layout->requestLayout();
			}

			need_measure__ = false;
		}

		void Label::set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_textAlign(textAlign);
			if (textAlign == Titanium::UI::TEXT_ALIGNMENT::CENTER) {
				label__->TextAlignment = Windows::UI::Xaml::TextAlignment::Center;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::LEFT) {
				label__->TextAlignment = Windows::UI::Xaml::TextAlignment::Left;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::RIGHT) {
				label__->TextAlignment = Windows::UI::Xaml::TextAlignment::Right;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::JUSTIFY) {
				label__->TextAlignment = Windows::UI::Xaml::TextAlignment::Justify;
			}
		}

		void Label::set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_verticalAlign(verticalAlign);
			if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::BOTTOM) {
				label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Bottom;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::CENTER) {
				label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::TOP) {
				label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
			}
			// TODO Windows supports stretch!
		}

		void Label::set_wordWrap(const bool& wordWrap) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_wordWrap(wordWrap);
			label__->TextWrapping = wordWrap ? Windows::UI::Xaml::TextWrapping::Wrap : Windows::UI::Xaml::TextWrapping::NoWrap;
		}

		void Label::set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_font(font);
			TitaniumWindows::UI::ViewHelper::SetFont<Windows::UI::Xaml::Controls::TextBlock^>(get_context(), label__, font);
		}

		void Label::set_attributedString(const std::shared_ptr<Titanium::UI::AttributedString>& attributedString) TITANIUM_NOEXCEPT
		{

			Titanium::UI::Label::set_attributedString(attributedString);

			label__->Inlines->Clear();

			if (attributedString == nullptr) {
				return;
			}

			//
			// simple implementation for attributed string due to mismatch with Windows Style API
			//   - only supports FOREGROUND_COLOR and FONT
			//   - attributes can't be nested
			// TODO: we might want to provide Windows-specific styling API leveraging Xaml Document API
			//
			const auto attributes = attributedString->get_attributes();
			const auto text = TitaniumWindows::Utility::ConvertToUTF8WString(attributedString->get_text());
			const auto text_length = text.length();

			auto root = ref new Span();
			//
			// store some attributes by index so we can search them faster
			//
			// ranges[index] = [length, hasUnderline, hasLink, url]
			//
			std::unordered_map<std::uint32_t, std::tuple<std::uint32_t, bool, bool, std::string>> ranges;
 			std::unordered_map<std::uint32_t, std::vector<Titanium::UI::Attribute>> styles;
			// scan all attributes to construct range collection
			for (const auto attribute : attributes) {

				const auto index = attribute.from;

				if (ranges.find(index) == ranges.end()) {
					ranges[index] = std::make_tuple(attribute.length, false, false, "");
				}


				if (styles.find(index) == styles.end()) {
					std::vector<Titanium::UI::Attribute> attrs;
					styles.emplace(index, attrs);
				}

				auto data = ranges.at(index);
				if (attribute.type == Titanium::UI::ATTRIBUTE_TYPE::UNDERLINES_STYLE) {
					std::get<1>(data) = true;
				} else if (attribute.type == Titanium::UI::ATTRIBUTE_TYPE::LINK) {
					std::get<2>(data) = true;
					std::get<3>(data) = static_cast<std::string>(attribute.value);
				}
				ranges.at(index) = data;

				styles.at(attribute.from).push_back(attribute);
			}

			std::uint32_t nostyle_start = 0;
			for (std::uint32_t pos = 0; pos < text_length; pos++) {
				if (ranges.find(pos) != ranges.end()) {
					const auto rangeInfo = ranges.at(pos);
					const auto length = std::get<0>(rangeInfo);
					const auto hasUnderline = std::get<1>(rangeInfo);
					const auto hasLink = std::get<2>(rangeInfo);

					// text with no attribute
					const auto nostyle_pos = pos - nostyle_start;
					if (nostyle_pos > 0) {
						auto run = ref new Run();
						run->Text = ref new Platform::String(text.substr(nostyle_start, nostyle_pos).data());
						root->Inlines->Append(run);
					}

					// extract attributes
					auto run  = ref new Run();
					// text with attribute
					run->Text = ref new Platform::String(text.substr(pos, length).data());

					Span^ span;
					if (hasUnderline) {        /* UNDERLINES_STYLE */
						span = ref new Underline();
					} else if (hasLink) { /* LINK */
						auto hyperlink = ref new Hyperlink();
						hyperlink->NavigateUri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertString(std::get<3>(rangeInfo)));
						span = hyperlink;
					} else {
						span = ref new Span();
					}

					if (styles.find(pos) != styles.end()) {
						for (const auto attribute : styles.at(pos)) {
							const auto attribute_styles = Titanium::UI::Constants::to_ATTRIBUTE_STYLE(static_cast<std::underlying_type<Titanium::UI::ATTRIBUTE_STYLE>::type>(attribute.value));
							switch (attribute.type) {
							case Titanium::UI::ATTRIBUTE_TYPE::FOREGROUND_COLOR: 
								span->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(
									WindowsViewLayoutDelegate::ColorForName(static_cast<std::string>(attribute.value)));
								break;
							case Titanium::UI::ATTRIBUTE_TYPE::FONT: 
							{
								const auto font = Titanium::UI::js_to_Font(static_cast<JSObject>(attribute.value));
								TitaniumWindows::UI::ViewHelper::SetFont<Windows::UI::Xaml::Documents::Span^>(get_context(), span, font);
								break;
							}
							case Titanium::UI::ATTRIBUTE_TYPE::EXPANSION:
							{
								// round based on 0.125 steps (i.e. 0.126 -> 0.125)
								const auto value = round(static_cast<double>(attribute.value) / 0.125) * 0.125;

								if (value <= -0.5) {
									run->FontStretch = FontStretch::UltraCondensed;
								} else if (value <= -0.375) {
									run->FontStretch = FontStretch::ExtraCondensed;
								} else if (value <= -0.25) {
									run->FontStretch = FontStretch::Condensed;
								} else if (value <= -0.125) {
									run->FontStretch = FontStretch::SemiCondensed;
								} else if (value <= 0) {
									run->FontStretch = FontStretch::Normal;
								} else if (value <= 0.125) {
									run->FontStretch = FontStretch::SemiExpanded;
								} else if (value <= 0.25) {
									run->FontStretch = FontStretch::Expanded;
								} else if (value <= 0.50) {
									run->FontStretch = FontStretch::ExtraExpanded;
								} else if (value <= 1.0) {
									run->FontStretch = FontStretch::UltraExpanded;
								}
								break;
							}
							case Titanium::UI::ATTRIBUTE_TYPE::WRITING_DIRECTION:
								if (attribute_styles.find(Titanium::UI::ATTRIBUTE_STYLE::WRITING_DIRECTION_LEFT_TO_RIGHT) != attribute_styles.end()) {
									run->FlowDirection = FlowDirection::LeftToRight;
								} else if (attribute_styles.find(Titanium::UI::ATTRIBUTE_STYLE::WRITING_DIRECTION_RIGHT_TO_LEFT) != attribute_styles.end()) {
									run->FlowDirection = FlowDirection::RightToLeft;
								}
								break;
							case Titanium::UI::ATTRIBUTE_TYPE::KERN:
								// convert px to 1/1000 em
								// TODO: can we assume 16px for 1 em?
								run->CharacterSpacing = static_cast<std::int32_t>(static_cast<std::int32_t>(attribute.value) / 16.0 * 1000.0);
								Typography::SetKerning(label__, (run->CharacterSpacing > 0));
								break;
							case Titanium::UI::ATTRIBUTE_TYPE::LIGATURE:
							{
								// range is ignored here, because Ligature affects entire text on TextBlock
								const auto value = static_cast<std::uint32_t>(attribute.value);
								Typography::SetStandardLigatures(label__, (value == 1 ? true : false));
								break;
							}
							}
						}
					}

					span->Inlines->Append(run);
					root->Inlines->Append(span);
					pos += length;
					nostyle_start = pos;
				}
			}

			// Append rest of the text with no attribute
			if (nostyle_start < text_length) {
				const auto len = text_length - nostyle_start;
				auto run = ref new Run();
				run->Text = ref new Platform::String(text.substr(nostyle_start, len).data());
				root->Inlines->Append(run);
			}

			label__->Inlines->Append(root);
		}

		void Label::set_maxLines(const std::uint32_t& maxLines) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_maxLines(maxLines);
			label__->MaxLines = maxLines;
		}

	} // namespace UI
} // namespace TitaniumWindows
