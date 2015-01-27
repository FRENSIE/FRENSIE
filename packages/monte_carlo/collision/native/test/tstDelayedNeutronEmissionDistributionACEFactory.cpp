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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestDelayedNeutronEmissionDistributionACEFactory : public MonteCarlo::DelayedNeutronEmissionDistributionACEFactory
{
public:
  TestDelayedNeutronEmissionDistributionACEFactory(
			   const std::string& table_name,
			   const double atomic_weight_ratio,
			   const Teuchos::ArrayView<const double>& bdd_block,
			   const Teuchos::ArrayView<const double>& dnedl_block,
		           const Teuchos::ArrayView<const double>& dned_block )
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
Teuchos::RCP<TestDelayedNeutronEmissionDistributionACEFactory> factory;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the precursor group decay constants are correct
TEUCHOS_UNIT_TEST( DelayedNeutronEmissionDistributionACEFactory,
		   getPrecursorGroupDecayConsts )
{
  const Teuchos::Array<double>& group_consts = 
    factory->getPrecursorGroupDecayConsts();

  TEST_EQUALITY_CONST( group_consts.size(), 6 );
  TEST_FLOATING_EQUALITY( group_consts[0], 1.24942300000e-2, 1e-15 );
  TEST_FLOATING_EQUALITY( group_consts[1], 3.02552000000e-2, 1e-15 );
  TEST_FLOATING_EQUALITY( group_consts[2], 1.15937600000e-1, 1e-15 );
  TEST_FLOATING_EQUALITY( group_consts[3], 3.41476400000e-1, 1e-15 );
  TEST_FLOATING_EQUALITY( group_consts[4], 1.31863000000e+0, 1e-15 );
  TEST_FLOATING_EQUALITY( group_consts[5], 9.97902700000e+0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the precursor group probability distributions are correct
TEUCHOS_UNIT_TEST( DelayedNeutronEmissionDistributionACEFactory,
		   getPrecursorGroupProbDists )
{
  const Teuchos::Array<Teuchos::RCP<Utility::OneDDistribution> >& prob_dists =
    factory->getPrecursorGroupProbDists();

  TEST_ASSERT( !prob_dists[0].is_null() );
  TEST_FLOATING_EQUALITY( prob_dists[0]->evaluate( 1e-11 ), 1.03412800000e-02, 1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[0]->evaluate( 1.0 ), 1.03412800000e-02, 1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[0]->evaluate( 30.0 ), 1.03412800000e-02, 1e-15 );

  TEST_ASSERT( !prob_dists[1].is_null() );
  TEST_FLOATING_EQUALITY( prob_dists[1]->evaluate( 1e-11 ), 
			  1.14819800000e-01, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[1]->evaluate( 1.0 ), 
			  1.14819800000e-01, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[1]->evaluate( 30.0 ), 
			  1.14819800000e-01, 
			  1e-15 );

  TEST_ASSERT( !prob_dists[2].is_null() );
  TEST_FLOATING_EQUALITY( prob_dists[2]->evaluate( 1e-11 ), 
			  1.27807200000e-01, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[2]->evaluate( 1.0 ), 
			  1.27807200000e-01, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[2]->evaluate( 30.0 ), 
			  1.27807200000e-01, 
			  1e-15 );
  
  TEST_ASSERT( !prob_dists[3].is_null() );
  TEST_FLOATING_EQUALITY( prob_dists[3]->evaluate( 1e-11 ), 
			  4.51836500000e-01, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[3]->evaluate( 1.0 ), 
			  4.51836500000e-01, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[3]->evaluate( 30.0 ), 
			  4.51836500000e-01, 
			  1e-15 );

  TEST_ASSERT( !prob_dists[4].is_null() );
  TEST_FLOATING_EQUALITY( prob_dists[4]->evaluate( 1e-11 ), 
			  2.33506500000e-01, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[4]->evaluate( 1.0 ), 
			  2.33506500000e-01, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[4]->evaluate( 30.0 ), 
			  2.33506500000e-01, 
			  1e-15 );
  
  TEST_ASSERT( !prob_dists[5].is_null() );
  TEST_FLOATING_EQUALITY( prob_dists[5]->evaluate( 1e-11 ), 
			  6.16886800000e-02, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[5]->evaluate( 1.0 ), 
			  6.16886800000e-02, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( prob_dists[5]->evaluate( 30.0 ), 
			  6.16886800000e-02, 
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the emission distribution can be constructed
TEUCHOS_UNIT_TEST( DelayedNeutronEmissionDistributionACEFactory,
		   createEmissionDistribution )
{
  Teuchos::RCP<MonteCarlo::NeutronScatteringDistribution> distribution;

  factory->createEmissionDistribution( distribution );

  TEST_ASSERT( !distribution.is_null() );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  std::string test_u238_ace_file_name;
  std::string test_u238_ace_table_name;
  
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
  Teuchos::RCP<Data::ACEFileHandler>
  ace_file_handler( new Data::ACEFileHandler( test_u238_ace_file_name,
					      test_u238_ace_table_name,
					      1u ) );

  Teuchos::RCP<Data::XSSNeutronDataExtractor>
  xss_data_extractor( 
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  factory.reset( new TestDelayedNeutronEmissionDistributionACEFactory(
				 ace_file_handler->getTableName(),
				 ace_file_handler->getTableAtomicWeightRatio(),
				 xss_data_extractor->extractBDDBlock(),    
				 xss_data_extractor->extractDNEDLBlock(),
				 xss_data_extractor->extractDNEDBlock() ) );

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
// end tstDelayedNeutronEmissionDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
