//---------------------------------------------------------------------------//
//!
//! \file   Utility_TetrahedronHelpers.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tetrahedron helper functions
//! 
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_TetrahedronHelpers.hpp"
#include "Utility_ContractException.hpp"
#include <moab/Matrix3.hpp>

namespace Utility{

// Calculate the volume of a tetrahedron
double calculateTetrahedronVolume( const double vertex_a[3],
				   const double vertex_b[3],
				   const double vertex_c[3],
				   const double reference_vertex[3] )
{
  double a1 = vertex_a[0] - reference_vertex[0];
  double a2 = vertex_a[1] - reference_vertex[1];
  double a3 = vertex_a[2] - reference_vertex[2];
  double b1 = vertex_b[0] - reference_vertex[0];
  double b2 = vertex_b[1] - reference_vertex[1];
  double b3 = vertex_b[2] - reference_vertex[2];
  double c1 = vertex_c[0] - reference_vertex[0];
  double c2 = vertex_c[1] - reference_vertex[1];
  double c3 = vertex_c[2] - reference_vertex[2];
  
  double volume =
    fabs( a1*(b2*c3-b3*c2) + a2*(b3*c1-b1*c3) + a3*(b1*c2-b2*c1) )/6.0;

  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( volume ) );
  testPostcondition( volume > 0.0 );

  return volume;
}

// Calculate tetrahedron barycentric transform matrix                        
template<>
void calculateBarycentricTransformMatrix<moab::Matrix3>( 
					       const double vertex_a[3],
					       const double vertex_b[3],
					       const double vertex_c[3],
					       const double reference_vertex[3],
					       moab::Matrix3& matrix )
{
  matrix( 0, 0 ) = vertex_a[0] - reference_vertex[0];
  matrix( 0, 1 ) = vertex_b[0] - reference_vertex[0];
  matrix( 0, 2 ) = vertex_c[0] - reference_vertex[0];
  matrix( 1, 0 ) = vertex_a[1] - reference_vertex[1];
  matrix( 1, 1 ) = vertex_b[1] - reference_vertex[1];
  matrix( 1, 2 ) = vertex_c[1] - reference_vertex[1];
  matrix( 2, 0 ) = vertex_a[2] - reference_vertex[2];
  matrix( 2, 1 ) = vertex_b[2] - reference_vertex[2];
  matrix( 2, 2 ) = vertex_c[2] - reference_vertex[2];
  
  // Check that the tet is valid (non-singular transform matrix)
  bool is_tet_valid = matrix.invert();

  testPrecondition( is_tet_valid );
} 

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TetrahedronHelpers.cpp
//---------------------------------------------------------------------------//
