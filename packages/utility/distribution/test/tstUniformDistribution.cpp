//---------------------------------------------------------------------------//
//!
//! \file   tstUniformDistribution.cpp
//! \author Alex Robinson
//! \brief  Uniform distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/io.hpp>

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
#include "Utility_UniformDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::TabularOneDDistribution> tab_distribution( 
			  new Utility::UniformDistribution( -1.0, 1.0, 2.0 ) );

Teuchos::RCP<Utility::OneDDistribution> distribution = tab_distribution;

Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<si::energy,si::amount> >
  unit_aware_tab_distribution;

Teuchos::RCP<Utility::UnitAwareOneDDistribution<si::energy,si::amount> >
  unit_aware_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( UniformDistribution, evaluate )
{  
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*si::joule ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*si::joule ),
  		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*si::joule ),
  		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*si::joule ),
  		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*si::joule ),
  		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( UniformDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.5 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.5 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( -1.0*si::joule ),
  		       0.0/si::joule );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*si::joule ),
  		       1.0/si::joule );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.5*si::joule ),
  		       1.0/si::joule );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.0*si::joule ),
  		       1.0/si::joule );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 2.0*si::joule ),
  		       0.0/si::joule );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( UniformDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 2.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST(unit_aware_tab_distribution->evaluateCDF(-1.0*si::joule),
		      0.0 );
  TEST_EQUALITY_CONST(unit_aware_tab_distribution->evaluateCDF(0.0*si::joule),
		      0.0 );
  TEST_EQUALITY_CONST(unit_aware_tab_distribution->evaluateCDF(0.5*si::joule),
		      0.5 );
  TEST_EQUALITY_CONST(unit_aware_tab_distribution->evaluateCDF(1.0*si::joule),
		      1.0 );
  TEST_EQUALITY_CONST(unit_aware_tab_distribution->evaluateCDF(2.0*si::joule),
		      1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 ); 

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<si::energy> sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.5*si::joule );
  
  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 ); 
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled 
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  unsigned trials = 0;

  quantity<si::energy> sample = 
    unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.5*si::joule ); 
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  unsigned bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0.0 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 ); 
  TEST_EQUALITY_CONST( bin_index, 0.0 );
  
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  unsigned bin_index;

  quantity<si::energy> sample = 
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );
  TEST_EQUALITY_CONST( bin_index, 0.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.5*si::joule ); 
  TEST_EQUALITY_CONST( bin_index, 0.0 );
  
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sampleWithRandomNumber )
{
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 ); 
    
  sample = tab_distribution->sampleWithRandomNumber( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sampleWithRandomNumber )
{
  quantity<si::energy> sample = 
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );
  
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.5*si::joule ); 
    
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = tab_distribution->sampleInSubrange( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_distribution->sampleInSubrange( 0.0 );
  TEST_EQUALITY_CONST( sample, -0.5 ); 
    
  sample = tab_distribution->sampleInSubrange( 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
    
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  quantity<si::energy> sample = 
    unit_aware_tab_distribution->sampleInSubrange( 0.5*si::joule );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );
  
  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*si::joule );
  TEST_EQUALITY_CONST( sample, 0.25*si::joule ); 
    
  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*si::joule );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*si::joule, 1e-14 );
    
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sampleWithRandomNumberInSubrange )
{
  double sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -0.5 ); 
    
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, 
		   sampleWithRandomNumberInSubrange )
{
  quantity<si::energy> sample = 
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 
							  0.0, 0.5*si::joule );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );
  
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 
							  0.5, 0.5*si::joule );
  TEST_EQUALITY_CONST( sample, 0.25*si::joule ); 
    
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 
							  1.0, 0.5*si::joule );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*si::joule, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be 
// returned
TEUCHOS_UNIT_TEST( UniformDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent 
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(), 
		       1.0*si::joule );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( UniformDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent 
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(), 
		       0.0*si::joule );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( UniformDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::UNIFORM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::UNIFORM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( UniformDistribution, isTabular )
{
  TEST_ASSERT( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, isTabular )
{
  TEST_ASSERT( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( UniformDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, isContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UniformDistribution, toParameterList )
{
  Teuchos::RCP<Utility::UniformDistribution> true_distribution =
   Teuchos::rcp_dynamic_cast<Utility::UniformDistribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::UniformDistribution>( "test distribution", 
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"uniform_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "uniform_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::UniformDistribution> 
    copy_distribution( new Utility::UniformDistribution );

  *copy_distribution = 
    read_parameter_list->get<Utility::UniformDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, toParameterList )
{
  typedef Utility::UnitAwareUniformDistribution<si::energy,si::amount> UnitAwareUniformDistribution;
  
  Teuchos::RCP<UnitAwareUniformDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<UnitAwareUniformDistribution>( unit_aware_distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<UnitAwareUniformDistribution>( "test distribution", 
						    *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"unit_aware_uniform_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "unit_aware_uniform_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<UnitAwareUniformDistribution> 
    copy_distribution( new UnitAwareUniformDistribution );

  *copy_distribution = 
    read_parameter_list->get<UnitAwareUniformDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UniformDistribution, fromParameterList )
{
  Utility::UniformDistribution xml_distribution = 
    test_dists_list->get<Utility::UniformDistribution>( "Uniform Distribution A" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( xml_distribution.evaluate( 0.0 ), 2.0 );
  
  xml_distribution = 
    test_dists_list->get<Utility::UniformDistribution>( "Uniform Distribution B" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(), 
		       2*Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( xml_distribution.evaluate( 1.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, fromParameterList )
{
  typedef Utility::UnitAwareUniformDistribution<si::energy,si::amount> UnitAwareUniformDistribution;
  
  UnitAwareUniformDistribution xml_distribution = 
    test_dists_list->get<UnitAwareUniformDistribution>( "Unit-Aware Uniform Distribution A" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 0.0*si::joule );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(), 10.0*si::joule);
  TEST_EQUALITY_CONST( xml_distribution.evaluate( 5.0*si::joule ), 3.0*si::mole );
  
  xml_distribution = 
    test_dists_list->get<UnitAwareUniformDistribution>( "Unit-Aware Uniform Distribution B" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 0.0*si::joule );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(), 
		       Utility::PhysicalConstants::pi*si::joule );
  TEST_EQUALITY_CONST( xml_distribution.evaluate( 1.0*si::joule ), 1.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be constructed from a unitless
// distribution
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( UnitAwareUniformDistribution,
				   unitless_copy_constructor,
				   IndepUnit,
				   DepUnit )
{
  typedef typename Utility::UnitTraits<IndepUnit>::template GetQuantityType<double>::value
    IndepQuantity;
  typedef typename Utility::UnitTraits<DepUnit>::template GetQuantityType<double>::value
    DepQuantity;
  
  Utility::UnitAwareUniformDistribution<IndepUnit,DepUnit> 
    unit_aware_dist_copy( 
     *Teuchos::rcp_dynamic_cast<Utility::UniformDistribution>(distribution) );

  IndepQuantity indep_quantity = 
    Utility::QuantityTraits<IndepQuantity>::initializeQuantity( -1.0 );
  DepQuantity dep_quantity = 
    Utility::QuantityTraits<DepQuantity>::initializeQuantity( 2.0 );

  TEST_EQUALITY_CONST( unit_aware_dist_copy.evaluate( indep_quantity ),
		       dep_quantity );
  
  Utility::setQuantity( indep_quantity, 0.0 );
  Utility::setQuantity( dep_quantity, 2.0 );
  
  TEST_EQUALITY_CONST( unit_aware_dist_copy.evaluate( indep_quantity ),
		       dep_quantity );

  Utility::setQuantity( indep_quantity, 1.0 );
  Utility::setQuantity( dep_quantity, 2.0 );
  
  TEST_EQUALITY_CONST( unit_aware_dist_copy.evaluate( indep_quantity ),
		       dep_quantity );
}

typedef si::energy si_energy;
typedef si::length si_length;
typedef si::area si_area;
typedef si::mass si_mass;
typedef si::time si_time;
typedef si::amount si_amount;
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareUniformDistribution,
				      unitless_copy_constructor,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareUniformDistribution,
				      unitless_copy_constructor,
				      si_length,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareUniformDistribution,
				      unitless_copy_constructor,
				      si_time,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareUniformDistribution,
				      unitless_copy_constructor,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareUniformDistribution,
				      unitless_copy_constructor,
				      si_area,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareUniformDistribution,
				      unitless_copy_constructor,
				      si_time,
				      si_energy );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareUniformDistribution,
				      unitless_copy_constructor,
				      si_time,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareUniformDistribution,
				      unitless_copy_constructor,
				      void,
				      si_energy );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareUniformDistribution,
				      unitless_copy_constructor,
				      void,
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

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::UniformDistribution );
  typedef Utility::UnitAwareUniformDistribution<si::energy,si::amount> UnitAwareUniformDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareUniformDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Initialize the unit-aware distributions
  unit_aware_tab_distribution.reset(
	     new Utility::UnitAwareUniformDistribution<si::energy,si::amount>( 
				      quantity<si::energy>( 0.0*si::joule ),
				      quantity<si::energy>( 1.0*si::joule ),
				      quantity<si::amount>( 1.0*si::mole ) ) );

  unit_aware_distribution = unit_aware_tab_distribution;
  
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
// end tstUniformDistribution.cpp
//---------------------------------------------------------------------------//

