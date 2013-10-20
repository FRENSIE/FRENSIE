//---------------------------------------------------------------------------//
//!
//! \file   IntersectionPointHelpers_def.hpp
//! \author Alex Robinson
//! \brief  IntersectionPoint class helper function definitions.
//!
//---------------------------------------------------------------------------//

#ifndef INTERSECTION_POINT_HELPERS_DEF_HPP
#define INTERSECTION_POINT_HELPERS_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"
#include "Vector.hpp"
#include "VectorHelpers.hpp"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"
#include "LinearAlgebraAlgorithms.hpp"

namespace FACEMC{

// Calculate the intersection point created by three planes
template<typename OrdinalType, typename ScalarType>
IntersectionPoint<OrdinalType,ScalarType> createIntersectionPoint(
	       const Surface<OrdinalType,ScalarType> &primary_surface,
	       const Surface<OrdinalType,ScalarType> &secondary_surface,
	       const Surface<OrdinalType,ScalarType> &tertiary_surface )
{
  // All of the surfaces must be planes
  testPrecondition( primary_surface.isPlanar() );
  testPrecondition( secondary_surface.isPlanar() );
  testPrecondition( tertiary_surface.isPlanar() );
  // None of the surface can be parallel (to guarantee a nonsingular system)
  remember( Vector<ScalarType> primary_normal = 
	    primary_surface.getLinearTermVector() );
  remember( Vector<ScalarType> secondary_normal =
	    secondary_surface.getLinearTermVector() );
  remember( Vector<ScalarType> tertiary_normal = 
	    tertiary_surface.getLinearTermVector() );
  testPrecondition( !primary_normal.isParallel( secondary_normal ) &&
		    !primary_normal.isAntiparallel( secondary_normal ) );
  testPrecondition( !primary_normal.isParallel( tertiary_normal ) &&
		    !primary_normal.isAntiparallel( tertiary_normal ) );
  testPrecondition( !secondary_normal.isParallel( tertiary_normal ) &&
		    !secondary_normal.isAntiparallel( tertiary_normal ) );
  
  // Create the system that will be solved (Ax = b)
  Matrix<ScalarType> A = 
    createMatrixFromRows( primary_surface.getLinearTermVector(),
			  secondary_surface.getLinearTermVector(),
			  tertiary_surface.getLinearTermVector() );

  Vector<ScalarType> b( -primary_surface.getConstantTerm(),
			-secondary_surface.getConstantTerm(),
			-tertiary_surface.getConstantTerm() );

  Vector<ScalarType> x = LinearAlgebra::solveSystem( A, b );

  return IntersectionPoint<OrdinalType,ScalarType>( x, 
						    primary_surface.getId(),
						    secondary_surface.getId(),
						    tertiary_surface.getId() );
}

} // end FACEMC namespace

#endif // end INTERSECTION_POINT_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end IntersectionPointHelpers_def.hpp
//---------------------------------------------------------------------------//
