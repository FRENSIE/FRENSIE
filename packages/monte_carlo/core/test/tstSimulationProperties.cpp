//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationProperties.cpp
//! \author Alex Robinson
//! \brief  Simulation properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationProperties.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationProperties, defaults )
{
  MonteCarlo::SimulationProperties properties;

  // General properties
  TEST_EQUALITY_CONST( properties.getParticleMode(),
                       MonteCarlo::NEUTRON_MODE );
  TEST_EQUALITY_CONST( properties.getNumberOfHistories(), 0 );
  TEST_EQUALITY_CONST( properties.getSurfaceFluxEstimatorAngleCosineCutoff(),
		       0.001 );
  TEST_ASSERT( properties.displayWarnings() );
  TEST_ASSERT( !properties.isImplicitCaptureModeOn() );
  
  // Neutron properties
  TEST_EQUALITY_CONST( properties.getFreeGasThreshold(), 400.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMinNeutronEnergy(), 1e-11 );
  TEST_EQUALITY_CONST( properties.getMinNeutronEnergy(), 1e-11 );
  TEST_EQUALITY_CONST( properties.getMaxNeutronEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMaxNeutronEnergy(), 20.0 );

  // Photon properties
  TEST_EQUALITY_CONST( properties.getAbsoluteMinPhotonEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( properties.getMinPhotonEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( properties.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getKahnSamplingCutoffEnergy(), 3.0 );
  TEST_EQUALITY_CONST( properties.getNumberOfPhotonHashGridBins(), 1000 );
  TEST_EQUALITY_CONST( properties.getIncoherentModelType(),
		       MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  TEST_ASSERT( properties.isAtomicRelaxationModeOn( MonteCarlo::PHOTON ) );
  TEST_ASSERT( !properties.isDetailedPairProductionModeOn() );
  TEST_ASSERT( !properties.isPhotonuclearInteractionModeOn() );

  // Adjoint Photon properties
  TEST_EQUALITY_CONST( properties.getAbsoluteMinAdjointPhotonEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( properties.getMinAdjointPhotonEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( properties.getMaxAdjointPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMaxAdjointPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getNumberOfAdjointPhotonHashGridBins(),
                       500 );
  TEST_EQUALITY_CONST( properties.getIncoherentAdjointModelType(),
                       MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
  TEST_EQUALITY_CONST( properties.getCriticalAdjointPhotonLineEnergies().size(), 0 );

  // Electron properties
  TEST_EQUALITY_CONST( properties.getAbsoluteMinElectronEnergy(), 1.5e-5 );
  TEST_EQUALITY_CONST( properties.getMinElectronEnergy(), 1.5e-5 );
  TEST_EQUALITY_CONST( properties.getMaxElectronEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMaxElectronEnergy(), 1.0e5 );
  TEST_ASSERT( properties.isAtomicRelaxationModeOn( MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST(
                     properties.getBremsstrahlungAngularDistributionFunction(),
                     MonteCarlo::TWOBS_DISTRIBUTION );
  TEST_EQUALITY_CONST( properties.getElasticCutoffAngleCosine(), 1.0 );
}

//---------------------------------------------------------------------------//
// Test that the min particle energy can be returned
TEUCHOS_UNIT_TEST( SimulationProperties, getMinParticleEnergy )
{
  MonteCarlo::SimulationProperties properties;
  
  TEST_EQUALITY_CONST( properties.getMinParticleEnergy<MonteCarlo::NeutronState>(),
                       1e-11 );
  TEST_EQUALITY_CONST( properties.getMinParticleEnergy<MonteCarlo::PhotonState>(),
                       1e-3 );
  TEST_EQUALITY_CONST( properties.getMinParticleEnergy<MonteCarlo::AdjointPhotonState>(),
                       1e-3 );
  TEST_EQUALITY_CONST( properties.getMinParticleEnergy<MonteCarlo::ElectronState>(),
                       1.5e-5 );
}

//---------------------------------------------------------------------------//
// Test that the max particle energy can be returned
TEUCHOS_UNIT_TEST( SimulationProperties, getMaxParticleEnergy )
{
  MonteCarlo::SimulationProperties properties;
  
  TEST_EQUALITY_CONST( properties.getMaxParticleEnergy<MonteCarlo::NeutronState>(),
                       20.0 );
  TEST_EQUALITY_CONST( properties.getMaxParticleEnergy<MonteCarlo::PhotonState>(),
                       20.0 );
  TEST_EQUALITY_CONST( properties.getMaxParticleEnergy<MonteCarlo::AdjointPhotonState>(),
                       20.0 );
  TEST_EQUALITY_CONST( properties.getMaxParticleEnergy<MonteCarlo::ElectronState>(),
                       20.0 );
}

//---------------------------------------------------------------------------//
// Test that atomic relaxation mode can be turned off/on
TEUCHOS_UNIT_TEST( SimulationProperties, setAtomicRelaxationModeOffOn )
{
  MonteCarlo::SimulationProperties properties;

  properties.setAtomicRelaxationModeOff( MonteCarlo::PHOTON );
  
  TEST_ASSERT( !properties.isAtomicRelaxationModeOn( MonteCarlo::PHOTON ) );

  properties.setAtomicRelaxationModeOn( MonteCarlo::PHOTON );

  TEST_ASSERT( properties.isAtomicRelaxationModeOn( MonteCarlo::PHOTON ) );

  properties.setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );
  
  TEST_ASSERT( !properties.isAtomicRelaxationModeOn( MonteCarlo::ELECTRON ) );

  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );

  TEST_ASSERT( properties.isAtomicRelaxationModeOn( MonteCarlo::ELECTRON ) );
}

//---------------------------------------------------------------------------//
// end tstSimulationProperties.cpp
//---------------------------------------------------------------------------//
