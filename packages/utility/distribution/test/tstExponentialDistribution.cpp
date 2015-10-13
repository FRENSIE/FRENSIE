//---------------------------------------------------------------------------//
//!
//! \file   tstExponentialDistribution.cpp
//! \author Alex Robinson
//! \brief  Histogram distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution( 
			     new Utility::ExponentialDistribution( 2.0, 3.0 ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ExponentialDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 2.0 );
  TEST_FLOATING_EQUALITY(distribution->evaluate( 1.0 ), 2.0*exp(-3.0), 1e-12);
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( ExponentialDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 3.0 );
  TEST_FLOATING_EQUALITY(distribution->evaluatePDF(1.0), 3.0*exp(-3.0), 1e-12);
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( ExponentialDistribution, sample_basic_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::ExponentialDistribution::sample( 3.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = Utility::ExponentialDistribution::sample( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );
  
  sample = Utility::ExponentialDistribution::sample( 3.0 );
  TEST_FLOATING_EQUALITY( sample, -log(0.5)/3.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( ExponentialDistribution, sample_static )
{
  
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( ExponentialDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = distribution->sample(); 
  TEST_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );

  sample = distribution->sample(); 
  TEST_FLOATING_EQUALITY( sample, -log(0.5)/3.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( ExponentialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  unsigned trials = 0;
  
  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1 );

  sample = distribution->sampleAndRecordTrials( trials ); 
  UTILITY_TEST_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );
  TEST_EQUALITY_CONST( trials, 2 );

  sample = distribution->sampleAndRecordTrials( trials ); 
  TEST_FLOATING_EQUALITY( sample, -log(0.5)/3.0, 1e-12 );
  TEST_EQUALITY_CONST( trials, 3 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( ExponentialDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( ExponentialDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( ExponentialDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::EXPONENTIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( ExponentialDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( ExponentialDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( ExponentialDistribution, toParameterList )
{
  Teuchos::RCP<Utility::ExponentialDistribution> true_distribution =
   Teuchos::rcp_dynamic_cast<Utility::ExponentialDistribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::ExponentialDistribution>( "test distribution", 
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"exponential_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "exponential_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::ExponentialDistribution> 
    copy_distribution( new Utility::ExponentialDistribution );

  *copy_distribution = 
    read_parameter_list->get<Utility::ExponentialDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( ExponentialDistribution, fromParameterList )
{
  Utility::ExponentialDistribution read_distribution = 
    test_dists_list->get<Utility::ExponentialDistribution>( "Exponential Distribution A" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), 1.0 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0 ), 
			  exp( -3.0 ), 
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 0.0 );
  
  read_distribution = 
    test_dists_list->get<Utility::ExponentialDistribution>( "Exponential Distribution B" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ),
		       Utility::PhysicalConstants::pi );
  TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0 ),
			  Utility::PhysicalConstants::pi*exp( -3.0 ),
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 0.0 );
  
  read_distribution = 
    test_dists_list->get<Utility::ExponentialDistribution>( "Exponential Distribution C" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0 ),
			  Utility::PhysicalConstants::pi*exp( -3.0 ),
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 1.0 );

  read_distribution = 
    test_dists_list->get<Utility::ExponentialDistribution>( "Exponential Distribution D" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0 ),
			  Utility::PhysicalConstants::pi*exp( -3.0 ),
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(), 2.0 );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 1.0 );

  read_distribution = 
    test_dists_list->get<Utility::ExponentialDistribution>( "Exponential Distribution E" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0 ),
			  Utility::PhysicalConstants::pi*exp( -3.0 ),
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_dists_xml_file;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "test_dists_xml_file",
		 &test_dists_xml_file,
		 "Test distributions xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::ExponentialDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstExponentialDistribution.cpp
//---------------------------------------------------------------------------//
