//---------------------------------------------------------------------------//
//!
//! \file   tstElasticElectronDistribution.cpp
//! \author Luke Kersting
//! \brief  ElasticElectron distribution unit tests.
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
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ElasticElectronDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution;
Teuchos::RCP<Utility::TabularOneDDistribution> elastic_distribution;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )				\
  typedef Utility::LinLin LinLin;					\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LinLin )			

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<typename InterpolationPolicy>
void initializeACEDistribution()
{
  Teuchos::Array<double> independent_values( 3 );
  independent_values[0] = -1.0;
  independent_values[1] = 0.999999;
  independent_values[2] = 1.0;
  
  Teuchos::Array<double> dependent_values( 3 );
  dependent_values[0] = 0.0;
  dependent_values[1] = 0.9999995;
  dependent_values[2] = 1.0;

  double energy = 1.0e-5;

  elastic_distribution.reset(new Utility::ElasticElectronDistribution<InterpolationPolicy>(
							  independent_values,
							  dependent_values,
                              energy,
                              82 ) );
  distribution = elastic_distribution;
}

// Initialize the distribution
template<typename InterpolationPolicy>
void initializeENDLDistribution()
{
  Teuchos::Array<double> independent_values( 3 );
  independent_values[2] = 2.0;
  independent_values[1] = 1.0E-6;
  independent_values[0] = 0.0;
  
  Teuchos::Array<double> dependent_values( 3 );
  dependent_values[2] = 5.0000000019895100E-01;
  dependent_values[1] = 4.9999999980104900E-01;
  dependent_values[0] = 5.0000000019895100E-01;

  double eta = 2.51317958942017E+03;
  double A = 3158035.826;

  elastic_distribution.reset(new Utility::ElasticElectronDistribution<InterpolationPolicy>(
							  independent_values,
							  dependent_values,
                              eta,
                              A ) );

  distribution = elastic_distribution;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution, 
				   evaluate,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 2.0 ), 
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.000001 ), 
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.0 ), 
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated 
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution, 
				   evaluatePDF,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->evaluatePDF( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 2.0 ), 
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 0.000001 ), 
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 0.0 ), 
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, evaluatePDF );

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated 
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution, 
				   evaluateCDF,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( elastic_distribution->evaluateCDF( 3.0 ), 1.0 );
  TEST_FLOATING_EQUALITY( elastic_distribution->evaluateCDF( 2.0 ), 
			  1.0000000000, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( elastic_distribution->evaluateCDF( 0.000001 ), 
			  0.0000005000, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( elastic_distribution->evaluateCDF( 0.0 ), 
			  0.0000000000, 
			  1e-10 );
  TEST_EQUALITY_CONST( elastic_distribution->evaluateCDF( -1.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, evaluateCDF );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sample,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = distribution->sample();
  TEST_COMPARE( sample, >=, 0.0 );
  TEST_COMPARE( sample, <=, 2.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, sample );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sampleAndRecordTrials,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-12 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_COMPARE( sample, >=, 0.0 );
  TEST_COMPARE( sample, <=, 2.0 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, sampleAndRecordTrials );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sampleAndRecordBinIndex,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  double sample = elastic_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = elastic_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = elastic_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_COMPARE( sample, >=, 0.0 );
  TEST_COMPARE( sample, <=, 2.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, sampleAndRecordBinIndex );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sampleWithRandomNumber,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  double sample = elastic_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = elastic_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, sampleWithRandomNumber );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sampleInSubrange,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = elastic_distribution->sampleInSubrange( 0.000001 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = elastic_distribution->sampleInSubrange( 0.000001 );
  TEST_FLOATING_EQUALITY( sample, 0.000001, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = elastic_distribution->sampleInSubrange( 0.000001 );
  TEST_COMPARE( sample, >=, 0.0 );
  TEST_COMPARE( sample, <=, 0.000001 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, sampleInSubrange );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sampleWithRandomNumberInSubrange,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  double sample = 
    elastic_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.000001  );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = 
        elastic_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.000001 );
  TEST_FLOATING_EQUALITY( sample, 0.000001, 1e-12 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, 
			 sampleWithRandomNumberInSubrange );

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   getUpperBoundOfIndepVar,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 2.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, getUpperBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   getLowerBoundOfIndepVar,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, getLowerBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   getDistributionType,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->getDistributionType(), 
		       Utility::ELASTIC_ELECTRON_DISTRIBUTION );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, getDistributionType );

//---------------------------------------------------------------------------//
// Check if the distribution is elastic electron
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   isTabular,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_ASSERT( distribution->isTabular() );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, isTabular );

//---------------------------------------------------------------------------//
// Check that the distribution is continuous
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   isContinuous,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_ASSERT( distribution->isContinuous() );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, isContinuous );

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   toParameterList,
				   InterpolationPolicy )
{
  initializeENDLDistribution<InterpolationPolicy>();

  typedef Utility::ElasticElectronDistribution<InterpolationPolicy> Distribution;

  Teuchos::RCP<Distribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Distribution>( distribution );

  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Distribution>( "test distribution", 
				      *true_distribution );

  std::ostringstream xml_file_name;
  xml_file_name << "elastic_electron_" << InterpolationPolicy::name() 
		<< "_dist_test_list.xml";
  
  Teuchos::writeParameterListToXmlFile( parameter_list,
					xml_file_name.str() );

  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( xml_file_name.str() );

std::cout << std::endl << "parameter_list =     \t"<< parameter_list << std::endl;
std::cout << std::endl << "read parameter_list =\t"<< *read_parameter_list << std::endl;
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Distribution> 
    copy_distribution( new Distribution );
/*
  *copy_distribution = read_parameter_list->get<Distribution>(
							  "test distribution");

std::cout << std::endl << "true distribution =\t" << *true_distribution<< std::endl;
std::cout << std::endl << "copy distribution =\t" << *copy_distribution << std::endl;

  TEST_EQUALITY( *copy_distribution, *true_distribution );*/
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, toParameterList );

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( ElasticElectronDistribution, fromParameterList )
{
  Utility::ElasticElectronDistribution<Utility::LinLin> distribution_1 = 
    test_dists_list->get<Utility::ElasticElectronDistribution<Utility::LinLin> >( "Elastic Electron Distribution A" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 2.0 );
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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::ElasticElectronDistribution<Utility::LinLin> );

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
// end tstElasticElectronDistribution.cpp
//---------------------------------------------------------------------------//
