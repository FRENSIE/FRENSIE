//---------------------------------------------------------------------------//
//!
//! \file   tstEnergyDependentNeutronMultiplicityReaction.cpp
//! \author Alex Robinson
//! \brief  Energy dependent neutron multiplicity reaction
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringDistributionFactory.hpp"
#include "MonteCarlo_EnergyDependentNeutronMultiplicityReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_ace_file_name;
std::string test_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;

Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;

Teuchos::RCP<MonteCarlo::NuclearReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeReaction()
{
  MonteCarlo::NeutronScatteringDistributionFactory 
    factory( test_ace_table_name,
	     ace_file_handler->getTableAtomicWeightRatio(),
	     xss_data_extractor->extractMTRBlock(),
	     xss_data_extractor->extractTYRBlock(),
	     xss_data_extractor->extractLANDBlock(),
	     xss_data_extractor->extractANDBlock(),
	     xss_data_extractor->extractLDLWBlock(),
	     xss_data_extractor->extractDLWBlock() );

  Teuchos::RCP<MonteCarlo::NeutronScatteringDistribution> scattering_dist;
  
  factory.createScatteringDistribution( MonteCarlo::N__ANYTHING_REACTION,
					scattering_dist );

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  Teuchos::ArrayView<const double> sig_block =
    xss_data_extractor->extractSIGBlock();

  unsigned threshold_index = (unsigned)sig_block[0];
  unsigned num_energies = (unsigned)sig_block[1];
  
  Teuchos::ArrayRCP<double> cross_section;
  cross_section.deepCopy( sig_block( 2, num_energies ) );

  Teuchos::ArrayView<const double> dlw_block = 
    xss_data_extractor->extractDLWBlock();

  Teuchos::ArrayView<const double> multiplicity_energy_grid = 
    dlw_block( 2, (unsigned)dlw_block[1] );

  Teuchos::ArrayView<const double> multiplicity = 
    dlw_block( 2 + (unsigned)dlw_block[1], (unsigned)dlw_block[1] );

  nuclear_reaction.reset( 
		        new MonteCarlo::EnergyDependentNeutronMultiplicityReaction(
				       MonteCarlo::N__ANYTHING_REACTION,
			               ace_file_handler->getTableTemperature(),
				       0.0,
				       multiplicity_energy_grid,
				       multiplicity,
				       threshold_index,
				       energy_grid,
				       cross_section,
				       scattering_dist ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of emitted neutrons can be returned
TEUCHOS_UNIT_TEST( EnergyDependentNeutronMultiplicityReaction,
		   getNumberOfEmittedNeutrons )
{
  unsigned number_of_emitted_neutrons = 
    nuclear_reaction->getNumberOfEmittedNeutrons( 1e-11 );

  TEST_EQUALITY_CONST( number_of_emitted_neutrons, 0.0 );

  number_of_emitted_neutrons = 
    nuclear_reaction->getNumberOfEmittedNeutrons( 30.0 );
  
  TEST_EQUALITY_CONST( number_of_emitted_neutrons, 0.0 );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.15;
  fake_stream[1] = 0.20;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  number_of_emitted_neutrons =
    nuclear_reaction->getNumberOfEmittedNeutrons( 150.0 );

  TEST_EQUALITY_CONST( number_of_emitted_neutrons, 1.0 );
  
  number_of_emitted_neutrons =
    nuclear_reaction->getNumberOfEmittedNeutrons( 150.0 );

  TEST_EQUALITY_CONST( number_of_emitted_neutrons, 2.0 );  
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv)
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test basic ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test basic ACE table name in basic ACE file" );

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

  // Initialize the ace file handler and data extractor
  ace_file_handler.reset(new Data::ACEFileHandler( test_ace_file_name,
						   test_ace_table_name,
						   1u ) );
  xss_data_extractor.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray()));

  // Initialize the reaction
  initializeReaction();

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
// end tstEnergyDependentNeutronMultiplicityReaction.cpp
//---------------------------------------------------------------------------//
