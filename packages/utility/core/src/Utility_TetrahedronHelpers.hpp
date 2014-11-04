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
				   const double reference_vertex[3] );

//! Calculate the volume of a tetrahedron
double calculateTetrahedronVolume( const moab::CartVect& vertex_a,
				   const moab::CartVect& vertex_b,
				   const moab::CartVect& vertex_c,
				   const moab::CartVect& reference_vertex );

//! Calculate tetrahedron barycentric transform matrix
template<typename Matrix>
void calculateBarycentricTransformMatrix( const double vertex_a[3],
                                          const double vertex_b[3],
                                          const double vertex_c[3],
                                          const double reference_vertex[3],
					  Matrix& matrix );

//! Calculate tetrahedron barycentric transform matrix
template<typename Matrix>
void calculateBarycentricTransformMatrix( const moab::CartVect& vertex_a,
					  const moab::CartVect& vertex_b,
					  const moab::CartVect& vertex_c,
					  const moab::CartVect& reference_vertex,
					  Matrix& matrix );

//! Calculate tetrahedron barycentric transform matrix
void calculateBarycentricTransformMatrix( const double vertex_a[3],
					  const double vertex_b[3],
					  const double vertex_c[3],
					  const double reference_vertex[3],
					  double transform_arrays[9] );

//! Calculate the volume of a tetrahedron
void calculateBarycentricTransformMatrix( const moab::CartVect& vertex_a,
					  const moab::CartVect& vertex_b,
					  const moab::CartVect& vertex_c,
					  const moab::CartVect& reference_vertex,
					  double transform_arrays[9] );

//! Return if a point is in a tet
template<typename Matrix>                                                      
bool isPointInTet( const double point[3],    
		   Matrix& matrix );

//! Return if a point is in a tet
template<typename Matrix>                                                      
bool isPointInTet( const moab::CartVect& point,    
		   Matrix& matrix );
  
//! Return if a point is in a tet                                             
bool isPointInTet( const double point[3],    
		   double barycentric_array[9] );

//! Return if a point is in a tet                                             
bool isPointInTet( const moab::CartVect& point,    
		   double barycentric_array[9] );
					  
                
// Calculate the volume of a tetrahedron
inline double calculateTetrahedronVolume( const moab::CartVect& vertex_a,
					  const moab::CartVect& vertex_b,
					  const moab::CartVect& vertex_c,
					  const moab::CartVect& reference_vertex )
{
  return calculateTetrahedronVolume( vertex_a.array(),
				     vertex_b.array(),
				     vertex_c.array(),
				     reference_vertex.array() );
}

// Calculate tetrahedron barycentric transform matrix
template<typename Matrix>
inline void calculateBarycentricTransformMatrix(
					  const moab::CartVect& vertex_a,
					  const moab::CartVect& vertex_b,
					  const moab::CartVect& vertex_c, 
					  const moab::CartVect& reference_vertex,
					  Matrix& matrix )
{
  calculateBarycentricTransformMatrix( vertex_a.array(),
				       vertex_b.array(),
				       vertex_c.array(),
				       reference_vertex.array(),
				       matrix );
}

// Calculate tetrahedron barycentric transform matrix
inline void calculateBarycentricTransformMatrix( const double vertex_a[3],
						 const double vertex_b[3],
						 const double vertex_c[3],
						 const double reference_vertex[3],
						 double transform_arrays[9] )
{
  // Create temporary matrix
  Teuchos::SerialDenseMatrix<int,double> tmp_matrix( 3, 3 );

  calculateBarycentricTransformMatrix( vertex_a, 
				       vertex_b,
				       vertex_c,
				       reference_vertex,
				       tmp_matrix );

  // Copy the matrix into the array
  transform_arrays[0] = tmp_matrix( 0, 0 );
  transform_arrays[1] = tmp_matrix( 0, 1 );
  transform_arrays[2] = tmp_matrix( 0, 2 );
  transform_arrays[3] = tmp_matrix( 1, 0 );
  transform_arrays[4] = tmp_matrix( 1, 1 );
  transform_arrays[5] = tmp_matrix( 1, 2 );
  transform_arrays[6] = tmp_matrix( 2, 0 );
  transform_arrays[7] = tmp_matrix( 2, 1 );
  transform_arrays[8] = tmp_matrix( 2, 2 );
}


// Calculate the volume of a tetrahedron
inline void calculateBarycentricTransformMatrix( const moab::CartVect& vertex_a,
					         const moab::CartVect& vertex_b,
					         const moab::CartVect& vertex_c,
					         const moab::CartVect& reference_vertex,
				                 double transform_arrays[9] )
{
  return calculateBarycentricTransformMatrix( vertex_a.array(),
				              vertex_b.array(),
				              vertex_c.array(),
				              reference_vertex.array(),
				              transform_arrays );
}

// Return if a point is in a tet
template<typename Matrix>                                                      
inline bool isPointInTet( const moab::CartVect& point,    
		   Matrix& matrix )
{
  return isPointInTet( point.array(),
                       matrix );
}

// Return if a point is in a tet                                                
inline bool isPointInTet( const double point[3],    
		          double barycentric_array[9] )
{
  // Create temporary matrix
  Teuchos::SerialDenseMatrix<int,double> tmp_matrix( 3, 3 );
  tmp_matrix( 0, 0 ) = barycentric_array[0];
  tmp_matrix( 0, 1 ) = barycentric_array[1];
  tmp_matrix( 0, 2 ) = barycentric_array[2];
  tmp_matrix( 1, 0 ) = barycentric_array[3];
  tmp_matrix( 1, 1 ) = barycentric_array[4];
  tmp_matrix( 1, 2 ) = barycentric_array[5];
  tmp_matrix( 2, 0 ) = barycentric_array[6];
  tmp_matrix( 2, 1 ) = barycentric_array[7];
  tmp_matrix( 2, 2 ) = barycentric_array[8];
  
  return isPointInTet( point,
                       tmp_matrix );
}

// Return if a point is in a tet                                                   
inline bool isPointInTet( const moab::CartVect& point,    
		          double barycentric_array[9] )
{
  return isPointInTet( point.array(),
                       barycentric_array);
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
