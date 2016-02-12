//---------------------------------------------------------------------------//
//!
//! \file   Utility_TetrahedronHelpers_def.hpp
//! \author Luke Kersting, Philip Britt
//! \brief  Tetrahedron helper function template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TETRAHEDRON_HELPERS_DEF_HPP
#define UTILITY_TETRAHEDRON_HELPERS_DEF_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseSolver.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_BLAS_types.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

//only need points a,b,d,e - rewrite code to utilize only those three

//note: reference_vertex1 is point a, reference_vertex2 is point g
template<typename TestPoint>      
bool isPointInHex( const TestPoint& point, 
                   const double reference_x_plane_set[2],
                   const double reference_y_plane_set[2],
                   const double reference_z_plane_set[2],
                   const double tol)
{
  
  bool inside_hex = true;
  if(point[1] > reference_x_plane_set[2] + tol || point[1] < reference_x_plane_set[1] - tol) inside_hex = false;
  if(point[2] > reference_y_plane_set[2] + tol || point[2] < reference_y_plane_set[1] - tol) inside_hex = false;
  if(point[3] > reference_z_plane_set[2] + tol || point[3] < reference_z_plane_set[1] - tol) inside_hex = false;
  return inside_hex;

}





} // end Utility namespace

#endif // end UTILITY_TETRAHEDRON_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TetrahedronHelpers_def.hpp
//---------------------------------------------------------------------------//
