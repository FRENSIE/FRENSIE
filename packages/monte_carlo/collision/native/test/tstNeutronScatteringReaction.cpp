//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronScatteringReaction.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NeutronScatteringReaction.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_basic_ace_file_name;
std::string test_basic_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;

Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;

Teuchos::RCP<MonteCarlo::NuclearReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeReaction()
{
  MonteCarlo::NeutronNuclearScatteringDistributionACEFactory
    factory( test_basic_ace_table_name,
	     ace_file_handler->getTableAtomicWeightRatio(),
	     *xss_data_extractor );

  Teuchos::RCP<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > scattering_dist;

  factory.createScatteringDistribution( MonteCarlo::N__N_ELASTIC_REACTION,
					scattering_dist );

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  Teuchos::ArrayRCP<double> cross_section;
  cross_section.deepCopy( xss_data_extractor->extractElasticCrossSection() );

  nuclear_reaction.reset( new MonteCarlo::NeutronScatteringReaction(
				       MonteCarlo::N__N_ELASTIC_REACTION,
			               ace_file_handler->getTableTemperature(),
				       0.0,
				       1u,
				       0u,
				       energy_grid,
				       cross_section,
				       scattering_dist ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of emitted neutrons can be returned
TEUCHOS_UNIT_TEST( NeutronScatteringReaction_elastic,
		   getNumberOfEmittedNeutrons )
{
  TEST_EQUALITY_CONST( nuclear_reaction->getNumberOfEmittedNeutrons( 0.0 ), 1);
}

//---------------------------------------------------------------------------//
// Check that the reaction can be simulated
TEUCHOS_UNIT_TEST( NeutronScatteringReaction_elastic,
		   react )
{
  MonteCarlo::ParticleBank bank;

  {
    Teuchos::RCP<MonteCarlo::NeutronState> neutron( new MonteCarlo::NeutronState(0ull) );

    neutron->setDirection( 0.0, 0.0, 1.0 );
    neutron->setEnergy( 1.0 );

    bank.push( neutron );
  }

  nuclear_reaction->react( dynamic_cast<MonteCarlo::NeutronState&>(bank.top()),
			   bank );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  std::cout << std::endl << std::endl << bank.top() << std::endl;
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
  ace_file_handler.reset(new Data::ACEFileHandler( test_basic_ace_file_name,
						   test_basic_ace_table_name,
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
// end tstNeutronScatteringReaction.cpp
//---------------------------------------------------------------------------//

