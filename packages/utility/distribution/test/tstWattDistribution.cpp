//---------------------------------------------------------------------------//
//!
//! \file   tstWattDistribution.cpp
//! \author Aaron Tumulak
//! \brief  Watt distribution unit tests.
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
#include "Utility_WattDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution(
				 new Utility::WattDistribution( 1.0, 1.0, 1.0, 0.1 ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( WattDistribution, evaluate )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = exp( -1.0 ) * sinh( 1.0 );
  
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( WattDistribution, evaluatePDF )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = 0.25 * sqrt( Utility::PhysicalConstants::pi ) * exp( 0.25 ) * ( erf( sqrt(0.9) - sqrt(0.25) ) + erf( sqrt(0.9) + sqrt(0.25) ) ) - exp( -0.9 ) * sinh( sqrt(0.9) );
  test_value_2 = pow( test_value_2, -1.0 ) * exp( -1.0 ) * sinh( 1.0 );

  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method
TEUCHOS_UNIT_TEST( WattDistribution, sample )
{
  std::vector<double> fake_stream( 15 );
  fake_stream[0] = 0.8110855833521807; // Maxwellian Distribution
  fake_stream[1] = 0.9603231091455754; // Sample Accepted. Sample is:
  fake_stream[2] = 0.3888878000049402; // 0.23654793157394
  fake_stream[3] = 0.1790067705163392; // Watt Distribution Sample Accepted. Sample is: 0.17431015530718
  fake_stream[4] = 0.7971990719536760; // Maxwellian Distribution
  fake_stream[5] = 0.0448247918373053; // Sample Rejected. Sample is:
  fake_stream[6] = 0.0375590391821071; // 3.32084968701263
  fake_stream[7] = 0.9522705508082248; // Maxwellian Distribution
  fake_stream[8] = 0.5691586660769004; // Sample Accepted. Sample is:
  fake_stream[9] = 0.0083308067369354; // 0.61240561891848
  fake_stream[10] = 0.6415677450291360; // Watt Distribution Sample Rejected. Sample is: 1.08397711671084
  fake_stream[11] = 0.8589987123720327; // Maxwellian Distribution
  fake_stream[12] = 0.4981431293148418; // Sample Accepted. Sample is:
  fake_stream[13] = 0.5932835342621010; // 0.39976547875177
  fake_stream[14] = 0.6731968005067009; // Watt Distribution Sample Accepted. Sample is: 0.86877979533891

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.17431015530718, 1e-13 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.86877979533891, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, passing in
// parameters
TEUCHOS_UNIT_TEST( WattDistribution, sampleAndRecordTrials_pass_parameters )
{
  std::vector<double> fake_stream( 15 );
  fake_stream[0] = 0.6617443503056450; // Maxwellian Distribution
  fake_stream[1] = 0.8510592242616175; // Sample Accepted. Sample is:
  fake_stream[2] = 0.5401745197210969; // 0.09667248521245
  fake_stream[3] = 0.2005969462099806; // Watt Distribution Sample Accepted. Sample is: 0.07927727029875
  fake_stream[4] = 0.5189418543931951; // Maxwellian Distribution
  fake_stream[5] = 0.7484231272861934; // Sample Rejected. Sample is:
  fake_stream[6] = 0.8345865134048199; // 0.13501824430785
  fake_stream[7] = 0.8704061668810904; // Maxwellian Distribution
  fake_stream[8] = 0.5575773053122431; // Sample Accepted. Sample is:
  fake_stream[9] = 0.7452925729418971; // 0.04548390223293
  fake_stream[10] = 0.6556974287666129; // Watt Distribution Sample Rejected. Sample is: 0.05068410532744
  fake_stream[11] = 0.8140855348977614; // Maxwellian Distribution
  fake_stream[12] = 0.5750169688125915; // Sample Accepted. Sample is:
  fake_stream[13] = 0.8372435273691630; // 0.04821527540845
  fake_stream[14] = 0.4721727279140688; // Watt Distribution Sample Accepted. Sample is: 0.04844237604136

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double incident_energy, a_parameter, b_parameter, restriction_energy, sample;
  unsigned trials = 0;
  
  incident_energy = 0.5;
  a_parameter = 0.2;
  b_parameter = 0.3;
  restriction_energy = 0.4;

  sample = Utility::WattDistribution::sampleAndRecordTrials(incident_energy, a_parameter, b_parameter, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.07927727029875, 1e-13 );
  TEST_EQUALITY_CONST( trials, 1.0 );
  
  incident_energy = 0.3;
  a_parameter = 0.2;
  b_parameter = 0.1;
  restriction_energy = 0.25;

  sample = Utility::WattDistribution::sampleAndRecordTrials(incident_energy, a_parameter, b_parameter, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.04844237604136, 1e-13 );
  TEST_EQUALITY_CONST( trials, 4.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( WattDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( WattDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( WattDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::WATT_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( WattDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( WattDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( WattDistribution, toParameterList )
{
  Teuchos::RCP<Utility::WattDistribution> true_distribution =
  Teuchos::rcp_dynamic_cast<Utility::WattDistribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::WattDistribution>( "test distribution",
                                                  *true_distribution );
  
  Teuchos::writeParameterListToXmlFile( parameter_list,
                                       "watt_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
  Teuchos::getParametersFromXmlFile( "watt_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );
  
  Teuchos::RCP<Utility::WattDistribution>
  copy_distribution( new Utility::WattDistribution );
  
  *copy_distribution = read_parameter_list->get<Utility::WattDistribution>(
                                                                             "test distribution");
  
  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( WattDistribution, fromParameterList )
{
  double test_value_1;
  double test_value_2;

  Utility::WattDistribution distribution = 
    test_dists_list->get<Utility::WattDistribution>( "Watt Distribution A" );

  test_value_1 = 0.0 ;
  test_value_2 = 0.25 * sqrt( Utility::PhysicalConstants::pi ) * exp( 0.25 ) * ( erf( sqrt(0.9) - sqrt(0.25) ) + erf( sqrt(0.9) + sqrt(0.25) ) ) - exp( -0.9 ) * sinh( sqrt(0.9) );
  test_value_2 = pow( test_value_2, -1.0 ) * exp( -1.0 ) * sinh( 1.0 );
  
  TEST_EQUALITY_CONST( distribution.evaluatePDF( 0.0 ), test_value_1 );
  TEST_FLOATING_EQUALITY( distribution.evaluatePDF( 1.0 ), 
			  test_value_2,
			  1e-15 );

   distribution = 
    test_dists_list->get<Utility::WattDistribution>( "Watt Distribution B" );

  test_value_1 = 0.0 ;
  test_value_2 = 0.25 * sqrt( Utility::PhysicalConstants::pi * pow( 2.0, 3.0 ) * 1.0 )
    * exp( 0.25 * 2.0 ) * ( erf( sqrt( 1.5 ) - sqrt( 0.25 * 2.0 ) )
    + erf( sqrt( 1.5 ) + sqrt( 0.25 * 2.0 ) ) )
    - 2.0 * exp( - 1.5 ) * sinh( sqrt( 3.0 ) );
  test_value_2 = pow( test_value_2, -1.0 ) * exp( -0.5 ) * sinh( 1.0 );
 
  TEST_EQUALITY_CONST( distribution.evaluatePDF( 0.0 ), test_value_1 );
  TEST_FLOATING_EQUALITY( distribution.evaluatePDF( 1.0 ), 
			  test_value_2,
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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::WattDistribution );

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
// end tstWattDistribution.cpp
//---------------------------------------------------------------------------//
