//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomACEFactory.cpp
//! \author Luke Kersting
//! \brief  Electroatom factory using ACE data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomACEFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model;
std::string electroatom_name;
double atomic_weight;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a basic electroatom can be created
TEUCHOS_UNIT_TEST( ElectroatomACEFactory, createElectroatom_basic )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );

  Teuchos::RCP<MonteCarlo::Electroatom> atom;

  atom.reset();
  MonteCarlo::ElectroatomACEFactory::createElectroatom( *xss_data_extractor,
                                                        electroatom_name,
                                                        atomic_weight,
                                                        relaxation_model,
                                                        properties, 
                                                        atom );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  double energy, cross_section;

  // Test that the total cross section can be returned
  energy = 2e-3;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.806193787852E+08, 1e-12 );

  energy = 4e-4;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.278128947846E+09, 1e-12 );

  energy = 9e-5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.411603154884E+09, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
            1e-5,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            1e5,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
           1e-5,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           8.9754E-02,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.250673571307E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           1e5,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190000000E+01, 1e-12 );


  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
          1e-5,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          2e-3,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.774672656160E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1e5,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );


  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );


  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.100574153670E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 8.887469904554E+08, 1e-12 );

  atom.reset();
}


TEUCHOS_UNIT_TEST( ElectroatomACEFactory, createElectroatom_detailed_brem )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::TWOBS_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );

  Teuchos::RCP<MonteCarlo::Electroatom> atom;

  MonteCarlo::ElectroatomACEFactory::createElectroatom( *xss_data_extractor,
                                                        electroatom_name,
                                                        atomic_weight,
                                                        relaxation_model,
                                                        properties, 
                                                        atom );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  double energy, cross_section;

  // Test that the total cross section can be returned
  energy = 2e-3;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.806193787852E+08, 1e-12 );

  energy = 4e-4;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.278128947846E+09, 1e-12 );

  energy = 9e-5;
  cross_section = atom->getTotalCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.411603154884E+09, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 2e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 4e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 9e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );


  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 2.100574153670E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 8.887469904554E+08, 1e-12 );


  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
            1e-5,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            1e5,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );


  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
           1e-5,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           8.975400000000E-02,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.250673571307E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           1e5,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190000000E+01, 1e-12 );


  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
          1e-5,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          2e-3,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.774672656160E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1e5,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a electroatom with electroionization subshell data can be created
TEUCHOS_UNIT_TEST( ElectroatomACEFactory, createElectroatom_ionization_subshells )
{
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 100 );

  Teuchos::RCP<MonteCarlo::Electroatom> atom;
 
  MonteCarlo::ElectroatomACEFactory::createElectroatom( *xss_data_extractor,
                                                        electroatom_name,
                                                        atomic_weight,
                                                        relaxation_model,
                                                        properties,
                                                        atom );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 2e-3;
  double cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.806193787852E+08,
                          1e-12 );


  energy = 4e-4;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.278128947846E+09,
                          1e-12 );


  energy = 9e-5;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.411603154884E+09,
                          1e-12 );


  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1e-2 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2e-3 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4e-4,
                 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.100574153670E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.436635458458E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.887469904554E+08,
                          1e-12 );

  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
            1e-5,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
            1e5,
            MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
           1e-5,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           8.975400000000E-02,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.250673571307E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
           1e5,
           MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190000000E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
          1e-5,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          2e-3,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.774672656160E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
          1e5,
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace_file",
                   &test_ace_file_name,
                   "Test ACE file name" );
  clp().setOption( "test_ace_table",
                   &test_ace_table_name,
                   "Test ACE table name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace_file_name,
                                  test_ace_table_name,
                                  1u ) );
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

    electroatom_name = test_ace_table_name;
    atomic_weight = ace_file_handler->getTableAtomicWeightRatio()*
      Utility::PhysicalConstants::neutron_rest_mass_amu;
  }
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroatomACEFactory.cpp
//---------------------------------------------------------------------------//
