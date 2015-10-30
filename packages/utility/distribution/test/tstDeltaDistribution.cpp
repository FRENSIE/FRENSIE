//---------------------------------------------------------------------------//
//!
//! \file   tstDeltaDistribution.cpp
//! \author Alex Robinson
//! \brief  Delta distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"

using boost::units::quantity;
namespace si = boost::units::si;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::TabularOneDDistribution>
  tab_distribution( new Utility::DeltaDistribution( 0.0 ) );

Teuchos::RCP<Utility::OneDDistribution>
  distribution( tab_distribution );

Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<si::time> >
  unit_aware_tab_distribution( new Utility::UnitAwareDeltaDistribution<si::time>( 3.0*si::seconds ) );

Teuchos::RCP<Utility::UnitAwareOneDDistribution<si::time> >
  unit_aware_distribution( unit_aware_tab_distribution );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( DeltaDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*si::seconds ), 
		       0.0 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*si::seconds ), 
		       1.0 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 6.0*si::seconds ), 
		       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( DeltaDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*si::seconds ),
		       0.0/si::seconds );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 3.0*si::seconds ),
		       1.0/si::seconds );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 6.0*si::seconds ),
		       0.0/si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( DeltaDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 1.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( 
		   unit_aware_tab_distribution->evaluateCDF( 0.0*si::seconds ),
		   0.0 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_distribution->evaluateCDF( 3.0*si::seconds ),
		   1.0 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_distribution->evaluateCDF( 6.0*si::seconds ),
		   1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sample )
{
  TEST_EQUALITY_CONST( distribution->sample(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sample )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->sample(), 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleAndRecordTrials )
{
  unsigned trials = 0;
  double sample = distribution->sampleAndRecordTrials( trials );
  
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleAndRecordTrials )
{
  unsigned trials = 0;
  
  quantity<si::time> sample = 
    unit_aware_distribution->sampleAndRecordTrials( trials );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
  TEST_EQUALITY_CONST( trials, 1 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleAndRecordBinIndex )
{
  unsigned bin_index = 0;
  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleAndRecordBinIndex )
{
  unsigned bin_index = 0;
  
  quantity<si::time> sample = 
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
  TEST_EQUALITY_CONST( bin_index, 0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleWithRandomNumber )
{
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleWithRandomNumber )
{
  quantity<si::time> sample = 
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.5 );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleInSubrange )
{
  double sample = tab_distribution->sampleInSubrange( 1.0 );
  
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleInSubrange( 0.1 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleInSubrange )
{
  quantity<si::time> sample = 
    unit_aware_tab_distribution->sampleInSubrange( 4.0*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleInSubrange( 3.1*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleWithRandomNumberInSubrange )
{
  double sample = 
    tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 1.0 );
  
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 2.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, 
		   sampleWithRandomNumberInSubrange )
{
  quantity<si::time> sample = 
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 4.0*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 3.1*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can
// be returned
TEUCHOS_UNIT_TEST( DeltaDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent 
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can 
// be returned
TEUCHOS_UNIT_TEST( DeltaDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent 
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(), 
		       3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( DeltaDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(), 
		       Utility::DELTA_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::DELTA_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( DeltaDistribution, toParameterList )
{
  Teuchos::RCP<Utility::DeltaDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::DeltaDistribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::DeltaDistribution>( "test distribution", 
						  *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"delta_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "delta_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );
  
  Teuchos::RCP<Utility::DeltaDistribution> 
    copy_distribution( new Utility::DeltaDistribution );
  
  *copy_distribution = read_parameter_list->get<Utility::DeltaDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, toParameterList )
{
  typedef Utility::UnitAwareDeltaDistribution<si::time> UnitAwareDeltaDistribution;
  
  Teuchos::RCP<UnitAwareDeltaDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<UnitAwareDeltaDistribution>( unit_aware_distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<UnitAwareDeltaDistribution>( "test distribution", 
						  *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"unit_aware_delta_dist_test_list.xml");
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "unit_aware_delta_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );
  
  Teuchos::RCP<UnitAwareDeltaDistribution> 
    copy_distribution( new UnitAwareDeltaDistribution );
  
  *copy_distribution = read_parameter_list->get<UnitAwareDeltaDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
  
  std::cout << boost::units::name_string( si::energy() ) << std::endl;
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( DeltaDistribution, fromParameterList )
{
  Utility::DeltaDistribution xml_distribution = 
    test_dists_list->get<Utility::DeltaDistribution>( "Delta Distribution A" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 0 );

  xml_distribution = 
    test_dists_list->get<Utility::DeltaDistribution>( "Delta Distribution B" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 
		       Utility::PhysicalConstants::pi );

  xml_distribution = 
    test_dists_list->get<Utility::DeltaDistribution>( "Delta Distribution C" );
  
  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 
		       -Utility::PhysicalConstants::pi/2 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, fromParameterList )
{
  typedef Utility::UnitAwareDeltaDistribution<si::time> UnitAwareDeltaDistribution;
  
  UnitAwareDeltaDistribution xml_distribution = 
    test_dists_list->get<UnitAwareDeltaDistribution>( "Unit-Aware Delta Distribution A" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 
		       3.0*si::seconds );

  xml_distribution = 
    test_dists_list->get<UnitAwareDeltaDistribution>( "Unit-Aware Delta Distribution B" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 
		       2*Utility::PhysicalConstants::pi*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be constructed from a unitless
// distribution
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareDeltaDistribution,
				   unitless_copy_constructor,
				   IndepUnit )
{
  typedef typename Utility::UnitTraits<IndepUnit>::template GetQuantityType<double>::type
    IndepQuantity;
  
  Utility::UnitAwareDeltaDistribution<IndepUnit> unit_aware_dist_copy = 
    Utility::UnitAwareDeltaDistribution<IndepUnit>::fromUnitlessDistribution( 
     *Teuchos::rcp_dynamic_cast<Utility::DeltaDistribution>(distribution) );

  IndepQuantity indep_quantity = 
    Utility::QuantityTraits<IndepQuantity>::initializeQuantity( -1.0 );

  TEST_EQUALITY_CONST( unit_aware_dist_copy.evaluate( indep_quantity ), 0.0 );
  
  Utility::setQuantity( indep_quantity, 0.0 );
    
  TEST_EQUALITY_CONST( unit_aware_dist_copy.evaluate( indep_quantity ), 1.0 );

  Utility::setQuantity( indep_quantity, 1.0 );
    
  TEST_EQUALITY_CONST( unit_aware_dist_copy.evaluate( indep_quantity ), 0.0 );
}

typedef si::energy si_energy;
typedef si::length si_length;
typedef si::area si_area;
typedef si::mass si_mass;
typedef si::time si_time;
typedef si::amount si_amount;
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( UnitAwareDeltaDistribution,
				      unitless_copy_constructor,
				      si_energy );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( UnitAwareDeltaDistribution,
				      unitless_copy_constructor,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( UnitAwareDeltaDistribution,
				      unitless_copy_constructor,
				      si_time );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( UnitAwareDeltaDistribution,
				      unitless_copy_constructor,
				      si_area );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( UnitAwareDeltaDistribution,
				      unitless_copy_constructor,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( UnitAwareDeltaDistribution,
				      unitless_copy_constructor,
				      void );

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

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::DeltaDistribution );
  typedef Utility::UnitAwareDeltaDistribution<si::time> UnitAwareDeltaDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareDeltaDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

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
// end tstDeltaDistribution.cpp
//---------------------------------------------------------------------------//
