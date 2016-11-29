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
  MonteCarlo::SimulationPhotonProperties properties;
  
  TEST_EQUALITY_CONST( properties.getAbsoluteMinPhotonEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( properties.getMinPhotonEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( properties.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getKahnSamplingCutoffEnergy(), 3.0 );
  TEST_EQUALITY_CONST( properties.getNumberOfPhotonHashGridBins(), 1000 );
  TEST_EQUALITY_CONST( properties.getIncoherentModelType(),
		       MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  TEST_ASSERT( properties.isAtomicRelaxationModeOn() );
  TEST_ASSERT( !properties.isDetailedPairProductionModeOn() );
  TEST_ASSERT( !properties.isPhotonuclearInteractionModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the min photon energy can be set
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setMinPhotonEnergy )
{
  MonteCarlo::SimulationPhotonProperties properties;
  
  properties.setMinPhotonEnergy( 1e-2 );

  TEST_EQUALITY_CONST( properties.getMinPhotonEnergy(), 1e-2 );
}

//---------------------------------------------------------------------------//
// Test that the max photon energy can be set
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setMaxPhotonEnergy )
{
  MonteCarlo::SimulationPhotonProperties properties;
  
  properties.setMaxPhotonEnergy( 15.0 );

  TEST_EQUALITY_CONST( properties.getMaxPhotonEnergy(), 15.0 );
}

//---------------------------------------------------------------------------//
// Test that the Kahn sampling cutoff energy can be set
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setKahnSamplingCutoffEnergy )
{
  MonteCarlo::SimulationPhotonProperties properties;
  
  properties.setKahnSamplingCutoffEnergy( 2.5 );

  TEST_EQUALITY_CONST( properties.getKahnSamplingCutoffEnergy(), 2.5 );
}

//---------------------------------------------------------------------------//
// Test that the number of photon hash grid bins can be set
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setNumberOfPhotonHashGridBins )
{
  MonteCarlo::SimulationPhotonProperties properties;
  
  properties.setNumberOfPhotonHashGridBins( 500 );

  TEST_EQUALITY_CONST( properties.getNumberOfPhotonHashGridBins(), 500 );
}

//---------------------------------------------------------------------------//
// Test that the incoherent model type can be set
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setIncoherentModelType )
{
  MonteCarlo::SimulationPhotonProperties properties;
  
  properties.setIncoherentModelType( MonteCarlo::KN_INCOHERENT_MODEL );

  TEST_EQUALITY_CONST( properties.getIncoherentModelType(),
                       MonteCarlo::KN_INCOHERENT_MODEL );
}

//---------------------------------------------------------------------------//
// Test that atomic relaxation mode can be turned off
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setAtomicRelaxationModeOffOn )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setAtomicRelaxationModeOff();

  TEST_ASSERT( !properties.isAtomicRelaxationModeOn() );

  properties.setAtomicRelaxationModeOn();
  
  TEST_ASSERT( properties.isAtomicRelaxationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the detailed pair production mode can be turned on
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setDetailedPairProductionModeOnOff )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setDetailedPairProductionModeOn();

  TEST_ASSERT( properties.isDetailedPairProductionModeOn() );

  properties.setDetailedPairProductionModeOff();
  
  TEST_ASSERT( !properties.isDetailedPairProductionModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the photonuclear interaction mode can be turned on
TEUCHOS_UNIT_TEST( SimulationPhotonProperties, setPhotonuclearInteractionModeOnOff )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setPhotonuclearInteractionModeOn();

  TEST_ASSERT( properties.isPhotonuclearInteractionModeOn() );

  properties.setPhotonuclearInteractionModeOff();
  
  TEST_ASSERT( !properties.isPhotonuclearInteractionModeOn() );
}

//---------------------------------------------------------------------------//
// end tstSimulationPhotonProperties.cpp
//---------------------------------------------------------------------------//
