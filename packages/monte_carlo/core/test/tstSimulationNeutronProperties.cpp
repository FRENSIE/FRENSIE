//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationNeutronProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation neutron properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationNeutronProperties.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationNeutronProperties, defaults )
{
  MonteCarlo::SimulationNeutronProperties properties;
  
  TEST_EQUALITY_CONST( properties.getFreeGasThreshold(), 400.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMinNeutronEnergy(), 1e-11 );
  TEST_EQUALITY_CONST( properties.getMinNeutronEnergy(), 1e-11 );
  TEST_EQUALITY_CONST( properties.getMaxNeutronEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMaxNeutronEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Test that the free gas thermal treatment temp threshold can be set
TEUCHOS_UNIT_TEST( SimulationNeutronProperties, setFreeGasThreshold )
{
  MonteCarlo::SimulationNeutronProperties properties;
  
  properties.setFreeGasThreshold( 1000.0 );

  TEST_EQUALITY_CONST( properties.getFreeGasThreshold(), 1000.0 );
}

//---------------------------------------------------------------------------//
// Test that the min neutron energy can be set
TEUCHOS_UNIT_TEST( SimulationNeutronProperties, setMinNeutronEnergy )
{
  MonteCarlo::SimulationNeutronProperties properties;
  
  properties.setMinNeutronEnergy( 1e-8 );

  TEST_EQUALITY_CONST( properties.getMinNeutronEnergy(), 1e-8 );
}

//---------------------------------------------------------------------------//
// Test that the max neutron energy can be set
TEUCHOS_UNIT_TEST( SimulationNeutronProperties, setMaxNeutronEnergy )
{
  MonteCarlo::SimulationNeutronProperties properties;
  
  properties.setMaxNeutronEnergy( 15.0 );

  TEST_EQUALITY_CONST( properties.getMaxNeutronEnergy(), 15.0 );
}

//---------------------------------------------------------------------------//
// end tstSimulationNeutronProperties.cpp
//---------------------------------------------------------------------------//
