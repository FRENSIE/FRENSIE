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

// FRENSIE Includes
#include "MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestFissionNeutronMultiplicityDistributionACEFactory : public MonteCarlo::FissionNeutronMultiplicityDistributionACEFactory
{
public:
  TestFissionNeutronMultiplicityDistributionACEFactory(
			    const std::string& table_name,
			    const Utility::ArrayView<const double>& nu_block,
			    const Utility::ArrayView<const double>& dnu_block )
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

std::shared_ptr<const Data::XSSNeutronDataExtractor> xss_data_extractor;
std::shared_ptr<const TestFissionNeutronMultiplicityDistributionACEFactory>
multiplicity_dist_factory;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the prompt distribution can be found
FRENSIE_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   doesPromptDistExist )
{
  FRENSIE_CHECK( multiplicity_dist_factory->doesPromptDistExist() );
}

//---------------------------------------------------------------------------//
// Check that the delayed distribution can be found
FRENSIE_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   doesDelayedDistExist )
{
  FRENSIE_CHECK( multiplicity_dist_factory->doesDelayedDistExist() );
}

//---------------------------------------------------------------------------//
// Check that the total distribution can be found
FRENSIE_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   doesTotalDistExist )
{
  FRENSIE_CHECK( multiplicity_dist_factory->doesTotalDistExist() );
}

//---------------------------------------------------------------------------//
// Check that the prompt distribution is valid
FRENSIE_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   getPromptMultDist )
{
  const std::shared_ptr<const Utility::UnivariateDistribution>& prompt_dist =
    multiplicity_dist_factory->getPromptMultDist();

  FRENSIE_CHECK( prompt_dist.get() != NULL );
  FRENSIE_CHECK_EQUAL( prompt_dist->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the delayed distribution is valid
FRENSIE_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   getDelayedMultDist )
{
  const std::shared_ptr<const Utility::UnivariateDistribution>& delayed_dist =
    multiplicity_dist_factory->getPromptMultDist();

  FRENSIE_CHECK( delayed_dist.get() != NULL );
  FRENSIE_CHECK_EQUAL( delayed_dist->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the total distribution is valid
FRENSIE_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   getTotalMultDist )
{
  const std::shared_ptr<const Utility::UnivariateDistribution>& total_dist =
    multiplicity_dist_factory->getTotalMultDist();

  FRENSIE_CHECK( total_dist.get() != NULL );
  FRENSIE_CHECK_EQUAL( total_dist->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the FissionNeutronMultiplicityDistribution can be created
FRENSIE_UNIT_TEST( FissionNeutronMultiplicityDistributionACEFactory,
		   createDistribution )
{
  std::shared_ptr<const MonteCarlo::FissionNeutronMultiplicityDistribution>
    distribution;

  multiplicity_dist_factory->createDistribution( distribution );

  FRENSIE_CHECK( distribution.get() != NULL );
  FRENSIE_CHECK( distribution->getAverageNumberOfEmittedNeutrons( 1.0 ) > 0.0 );
  FRENSIE_CHECK( distribution->getAverageNumberOfEmittedNeutrons( 1.0 ) < 4.0 );
  FRENSIE_CHECK( distribution->getAverageNumberOfPromptNeutrons( 1.0 ) > 0.0 );
  FRENSIE_CHECK( distribution->getAverageNumberOfPromptNeutrons( 1.0 ) < 4.0 );
  FRENSIE_CHECK( distribution->getAverageNumberOfDelayedNeutrons( 1.0 ) > 0.0 );
  FRENSIE_CHECK( distribution->getAverageNumberOfDelayedNeutrons( 1.0 ) < 1.0 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_u238_ace_file_name;
unsigned test_u238_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_u238_ace_file",
                                        test_u238_ace_file_name, "",
                                        "Test U238 ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_u238_ace_file_start_line",
                                        test_u238_ace_file_start_line, 1,
                                        "Test U238 ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize ace file handler, data extractor and multiplicity factory
  std::unique_ptr<Data::ACEFileHandler>
    ace_file_handler( new Data::ACEFileHandler( test_u238_ace_file_name,
                                                "92238.70c",
                                                test_u238_ace_file_start_line ) );

  xss_data_extractor.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  multiplicity_dist_factory.reset(
		    new TestFissionNeutronMultiplicityDistributionACEFactory(
				     ace_file_handler->getTableName(),
				     xss_data_extractor->extractNUBlock(),
				     xss_data_extractor->extractDNUBlock() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFissionNeutronMultiplicityDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
