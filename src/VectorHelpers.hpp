//---------------------------------------------------------------------------//
//!
//! \file   VectorHelpers.hpp
//! \author Alex Robinson
//! \brief  Vector helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef VECTOR_HELPERS_HPP
#define VECTOR_HELPERS_HPP

// FACEMC Includes
#include "Vector.hpp"
#include "Tuple.hpp"
#include "Axis.hpp"

namespace FACEMC{

// Create a vector
template<typename ScalarType>
Vector<ScalarType> createVector( const ScalarType x, 
				 const ScalarType y,
				 const ScalarType z );

// Create a vector from a tuple struct
template<typename ScalarType>
Vector<ScalarType> createVector( 
			 const Trip<ScalarType,ScalarType,ScalarType> &tuple );

//! Create a x-axis vector
template<typename ScalarType>
Vector<ScalarType> createXAxisVector(
		    const AxisVectorDirection direction = POSITIVE_DIRECTION );

//! Create a y-axis vector
template<typename ScalarType>
Vector<ScalarType> createYAxisVector(
		    const AxisVectorDirection direction = POSITIVE_DIRECTION );

//! Create a z-axis vector
template<typename ScalarType>
Vector<ScalarType> createZAxisVector(
		    const AxisVectorDirection direction = POSITIVE_DIRECTION );

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
