//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationPhotonProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationPhotonProperties.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, defaults )
{
  TEST_EQUALITY_CONST(
               MonteCarlo::SimulationPhotonProperties::getAbsoluteMinPhotonEnergy(),
               1e-3 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationPhotonProperties::getMinPhotonEnergy(),
		       1e-3 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationPhotonProperties::getMaxPhotonEnergy(),
                       20.0 );
  TEST_EQUALITY_CONST(
                MonteCarlo::SimulationPhotonProperties::getAbsoluteMaxPhotonEnergy(),
                20.0 );
  TEST_EQUALITY_CONST(
	       MonteCarlo::SimulationPhotonProperties::getKahnSamplingCutoffEnergy(),
	       3.0 );
  TEST_EQUALITY_CONST(
	     MonteCarlo::SimulationPhotonProperties::getNumberOfPhotonHashGridBins(),
	     1000 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationPhotonProperties::getIncoherentModelType(),
		       MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  TEST_ASSERT( MonteCarlo::SimulationPhotonProperties::isAtomicRelaxationModeOn() );
  TEST_ASSERT( !MonteCarlo::SimulationPhotonProperties::isDetailedPairProductionModeOn() );
  TEST_ASSERT( !MonteCarlo::SimulationPhotonProperties::isPhotonuclearInteractionModeOn() );

}

//---------------------------------------------------------------------------//
// Test that the min photon energy can be set
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setMinPhotonEnergy )
{
  double default_value =
    MonteCarlo::SimulationPhotonProperties::getMinPhotonEnergy();

  MonteCarlo::SimulationPhotonProperties::setMinPhotonEnergy( 1e-2 );

  TEST_ASSERT( MonteCarlo::SimulationPhotonProperties::getMinPhotonEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationPhotonProperties::getMinPhotonEnergy(),
		       1e-2 );

  // Reset the default value
  MonteCarlo::SimulationPhotonProperties::setMinPhotonEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that the max photon energy can be set
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setMaxPhotonEnergy )
{
  double default_value =
    MonteCarlo::SimulationPhotonProperties::getMaxPhotonEnergy();

  MonteCarlo::SimulationPhotonProperties::setMaxPhotonEnergy( 15.0 );

  TEST_ASSERT( MonteCarlo::SimulationPhotonProperties::getMaxPhotonEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationPhotonProperties::getMaxPhotonEnergy(),
		       15.0 );

  // Reset the default value
  MonteCarlo::SimulationPhotonProperties::setMaxPhotonEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that the Kahn sampling cutoff energy can be set
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setKahnSamplingCutoffEnergy )
{
  double default_value =
    MonteCarlo::SimulationPhotonProperties::getKahnSamplingCutoffEnergy();

  MonteCarlo::SimulationPhotonProperties::setKahnSamplingCutoffEnergy( 2.5 );

  TEST_ASSERT(
	    MonteCarlo::SimulationPhotonProperties::getKahnSamplingCutoffEnergy() !=
	    default_value );
  TEST_EQUALITY_CONST(
	      MonteCarlo::SimulationPhotonProperties::getKahnSamplingCutoffEnergy(),
	      2.5 );

  // Reset the default value
  MonteCarlo::SimulationPhotonProperties::setKahnSamplingCutoffEnergy(
							       default_value );
}

//---------------------------------------------------------------------------//
// Test that the number of photon hash grid bins can be set
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setNumberOfPhotonHashGridBins )
{
  unsigned default_value =
    MonteCarlo::SimulationPhotonProperties::getNumberOfPhotonHashGridBins();

  MonteCarlo::SimulationPhotonProperties::setNumberOfPhotonHashGridBins( 500 );

  TEST_ASSERT(
	  MonteCarlo::SimulationPhotonProperties::getNumberOfPhotonHashGridBins() !=
	  default_value );
  TEST_EQUALITY_CONST(
	     MonteCarlo::SimulationPhotonProperties::getNumberOfPhotonHashGridBins(),
	     500 );

  // Reset the default value
  MonteCarlo::SimulationPhotonProperties::setNumberOfPhotonHashGridBins( default_value );
}

//---------------------------------------------------------------------------//
// Test that the incoherent model type can be set
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setIncoherentModelType )
{
  MonteCarlo::IncoherentModelType default_model =
    MonteCarlo::SimulationPhotonProperties::getIncoherentModelType();

  MonteCarlo::SimulationPhotonProperties::setIncoherentModelType(
					     MonteCarlo::KN_INCOHERENT_MODEL );

  TEST_ASSERT( MonteCarlo::SimulationPhotonProperties::getIncoherentModelType() !=
	       default_model );
  TEST_EQUALITY_CONST(
		    MonteCarlo::SimulationPhotonProperties::getIncoherentModelType(),
		    MonteCarlo::KN_INCOHERENT_MODEL );

  // Reset the default model
  MonteCarlo::SimulationPhotonProperties::setIncoherentModelType( default_model );
}

//---------------------------------------------------------------------------//
// Test that atomic relaxation mode can be turned off
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setAtomicRelaxationModeOff )
{
  TEST_ASSERT( MonteCarlo::SimulationPhotonProperties::isAtomicRelaxationModeOn() );

  MonteCarlo::SimulationPhotonProperties::setAtomicRelaxationModeOff();

  TEST_ASSERT( !MonteCarlo::SimulationPhotonProperties::isAtomicRelaxationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the detailed pair production mode can be turned on
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setDetailedPairProductionModeOn )
{
  TEST_ASSERT( !MonteCarlo::SimulationPhotonProperties::isDetailedPairProductionModeOn() );

  MonteCarlo::SimulationPhotonProperties::setDetailedPairProductionModeOn();

  TEST_ASSERT( MonteCarlo::SimulationPhotonProperties::isDetailedPairProductionModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the photonuclear interaction mode can be turned on
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setPhotonuclearInteractionModeOn )
{
  TEST_ASSERT( !MonteCarlo::SimulationPhotonProperties::isPhotonuclearInteractionModeOn() );

  MonteCarlo::SimulationPhotonProperties::setPhotonuclearInteractionModeOn();

  TEST_ASSERT( MonteCarlo::SimulationPhotonProperties::isPhotonuclearInteractionModeOn() );
}

//---------------------------------------------------------------------------//
// end tstSimulationPhotonProperties.cpp
//---------------------------------------------------------------------------//
