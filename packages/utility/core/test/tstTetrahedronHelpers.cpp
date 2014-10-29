//---------------------------------------------------------------------------//
//!
//! \file   tstTetrahedronHelpers.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tetrahedron helper functions
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>

// FRENSIE Includes
#include "Utility_TetrahedronHelpers.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the volume of a tet can be calculated
TEUCHOS_UNIT_TEST( TetrahedronHelpers, calculateTetrahedronVolume_array )
{
  double vertex_a[3] = {0.0, 0.0, 0.0};
  double vertex_b[3] = {1.0, 0.0, 0.0};
  double vertex_c[3] = {0.0, 1.0, 0.0};
  double vertex_d[3] = {0.0, 0.0, 1.0};

  double volume = Utility::calculateTetrahedronVolume( vertex_a,
						       vertex_b,
						       vertex_c,
						       vertex_d );

  TEST_EQUALITY_CONST( volume, 1.0/6.0 );
}

//---------------------------------------------------------------------------//
// Check that the volume of a tet can be calculated
TEUCHOS_UNIT_TEST( TetrahedronHelpers, calculateTetrahedronVolume_cartvect )
{
  moab::CartVect vertex_a( 0.0, 0.0, 0.0 );
  moab::CartVect vertex_b( 1.0, 0.0, 0.0 );
  moab::CartVect vertex_c( 0.0, 1.0, 0.0 );
  moab::CartVect vertex_d( 0.0, 0.0, 1.0 );
  
  double volume = Utility::calculateTetrahedronVolume( vertex_a,
						       vertex_b,
						       vertex_c,
						       vertex_d );
  
  TEST_EQUALITY_CONST( volume, 1.0/6.0 );
}

//---------------------------------------------------------------------------//
// end tstTetrahedronHelpers.cpp
//---------------------------------------------------------------------------//
