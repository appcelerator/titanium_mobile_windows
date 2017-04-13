/**
 * Windows Native Wrapper for Windows.UI.Colors
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Colors.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{

		Colors::Colors(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("Colors::ctor");
		}

		void Colors::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Colors::postCallAsConstructor ", this);

		}

		::Windows::UI::Colors^ Colors::unwrapWindows_UI_Colors() const
		{
			return dynamic_cast<::Windows::UI::Colors^>(wrapped__);
		}

		::Windows::UI::Colors^ Colors::unwrap() const
		{
			return unwrapWindows_UI_Colors();
		}

		void Colors::wrap(::Windows::UI::Colors^ object)
		{
			wrapped__ = object;
		}

		void Colors::JSExportInitialize()
		{
			JSExport<Colors>::SetClassVersion(1);
			JSExport<Colors>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(Colors, AliceBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, AntiqueWhite);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Aqua);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Aquamarine);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Azure);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Beige);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Bisque);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Black);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, BlanchedAlmond);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Blue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, BlueViolet);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Brown);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, BurlyWood);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, CadetBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Chartreuse);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Chocolate);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Coral);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, CornflowerBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Cornsilk);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Crimson);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Cyan);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkCyan);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkGoldenrod);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkGray);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkKhaki);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkMagenta);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkOliveGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkOrange);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkOrchid);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkRed);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkSalmon);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkSeaGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkSlateBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkSlateGray);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkTurquoise);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DarkViolet);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DeepPink);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DeepSkyBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DimGray);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, DodgerBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Firebrick);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, FloralWhite);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, ForestGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Fuchsia);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Gainsboro);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, GhostWhite);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Gold);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Goldenrod);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Gray);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Green);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, GreenYellow);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Honeydew);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, HotPink);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, IndianRed);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Indigo);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Ivory);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Khaki);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Lavender);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LavenderBlush);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LawnGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LemonChiffon);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightCoral);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightCyan);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightGoldenrodYellow);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightGray);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightPink);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightSalmon);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightSeaGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightSkyBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightSlateGray);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightSteelBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LightYellow);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Lime);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, LimeGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Linen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Magenta);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Maroon);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MediumAquamarine);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MediumBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MediumOrchid);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MediumPurple);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MediumSeaGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MediumSlateBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MediumSpringGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MediumTurquoise);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MediumVioletRed);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MidnightBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MintCream);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, MistyRose);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Moccasin);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, NavajoWhite);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Navy);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, OldLace);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Olive);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, OliveDrab);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Orange);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, OrangeRed);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Orchid);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, PaleGoldenrod);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, PaleGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, PaleTurquoise);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, PaleVioletRed);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, PapayaWhip);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, PeachPuff);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Peru);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Pink);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Plum);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, PowderBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Purple);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Red);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, RosyBrown);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, RoyalBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, SaddleBrown);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Salmon);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, SandyBrown);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, SeaGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, SeaShell);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Sienna);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Silver);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, SkyBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, SlateBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, SlateGray);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Snow);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, SpringGreen);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, SteelBlue);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Tan);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Teal);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Thistle);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Tomato);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Transparent);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Turquoise);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Violet);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Wheat);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, White);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, WhiteSmoke);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, Yellow);
			TITANIUM_ADD_PROPERTY_READONLY(Colors, YellowGreen);
		}

		TITANIUM_PROPERTY_GETTER(Colors, AliceBlue)
		{
			auto value = unwrap()->AliceBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, AntiqueWhite)
		{
			auto value = unwrap()->AntiqueWhite;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Aqua)
		{
			auto value = unwrap()->Aqua;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Aquamarine)
		{
			auto value = unwrap()->Aquamarine;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Azure)
		{
			auto value = unwrap()->Azure;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Beige)
		{
			auto value = unwrap()->Beige;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Bisque)
		{
			auto value = unwrap()->Bisque;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Black)
		{
			auto value = unwrap()->Black;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, BlanchedAlmond)
		{
			auto value = unwrap()->BlanchedAlmond;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Blue)
		{
			auto value = unwrap()->Blue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, BlueViolet)
		{
			auto value = unwrap()->BlueViolet;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Brown)
		{
			auto value = unwrap()->Brown;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, BurlyWood)
		{
			auto value = unwrap()->BurlyWood;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, CadetBlue)
		{
			auto value = unwrap()->CadetBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Chartreuse)
		{
			auto value = unwrap()->Chartreuse;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Chocolate)
		{
			auto value = unwrap()->Chocolate;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Coral)
		{
			auto value = unwrap()->Coral;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, CornflowerBlue)
		{
			auto value = unwrap()->CornflowerBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Cornsilk)
		{
			auto value = unwrap()->Cornsilk;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Crimson)
		{
			auto value = unwrap()->Crimson;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Cyan)
		{
			auto value = unwrap()->Cyan;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkBlue)
		{
			auto value = unwrap()->DarkBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkCyan)
		{
			auto value = unwrap()->DarkCyan;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkGoldenrod)
		{
			auto value = unwrap()->DarkGoldenrod;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkGray)
		{
			auto value = unwrap()->DarkGray;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkGreen)
		{
			auto value = unwrap()->DarkGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkKhaki)
		{
			auto value = unwrap()->DarkKhaki;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkMagenta)
		{
			auto value = unwrap()->DarkMagenta;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkOliveGreen)
		{
			auto value = unwrap()->DarkOliveGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkOrange)
		{
			auto value = unwrap()->DarkOrange;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkOrchid)
		{
			auto value = unwrap()->DarkOrchid;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkRed)
		{
			auto value = unwrap()->DarkRed;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkSalmon)
		{
			auto value = unwrap()->DarkSalmon;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkSeaGreen)
		{
			auto value = unwrap()->DarkSeaGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkSlateBlue)
		{
			auto value = unwrap()->DarkSlateBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkSlateGray)
		{
			auto value = unwrap()->DarkSlateGray;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkTurquoise)
		{
			auto value = unwrap()->DarkTurquoise;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DarkViolet)
		{
			auto value = unwrap()->DarkViolet;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DeepPink)
		{
			auto value = unwrap()->DeepPink;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DeepSkyBlue)
		{
			auto value = unwrap()->DeepSkyBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DimGray)
		{
			auto value = unwrap()->DimGray;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, DodgerBlue)
		{
			auto value = unwrap()->DodgerBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Firebrick)
		{
			auto value = unwrap()->Firebrick;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, FloralWhite)
		{
			auto value = unwrap()->FloralWhite;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, ForestGreen)
		{
			auto value = unwrap()->ForestGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Fuchsia)
		{
			auto value = unwrap()->Fuchsia;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Gainsboro)
		{
			auto value = unwrap()->Gainsboro;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, GhostWhite)
		{
			auto value = unwrap()->GhostWhite;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Gold)
		{
			auto value = unwrap()->Gold;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Goldenrod)
		{
			auto value = unwrap()->Goldenrod;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Gray)
		{
			auto value = unwrap()->Gray;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Green)
		{
			auto value = unwrap()->Green;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, GreenYellow)
		{
			auto value = unwrap()->GreenYellow;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Honeydew)
		{
			auto value = unwrap()->Honeydew;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, HotPink)
		{
			auto value = unwrap()->HotPink;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, IndianRed)
		{
			auto value = unwrap()->IndianRed;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Indigo)
		{
			auto value = unwrap()->Indigo;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Ivory)
		{
			auto value = unwrap()->Ivory;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Khaki)
		{
			auto value = unwrap()->Khaki;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Lavender)
		{
			auto value = unwrap()->Lavender;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LavenderBlush)
		{
			auto value = unwrap()->LavenderBlush;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LawnGreen)
		{
			auto value = unwrap()->LawnGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LemonChiffon)
		{
			auto value = unwrap()->LemonChiffon;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightBlue)
		{
			auto value = unwrap()->LightBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightCoral)
		{
			auto value = unwrap()->LightCoral;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightCyan)
		{
			auto value = unwrap()->LightCyan;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightGoldenrodYellow)
		{
			auto value = unwrap()->LightGoldenrodYellow;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightGray)
		{
			auto value = unwrap()->LightGray;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightGreen)
		{
			auto value = unwrap()->LightGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightPink)
		{
			auto value = unwrap()->LightPink;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightSalmon)
		{
			auto value = unwrap()->LightSalmon;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightSeaGreen)
		{
			auto value = unwrap()->LightSeaGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightSkyBlue)
		{
			auto value = unwrap()->LightSkyBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightSlateGray)
		{
			auto value = unwrap()->LightSlateGray;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightSteelBlue)
		{
			auto value = unwrap()->LightSteelBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LightYellow)
		{
			auto value = unwrap()->LightYellow;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Lime)
		{
			auto value = unwrap()->Lime;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, LimeGreen)
		{
			auto value = unwrap()->LimeGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Linen)
		{
			auto value = unwrap()->Linen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Magenta)
		{
			auto value = unwrap()->Magenta;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Maroon)
		{
			auto value = unwrap()->Maroon;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MediumAquamarine)
		{
			auto value = unwrap()->MediumAquamarine;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MediumBlue)
		{
			auto value = unwrap()->MediumBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MediumOrchid)
		{
			auto value = unwrap()->MediumOrchid;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MediumPurple)
		{
			auto value = unwrap()->MediumPurple;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MediumSeaGreen)
		{
			auto value = unwrap()->MediumSeaGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MediumSlateBlue)
		{
			auto value = unwrap()->MediumSlateBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MediumSpringGreen)
		{
			auto value = unwrap()->MediumSpringGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MediumTurquoise)
		{
			auto value = unwrap()->MediumTurquoise;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MediumVioletRed)
		{
			auto value = unwrap()->MediumVioletRed;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MidnightBlue)
		{
			auto value = unwrap()->MidnightBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MintCream)
		{
			auto value = unwrap()->MintCream;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, MistyRose)
		{
			auto value = unwrap()->MistyRose;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Moccasin)
		{
			auto value = unwrap()->Moccasin;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, NavajoWhite)
		{
			auto value = unwrap()->NavajoWhite;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Navy)
		{
			auto value = unwrap()->Navy;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, OldLace)
		{
			auto value = unwrap()->OldLace;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Olive)
		{
			auto value = unwrap()->Olive;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, OliveDrab)
		{
			auto value = unwrap()->OliveDrab;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Orange)
		{
			auto value = unwrap()->Orange;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, OrangeRed)
		{
			auto value = unwrap()->OrangeRed;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Orchid)
		{
			auto value = unwrap()->Orchid;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, PaleGoldenrod)
		{
			auto value = unwrap()->PaleGoldenrod;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, PaleGreen)
		{
			auto value = unwrap()->PaleGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, PaleTurquoise)
		{
			auto value = unwrap()->PaleTurquoise;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, PaleVioletRed)
		{
			auto value = unwrap()->PaleVioletRed;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, PapayaWhip)
		{
			auto value = unwrap()->PapayaWhip;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, PeachPuff)
		{
			auto value = unwrap()->PeachPuff;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Peru)
		{
			auto value = unwrap()->Peru;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Pink)
		{
			auto value = unwrap()->Pink;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Plum)
		{
			auto value = unwrap()->Plum;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, PowderBlue)
		{
			auto value = unwrap()->PowderBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Purple)
		{
			auto value = unwrap()->Purple;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Red)
		{
			auto value = unwrap()->Red;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, RosyBrown)
		{
			auto value = unwrap()->RosyBrown;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, RoyalBlue)
		{
			auto value = unwrap()->RoyalBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, SaddleBrown)
		{
			auto value = unwrap()->SaddleBrown;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Salmon)
		{
			auto value = unwrap()->Salmon;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, SandyBrown)
		{
			auto value = unwrap()->SandyBrown;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, SeaGreen)
		{
			auto value = unwrap()->SeaGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, SeaShell)
		{
			auto value = unwrap()->SeaShell;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Sienna)
		{
			auto value = unwrap()->Sienna;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Silver)
		{
			auto value = unwrap()->Silver;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, SkyBlue)
		{
			auto value = unwrap()->SkyBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, SlateBlue)
		{
			auto value = unwrap()->SlateBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, SlateGray)
		{
			auto value = unwrap()->SlateGray;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Snow)
		{
			auto value = unwrap()->Snow;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, SpringGreen)
		{
			auto value = unwrap()->SpringGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, SteelBlue)
		{
			auto value = unwrap()->SteelBlue;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Tan)
		{
			auto value = unwrap()->Tan;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Teal)
		{
			auto value = unwrap()->Teal;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Thistle)
		{
			auto value = unwrap()->Thistle;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Tomato)
		{
			auto value = unwrap()->Tomato;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Transparent)
		{
			auto value = unwrap()->Transparent;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Turquoise)
		{
			auto value = unwrap()->Turquoise;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Violet)
		{
			auto value = unwrap()->Violet;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Wheat)
		{
			auto value = unwrap()->Wheat;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, White)
		{
			auto value = unwrap()->White;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, WhiteSmoke)
		{
			auto value = unwrap()->WhiteSmoke;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, Yellow)
		{
			auto value = unwrap()->Yellow;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Colors, YellowGreen)
		{
			auto value = unwrap()->YellowGreen;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		} // namespace UI
	} // namespace Windows
} // namespace Titanium
