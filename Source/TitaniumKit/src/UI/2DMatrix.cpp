/**
 * TitaniumKit Titanium.UI.2DMatrix
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/2DMatrix.hpp"
#include "Titanium/UI/MatrixCreationDict.hpp"
#include "Titanium/detail/TiImpl.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#define CREATE_MATRIX(MATRIX_NAME) \
JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium"); \
TITANIUM_ASSERT(Titanium_property.IsObject()); \
JSObject Titanium = static_cast<JSObject>(Titanium_property); \
\
JSValue UI_property = Titanium.GetProperty("UI"); \
TITANIUM_ASSERT(UI_property.IsObject()); \
JSObject UI = static_cast<JSObject>(UI_property); \
\
JSValue TwoDMatrix_property = UI.GetProperty("Matrix2D"); \
TITANIUM_ASSERT(TwoDMatrix_property.IsObject()); \
JSObject TwoDMatrix_Class = static_cast<JSObject>(TwoDMatrix_property); \
\
auto new_matrix = TwoDMatrix_Class.CallAsConstructor(); \
auto MATRIX_NAME = new_matrix.GetPrivate<TwoDMatrix>()

namespace Titanium
{
	namespace UI
	{


		TwoDMatrix::TwoDMatrix(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.Matrix2D"),
			a__(1),
			b__(0),
			c__(0),
			d__(1),
			tx__(0),
			ty__(0)
		{
		}

		void TwoDMatrix::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			if (!arguments.empty()) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				const auto object = static_cast<JSObject>(_0);
				params__ = Titanium::UI::js_to_MatrixCreationDict(object);

				auto blah = get_shared_ptr_for_module<Titanium::UI::TwoDMatrix>();
				if (params__.rotate != 0) {
					blah = rotate(params__.rotate, 0);
				}
				if (params__.scale != 1.0) {
					blah = scale(params__.scale, params__.scale, 0, 0);
				}

				set_a(blah->get_a());
				set_b(blah->get_b());
				set_c(blah->get_c());
				set_d(blah->get_d());
				set_tx(blah->get_tx());
				set_ty(blah->get_ty());
			}
		}

		TITANIUM_PROPERTY_READWRITE(TwoDMatrix, double, a)

		TITANIUM_PROPERTY_READWRITE(TwoDMatrix, double, b)

		TITANIUM_PROPERTY_READWRITE(TwoDMatrix, double, c)

		TITANIUM_PROPERTY_READWRITE(TwoDMatrix, double, d)

		TITANIUM_PROPERTY_READWRITE(TwoDMatrix, double, tx)

		TITANIUM_PROPERTY_READWRITE(TwoDMatrix, double, ty)

		std::shared_ptr<TwoDMatrix> TwoDMatrix::invert() TITANIUM_NOEXCEPT
		{
			CREATE_MATRIX(matrix);
			// TODO If this is an identity matrix already, don't do anything. We default to identity matrix
			auto delta = a__ * tx__ - b__ * c__;

			matrix->set_a(d__ / delta);
			matrix->set_b(-b__ / delta);
			matrix->set_c(-c__ / delta);
			matrix->set_d(a__ / delta);
			matrix->set_tx((c__ * ty__ - d__ * tx__) / delta);
			matrix->set_ty(-(a__ * ty__ - b__ * tx__) / delta);

			return matrix;
		}

		std::shared_ptr<TwoDMatrix> TwoDMatrix::multiply(const std::shared_ptr<TwoDMatrix> t2) TITANIUM_NOEXCEPT
		{
			return multiply(t2->get_a(), t2->get_b(), t2->get_c(), t2->get_d(), t2->get_tx(), t2->get_ty());
		}

		std::shared_ptr<TwoDMatrix> TwoDMatrix::multiply(const double a2, const double b2, const double c2, const double d2, const double tx2, const double ty2)
		{
			CREATE_MATRIX(matrix);
			// keep copies of the original data since we're going to start changing them...
			const auto a1 = get_a();
			const auto b1 = get_b();
			const auto c1 = get_c();
			const auto d1 = get_d();
			const auto tx1 = get_tx();
			const auto ty1 = get_ty();
			// do the actual mutliplication!
			matrix->set_a(a1 * a2 + b1 * c2);
			matrix->set_b(a1 * b2 + b1 * d2);
			matrix->set_c(c1 * a2 + d1 * c2);
			matrix->set_d(c1 * b2 + d1 * d2);
			matrix->set_tx(tx1 * a2 + ty1 * c2 + tx2);
			matrix->set_ty(tx1 * b2 + ty1 * d2 + ty2);

			return matrix;
		}

		std::shared_ptr<TwoDMatrix> TwoDMatrix::rotate(const double& angle, const double& toAngle) TITANIUM_NOEXCEPT
		{
			const auto rads = angle * M_PI / 180.0; // convert angle in degrees to radians
			const auto cosine = cos(rads);
			const auto sine = sin(rads);

			return multiply(cosine, sine, -sine, cosine, 0, 0);
		}

		std::shared_ptr<TwoDMatrix> TwoDMatrix::scale(const double& sx, const double& sy, const double& toSx, const double& toSy) TITANIUM_NOEXCEPT
		{
			return multiply(sx, 0, 0, sy, 0, 0);
		}

		std::shared_ptr<TwoDMatrix> TwoDMatrix::translate(const double& tx, const double& ty) TITANIUM_NOEXCEPT
		{
			return multiply(1, 0, 0, 1, tx, ty);
		}

		void TwoDMatrix::JSExportInitialize() {
			JSExport<TwoDMatrix>::SetClassVersion(1);
			JSExport<TwoDMatrix>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(TwoDMatrix, a);
			TITANIUM_ADD_PROPERTY(TwoDMatrix, b);
			TITANIUM_ADD_PROPERTY(TwoDMatrix, c);
			TITANIUM_ADD_PROPERTY(TwoDMatrix, d);
			TITANIUM_ADD_PROPERTY(TwoDMatrix, tx);
			TITANIUM_ADD_PROPERTY(TwoDMatrix, ty);

			TITANIUM_ADD_FUNCTION(TwoDMatrix, invert);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, multiply);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, rotate);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, scale);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, translate);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, getA);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, setA);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, getB);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, setB);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, getC);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, setC);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, getD);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, setD);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, getTx);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, setTx);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, getTy);
			TITANIUM_ADD_FUNCTION(TwoDMatrix, setTy);
		}

		TITANIUM_PROPERTY_GETTER(TwoDMatrix, a)
		{
			return get_context().CreateNumber(get_a());
		}

		TITANIUM_PROPERTY_SETTER(TwoDMatrix, a)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_a(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(TwoDMatrix, b)
		{
			return get_context().CreateNumber(get_b());
		}

		TITANIUM_PROPERTY_SETTER(TwoDMatrix, b)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_b(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(TwoDMatrix, c)
		{
			return get_context().CreateNumber(get_c());
		}

		TITANIUM_PROPERTY_SETTER(TwoDMatrix, c)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_c(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(TwoDMatrix, d)
		{
			return get_context().CreateNumber(get_d());
		}

		TITANIUM_PROPERTY_SETTER(TwoDMatrix, d)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_d(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(TwoDMatrix, tx)
		{
			return get_context().CreateNumber(get_tx());
		}

		TITANIUM_PROPERTY_SETTER(TwoDMatrix, tx)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_tx(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(TwoDMatrix, ty)
		{
			return get_context().CreateNumber(get_ty());
		}

		TITANIUM_PROPERTY_SETTER(TwoDMatrix, ty)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_ty(static_cast<double>(argument));
			return true;
		}

		TITANIUM_FUNCTION(TwoDMatrix, invert)
		{
			const auto result = invert();
			if (result == nullptr) {
				return get_context().CreateNull();
			}
			return result->get_object();
		}
		TITANIUM_FUNCTION(TwoDMatrix, multiply)
		{
			if (arguments.empty()) {
				return get_context().CreateUndefined();
			}

			ENSURE_OBJECT_AT_INDEX(t2, 0);
			const auto other = t2.GetPrivate<Titanium::UI::TwoDMatrix>();

			const auto result = multiply(other);
			if (result == nullptr) {
				return get_context().CreateNull();
			}
			return result->get_object();
		}

		TITANIUM_FUNCTION(TwoDMatrix, rotate)
		{
			if (arguments.empty()) {
				return get_context().CreateUndefined();
			}

			ENSURE_DOUBLE_AT_INDEX(angle, 0);
			ENSURE_OPTIONAL_DOUBLE_AT_INDEX(toAngle, 1, 0);

			const auto result = rotate(angle, toAngle);
			if (result == nullptr) {
				return get_context().CreateNull();
			}
			return result->get_object();
		}

		TITANIUM_FUNCTION(TwoDMatrix, scale)
		{
			if (arguments.size() < 2) {
				return get_context().CreateUndefined();
			}

			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_DOUBLE_AT_INDEX(sx, 0);
			ENSURE_DOUBLE_AT_INDEX(sy, 1);
			ENSURE_OPTIONAL_DOUBLE_AT_INDEX(toSx, 2, 0);
			ENSURE_OPTIONAL_DOUBLE_AT_INDEX(toSy, 3, 0);

			const auto result = scale(sx, sy, toSx, toSy);
			if (result == nullptr) {
				return get_context().CreateNull();
			}
			return result->get_object();
		}

		TITANIUM_FUNCTION(TwoDMatrix, translate)
		{
			if (arguments.size() < 2) {
				return get_context().CreateUndefined();
			}

			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_DOUBLE_AT_INDEX(tx, 0);
			ENSURE_DOUBLE_AT_INDEX(ty, 1);

			const auto result = translate(tx, ty);
			if (result == nullptr) {
				return get_context().CreateNull();
			}
			return result->get_object();
		}

		TITANIUM_FUNCTION_AS_GETTER(TwoDMatrix, getA, a)

		TITANIUM_FUNCTION_AS_SETTER(TwoDMatrix, setA, a)

		TITANIUM_FUNCTION_AS_GETTER(TwoDMatrix, getB, b)

		TITANIUM_FUNCTION_AS_SETTER(TwoDMatrix, setB, b)

		TITANIUM_FUNCTION_AS_GETTER(TwoDMatrix, getC, c)

		TITANIUM_FUNCTION_AS_SETTER(TwoDMatrix, setC, c)

		TITANIUM_FUNCTION_AS_GETTER(TwoDMatrix, getD, d)

		TITANIUM_FUNCTION_AS_SETTER(TwoDMatrix, setD, d)

		TITANIUM_FUNCTION_AS_GETTER(TwoDMatrix, getTx, tx)

		TITANIUM_FUNCTION_AS_SETTER(TwoDMatrix, setTx, tx)

		TITANIUM_FUNCTION_AS_GETTER(TwoDMatrix, getTy, ty)

		TITANIUM_FUNCTION_AS_SETTER(TwoDMatrix, setTy, ty)

	} // namespace UI
} // namespace Titanium
