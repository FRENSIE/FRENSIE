//---------------------------------------------------------------------------//
//!
//! \file   tstDiscreteDistribution.cpp
//! \author Alex Robinson
//! \brief  Discrete distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution;
Teuchos::RCP<Utility::OneDDistribution> cdf_cons_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( DiscreteDistribution, evaluate )
{  
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( distribution->evaluate( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( -1.0 ), 
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 0.0 ), 
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 1.0 ), 
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( DiscreteDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.50 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 0.0 ), 0.50 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
/*! \todo Add tests for all versions of the sample function
 */ 
TEUCHOS_UNIT_TEST( DiscreteDistribution, sample )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0/4.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 3.0/4.0;
  fake_stream[5] = 0.85;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  unsigned bin_index;

  // Test the first bin
  double sample = distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  // Test the first bin
  sample = cdf_cons_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = cdf_cons_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = cdf_cons_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = cdf_cons_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = cdf_cons_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = cdf_cons_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = cdf_cons_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getSamplingEfficiency )
{
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution dependent variable can be
// returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->getLowerBoundOfIndepVar(),-1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
  TEST_EQUALITY_CONST( cdf_cons_distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( DiscreteDistribution, toParameterList )
{
  Teuchos::RCP<Utility::DiscreteDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::DiscreteDistribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::DiscreteDistribution>( "test distribution", 
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"discrete_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "discrete_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::DiscreteDistribution> 
    copy_distribution( new Utility::DiscreteDistribution );

  *copy_distribution = read_parameter_list->get<Utility::DiscreteDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( DiscreteDistribution, fromParameterList )
{
  Utility::DiscreteDistribution distribution = 
    test_dists_list->get<Utility::DiscreteDistribution>( "Discrete Distribution A" );
  
  TEST_EQUALITY_CONST( distribution.getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( distribution.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( distribution.evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( distribution.evaluatePDF( 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( distribution.evaluatePDF( 1.0 ), 0.25 );

  distribution = 
    test_dists_list->get<Utility::DiscreteDistribution>( "Discrete Distribution B" );

  TEST_EQUALITY_CONST( distribution.getLowerBoundOfIndepVar(), 
		       -Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( distribution.getUpperBoundOfIndepVar(),
		       Utility::PhysicalConstants::pi );
  TEST_FLOATING_EQUALITY( distribution.evaluatePDF(-Utility::PhysicalConstants::pi/2),
			  0.2,
			  1e-15 );
  TEST_FLOATING_EQUALITY( distribution.evaluatePDF(Utility::PhysicalConstants::pi),
			  0.2,
			  1e-15 );
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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::DiscreteDistribution );
  
  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Create a distribution using the standard constructor
  Teuchos::Array<double> independent_values( 3 );
  independent_values[0] = -1.0;
  independent_values[1] = 0.0;
  independent_values[2] = 1.0;
  
  Teuchos::Array<double> dependent_values( 3 );
  dependent_values[0] = 1.0;
  dependent_values[1] = 2.0;
  dependent_values[2] = 1.0;
  
  distribution.reset( new Utility::DiscreteDistribution( independent_values,
							 dependent_values ) );
  
  // Create a distribution using the cdf constructor
  Teuchos::Array<double> cdf_values( 3 );
  cdf_values[0] = 0.25;
  cdf_values[1] = 0.75;
  cdf_values[2] = 1.0;

  cdf_cons_distribution.reset( new Utility::DiscreteDistribution(
							  independent_values,
							  cdf_values,
							  true ) );
  
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
// end tstDiscreteDistribution.cpp
//---------------------------------------------------------------------------//
