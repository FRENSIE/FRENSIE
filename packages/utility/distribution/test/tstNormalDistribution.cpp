//---------------------------------------------------------------------------//
//!
//! \file   tstNormalDistribution.cpp
//! \author Alex Robinson
//! \brief  Normal distribution unit tests.
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
#include "Utility_NormalDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution(
				 new Utility::NormalDistribution( 0.0, 1.0 ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( NormalDistribution, evaluate )
{
  double center_value = 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi );
  double off_center_value = center_value*exp( -4.0/2.0 );
  
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), center_value);
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), off_center_value );
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), off_center_value );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( NormalDistribution, evaluatePDF )
{
  double center_value = 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi );
  double off_center_value = center_value*exp( -4.0/2.0 );
  
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), center_value);
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), off_center_value );
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), off_center_value );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( NormalDistribution, sample )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( NormalDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( NormalDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( NormalDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(),
		       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( NormalDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::NORMAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( NormalDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( NormalDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( NormalDistribution, toParameterList )
{
  Teuchos::RCP<Utility::NormalDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::NormalDistribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::NormalDistribution>( "test distribution", 
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"normal_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "normal_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::NormalDistribution> 
    copy_distribution( new Utility::NormalDistribution );

  *copy_distribution = read_parameter_list->get<Utility::NormalDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( NormalDistribution, fromParameterList )
{
  Utility::NormalDistribution distribution = 
    test_dists_list->get<Utility::NormalDistribution>( "Normal Distribution A" );

  TEST_EQUALITY_CONST( distribution.getLowerBoundOfIndepVar(),
		       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );

  distribution = 
    test_dists_list->get<Utility::NormalDistribution>( "Normal Distribution B" );
  
  TEST_EQUALITY_CONST( distribution.getLowerBoundOfIndepVar(),
		       -Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( distribution.getUpperBoundOfIndepVar(),
		       Utility::PhysicalConstants::pi );

  distribution = 
    test_dists_list->get<Utility::NormalDistribution>( "Normal Distribution C" );

  TEST_EQUALITY_CONST( distribution.getLowerBoundOfIndepVar(),
		       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::NormalDistribution );

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
// end tstNormalDistribution.cpp
//---------------------------------------------------------------------------//

