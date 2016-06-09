//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationElectronProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation electron properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationElectronProperties, defaults )
{
  TEST_EQUALITY_CONST(
	MonteCarlo::SimulationElectronProperties::getAbsoluteMinElectronEnergy(),
	1.5e-5 );
  TEST_EQUALITY_CONST(
	MonteCarlo::SimulationElectronProperties::getMinElectronEnergy(),
	1.5e-5 );
  TEST_EQUALITY_CONST(
	MonteCarlo::SimulationElectronProperties::getMaxElectronEnergy(),
	20.0 );
  TEST_EQUALITY_CONST(
	MonteCarlo::SimulationElectronProperties::getAbsoluteMaxElectronEnergy(),
	20.0 );
  TEST_ASSERT(
	MonteCarlo::SimulationElectronProperties::isAtomicRelaxationModeOn() );
  TEST_EQUALITY_CONST(
	MonteCarlo::SimulationElectronProperties::getBremsstrahlungAngularDistributionFunction(),
	MonteCarlo::TWOBS_DISTRIBUTION );
  TEST_EQUALITY_CONST(
	MonteCarlo::SimulationElectronProperties::getElasticCutoffAngleCosine(),
	0.999999 );
}

//---------------------------------------------------------------------------//
// Test that the min electron energy can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setMinElectronEnergy )
{
  double default_value =
    MonteCarlo::SimulationElectronProperties::getMinElectronEnergy();

  MonteCarlo::SimulationElectronProperties::setMinElectronEnergy( 1e-2 );

  TEST_ASSERT( MonteCarlo::SimulationElectronProperties::getMinElectronEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationElectronProperties::getMinElectronEnergy(),
		      1e-2 );

  // Reset the default value
  MonteCarlo::SimulationElectronProperties::setMinElectronEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that the max electron energy can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setMaxElectronEnergy )
{
  double default_value =
    MonteCarlo::SimulationElectronProperties::getMaxElectronEnergy();

  MonteCarlo::SimulationElectronProperties::setMaxElectronEnergy( 15.0 );

  TEST_ASSERT( MonteCarlo::SimulationElectronProperties::getMaxElectronEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationElectronProperties::getMaxElectronEnergy(),
		      15.0 );

  // Reset the default value
  MonteCarlo::SimulationElectronProperties::setMaxElectronEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that atomic relaxation mode can be turned off
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setAtomicRelaxationModeOff )
{
  TEST_ASSERT( MonteCarlo::SimulationElectronProperties::isAtomicRelaxationModeOn() );

  MonteCarlo::SimulationElectronProperties::setAtomicRelaxationModeOff();

  TEST_ASSERT( !MonteCarlo::SimulationElectronProperties::isAtomicRelaxationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the bremsstrahlung angular distribution function can be turned to Dipole
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setBremsstrahlungAngularDistributionFunction_Dipole )
{
  TEST_EQUALITY_CONST(
    MonteCarlo::SimulationElectronProperties::getBremsstrahlungAngularDistributionFunction(),
	MonteCarlo::TWOBS_DISTRIBUTION );

  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::SimulationElectronProperties::setBremsstrahlungAngularDistributionFunction(
                          function );

  TEST_EQUALITY_CONST(
    MonteCarlo::SimulationElectronProperties::getBremsstrahlungAngularDistributionFunction(),
	MonteCarlo::DIPOLE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the bremsstrahlung angular distribution function can be turned to Tabular
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setBremsstrahlungAngularDistributionFunction_Tabular )
{
  TEST_EQUALITY_CONST(
    MonteCarlo::SimulationElectronProperties::getBremsstrahlungAngularDistributionFunction(),
	MonteCarlo::DIPOLE_DISTRIBUTION );

  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::TABULAR_DISTRIBUTION;

  MonteCarlo::SimulationElectronProperties::setBremsstrahlungAngularDistributionFunction(
                          function );

  TEST_EQUALITY_CONST(
    MonteCarlo::SimulationElectronProperties::getBremsstrahlungAngularDistributionFunction(),
	MonteCarlo::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the elastic cutoff angle cosine can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setElasticCutoffAngleCosine )
{
  TEST_EQUALITY(
        MonteCarlo::SimulationElectronProperties::getElasticCutoffAngleCosine(),
        0.999999 );

  MonteCarlo::SimulationElectronProperties::setElasticCutoffAngleCosine( 0.9 );

  TEST_EQUALITY(
        MonteCarlo::SimulationElectronProperties::getElasticCutoffAngleCosine(),
        0.9 );
}

//---------------------------------------------------------------------------//
// end tstSimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
