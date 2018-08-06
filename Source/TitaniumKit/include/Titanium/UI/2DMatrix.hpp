/**
 * TitaniumKit Titanium.UI.2DMatrix
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_2DMATRIX_HPP_
#define _TITANIUM_2DMATRIX_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/MatrixCreationDict.hpp"

namespace Titanium
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium 2DMatrix Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.2DMatrix
		*/
		class TITANIUMKIT_EXPORT TwoDMatrix : public Module, public JSExport<TwoDMatrix>
		{

		public:

			/*!
			  @property
			  @abstract a
			  @discussion The entry at position [1,1] in the matrix.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, a);

			/*!
			  @property
			  @abstract b
			  @discussion The entry at position [1,2] in the matrix.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, b);

			/*!
			  @property
			  @abstract c
			  @discussion The entry at position [2,1] in the matrix.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, c);

			/*!
			  @property
			  @abstract d
			  @discussion The entry at position [2,2] in the matrix.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, d);

			/*!
			  @property
			  @abstract tx
			  @discussion The entry at position [3,1] in the matrix.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, tx);

			/*!
			  @property
			  @abstract ty
			  @discussion The entry at position [3,2] in the matrix.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, ty);

			/*!
			  @method
			  @abstract invert
			  @discussion Returns a matrix constructed by inverting this matrix.
			*/
			virtual std::shared_ptr<TwoDMatrix> invert() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract multiply
			  @discussion Returns a matrix constructed by combining two existing matrices.
			*/
			virtual std::shared_ptr<TwoDMatrix> multiply(const std::shared_ptr<TwoDMatrix> t2) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract rotate
			  @discussion Returns a matrix constructed by rotating this matrix.
			*/
			virtual std::shared_ptr<TwoDMatrix> rotate(const double& angle, const double& toAngle) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract scale
			  @discussion Returns a `2DMatrix` object that specifies a scaling animation from one scale to another.
			*/
			virtual std::shared_ptr<TwoDMatrix> scale(const double& sx, const double& sy, const double& toSx, const double& toSy) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract translate
			  @discussion Returns a matrix constructed by applying a translation transform to this matrix.
			*/
			virtual std::shared_ptr<TwoDMatrix> translate(const double& tx, const double& ty) TITANIUM_NOEXCEPT;

			TwoDMatrix(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~TwoDMatrix() = default;
			TwoDMatrix(const TwoDMatrix &) = default;
			TwoDMatrix& operator=(const TwoDMatrix &) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TwoDMatrix(TwoDMatrix&&)                 = default;
			TwoDMatrix& operator=(TwoDMatrix&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			TITANIUM_PROPERTY_DEF(a);
			TITANIUM_PROPERTY_DEF(b);
			TITANIUM_PROPERTY_DEF(c);
			TITANIUM_PROPERTY_DEF(d);
			TITANIUM_PROPERTY_DEF(tx);
			TITANIUM_PROPERTY_DEF(ty);

			TITANIUM_FUNCTION_DEF(invert);
			TITANIUM_FUNCTION_DEF(multiply);
			TITANIUM_FUNCTION_DEF(rotate);
			TITANIUM_FUNCTION_DEF(scale);
			TITANIUM_FUNCTION_DEF(translate);
			TITANIUM_FUNCTION_DEF(getA);
			TITANIUM_FUNCTION_DEF(setA);
			TITANIUM_FUNCTION_DEF(getB);
			TITANIUM_FUNCTION_DEF(setB);
			TITANIUM_FUNCTION_DEF(getC);
			TITANIUM_FUNCTION_DEF(setC);
			TITANIUM_FUNCTION_DEF(getD);
			TITANIUM_FUNCTION_DEF(setD);
			TITANIUM_FUNCTION_DEF(getTx);
			TITANIUM_FUNCTION_DEF(setTx);
			TITANIUM_FUNCTION_DEF(getTy);
			TITANIUM_FUNCTION_DEF(setTy);

			Titanium::UI::MatrixCreationDict get_parameters() 
			{
				return params__;
			}
		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			double a__;
			double b__;
			double c__;
			double d__;
			double tx__;
			double ty__;

			// Save constructor parameters
			Titanium::UI::MatrixCreationDict params__;
#pragma warning(pop)

			std::shared_ptr<TwoDMatrix> multiply(const double a, const double b, const double c, const double d, const double tx, const double ty);

		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_2DMATRIX_HPP_