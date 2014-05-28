//---------------------------------------------------------------------------//
//!
//! \file   Geometry_IntersectionPointHelpers.hpp
//! \author Alex Robinson
//! \brief  IntersectionPoint class helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_INTERSECTION_POINT_HELPERS_HPP
#define GEOMETRY_INTERSECTION_POINT_HELPERS_HPP

// FRENSIE Includes
#include "Geometry_IntersectionPoint.hpp"
#include "Geometry_Surface.hpp"

namespace Geometry{

//! Calculate the intersection point created by three planes
template<typename OrdinalType, typename ScalarType>
IntersectionPoint<OrdinalType,ScalarType> createIntersectionPoint(
	       const Surface<OrdinalType,ScalarType> &primary_surface,
	       const Surface<OrdinalType,ScalarType> &secondary_surface,
	       const Surface<OrdinalType,ScalarType> &tertiary_surface );

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_IntersectionPointHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_INTERSECTION_POINT_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Geometry_IntersectionPointHelpers.hpp
//---------------------------------------------------------------------------//
