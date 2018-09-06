//---------------------------------------------------------------------------//
//!
//! \file   tstNuclideFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclide factory class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_DecoupledPhotonProductionNuclide.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::si::kelvin;
using Utility::Units::MeV;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::unique_ptr<const boost::filesystem::path> data_directory;
std::unique_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase> nuclide_definitions;

std::shared_ptr<const MonteCarlo::SimulationProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a factory can be constructed
FRENSIE_UNIT_TEST( NuclideFactory, constructor )
{
  MonteCarlo::NuclideFactory::ScatteringCenterNameSet nuclide_names;
  nuclide_names.insert( "H-1_293.6K" );
  nuclide_names.insert( "H-1_300K" );
  nuclide_names.insert( "H-1_900K" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfNeutronHashGridBins( 100 );
  properties.setUnresolvedResonanceProbabilityTableModeOff();
  properties.setParticleMode( MonteCarlo::NEUTRON_MODE );

  std::unique_ptr<MonteCarlo::NuclideFactory> factory;

  FRENSIE_CHECK_NO_THROW( factory.reset( new MonteCarlo::NuclideFactory(
                                                          *data_directory,
                                                          nuclide_names,
                                                          *nuclide_definitions,
                                                          properties,
                                                          true ) ) );
}

//---------------------------------------------------------------------------//
// Check that a nuclide map can be created
FRENSIE_UNIT_TEST( NuclideFactory, createNuclideMap_basic )
{
  MonteCarlo::NuclideFactory::ScatteringCenterNameSet nuclide_names;
  nuclide_names.insert( "H-1_293.6K" );
  nuclide_names.insert( "H-1_300K" );
  nuclide_names.insert( "H-1_900K" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfNeutronHashGridBins( 100 );
  properties.setUnresolvedResonanceProbabilityTableModeOff();
  properties.setParticleMode( MonteCarlo::NEUTRON_MODE );

  std::unique_ptr<MonteCarlo::NuclideFactory> factory(
                                      new MonteCarlo::NuclideFactory(
                                                          *data_directory,
                                                          nuclide_names,
                                                          *nuclide_definitions,
                                                          properties,
                                                          true ) );
  
  MonteCarlo::NuclideFactory::NuclideNameMap nuclide_map;

  factory->createNuclideMap( nuclide_map );

  FRENSIE_CHECK_EQUAL( nuclide_map.size(), 3 );
  FRENSIE_CHECK( nuclide_map.count( "H-1_293.6K" ) );
  FRENSIE_CHECK( nuclide_map["H-1_293.6K"].get() != NULL );
  FRENSIE_CHECK( nuclide_map.count( "H-1_300K" ) );
  FRENSIE_CHECK( nuclide_map["H-1_300K"].get() != NULL );
  FRENSIE_CHECK( nuclide_map.count( "H-1_900K" ) );
  FRENSIE_CHECK( nuclide_map["H-1_900K"].get() != NULL );
}

// //---------------------------------------------------------------------------//
// // Check that a nuclide map can be created
// FRENSIE_UNIT_TEST( NuclideFactory, createNuclideMap_unresolved_resonances )
// {

// }

//---------------------------------------------------------------------------//
// Check that a nuclide map can be created
FRENSIE_UNIT_TEST( NuclideFactory, createNuclideMap_photon_production )
{
  MonteCarlo::NuclideFactory::ScatteringCenterNameSet nuclide_names;
  nuclide_names.insert( "H-1_293.6K" );
  nuclide_names.insert( "H-1_300K" );
  nuclide_names.insert( "H-1_900K" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfNeutronHashGridBins( 100 );
  properties.setUnresolvedResonanceProbabilityTableModeOff();
  properties.setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );

  std::unique_ptr<MonteCarlo::NuclideFactory> factory(
                                      new MonteCarlo::NuclideFactory(
                                                          *data_directory,
                                                          nuclide_names,
                                                          *nuclide_definitions,
                                                          properties,
                                                          true ) );
  
  MonteCarlo::NuclideFactory::NuclideNameMap nuclide_map;

  factory->createNuclideMap( nuclide_map );

  FRENSIE_CHECK_EQUAL( nuclide_map.size(), 3 );
  
  FRENSIE_CHECK( nuclide_map.count( "H-1_293.6K" ) );
  FRENSIE_REQUIRE( nuclide_map["H-1_293.6K"].get() != NULL );

  const MonteCarlo::DecoupledPhotonProductionNuclide* true_nuclide =
    dynamic_cast<const MonteCarlo::DecoupledPhotonProductionNuclide*>(
                                             nuclide_map["H-1_293.6K"].get() );

  FRENSIE_CHECK( true_nuclide != NULL );
  
  FRENSIE_CHECK( nuclide_map.count( "H-1_300K" ) );
  FRENSIE_REQUIRE( nuclide_map["H-1_300K"].get() != NULL );

  true_nuclide =
    dynamic_cast<const MonteCarlo::DecoupledPhotonProductionNuclide*>(
                                               nuclide_map["H-1_300K"].get() );

  FRENSIE_CHECK( true_nuclide != NULL );
  
  FRENSIE_CHECK( nuclide_map.count( "H-1_900K" ) );
  FRENSIE_REQUIRE( nuclide_map["H-1_900K"].get() != NULL );

  true_nuclide =
    dynamic_cast<const MonteCarlo::DecoupledPhotonProductionNuclide*>(
                                               nuclide_map["H-1_900K"].get() );

  FRENSIE_CHECK( true_nuclide != NULL );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_scattering_center_database_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_database",
                                        test_scattering_center_database_name, "",
                                        "Test scattering center database name "
                                        "with path" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Determine the database directory
  boost::filesystem::path database_path =
    test_scattering_center_database_name;
  
  data_directory.reset(
                  new boost::filesystem::path( database_path.parent_path() ) );

  // Load the database
  const Data::ScatteringCenterPropertiesDatabase database( database_path );

  const Data::NuclideProperties& h1_properties =
    database.getNuclideProperties( 1001 );

  // Initialize the nuclide definitions
  nuclide_definitions.reset( new MonteCarlo::ScatteringCenterDefinitionDatabase );

  MonteCarlo::ScatteringCenterDefinition& h1_293K_definition =
    nuclide_definitions->createDefinition( "H-1_293.6K", 1001 );

  h1_293K_definition.setNuclearDataProperties(
                                 h1_properties.getSharedNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         2.53010E-08*MeV,
                                         true ) );

  // There is no test data for 300K so we'll just use the closest evaluation
  MonteCarlo::ScatteringCenterDefinition& h1_300K_definition =
    nuclide_definitions->createDefinition( "H-1_300K", 1001 );

  h1_300K_definition.setNuclearDataProperties(
                                 h1_properties.getSharedNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         300*kelvin,
                                         false ) );

  // There is no test data for 900K so we'll just use the closest evaluation
  MonteCarlo::ScatteringCenterDefinition& h1_900K_definition =
    nuclide_definitions->createDefinition( "H-1_900K", 1001 );

  h1_900K_definition.setNuclearDataProperties(
                                 h1_properties.getSharedNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         900*kelvin,
                                         false ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNuclideFactory.cpp
//---------------------------------------------------------------------------//
