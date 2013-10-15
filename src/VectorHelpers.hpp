//---------------------------------------------------------------------------//
//!
//! \file   VectorHelpers.hpp
//! \author Alex Robinson
//! \brief  Vector helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef VECTOR_HELPERS_HPP
#define VECTOR_HELPERS_HPP

#include "Vector.hpp"

namespace FACEMC{

//! Enum for specifying which axis to align eigenvectors with
enum Axis{
  X_AXIS,
  Y_AXIS,
  Z_AXIS,
  UNDEFINED_AXIS
};

//! Direction of the axis vector that will be created
enum AxisVectorDirection{
  POSITIVE_DIRECTION,
  NEGATIVE_DIRECTION
};

// Create a vector
template<typename ScalarType>
Vector<ScalarType> createVector( const ScalarType x, 
				 const ScalarType y,
				 const ScalarType z );

//! Create a x-axis vector
template<typename ScalarType>
Vector<ScalarType> createXAxisVector(
		          AxisVectorDirection direction = POSITIVE_DIRECTION );

//! Create a y-axis vector
template<typename ScalarType>
Vector<ScalarType> createYAxisVector(
			  AxisVectorDirection direction = POSITIVE_DIRECTION );

//! Create a z-axis vector
template<typename ScalarType>
Vector<ScalarType> createZAxisVector(
			  AxisVectorDirection direction = POSITIVE_DIRECTION );

//! Create a vector that satisfies the relationship n*x0+const = 0 (ret. x0)
template<typename ScalarType>
Vector<ScalarType> createZeroingVector( const Vector<ScalarType> &vector,
					const ScalarType constant_term );

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "VectorHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end VECTOR_HELPERS_HPP

//---------------------------------------------------------------------------//
// end VectorHelpers.hpp
//---------------------------------------------------------------------------//
