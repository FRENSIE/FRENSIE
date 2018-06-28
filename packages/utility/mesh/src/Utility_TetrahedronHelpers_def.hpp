//---------------------------------------------------------------------------//
//!
//! \file   Utility_TetrahedronHelpers_def.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tetrahedron helper function template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TETRAHEDRON_HELPERS_DEF_HPP
#define UTILITY_TETRAHEDRON_HELPERS_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

// Determine if a point is in a given tet
/*! \details Make sure the matrix has dimensions 3x3!
 */
template<typename TestPoint, typename ReferencePoint, typename Matrix>
bool isPointInTet( const TestPoint& point,
                   const ReferencePoint& reference_vertex,
		   const Matrix& matrix,
		   const double tol )
{
  double barycentric_location_vector[3];
  barycentric_location_vector[0] = matrix( 0, 0 ) *
                                   (point[0] - reference_vertex[0]) +
                                   matrix( 0, 1 ) *
                                   (point[1] - reference_vertex[1]) +
                                   matrix( 0, 2 ) *
                                   (point[2] - reference_vertex[2]);
  barycentric_location_vector[1] = matrix( 1, 0 ) *
                                   (point[0] - reference_vertex[0]) +
                                   matrix( 1, 1 ) *
                                   (point[1] - reference_vertex[1]) +
                                   matrix( 1, 2 ) *
                                   (point[2] - reference_vertex[2]);
  barycentric_location_vector[2] = matrix( 2, 0 ) *
                                   (point[0] - reference_vertex[0]) +
                                   matrix( 2, 1 ) *
                                   (point[1] - reference_vertex[1]) +
                                   matrix( 2, 2 ) *
                                   (point[2] - reference_vertex[2]);

  if ( ( barycentric_location_vector[0] < -tol ||
         barycentric_location_vector[1] < -tol ||
         barycentric_location_vector[2] < -tol ) ||
       ( barycentric_location_vector[0] + barycentric_location_vector[1] +
         barycentric_location_vector[2] > 1.0 + tol ) )
  {
    return false;
  }
  else
  {
    return true;
  }
}



} // end Utility namespace

#endif // end UTILITY_TETRAHEDRON_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TetrahedronHelpers_def.hpp
//---------------------------------------------------------------------------//
