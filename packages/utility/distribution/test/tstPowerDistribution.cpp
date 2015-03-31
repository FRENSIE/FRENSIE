//---------------------------------------------------------------------------//
//!
//! \file   tstPowerDistribution.cpp
//! \author Alex Robinson
//! \brief  Power distribution unit tests.
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
#include "Utility_PowerDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )			\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 1u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 2u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 3u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 4u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 5u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 6u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 7u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 8u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 9u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 10u )	

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<unsigned N>
void initializeDistribution( 
			Teuchos::RCP<Utility::OneDDistribution>& distribution )
{
  distribution.reset( new Utility::PowerDistribution<N>( (N+1.0), 0.0, 1.0 ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, evaluate, N )
{
  initializeDistribution<N>( distribution );
  
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), N + 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}
				   
UNIT_TEST_INSTANTIATION( PowerDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, evaluatePDF, N )
{
  initializeDistribution<N>( distribution );

  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), N + 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}
				   
UNIT_TEST_INSTANTIATION( PowerDistribution, evaluatePDF );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, sample, N )
{
  initializeDistribution<N>( distribution );
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, pow(0.5, 1.0/(N+1u)) );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION( PowerDistribution, sample );

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, 
					   getSamplingEfficiency, 
					   N )
{
  initializeDistribution<N>( distribution );

  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );
}

UNIT_TEST_INSTANTIATION( PowerDistribution, getSamplingEfficiency );

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, 
					   getUpperBoundOfIndepVar,
					   N )
{
  initializeDistribution<N>( distribution );
  
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

UNIT_TEST_INSTANTIATION( PowerDistribution, getUpperBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, 
					   getLowerBoundOfIndepVar,
					   N )
{
  initializeDistribution<N>( distribution );
  
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

UNIT_TEST_INSTANTIATION( PowerDistribution, getLowerBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution,
					    getDistributionType,
					    N )
{
  initializeDistribution<N>( distribution );

  switch( N )
  {
  case 1u:
    TEST_EQUALITY_CONST( distribution->getDistributionType(),
			 Utility::POWER_1_DISTRIBUTION );
    break;
  case 2u:
    TEST_EQUALITY_CONST( distribution->getDistributionType(),
			 Utility::POWER_2_DISTRIBUTION );
    break;
  default:
    TEST_EQUALITY_CONST( distribution->getDistributionType(),
			 Utility::POWER_N_DISTRIBUTION );
    break;
  }
}

UNIT_TEST_INSTANTIATION( PowerDistribution, getDistributionType );

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution,
					    toFromParameterList,
					    N )
{
  initializeDistribution<N>( distribution );

  Teuchos::RCP<Utility::PowerDistribution<N> > true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::PowerDistribution<N> >( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::PowerDistribution<N> >( "test distribution", 
						      *true_distribution );

  std::ostringstream xml_file_name;
  xml_file_name << "power_" << N << "_dist_test_list.xml";
  
  Teuchos::writeParameterListToXmlFile( parameter_list,
					xml_file_name.str() );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( xml_file_name.str() );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::PowerDistribution<N> > 
    copy_distribution( new Utility::PowerDistribution<N> );

  *copy_distribution = 
    read_parameter_list->get<Utility::PowerDistribution<N> >(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

UNIT_TEST_INSTANTIATION( PowerDistribution, toFromParameterList );

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( PowerDistribution, fromParameterList )
{
  Utility::PowerDistribution<1u> distribution_1 = 
    test_dists_list->get<Utility::PowerDistribution<1u> >( "Power Distribution A" );
  
  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), 0 );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 1 );
  TEST_EQUALITY_CONST( distribution_1.evaluate( 1.0 ), 2.0 );

  distribution_1 = 
    test_dists_list->get<Utility::PowerDistribution<1u> >( "Power Distribution B" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), 0 );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 
		       Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( distribution_1.evaluate( 1.0 ), 1.0 );

  Utility::PowerDistribution<2u> distribution_2 = 
    test_dists_list->get<Utility::PowerDistribution<2u> >( "Power Distribution C" );

  TEST_EQUALITY_CONST( distribution_2.getLowerBoundOfIndepVar(), 0 );
  TEST_EQUALITY_CONST( distribution_2.getUpperBoundOfIndepVar(), 
		       2*Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( distribution_2.evaluate( 1.0 ), 3.0 );

  distribution_2 = 
    test_dists_list->get<Utility::PowerDistribution<2u> >( "Power Distribution D" );

  TEST_EQUALITY_CONST( distribution_2.getLowerBoundOfIndepVar(), 0 );
  TEST_EQUALITY_CONST( distribution_2.getUpperBoundOfIndepVar(), 
		       3*Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( distribution_2.evaluate( 0.5 ), 0.25 );

  Utility::PowerDistribution<3u> distribution_3 = 
    test_dists_list->get<Utility::PowerDistribution<3u> >( "Power Distribution E" );

  TEST_EQUALITY_CONST( distribution_3.getLowerBoundOfIndepVar(), 0 );
  TEST_EQUALITY_CONST( distribution_3.getUpperBoundOfIndepVar(), 
		       Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( distribution_3.evaluate( 1.0 ), 4.0 );

  distribution_3 = 
    test_dists_list->get<Utility::PowerDistribution<3u> >( "Power Distribution F" );

  TEST_EQUALITY_CONST( distribution_3.getLowerBoundOfIndepVar(), 0 );
  TEST_EQUALITY_CONST( distribution_3.getUpperBoundOfIndepVar(), 
		       5*Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( distribution_3.evaluate( 1.0 ), 1.0 );
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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::PowerDistribution<1u> );
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::PowerDistribution<2u> );
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::PowerDistribution<3u> );

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
// end tstPowerDistribution.cpp
//---------------------------------------------------------------------------//
