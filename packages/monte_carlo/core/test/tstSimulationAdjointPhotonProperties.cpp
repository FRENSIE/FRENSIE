//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationAdjointPhotonProperties.cpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationAdjointPhotonProperties, defaults )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;
  
  TEST_EQUALITY_CONST( properties.getAbsoluteMinAdjointPhotonEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( properties.getMinAdjointPhotonEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( properties.getMaxAdjointPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMaxAdjointPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getNumberOfAdjointPhotonHashGridBins(),
                       500 );
  TEST_EQUALITY_CONST( properties.getIncoherentAdjointModelType(),
                       MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
}

//---------------------------------------------------------------------------//
// Check that the min adjoint photon energy can be set
TEUCHOS_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setMinAdjointPhotonEnergy )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;
  
  properties.setMinAdjointPhotonEnergy( 1e-2 );

  TEST_EQUALITY_CONST( properties.getMinAdjointPhotonEnergy(), 1e-2 );
}

//---------------------------------------------------------------------------//
// Check that the max adjoint photon energy can be set
TEUCHOS_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setMaxAdjointPhotonEnergy )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;
  
  properties.setMaxAdjointPhotonEnergy( 15.0 );

  TEST_EQUALITY_CONST( properties.getMaxAdjointPhotonEnergy(), 15.0 );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photon hash grid bins can be set
TEUCHOS_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setNumberOfAdjointPhotonHashGridBins )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;
  
  properties.setNumberOfAdjointPhotonHashGridBins( 750 );

  TEST_EQUALITY_CONST( properties.getNumberOfAdjointPhotonHashGridBins(),
                       750 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent adjoint model type can be set
TEUCHOS_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setIncoherentAdjointModelType )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;
  
  properties.setIncoherentAdjointModelType(
                                     MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );

  TEST_EQUALITY_CONST( properties.getIncoherentAdjointModelType(),
                       MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );
}

//---------------------------------------------------------------------------//
// end tstSimulationAdjointPhotonProperties.cpp
//---------------------------------------------------------------------------//
