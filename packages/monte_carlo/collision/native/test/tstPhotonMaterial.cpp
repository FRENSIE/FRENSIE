//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonMaterial.cpp
//! \author Alex Robinson
//! \brief  Photon material class unit tests
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
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_PhotonMaterial.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotonMaterial> material;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
TEUCHOS_UNIT_TEST( PhotonMaterial, getId )
{
  TEST_EQUALITY_CONST( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
TEUCHOS_UNIT_TEST( PhotonMaterial, getNumberDensity )
{
  TEST_FLOATING_EQUALITY( material->getNumberDensity(),
			  2.9064395906311e-3,
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
TEUCHOS_UNIT_TEST( PhotonMaterial, getMacroscopicTotalCrossSection )
{
  double cross_section = 
    material->getMacroscopicTotalCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  cross_section = 
    material->getMacroscopicTotalCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic absorption cross section can be returned
TEUCHOS_UNIT_TEST( PhotonMaterial, getMacroscopicAbsorptionCrossSection )
{
  double cross_section =
    material->getMacroscopicAbsorptionCrossSection(exp( -1.381551055796E+01 ));
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
  
  cross_section = 
    material->getMacroscopicAbsorptionCrossSection(exp( -1.214969212306E+01 ));
  
  TEST_FLOATING_EQUALITY( cross_section, 85114.18059425855, 1e-12 );

  cross_section = 
    material->getMacroscopicAbsorptionCrossSection(exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 4.138700272111011e-08, 1e-11 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( PhotonMaterial, getSurvivalProbability )
{
  double survival_prob = 
    material->getSurvivalProbability( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( survival_prob, 1.0, 1e-12 );

  survival_prob = 
    material->getSurvivalProbability( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( survival_prob, 0.9999996542464503, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic cross section for a specific reaction can be ret
TEUCHOS_UNIT_TEST( PhotonMaterial, getMacroscopicReactionCrossSection )
{
  // Test that the incoherent cross section can be returned
  double cross_section = material->getMacroscopicReactionCrossSection(
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.460222195795113e-09, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.060877396028078e-06, 1e-12 );

  // Test that the coherent cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
				   exp(-1.381551055796E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.8233859760860873e-05, 1e-12 );
				      
  cross_section = material->getMacroscopicReactionCrossSection(
				   exp( 1.151292546497E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.712301051729535e-13, 1e-12 );

  // Test that the K subshell photoelectric cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
		   exp( -1.381551055796E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		   exp( -2.427128314806E+00 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 5.684476918092442, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		   exp( 1.151292546497E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 3.4075097760409515e-08, 1e-12 );

  // Test that the P3 subshell photoelectric cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
		  exp( -1.381551055796E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		  exp( -1.214969212306E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 85114.18059425855, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection(
		  exp( 1.151292546497E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.5612230905027824e-13, 1e-12 );

  // Test that the pair production cross section can be returned
  cross_section = material->getMacroscopicReactionCrossSection(
			    exp( -1.381551055796E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 
			    exp( 2.480967890857E-02 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.7562829707526906e-09, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 
			    exp( 1.151292546497E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.11969677359280363, 1e-12 );

  // Test that there is not (gamma,total) reaction
  cross_section = material->getMacroscopicReactionCrossSection(
					    1e-3,
					    MonteCarlo::GAMMA__TOTAL_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicReactionCrossSection(
					   20.0,
					   MonteCarlo::GAMMA__TOTAL_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a photon can collide with the material
TEUCHOS_UNIT_TEST( PhotonMaterial, collideAnalogue )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 0.9; // select the incoherent reaction
  fake_stream[2] = 0.001; // sample from first term of koblinger's method
  fake_stream[3] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[4] = 0.5; // accept x in scattering function rejection loop
  fake_stream[5] = 0.005; // select first shell for collision - old
  fake_stream[6] = 0.005; // select first shell for collision - endf
  fake_stream[7] = 6.427713151861e-01; // select pz = 40.0
  fake_stream[8] = 0.25; // select energy loss

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideAnalogue( photon, bank );
  std::cout.precision( 18 );
  std::cout << photon.getEnergy() << std::endl;
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a photon can collide with the material and survival bias
TEUCHOS_UNIT_TEST( PhotonMaterial, collideSurvivalBias )
{
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 0.9; // select the incoherent reaction
  fake_stream[2] = 0.001; // sample from first term of koblinger's method
  fake_stream[3] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[4] = 0.5; // accept x in scattering function rejection loop
  fake_stream[5] = 0.005; // select first shell for collision - old
  fake_stream[6] = 0.005; // select first shell for collision - endf
  fake_stream[7] = 6.427713151861e-01; // select pz = 40.0
  fake_stream[8] = 0.25; // select energy loss

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  material->collideSurvivalBias( photon, bank );
  
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getWeight(), 0.99623491442141220986, 1e-12 );

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
    
    MonteCarlo::PhotoatomFactory factory( 
		 test_cross_sections_xml_directory,
		 cross_section_table_info,
		 atom_aliases,
		 atomic_relaxation_model_factory,
		 1000,
		 MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		 3.0,
		 false,
		 true );

    std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> >
      atom_map;

    factory.createPhotoatomMap( atom_map );

    // Assign the atom fractions and names
    Teuchos::Array<double> atom_fractions( 1 );
    Teuchos::Array<std::string> atom_names( 1 );

    atom_fractions[0] = -1.0; // weight fraction
    atom_names[0] = "Pb";

    // Create the test material
    material.reset( new MonteCarlo::PhotonMaterial( 0,
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
// end tstPhotonMaterial.cpp
//---------------------------------------------------------------------------//
