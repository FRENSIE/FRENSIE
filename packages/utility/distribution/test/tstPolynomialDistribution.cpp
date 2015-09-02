//---------------------------------------------------------------------------//
//!
//! \file   tstPolynomialDistribution.cpp
//! \author Alex Robinson
//! \brief  Polynomial distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_PolynomialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( PolynomialDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5 ), 2.75 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 6.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( PolynomialDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.5 ), 2.75/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( PolynomialDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.5 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, sqrt(0.5) );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, pow( 0.5, 1.0/3.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( PolynomialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;
  
  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.5 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;
  
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, sqrt(0.5) );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;
  
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, pow( 0.5, 1.0/3.0 ) );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be 
// returned
TEUCHOS_UNIT_TEST( PolynomialDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( PolynomialDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( PolynomialDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::POLYNOMIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( PolynomialDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( PolynomialDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to and read from an xml file
TEUCHOS_UNIT_TEST( PolynomialDistribution, toParameterList )
{
  Teuchos::RCP<Utility::PolynomialDistribution> true_distribution = 
    Teuchos::rcp_dynamic_cast<Utility::PolynomialDistribution>( distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Utility::PolynomialDistribution>( "test_distribution",
						       *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"polynomial_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "polynomial_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::PolynomialDistribution>
    copy_distribution( new Utility::PolynomialDistribution );

  *copy_distribution = 
    read_parameter_list->get<Utility::PolynomialDistribution>( 
							 "test_distribution" );
  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( PolynomialDistribution, fromParameterList )
{
  Utility::PolynomialDistribution distribution = 
    test_dists_list->get<Utility::PolynomialDistribution>( "Polynomial Distribution A" );

  TEST_EQUALITY_CONST( distribution.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( distribution.getUpperBoundOfIndepVar(), 1.0 );

  distribution = 
    test_dists_list->get<Utility::PolynomialDistribution>( "Polynomial Distribution B" );

  TEST_EQUALITY_CONST( distribution.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( distribution.getUpperBoundOfIndepVar(), 
		       Utility::PhysicalConstants::pi/2 );
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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::PolynomialDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  // Initialize the polynomial distribution
  Teuchos::Array<double> coeffs( 3 );
  coeffs[0] = 1.0;
  coeffs[1] = 2.0;
  coeffs[2] = 3.0;

  distribution.reset( new Utility::PolynomialDistribution( coeffs, 0.0, 1.0 ));
  
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
// end tstPolynomialDistribution.cpp
//---------------------------------------------------------------------------//
