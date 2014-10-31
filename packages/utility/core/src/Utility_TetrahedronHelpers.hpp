//---------------------------------------------------------------------------//
//!
//! \file   Utility_TetrahedronHelpers.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tetrahedron helper functions
//! 
//---------------------------------------------------------------------------//

#ifndef UTILITY_TETRAHEDRON_HELPERS_HPP
#define UTILITY_TETRAHEDRON_HELPERS_HPP

// Moab Includes
#include <moab/CartVect.hpp>

namespace Utility{

//! Calculate the volume of a tetrahedron
double calculateTetrahedronVolume( const double vertex_a[3],
				   const double vertex_b[3],
				   const double vertex_c[3],
				   const double vertex_d[3] );

//! Calculate the volume of a tetrahedron
double calculateTetrahedronVolume( const moab::CartVect& vertex_a,
				   const moab::CartVect& vertex_b,
				   const moab::CartVect& vertex_c,
				   const moab::CartVect& vertex_d );


// Calculate the volume of a tetrahedron
inline double calculateTetrahedronVolume( const moab::CartVect& vertex_a,
					  const moab::CartVect& vertex_b,
					  const moab::CartVect& vertex_c,
					  const moab::CartVect& vertex_d )
{
  return calculateTetrahedronVolume( vertex_a.array(),
				     vertex_b.array(),
				     vertex_c.array(),
				     vertex_d.array() );
}

//! Calculate tetrahedron barycentric transform matrix
void calculateBarycentricTransformMatrix( const double vertex_a[3],
					  const double vertex_b[3],
					  const double vertex_c[3],
					  const double vertex_d[3],
					  double transform_arrays[9] );

//! Calculate the volume of a tetrahedron
void calculateBarycentricTransformMatrix( const moab::CartVect& vertex_a,
					  const moab::CartVect& vertex_b,
					  const moab::CartVect& vertex_c,
					  const moab::CartVect& vertex_d,
					  double transform_arrays[9] );
                

// Calculate the volume of a tetrahedron
/* inline double calculateBarycentricTransformMatrix( const moab::CartVect& vertex_a,
					           const moab::CartVect& vertex_b,
					           const moab::CartVect& vertex_c,
					           const moab::CartVect& vertex_d,
				              double transform_arrays[9] )
{
  return calculateBarycentricTransformMatrix( vertex_a.array(),
				              vertex_b.array(),
				              vertex_c.array(),
				              vertex_d.array(),
				              transform_arrays[9] );
}
*/
} // end Utility namespace

#endif // end UTILITY_TETRAHEDRON_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_TetrahedronHelpers.hpp
//---------------------------------------------------------------------------//
