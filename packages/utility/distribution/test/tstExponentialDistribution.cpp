//---------------------------------------------------------------------------//
//!
//! \file   tstExponentialDistribution.cpp
//! \author Alex Robinson
//! \brief  Histogram distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <limits>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DynamicOutputFormatter.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
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

Teuchos::RCP<Utility::OneDDistribution> distribution(
			     new Utility::ExponentialDistribution( 2.0, 3.0 ) );
Teuchos::RCP<Utility::UnitAwareOneDDistribution<cgs::length,si::amount> > unit_aware_distribution( new Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>( 2.0*si::mole, 300.0/si::meter, 0.0*si::meter ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ExponentialDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 2.0 );
  TEST_FLOATING_EQUALITY(distribution->evaluate( 1.0 ), 2.0*exp(-3.0), 1e-12);
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate(-1.0*cgs::centimeter),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*cgs::centimeter),
		       2.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY(
		       unit_aware_distribution->evaluate( 1.0*cgs::centimeter),
		       2.0*exp(-3.0)*si::mole,
		       1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( ExponentialDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 3.0 );
  TEST_FLOATING_EQUALITY(distribution->evaluatePDF(1.0), 3.0*exp(-3.0), 1e-12);
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST(
		  unit_aware_distribution->evaluatePDF( -1.0*cgs::centimeter ),
		  0.0/cgs::centimeter );
  TEST_EQUALITY_CONST(
		   unit_aware_distribution->evaluatePDF( 0.0*cgs::centimeter ),
		   3.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY(
		   unit_aware_distribution->evaluatePDF( 1.0*cgs::centimeter ),
		   3.0*exp(-3.0)/cgs::centimeter,
		   1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( ExponentialDistribution, sample_basic_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::ExponentialDistribution::sample( 3.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = Utility::ExponentialDistribution::sample( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );

  sample = Utility::ExponentialDistribution::sample( 3.0 );
  TEST_FLOATING_EQUALITY( sample, -log(0.5)/3.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, sample_basic_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample =
    Utility::UnitAwareExponentialDistribution<cgs::length>::sample( 3.0/cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = Utility::UnitAwareExponentialDistribution<cgs::length>::sample( 3.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  11.5131919974469596*cgs::centimeter,
				  1e-15 );

  sample = Utility::UnitAwareExponentialDistribution<cgs::length>::sample( 3.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -log(0.5)/3.0*cgs::centimeter,
				  1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( ExponentialDistribution, sample_static )
{
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double inf = std::numeric_limits<double>::infinity();

  double sample = Utility::ExponentialDistribution::sample( 3.0, 0.0, inf );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = Utility::ExponentialDistribution::sample( 3.0, 0.0, inf );
  TEST_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );

  sample = Utility::ExponentialDistribution::sample( 3.0, 0.0, inf );
  TEST_FLOATING_EQUALITY( sample, -log(0.5)/3.0, 1e-12 );

  sample = Utility::ExponentialDistribution::sample( 3.0, 1.0, inf );
  TEST_FLOATING_EQUALITY( sample, 1.2310490601866484, 1e-12 );

  sample = Utility::ExponentialDistribution::sample( 3.0, 1.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.2148532763287345, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, sample_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> inf =
    Utility::QuantityTraits<quantity<cgs::length> >::inf();

  quantity<cgs::length> sample =
    Utility::UnitAwareExponentialDistribution<cgs::length>::sample(
			       3.0/cgs::centimeter, 0.0*cgs::centimeter, inf );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = Utility::UnitAwareExponentialDistribution<cgs::length>::sample(
			       3.0/cgs::centimeter, 0.0*cgs::centimeter, inf );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  11.5131919974469596*cgs::centimeter,
				  1e-15 );

  sample = Utility::UnitAwareExponentialDistribution<cgs::length>::sample(
			       3.0/cgs::centimeter, 0.0*cgs::centimeter, inf );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -log(0.5)/3.0*cgs::centimeter,
				  1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( ExponentialDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -log(0.5)/3.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  11.5131919974469596*cgs::centimeter,
				  1e-15 );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -log(0.5)/3.0*cgs::centimeter,
				  1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( ExponentialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1 );

  sample = distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );
  TEST_EQUALITY_CONST( trials, 2 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, -log(0.5)/3.0, 1e-12 );
  TEST_EQUALITY_CONST( trials, 3 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  11.5131919974469596*cgs::centimeter,
				  1e-15 );
  TEST_EQUALITY_CONST( trials, 2 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -log(0.5)/3.0*cgs::centimeter,
				  1e-12 );
  TEST_EQUALITY_CONST( trials, 3 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( ExponentialDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       Utility::QuantityTraits<quantity<cgs::length> >::inf());
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( ExponentialDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       Utility::QuantityTraits<quantity<cgs::length> >::zero());
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( ExponentialDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::EXPONENTIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::EXPONENTIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( ExponentialDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, isTabular )
{
  TEST_ASSERT( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( ExponentialDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, isContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( ExponentialDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::ExponentialDistribution test_dist( 1.0, 1.0, 0.1, 1.0 );

  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution,
                   isCompatibleWithInterpType )
{
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>
    test_dist( 1.0*si::mole, 1.0/si::meter, 0.1*si::meter, 1.0*si::meter );

  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( ExponentialDistribution, toParameterList )
{
  Teuchos::RCP<Utility::ExponentialDistribution> true_distribution =
   Teuchos::rcp_dynamic_cast<Utility::ExponentialDistribution>( distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Utility::ExponentialDistribution>( "test distribution",
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"exponential_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "exponential_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::ExponentialDistribution>
    copy_distribution( new Utility::ExponentialDistribution );

  *copy_distribution =
    read_parameter_list->get<Utility::ExponentialDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, toParameterList )
{
  typedef Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>
    UnitAwareExponentialDistribution;

  Teuchos::RCP<UnitAwareExponentialDistribution> true_distribution =
   Teuchos::rcp_dynamic_cast<UnitAwareExponentialDistribution>(
						     unit_aware_distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<UnitAwareExponentialDistribution>( "test distribution",
							*true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"unit_aware_exponential_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "unit_aware_exponential_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<UnitAwareExponentialDistribution>
    copy_distribution( new UnitAwareExponentialDistribution );

  *copy_distribution =
    read_parameter_list->get<UnitAwareExponentialDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( ExponentialDistribution, fromParameterList )
{
  Utility::ExponentialDistribution read_distribution =
    test_dists_list->get<Utility::ExponentialDistribution>( "Exponential Distribution A" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), 1.0 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0 ),
			  exp( -3.0 ),
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 0.0 );

  read_distribution =
    test_dists_list->get<Utility::ExponentialDistribution>( "Exponential Distribution B" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ),
		       Utility::PhysicalConstants::pi );
  TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0 ),
			  Utility::PhysicalConstants::pi*exp( -3.0 ),
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 0.0 );

  read_distribution =
    test_dists_list->get<Utility::ExponentialDistribution>( "Exponential Distribution C" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0 ),
			  Utility::PhysicalConstants::pi*exp( -3.0 ),
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 1.0 );

  read_distribution =
    test_dists_list->get<Utility::ExponentialDistribution>( "Exponential Distribution D" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0 ),
			  Utility::PhysicalConstants::pi*exp( -3.0 ),
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(), 2.0 );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 1.0 );

  read_distribution =
    test_dists_list->get<Utility::ExponentialDistribution>( "Exponential Distribution E" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0 ),
			  Utility::PhysicalConstants::pi*exp( -3.0 ),
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareExponentialDistribution, fromParameterList )
{
  typedef Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>
    UnitAwareExponentialDistribution;

  UnitAwareExponentialDistribution read_distribution =
    test_dists_list->get<UnitAwareExponentialDistribution>( "Unit-Aware Exponential Distribution A" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*cgs::centimeter ),
  		       1.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY(
  			     read_distribution.evaluate( 1.0*cgs::centimeter ),
  			     exp( -3.0 )*si::mole,
  			     1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
  		       Utility::QuantityTraits<quantity<cgs::length> >::inf());
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
  		       0.0*cgs::centimeter );

  read_distribution =
    test_dists_list->get<UnitAwareExponentialDistribution>(
				     "Unit-Aware Exponential Distribution B" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*cgs::centimeter ),
  		       Utility::PhysicalConstants::pi*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY(
			  read_distribution.evaluate( 1.0*cgs::centimeter ),
  			  Utility::PhysicalConstants::pi*exp( -3.0 )*si::mole,
  			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
  		       Utility::QuantityTraits<quantity<cgs::length> >::inf());
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
		       0.0*cgs::centimeter );

  read_distribution =
    test_dists_list->get<UnitAwareExponentialDistribution>(
				     "Unit-Aware Exponential Distribution C" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*cgs::centimeter ),
		       0.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY(
			   read_distribution.evaluate( 1.0*cgs::centimeter ),
			   Utility::PhysicalConstants::pi*exp( -3.0 )*si::mole,
			   1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
  		       Utility::QuantityTraits<quantity<cgs::length> >::inf());
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
		       1.0*cgs::centimeter );

  read_distribution =
    test_dists_list->get<UnitAwareExponentialDistribution>(
				     "Unit-Aware Exponential Distribution D" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*cgs::centimeter ),
		       0.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY(
			   read_distribution.evaluate( 1.0*cgs::centimeter ),
			   Utility::PhysicalConstants::pi*exp( -3.0 )*si::mole,
			   1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       2.0*cgs::centimeter );
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
		       1.0*cgs::centimeter );

  read_distribution =
    test_dists_list->get<UnitAwareExponentialDistribution>(
				     "Unit-Aware Exponential Distribution E" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*cgs::centimeter ),
		       0.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY(
			   read_distribution.evaluate( 1.0*cgs::centimeter ),
			   Utility::PhysicalConstants::pi*exp( -3.0 )*si::mole,
			   1e-15 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
  		       Utility::QuantityTraits<quantity<cgs::length> >::inf());
  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
		       1.0*cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareExponentialDistribution,
				   explicit_conversion,
				   IndepUnitA,
				   DepUnitA,
				   IndepUnitB,
				   DepUnitB )
{
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitA>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityA;

  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitB>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityB;

  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  // Copy from unitless distribution to distribution type A (static method)
  Utility::UnitAwareExponentialDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareExponentialDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::ExponentialDistribution>( distribution ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwareExponentialDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 3.0 );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 2.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b( inv_indep_quantity_a );
  DepQuantityB dep_quantity_b( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );

  Utility::setQuantity( indep_quantity_a, 1.0 );
  Utility::setQuantity( inv_indep_quantity_a, 3.0*exp(-3.0) );
  Utility::setQuantity( dep_quantity_a, 2.0*exp(-3.0) );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );
}

typedef si::energy si_energy;
typedef cgs::energy cgs_energy;
typedef si::amount si_amount;
typedef si::length si_length;
typedef cgs::length cgs_length;
typedef si::mass si_mass;
typedef cgs::mass cgs_mass;
typedef si::dimensionless si_dimensionless;
typedef cgs::dimensionless cgs_dimensionless;

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareExponentialDistribution,
				      explicit_conversion,
				      void,
				      MegaElectronVolt,
				      void,
				      KiloElectronVolt );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_dists_xml_file;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_dists_xml_file",
                   &test_dists_xml_file,
                   "Test distributions xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::ExponentialDistribution );
  typedef Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> UnitAwareExponentialDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareExponentialDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstExponentialDistribution.cpp
//---------------------------------------------------------------------------//
