//---------------------------------------------------------------------------//
//!
//! \file   Utility_HexahedronHelpers.hpp
//! \author Luke Kersting, Philip Britt
//! \brief  Hexahedron helper functions
//! 
//---------------------------------------------------------------------------//

#ifndef UTILITY_HEXAHEDRON_HELPERS_HPP
#define UTILITY_HEXAHEDRON_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseMatrix.hpp>
#include <Teuchos_TwoDArray.hpp>
#include <Teuchos_Array.hpp>


// Moab Includes
#include <moab/CartVect.hpp>
#include <moab/Matrix3.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

//! Calculate the volume of a hexahedron
double calculateHexahedronVolume(  const double x_plane_set[2],
				   const double y_plane_set[2],
				   const double z_plane_set[2]);

//! Calculate the volume of a hexahedron - needs to be changed


//! Return if a point is in a hex 
template<typename TestPoint>
bool isPointInHex( const TestPoint& point,
                   const double reference_x_plane_set[2],
                   const double reference_y_plane_set[2],//use some other object for these 3 parts such that I can pass by reference in order to make code more efficient
                   const double reference_z_plane_set[2],
                   const double tol);
               
// Calculate the volume of a hexahedron



void findPlanarSets(double x_plane_set[2],
                    double y_plane_set[2],
                    double z_plane_set[2],
                    const Teuchos::TwoDArray<double>& vertex_set);

// Calculate hexahedron face normal vectors
inline void findPlanarSets( const moab::CartVect& vertex_a,
			    const moab::CartVect& vertex_b,
			    const moab::CartVect& vertex_c,
			    const moab::CartVect& vertex_d,
			    const moab::CartVect& vertex_e,
			    const moab::CartVect& vertex_f,
			    const moab::CartVect& vertex_g,
			    const moab::CartVect& vertex_h,
			    Teuchos::TwoDArray<double>& vertex_set)
{
  // Test size of vertex_set for 8 rows and 3 columns
  testPrecondition(vertex_set.getNumRows() == 8);
  testPrecondition(vertex_set.getNumCols() == 3);  

  for (int i = 0; i != 3; i++) vertex_set[0][i] = vertex_a[i];
  for (int i = 0; i != 3; i++) vertex_set[1][i] = vertex_b[i];
  for (int i = 0; i != 3; i++) vertex_set[2][i] = vertex_c[i];
  for (int i = 0; i != 3; i++) vertex_set[3][i] = vertex_d[i];
  for (int i = 0; i != 3; i++) vertex_set[4][i] = vertex_e[i];
  for (int i = 0; i != 3; i++) vertex_set[5][i] = vertex_f[i];
  for (int i = 0; i != 3; i++) vertex_set[6][i] = vertex_g[i];
  for (int i = 0; i != 3; i++) vertex_set[7][i] = vertex_h[i];

  double x_plane_set[2];
  double y_plane_set[2];
  double z_plane_set[2];

  findPlanarSets( x_plane_set,
                  y_plane_set,
                  z_plane_set,
                  vertex_set);
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_HexahedronHelpers_def.hpp"

//---------------------------------------------------------------------------//


#endif // end UTILITY_HEXAHEDRON_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_HexahedronHelpers.hpp
//---------------------------------------------------------------------------//
