//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomEPR14Factory.cpp
//! \author Luke Kersting
//! \brief  Positronatom factory using EPR14 data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PositronatomACEFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor;
std::shared_ptr<const MonteCarlo::AtomicRelaxationModel> relaxation_model;
std::string positronatom_name;
double atomic_weight;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a basic positron-atom can be created
FRENSIE_UNIT_TEST( PositronatomACEFactory, createPositronatom_basic )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  atom.reset();
  MonteCarlo::PositronatomACEFactory::createPositronatom( *xss_data_extractor,
                                                        positronatom_name,
                                                        atomic_weight,
                                                        relaxation_model,
                                                        properties,
                                                        atom );

  // Test the positron-atom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.14p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  double energy, cross_section;

  // Test that the total cross section can be returned
  energy = 2e-3;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.806193787852e8, 1e-12 );

  energy = 4e-4;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.278128947846e9, 1e-12 );

  energy = 9e-5;
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

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );

  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.100574153670e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 8.9754e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.250673571307e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.06530e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.774672656160e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );

  atom.reset();
}

//---------------------------------------------------------------------------//
/* Check that a positron-atom with detailed 2BS photon angular distribution
 * data can be created
 */
FRENSIE_UNIT_TEST( PositronatomACEFactory, createPositronatom_detailed_brem )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::TWOBS_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomACEFactory::createPositronatom( *xss_data_extractor,
                                                        positronatom_name,
                                                        atomic_weight,
                                                        relaxation_model,
                                                        properties,
                                                        atom );

  // Test the positron-atom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.14p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  double energy, cross_section;

  // Test that the total cross section can be returned
  energy = 2e-3;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.806193787852e8, 1e-12 );

  energy = 4e-4;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.278128947846e9, 1e-12 );

  energy = 9e-5;
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

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );

  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.100574153670e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 8.9754e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.250673571307e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.06530e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.774672656160e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a positron-atom without elastic subshell data can be created
FRENSIE_UNIT_TEST( PositronatomACEFactory, createPositronatom_no_elastic )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setElasticModeOff();

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomACEFactory::createPositronatom( *xss_data_extractor,
                                                        positronatom_name,
                                                        atomic_weight,
                                                        relaxation_model,
                                                        properties,
                                                        atom );

  // Test the positron-atom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.14p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2e-3;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.806193787852e8-2.100574153670e8, 1e-12 );

  energy = 4e-4;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.278128947846e9-4.436635458458e8, 1e-12 );

  energy = 9e-5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.411603154884e9-8.887469904554e8, 1e-12 );


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

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );

  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 8.9754e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.250673571307e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.06530e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.774672656160e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a positron-atom without electroionization subshell data can be created
FRENSIE_UNIT_TEST( PositronatomACEFactory, createPositronatom_no_electroionization )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setElectroionizationModeOff();

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomACEFactory::createPositronatom( *xss_data_extractor,
                                                        positronatom_name,
                                                        atomic_weight,
                                                        relaxation_model,
                                                        properties,
                                                        atom );

  // Test the positron-atom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.14p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2e-3;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.806193787852e8-7.403570475672e7, 1e-12 );

  energy = 4e-4;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.278128947846e9-2.117744877649e8, 1e-12 );

  energy = 9e-5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.411603154884e9-3.624289144575e8, 1e-12 );


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

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );

  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.100574153670e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a positron-atom without bremsstrahlung data can be created
FRENSIE_UNIT_TEST( PositronatomACEFactory, createPositronatom_no_bremsstrahlung )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setBremsstrahlungModeOff();

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomACEFactory::createPositronatom( *xss_data_extractor,
                                                        positronatom_name,
                                                        atomic_weight,
                                                        relaxation_model,
                                                        properties,
                                                        atom );


  // Test the positron-atom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.14p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2e-3;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.806193787852e8-9.258661418255e3, 1e-12 );

  energy = 4e-4;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.278128947846e9-8.914234996439e3, 1e-12 );

  energy = 9e-5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.411603154884e9-7.249970966838e3, 1e-12 );


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

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042e9, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.100574153670e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 8.9754e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.250673571307e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.06530e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.774672656160e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a positron-atom without atomic excitation data can be created
FRENSIE_UNIT_TEST( PositronatomACEFactory, createPositronatom_no_atomic_excitation )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );
  properties.setAtomicExcitationModeOff();

  std::shared_ptr<const MonteCarlo::Positronatom> atom;

  MonteCarlo::PositronatomACEFactory::createPositronatom( *xss_data_extractor,
                                                        positronatom_name,
                                                        atomic_weight,
                                                        relaxation_model,
                                                        properties,
                                                        atom );

  // Test the positron-atom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.14p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2e-3;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.806193787852e8-1.965170e8, 1e-12 );

  energy = 4e-4;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.278128947846e9-6.22682e08, 1e-12 );

  energy = 9e-5;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.411603154884e9-1.16042e09, 1e-12 );

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

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439e3, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838e3, 1e-12 );

  // Test that the decoupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 2e-3, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.100574153670e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 9e-5, reaction);
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.887469904554e8, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  reaction = MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 4e-4, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction);
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 8.9754e-2, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.250673571307e-1, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  reaction = MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.06530e8, 1e-12 );

  cross_section = atom->getReactionCrossSection( 2e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.774672656160e7, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Create a file handler and data extractor
    std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace_file_name,
                                  "82000.14p",
                                  test_ace_file_start_line ) );
    
    xss_data_extractor.reset(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

    MonteCarlo::AtomicRelaxationModelFactory::createAtomicRelaxationModel(
           *xss_data_extractor,
           relaxation_model,
           1e-3,
           1e-5,
           true );

    positronatom_name = "82000.14p";
    atomic_weight = ace_file_handler->getTableAtomicWeightRatio()*
      Utility::PhysicalConstants::neutron_rest_mass_amu;
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomEPR14Factory.cpp
//---------------------------------------------------------------------------//
