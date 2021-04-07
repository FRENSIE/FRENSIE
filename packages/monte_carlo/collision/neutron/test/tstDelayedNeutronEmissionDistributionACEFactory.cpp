//---------------------------------------------------------------------------//
//!
//! \file   tstDelayedNeutronEmissionDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Delayed neutron emission distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestDelayedNeutronEmissionDistributionACEFactory : public MonteCarlo::DelayedNeutronEmissionDistributionACEFactory
{
public:
  TestDelayedNeutronEmissionDistributionACEFactory(
			   const std::string& table_name,
			   const double atomic_weight_ratio,
			   const Utility::ArrayView<const double>& bdd_block,
			   const Utility::ArrayView<const double>& dnedl_block,
		           const Utility::ArrayView<const double>& dned_block )
    : MonteCarlo::DelayedNeutronEmissionDistributionACEFactory( table_name,
                                                                atomic_weight_ratio,
                                                                bdd_block,
                                                                dnedl_block,
                                                                dned_block )
  { /* ... */ }

  ~TestDelayedNeutronEmissionDistributionACEFactory()
  { /* ... */ }

  using MonteCarlo::DelayedNeutronEmissionDistributionACEFactory::getPrecursorGroupDecayConsts;
  using MonteCarlo::DelayedNeutronEmissionDistributionACEFactory::getPrecursorGroupProbDists;
  using MonteCarlo::DelayedNeutronEmissionDistributionACEFactory::getPrecursorGroupEmissionDists;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::XSSNeutronDataExtractor> xss_data_extractor;
std::shared_ptr<TestDelayedNeutronEmissionDistributionACEFactory> factory;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the precursor group decay constants are correct
FRENSIE_UNIT_TEST( DelayedNeutronEmissionDistributionACEFactory,
		   getPrecursorGroupDecayConsts )
{
  const std::vector<double>& group_consts =
    factory->getPrecursorGroupDecayConsts();

  FRENSIE_CHECK_EQUAL( group_consts.size(), 6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( group_consts[0], 1.24942300000e-2, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( group_consts[1], 3.02552000000e-2, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( group_consts[2], 1.15937600000e-1, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( group_consts[3], 3.41476400000e-1, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( group_consts[4], 1.31863000000e+0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( group_consts[5], 9.97902700000e+0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the precursor group probability distributions are correct
FRENSIE_UNIT_TEST( DelayedNeutronEmissionDistributionACEFactory,
		   getPrecursorGroupProbDists )
{
  const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >& prob_dists =
    factory->getPrecursorGroupProbDists();

  FRENSIE_CHECK( prob_dists[0].get() != NULL );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[0]->evaluate( 1e-11 ), 1.03412800000e-02, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[0]->evaluate( 1.0 ), 1.03412800000e-02, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[0]->evaluate( 30.0 ), 1.03412800000e-02, 1e-15 );

  FRENSIE_CHECK( prob_dists[1].get() != NULL );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[1]->evaluate( 1e-11 ),
			  1.14819800000e-01,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[1]->evaluate( 1.0 ),
			  1.14819800000e-01,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[1]->evaluate( 30.0 ),
			  1.14819800000e-01,
			  1e-15 );

  FRENSIE_CHECK( prob_dists[2].get() != NULL );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[2]->evaluate( 1e-11 ),
			  1.27807200000e-01,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[2]->evaluate( 1.0 ),
			  1.27807200000e-01,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[2]->evaluate( 30.0 ),
			  1.27807200000e-01,
			  1e-15 );

  FRENSIE_CHECK( prob_dists[3].get() != NULL );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[3]->evaluate( 1e-11 ),
			  4.51836500000e-01,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[3]->evaluate( 1.0 ),
			  4.51836500000e-01,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[3]->evaluate( 30.0 ),
			  4.51836500000e-01,
			  1e-15 );

  FRENSIE_CHECK( prob_dists[4].get() != NULL );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[4]->evaluate( 1e-11 ),
			  2.33506500000e-01,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[4]->evaluate( 1.0 ),
			  2.33506500000e-01,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[4]->evaluate( 30.0 ),
			  2.33506500000e-01,
			  1e-15 );

  FRENSIE_CHECK( prob_dists[5].get() != NULL );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[5]->evaluate( 1e-11 ),
			  6.16886800000e-02,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[5]->evaluate( 1.0 ),
			  6.16886800000e-02,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( prob_dists[5]->evaluate( 30.0 ),
			  6.16886800000e-02,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the emission distribution can be constructed
FRENSIE_UNIT_TEST( DelayedNeutronEmissionDistributionACEFactory,
		   createEmissionDistribution )
{
  std::shared_ptr<const MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> >
    distribution;

  factory->createEmissionDistribution( distribution );

  FRENSIE_CHECK( distribution.get() != NULL );
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

  factory.reset( new TestDelayedNeutronEmissionDistributionACEFactory(
				 ace_file_handler->getTableName(),
				 ace_file_handler->getTableAtomicWeightRatio(),
				 xss_data_extractor->extractBDDBlock(),
				 xss_data_extractor->extractDNEDLBlock(),
				 xss_data_extractor->extractDNEDBlock() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDelayedNeutronEmissionDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
