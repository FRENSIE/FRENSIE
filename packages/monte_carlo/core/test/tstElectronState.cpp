//---------------------------------------------------------------------------//
//!
//! \file   tstElectronState.cpp
//! \author Luke Kersting
//! \brief  Electron state unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle type
TEUCHOS_UNIT_TEST( ElectronState, getParticleType )
{
  MonteCarlo::ElectronState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getParticleType(), MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// end tstElectronState.cpp
//---------------------------------------------------------------------------//
