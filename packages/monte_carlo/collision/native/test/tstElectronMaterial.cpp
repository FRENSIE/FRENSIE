//---------------------------------------------------------------------------//
//!
//! \file   tstElectronMaterial.cpp
//! \author Luke Kersting
//! \brief  Electron material class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_ElectronMaterial.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectronMaterial> material;

std::string test_cross_sections_xml_directory;
Teuchos::ParameterList cross_section_table_info;
boost::unordered_set<std::string> electroatom_aliases;
Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
TEUCHOS_UNIT_TEST( ElectronMaterial, getId )
{
  TEST_EQUALITY_CONST( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
TEUCHOS_UNIT_TEST( ElectronMaterial, getNumberDensity )
{
  TEST_FLOATING_EQUALITY( material->getNumberDensity(),
                          2.9064395906311e-3,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
TEUCHOS_UNIT_TEST( ElectronMaterial, getMacroscopicTotalCrossSection )
{
  double energy = 1.00000e-05;
  double cross_section =
    material->getMacroscopicTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.641204418336E+06,
                          1e-12 );


  energy = 1.00000e+05;
  cross_section =
    material->getMacroscopicTotalCrossSection( energy );

  cross_section =
    material->getMacroscopicTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.269992326372E+03,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic absorption cross section can be returned
TEUCHOS_UNIT_TEST( ElectronMaterial, getMacroscopicAbsorptionCrossSection )
{
  double cross_section =
    material->getMacroscopicAbsorptionCrossSection( 1.00000e-05 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section =
    material->getMacroscopicAbsorptionCrossSection( 1.00000e+00 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section =
    material->getMacroscopicAbsorptionCrossSection( 1.00000e+05 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( ElectronMaterial, getSurvivalProbability )
{
  double survival_prob =
    material->getSurvivalProbability( 1.00000e-05 );

  TEST_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );

  survival_prob =
    material->getSurvivalProbability( 1.00000e+05 );

  TEST_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic cross section for a specific reaction can be ret
TEUCHOS_UNIT_TEST( ElectronMaterial, getMacroscopicReactionCrossSection )
{
  // Test that the atomic excitation cross section can be returned
  double cross_section = material->getMacroscopicReactionCrossSection(
				 1.00000e-05,
				 MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.545329003693E+04, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
				 1.00000e+05,
				 MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.588134602166E+03, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
				   1.00000e-05,
				   MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.415377951846E+01, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
				   1.00000e+05,
				   MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 5.679677054824E+00, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
		   1.00000e-05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		   8.97540E-02,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.6350071826026E-04, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		   1.00000e+05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.060615028974E-01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
		  1.00000e-05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.096230095899E+05, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		  1.00000e+05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 5.296521123591E+02, 1e-12 );

  // Test that the cutoff elastic cross section can be returned
  double energy = 1.00000e-05;
  cross_section = material->getMacroscopicReactionCrossSection(
			    energy,
			    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.234825686582E+06,
                          1e-12 );

  energy = 1.00000e+05;
  cross_section = material->getMacroscopicReactionCrossSection(
			    energy,
			    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.566534386946E-04,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a electron can collide with the material
TEUCHOS_UNIT_TEST( ElectronMaterial, collideAnalogue )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setCell( 4 );

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 0.36; // select the elastic reaction
  fake_stream[2] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideAnalogue( electron, bank );

  TEST_EQUALITY_CONST( electron.getEnergy(), 1e-3 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.9874366113907, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a electron can collide with the material and survival bias
TEUCHOS_UNIT_TEST( ElectronMaterial, collideSurvivalBias )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setCell( 4 );

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 0.36; // select the elastic reaction
  fake_stream[2] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideSurvivalBias( electron, bank );

  TEST_EQUALITY_CONST( electron.getEnergy(), 1e-3 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.9874366113907, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getWeight(), 1.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &test_cross_sections_xml_directory,
                   "Directory where test cross_sections.xml file is located." );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  {
    // Assign the name of the cross_sections.xml file with path
    std::string cross_section_xml_file = test_cross_sections_xml_directory;
    cross_section_xml_file += "/cross_sections.xml";

    // Read in the xml file storing the cross section table info
    Teuchos::updateParametersFromXmlFile(
				 cross_section_xml_file,
				 Teuchos::inoutArg(cross_section_table_info) );

    std::unordered_set<std::string> atom_aliases;
    atom_aliases.insert( "Pb" );

    // Create the factories
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory>
      atomic_relaxation_model_factory(
				new MonteCarlo::AtomicRelaxationModelFactory );


    double upper_cutoff_angle_cosine = 1.0;
    unsigned hash_grid_bins = 100;

    MonteCarlo::ElectroatomFactory factory( test_cross_sections_xml_directory,
                                            cross_section_table_info,
                                            atom_aliases,
                                            atomic_relaxation_model_factory,
                                            hash_grid_bins,
                                            MonteCarlo::TWOBS_DISTRIBUTION,
                                            true,
                                            upper_cutoff_angle_cosine );

    std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
      atom_map;

    factory.createElectroatomMap( atom_map );

    // Assign the atom fractions and names
    Teuchos::Array<double> atom_fractions( 1 );
    Teuchos::Array<std::string> atom_names( 1 );

    atom_fractions[0] = -1.0; // weight fraction
    atom_names[0] = "Pb";

    // Create the test material
    material.reset( new MonteCarlo::ElectronMaterial( 0,
                                                      -1.0,
                                                      atom_map,
                                                      atom_fractions,
                                                      atom_names ) );
  }

  // Create the set of electroatom aliases
  electroatom_aliases.insert( "Pb" );

  // Create each electroatom in the set
  boost::unordered_set<std::string>::const_iterator electroatom_name =
    electroatom_aliases.begin();

  Teuchos::ParameterList table_info;

  table_info = cross_section_table_info.sublist( *electroatom_name );


  // Set the abs. path to the ace library file containing the desired table
  std::string ace_file_path = test_cross_sections_xml_directory + "/";

  ace_file_path +=
      table_info.get<std::string>("electroatomic_file_path");

  // Get the start line
  int electroatomic_file_start_line;

  electroatomic_file_start_line =
      table_info.get<int>( "electroatomic_file_start_line" );

  // Get the table name
  std::string electroatomic_table_name;

  electroatomic_table_name =
      table_info.get<std::string>( "electroatomic_table_name" );

  // Create the ACEFileHandler
  Data::ACEFileHandler ace_file_handler( ace_file_path,
					   electroatomic_table_name,
					   electroatomic_file_start_line,
					   1u );

  // Create the XSS data extractor
  xss_data_extractor.reset( new Data::XSSEPRDataExtractor(
					 ace_file_handler.getTableNXSArray(),
					 ace_file_handler.getTableJXSArray(),
					 ace_file_handler.getTableXSSArray() ) );


  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectronMaterial.cpp
//---------------------------------------------------------------------------//
