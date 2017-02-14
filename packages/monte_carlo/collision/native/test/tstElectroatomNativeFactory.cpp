//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Electroatom factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model;
std::string electroatom_name;
double atomic_weight;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
TEUCHOS_UNIT_TEST( ElectroatomNativeFactory, createElectroatom_detailed_brem )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::TWOBS_DISTRIBUTION );
  properties.setLinLinLogInterpolationModeOff();
  properties.setWeightedInterpolationModeOn();
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );

  Teuchos::RCP<MonteCarlo::Electroatom> atom;
  
  MonteCarlo::ElectroatomNativeFactory::createElectroatom( *data_container,
                                                           electroatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "Pb-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.62906011980e9, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.252314241820250e7, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.95701304790e6, 1e-12 );


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


  // Test that the analog elastic cross section can be returned
  reaction = MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.14554e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.68623e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.103010e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.1309e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.489240e9, 1e-12 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
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
}

//---------------------------------------------------------------------------//
// Check that a electroatom with a higher cutoff angle can be created
TEUCHOS_UNIT_TEST( ElectroatomNativeFactory, createElectroatom_cutoff )
{
  double cutoff_angle_cosine = 0.9;

  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setWeightedInterpolationModeOff();
  properties.setElasticCutoffAngleCosine( cutoff_angle_cosine );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  Teuchos::RCP<MonteCarlo::Electroatom> atom;
  
  MonteCarlo::ElectroatomNativeFactory::createElectroatom( *data_container,
                                                           electroatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
        cutoff_elastic_distribution,
        *data_container,
        cutoff_angle_cosine );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "Pb-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1e-5;
  double cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( energy, cutoff_angle_cosine );
  double inelastic = 1.398201198e8;
  double elastic = 2.48924e9*cross_section_ratio + 1.106329441558590e8;

  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 2e-1;
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( energy, cutoff_angle_cosine );
  inelastic = 6.411260911064270e6;
  elastic = 1.61118815071382e7*cross_section_ratio + 1.8916841363881219e+06;

  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 1e5;
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( energy, cutoff_angle_cosine );
  inelastic = 2.84540304790e6;
  elastic = 8.83051e-2*cross_section_ratio + 2.203770304996720e-3;

  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );


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

  cross_section = atom->getReactionCrossSection( 5.520610e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-5,reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the hybrid elastic cross section can be returned
  reaction = MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1e5, cutoff_angle_cosine );
  TEST_FLOATING_EQUALITY( cross_section,
                          8.83051e-2*cross_section_ratio + 2.20377030499672e-3,
                          1e-11 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1e-3, cutoff_angle_cosine );
  TEST_FLOATING_EQUALITY( cross_section,
                          2.90281E+8*cross_section_ratio + 1.2584013774057174E+8,
                          1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1.99526e-4, cutoff_angle_cosine );
  TEST_FLOATING_EQUALITY( cross_section,
                          6.1309E+8*cross_section_ratio + 2.133609331382077e8,
                          1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1.e-5, cutoff_angle_cosine );
  TEST_FLOATING_EQUALITY( cross_section,
                          2.489240e9*cross_section_ratio + 1.106329441558590e8,
                          1e-12 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no screened Rutherford reaction
  reaction = MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no moment preserving elastic cross section
  reaction = MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
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
}

//---------------------------------------------------------------------------//
// Check that a electroatom with no elastic data can be created
TEUCHOS_UNIT_TEST( ElectroatomNativeFactory, createElectroatom_no_elastic )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 0.9 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setElasticModeOff();

  Teuchos::RCP<MonteCarlo::Electroatom> atom;

  MonteCarlo::ElectroatomNativeFactory::createElectroatom( *data_container,
                                                           electroatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
        cutoff_elastic_distribution,
        *data_container,
        properties.getElasticCutoffAngleCosine() );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "Pb-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1e-5;
  double inelastic = 1.398201198e8;
  double elastic = 0.0;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );


  energy = 2e-1;
  inelastic = 6.411260911064270e6;
  elastic = 0.0;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 1e5;
  inelastic = 2.84540304790e6;
  elastic = 0.0;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );


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

  cross_section = atom->getReactionCrossSection( 5.520610e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-5,reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the hybrid elastic cross section can be returned
  reaction = MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no screened Rutherford reaction
  reaction = MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that there is no moment preserving elastic cross section
  reaction = MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
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
}

//---------------------------------------------------------------------------//
// Check that a electroatom with no electroionization subshell data can be created
TEUCHOS_UNIT_TEST( ElectroatomNativeFactory, createElectroatom_no_electroionization )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setElectroionizationModeOff();

  Teuchos::RCP<MonteCarlo::Electroatom> atom;
  
  MonteCarlo::ElectroatomNativeFactory::createElectroatom( *data_container,
                                                           electroatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "Pb-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.62906011980e9-1.310577e8, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.252314241820250e7-2.19690850106427e6, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.95701304790e6-1.2648388779e6, 1e-12 );


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

  cross_section = atom->getReactionCrossSection( 5.520610e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the analog elastic cross section can be returned
  reaction = MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.14554e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.68623e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.103010e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.1309e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.489240e9, 1e-12 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the moment preserving elastic cross section can be returned
  reaction = MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no K subshell electroionization cross section
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that tthere is no P3 subshell electroionization cross section
  reaction = MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a electroatom with no bremsstrahlung data can be created
TEUCHOS_UNIT_TEST( ElectroatomNativeFactory, createElectroatom_no_bremsstrahlung )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setBremsstrahlungModeOff();

  Teuchos::RCP<MonteCarlo::Electroatom> atom;
  
  MonteCarlo::ElectroatomNativeFactory::createElectroatom( *data_container,
                                                           electroatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "Pb-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.6290601198e9-4.8698e3, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.25231424182025e7-1.98241e3, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.9570130479e6-1.95417e3, 1e-12 );


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


  // Test that there is no bremsstrahlung cross section
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the analog elastic cross section can be returned
  reaction = MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.14554e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.68623e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.103010e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.1309e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.489240e9, 1e-12 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
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
}

//---------------------------------------------------------------------------//
// Check that a electroatom with no atomic excitation data can be created
TEUCHOS_UNIT_TEST( ElectroatomNativeFactory, createElectroatom_no_atomic_excitation )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setAtomicExcitationModeOff();

  Teuchos::RCP<MonteCarlo::Electroatom> atom;
  
  MonteCarlo::ElectroatomNativeFactory::createElectroatom( *data_container,
                                                           electroatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "Pb-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.6290601198e9-8.757550e6, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.252314241820250e7-4.21237e6, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.9570130479e6-1.57861e6, 1e-12 );


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
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  TEST_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the analog elastic cross section can be returned
  reaction = MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.14554e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.68623e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.103010e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 6.1309e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  TEST_FLOATING_EQUALITY( cross_section, 2.489240e9, 1e-12 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
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
}


//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Create the atomic relaxation model
  MonteCarlo::AtomicRelaxationModelFactory::createAtomicRelaxationModel(
                               *data_container,
                               relaxation_model,
                               1e-3,
                               1e-5,
                               true );

  // Initialize the remaining electroatom data
  electroatom_name = "Pb-Native";
  atomic_weight = 207.1999470456033;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
