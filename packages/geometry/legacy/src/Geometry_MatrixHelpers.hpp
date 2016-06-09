//---------------------------------------------------------------------------//
//!
//! \file   Geometry_MatrixHelpers.hpp
//! \author Alex Robinson
//! \brief  Matrix helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MATRIX_HELPERS_HPP
#define GEOMETRY_MATRIX_HELPERS_HPP

// FRENSIE Includes
#include "Geometry_Matrix.hpp"
#include "Geometry_Vector.hpp"

namespace Geometry{

//! Create a 3x3 matrix
template<typename ScalarType>
Matrix<ScalarType> createMatrix(
	    const ScalarType a00, const ScalarType a01, const ScalarType a02,
	    const ScalarType a10, const ScalarType a11, const ScalarType a12,
	    const ScalarType a20, const ScalarType a21, const ScalarType a22 );

//! Create a 3x3 symmetric matrix
template<typename ScalarType>
Matrix<ScalarType> createMatrix(
	    const ScalarType a00,
	    const ScalarType a10, const ScalarType a11,
	    const ScalarType a20, const ScalarType a21, const ScalarType a22 );

//! Create a 3x3 matrix from rows
template<typename ScalarType>
Matrix<ScalarType> createMatrixFromRows( const Vector<ScalarType> row_1,
					 const Vector<ScalarType> row_2,
					 const Vector<ScalarType> row_3 );

//! Create a 3x3 matrix from columns
template<typename ScalarType>
Matrix<ScalarType> createMatrixFromColumns(const Vector<ScalarType> column_1,
					   const Vector<ScalarType> column_2,
					   const Vector<ScalarType> column_3 );

//! Create a rotation matrix for rotation about the x-axis.
template<typename ScalarType>
Matrix<ScalarType> createXAxisRotationMatrix(const ScalarType rotation_angle );

//! Create a rotation matrix for rotation about the y-axis.
template<typename ScalarType>
Matrix<ScalarType> createYAxisRotationMatrix(const ScalarType rotation_angle );

//! Create a rotation matrix for rotation about the z-axis.
template<typename ScalarType>
Matrix<ScalarType> createZAxisRotationMatrix(const ScalarType rotation_angle );

//! Create a rotation matrix that will rotate one unit vector to another.
/*! \details When rotating surfaces initial_direction = desired_direction
 * and final_direction = surface_normal.
 */
template<typename ScalarType>
Matrix<ScalarType> createRotationMatrixFromUnitVectors(
			           const Vector<ScalarType> &initial_direction,
			           const Vector<ScalarType> &final_direction );

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_MatrixHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_MATRIX_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Geometry_MatrixHelpers.hpp
//---------------------------------------------------------------------------//
