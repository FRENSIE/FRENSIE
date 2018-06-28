//---------------------------------------------------------------------------//
//!
//! \file   Utility_TetrahedronHelpers.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tetrahedron helper functions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TETRAHEDRON_HELPERS_HPP
#define UTILITY_TETRAHEDRON_HELPERS_HPP

// Std Lib Includes
#include <vector>

namespace Utility{

//! Calculate the volume of a tetrahedron
double calculateTetrahedronVolume( const double vertex_a[3],
				   const double vertex_b[3],
				   const double vertex_c[3],
				   const double reference_vertex[3] );

//! Calculate tetrahedron barycentric transform matrix
void calculateBarycentricTransformMatrix( const double vertex_a[3],
					  const double vertex_b[3],
					  const double vertex_c[3],
					  const double reference_vertex[3],
					  double transform_arrays[9] );

//! Return if a point is in a tet
bool isPointInTet( const double point[3],
                   const double reference_vertex[3],
                   const double barycentric_matrix[9],
                   const double tol = 1e-6 );

} // end Utility namespace

#endif // end UTILITY_TETRAHEDRON_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_TetrahedronHelpers.hpp
//---------------------------------------------------------------------------//
