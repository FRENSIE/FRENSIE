//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationPhotonProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SimulationPhotonProperties.hpp"
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
FRENSIE_UNIT_TEST( SimulationPhotonProperties, defaults )
{
  MonteCarlo::SimulationPhotonProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getKahnSamplingCutoffEnergy(), 3.0 );
  FRENSIE_CHECK_EQUAL( properties.getNumberOfPhotonHashGridBins(), 1000 );
  FRENSIE_CHECK_EQUAL( properties.getIncoherentModelType(),
		       MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn() );
  FRENSIE_CHECK( !properties.isDetailedPairProductionModeOn() );
  FRENSIE_CHECK( !properties.isPhotonuclearInteractionModeOn() );
  FRENSIE_CHECK_SMALL( properties.getPhotonRouletteThresholdWeight(), 1e-30 );
  FRENSIE_CHECK_SMALL( properties.getPhotonRouletteSurvivalWeight(), 1e-30 );
}

//---------------------------------------------------------------------------//
// Test that the min photon energy can be set
FRENSIE_UNIT_TEST( SimulationPhotonProperties, setMinPhotonEnergy )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setMinPhotonEnergy( 1e-2 );

  FRENSIE_CHECK_EQUAL( properties.getMinPhotonEnergy(), 1e-2 );
}

//---------------------------------------------------------------------------//
// Test that the max photon energy can be set
FRENSIE_UNIT_TEST( SimulationPhotonProperties, setMaxPhotonEnergy )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setMaxPhotonEnergy( 15.0 );

  FRENSIE_CHECK_EQUAL( properties.getMaxPhotonEnergy(), 15.0 );
}

//---------------------------------------------------------------------------//
// Test that the Kahn sampling cutoff energy can be set
FRENSIE_UNIT_TEST( SimulationPhotonProperties, setKahnSamplingCutoffEnergy )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setKahnSamplingCutoffEnergy( 2.5 );

  FRENSIE_CHECK_EQUAL( properties.getKahnSamplingCutoffEnergy(), 2.5 );
}

//---------------------------------------------------------------------------//
// Test that the number of photon hash grid bins can be set
FRENSIE_UNIT_TEST( SimulationPhotonProperties, setNumberOfPhotonHashGridBins )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setNumberOfPhotonHashGridBins( 500 );

  FRENSIE_CHECK_EQUAL( properties.getNumberOfPhotonHashGridBins(), 500 );
}

//---------------------------------------------------------------------------//
// Test that the incoherent model type can be set
FRENSIE_UNIT_TEST( SimulationPhotonProperties, setIncoherentModelType )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setIncoherentModelType( MonteCarlo::KN_INCOHERENT_MODEL );

  FRENSIE_CHECK_EQUAL( properties.getIncoherentModelType(),
                       MonteCarlo::KN_INCOHERENT_MODEL );
}

//---------------------------------------------------------------------------//
// Test that atomic relaxation mode can be turned off
FRENSIE_UNIT_TEST( SimulationPhotonProperties, setAtomicRelaxationModeOffOn )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setAtomicRelaxationModeOff();

  FRENSIE_CHECK( !properties.isAtomicRelaxationModeOn() );

  properties.setAtomicRelaxationModeOn();

  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the detailed pair production mode can be turned on
FRENSIE_UNIT_TEST( SimulationPhotonProperties, setDetailedPairProductionModeOnOff )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setDetailedPairProductionModeOn();

  FRENSIE_CHECK( properties.isDetailedPairProductionModeOn() );

  properties.setDetailedPairProductionModeOff();

  FRENSIE_CHECK( !properties.isDetailedPairProductionModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the photonuclear interaction mode can be turned on
FRENSIE_UNIT_TEST( SimulationPhotonProperties, setPhotonuclearInteractionModeOnOff )
{
  MonteCarlo::SimulationPhotonProperties properties;

  properties.setPhotonuclearInteractionModeOn();

  FRENSIE_CHECK( properties.isPhotonuclearInteractionModeOn() );

  properties.setPhotonuclearInteractionModeOff();

  FRENSIE_CHECK( !properties.isPhotonuclearInteractionModeOn() );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be set
FRENSIE_UNIT_TEST( SimulationPhotonProperties,
                   getPhotonRouletteThresholdWeight )
{
  MonteCarlo::SimulationPhotonProperties properties;

  double weight = 1e-14;

  properties.setPhotonRouletteThresholdWeight( weight );

  FRENSIE_CHECK_EQUAL( properties.getPhotonRouletteThresholdWeight(),
                       weight );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be set
FRENSIE_UNIT_TEST( SimulationPhotonProperties,
                   getPhotonRouletteSurvivalWeight )
{
  MonteCarlo::SimulationPhotonProperties properties;

  double weight = 1e-12;

  properties.setPhotonRouletteSurvivalWeight( weight );

  FRENSIE_CHECK_EQUAL( properties.getPhotonRouletteSurvivalWeight(),
                       weight );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SimulationPhotonProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_simulation_photon_props" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::SimulationPhotonProperties default_properties;

    MonteCarlo::SimulationPhotonProperties custom_properties;
    custom_properties.setMinPhotonEnergy( 1e-2 );
    custom_properties.setMaxPhotonEnergy( 15.0 );
    custom_properties.setKahnSamplingCutoffEnergy( 2.5 );
    custom_properties.setNumberOfPhotonHashGridBins( 500 );
    custom_properties.setIncoherentModelType( MonteCarlo::KN_INCOHERENT_MODEL );
    custom_properties.setAtomicRelaxationModeOff();
    custom_properties.setDetailedPairProductionModeOn();
    custom_properties.setPhotonuclearInteractionModeOn();
    custom_properties.setPhotonRouletteThresholdWeight( 1e-15 );
    custom_properties.setPhotonRouletteSurvivalWeight( 1e-13 );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( default_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( custom_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::SimulationPhotonProperties default_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( default_properties ) );

  FRENSIE_CHECK_EQUAL( default_properties.getAbsoluteMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( default_properties.getMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( default_properties.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getAbsoluteMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getKahnSamplingCutoffEnergy(), 3.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getNumberOfPhotonHashGridBins(), 1000 );
  FRENSIE_CHECK_EQUAL( default_properties.getIncoherentModelType(),
		       MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  FRENSIE_CHECK( default_properties.isAtomicRelaxationModeOn() );
  FRENSIE_CHECK( !default_properties.isDetailedPairProductionModeOn() );
  FRENSIE_CHECK( !default_properties.isPhotonuclearInteractionModeOn() );
  FRENSIE_CHECK_SMALL( default_properties.getPhotonRouletteThresholdWeight(), 1e-30 );
  FRENSIE_CHECK_SMALL( default_properties.getPhotonRouletteSurvivalWeight(), 1e-30  );

  MonteCarlo::SimulationPhotonProperties custom_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( custom_properties ) );

  FRENSIE_CHECK_EQUAL( custom_properties.getAbsoluteMinPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMinPhotonEnergy(), 1e-2 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMaxPhotonEnergy(), 15.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getAbsoluteMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getKahnSamplingCutoffEnergy(), 2.5 );
  FRENSIE_CHECK_EQUAL( custom_properties.getNumberOfPhotonHashGridBins(), 500 );
  FRENSIE_CHECK_EQUAL( custom_properties.getIncoherentModelType(),
		       MonteCarlo::KN_INCOHERENT_MODEL );
  FRENSIE_CHECK( !custom_properties.isAtomicRelaxationModeOn() );
  FRENSIE_CHECK( custom_properties.isDetailedPairProductionModeOn() );
  FRENSIE_CHECK( custom_properties.isPhotonuclearInteractionModeOn() );
  FRENSIE_CHECK_EQUAL( custom_properties.getPhotonRouletteThresholdWeight(), 1e-15 );
  FRENSIE_CHECK_EQUAL( custom_properties.getPhotonRouletteSurvivalWeight(), 1e-13 );
}

//---------------------------------------------------------------------------//
// end tstSimulationPhotonProperties.cpp
//---------------------------------------------------------------------------//
