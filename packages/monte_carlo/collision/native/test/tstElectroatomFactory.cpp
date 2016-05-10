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
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"

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

  double cutoff_angle_cosine = 0.999999;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
        cross_sections_xml_directory,
        cross_section_table_info,
        electroatom_aliases,
        atomic_relaxation_model_factory,
        hash_grid_bins,  
        function,
        false,
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

  // Test that the total electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection( 
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.053785458456E+07, 1e-12 );
    
  cross_section = atom->getReactionCrossSection( 
                   2.000000000000E-03,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.403570475672E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
                   4.000000000000E-04,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.117744877649E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
                   9.000000000000E-05,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.624289144575E+08, 1e-12 );

  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		   1e-6,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
		   1e5,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

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

  double cutoff_angle_cosine = 0.999999;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
                                              cross_sections_xml_directory,
					                          cross_section_table_info,
                                              electroatom_aliases,
					                          atomic_relaxation_model_factory,
                                              hash_grid_bins,  
                                              function,
                                              false,
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

  // Test that the screened Rutherford elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 
                          2.1116099116949E+06, 
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          1.088440E+06, 
                          1e-12 );
  
  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          0.0, 
                          1e-12 );

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
                                              function,
                                              false,
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

  double cutoff_angle_cosine = 0.999999;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
        cross_sections_xml_directory,
        cross_section_table_info,
        electroatom_aliases,
        atomic_relaxation_model_factory,
        hash_grid_bins,  
        function,
        false,
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

  // Test that the total electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection( 
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.053785458456E+07, 1e-12 );
    
  cross_section = atom->getReactionCrossSection( 
                   2.000000000000E-03,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.403570475672E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
                   4.000000000000E-04,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.117744877649E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
                   9.000000000000E-05,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.624289144575E+08, 1e-12 );

  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		   1e-6,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
		   1e5,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

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

  double cutoff_angle_cosine = 0.999999;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
        cross_sections_xml_directory,
        cross_section_table_info,
        electroatom_aliases,
        atomic_relaxation_model_factory,
        hash_grid_bins,  
        function,
        true,
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

  // Test that the screened Rutherford elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 
                          2.1116099116949E+06, 
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          1.088440E+06, 
                          1e-12 );
  
  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  
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
  
  double cutoff_angle_cosine = 0.999999;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
                                              cross_sections_xml_directory,
					                          cross_section_table_info,
                                              electroatom_aliases,
					                          atomic_relaxation_model_factory,
                                              hash_grid_bins,
                                              function,
                                              true,
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

// Check that a electroatom map can be created (electroionization subshell data)
TEUCHOS_UNIT_TEST( ElectroatomFactory, createElectroatomMap_native_ionization_subshells )
{
  // Create the set of electroatom aliases
  electroatom_aliases.clear();
  electroatom_aliases.insert( "Pb-Native" );
  
  // Set the bremsstrahlung photon angular distribution function
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  double cutoff_angle_cosine = 0.999999;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
                                              cross_sections_xml_directory,
					                          cross_section_table_info,
                                              electroatom_aliases,
					                          atomic_relaxation_model_factory,
                                              hash_grid_bins,  
                                              function,
                                              true,
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

  // Test that the screened Rutherford elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 
                          2.1116099116949E+06, 
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          1.088440E+06, 
                          1e-12 );
  
  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  
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
  
  double cutoff_angle_cosine = 0.999999;

  electroatom_factory.reset( new MonteCarlo::ElectroatomFactory(
        cross_sections_xml_directory,
        cross_section_table_info,
        electroatom_aliases,
        atomic_relaxation_model_factory,
        hash_grid_bins,  
        function,
        true,
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
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_cross_sections_xml_directory",
                 &cross_sections_xml_directory,
                 "Test cross_sections.xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

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

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}


//---------------------------------------------------------------------------//
// end tstElectroatomFactory.cpp
//---------------------------------------------------------------------------//
