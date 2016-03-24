//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronMaterial.cpp
//! \author Alex Robinson
//! \brief  Neutron material class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_NeutronMaterial.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_cross_sections_xml_directory;

Teuchos::RCP<MonteCarlo::NeutronMaterial> material;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeSolidHydrogen()
{
  // Assign the name of the cross_sections.xml file with path
  std::string cross_section_xml_file = test_cross_sections_xml_directory;
  cross_section_xml_file += "/cross_sections.xml";

  // Read in the xml file storing the cross section table information 
  Teuchos::ParameterList cross_section_table_info;
  Teuchos::updateParametersFromXmlFile( 
			         cross_section_xml_file,
			         Teuchos::inoutArg(cross_section_table_info) );
  
  std::unordered_set<std::string> nuclide_aliases;
  nuclide_aliases.insert( "H-1_293.6K" );

  MonteCarlo::NuclideFactory nuclide_factory(test_cross_sections_xml_directory,
					     cross_section_table_info,
					     nuclide_aliases,
					     false,
					     false );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Nuclide> > 
    nuclide_map;

  nuclide_factory.createNuclideMap( nuclide_map );

  Teuchos::Array<double> nuclide_fractions( 1 );
  Teuchos::Array<std::string> nuclide_names( 1 );

  nuclide_fractions[0] = -1.0; // weight fraction
  nuclide_names[0] = "H-1_293.6K";
  
  material.reset( new MonteCarlo::NeutronMaterial( 0,
					       -1.0, // mass density (g/cm^3)
					       nuclide_map,
					       nuclide_fractions,
					       nuclide_names ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
TEUCHOS_UNIT_TEST( NeutronMaterial_hydrogen, getId )
{
  initializeSolidHydrogen();
  
  TEST_EQUALITY_CONST( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
TEUCHOS_UNIT_TEST( NeutronMaterial_hydrogen, getNumberDensity )
{
  TEST_FLOATING_EQUALITY(material->getNumberDensity(), 0.5975385703365, 1e-13);
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned 
TEUCHOS_UNIT_TEST( NeutronMaterial_hydrogen, getMacroscopicTotalCrossSection )
{
  double cross_section = material->getMacroscopicTotalCrossSection( 1.0e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  cross_section = material->getMacroscopicTotalCrossSection( 2.0e1 );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic absorption cross section can be returned
TEUCHOS_UNIT_TEST( NeutronMaterial_hydrogen, 
		   getMacroscopicAbsorptionCrossSection )
{
  double cross_section = 
    material->getMacroscopicAbsorptionCrossSection( 1.0e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 2.0e1 );

  TEST_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( NeutronMaterial_hydrogen, getSurvivalProbability )
{
  double survival_prob = material->getSurvivalProbability( 1.0e-11 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.98581342025975, 1e-13 );

  survival_prob = material->getSurvivalProbability( 2.0e1 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.99994361011057, 1e-13 );
}

//---------------------------------------------------------------------------//
// Check that a reaction cross section can be returned
TEUCHOS_UNIT_TEST( NeutronMaterial_hydrogen, 
		   getMacroscopicReationCrossSection )
{
  double cross_section = 
    material->getMacroscopicReactionCrossSection( 1.0e-11, 
						  MonteCarlo::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection( 
						   2.0e1, 
						   MonteCarlo::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  cross_section = material->getMacroscopicReactionCrossSection( 
					       1.0e-11,
					       MonteCarlo::N__N_ELASTIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 693.47099764974, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection( 
					       2.0e1,
					       MonteCarlo::N__N_ELASTIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.28845947418338, 1e-13 );
  
  cross_section = material->getMacroscopicReactionCrossSection( 
					           1.0e-11,
					           MonteCarlo::N__GAMMA_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection( 
					           2.0e1,
					           MonteCarlo::N__GAMMA_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection( 
					       1.0e-11,
					       MonteCarlo::N__TOTAL_D_PRODUCTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection( 
					       2.0e1,
					       MonteCarlo::N__TOTAL_D_PRODUCTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );

  cross_section = material->getMacroscopicReactionCrossSection( 
					                      1.0e-11,
					                      MonteCarlo::N__DPA );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );

  cross_section = material->getMacroscopicReactionCrossSection( 
					                      2.0e1,
					                      MonteCarlo::N__DPA );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.833066682067e-4, 1e-13 );
  
  cross_section = material->getMacroscopicReactionCrossSection( 
					         1.0e-11,
					         MonteCarlo::N__FISSION_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with a material
TEUCHOS_UNIT_TEST( NeutronMaterial_hydrogen, collideAnalogue )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  material->collideAnalogue( neutron, bank );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  std::cout << neutron << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with a material
TEUCHOS_UNIT_TEST( NeutronMaterial_hydrogen, collideSurvivalBias )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.03125e-11 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  material->collideSurvivalBias( neutron, bank );

  TEST_FLOATING_EQUALITY( neutron.getWeight(), 0.98581348192787, 1e-14 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  std::cout << neutron << std::endl;
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_cross_sections_xml_directory",
		 &test_cross_sections_xml_directory,
		 "Test cross_sections.xml file name" );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstNeutronMaterial.cpp
//---------------------------------------------------------------------------//
