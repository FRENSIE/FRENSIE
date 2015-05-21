//---------------------------------------------------------------------------//
//!
//! \file   tstMaxwellFissionDistribution.cpp
//! \author Aaron Tumulak
//! \brief  Maxwell Fission distribution unit tests.
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
#include "Utility_MaxwellFissionDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution(
				 new Utility::MaxwellFissionDistribution( 1.0, 1.0, 0.1 ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, evaluate )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = ( sqrt( Utility::PhysicalConstants::pi) * 0.5 * erf(sqrt(0.9)) - sqrt(0.9) * exp(-0.9) );
  test_value_2 = pow( test_value_2, -1.0 );
  test_value_2 = test_value_2 * exp( -1.0 );
  
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, evaluatePDF )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = ( sqrt( Utility::PhysicalConstants::pi) * 0.5 * erf(sqrt(0.9)) - sqrt(0.9) * exp(-0.9) );
  test_value_2 = pow( test_value_2, -1.0 );
  test_value_2 = test_value_2 * exp( -1.0 );

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.9526660807223237;
  fake_stream[1] = 0.2628340201570147;
  fake_stream[2] = 0.4684607693058543;
  fake_stream[3] = 0.2948581100330813;
  fake_stream[4] = 0.4810986077957187;
  fake_stream[5] = 0.8453449553051804;
  fake_stream[6] = 0.4656289304981871;
  fake_stream[7] = 0.7470315175721101;
  fake_stream[8] = 0.5418708973800604;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.78269807500829, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.89106359701991, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method and the 
// trials can be recorded
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.9526660807223237;
  fake_stream[1] = 0.2628340201570147;
  fake_stream[2] = 0.4684607693058543;
  fake_stream[3] = 0.2948581100330813;
  fake_stream[4] = 0.4810986077957187;
  fake_stream[5] = 0.8453449553051804;
  fake_stream[6] = 0.4656289304981871;
  fake_stream[7] = 0.7470315175721101;
  fake_stream[8] = 0.5418708973800604;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 0.78269807500829, 1e-14 );
  TEST_EQUALITY_CONST( trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 0.89106359701991, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, passing in
// parameters
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, 
		   sampleAndRecordTrials_pass_parameters )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.1324998063336137;
  fake_stream[1] = 0.9247996934252033;
  fake_stream[2] = 0.1918514900811418;
  fake_stream[3] = 0.3062640867105594;
  fake_stream[4] = 0.8754839687423933;
  fake_stream[5] = 0.2274300298185482;
  fake_stream[6] = 0.9336967385663441;
  fake_stream[7] = 0.2459018944829507;
  fake_stream[8] = 0.4770873202414019;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double incident_energy, nuclear_temperature, restriction_energy, sample;
  unsigned trials = 0;
  
  incident_energy = 0.5;
  nuclear_temperature = 0.1;
  restriction_energy = 0.01;

  sample = Utility::MaxwellFissionDistribution::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.20924646054839, 1e-13 );
  
  incident_energy = 0.75;
  nuclear_temperature = 0.5;
  restriction_energy = 0.25;

  sample = Utility::MaxwellFissionDistribution::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.41023025568120, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::MAXWELLFISSION_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, toParameterList )
{
  Teuchos::RCP<Utility::MaxwellFissionDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::MaxwellFissionDistribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::MaxwellFissionDistribution>( "test distribution", 
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"maxwellfission_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "maxwellfission_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::MaxwellFissionDistribution> 
    copy_distribution( new Utility::MaxwellFissionDistribution );

  *copy_distribution = read_parameter_list->get<Utility::MaxwellFissionDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, fromParameterList )
{
  double test_value_1;
  double test_value_2;

  Utility::MaxwellFissionDistribution distribution = 
    test_dists_list->get<Utility::MaxwellFissionDistribution>( "Maxwell Fission Distribution A" );

  test_value_1 = 0.0 ;
  test_value_2 = ( sqrt( Utility::PhysicalConstants::pi) * 0.5 * erf(sqrt(0.9)) - sqrt(0.9) * exp(-0.9) );
  test_value_2 = pow( test_value_2, -1.0 );
  test_value_2 = test_value_2 * exp( -1.0 );
  
  TEST_EQUALITY_CONST( distribution.evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution.evaluate( 1.0 ), test_value_2 );

  distribution = 
    test_dists_list->get<Utility::MaxwellFissionDistribution>( "Maxwell Fission Distribution B" );
  
  test_value_1 = 0.0 ;
  test_value_2 = pow( 2.0, 1.5 ) * ( sqrt( Utility::PhysicalConstants::pi) * 0.5 * erf(sqrt(1.0)) - sqrt(1.0) * exp(-1.0) );
  test_value_2 = pow( test_value_2, -1.0 );
  test_value_2 = test_value_2 * exp( -0.5 );
  
  TEST_EQUALITY_CONST( distribution.evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution.evaluate( 1.0 ), test_value_2 );

  distribution = 
    test_dists_list->get<Utility::MaxwellFissionDistribution>( "Maxwell Fission Distribution C" );

  test_value_1 = 0.0 ;
  test_value_2 = ( sqrt( Utility::PhysicalConstants::pi) * 0.5 * erf(sqrt(1.0)) - sqrt(1.0) * exp(-1.0) );
  test_value_2 = pow( test_value_2, -1.0 );
  test_value_2 = test_value_2 * exp( -1.0 );
  
  TEST_EQUALITY_CONST( distribution.evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution.evaluate( 1.0 ), test_value_2 );
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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::MaxwellFissionDistribution );

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
// end tstMaxwellFissionDistribution.cpp
//---------------------------------------------------------------------------//

