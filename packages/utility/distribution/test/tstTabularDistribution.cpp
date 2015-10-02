//---------------------------------------------------------------------------//
//!
//! \file   tstTabularDistribution.cpp
//! \author Alex Robinson
//! \brief  Tabular distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution;
Teuchos::RCP<Utility::TabularOneDDistribution> tab_distribution;

Teuchos::RCP<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution;
Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> >
unit_aware_tab_distribution;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )				\
  typedef Utility::LinLin LinLin;					\
  typedef Utility::LogLin LogLin;					\
  typedef Utility::LinLog LinLog;					\
  typedef Utility::LogLog LogLog;					\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LinLin )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LogLin )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LinLog )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LogLog )	

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<typename InterpolationPolicy, typename BaseDistribution>
void initialize( Teuchos::RCP<BaseDistribution>& dist )
{
  // Use the basic constructor
  Teuchos::Array<double> independent_values( 4 );
  independent_values[0] = 1e-3;
  independent_values[1] = 1e-2;
  independent_values[2] = 1e-1;
  independent_values[3] = 1.0;
  
  Teuchos::Array<double> dependent_values( 4 );
  dependent_values[0] = 1e2;
  dependent_values[1] = 1e1;
  dependent_values[2] = 1.0;
  dependent_values[3] = 1e-1;

  dist.reset(new Utility::UnitAwareTabularDistribution<InterpolationPolicy,typename BaseDistribution::IndepUnit, typename BaseDistribution::DepUnit>(
							  independent_values,
							  dependent_values ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution, 
				   evaluate,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-3 ), 1e2 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-2 ), 1e1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-1 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 1e-1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
				   evaluate,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV ), 
		       0.0*si::mole );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated 
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution, 
				   evaluatePDF,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-3 ), 
			  67.340006734, 
			  1e-6 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-2 ), 
			  6.7340006734, 
			  1e-6 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-1 ), 
			  0.67340006734, 
			  1e-6 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1.0 ), 
			  0.067340006734, 
			  1e-6 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, evaluatePDF );

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated 
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution, 
				   evaluateCDF,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-3 ), 
			  0.0000000000, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-2 ), 
			  0.33333333333, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-1 ), 
			  0.66666666667, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1.0 ), 
			  1.0000000000, 
			  1e-10 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 2.0 ), 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, evaluateCDF );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sample,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 1e-3 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = distribution->sample();
  TEST_COMPARE( sample, >=, 1e-3 );
  TEST_COMPARE( sample, <=, 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sample );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sampleAndRecordTrials,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1e-3 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_COMPARE( sample, >=, 1e-3 );
  TEST_COMPARE( sample, <=, 1.0 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sampleAndRecordTrials );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sampleAndRecordBinIndex,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1e-3 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_COMPARE( sample, >=, 1e-3 );
  TEST_COMPARE( sample, <=, 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sampleAndRecordBinIndex );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sampleWithRandomNumber,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 1e-3 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sampleWithRandomNumber );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sampleInSubrange,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleInSubrange( 1e-1  );
  TEST_EQUALITY_CONST( sample, 1e-3 );
  
  sample = tab_distribution->sampleInSubrange( 1e-1 );
  TEST_FLOATING_EQUALITY( sample, 1e-1, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = tab_distribution->sampleInSubrange( 1e-1 );
  TEST_COMPARE( sample, >=, 1e-3 );
  TEST_COMPARE( sample, <=, 1e-1 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sampleInSubrange );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sampleWithRandomNumberInSubrange,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  double sample = 
    tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 1e-1  );
  TEST_EQUALITY_CONST( sample, 1e-3 );
  
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 1e-1 );
  TEST_FLOATING_EQUALITY( sample, 1e-1, 1e-12 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, 
			 sampleWithRandomNumberInSubrange );

//---------------------------------------------------------------------------//
// Check that a distribution can be constructed from a cdf
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution, 
				   cdf_constructor,
				   InterpolationPolicy )
{
  Teuchos::Array<double> indep_values( 4 ), cdf_values( 4 );
  indep_values[0] = 1e-3;
  indep_values[1] = 1e-2;
  indep_values[2] = 1e-1;
  indep_values[3] = 1.0;

  cdf_values[0] = 0.0;
  cdf_values[1] = 0.495;
  cdf_values[2] = 0.99;
  cdf_values[3] = 1.485;
  
  Teuchos::RCP<Utility::TabularOneDDistribution> 
    dist_from_cdf( new Utility::TabularDistribution<InterpolationPolicy>( 
								indep_values,
								cdf_values,
								true ) );

  TEST_EQUALITY_CONST( dist_from_cdf->evaluate( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1e-3 ), 55.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1e-2 ), 55.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1e-1 ), 5.5, 1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1.0 ), 0.55, 1e-15 );
  TEST_EQUALITY_CONST( dist_from_cdf->evaluate( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( dist_from_cdf->evaluatePDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1e-3 ), 
			  37.03703703703703,
			  1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1e-2 ), 
			  37.03703703703703,
			  1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1e-1 ), 
			  3.703703703703703,
			  1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1.0 ), 
			  0.37037037037037046,
			  1e-15 );
  TEST_EQUALITY_CONST( dist_from_cdf->evaluatePDF( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( dist_from_cdf->evaluateCDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1e-3 ), 
			  0.0000000000, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1e-2 ), 
			  0.33333333333, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1e-1 ), 
			  0.66666666667, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1.0 ), 
			  1.0000000000, 
			  1e-10 );
  TEST_EQUALITY_CONST( dist_from_cdf->evaluateCDF( 2.0 ), 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, cdf_constructor );

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   getUpperBoundOfIndepVar,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, getUpperBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   getLowerBoundOfIndepVar,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 1e-3 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, getLowerBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   getDistributionType,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getDistributionType(), 
		       Utility::TABULAR_DISTRIBUTION );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, getDistributionType );

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   isTabular,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_ASSERT( distribution->isTabular() );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, isTabular );

//---------------------------------------------------------------------------//
// Check that the distribution is continuous
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   isContinuous,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_ASSERT( distribution->isContinuous() );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, isContinuous );

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   toParameterList,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  typedef Utility::TabularDistribution<InterpolationPolicy> Distribution;

  Teuchos::RCP<Distribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Distribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Distribution>( "test distribution", 
				      *true_distribution );

  std::ostringstream xml_file_name;
  xml_file_name << "tabular_" << InterpolationPolicy::name() 
		<< "_dist_test_list.xml";
  
  Teuchos::writeParameterListToXmlFile( parameter_list,
					xml_file_name.str() );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( xml_file_name.str() );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Distribution> 
    copy_distribution( new Distribution );

  *copy_distribution = read_parameter_list->get<Distribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, toParameterList );

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( TabularDistribution, fromParameterList )
{
  Utility::TabularDistribution<Utility::LinLin> distribution_1 = 
    test_dists_list->get<Utility::TabularDistribution<Utility::LinLin> >( "Tabular Distribution A" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), 0.001 );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 
		       Utility::PhysicalConstants::pi );
  
  distribution_1 = 
    test_dists_list->get<Utility::TabularDistribution<Utility::LinLin> >( "Tabular Distribution B" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), 0.001 );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 1.0 );

  Utility::TabularDistribution<Utility::LogLog> distribution_2 = 
    test_dists_list->get<Utility::TabularDistribution<Utility::LogLog> >( "Tabular Distribution C" );

  TEST_EQUALITY_CONST( distribution_2.getLowerBoundOfIndepVar(), 0.001 );
  TEST_EQUALITY_CONST( distribution_2.getUpperBoundOfIndepVar(), 10.0 );
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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::TabularDistribution<Utility::LinLin> );
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::TabularDistribution<Utility::LogLin> );
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::TabularDistribution<Utility::LinLog> );
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::TabularDistribution<Utility::LogLog> );

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
// end tstTabularDistribution.cpp
//---------------------------------------------------------------------------//
