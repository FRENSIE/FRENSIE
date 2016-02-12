//---------------------------------------------------------------------------//
//!
//! \file   Utility_HexahedronHelpers.cpp
//! \author Luke Kersting, Philip Britt
//! \brief  Hexahedron helper functions
//! 
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_HexahedronHelpers.hpp"
#include "Utility_ContractException.hpp"
#include <moab/Matrix3.hpp>

namespace Utility{

// Calculate the volume of a hexahedron
double calculateHexahedronVolume( const double x_plane_set[2],
				  const double y_plane_set[2],
				  const double z_plane_set[2] )
{
  
  
  double volume = (x_plane_set[2] - x_plane_set[1]) * (y_plane_set[2] - y_plane_set[1]) * (z_plane_set[2] - z_plane_set[1]);

  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( volume ) );
  testPostcondition( volume > 0.0 );

  return volume;
}

void findPlanarSets( double x_plane_set[2],
                     double y_plane_set[2],
                     double z_plane_set[2],
                     const Teuchos::TwoDArray<double>& vertex_set(8,3))
{
        x_plane_set[0] = vertex_set[0][0];
        x_plane_set[1] = vertex_set[2][0];
        y_plane_set[0] = vertex_set[0][1];
        y_plane_set[1] = vertex_set[4][1];
        z_plane_set[0] = vertex_set[3][2];
        z_plane_set[1] = vertex_set[0][2];

}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HexahedronHelpers.cpp
//---------------------------------------------------------------------------//
