//---------------------------------------------------------------------------//
//!
//! \file   Utility_TetrahedronHelpers.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tetrahedron helper functions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>
#include <cstring>

// FRENSIE Includes
#include "Utility_TetrahedronHelpers.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

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

  testPostcondition( !QuantityTraits<double>::isnaninf( volume ) );
  testPostcondition( volume > 0.0 );

  return volume;
}

// Calculate tetrahedron barycentric transform matrix
void calculateBarycentricTransformMatrix( const double vertex_a[3],
                                          const double vertex_b[3],
                                          const double vertex_c[3],
                                          const double reference_vertex[3],
                                          double matrix[9] )
{
  double a0 = vertex_a[0] - reference_vertex[0]; // 0
  double a1 = vertex_b[0] - reference_vertex[0]; // 1
  double a2 = vertex_c[0] - reference_vertex[0]; // 2
  double b0 = vertex_a[1] - reference_vertex[1]; // 3
  double b1 = vertex_b[1] - reference_vertex[1]; // 4
  double b2 = vertex_c[1] - reference_vertex[1]; // 5
  double c0 = vertex_a[2] - reference_vertex[2]; // 6
  double c1 = vertex_b[2] - reference_vertex[2]; // 7
  double c2 = vertex_c[2] - reference_vertex[2]; // 8
  
  // Compute the determinant
  double determinant = a0*b1*c2 + a1*b2*c0 + a2*b0*c1 -
    a0*b2*c1 - a1*b0*c2 - a2*b1*c0;
  
  TEST_FOR_EXCEPTION( determinant == 0,
                      std::runtime_error,
                      "A barycentric transform matrix cannot be constructed "
                      "because the points of the tetrahedron are invalid!" );

  // Compute the inverse matrix
  double inverse_determinant = 1.0/determinant;

  matrix[0] = inverse_determinant*(b1*c2 - b2*c1);
  matrix[1] = inverse_determinant*(a2*c1 - c2*a1);
  matrix[2] = inverse_determinant*(a1*b2 - b1*a2);
  matrix[3] = inverse_determinant*(b2*c0 - c2*b0);
  matrix[4] = inverse_determinant*(a0*c2 - c0*a2);
  matrix[5] = inverse_determinant*(a2*b0 - b2*a0);
  matrix[6] = inverse_determinant*(b0*c1 - c0*b1);
  matrix[7] = inverse_determinant*(a1*c0 - c1*a0);
  matrix[8] = inverse_determinant*(a0*b1 - b0*a1);
}

// Return if a point is in a tet
bool isPointInTet( const double point[3],
                   const double reference_vertex[3],
                   const double barycentric_matrix[9],
                   const double tol )
{
  double barycentric_location_vector[3];

  barycentric_location_vector[0] = barycentric_matrix[0] *
                                   (point[0] - reference_vertex[0]) +
                                   barycentric_matrix[1] *
                                   (point[1] - reference_vertex[1]) +
                                   barycentric_matrix[2] *
                                   (point[2] - reference_vertex[2]);
  barycentric_location_vector[1] = barycentric_matrix[3] *
                                   (point[0] - reference_vertex[0]) +
                                   barycentric_matrix[4] *
                                   (point[1] - reference_vertex[1]) +
                                   barycentric_matrix[5] *
                                   (point[2] - reference_vertex[2]);
  barycentric_location_vector[2] = barycentric_matrix[6] *
                                   (point[0] - reference_vertex[0]) +
                                   barycentric_matrix[7] *
                                   (point[1] - reference_vertex[1]) +
                                   barycentric_matrix[8] *
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

//---------------------------------------------------------------------------//
// end Utility_TetrahedronHelpers.cpp
//---------------------------------------------------------------------------//
