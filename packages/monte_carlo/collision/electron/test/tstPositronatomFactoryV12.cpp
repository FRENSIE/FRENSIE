//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomFactoryV12.cpp
//! \author Luke Kersting
//! \brief  Positronatom factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PositronatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<const boost::filesystem::path> data_directory;
std::unique_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase> positronatom_definitions;
std::shared_ptr<MonteCarlo::AtomicRelaxationModelFactory>
atomic_relaxation_model_factory;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a positron-atom map can be created (only basic data)
FRENSIE_UNIT_TEST( PositronatomFactory, createPositronatomMap_ace_basic )
{
  // Create the set of positron-atom aliases
  MonteCarlo::PositronatomFactory::ScatteringCenterNameSet positronatom_aliases;
  positronatom_aliases.insert( "Pb" );

  // Set the bremsstrahlung photon angular distribution function
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::PositronatomFactory> positronatom_factory(
                              new MonteCarlo::PositronatomFactory(
                                               *data_directory,
                                               positronatom_aliases,
                                               *positronatom_definitions,
                                               atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PositronatomFactory::PositronatomNameMap positronatom_map;

  positronatom_factory->createPositronatomMap( positronatom_map );

  FRENSIE_CHECK_EQUAL( positronatom_map.size(), 1 );
  FRENSIE_CHECK( positronatom_map.count( "Pb" ) );
  FRENSIE_CHECK( positronatom_map["Pb"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Positronatom>& atom = positronatom_map["Pb"];

  // Test the positron-atom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.12p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2.0e-3;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.806193787852e8, 1e-12 );

  energy = 4.0e-4;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.278128947846e9, 1e-12 );

  energy = 9.0e-5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.411603154884e9, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-2 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  MonteCarlo::PositronatomicReactionType reaction;

  // Test that there is no total positron-ionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 8.9754e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.250673571307e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.06530e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.774672656160e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );


  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );


  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.100574153670e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );

  // Reset the positron-atom factory
  positronatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a positron-atom map can be created (2BS bremsstrahlung data)
FRENSIE_UNIT_TEST( PositronatomFactory, createPositronatomMap_ace_2BS_brem )
{
  // Create the set of positron-atom aliases
  MonteCarlo::PositronatomFactory::ScatteringCenterNameSet positronatom_aliases;
  positronatom_aliases.insert( "Pb" );

  // Set the bremsstrahlung photon angular distribution function
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction(
                                              MonteCarlo::TWOBS_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::PositronatomFactory> positronatom_factory(
                                  new MonteCarlo::PositronatomFactory(
                                               *data_directory,
                                               positronatom_aliases,
                                               *positronatom_definitions,
                                               atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PositronatomFactory::PositronatomNameMap positronatom_map;

  positronatom_factory->createPositronatomMap( positronatom_map );

  FRENSIE_CHECK_EQUAL( positronatom_map.size(), 1 );
  FRENSIE_CHECK( positronatom_map.count( "Pb" ) );
  FRENSIE_CHECK( positronatom_map["Pb"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Positronatom>& atom = positronatom_map["Pb"];

  // Test the positron-atom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.12p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy, cross_section;
  energy = 2.0e-3;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.806193787852e8, 1e-12 );

  energy = 4.0e-4;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.278128947846e9, 1e-12 );

  energy = 9.0e-5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.411603154884e9, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.0e-2 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  MonteCarlo::PositronatomicReactionType reaction;

  // Test that there is no total positron-ionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 8.9754e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.250673571307e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.77467265616e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );


  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );


  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.10057415367e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );

  // Reset the positron-atom factory
  positronatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a positron-atom map can be created (positron-ionization subshell data)
FRENSIE_UNIT_TEST( PositronatomFactory, createPositronatomMap_ace_ionization_subshells )
{
  // Create the set of positron-atom aliases
  MonteCarlo::PositronatomFactory::ScatteringCenterNameSet positronatom_aliases;
  positronatom_aliases.insert( "Pb" );

  // Set the bremsstrahlung photon angular distribution function
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::PositronatomFactory> positronatom_factory(
                                      new MonteCarlo::PositronatomFactory(
                                              *data_directory,
                                               positronatom_aliases,
                                               *positronatom_definitions,
                                               atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PositronatomFactory::PositronatomNameMap positronatom_map;

  positronatom_factory->createPositronatomMap( positronatom_map );

  FRENSIE_CHECK_EQUAL( positronatom_map.size(), 1 );
  FRENSIE_CHECK( positronatom_map.count( "Pb" ) );
  FRENSIE_CHECK( positronatom_map["Pb"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Positronatom>& atom = positronatom_map["Pb"];

  // Test the positron-atom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.12p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );


  // Test that the total cross section can be returned
  double energy = 2.0e-3;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.806193787852e8, 1e-12 );

  energy = 4.0e-4;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.278128947846e9, 1e-12 );

  energy = 9.0e-5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.411603154884e9, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.0e-2 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  MonteCarlo::PositronatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );


  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.100574153670e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );


  // Test that there is no total positron-ionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 8.9754e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.250673571307e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.06530e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.774672656160e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that tables are not duplicated
FRENSIE_UNIT_TEST( PositronatomFactory, no_duplicate_tables )
{
  // Create the set of positron-atom aliases
  MonteCarlo::PositronatomFactory::ScatteringCenterNameSet positronatom_aliases;
  positronatom_aliases.insert( "H-1_293.6K" );
  positronatom_aliases.insert( "H-1_300K" );

  // Set the bremsstrahlung photon angular distribution function
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::PositronatomFactory> positronatom_factory(
                                           new MonteCarlo::PositronatomFactory(
                                               *data_directory,
                                               positronatom_aliases,
                                               *positronatom_definitions,
                                               atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PositronatomFactory::PositronatomNameMap positronatom_map;

  positronatom_factory->createPositronatomMap( positronatom_map );

  FRENSIE_CHECK_EQUAL( positronatom_map.size(), 2 );

  FRENSIE_CHECK( positronatom_map.count( "H-1_293.6K" ) );
  FRENSIE_CHECK( positronatom_map["H-1_293.6K"].get() != NULL );

  FRENSIE_CHECK( positronatom_map.count( "H-1_300K" ) );
  FRENSIE_CHECK( positronatom_map["H-1_300K"].get() != NULL );

  FRENSIE_CHECK( positronatom_map["H-1_293.6K"] ==  positronatom_map["H-1_300K"] );
}

//---------------------------------------------------------------------------//
// Custom setup
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

  const Data::AtomProperties& h_properties =
    database.getAtomProperties( 1001 );

  const Data::AtomProperties& pb_properties =
    database.getAtomProperties( Data::Pb_ATOM );

  // Initialize the positronatom definitions
  positronatom_definitions.reset( new MonteCarlo::ScatteringCenterDefinitionDatabase );

  MonteCarlo::ScatteringCenterDefinition& h1_293K_definition =
    positronatom_definitions->createDefinition( "H-1_293.6K", 1001 );

  h1_293K_definition.setElectroatomicDataProperties(
           h_properties.getSharedElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::ACE_EPR_FILE, 12 ) );

  positronatom_definitions->createDefinitionAlias( "H-1_293.6K", "H-1_300K" );

  MonteCarlo::ScatteringCenterDefinition& pb_definition =
    positronatom_definitions->createDefinition( "Pb", Data::Pb_ATOM );

  pb_definition.setElectroatomicDataProperties(
          pb_properties.getSharedElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::ACE_EPR_FILE, 12 ) );

  // Create the atomic relaxation model factory
  atomic_relaxation_model_factory.reset(
                new MonteCarlo::AtomicRelaxationModelFactory );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomFactoryV12.cpp
//---------------------------------------------------------------------------//
