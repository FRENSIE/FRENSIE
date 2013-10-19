//---------------------------------------------------------------------------//
//!
//! \file   IntersectionPointHelpers.hpp
//! \author Alex Robinson
//! \brief  IntersectionPoint class helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef INTERSECTION_POINT_HELPERS_HPP
#define INTERSECTION_POINT_HELPERS_HPP

// FACEMC Includes
#include "IntersectionPoint.hpp"
#include "Surface.hpp"

namespace FACEMC{

//! Calculate the intersection point created by three planes
template<typename OrdinalType, typename ScalarType>
IntersectionPoint<OrdinalType,ScalarType> createIntersectionPoint(
	       const Surface<OrdinalType,ScalarType> &primary_surface,
	       const Surface<OrdinalType,ScalarType> &secondary_surface,
	       const Surface<OrdinalType,ScalarType> &tertiary_surface );

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "IntersectionPointHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end INTERSECTION_POINT_HELPERS_HPP

//---------------------------------------------------------------------------//
// end IntersectionPointHelpers.hpp
//---------------------------------------------------------------------------//
