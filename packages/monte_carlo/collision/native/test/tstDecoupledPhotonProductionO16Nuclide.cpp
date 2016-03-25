//---------------------------------------------------------------------------//
//!
//! \file   testDecoupledPhotonProductionO16Nuclide.cpp
//! \author Eli Moll
//! \brief  Decoupled photon production nuclide class unit tests for O16
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionNuclide.hpp"
#include "MonteCarlo_Nuclide.hpp"
#include "MonteCarlo_DecoupledPhotonProductionReactionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_o16_ace_file_name;
std::string test_o16_ace_table_name;

Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionNuclide> o16_nuclide;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeDecoupledPhotonProductionNuclide( Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionNuclide>& nuclide,
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

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  MonteCarlo::DecoupledPhotonProductionReactionACEFactory reaction_factory( 
				 ace_table_name,
				 ace_file_handler->getTableAtomicWeightRatio(),
				 ace_file_handler->getTableTemperature(),
				 energy_grid,
				 *xss_data_extractor );
  
  // Populate the photon production reactions
  MonteCarlo::DecoupledPhotonProductionNuclide::PhotonProductionReactionMap 
                                         standard_photon_production_reactions;
  reaction_factory.createPhotonProductionReactions( 
                                       standard_photon_production_reactions );
  
  MonteCarlo::Nuclide::ReactionMap standard_scattering_reactions;
  reaction_factory.createScatteringReactions( standard_scattering_reactions );
  reaction_factory.createFissionReactions( standard_scattering_reactions );

  MonteCarlo::Nuclide::ReactionMap standard_absorption_reactions;
  reaction_factory.createAbsorptionReactions( standard_absorption_reactions );
  
  nuclide.reset( new MonteCarlo::DecoupledPhotonProductionNuclide( 
			 ace_table_name,
			 8u,
			 16u,
			 0u,
			 ace_file_handler->getTableAtomicWeightRatio(),
			 ace_file_handler->getTableTemperature(),
			 energy_grid,
			 standard_scattering_reactions,
			 standard_absorption_reactions,
			 standard_photon_production_reactions ) );
}
  
//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the nuclide name can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionNuclide_O16, getName )
{
  TEST_EQUALITY_CONST( o16_nuclide->getName(), "8016.70c" );
}

//---------------------------------------------------------------------------//
// Check that the nuclide id can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionNuclide_O16, getId )
{
  TEST_EQUALITY_CONST( o16_nuclide->getId(), 801670u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide atomic number can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionNuclide_O16, getAtomicNumber )
{
  TEST_EQUALITY_CONST( o16_nuclide->getAtomicNumber(), 8u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide atomic mass number can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionNuclide_O16, getAtomicMassNumber )
{
  TEST_EQUALITY_CONST( o16_nuclide->getAtomicMassNumber(), 16u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide isomer number can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionNuclide_O16, getIsomerNumber )
{
  TEST_EQUALITY_CONST( o16_nuclide->getIsomerNumber(), 0u );
} 

//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionNuclide_O16, getAtomicWeightRatio )
{
  TEST_EQUALITY_CONST( o16_nuclide->getAtomicWeightRatio(), 
                                                    1.58575099999999996e+01 );
}

//---------------------------------------------------------------------------//
// Check that the temperature can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionNuclide_O16, getTemperature )
{
  TEST_EQUALITY_CONST( o16_nuclide->getTemperature(), 2.53010e-8 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionNuclide_O16, getTotalCrossSection )
{
  double cross_section = o16_nuclide->getTotalCrossSection( 1.0e-11 );

  TEST_FLOATING_EQUALITY( cross_section, 5.50173975000E+01, 1e-9 );

  cross_section = o16_nuclide->getTotalCrossSection( 1.5e2 );

  TEST_FLOATING_EQUALITY( cross_section, 4.43000000000E-01, 1e-9 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

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

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  initializeDecoupledPhotonProductionNuclide( o16_nuclide,
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
// end tstDecoupledPhotonProductionNuclide.cpp
//---------------------------------------------------------------------------//
