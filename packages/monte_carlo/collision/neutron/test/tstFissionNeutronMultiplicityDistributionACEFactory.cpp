//---------------------------------------------------------------------------//
//!
//! \file   tstFissionNeutronMultiplicityDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Fission neutron multiplicity distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestFissionNeutronMultiplicityDistributionACEFactory : public MonteCarlo::FissionNeutronMultiplicityDistributionACEFactory
{
public:
  TestFissionNeutronMultiplicityDistributionACEFactory(
			    const std::string& table_name,
			    const Teuchos::ArrayView<const double>& nu_block,
			    const Teuchos::ArrayView<const double>& dnu_block )
    : FissionNeutronMultiplicityDistributionACEFactory( table_name,
						     nu_block,
						     dnu_block )
  { /* ... */ }

  ~TestFissionNeutronMultiplicityDistributionACEFactory()
  { /* ... */ }

  using MonteCarlo::FissionNeutronMultiplicityDistributionACEFactory::doesPromptDistExist;
  using MonteCarlo::FissionNeutronMultiplicityDistributionACEFactory::doesDelayedDistExist;
  using MonteCarlo::FissionNeutronMultiplicityDistributionACEFactory::doesTotalDistExist;
  using MonteCarlo::FissionNeutronMultiplicityDistributionACEFactory::getPromptMultDist;
  using MonteCarlo::FissionNeutronMultiplicityDistributionACEFactory::getDelayedMultDist;
  using MonteCarlo::FissionNeutronMultiplicityDistributionACEFactory::getTotalMultDist;
};

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_u238_ace_file_name;
std::string test_u238_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;
Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;
Teuchos::RCP<TestFissionNeutronMultiplicityDistributionACEFactory>
multiplicity_dist_factory;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the prompt distribution can be found
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   doesPromptDistExist )
{
  TEST_ASSERT( multiplicity_dist_factory->doesPromptDistExist() );
}

//---------------------------------------------------------------------------//
// Check that the delayed distribution can be found
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   doesDelayedDistExist )
{
  TEST_ASSERT( multiplicity_dist_factory->doesDelayedDistExist() );
}

//---------------------------------------------------------------------------//
// Check that the total distribution can be found
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   doesTotalDistExist )
{
  TEST_ASSERT( multiplicity_dist_factory->doesTotalDistExist() );
}

//---------------------------------------------------------------------------//
// Check that the prompt distribution is valid
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   getPromptMultDist )
{
  const Teuchos::RCP<Utility::OneDDistribution>& prompt_dist =
    multiplicity_dist_factory->getPromptMultDist();

  TEST_ASSERT( !prompt_dist.is_null() );
  TEST_EQUALITY_CONST( prompt_dist->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the delayed distribution is valid
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   getDelayedMultDist )
{
  const Teuchos::RCP<Utility::OneDDistribution>& delayed_dist =
    multiplicity_dist_factory->getPromptMultDist();

  TEST_ASSERT( !delayed_dist.is_null() );
  TEST_EQUALITY_CONST( delayed_dist->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the total distribution is valid
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   getTotalMultDist )
{
  const Teuchos::RCP<Utility::OneDDistribution>& total_dist =
    multiplicity_dist_factory->getTotalMultDist();

  TEST_ASSERT( !total_dist.is_null() );
  TEST_EQUALITY_CONST( total_dist->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the FissionNeutronMultiplicityDistribution can be created
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   createDistribution )
{
  Teuchos::RCP<MonteCarlo::FissionNeutronMultiplicityDistribution> distribution;

  multiplicity_dist_factory->createDistribution( distribution );

  TEST_ASSERT( !distribution.is_null() );
  TEST_ASSERT( distribution->getAverageNumberOfEmittedNeutrons( 1.0 ) > 0.0 );
  TEST_ASSERT( distribution->getAverageNumberOfEmittedNeutrons( 1.0 ) < 4.0 );
  TEST_ASSERT( distribution->getAverageNumberOfPromptNeutrons( 1.0 ) > 0.0 );
  TEST_ASSERT( distribution->getAverageNumberOfPromptNeutrons( 1.0 ) < 4.0 );
  TEST_ASSERT( distribution->getAverageNumberOfDelayedNeutrons( 1.0 ) > 0.0 );
  TEST_ASSERT( distribution->getAverageNumberOfDelayedNeutrons( 1.0 ) < 1.0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_u238_ace_file",
		 &test_u238_ace_file_name,
		 "Test U238 ACE file name" );
  clp.setOption( "test_u238_ace_table",
		 &test_u238_ace_table_name,
		 "Test U238 ACE table name in basic ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize ace file handler, data extractor and multiplicity factory
  ace_file_handler.reset( new Data::ACEFileHandler( test_u238_ace_file_name,
						    test_u238_ace_table_name,
						    1u ) );

  xss_data_extractor.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  multiplicity_dist_factory.reset(
		    new TestFissionNeutronMultiplicityDistributionACEFactory(
				     ace_file_handler->getTableName(),
				     xss_data_extractor->extractNUBlock(),
				     xss_data_extractor->extractDNUBlock() ) );

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
// end tstFissionNeutronMultiplicityDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
