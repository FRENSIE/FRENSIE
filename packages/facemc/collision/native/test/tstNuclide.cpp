//---------------------------------------------------------------------------//
//!
//! \file   tstNuclide.cpp
//! \author Alex Robinson
//! \brief  Nuclide class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Facemc_Nuclide.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_h1_ace_file_name;
std::string test_h1_ace_table_name;
std::string test_o16_ace_file_name;
std::string test_o16_ace_table_name;
// std::string test_fission_ace_file_name;
// std::string test_ptable_ace_file_name;
// std::string test_fission_ptable_ace_file_name;

Teuchos::RCP<Facemc::Nuclide> h1_nuclide;
Teuchos::RCP<Facemc::Nuclide> o16_nuclide;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeNuclide( Teuchos::RCP<Facemc::Nuclide>& nuclide,
			const std::string& ace_file_name,
			const std::string& ace_table_name )
{
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;
  ace_file_handler.reset(new Data::ACEFileHandler( ace_file_name,
						   ace_table_name,
						   1u ) );

  Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;
  
  xss_data_extractor.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray()));

  nuclide.reset( new Facemc::Nuclide( 
				 ace_table_name,
				 1u,
				 1u,
				 0u,
				 ace_file_handler->getTableAtomicWeightRatio(),
				 ace_file_handler->getTableTemperature(),
				 *xss_data_extractor ) );
}
  
//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the nuclide name can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getName )
{
  TEST_EQUALITY_CONST( h1_nuclide->getName(), "1001.70c" );
}

//---------------------------------------------------------------------------//
// Check that the nuclide id can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getId )
{
  TEST_EQUALITY_CONST( h1_nuclide->getId(), 100170u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide atomic number can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getAtomicNumber )
{
  TEST_EQUALITY_CONST( h1_nuclide->getAtomicMassNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide atomic mass number can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getAtomicMassNumber )
{
  TEST_EQUALITY_CONST( h1_nuclide->getAtomicMassNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide isomer number can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getIsomerNumber )
{
  TEST_EQUALITY_CONST( h1_nuclide->getIsomerNumber(), 0u );
} 

//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getAtomicWeightRatio )
{
  TEST_EQUALITY_CONST( h1_nuclide->getAtomicWeightRatio(), 0.999167 );
}

//---------------------------------------------------------------------------//
// Check that the temperature can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getTemperature )
{
  TEST_EQUALITY_CONST( h1_nuclide->getTemperature(), 2.53010e-8 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getTotalCrossSection )
{
  double cross_section = h1_nuclide->getTotalCrossSection( 1.0e-11 );

  TEST_EQUALITY_CONST( cross_section, 1.17724711e3 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.015625e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 1.168262615e3, 1e-15 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.03125e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 1.15927812e3, 1e-15 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.046875e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 1.15069229e3, 1e-9 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.0625e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 1.14210646e3 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.90e1 );

  TEST_FLOATING_EQUALITY( cross_section, 5.08805961e-1, 1e-9 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.925e1 );

  TEST_FLOATING_EQUALITY( cross_section, 5.02148202e-1, 1e-9 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.95e1 );

  TEST_FLOATING_EQUALITY( cross_section, 4.95490443e-1, 1e-9 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.975e1 );

  TEST_FLOATING_EQUALITY( cross_section, 4.891319335e-1, 1e-9 );

  cross_section = h1_nuclide->getTotalCrossSection( 2.0e1 );

  TEST_FLOATING_EQUALITY( cross_section, 4.82773424e-1, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getAbsorptionCrossSection )
{
  double cross_section = h1_nuclide->getAbsorptionCrossSection(1.0e-11 );

  TEST_EQUALITY_CONST( cross_section, 1.670111e1 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.015625e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 1.6573615e1, 1e-15 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.03125e-11 );

  TEST_EQUALITY_CONST( cross_section, 1.644612e1 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.046875e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 1.632429e1, 1e-15 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.0625e-11 );

  TEST_EQUALITY_CONST( cross_section, 1.620246e1 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.90e1 );

  TEST_EQUALITY_CONST( cross_section, 2.766095e-5 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.925e1 );

  TEST_FLOATING_EQUALITY( cross_section, 2.755177e-5, 1e-15 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.95e1 );

  TEST_EQUALITY_CONST( cross_section, 2.744259e-5 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.975e1 );

  TEST_FLOATING_EQUALITY( cross_section, 2.7333065e-5, 1e-15 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 2.0e1 );

  TEST_EQUALITY_CONST( cross_section, 2.722354e-5 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getSurvivalProbability )
{
  double survival_prob = h1_nuclide->getSurvivalProbability( 1.0e-11 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.98581342025975, 1e-13 );

  survival_prob = h1_nuclide->getSurvivalProbability( 1.03125e-11 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.98581348192787, 1e-13 );

  survival_prob = h1_nuclide->getSurvivalProbability( 1.0625e-11 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.98581352915209, 1e-13 );

  survival_prob = h1_nuclide->getSurvivalProbability( 1.90e1 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.99994563556224, 1e-13 );

  survival_prob = h1_nuclide->getSurvivalProbability( 1.95e1 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.99994461529907, 1e-13  );

  survival_prob = h1_nuclide->getSurvivalProbability( 2.0e1 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.99994361011057, 1e-13 );
}

//---------------------------------------------------------------------------//
// Check that a reaction cross section can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getReactionCrossSection )
{
  double cross_section = 
    h1_nuclide->getReactionCrossSection( 1.0e-11, Facemc::N__TOTAL_REACTION );

  TEST_EQUALITY_CONST( cross_section, 1.17724711e3 );

  cross_section = 
    h1_nuclide->getReactionCrossSection( 2.0e1, Facemc::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.82773424e-1, 1e-9 );
  
  cross_section = 
    h1_nuclide->getReactionCrossSection( 1.0e-11, Facemc::N__N_ELASTIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 1.160546e3 );

  cross_section = 
    h1_nuclide->getReactionCrossSection( 2.0e1, Facemc::N__N_ELASTIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 4.827462e-1 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 1.0e-11, Facemc::N__GAMMA_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 1.670111e1 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 2.0e1, Facemc::N__GAMMA_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 2.722354e-5 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 1.0e-11, Facemc::N__TOTAL_D_PRODUCTION );
  
  TEST_EQUALITY_CONST( cross_section, 1.670111e1 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 2.0e1, Facemc::N__TOTAL_D_PRODUCTION );
  
  TEST_EQUALITY_CONST( cross_section, 2.722354e-5 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 1.0e-11, Facemc::N__DPA );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 2.0e1, Facemc::N__DPA );
  
  TEST_EQUALITY_CONST( cross_section, 3.067696e-4 );

  cross_section = 
    h1_nuclide->getReactionCrossSection( 1.0e-11, Facemc::N__FISSION_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the a neutron can collide with a nuclide
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, collideAnalogue )
{
  Facemc::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  Facemc::ParticleBank bank;

  h1_nuclide->collideAnalogue( neutron, bank );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  std::cout << neutron << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with a nuclide
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, collideSurvivalBias)
{
  Facemc::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.03125e-11 );
  neutron.setWeight( 1.0 );

  Facemc::ParticleBank bank;

  h1_nuclide->collideSurvivalBias( neutron, bank );

  TEST_FLOATING_EQUALITY( neutron.getWeight(), 0.98581348192787, 1e-14 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  std::cout << neutron << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with a nuclide
TEUCHOS_UNIT_TEST( Nuclide_oxygen, collideSurvivalBias)
{
  double energy;
  for( unsigned i = 0; i < 1e6; ++i )
  {
    // energy = exp(log(1.01e-11) + ((log(1.0)-log(1.01e-11))/1e6)*i);
    // std::cout << energy << " " << o16_nuclide->getTotalCrossSection( energy )
    // 	      << " " << o16_nuclide->getAbsorptionCrossSection( energy )
    // 	      << " " << o16_nuclide->getReactionCrossSection( energy, Facemc::N__ALPHA_REACTION )
    // 	      << " " << o16_nuclide->getReactionCrossSection( energy, Facemc::N__N_ELASTIC_REACTION )
    // 	      << " " << o16_nuclide->getReactionCrossSection( energy, Facemc::N__N_EXCITED_STATE_1_REACTION )
    // 	      << " " << o16_nuclide->getReactionCrossSection( energy, Facemc::N__N_EXCITED_STATE_2_REACTION )
    // 	      << std::endl;
  }
  
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h1_ace_file",
		 &test_h1_ace_file_name,
		 "Test h1 ACE file name" );
  clp.setOption( "test_h1_ace_table",
		 &test_h1_ace_table_name,
		 "Test h1 ACE table name in h1 ACE file" );

  clp.setOption( "test_o16_ace_file",
		 &test_o16_ace_file_name,
		 "Test o16 ACE file name" );
  clp.setOption( "test_o16_ace_table",
		 &test_o16_ace_table_name,
		 "Test o16 ACE table name in o16 ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize nuclear reaction factories
  initializeNuclide( h1_nuclide,
		     test_h1_ace_file_name,
		     test_h1_ace_table_name );

  initializeNuclide( o16_nuclide,
		     test_o16_ace_file_name,
		     test_o16_ace_table_name );

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
// end tstNuclide.cpp
//---------------------------------------------------------------------------//
