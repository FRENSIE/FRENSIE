//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomFactory.cpp
//! \author Luke Kersting
//! \brief  Electroatom factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Data_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronState.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string cross_sections_xml_directory;
Teuchos::ParameterList cross_section_table_info;
std::unordered_set<std::string> electroatom_aliases;
Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory>
atomic_relaxation_model_factory;
Teuchos::RCP<MonteCarlo::ElectroatomFactory> electroatom_factory;
MonteCarlo::BremsstrahlungAngularDistributionType function;
unsigned hash_grid_bins = 100;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (only basic data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_ace_basic )
{
  // Create the set of electroatom aliases
  electroatom_aliases.clear();
  electroatom_aliases.insert( "Pb" );

  // Set the bremsstrahlung photon angular distribution function
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  double cutoff_angle_cosine = 1.0;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
        cross_sections_xml_directory,
        cross_section_table_info,
        electroatom_aliases,
        atomic_relaxation_model_factory,
        hash_grid_bins,
        false,
        true,
        true,
        true,
        true,
        function,
        cutoff_angle_cosine ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  TEST_EQUALITY_CONST( electroatom_map.size(), 1 );
  TEST_ASSERT( electroatom_map.count( "Pb" ) );
  TEST_ASSERT( !electroatom_map["Pb"].is_null() );

  Teuchos::RCP<MonteCarlo::Electroatom>& atom = electroatom_map["Pb"];

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2.000000000000E-03;
  double cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.806193787852E+08,
                          1e-12 );


  energy = 4.000000000000E-04;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.278128947846E+09,
                          1e-12 );


  energy = 9.000000000000E-05;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.411603154884E+09,
                          1e-12 );

  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1e-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2e-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4e-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9e-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
            1.000000000000E-05,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.000000000000E+05,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000000000000E-05,
            MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            8.975400000000E-02,
            MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.250673571307E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.000000000000E+05,
            MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190000000E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000000000000E-05,
            MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            2.000000000000E-03,
            MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.774672656160E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.000000000000E+05,
            MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );


  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
            2.000000000000E-03,
            MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            4.000000000000E-04,
            MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            9.000000000000E-05,
            MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
            2.000000000000E-03,
            MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            4.000000000000E-04,
                 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            9.000000000000E-05,
            MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            2.000000000000E-03,
            MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.100574153670E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            4.000000000000E-04,
            MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.436635458458E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            9.000000000000E-05,
            MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.887469904554E+08,
                          1e-12 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (only basic data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_native_basic )
{
  // Create the set of electroatom aliases
  electroatom_aliases.clear();
  electroatom_aliases.insert( "Pb-Native" );

  // Set the bremsstrahlung photon angular distribution function
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  double cutoff_angle_cosine = 0.9;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
                                    cross_sections_xml_directory,
                                    cross_section_table_info,
                                    electroatom_aliases,
                                    atomic_relaxation_model_factory,
                                    hash_grid_bins,
                                    false,
                                    true,
                                    true,
                                    true,
                                    true,
                                    function,
                                    cutoff_angle_cosine ) );

  std::string electroatom_file_path, electroatom_file_type, electroatom_table_name;
  int electroatom_file_start_line;
  double atomic_weight;

  Data::CrossSectionsXMLProperties::extractInfoFromElectroatomTableInfoParameterList(
                          cross_sections_xml_directory,
                          "Pb-Native",
                          cross_section_table_info,
                          electroatom_file_path,
                          electroatom_file_type,
                          electroatom_table_name,
                          electroatom_file_start_line,
                          atomic_weight );

  // Create the native data file container
  Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> data_container(
    new Data::ElectronPhotonRelaxationDataContainer(
                             electroatom_file_path ) );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
        cutoff_elastic_distribution,
        *data_container,
        cutoff_angle_cosine );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  TEST_EQUALITY_CONST( electroatom_map.size(), 1 );
  TEST_ASSERT( electroatom_map.count( "Pb-Native" ) );
  TEST_ASSERT( !electroatom_map["Pb-Native"].is_null() );

  Teuchos::RCP<MonteCarlo::Electroatom>& atom = electroatom_map["Pb-Native"];

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1e-5;
  double cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( energy, cutoff_angle_cosine );
  double inelastic = 1.398201198E+08;
  double elastic = 2.48924E+09*cross_section_ratio + 1.106329441558590E+08;

  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 2e-1;
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( energy, cutoff_angle_cosine );
  inelastic = 6.411260911064270E+06;
  elastic = 1.61118815071382E+07*cross_section_ratio + 1.8916841363881219e+06;

  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 1e5;
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( energy, cutoff_angle_cosine );
  inelastic = 2.845403047900000E+06;
  elastic = 8.83051E-02*cross_section_ratio + 2.203770304996720E-03;

  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.000000000E-02 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.000000000000E-03 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.000000000000E-04 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.000000000000E-05 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   2.000000000000E-03,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   4.000000000000E-04,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   9.000000000000E-05,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
           1.000000000000E-05,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           9.121750E-02,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.500920E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           1.000000000000E+05,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
          1.000000000000E-05,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1.000000000000E-03,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 3.248850E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1.000000000000E+05,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 9.528370E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    5.520610E-04,
                 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 9.235190E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 4.869800E+03, 1e-12 );


  // Test that the hybrid elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.00E+05,
                    MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1.E+05, cutoff_angle_cosine );
  TEST_FLOATING_EQUALITY( cross_section,
                          8.83051e-2*cross_section_ratio + 2.20377030499672E-03,
                          1e-11 );

  cross_section = atom->getReactionCrossSection(
                    1.00E-03,
                    MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1.E-03, cutoff_angle_cosine );
  TEST_FLOATING_EQUALITY( cross_section,
                          2.90281E+8*cross_section_ratio + 1.25840137740571E+8,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.995260E-04,
                    MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1.99526E-04, cutoff_angle_cosine );
  TEST_FLOATING_EQUALITY( cross_section,
                          6.1309E+8*cross_section_ratio + 2.1336093313820770e+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1E-5, cutoff_angle_cosine );
  TEST_FLOATING_EQUALITY( cross_section,
                          2.48924E+9*cross_section_ratio + 1.10632944155859E+8,
                          1e-12 );


  // Test that there is no cutoff elastic cross section
  cross_section = atom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no screened Rutherford reaction
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no moment preserving elastic cross section
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}
/*
//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (tabular bremsstrahlung data)
// TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_tabular_brem )
{
  // Create the set of electroatom aliases
  electroatom_aliases.insert( "Pb" );

  // Set the bremsstrahlung photon angular distribution function
  function = MonteCarlo::TABULAR_DISTRIBUTION;
  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
                                              cross_sections_xml_directory,
                                              electroatom_aliases,
                                              cross_section_table_info,
                                              atomic_relaxation_model_factory,
                                              false,
                                              true,
                                              true,
                                              true,
                                              true,
                                              function,
                                              1.0 ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;
  electroatom_factory->createElectroatomMap( electroatom_map );
  TEST_EQUALITY_CONST( electroatom_map.size(), 1 );
  TEST_ASSERT( electroatom_map.count( "Pb" ) );
  TEST_ASSERT( !electroatom_map["Pb"].is_null() );
}
*/

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (2BS bremsstrahlung data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_ace_2BS_brem )
{
  // Create the set of electroatom aliases
  electroatom_aliases.clear();
  electroatom_aliases.insert( "Pb" );

  // Set the bremsstrahlung photon angular distribution function
  function = MonteCarlo::TWOBS_DISTRIBUTION;

  double cutoff_angle_cosine = 1.0;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
        cross_sections_xml_directory,
        cross_section_table_info,
        electroatom_aliases,
        atomic_relaxation_model_factory,
        hash_grid_bins,
        false,
        true,
        true,
        true,
        true,
        function,
        cutoff_angle_cosine ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  TEST_EQUALITY_CONST( electroatom_map.size(), 1 );
  TEST_ASSERT( electroatom_map.count( "Pb" ) );
  TEST_ASSERT( !electroatom_map["Pb"].is_null() );

  Teuchos::RCP<MonteCarlo::Electroatom>& atom = electroatom_map["Pb"];

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2.000000000000E-03;
  double cross_section =
    atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.806193787852E+08, 1e-12 );

  energy = 4.0E-04;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.278128947846E+09, 1e-12 );


  energy = 9.0E-05;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.411603154884E+09, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.000000000E-02 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.000000000000E-03 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.000000000000E-04 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.000000000000E-05 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
            1.000000000000E-05,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
            1.000000000000E+05,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
           1.000000000000E-05,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
           8.975400000000E-02,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.250673571307E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           1.000000000000E+05,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190000000E+01, 1e-12 );


  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
          1e-5,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          2.000000000000E-03,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.774672656160E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1.000000000000E+05,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );


  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );


  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.100574153670E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section,
                          4.436635458458E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section,
                          8.887469904554E+08,
                          1e-12 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (2BS bremsstrahlung data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_native_2BS_brem )
{
  // Create the set of electroatom aliases
  electroatom_aliases.clear();
  electroatom_aliases.insert( "Pb-Native" );

  // Set the bremsstrahlung photon angular distribution function
  function = MonteCarlo::TWOBS_DISTRIBUTION;

  double cutoff_angle_cosine = 1.0;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
        cross_sections_xml_directory,
        cross_section_table_info,
        electroatom_aliases,
        atomic_relaxation_model_factory,
        hash_grid_bins,
        true,
        true,
        true,
        true,
        true,
        function,
        cutoff_angle_cosine ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  TEST_EQUALITY_CONST( electroatom_map.size(), 1 );
  TEST_ASSERT( electroatom_map.count( "Pb-Native" ) );
  TEST_ASSERT( !electroatom_map["Pb-Native"].is_null() );

  Teuchos::RCP<MonteCarlo::Electroatom>& atom = electroatom_map["Pb-Native"];

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.00E-05;
  double cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.629060119800000E+09,
                          1e-12 );


  energy = 2.00E-01;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.252314241820250E+07,
                          1e-12 );


  energy = 1.00E+05;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.957013047900000E+06,
                          1e-12 );

  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   2.000000000000E-03,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   4.000000000000E-04,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   9.000000000000E-05,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
           1.000000000000E-05,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           9.121750E-02,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.500920E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           1.000000000000E+05,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
          1.000000000000E-05,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1.000000000000E-03,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.248850E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1.000000000000E+05,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    5.520610E-04,
                 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.235190E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.869800E+03, 1e-12 );

  // Test that the analog elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.000E+05,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.830509999999990E-02 + 2.1116099116949E+06,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.995260E+01,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.0571E+06 + 1.088440E+06,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    6.309570E+00,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.68623E+06 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.100574153670E+08 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.436635458458E+08 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.887469904554E+08 + 0.0,
                          1e-12 );

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  // Test that the screened Rutherford elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  // Test that the moment preserving elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (electroionization subshell data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_ace_ionization_subshells )
{
  // Create the set of electroatom aliases
  electroatom_aliases.clear();
  electroatom_aliases.insert( "Pb" );

  // Set the bremsstrahlung photon angular distribution function
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  double cutoff_angle_cosine = 1.0;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
                                              cross_sections_xml_directory,
                                              cross_section_table_info,
                                              electroatom_aliases,
                                              atomic_relaxation_model_factory,
                                              hash_grid_bins,
                                              true,
                                              true,
                                              true,
                                              true,
                                              true,
                                              function,
                                              cutoff_angle_cosine ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  TEST_EQUALITY_CONST( electroatom_map.size(), 1 );
  TEST_ASSERT( electroatom_map.count( "Pb" ) );
  TEST_ASSERT( !electroatom_map["Pb"].is_null() );

  Teuchos::RCP<MonteCarlo::Electroatom>& atom = electroatom_map["Pb"];

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2.000000000000E-03;
  double cross_section =
    atom->getTotalCrossSection( energy );


  TEST_FLOATING_EQUALITY( cross_section,
                          4.806193787852E+08,
                          1e-12 );


  energy = 4.000000000000E-04;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.278128947846E+09,
                          1e-12 );


  energy = 9.000000000000E-05;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.411603154884E+09,
                          1e-12 );

  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.100574153670E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.436635458458E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.887469904554E+08,
                          1e-12 );

  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
            1.000000000000E-05,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.000000000000E+05,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
           1.000000000000E-05,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           8.975400000000E-02,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.250673571307E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           1.000000000000E+05,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190000000E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
          1.000000000000E-05,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          2.000000000000E-03,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.774672656160E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1.000000000000E+05,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (electroionization subshell data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_native_ionization_subshells )
{
  // Create the set of electroatom aliases
  electroatom_aliases.clear();
  electroatom_aliases.insert( "Pb-Native" );

  // Set the bremsstrahlung photon angular distribution function
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  double cutoff_angle_cosine = 1.0;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
                                              cross_sections_xml_directory,
                                              cross_section_table_info,
                                              electroatom_aliases,
                                              atomic_relaxation_model_factory,
                                              hash_grid_bins,
                                              true,
                                              true,
                                              true,
                                              true,
                                              true,
                                              function,
                                              cutoff_angle_cosine ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  TEST_EQUALITY_CONST( electroatom_map.size(), 1 );
  TEST_ASSERT( electroatom_map.count( "Pb-Native" ) );
  TEST_ASSERT( !electroatom_map["Pb-Native"].is_null() );

  Teuchos::RCP<MonteCarlo::Electroatom>& atom = electroatom_map["Pb-Native"];

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.00E-05;
  double cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.629060119800000E+09,
                          1e-12 );


  energy = 2.00E-01;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.252314241820250E+07,
                          1e-12 );


  energy = 1.00E+05;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.957013047900000E+06,
                          1e-12 );

  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   2.000000000000E-03,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   4.000000000000E-04,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                   9.000000000000E-05,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
           1.000000000000E-05,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           9.121750E-02,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.500920E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           1.000000000000E+05,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
          1.000000000000E-05,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1.000000000000E-03,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.248850E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1.000000000000E+05,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    5.520610E-04,
                 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.235190E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.869800E+03, 1e-12 );

  // Test that the analog elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.000E+05,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.830509999999990E-02 + 2.1116099116949E+06,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.995260E+01,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.0571E+06 + 1.088440E+06,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    6.309570E+00,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.68623E+06 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.100574153670E+08 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.436635458458E+08 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.887469904554E+08 + 0.0,
                          1e-12 );

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the screened Rutherford elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the moment preserving elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that tables are not duplicated
TEUCHOS_UNIT_TEST( ElectroatomFactory, no_duplicate_tables )
{
  // Create the set of electroatom aliases
  electroatom_aliases.clear();
  electroatom_aliases.insert( "H-1_293.6K" );
  electroatom_aliases.insert( "H-1_300K" );

  // Set the bremsstrahlung photon angular distribution function
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  double cutoff_angle_cosine = 1.0;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
        cross_sections_xml_directory,
        cross_section_table_info,
        electroatom_aliases,
        atomic_relaxation_model_factory,
        hash_grid_bins,
        true,
        true,
        true,
        true,
        true,
        function,
        cutoff_angle_cosine ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  TEST_EQUALITY_CONST( electroatom_map.size(), 2 );

  TEST_ASSERT( electroatom_map.count( "H-1_293.6K" ) );
  TEST_ASSERT( !electroatom_map["H-1_293.6K"].is_null() );

  TEST_ASSERT( electroatom_map.count( "H-1_300K" ) );
  TEST_ASSERT( !electroatom_map["H-1_300K"].is_null() );

  TEST_EQUALITY( electroatom_map["H-1_293.6K"], electroatom_map["H-1_300K"] );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &cross_sections_xml_directory,
                   "Test cross_sections.xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  {
    std::string cross_sections_xml_file = cross_sections_xml_directory;
    cross_sections_xml_file += "/cross_sections.xml";

    // Read in the xml file storing the cross section table info
    Teuchos::updateParametersFromXmlFile(
           cross_sections_xml_file,
           Teuchos::inoutArg( cross_section_table_info ) );

    // Create the atomic relaxation model factory
    atomic_relaxation_model_factory.reset(
        new MonteCarlo::AtomicRelaxationModelFactory );
  }

  hash_grid_bins = 100;
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();


//---------------------------------------------------------------------------//
// end tstElectroatomFactory.cpp
//---------------------------------------------------------------------------//
