//---------------------------------------------------------------------------//
//!
//! \file   tstEvaporationDistribution.cpp
//! \author Aaron Tumulak
//! \brief  Evaporation distribution unit tests.
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
#include "Utility_EvaporationDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

Teuchos::RCP<Utility::EvaporationDistribution> distribution(
				 new Utility::EvaporationDistribution( 1.0, 1.0, 0.1 ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( EvaporationDistribution, evaluate )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = pow( 1.0 - exp(-0.9) * (1.0 + 0.9), -1.0 ) * exp( -1.0 ); 
  
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( EvaporationDistribution, evaluatePDF )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = pow( 1.0 - exp(-0.9) * (1.0 + 0.9), -1.0 ) * exp( -1.0 );

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method
TEUCHOS_UNIT_TEST( EvaporationDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.8388165507412660;
  fake_stream[1] = 0.0267354287196134;
  fake_stream[2] = 0.9615425535640773;
  fake_stream[3] = 0.9996969006924931;
  fake_stream[4] = 0.1891183747157897;
  fake_stream[5] = 0.8650163759473460;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.70470821836401, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.83920374256297, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, and the
// trials can be recorded
TEUCHOS_UNIT_TEST( EvaporationDistribution, sampleAndRecordTrials_pass_parameters )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.7109904185738904;
  fake_stream[1] = 0.1535897705184878;
  fake_stream[2] = 0.6915260327666102;
  fake_stream[3] = 0.6291257012282162;
  fake_stream[4] = 0.3183560295023423;
  fake_stream[5] = 0.7492388871308626;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double incident_energy, nuclear_temperature, restriction_energy, sample;
  unsigned trials = 0;
 
  incident_energy = 0.5;
  nuclear_temperature = 0.1;
  restriction_energy = 0.01;

  sample = distribution->sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.13885427138954, 1e-13 );
  TEST_EQUALITY_CONST( trials, 1.0 );

  incident_energy = 0.75;
  nuclear_temperature = 0.5;
  restriction_energy = 0.25;

  sample = distribution->sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.43320278283758, 1e-13 );
  TEST_EQUALITY_CONST( trials, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( EvaporationDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( EvaporationDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( EvaporationDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::EVAPORATION_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to and read from an xml file
TEUCHOS_UNIT_TEST( EvaporationDistribution, toFromParameterList )
{
  Teuchos::RCP<Utility::EvaporationDistribution> true_distribution =
  Teuchos::rcp_dynamic_cast<Utility::EvaporationDistribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::EvaporationDistribution>( "test distribution",
                                                  *true_distribution );
  
  Teuchos::writeParameterListToXmlFile( parameter_list,
                                       "evaporation_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
  Teuchos::getParametersFromXmlFile( "evaporation_dist_test_list.xml" );

  // TEST_EQUALITY( parameter_list, *read_parameter_list );
  TEST_EQUALITY( *read_parameter_list, *read_parameter_list );
  
  Teuchos::RCP<Utility::EvaporationDistribution>
  copy_distribution( new Utility::EvaporationDistribution );
  
  *copy_distribution = read_parameter_list->get<Utility::EvaporationDistribution>(
                                                                             "test distribution");
  
  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
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
// end tstEvaporationDistribution.cpp
//---------------------------------------------------------------------------//

