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
Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory>
atomic_relaxation_model_factory;

std::shared_ptr<MonteCarlo::SimulationProperties> properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (only basic data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_ace_basic )
{
  // Create the set of electroatom aliases
  std::unordered_set<std::string> electroatom_aliases;
  electroatom_aliases.insert( "Pb" );

  // Set the bremsstrahlung photon angular distribution function
  properties->setBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  properties->setElasticCutoffAngleCosine( 1.0 );
  properties->setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                              new MonteCarlo::ElectroatomFactory(
                                               cross_sections_xml_directory,
                                               cross_section_table_info,
                                               electroatom_aliases,
                                               atomic_relaxation_model_factory,
                                               *properties ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_map.clear();
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
  double energy = 2.0e-3;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.806193787852e8, 1e-12 );

  energy = 4.0e-4;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.278128947846e9, 1e-12 );

  energy = 9.0e-5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.411603154884e9, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  MonteCarlo::ElectroatomicReactionType reaction;

  // Test that the total electroionization cross section can be returned
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.4035704756720006e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.117744877649e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 3.6242891445749998e+08, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );


  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction);
  TEST_FLOATING_EQUALITY( cross_section, 2.100574153670e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction);
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction);
  TEST_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created using eprdata14 file
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_epr14 )
{
  // Create the set of electroatom aliases
  std::unordered_set<std::string> electroatom_aliases;
  electroatom_aliases.insert( "Pb_v14" );

  // Set the bremsstrahlung photon angular distribution function
  properties->setBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  properties->setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                              new MonteCarlo::ElectroatomFactory(
                                               cross_sections_xml_directory,
                                               cross_section_table_info,
                                               electroatom_aliases,
                                               atomic_relaxation_model_factory,
                                               *properties ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_map.clear();
  electroatom_factory->createElectroatomMap( electroatom_map );

  TEST_EQUALITY_CONST( electroatom_map.size(), 1 );
  TEST_ASSERT( electroatom_map.count( "Pb_v14" ) );
  TEST_ASSERT( !electroatom_map["Pb_v14"].is_null() );

  Teuchos::RCP<MonteCarlo::Electroatom>& atom = electroatom_map["Pb_v14"];

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.14p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.6290601198e+09, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.25222252404707632959e+07, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.9570130479e+06, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  MonteCarlo::ElectroatomicReactionType reaction;

  // Test that the total electroionization cross section can be returned
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.4035704756720006e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.117744877649e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 3.6242891445749998e+08, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction);
  TEST_FLOATING_EQUALITY( cross_section, 2.100574153670e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction);
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction);
  TEST_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction);
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction);
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction);
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created with moment preserving data
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_hybrid )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-15;

  // Create the set of electroatom aliases
  std::unordered_set<std::string> electroatom_aliases;
  electroatom_aliases.insert( "Pb-Native" );

  // Set the bremsstrahlung photon angular distribution function
  properties->setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties->setElectronTwoDInterpPolicy( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  properties->setElectronTwoDSamplingPolicy( MonteCarlo::CORRELATED_SAMPLING );
  properties->setElasticElectronDistributionMode( MonteCarlo::HYBRID_DISTRIBUTION );
  properties->setElasticCutoffAngleCosine( cutoff_angle_cosine );
  properties->setElectronEvaluationTolerance( evaluation_tol );
  properties->setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                               new MonteCarlo::ElectroatomFactory(
                                               cross_sections_xml_directory,
                                               cross_section_table_info,
                                               electroatom_aliases,
                                               atomic_relaxation_model_factory,
                                               *properties ) );

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
    new Data::ElectronPhotonRelaxationDataContainer( electroatom_file_path ) );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LogLogCosLog,Utility::UnitBaseCorrelated>(
        elastic_distribution,
        *data_container,
        properties->getElasticCutoffAngleCosine(),
        properties->getElectronEvaluationTolerance() );

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
            elastic_distribution->evaluateCutoffCrossSectionRatio( energy );
  double inelastic = 1.398201198e8;
  double elastic = 2.48924e9*cross_section_ratio + 1.1063294415585944e+08;

  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 2e-1;
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( energy );
  inelastic = 6.4103437333324831e+06;
  elastic = 1.6111881507138280e+07*cross_section_ratio + 1.8627628267192466e+06;

  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 1e5;
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( energy );
  inelastic = 2.8454030479e+06;
  elastic = 8.83051e-2*cross_section_ratio + 2.2037703049967248e-03;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  MonteCarlo::ElectroatomicReactionType reaction;

  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-2, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.06530e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.52061e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.23519e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the hybrid elastic cross section can be returned
  reaction = MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( 1e5 );
  TEST_FLOATING_EQUALITY( cross_section,
                          8.83051e-2*cross_section_ratio + 2.2037700886489448e-03,
                          1e-11 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section,
                          2.90281E+8*cross_section_ratio + 1.2584013774057175e+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( 1.995260e-4 );
  TEST_FLOATING_EQUALITY( cross_section,
                          6.1309E+8*cross_section_ratio + 2.5195477504187709e+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section,
                          2.48924E+9*cross_section_ratio + 1.1063294415585944e+08,
                          1e-12 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no screened Rutherford reaction
  reaction = MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.99526e1, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.30957, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no moment preserving elastic cross section
  reaction = MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.99526e1, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.30957, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  electroatom_map.clear();
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (2BS bremsstrahlung data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_ace_2BS_brem )
{
  // Create the set of electroatom aliases
  std::unordered_set<std::string> electroatom_aliases;
  electroatom_aliases.insert( "Pb" );

  // Set the bremsstrahlung photon angular distribution function
  properties->setBremsstrahlungAngularDistributionFunction(
                                              MonteCarlo::TWOBS_DISTRIBUTION );
  properties->setElasticCutoffAngleCosine( 1.0 );
  properties->setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                                  new MonteCarlo::ElectroatomFactory(
                                               cross_sections_xml_directory,
                                               cross_section_table_info,
                                               electroatom_aliases,
                                               atomic_relaxation_model_factory,
                                               *properties ) );

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
  double energy, cross_section;
  energy = 2.0e-3;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.806193787852e8, 1e-12 );

  energy = 4.0e-4;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.278128947846e9, 1e-12 );

  energy = 9.0e-5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.411603154884e9, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.0e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  MonteCarlo::ElectroatomicReactionType reaction;

  // Test that the total electroionization cross section can be returned
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.4035704756720006e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.117744877649e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 3.6242891445749998e+08, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );


  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.10057415367e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (2BS bremsstrahlung data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_native_2BS_brem )
{
  // Create the set of electroatom aliases
  std::unordered_set<std::string> electroatom_aliases;
  electroatom_aliases.insert( "Pb-Native" );

  // Set the bremsstrahlung photon angular distribution function
  properties->setBremsstrahlungAngularDistributionFunction(
                                              MonteCarlo::TWOBS_DISTRIBUTION );
  properties->setElasticCutoffAngleCosine( 1.0 );
  properties->setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                                      new MonteCarlo::ElectroatomFactory(
                                               cross_sections_xml_directory,
                                               cross_section_table_info,
                                               electroatom_aliases,
                                               atomic_relaxation_model_factory,
                                               *properties ) );

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
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.62906011980000019073e+09, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.25222252404707632959e+07, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.95701304790000058711e+06, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.0e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  MonteCarlo::ElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.14554e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.68623e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2e-1, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.61118815071382801980e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.10301e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.1309e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-2, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (electroionization subshell data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_ace_ionization_subshells )
{
  // Create the set of electroatom aliases
  std::unordered_set<std::string> electroatom_aliases;
  electroatom_aliases.insert( "Pb" );

  // Set the bremsstrahlung photon angular distribution function
  properties->setBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  properties->setElasticCutoffAngleCosine( 1.0 );
  properties->setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                                      new MonteCarlo::ElectroatomFactory(
                                              cross_sections_xml_directory,
                                              cross_section_table_info,
                                              electroatom_aliases,
                                              atomic_relaxation_model_factory,
                                              *properties ) );

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
  double energy = 2.0e-3;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.806193787852e8, 1e-12 );

  energy = 4.0e-4;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.278128947846e9, 1e-12 );

  energy = 9.0e-5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.411603154884e9, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.0e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  MonteCarlo::ElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );


  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.100574153670e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );


  // Test that the total electroionization cross section can be returned
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 7.4035704756720006e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.117744877649e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 3.6242891445749998e+08, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (electroionization subshell data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_native_ionization_subshells )
{
  // Create the set of electroatom aliases
  std::unordered_set<std::string> electroatom_aliases;
  electroatom_aliases.insert( "Pb-Native" );

  // Set the bremsstrahlung photon angular distribution function
  properties->setBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  // Set the secondary interpolation policy to LinLinLin
//  properties->setLinLinLogInterpolationModeOff();
  // Set the elastic cutoff angle cosine to 1.0
  properties->setElasticCutoffAngleCosine( 1.0 );
  // Set atomic relaxation on for electrons
  properties->setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );

  // Create the electratom factory
  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                                   new MonteCarlo::ElectroatomFactory(
                                              cross_sections_xml_directory,
                                              cross_section_table_info,
                                              electroatom_aliases,
                                              atomic_relaxation_model_factory,
                                              *properties ) );

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
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.62906011980000019073e+09, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.25222252404707632959e+07, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.95701304790000058711e+06, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  MonteCarlo::ElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.14554e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.68623e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2e-1, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.61118815071382801980e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.10301e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.1309e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that tables are not duplicated
TEUCHOS_UNIT_TEST( ElectroatomFactory, no_duplicate_tables )
{
  // Create the set of electroatom aliases
  std::unordered_set<std::string> electroatom_aliases;
  electroatom_aliases.insert( "H-1_293.6K" );
  electroatom_aliases.insert( "H-1_300K" );

  // Set the bremsstrahlung photon angular distribution function
  properties->setBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  properties->setElasticCutoffAngleCosine( 1.0 );
  properties->setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                                           new MonteCarlo::ElectroatomFactory(
                                               cross_sections_xml_directory,
                                               cross_section_table_info,
                                               electroatom_aliases,
                                               atomic_relaxation_model_factory,
                                               *properties ) );

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
  std::string cross_sections_xml_file = cross_sections_xml_directory;
  cross_sections_xml_file += "/cross_sections.xml";

  // Read in the xml file storing the cross section table info
  Teuchos::updateParametersFromXmlFile(
                   cross_sections_xml_file,
                   Teuchos::inoutArg( cross_section_table_info ) );

  // Create the atomic relaxation model factory
  atomic_relaxation_model_factory.reset(
                new MonteCarlo::AtomicRelaxationModelFactory );

  // Create the simulation properties
  properties.reset( new MonteCarlo::SimulationProperties );
  properties->setNumberOfElectronHashGridBins( 100 );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();


//---------------------------------------------------------------------------//
// end tstElectroatomFactory.cpp
//---------------------------------------------------------------------------//
