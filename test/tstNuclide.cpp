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
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "ACEFileHandler.hpp"
#include "XSSNeutronDataExtractor.hpp"
#include "Nuclide.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_basic_ace_file_name;
std::string test_basic_ace_table_name;
// std::string test_fission_ace_file_name;
// std::string test_ptable_ace_file_name;
// std::string test_fission_ptable_ace_file_name;

Teuchos::RCP<FACEMC::ACEFileHandler> ace_file_handler;

Teuchos::RCP<FACEMC::XSSNeutronDataExtractor> xss_data_extractor;

Teuchos::RCP<FACEMC::Nuclide> nuclide;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeNuclide()
{
  ace_file_handler.reset(new FACEMC::ACEFileHandler( test_basic_ace_file_name,
						     test_basic_ace_table_name,
						     1u ) );
  xss_data_extractor.reset(
   new FACEMC::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				        ace_file_handler->getTableJXSArray(),
				        ace_file_handler->getTableXSSArray()));

  nuclide.reset( new FACEMC::Nuclide( 
				 test_basic_ace_table_name,
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
  initializeNuclide();

  TEST_EQUALITY_CONST( nuclide->getName(), "1001.70c" );
}

//---------------------------------------------------------------------------//
// Check that the nuclide id can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getId )
{
  TEST_EQUALITY_CONST( nuclide->getId(), 100170u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide atomic number can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getAtomicNumber )
{
  TEST_EQUALITY_CONST( nuclide->getAtomicMassNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide atomic mass number can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getAtomicMassNumber )
{
  TEST_EQUALITY_CONST( nuclide->getAtomicMassNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide isomer number can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getIsomerNumber )
{
  TEST_EQUALITY_CONST( nuclide->getIsomerNumber(), 0u );
} 

//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getAtomicWeightRatio )
{
  TEST_EQUALITY_CONST( nuclide->getAtomicWeightRatio(), 0.999167 );
}

//---------------------------------------------------------------------------//
// Check that the temperature can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getTemperature )
{
  TEST_EQUALITY_CONST( nuclide->getTemperature(), 2.53010e-8 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getTotalCrossSection )
{
  double cross_section = nuclide->getTotalCrossSection( 1.0e-11 );

  TEST_EQUALITY_CONST( cross_section, 1.17724711e3 );

  cross_section = nuclide->getTotalCrossSection( 1.015625e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 1.168262615e3, 1e-15 );

  cross_section = nuclide->getTotalCrossSection( 1.03125e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 1.15927812e3, 1e-15 );

  cross_section = nuclide->getTotalCrossSection( 1.046875e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 1.15069229e3, 1e-9 );

  cross_section = nuclide->getTotalCrossSection( 1.0625e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 1.14210646e3 );

  cross_section = nuclide->getTotalCrossSection( 1.90e1 );

  TEST_FLOATING_EQUALITY( cross_section, 5.08805961e-1, 1e-9 );

  cross_section = nuclide->getTotalCrossSection( 1.925e1 );

  TEST_FLOATING_EQUALITY( cross_section, 5.02148202e-1, 1e-9 );

  cross_section = nuclide->getTotalCrossSection( 1.95e1 );

  TEST_FLOATING_EQUALITY( cross_section, 4.95490443e-1, 1e-9 );

  cross_section = nuclide->getTotalCrossSection( 1.975e1 );

  TEST_FLOATING_EQUALITY( cross_section, 4.891319335e-1, 1e-9 );

  cross_section = nuclide->getTotalCrossSection( 2.0e1 );

  TEST_FLOATING_EQUALITY( cross_section, 4.82773424e-1, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getAbsorptionCrossSection )
{
  double cross_section = nuclide->getAbsorptionCrossSection( 1.0e-11 );

  TEST_EQUALITY_CONST( cross_section, 1.670111e1 );

  cross_section = nuclide->getAbsorptionCrossSection( 1.015625e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 1.6573615e1, 1e-15 );

  cross_section = nuclide->getAbsorptionCrossSection( 1.03125e-11 );

  TEST_EQUALITY_CONST( cross_section, 1.644612e1 );

  cross_section = nuclide->getAbsorptionCrossSection( 1.046875e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 1.632429e1, 1e-15 );

  cross_section = nuclide->getAbsorptionCrossSection( 1.0625e-11 );

  TEST_EQUALITY_CONST( cross_section, 1.620246e1 );

  cross_section = nuclide->getAbsorptionCrossSection( 1.90e1 );

  TEST_EQUALITY_CONST( cross_section, 2.766095e-5 );

  cross_section = nuclide->getAbsorptionCrossSection( 1.925e1 );

  TEST_FLOATING_EQUALITY( cross_section, 2.755177e-5, 1e-15 );

  cross_section = nuclide->getAbsorptionCrossSection( 1.95e1 );

  TEST_EQUALITY_CONST( cross_section, 2.744259e-5 );

  cross_section = nuclide->getAbsorptionCrossSection( 1.975e1 );

  TEST_FLOATING_EQUALITY( cross_section, 2.7333065e-5, 1e-15 );

  cross_section = nuclide->getAbsorptionCrossSection( 2.0e1 );

  TEST_EQUALITY_CONST( cross_section, 2.722354e-5 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getSurvivalProbability )
{
  double survival_prob = nuclide->getSurvivalProbability( 1.0e-11 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.98581342025975, 1e-13 );

  survival_prob = nuclide->getSurvivalProbability( 1.03125e-11 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.98581348192787, 1e-13 );

  survival_prob = nuclide->getSurvivalProbability( 1.0625e-11 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.98581352915209, 1e-13 );

  survival_prob = nuclide->getSurvivalProbability( 1.90e1 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.99994563556224, 1e-13 );

  survival_prob = nuclide->getSurvivalProbability( 1.95e1 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.99994461529907, 1e-13  );

  survival_prob = nuclide->getSurvivalProbability( 2.0e1 );

  TEST_FLOATING_EQUALITY( survival_prob, 0.99994361011057, 1e-13 );
}

//---------------------------------------------------------------------------//
// Check that a reaction cross section can be returned
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, getReactionCrossSection )
{
  double cross_section = 
    nuclide->getReactionCrossSection( 1.0e-11, FACEMC::N__TOTAL_REACTION );

  TEST_EQUALITY_CONST( cross_section, 1.17724711e3 );

  cross_section = 
    nuclide->getReactionCrossSection( 2.0e1, FACEMC::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.82773424e-1, 1e-9 );
  
  cross_section = 
    nuclide->getReactionCrossSection( 1.0e-11, FACEMC::N__N_ELASTIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 1.160546e3 );

  cross_section = 
    nuclide->getReactionCrossSection( 2.0e1, FACEMC::N__N_ELASTIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 4.827462e-1 );

  cross_section =
    nuclide->getReactionCrossSection( 1.0e-11, FACEMC::N__GAMMA_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 1.670111e1 );

  cross_section =
    nuclide->getReactionCrossSection( 2.0e1, FACEMC::N__GAMMA_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 2.722354e-5 );

  cross_section =
    nuclide->getReactionCrossSection( 1.0e-11, FACEMC::N__TOTAL_D_PRODUCTION );
  
  TEST_EQUALITY_CONST( cross_section, 1.670111e1 );

  cross_section =
    nuclide->getReactionCrossSection( 2.0e1, FACEMC::N__TOTAL_D_PRODUCTION );
  
  TEST_EQUALITY_CONST( cross_section, 2.722354e-5 );

  cross_section =
    nuclide->getReactionCrossSection( 1.0e-11, FACEMC::N__DPA );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    nuclide->getReactionCrossSection( 2.0e1, FACEMC::N__DPA );
  
  TEST_EQUALITY_CONST( cross_section, 3.067696e-4 );

  cross_section = 
    nuclide->getReactionCrossSection( 1.0e-11, FACEMC::N__FISSION_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the a neutron can collide with a nuclide
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, collideAnalogue )
{
  FACEMC::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  FACEMC::ParticleBank bank;

  nuclide->collideAnalogue( neutron, bank );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  std::cout << neutron << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with a nuclide
TEUCHOS_UNIT_TEST( Nuclide_hydrogen, collideSurvivalBias)
{
  FACEMC::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.03125e-11 );
  neutron.setWeight( 1.0 );

  FACEMC::ParticleBank bank;

  nuclide->collideSurvivalBias( neutron, bank );

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

  clp.setOption( "test_basic_ace_file",
		 &test_basic_ace_file_name,
		 "Test basic ACE file name" );
  clp.setOption( "test_basic_ace_table",
		 &test_basic_ace_table_name,
		 "Test basic ACE table name in basic ACE file" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstNuclide.cpp
//---------------------------------------------------------------------------//
