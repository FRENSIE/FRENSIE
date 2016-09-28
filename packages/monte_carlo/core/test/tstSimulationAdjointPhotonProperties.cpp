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
  TEST_EQUALITY_CONST(
            MonteCarlo::SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy(),
            1e-3 );
  TEST_EQUALITY_CONST(
            MonteCarlo::SimulationAdjointPhotonProperties::getMinAdjointPhotonEnergy(),
            1e-3 );
  TEST_EQUALITY_CONST(
            MonteCarlo::SimulationAdjointPhotonProperties::getMaxAdjointPhotonEnergy(),
            20.0 );
  TEST_EQUALITY_CONST(
            MonteCarlo::SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy(),
            20.0 );
  TEST_EQUALITY_CONST(
	    MonteCarlo::SimulationAdjointPhotonProperties::getNumberOfAdjointPhotonHashGridBins(),
            500 );
  TEST_EQUALITY_CONST(
            MonteCarlo::SimulationAdjointPhotonProperties::getIncoherentAdjointModelType(),
            MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
}

//---------------------------------------------------------------------------//
// Check that the min adjoint photon energy can be set
TEUCHOS_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setMinAdjointPhotonEnergy )
{
  double default_value =
    MonteCarlo::SimulationAdjointPhotonProperties::getMinAdjointPhotonEnergy();

  MonteCarlo::SimulationAdjointPhotonProperties::setMinAdjointPhotonEnergy( 1e-2 );

  TEST_ASSERT( MonteCarlo::SimulationAdjointPhotonProperties::getMinAdjointPhotonEnergy() != default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationAdjointPhotonProperties::getMinAdjointPhotonEnergy(),
                       1e-2 );

  // Reset the default value
  MonteCarlo::SimulationAdjointPhotonProperties::setMinAdjointPhotonEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Check that the max adjoint photon energy can be set
TEUCHOS_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setMaxAdjointPhotonEnergy )
{
  double default_value =
    MonteCarlo::SimulationAdjointPhotonProperties::getMaxAdjointPhotonEnergy();

  MonteCarlo::SimulationAdjointPhotonProperties::setMaxAdjointPhotonEnergy( 15.0 );

  TEST_ASSERT( MonteCarlo::SimulationAdjointPhotonProperties::getMaxAdjointPhotonEnergy() != default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationAdjointPhotonProperties::getMaxAdjointPhotonEnergy(),
                       15.0 );

  // Reset the default value
  MonteCarlo::SimulationAdjointPhotonProperties::setMaxAdjointPhotonEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photon hash grid bins can be set
TEUCHOS_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setNumberOfAdjointPhotonHashGridBins )
{
  unsigned default_value =
    MonteCarlo::SimulationAdjointPhotonProperties::getNumberOfAdjointPhotonHashGridBins();

  MonteCarlo::SimulationAdjointPhotonProperties::setNumberOfAdjointPhotonHashGridBins( 750 );

  TEST_ASSERT(
	  MonteCarlo::SimulationAdjointPhotonProperties::getNumberOfAdjointPhotonHashGridBins() !=
	  default_value );
  TEST_EQUALITY_CONST(
	     MonteCarlo::SimulationAdjointPhotonProperties::getNumberOfAdjointPhotonHashGridBins(),
	     750 );

  // Reset the default value
  MonteCarlo::SimulationAdjointPhotonProperties::setNumberOfAdjointPhotonHashGridBins( default_value );
}

//---------------------------------------------------------------------------//
// Check that the incoherent adjoint model type can be set
TEUCHOS_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setIncoherentAdjointModelType )
{
  MonteCarlo::IncoherentAdjointModelType default_model =
    MonteCarlo::SimulationAdjointPhotonProperties::getIncoherentAdjointModelType();

  MonteCarlo::SimulationAdjointPhotonProperties::setIncoherentAdjointModelType(
                                     MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );

  TEST_ASSERT( MonteCarlo::SimulationAdjointPhotonProperties::getIncoherentAdjointModelType() !=
	       default_model );
  TEST_EQUALITY_CONST(
		    MonteCarlo::SimulationAdjointPhotonProperties::getIncoherentAdjointModelType(),
		    MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );

  // Reset the default model
  MonteCarlo::SimulationAdjointPhotonProperties::setIncoherentAdjointModelType( default_model );
}

//---------------------------------------------------------------------------//
// end tstSimulationAdjointPhotonProperties.cpp
//---------------------------------------------------------------------------//
