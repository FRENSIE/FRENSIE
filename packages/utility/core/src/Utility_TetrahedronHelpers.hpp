//---------------------------------------------------------------------------//
//!
//! \file   Utility_TetrahedronHelpers.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tetrahedron helper functions
//! 
//---------------------------------------------------------------------------//

#ifndef UTILITY_TETRAHEDRON_HELPERS_HPP
#define UTILITY_TETRAHEDRON_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseMatrix.hpp>

// Moab Includes
#include <moab/CartVect.hpp>
#include <moab/Matrix3.hpp>

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

//! Calculate tetrahedron barycentric transform matrix
template<typename Matrix>
void calculateBarycentricTransformMatrix( const double vertex_a[3],
                                          const double vertex_b[3],
                                          const double vertex_c[3],
                                          const double vertex_d[3],
					  Matrix& matrix );

//! Calculate tetrahedron barycentric transform matrix
template<typename Matrix>
void calculateBarycentricTransformMatrix( const moab::CartVect& vertex_a,
					  const moab::CartVect& vertex_b,
					  const moab::CartVect& vertex_c,
					  const moab::CartVect& vertex_d,
					  Matrix& matrix );

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

// Calculate tetrahedron barycentric transform matrix
template<typename Matrix>
inline void calculateBarycentricTransformMatrix(
					  const moab::CartVect& vertex_a,
					  const moab::CartVect& vertex_b,
					  const moab::CartVect& vertex_c, 
					  const moab::CartVect& vertex_d,
					  Matrix& matrix )
{
  calculateBarycentricTransformMatrix( vertex_a.array(),
				       vertex_b.array(),
				       vertex_c.array(),
				       vertex_d.array(),
				       matrix );
}

// Calculate tetrahedron barycentric transform matrix
inline void calculateBarycentricTransformMatrix( const double vertex_a[3],
						 const double vertex_b[3],
						 const double vertex_c[3],
						 const double vertex_d[3],
						 double transform_arrays[9] )
{
  // Create temporary matrix
  Teuchos::SerialDenseMatrix<int,double> tmp_matrix( 3, 3 );

  calculateBarycentricTransformMatrix( vertex_a, 
				       vertex_b,
				       vertex_c,
				       vertex_d,
				       tmp_matrix );

  // Copy the matrix into the array
  transform_arrays[0] = tmp_matrix( 0, 0 );
  transform_arrays[1] = tmp_matrix( 0, 1 );
  transform_arrays[2] = tmp_matrix( 0, 2 );
}


// Calculate the volume of a tetrahedron
inline void calculateBarycentricTransformMatrix( const moab::CartVect& vertex_a,
					         const moab::CartVect& vertex_b,
					         const moab::CartVect& vertex_c,
					         const moab::CartVect& vertex_d,
				                 double transform_arrays[9] )
{
  return calculateBarycentricTransformMatrix( vertex_a.array(),
				              vertex_b.array(),
				              vertex_c.array(),
				              vertex_d.array(),
				              transform_arrays );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_TetrahedronHelpers_def.hpp"

//---------------------------------------------------------------------------//


#endif // end UTILITY_TETRAHEDRON_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_TetrahedronHelpers.hpp
//---------------------------------------------------------------------------//
