//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationProperties.cpp
//! \author Alex Robinson
//! \brief  Simulation properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
FRENSIE_UNIT_TEST( SimulationProperties, defaults )
{
  MonteCarlo::SimulationProperties properties;

  // General properties
  FRENSIE_CHECK_EQUAL( properties.getParticleMode(),
                       MonteCarlo::NEUTRON_MODE );
  FRENSIE_CHECK_EQUAL( properties.getNumberOfHistories(), 0 );
  FRENSIE_CHECK_EQUAL( properties.getSurfaceFluxEstimatorAngleCosineCutoff(),
                       0.001 );
  FRENSIE_CHECK( properties.displayWarnings() );
  FRENSIE_CHECK( !properties.isImplicitCaptureModeOn() );

  // Neutron properties
  FRENSIE_CHECK_EQUAL( properties.getFreeGasThreshold(), 400.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( properties.getMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( properties.getMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK( properties.isUnresolvedResonanceProbabilityTableModeOn() );

  // Photon properties
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getKahnSamplingCutoffEnergy(), 3.0 );
  FRENSIE_CHECK_EQUAL( properties.getNumberOfPhotonHashGridBins(), 1000 );
  FRENSIE_CHECK_EQUAL( properties.getIncoherentModelType(),
                       MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !properties.isDetailedPairProductionModeOn() );
  FRENSIE_CHECK( !properties.isPhotonuclearInteractionModeOn() );

  // Adjoint Photon properties
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinAdjointPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMinAdjointPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMaxAdjointPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxAdjointPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getNumberOfAdjointPhotonHashGridBins(),
                       500 );
  FRENSIE_CHECK_EQUAL( properties.getIncoherentAdjointModelType(),
                       MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
  FRENSIE_CHECK_EQUAL( properties.getCriticalAdjointPhotonLineEnergies().size(), 0 );

  // Electron properties
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinElectronEnergy(), 1.5e-5 );
  FRENSIE_CHECK_EQUAL( properties.getMinElectronEnergy(), 1.5e-5 );
  FRENSIE_CHECK_EQUAL( properties.getMaxElectronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxElectronEnergy(), 1.0e5 );
  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( properties.isElasticModeOn() );
  FRENSIE_CHECK( properties.isElectroionizationModeOn() );
  FRENSIE_CHECK( properties.isBremsstrahlungModeOn() );
  FRENSIE_CHECK( properties.isAtomicExcitationModeOn() );
  FRENSIE_CHECK_EQUAL( properties.getElectronEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( properties.getBremsstrahlungAngularDistributionFunction(),
                       MonteCarlo::TWOBS_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( properties.getElasticElectronDistributionMode(),
                       MonteCarlo::DECOUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::TWO_D_UNION );
  FRENSIE_CHECK_EQUAL( properties.getElasticCutoffAngleCosine(), 1.0 );
}

//---------------------------------------------------------------------------//
// Test that the min particle energy can be returned
FRENSIE_UNIT_TEST( SimulationProperties, getMinParticleEnergy )
{
  MonteCarlo::SimulationProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getMinParticleEnergy<MonteCarlo::NeutronState>(),
                       1e-11 );
  FRENSIE_CHECK_EQUAL( properties.getMinParticleEnergy<MonteCarlo::PhotonState>(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMinParticleEnergy<MonteCarlo::AdjointPhotonState>(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMinParticleEnergy<MonteCarlo::ElectronState>(),
                       1.5e-5 );
}

//---------------------------------------------------------------------------//
// Test that the max particle energy can be returned
FRENSIE_UNIT_TEST( SimulationProperties, getMaxParticleEnergy )
{
  MonteCarlo::SimulationProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getMaxParticleEnergy<MonteCarlo::NeutronState>(),
                       20.0 );
  FRENSIE_CHECK_EQUAL( properties.getMaxParticleEnergy<MonteCarlo::PhotonState>(),
                       20.0 );
  FRENSIE_CHECK_EQUAL( properties.getMaxParticleEnergy<MonteCarlo::AdjointPhotonState>(),
                       20.0 );
  FRENSIE_CHECK_EQUAL( properties.getMaxParticleEnergy<MonteCarlo::ElectronState>(),
                       20.0 );
}

//---------------------------------------------------------------------------//
// Test that atomic relaxation mode can be turned off/on
FRENSIE_UNIT_TEST( SimulationProperties, setAtomicRelaxationModeOffOn )
{
  MonteCarlo::SimulationProperties properties;

  properties.setAtomicRelaxationModeOff( MonteCarlo::PHOTON );

  FRENSIE_CHECK( !properties.isAtomicRelaxationModeOn( MonteCarlo::PHOTON ) );

  properties.setAtomicRelaxationModeOn( MonteCarlo::PHOTON );

  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn( MonteCarlo::PHOTON ) );

  properties.setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  FRENSIE_CHECK( !properties.isAtomicRelaxationModeOn( MonteCarlo::ELECTRON ) );

  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );

  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn( MonteCarlo::ELECTRON ) );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SimulationProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_simulation_props" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::SimulationProperties properties;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::SimulationProperties properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( properties ) );

  FRENSIE_CHECK_EQUAL( properties.getParticleMode(),
                       MonteCarlo::NEUTRON_MODE );
  FRENSIE_CHECK_EQUAL( properties.getNumberOfHistories(), 0 );
  FRENSIE_CHECK_EQUAL( properties.getSurfaceFluxEstimatorAngleCosineCutoff(),
                       0.001 );
  FRENSIE_CHECK( properties.displayWarnings() );
  FRENSIE_CHECK( !properties.isImplicitCaptureModeOn() );

  FRENSIE_CHECK_EQUAL( properties.getFreeGasThreshold(), 400.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( properties.getMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( properties.getMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK( properties.isUnresolvedResonanceProbabilityTableModeOn() );

  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getKahnSamplingCutoffEnergy(), 3.0 );
  FRENSIE_CHECK_EQUAL( properties.getNumberOfPhotonHashGridBins(), 1000 );
  FRENSIE_CHECK_EQUAL( properties.getIncoherentModelType(),
                       MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !properties.isDetailedPairProductionModeOn() );
  FRENSIE_CHECK( !properties.isPhotonuclearInteractionModeOn() );

  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinAdjointPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMinAdjointPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMaxAdjointPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxAdjointPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getNumberOfAdjointPhotonHashGridBins(),
                       500 );
  FRENSIE_CHECK_EQUAL( properties.getIncoherentAdjointModelType(),
                       MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
  FRENSIE_CHECK_EQUAL( properties.getCriticalAdjointPhotonLineEnergies().size(), 0 );

  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinElectronEnergy(), 1.5e-5 );
  FRENSIE_CHECK_EQUAL( properties.getMinElectronEnergy(), 1.5e-5 );
  FRENSIE_CHECK_EQUAL( properties.getMaxElectronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxElectronEnergy(), 1.0e5 );
  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( properties.isElasticModeOn() );
  FRENSIE_CHECK( properties.isElectroionizationModeOn() );
  FRENSIE_CHECK( properties.isBremsstrahlungModeOn() );
  FRENSIE_CHECK( properties.isAtomicExcitationModeOn() );
  FRENSIE_CHECK_EQUAL( properties.getElectronEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( properties.getBremsstrahlungAngularDistributionFunction(),
                       MonteCarlo::TWOBS_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( properties.getElasticElectronDistributionMode(),
                       MonteCarlo::DECOUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::TWO_D_UNION );
  FRENSIE_CHECK_EQUAL( properties.getElasticCutoffAngleCosine(), 1.0 );
}

//---------------------------------------------------------------------------//
// end tstSimulationProperties.cpp
//---------------------------------------------------------------------------//
