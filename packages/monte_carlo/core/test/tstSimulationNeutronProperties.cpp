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
  TEST_EQUALITY_CONST( MonteCarlo::SimulationNeutronProperties::getFreeGasThreshold(),
                       400.0 );
  TEST_EQUALITY_CONST( 
               MonteCarlo::SimulationNeutronProperties::getAbsoluteMinNeutronEnergy(),
               1e-11 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationNeutronProperties::getMinNeutronEnergy(),
                       1e-11 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationNeutronProperties::getMaxNeutronEnergy(),
                       20.0 );
  TEST_EQUALITY_CONST( 
               MonteCarlo::SimulationNeutronProperties::getAbsoluteMaxNeutronEnergy(),
               20.0 );
}


//---------------------------------------------------------------------------//
// Test that the free gas thermal treatment temp threshold can be set
TEUCHOS_UNIT_TEST( SimulationNeutronProperties, setFreeGasThreshold )
{
  double default_value = 
    MonteCarlo::SimulationNeutronProperties::getFreeGasThreshold();

  MonteCarlo::SimulationNeutronProperties::setFreeGasThreshold( 1000.0 );

  TEST_ASSERT( MonteCarlo::SimulationNeutronProperties::getFreeGasThreshold() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationNeutronProperties::getFreeGasThreshold(),
		       1000.0 );

  // Reset to the default
  MonteCarlo::SimulationNeutronProperties::setFreeGasThreshold( default_value );
}

//---------------------------------------------------------------------------//
// Test that the min neutron energy can be set
TEUCHOS_UNIT_TEST( SimulationNeutronProperties, setMinNeutronEnergy )
{
  double default_value = 
    MonteCarlo::SimulationNeutronProperties::getMinNeutronEnergy();

  MonteCarlo::SimulationNeutronProperties::setMinNeutronEnergy( 1e-8 );
  
  TEST_ASSERT( MonteCarlo::SimulationNeutronProperties::getMinNeutronEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationNeutronProperties::getMinNeutronEnergy(),
		       1e-8 );

  // Reset the default
  MonteCarlo::SimulationNeutronProperties::setMinNeutronEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that the max neutron energy can be set
TEUCHOS_UNIT_TEST( SimulationNeutronProperties, setMaxNeutronEnergy )
{
  double default_value = 
    MonteCarlo::SimulationNeutronProperties::getMaxNeutronEnergy();

  MonteCarlo::SimulationNeutronProperties::setMaxNeutronEnergy( 15.0 );
  
  TEST_ASSERT( MonteCarlo::SimulationNeutronProperties::getMaxNeutronEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationNeutronProperties::getMaxNeutronEnergy(),
		       15.0 );

  // Reset the default
  MonteCarlo::SimulationNeutronProperties::setMaxNeutronEnergy( default_value );
}

//---------------------------------------------------------------------------//
// end tstSimulationNeutronProperties.cpp
//---------------------------------------------------------------------------//
