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
double calculateHexahedronVolume( const double vertex_a[3],
				  const double vertex_b[3],
				  const double vertex_c[3],
				  const double vertex_d[3],
				  const double vertex_e[3],
				  const double vertex_f[3],
				  const double vertex_g[3],
				  const double vertex_h[3] )
{
  
  
  double volume;

  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( volume ) );
  testPostcondition( volume > 0.0 );

  return volume;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HexahedronHelpers.cpp
//---------------------------------------------------------------------------//
