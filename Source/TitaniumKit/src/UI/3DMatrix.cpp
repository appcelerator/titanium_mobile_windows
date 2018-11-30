/**
 * TitaniumKit Titanium.UI.3DMatrix
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/3DMatrix.hpp"

namespace Titanium
{
	namespace UI
	{

		ThreeDMatrix::ThreeDMatrix(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.Matrix3D"),
			m11__(0),
			m12__(0),
			m13__(0),
			m14__(0),
			m21__(0),
			m22__(0),
			m23__(0),
			m24__(0),
			m31__(0),
			m32__(0),
			m33__(0),
			m34__(0),
			m41__(0),
			m42__(0),
			m43__(0),
			m44__(0)
		{
		}

		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m11)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m12)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m13)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m14)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m21)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m22)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m23)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m24)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m31)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m32)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m33)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m34)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m41)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m42)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m43)
		TITANIUM_PROPERTY_READWRITE(ThreeDMatrix, double, m44)

		std::shared_ptr<ThreeDMatrix> ThreeDMatrix::invert() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ThreeDMatrix::invert: Unimplemented");
			return nullptr;
		}

		std::shared_ptr<ThreeDMatrix> ThreeDMatrix::multiply(std::shared_ptr<ThreeDMatrix> t2) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ThreeDMatrix::multiply: Unimplemented");
			return nullptr;
		}

		std::shared_ptr<ThreeDMatrix> ThreeDMatrix::rotate(const double& angle, const double& x, const double& y, const double& z) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ThreeDMatrix::rotate: Unimplemented");
			return nullptr;
		}

		std::shared_ptr<ThreeDMatrix> ThreeDMatrix::scale(const double& sx, const double& sy, const double& sz) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ThreeDMatrix::scale: Unimplemented");
			return nullptr;
		}

		std::shared_ptr<ThreeDMatrix> ThreeDMatrix::translate(const double& tx, const double& ty, const double& tz) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ThreeDMatrix::translate: Unimplemented");
			return nullptr;
		}

		void ThreeDMatrix::JSExportInitialize() 
		{
			JSExport<ThreeDMatrix>::SetClassVersion(1);
			JSExport<ThreeDMatrix>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m11);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m12);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m13);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m14);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m21);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m22);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m23);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m24);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m31);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m32);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m33);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m34);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m41);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m42);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m43);
			TITANIUM_ADD_PROPERTY(ThreeDMatrix, m44);

			TITANIUM_ADD_FUNCTION(ThreeDMatrix, invert);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, multiply);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, rotate);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, scale);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, translate);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM11);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM11);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM12);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM12);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM13);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM13);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM14);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM14);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM21);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM21);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM22);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM22);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM23);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM23);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM24);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM24);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM31);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM31);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM32);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM32);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM33);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM33);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM34);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM34);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM41);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM41);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM42);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM42);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM43);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM43);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, getM44);
			TITANIUM_ADD_FUNCTION(ThreeDMatrix, setM44);
		}

		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m11)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m11)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m12)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m12)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m13)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m13)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m14)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m14)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m21)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m21)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m22)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m22)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m23)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m23)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m24)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m24)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m31)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m31)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m32)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m32)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m33)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m33)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m34)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m34)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m41)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m41)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m42)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m42)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m43)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m43)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ThreeDMatrix, m44)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ThreeDMatrix, m44)

		TITANIUM_FUNCTION(ThreeDMatrix, invert)
		{
			const auto matrix = invert();
			if (matrix) {
				return matrix->get_object();
			} else {
				return get_context().CreateUndefined();
			}
		}

		TITANIUM_FUNCTION(ThreeDMatrix, multiply)
		{
			ENSURE_OBJECT_AT_INDEX(t2, 0);

			const auto matrix = multiply(t2.GetPrivate<ThreeDMatrix>());
			if (matrix) {
				return matrix->get_object();
			} else {
				return get_context().CreateUndefined();
			}
		}

		TITANIUM_FUNCTION(ThreeDMatrix, rotate)
		{
			ENSURE_ARGUMENT_INDEX(3);
			ENSURE_DOUBLE_AT_INDEX(angle, 0);
			ENSURE_DOUBLE_AT_INDEX(x, 1);
			ENSURE_DOUBLE_AT_INDEX(y, 2);
			ENSURE_DOUBLE_AT_INDEX(z, 3);
			const auto matrix = rotate(angle, x, y, z);
			if (matrix) {
				return matrix->get_object();
			} else {
				return get_context().CreateUndefined();
			}
		}

		TITANIUM_FUNCTION(ThreeDMatrix, scale)
		{
			ENSURE_ARGUMENT_INDEX(2);
			ENSURE_DOUBLE_AT_INDEX(sx, 0);
			ENSURE_DOUBLE_AT_INDEX(sy, 1);
			ENSURE_DOUBLE_AT_INDEX(sz, 2);
			const auto matrix = scale(sx, sy, sz);
			if (matrix) {
				return matrix->get_object();
			} else {
				return get_context().CreateUndefined();
			}
		}

		TITANIUM_FUNCTION(ThreeDMatrix, translate)
		{
			ENSURE_ARGUMENT_INDEX(2);
			ENSURE_DOUBLE_AT_INDEX(tx, 0);
			ENSURE_DOUBLE_AT_INDEX(ty, 1);
			ENSURE_DOUBLE_AT_INDEX(tz, 2);
			const auto matrix = translate(tx, ty, tz);
			if (matrix) {
				return matrix->get_object();
			} else {
				return get_context().CreateUndefined();
			}
		}

		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM11, m11)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM11, m11)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM12, m12)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM12, m12)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM13, m13)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM13, m13)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM14, m14)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM14, m14)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM21, m21)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM21, m21)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM22, m22)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM22, m22)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM23, m23)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM23, m23)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM24, m24)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM24, m24)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM31, m31)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM31, m31)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM32, m32)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM32, m32)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM33, m33)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM33, m33)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM34, m34)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM34, m34)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM41, m41)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM41, m41)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM42, m42)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM42, m42)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM43, m43)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM43, m43)
		TITANIUM_FUNCTION_AS_GETTER(ThreeDMatrix, getM44, m44)
		TITANIUM_FUNCTION_AS_SETTER(ThreeDMatrix, setM44, m44)

	} // namespace UI
} // namespace Titanium