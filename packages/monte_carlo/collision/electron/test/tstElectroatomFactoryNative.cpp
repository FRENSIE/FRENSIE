//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomFactoryNative.cpp
//! \author Luke Kersting
//! \brief  Electroatom factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<const boost::filesystem::path> data_directory;
std::unique_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase> electroatom_definitions;
std::shared_ptr<MonteCarlo::AtomicRelaxationModelFactory>
atomic_relaxation_model_factory;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a electroatom map can be created with moment preserving data
FRENSIE_UNIT_TEST( ElectroatomFactory, createElectroatomMap_hybrid )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-15;

  // Create the set of electroatom aliases
  MonteCarlo::ElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
  electroatom_aliases.insert( "Pb-Native" );

  // Set the bremsstrahlung photon angular distribution function
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElectronTwoDInterpPolicy( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  properties.setElectronTwoDGridPolicy( MonteCarlo::CORRELATED_GRID );
  properties.setElasticElectronDistributionMode( MonteCarlo::HYBRID_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( cutoff_angle_cosine );
  properties.setElectronEvaluationTolerance( evaluation_tol );
  properties.setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                               new MonteCarlo::ElectroatomFactory(
                                               *data_directory,
                                               electroatom_aliases,
                                               *electroatom_definitions,
                                               atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::ElectroatomFactory::ElectroatomNameMap electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  // Create the native data file container
  std::unique_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container(
     new Data::ElectronPhotonRelaxationDataContainer( *data_directory / electroatom_definitions->getDefinition( "Pb-Native" ).getElectroatomicDataProperties().filePath() ) );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LogLogCosLog,Utility::UnitBaseCorrelated>(
        elastic_distribution,
        *data_container,
        properties.getElasticCutoffAngleCosine(),
        properties.getElectronEvaluationTolerance() );

  FRENSIE_CHECK_EQUAL( electroatom_map.size(), 1 );
  FRENSIE_CHECK( electroatom_map.count( "Pb-Native" ) );
  FRENSIE_CHECK( electroatom_map["Pb-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Electroatom>& atom = electroatom_map["Pb-Native"];

  // Test the electroatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-6 );


  // Test that the total cross section can be returned
  double energy = 1e-5;
  double cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( energy );
  double inelastic = 1.398201198e8;
  double elastic = 2.48924e9*cross_section_ratio + 1.1063294415585944e+08;

  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 2e-1;
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( energy );
  inelastic = 6.4103437333324831e+06;
  elastic = 1.6111881507138280e+07*cross_section_ratio + 1.8627628267192466e+06;

  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 1e5;
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( energy );
  inelastic = 2.8454030479e+06;
  elastic = 8.83051e-2*cross_section_ratio + 2.2037703049967248e-03;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-2 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  MonteCarlo::ElectroatomicReactionType reaction;

  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-2, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.06530e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.52061e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.23519e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the hybrid elastic cross section can be returned
  reaction = MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.83051e-2*cross_section_ratio + 2.2037700886489448e-03,
                          1e-11 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( 1.0e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          2.90281E+8*cross_section_ratio + 1.2584013774057175e+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( 1.995260e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          4.8815266556554884e+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  cross_section_ratio =
            elastic_distribution->evaluateCutoffCrossSectionRatio( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          2.48924E+9*cross_section_ratio + 1.1063294415585944e+08,
                          1e-12 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no screened Rutherford reaction
  reaction = MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.99526e1, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.30957, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no moment preserving elastic cross section
  reaction = MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.99526e1, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.30957, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  electroatom_map.clear();
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (2BS bremsstrahlung data)
FRENSIE_UNIT_TEST( ElectroatomFactory, createElectroatomMap_native_2BS_brem )
{
  // Create the set of electroatom aliases
  MonteCarlo::ElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
  electroatom_aliases.insert( "Pb-Native" );

  // Set the bremsstrahlung photon angular distribution function
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction(
                                              MonteCarlo::TWOBS_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                                      new MonteCarlo::ElectroatomFactory(
                                               *data_directory,
                                               electroatom_aliases,
                                               *electroatom_definitions,
                                               atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::ElectroatomFactory::ElectroatomNameMap electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  FRENSIE_CHECK_EQUAL( electroatom_map.size(), 1 );
  FRENSIE_CHECK( electroatom_map.count( "Pb-Native" ) );
  FRENSIE_CHECK( electroatom_map["Pb-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Electroatom>& atom = electroatom_map["Pb-Native"];

  // Test the electroatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-6 );


  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.62906011980000019073e+09, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.25222252404707632959e+07, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.95701304790000058711e+06, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.0e-2 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9.0e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  MonteCarlo::ElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.14554e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.68623e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2e-1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.61118815071382801980e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.10301e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.1309e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-2, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a electroatom map can be created (electroionization subshell data)
FRENSIE_UNIT_TEST( ElectroatomFactory, createElectroatomMap_native_ionization_subshells )
{
  // Create the set of electroatom aliases
  MonteCarlo::ElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
  electroatom_aliases.insert( "Pb-Native" );

  // Set the bremsstrahlung photon angular distribution function
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  // Set the elastic cutoff angle cosine to 1.0
  properties.setElasticCutoffAngleCosine( 1.0 );
  // Set atomic relaxation on for electrons
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );

  // Create the electratom factory
  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                                   new MonteCarlo::ElectroatomFactory(
                                              *data_directory,
                                               electroatom_aliases,
					       *electroatom_definitions,
					       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::ElectroatomFactory::ElectroatomNameMap electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  FRENSIE_CHECK_EQUAL( electroatom_map.size(), 1 );
  FRENSIE_CHECK( electroatom_map.count( "Pb-Native" ) );
  FRENSIE_CHECK( electroatom_map["Pb-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Electroatom>& atom = electroatom_map["Pb-Native"];

  // Test the electroatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-6 );


  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.62906011980000019073e+09, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.25222252404707632959e+07, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.95701304790000058711e+06, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-2 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  MonteCarlo::ElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.14554e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.68623e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2e-1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.61118815071382801980e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.10301e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.1309e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );

  // Reset the electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that tables are not duplicated
FRENSIE_UNIT_TEST( ElectroatomFactory, no_duplicate_tables )
{
  // Create the set of electroatom aliases
  MonteCarlo::ElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
  electroatom_aliases.insert( "H-1_293.6K" );
  electroatom_aliases.insert( "H-1_300K" );

  // Set the bremsstrahlung photon angular distribution function
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction(
                                             MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ElectroatomFactory> electroatom_factory(
                                           new MonteCarlo::ElectroatomFactory(
                                               *data_directory,
                                               electroatom_aliases,
					       *electroatom_definitions,
					       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::ElectroatomFactory::ElectroatomNameMap electroatom_map;

  electroatom_factory->createElectroatomMap( electroatom_map );

  FRENSIE_CHECK_EQUAL( electroatom_map.size(), 2 );

  FRENSIE_CHECK( electroatom_map.count( "H-1_293.6K" ) );
  FRENSIE_CHECK( electroatom_map["H-1_293.6K"].get() != NULL );

  FRENSIE_CHECK( electroatom_map.count( "H-1_300K" ) );
  FRENSIE_CHECK( electroatom_map["H-1_300K"].get() != NULL );

  FRENSIE_CHECK( electroatom_map["H-1_293.6K"] == electroatom_map["H-1_300K"] );
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

  // Initialize the electroatom definitions
  electroatom_definitions.reset( new MonteCarlo::ScatteringCenterDefinitionDatabase );

  MonteCarlo::ScatteringCenterDefinition& h1_293K_definition =
    electroatom_definitions->createDefinition( "H-1_293.6K", 1001 );

  h1_293K_definition.setElectroatomicDataProperties(
           h_properties.getSharedElectroatomicDataProperties(
                     Data::ElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

  electroatom_definitions->createDefinitionAlias( "H-1_293.6K", "H-1_300K" );

  MonteCarlo::ScatteringCenterDefinition& pb_native_definition =
    electroatom_definitions->createDefinition( "Pb-Native", Data::Pb_ATOM );

  pb_native_definition.setElectroatomicDataProperties(
         pb_properties.getSharedElectroatomicDataProperties(
                     Data::ElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

  // Create the atomic relaxation model factory
  atomic_relaxation_model_factory.reset(
                new MonteCarlo::AtomicRelaxationModelFactory );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();


//---------------------------------------------------------------------------//
// end tstElectroatomFactoryNative.cpp
//---------------------------------------------------------------------------//
