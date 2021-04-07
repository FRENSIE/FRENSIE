//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Positronatom factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_PositronatomNativeFactory.hpp"
#include "MonteCarlo_PositronatomicReactionType.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<const MonteCarlo::AtomicRelaxationModel> relaxation_model;
std::string positronatom_name;
double atomic_weight;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
/* Check that a positronatom with detailed 2BS photon angular distribution
 * data can be created
 */
FRENSIE_UNIT_TEST( PositronatomNativeFactory, createPositronatom_default )
{
  MonteCarlo::SimulationProperties properties;

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomNativeFactory::createPositronatom( *data_container,
                                                           positronatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  // Test the positronatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "Pb-Native" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

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


  MonteCarlo::PositronatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.21237e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-1,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.98241e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.23519e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );



  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION;
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
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


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

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
/* Check that a positronatom with a decoupled elastic distribution and
 * detailed 2BS photon angular distribution data and can be created */
FRENSIE_UNIT_TEST( PositronatomNativeFactory, createPositronatom_decoupled )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::TWOBS_DISTRIBUTION );
  properties.setElectronTwoDInterpPolicy( MonteCarlo::LINLINLOG_INTERPOLATION );
  properties.setElasticElectronDistributionMode( MonteCarlo::DECOUPLED_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomNativeFactory::createPositronatom( *data_container,
                                                           positronatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  // Test the positronatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "Pb-Native" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

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


MonteCarlo::PositronatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.21237e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-1,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.98241e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.23519e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
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


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


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

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
/* Check that a positronatom with a cutoff elastic distribution can be created */
FRENSIE_UNIT_TEST( PositronatomNativeFactory, createPositronatom_cutoff )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElectronTwoDInterpPolicy( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  properties.setElasticElectronDistributionMode( MonteCarlo::CUTOFF_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 0.999999 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomNativeFactory::createPositronatom( *data_container,
                                                           positronatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  // Test the positronatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "Pb-Native" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.62906011980000019073e+09, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.25222252404707632959e+07, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.83051e-2+2.8454030479e6, 1e-12 );


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
  cross_section = atom->getReactionCrossSection( 2e-1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.21237e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-1,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.98241e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.23519e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.83051e-02, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0571e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.30957, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.68623e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.103010e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.1309e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.489240e9, 1e-12 );


  // Test that there is no total positron-ionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a positronatom with a hybrid elastic distribution can be created
FRENSIE_UNIT_TEST( PositronatomNativeFactory, createPositronatom_hybrid )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-15;

  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElectronTwoDInterpPolicy( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  properties.setElectronTwoDGridPolicy( MonteCarlo::CORRELATED_GRID );
  properties.setElasticElectronDistributionMode( MonteCarlo::HYBRID_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( cutoff_angle_cosine );
  properties.setElectronEvaluationTolerance( evaluation_tol );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomNativeFactory::createPositronatom( *data_container,
                                                           positronatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LogNudgedLogCosLog,Utility::Correlated>(
        cutoff_elastic_distribution,
        *data_container,
        properties.getElasticCutoffAngleCosine(),
        properties.getElectronEvaluationTolerance() );

  // Test the positronatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "Pb-Native" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1e-5;
  double cross_section_ratio =
    cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( energy );
  double inelastic = 1.398201198e+08;
  double elastic = 2.48924e9*cross_section_ratio + 1.1063294415585944e+08;

  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 2e-1;
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( energy );
  inelastic = 6.4103437333324831e+06;
  elastic = 1.6111881507138280e+07*cross_section_ratio + 1.8627628267192466e+06;

  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 1e5;
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( energy );
  inelastic = 2.8454030478999997e+06;
  elastic = 8.83051e-2*cross_section_ratio + 2.2037703049967248e-03;

  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );


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
  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-5,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the hybrid elastic cross section can be returned
  reaction = MonteCarlo::HYBRID_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.83051e-02*cross_section_ratio + 2.2037700886489448e-03,
                          1e-11 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          2.90281E+8*cross_section_ratio + 1.2584013774057175e+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( 1.995260e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          4.8815266556554884e+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          2.48924e9*cross_section_ratio + 1.1063294415585944e+08,
                          1e-12 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no screened Rutherford reaction
  reaction = MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no moment preserving elastic cross section
  reaction = MonteCarlo::MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


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

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a positronatom with no elastic data can be created
FRENSIE_UNIT_TEST( PositronatomNativeFactory, createPositronatom_no_elastic )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElectronEvaluationTolerance( 1e-7 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setElasticModeOff();

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomNativeFactory::createPositronatom( *data_container,
                                                           positronatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLog,Utility::Correlated>(
        cutoff_elastic_distribution,
        *data_container,
        1.0,
        properties.getElectronEvaluationTolerance() );

  // Test the positronatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "Pb-Native" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1e-5;
  double inelastic = 1.398201198e8;
  double elastic = 0.0;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );


  energy = 2e-1;
  inelastic = 6.4103437333324831e+06;
  elastic = 0.0;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );

  energy = 1e5;
  inelastic = 2.84540304790e6;
  elastic = 0.0;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, inelastic + elastic, 1e-12 );


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
  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-5,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the hybrid elastic cross section can be returned
  reaction = MonteCarlo::HYBRID_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no screened Rutherford reaction
  reaction = MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that there is no moment preserving elastic cross section
  reaction = MonteCarlo::MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


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

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a positronatom with no positron-ionization subshell data can be created
FRENSIE_UNIT_TEST( PositronatomNativeFactory, createPositronatom_no_positronionization )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setElectroionizationModeOff();

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomNativeFactory::createPositronatom( *data_container,
                                                           positronatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  // Test the positronatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "Pb-Native" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.6290601198e9-1.310577e8, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2522225240470763e7-2.1959913233324825e6, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.9570130479e6-1.2648388779e6, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1.0e5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2.0e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4.0e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 1.0e-5 );
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
  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.14554e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.68623e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.103010e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.1309e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.489240e9, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the moment preserving elastic cross section can be returned
  reaction = MonteCarlo::MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no total positron-ionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no K subshell positron-ionization cross section
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that tthere is no P3 subshell positron-ionization cross section
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a positronatom with no bremsstrahlung data can be created
FRENSIE_UNIT_TEST( PositronatomNativeFactory, createPositronatom_no_bremsstrahlung )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setBremsstrahlungModeOff();

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomNativeFactory::createPositronatom( *data_container,
                                                           positronatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  // Test the positronatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "Pb-Native" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.6290601198e9-4.8698e3, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2522225240470763e+07-1.98241e3, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.9570130479e6-1.95417e3, 1e-12 );


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


  // Test that there is no bremsstrahlung cross section
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-3,reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.14554e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.68623e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.103010e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.1309e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.489240e9, 1e-12 );


  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no total positron-ionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a positronatom with no atomic excitation data can be created
FRENSIE_UNIT_TEST( PositronatomNativeFactory, createPositronatom_no_atomic_excitation )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setAtomicExcitationModeOff();

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomNativeFactory::createPositronatom( *data_container,
                                                           positronatom_name,
                                                           atomic_weight,
                                                           relaxation_model,
                                                           properties,
                                                           atom );

  // Test the positronatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "Pb-Native" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.0e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.6290601198e9-8.757550e6, 1e-12 );

  energy = 2.0e-1;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2522225240470763e7-4.21237e6, 1e-12 );

  energy = 1.0e5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.9570130479e6-1.57861e6, 1e-12 );


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
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4.0e-4, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 9.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 5.520610e-4,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.235190e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5,reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.14554e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.68623e6, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.103010e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.1309e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.489240e9, 1e-12 );

  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no cutoff elastic cross section
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e1, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 6.309570e0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.995260e-4, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


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

  cross_section = atom->getReactionCrossSection( 9.121750e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.500920e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );


  // Test that the P3 subshell positron-ionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1.0e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1.0e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
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

  // Initialize the remaining positronatom data
  positronatom_name = "Pb-Native";
  atomic_weight = 207.1999470456033;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomNativeFactory.cpp
//---------------------------------------------------------------------------//
