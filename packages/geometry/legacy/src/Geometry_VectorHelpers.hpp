//---------------------------------------------------------------------------//
//!
//! \file   Geometry_VectorHelpers.hpp
//! \author Alex Robinson
//! \brief  Vector helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_VECTOR_HELPERS_HPP
#define GEOMETRY_VECTOR_HELPERS_HPP

// FRENSIE Includes
#include "Geometry_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Axis.hpp"

namespace Geometry{

// Create a vector
template<typename ScalarType>
Vector<ScalarType> createVector( const ScalarType x, 
				 const ScalarType y,
				 const ScalarType z );

// Create a vector from a tuple struct
template<typename ScalarType>
Vector<ScalarType> createVector( 
		const Utility::Trip<ScalarType,ScalarType,ScalarType> &tuple );

//! Create a x-axis vector
template<typename ScalarType>
Vector<ScalarType> createXAxisVector(
  const Utility::AxisVectorDirection direction = Utility::POSITIVE_DIRECTION );

//! Create a y-axis vector
template<typename ScalarType>
Vector<ScalarType> createYAxisVector(
  const Utility::AxisVectorDirection direction = Utility::POSITIVE_DIRECTION );

//! Create a z-axis vector
template<typename ScalarType>
Vector<ScalarType> createZAxisVector(
  const Utility::AxisVectorDirection direction = Utility::POSITIVE_DIRECTION );

//! Create a vector that satisfies the relationship n*x0+const = 0 (ret. x0)
template<typename ScalarType>
Vector<ScalarType> createZeroingVector( const Vector<ScalarType> &vector,
					const ScalarType constant_term );

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_VectorHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_VECTOR_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Geometry_VectorHelpers.hpp
//---------------------------------------------------------------------------//
