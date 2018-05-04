//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectroatomFactory.cpp
//! \author Luke Kersting
//! \brief  Adjoint electroatom factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<const boost::filesystem::path> data_directory;
std::unique_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase> adjoint_electroatom_definitions;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a adjoint electroatom map can be created (only basic data)
FRENSIE_UNIT_TEST( AdjointElectroatomFactory, createAdjointElectroatomMap_basic )
{
  // Create the set of electroatom aliases
  MonteCarlo::AdjointElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
  electroatom_aliases.insert( "H-Native" );

  MonteCarlo::SimulationProperties properties;
  properties.setAdjointElasticCutoffAngleCosine( 0.9 );
  properties.setAdjointElectronEvaluationTolerance( 1e-7 );
  properties.setAdjointElasticElectronDistributionMode( MonteCarlo::HYBRID_DISTRIBUTION );

  std::shared_ptr<MonteCarlo::AdjointElectroatomFactory> electroatom_factory(
                    new MonteCarlo::AdjointElectroatomFactory(
                                              *data_directory,
                                              electroatom_aliases,
                                              *adjoint_electroatom_definitions,
                                              properties,
                                              true ) );

  // Create the native data file container
  std::unique_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container(
                                                                                     new Data::AdjointElectronPhotonRelaxationDataContainer( *data_directory / adjoint_electroatom_definitions->getDefinition( "H-Native" ).getAdjointElectroatomicDataProperties().filePath() ) );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LogLogCosLog,Utility::Correlated>(
        cutoff_elastic_distribution,
        *data_container,
        properties.getAdjointElasticCutoffAngleCosine(),
        properties.getAdjointElectronEvaluationTolerance() );

  MonteCarlo::AdjointElectroatomFactory::AdjointElectroatomNameMap
    electroatom_map;

  electroatom_factory->createAdjointElectroatomMap( electroatom_map );

  FRENSIE_CHECK_EQUAL( electroatom_map.size(), 1 );
  FRENSIE_CHECK( electroatom_map.count( "H-Native" ) );
  FRENSIE_CHECK( electroatom_map["H-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::AdjointElectroatom>& atom = electroatom_map["H-Native"];

  // Test the electroatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 1.00790034799796868, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.6333104567923698e+10, 1e-12 );

  energy = 1e-3;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.8322030561513998e+07, 1e-12 );

  energy = 20.0;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.4386701575400948e+05, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =  atom->getAbsorptionCrossSection( 1e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  MonteCarlo::AdjointElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.1243057898416743e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0551636170350602e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.1829299836129925e+04, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.9800795006423726e+01, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.4246702389204639e+01, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.4971444066404619e-01, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no hybrid elastic cross section
  reaction = MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.7336893667900169e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.9778260498147749e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.0987213022929017, 1e-12 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.5998492533545486e+10, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.5792554094646232e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.2035367482136615e+04, 1e-12 );


  // Test that the L1 subshell electroionization cross section can be returned
  reaction = MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a adjoint electroatom map can be created (electroionization subshell data)
FRENSIE_UNIT_TEST( AdjointElectroatomFactory,
                   createAdjointElectroatomMap_ionization_subshells )
{
  // Create the set of electroatom aliases
  MonteCarlo::AdjointElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
  electroatom_aliases.insert( "C-Native" );

  MonteCarlo::SimulationProperties properties;
  properties.setAdjointElasticCutoffAngleCosine( 1.0 );
  properties.setAdjointElectronEvaluationTolerance( 1e-7 );
  properties.setAdjointElasticElectronDistributionMode( MonteCarlo::DECOUPLED_DISTRIBUTION );

  std::shared_ptr<MonteCarlo::AdjointElectroatomFactory> electroatom_factory(
                    new MonteCarlo::AdjointElectroatomFactory(
                                              *data_directory,
                                              electroatom_aliases,
                                              *adjoint_electroatom_definitions,
                                              properties,
                                              true ) );

  MonteCarlo::AdjointElectroatomFactory::AdjointElectroatomNameMap
    electroatom_map;

  electroatom_factory->createAdjointElectroatomMap( electroatom_map );

  FRENSIE_CHECK_EQUAL( electroatom_map.size(), 1 );
  FRENSIE_CHECK( electroatom_map.count( "C-Native" ) );
  FRENSIE_CHECK( electroatom_map["C-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::AdjointElectroatom>& atom = electroatom_map["C-Native"];

  // Test the adjoint electroatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 12.010980086796003263, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.4648687276171619e+11, 1e-12 );

  energy = 1e-3;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.8282013943425226e+08, 1e-12 );

  energy = 20.0;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8658119028274959e+05, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =  atom->getAbsorptionCrossSection( 1e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  MonteCarlo::AdjointElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.9000914445996724e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.5191230693157382e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.2407699864974697e+05, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.4925823250992471e+02, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.5421106635333803e+02, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.0705555132152691, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.06351e+09, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.2833237650446758e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.4129048986120211e+05, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no hybrid elastic cross section
  reaction = MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.6110462808911211e+09, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.7890501745726615e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0110763061599802e+04, 1e-12 );

  // Test that there is no P3 subshell electroionization cross section
  reaction = MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.3480113717434631e+11, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.5437124322869428e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.1818180758223236e+05, 1e-12 );

  // Reset the adjoint electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that tables are not duplicated
FRENSIE_UNIT_TEST( AdjointElectroatomFactory, no_duplicate_tables )
{
  // Create the set of electroatom aliases
  MonteCarlo::AdjointElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
  electroatom_aliases.insert( "H-Native" );
  electroatom_aliases.insert( "H-1-Native" );

  MonteCarlo::SimulationProperties properties;
  properties.setAdjointElasticCutoffAngleCosine( 1.0 );

  std::shared_ptr<MonteCarlo::AdjointElectroatomFactory> electroatom_factory(
                    new MonteCarlo::AdjointElectroatomFactory(
                                              *data_directory,
                                              electroatom_aliases,
                                              *adjoint_electroatom_definitions,
                                              properties,
                                              true ) );

  MonteCarlo::AdjointElectroatomFactory::AdjointElectroatomNameMap
    electroatom_map;

  electroatom_factory->createAdjointElectroatomMap( electroatom_map );

  FRENSIE_CHECK_EQUAL( electroatom_map.size(), 2 );

  FRENSIE_CHECK( electroatom_map.count( "H-Native" ) );
  FRENSIE_CHECK( electroatom_map["H-Native"].get() != NULL );

  FRENSIE_CHECK( electroatom_map.count( "H-1-Native" ) );
  FRENSIE_CHECK( electroatom_map["H-1-Native"].get() != NULL );

  FRENSIE_CHECK( electroatom_map["H-Native"] == electroatom_map["H-1-Native"] );
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

  const Data::AtomProperties& c_properties =
    database.getAtomProperties( Data::C_ATOM );

  // Initialize the adjoint electroatom definitions
  adjoint_electroatom_definitions.reset( new MonteCarlo::ScatteringCenterDefinitionDatabase );

  MonteCarlo::ScatteringCenterDefinition& h_native_definition =
    adjoint_electroatom_definitions->createDefinition( "H-Native", Data::H_ATOM );

  adjoint_electroatom_definitions->createDefinitionAlias( "H-Native", "H-1-Native" );

  h_native_definition.setAdjointElectroatomicDataProperties(
           h_properties.getSharedAdjointElectroatomicDataProperties(
              Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

  MonteCarlo::ScatteringCenterDefinition& c_native_definition =
    adjoint_electroatom_definitions->createDefinition( "C-Native", Data::C_ATOM );

  c_native_definition.setAdjointElectroatomicDataProperties(
           c_properties.getSharedAdjointElectroatomicDataProperties(
              Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();


//---------------------------------------------------------------------------//
// end tstAdjointElectroatomFactory.cpp
//---------------------------------------------------------------------------//
