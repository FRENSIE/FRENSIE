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

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectronMaterial> material;

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
  double cross_section = 
    material->getMacroscopicTotalCrossSection( 1.00000e-05 );

  TEST_FLOATING_EQUALITY( cross_section, 7.641204418336E+06, 1e-12 );

  cross_section = 
    material->getMacroscopicTotalCrossSection( 1.00000e+05 );

  TEST_FLOATING_EQUALITY( cross_section, 8.269992326372E+03, 1e-12 );
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

  // Test that the hard elastic cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
			    1.00000e-05,
			    MonteCarlo::ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.234825686582E+06, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 
			    1.00000e+05,
			    MonteCarlo::ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.566534386946E-04, 1e-12 );
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
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 0.36; // select the elastic reaction
  fake_stream[2] = 9.9990E-01; // choose angle from distribution
  fake_stream[3] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideAnalogue( electron, bank );

  TEST_EQUALITY_CONST( electron.getEnergy(), 1e-3 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.874339332031E-01, 1e-12 );

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
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 0.36; // select the elastic reaction
  fake_stream[2] = 9.9990E-01; // sample angle from distribution
  fake_stream[3] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideSurvivalBias( electron, bank );
  
  TEST_EQUALITY_CONST( electron.getEnergy(), 1e-3 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getWeight(), 1.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_cross_sections_xml_directory;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_cross_sections_xml_directory",
		 &test_cross_sections_xml_directory,
		 "Directory where test cross_sections.xml file is located." );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  {
    // Assign the name of the cross_sections.xml file with path
    std::string cross_section_xml_file = test_cross_sections_xml_directory;
    cross_section_xml_file += "/cross_sections.xml";
    
    // Read in the xml file storing the cross section table info
    Teuchos::ParameterList cross_section_table_info;
    Teuchos::updateParametersFromXmlFile(
				 cross_section_xml_file,
				 Teuchos::inoutArg(cross_section_table_info) );

    std::unordered_set<std::string> atom_aliases;
    atom_aliases.insert( "Pb" );

    // Create the factories
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory> 
      atomic_relaxation_model_factory(
				new MonteCarlo::AtomicRelaxationModelFactory );
    
    MonteCarlo::ElectroatomFactory factory( test_cross_sections_xml_directory,
                                            cross_section_table_info,
                                            atom_aliases,
                                            atomic_relaxation_model_factory,
                                            MonteCarlo::TWOBS_DISTRIBUTION,
                                            true);

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
// end tstElectronMaterial.cpp
//---------------------------------------------------------------------------//
