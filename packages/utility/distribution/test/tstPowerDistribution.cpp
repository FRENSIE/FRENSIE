//---------------------------------------------------------------------------//
//!
//! \file   tstPowerDistribution.cpp
//! \author Alex Robinson
//! \brief  Power distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_PowerDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

typedef std::tuple<
  std::integral_constant<size_t,1>,
  std::integral_constant<size_t,2>,
  std::integral_constant<size_t,3>,
  std::integral_constant<size_t,4>,
  std::integral_constant<size_t,5>,
  std::integral_constant<size_t,6>,
  std::integral_constant<size_t,7>,
  std::integral_constant<size_t,8>,
  std::integral_constant<size_t,9>,
  std::integral_constant<size_t,10>
 > TestInts;
  

typedef std::tuple<
  std::tuple<si::length,si::amount,cgs::length,si::amount>,
  std::tuple<cgs::length,si::amount,si::length,si::amount>,
  std::tuple<cgs::length,cgs::mass,si::length,si::mass>,
  std::tuple<si::length,si::mass,cgs::length,cgs::mass>,
  std::tuple<cgs::length,cgs::dimensionless,si::length,si::dimensionless>,
  std::tuple<si::length,si::dimensionless,cgs::length,cgs::dimensionless>,
  std::tuple<cgs::length,void*,si::length,void*>,
  std::tuple<si::length,void*,cgs::length,void*>,
  std::tuple<void*,cgs::dimensionless,void*,si::dimensionless>,
  std::tuple<void*,si::dimensionless,void*,cgs::dimensionless>,
  std::tuple<si::length,si::amount,cgs::length,si::amount>,
  std::tuple<cgs::length,si::amount,si::length,si::amount>,
  std::tuple<cgs::length,cgs::mass,si::length,si::mass>,
  std::tuple<si::length,si::mass,cgs::length,cgs::mass>,
  std::tuple<cgs::length,cgs::dimensionless,si::length,si::dimensionless>
 > TestUnitTypeQuads;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<Utility::PropertyTree> test_dists_ptree;

std::shared_ptr<Utility::OneDDistribution> distribution;

std::shared_ptr<Utility::UnitAwareOneDDistribution<cgs::length,si::amount> >
  unit_aware_distribution;

//---------------------------------------------------------------------------//
// Testing Tables
//---------------------------------------------------------------------------//
// This table describes the data in the property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable )
{
  std::vector<std::string> no_unused_children;
  Utility::PowerDistribution<1> dummy_dist;

  const double& pi = Utility::PhysicalConstants::pi;
  const double inf = Utility::QuantityTraits<double>::inf();

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_0_args" ) << "Distribution A" << true << no_unused_children << Utility::PowerDistribution<1>();
  NEW_ROW( "inline_2_args" ) << "Distribution B" << true << no_unused_children << Utility::PowerDistribution<1>( 1.0, 1.0, 2.0 );
  NEW_ROW( "inline_3_args_ucase" ) << "Distribution C" << true << no_unused_children << Utility::PowerDistribution<1>( 3.0, 1.0, 2.0 );
  NEW_ROW( "inline_3_args_lcase" ) << "Distribution D" << true << no_unused_children << Utility::PowerDistribution<1>( 2.0, pi/2, pi );
  NEW_ROW( "inline_bad_type" ) << "Distribution E" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_mult" ) << "Distribution F" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_mult" ) << "Distribution G" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_lower_limit" ) << "Distribution H" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_lower_limit" ) << "Distribution I" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_upper_limit" ) << "Distribution J" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_bad_limits" ) << "Distribution K" << false << no_unused_children << dummy_dist;

  NEW_ROW( "0_args" ) << "Distribution L" << true << no_unused_children << Utility::PowerDistribution<1>();
  NEW_ROW( "1_arg" ) << "Distribution M" << true << no_unused_children << Utility::PowerDistribution<1>( 3.0 );
  NEW_ROW( "2_args" ) << "Distribution N" << true << no_unused_children << Utility::PowerDistribution<1>( 1.0, 1.0, 2.0 );
  NEW_ROW( "3_args" ) << "Distribution O" << true << no_unused_children << Utility::PowerDistribution<1>( 3.0, 1.0, 2.0 );
  NEW_ROW( "extra_arg" ) << "Distribution P" << true << std::vector<std::string>( {"dummy"} ) << Utility::PowerDistribution<1>( 3.0, 1.0, 2.0 );
  NEW_ROW( "duplicate_args" ) << "Distribution Q" << true << std::vector<std::string>( {"multiplier", "lower boundary", "upper boundary"} ) << Utility::PowerDistribution<1>( 3.0, 1.0, 2.0 );
  NEW_ROW( "bad_type" ) << "Distribution R" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_mult" ) << "Distribution S" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_mult" ) << "Distribution T" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_lower_limit" ) << "Distribution U" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_lower_limit" ) << "Distribution V" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_upper_limit" ) << "Distribution W" << false << no_unused_children << dummy_dist;
  NEW_ROW( "bad_limits" ) << "Distribution X" << false << no_unused_children << dummy_dist;
}

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<unsigned N, typename IndepUnit, typename DepUnit>
void initializeDistribution(
       std::shared_ptr<Utility::UnitAwareOneDDistribution<IndepUnit,DepUnit> >&
       distribution )
{
  typedef typename Utility::UnitAwareOneDDistribution<IndepUnit,DepUnit>::IndepQuantity IndepQuantity;
  distribution.reset(
     new Utility::UnitAwarePowerDistribution<N,IndepUnit,DepUnit>(
	   (N+1.0),
	   Utility::QuantityTraits<IndepQuantity>::initializeQuantity( 0.0 ),
	   Utility::QuantityTraits<IndepQuantity>::initializeQuantity( 1.0 )));
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, evaluate, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), WrappedN::value + 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, evaluate, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate(-1.0*cgs::centimeter),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*cgs::centimeter),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*cgs::centimeter),
		       (WrappedN::value + 1.0)*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*cgs::centimeter),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, evaluatePDF, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), WrappedN::value+1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, evaluatePDF, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL(
	          unit_aware_distribution->evaluatePDF( -1.0*cgs::centimeter ),
		  0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_distribution->evaluatePDF( 0.0*cgs::centimeter ),
		   0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_distribution->evaluatePDF( 1.0*cgs::centimeter ),
		   (WrappedN::value+1.0)/cgs::centimeter );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_distribution->evaluatePDF( 2.0*cgs::centimeter ),
		   0.0/cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, sample, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u)) );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, sample, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u))*cgs::centimeter );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*cgs::centimeter, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, sample_static, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::PowerDistribution<WrappedN::value>::sample( 0.0, 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = Utility::PowerDistribution<WrappedN::value>::sample( 0.0, 1.0 );
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u)) );

  sample = Utility::PowerDistribution<WrappedN::value>::sample( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            sample_static,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample =
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length>::sample(
							 0.0*cgs::centimeter,
						         1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample =
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length>::sample(
							 0.0*cgs::centimeter,
						         1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u))*cgs::centimeter );

  sample =
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length>::sample(
							 0.0*cgs::centimeter,
						         1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*cgs::centimeter, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            sampleAndRecordTrials,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u)) );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            sampleAndRecordTrials,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u))*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            getUpperBoundOfIndepVar,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            getUpperBoundOfIndepVar,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       1.0*cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            getLowerBoundOfIndepVar,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            getLowerBoundOfIndepVar,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            getDistributionType,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  switch( WrappedN::value )
  {
  case 1u:
    FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
			 Utility::POWER_1_DISTRIBUTION );
    break;
  case 2u:
    FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
			 Utility::POWER_2_DISTRIBUTION );
    break;
  default:
    FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
			 Utility::POWER_N_DISTRIBUTION );
    break;
  }
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            getDistributionType,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  switch( WrappedN::value )
  {
  case 1u:
    FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
			 Utility::POWER_1_DISTRIBUTION );
    break;
  case 2u:
    FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
			 Utility::POWER_2_DISTRIBUTION );
    break;
  default:
    FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
			 Utility::POWER_N_DISTRIBUTION );
    break;
  }
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            getDistributionTypeName,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  FRENSIE_CHECK_EQUAL( Utility::PowerDistribution<WrappedN::value>::typeName( true, false, " " ),
                       std::string( "Power " ) + Utility::toString(WrappedN::value) + " Distribution" );
  FRENSIE_CHECK_EQUAL( Utility::PowerDistribution<WrappedN::value>::typeName( false ),
                       std::string( "Power" ) + Utility::toString(WrappedN::value) );
  FRENSIE_CHECK_EQUAL( Utility::typeName<Utility::PowerDistribution<WrappedN::value> >(),
                       std::string( "Power" ) + Utility::toString(WrappedN::value) + "Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            getDistributionTypeName,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>::typeName( true, false, " " )),
                       std::string( "Power " ) + Utility::toString(WrappedN::value) + " Distribution" );
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>::typeName( false )),
                       std::string( "Power" ) + Utility::toString(WrappedN::value) );
  FRENSIE_CHECK_EQUAL( (Utility::typeName<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >()),
                       (std::string( "UnitAwarePower" ) + Utility::toString(WrappedN::value) + "Distribution<" + Utility::typeName<cgs::length,si::amount>()+">") );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, isTabular, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, isTabular, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, isContinuous, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            isContinuous,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with an interpolation type
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            isCompatibleWithInterpType,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::PowerDistribution<WrappedN::value> test_dist( 1.0, 1.0, 2.0 );

  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            isCompatibleWithInterpType,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>
    test_dist( 1.0, 1.0*si::meter, 2.0*si::meter );

  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, toString, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  std::string dist_string = Utility::toString( Utility::PowerDistribution<WrappedN::value>() );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::PowerDistribution<WrappedN::value>( 2.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+type_name+", 1.000000000000000000e+00, 2.000000000000000000e+00, 2.000000000000000000e+00}" );

  initializeDistribution<WrappedN::value,void,void>( distribution );

  dist_string = Utility::toString( *distribution );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, "+Utility::toString<double>(WrappedN::value+1)+"}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be converted to a string
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, toString, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  std::string dist_string = Utility::toString( Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>() );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter ) );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+type_name+", 1.000000000000000000e+00, 2.000000000000000000e+00, 2.000000000000000000e+00}" );

  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  dist_string = Utility::toString( *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, "+Utility::toString<double>(WrappedN::value+1)+"}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, toStream, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  std::ostringstream oss;
  Utility::toStream( oss, Utility::PowerDistribution<WrappedN::value>() );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::PowerDistribution<WrappedN::value>( 2.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 1.000000000000000000e+00, 2.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  initializeDistribution<WrappedN::value,void,void>( distribution );

  Utility::toStream( oss, *distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, "+Utility::toString<double>(WrappedN::value+1)+"}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, toStream, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  std::ostringstream oss;
  Utility::toStream( oss, Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>() );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter ) );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 1.000000000000000000e+00, 2.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  Utility::toStream( oss, *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, "+Utility::toString<double>(WrappedN::value+1)+"}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, ostream_operator, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  std::ostringstream oss;
  oss << Utility::PowerDistribution<WrappedN::value>();

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::PowerDistribution<WrappedN::value>( 2.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 1.000000000000000000e+00, 2.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  initializeDistribution<WrappedN::value,void,void>( distribution );

  oss << *distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, "+Utility::toString<double>(WrappedN::value+1)+"}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            ostream_operator,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  std::ostringstream oss;
  oss << Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>();

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 1.000000000000000000e+00, 2.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  oss << *unit_aware_distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+type_name+", 0.000000000000000000e+00, 1.000000000000000000e+00, "+Utility::toString<double>(WrappedN::value+1)+"}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a string
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, fromString, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  Utility::PowerDistribution<WrappedN::value> test_dist =
    Utility::fromString<Utility::PowerDistribution<WrappedN::value> >( std::string("{")+type_name+"}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::PowerDistribution<WrappedN::value>() );

  test_dist = Utility::fromString<Utility::PowerDistribution<WrappedN::value> >( std::string("{")+type_name+", 1.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::PowerDistribution<WrappedN::value>( 1.0, 1.0, 2.0 ) );

  test_dist = Utility::fromString<Utility::PowerDistribution<WrappedN::value> >( std::string("{")+type_name+", 1.0, 2.0, 3.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::PowerDistribution<WrappedN::value>( 3.0, 1.0, 2.0 ) );

  initializeDistribution<WrappedN::value,void,void>( distribution );

  test_dist = Utility::fromString<Utility::PowerDistribution<WrappedN::value> >( Utility::toString( *distribution ) );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::PowerDistribution<WrappedN::value>*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a string
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, fromString, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> test_dist =
    Utility::fromString<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >( std::string("{")+type_name+"}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>()) );

  test_dist = Utility::fromString<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >( std::string("{")+type_name+", 1.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 1.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  test_dist = Utility::fromString<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >( std::string("{")+type_name+", 1.0, 2.0, 3.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 3.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  test_dist = Utility::fromString<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >( Utility::toString( *unit_aware_distribution ) );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, fromStream, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  std::istringstream iss( std::string("{")+type_name+"}" );
  
  Utility::PowerDistribution<WrappedN::value> test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::PowerDistribution<WrappedN::value>() );

  iss.str( std::string("{")+type_name+", 1.0, 2.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::PowerDistribution<WrappedN::value>( 1.0, 1.0, 2.0 ) );

  iss.str( std::string("{")+type_name+", 1.0, 2.0, 3.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::PowerDistribution<WrappedN::value>( 3.0, 1.0, 2.0 ) );

  initializeDistribution<WrappedN::value,void,void>( distribution );

  iss.str( Utility::toString( *distribution ) );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::PowerDistribution<WrappedN::value>*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, fromStream, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  std::istringstream iss( std::string("{")+type_name+"}" );
  
  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> test_dist;
  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>()) );

  iss.str( std::string("{")+type_name+", 1.0, 2.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 1.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  iss.str( std::string("{")+type_name+", 1.0, 2.0, 3.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 3.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  iss.str( Utility::toString( *unit_aware_distribution ) );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, istream_operator, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  std::istringstream iss( std::string("{")+type_name+"}" );
  
  Utility::PowerDistribution<WrappedN::value> test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::PowerDistribution<WrappedN::value>() );

  iss.str( std::string("{")+type_name+", 1.0, 2.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::PowerDistribution<WrappedN::value>( 1.0, 1.0, 2.0 ) );

  iss.str( std::string("{")+type_name+", 1.0, 2.0, 3.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::PowerDistribution<WrappedN::value>( 3.0, 1.0, 2.0 ) );

  initializeDistribution<WrappedN::value,void,void>( distribution );

  iss.str( Utility::toString( *distribution ) );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::PowerDistribution<WrappedN::value>*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            istream_operator,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  std::istringstream iss( std::string("{")+type_name+"}" );
  
  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> test_dist;
  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>()) );

  iss.str( std::string("{")+type_name+", 1.0, 2.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 1.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  iss.str( std::string("{")+type_name+", 1.0, 2.0, 3.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 3.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  iss.str( Utility::toString( *unit_aware_distribution ) );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be writted to a property tree
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, toPropertyTree, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", Utility::PowerDistribution<WrappedN::value>() );

  Utility::PowerDistribution<WrappedN::value> copy_dist =
    ptree.get<Utility::PowerDistribution<WrappedN::value> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PowerDistribution<WrappedN::value>() );

  ptree.put( "test distribution", Utility::PowerDistribution<WrappedN::value>( 2.0 ) );

  copy_dist = ptree.get<Utility::PowerDistribution<WrappedN::value> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PowerDistribution<WrappedN::value>( 2.0 ) );

  ptree.put( "test distribution", Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 ) );

  copy_dist = ptree.get<Utility::PowerDistribution<WrappedN::value> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 ) );

  initializeDistribution<WrappedN::value,void,void>( distribution );

  ptree.put( "test distribution", *distribution );

  copy_dist = ptree.get<Utility::PowerDistribution<WrappedN::value> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::PowerDistribution<WrappedN::value>*>( distribution.get() ) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::PowerDistribution<WrappedN::value>().toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::PowerDistribution<WrappedN::value> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PowerDistribution<WrappedN::value>() );

  ptree = Utility::PowerDistribution<WrappedN::value>().toPropertyTree( false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = Utility::PowerDistribution<WrappedN::value>( 2.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::PowerDistribution<WrappedN::value> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PowerDistribution<WrappedN::value>( 2.0 ) );

  ptree = Utility::PowerDistribution<WrappedN::value>( 2.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::PowerDistribution<WrappedN::value> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 ) );

  ptree = Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 2.0 );

  initializeDistribution<WrappedN::value,void,void>( distribution );

  ptree = distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::PowerDistribution<WrappedN::value> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::PowerDistribution<WrappedN::value>*>( distribution.get() ) );

  ptree = distribution->toPropertyTree( false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ),
                       (double)(WrappedN::value+1) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::PowerDistribution<WrappedN::value>(), true );

  copy_dist = ptree.get_value<Utility::PowerDistribution<WrappedN::value> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PowerDistribution<WrappedN::value>() );

  ptree = Utility::toPropertyTree( Utility::PowerDistribution<WrappedN::value>(), false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::PowerDistribution<WrappedN::value>( 2.0 ), true );

  copy_dist = ptree.get_value<Utility::PowerDistribution<WrappedN::value> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PowerDistribution<WrappedN::value>( 2.0 ) );

  ptree = Utility::toPropertyTree( Utility::PowerDistribution<WrappedN::value>( 2.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 ), true );

  copy_dist = ptree.get_value<Utility::PowerDistribution<WrappedN::value> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 ) );

  ptree = Utility::toPropertyTree( Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 2.0 );

  initializeDistribution<WrappedN::value,void,void>( distribution );

  ptree = Utility::toPropertyTree( *distribution, true );

  copy_dist = ptree.get_value<Utility::PowerDistribution<WrappedN::value> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::PowerDistribution<WrappedN::value>*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *distribution, false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ),
                       (double)(WrappedN::value+1) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be writted to a property tree
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            toPropertyTree,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::string type_name( "Power " );
  type_name += Utility::toString( WrappedN::value );
  type_name += " Distribution";

  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>()) );

  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> copy_dist =
    ptree.get<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>()) );

  ptree.put( "test distribution", Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 ) );

  copy_dist = ptree.get<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 )) );

  ptree.put( "test distribution", Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter ) );

  copy_dist = ptree.get<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  ptree.put( "test distribution", *unit_aware_distribution );

  copy_dist = ptree.get<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>*>( unit_aware_distribution.get() )) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>().toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>()) );

  ptree = Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>().toPropertyTree( false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 )) );

  ptree = Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  ptree = Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 2.0 );

  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  ptree = unit_aware_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = unit_aware_distribution->toPropertyTree( false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ),
                       (double)(WrappedN::value+1) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>(), true );

  copy_dist = ptree.get_value<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>()) );

  ptree = Utility::toPropertyTree( Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>(), false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 ), true );

  copy_dist = ptree.get_value<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter ), true );

  copy_dist = ptree.get_value<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 2.0 );

  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), type_name );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ),
                       (double)(WrappedN::value+1) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( PowerDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  FETCH_FROM_TABLE( std::string, dist_name );                           
  FETCH_FROM_TABLE( bool, valid_dist_rep );                             
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children ); 
  FETCH_FROM_TABLE( Utility::PowerDistribution<1>, expected_dist );     
                                                   
  Utility::PowerDistribution<1> dist;                         
  std::vector<std::string> unused_children;        

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FRENSIE_CHECK_NO_THROW(
              dist = Utility::fromPropertyTree<Utility::PowerDistribution<1> >(
                                      test_dists_ptree->get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW(
                     Utility::fromPropertyTree<Utility::PowerDistribution<1> >(
                                  test_dists_ptree->get_child( dist_name ) ), 
                     Utility::PropertyTreeConversionException );    
  }
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwarePowerDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  typedef Utility::UnitAwarePowerDistribution<1,cgs::length,si::amount> Distribution;
  
  FETCH_FROM_TABLE( std::string, dist_name );                           
  FETCH_FROM_TABLE( bool, valid_dist_rep );                             
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children ); 
  FETCH_FROM_TABLE( Distribution, expected_dist );     
                                                   
  Distribution dist;                         
  std::vector<std::string> unused_children;        

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FRENSIE_CHECK_NO_THROW( dist = Utility::fromPropertyTree<Distribution>(
                                      test_dists_ptree->get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::fromPropertyTree<Distribution>(
                                    test_dists_ptree->get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, archive, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  std::string archive_name( "test_power_dist" );
  archive_name += Utility::toString( WrappedN::value );
  archive_name += ".h5a";

  // Create and archive some power distributions
  {
    Utility::PowerDistribution<WrappedN::value> dist_a;
    Utility::PowerDistribution<WrappedN::value> dist_b( 2.0 );
    Utility::PowerDistribution<WrappedN::value> dist_c( 3.0, 1.0, 2.0 );
    initializeDistribution<WrappedN::value,void,void>( distribution );

    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_c ) );
    FRENSIE_REQUIRE_NO_THROW(
                          archive << BOOST_SERIALIZATION_NVP( distribution ) );
  }

  // Load the archived distribution
  Utility::HDF5IArchive archive( archive_name );

  Utility::PowerDistribution<WrappedN::value> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::PowerDistribution<WrappedN::value>() );

  Utility::PowerDistribution<WrappedN::value> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::PowerDistribution<WrappedN::value>( 2.0 ) );

  Utility::PowerDistribution<WrappedN::value> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, Utility::PowerDistribution<WrappedN::value>( 3.0, 1.0, 2.0 ) );

  std::shared_ptr<Utility::OneDDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::PowerDistribution<WrappedN::value>*>( shared_dist.get() ),
                       *dynamic_cast<Utility::PowerDistribution<WrappedN::value>*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, archive, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  std::string archive_name( "test_unit_aware_power_dist" );
  archive_name += Utility::toString( WrappedN::value );
  archive_name += ".h5a";

  // Create and archive some power distributions
  {
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_a;
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_b( 2.0 );
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_c( 3.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter );
    initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_c ) );
    FRENSIE_REQUIRE_NO_THROW(
               archive << BOOST_SERIALIZATION_NVP( unit_aware_distribution ) );
  }

  // Load the archived distribution
  Utility::HDF5IArchive archive( archive_name );

  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>()) );

  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 )) );

  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 3.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<cgs::length,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "unit_aware_distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>*>( shared_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwarePowerDistribution,
				   explicit_conversion_1,
                                   TestUnitTypeQuads )
{
  FETCH_TEMPLATE_PARAM( 0, RawIndepUnitA );
  FETCH_TEMPLATE_PARAM( 1, RawDepUnitA );
  FETCH_TEMPLATE_PARAM( 2, RawIndepUnitB );
  FETCH_TEMPLATE_PARAM( 3, RawDepUnitB );

  typedef typename std::remove_pointer<RawIndepUnitA>::type IndepUnitA;
  typedef typename std::remove_pointer<RawDepUnitA>::type DepUnitA;
  typedef typename std::remove_pointer<RawIndepUnitB>::type IndepUnitB;
  typedef typename std::remove_pointer<RawDepUnitB>::type DepUnitB;
  
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitA>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityA;

  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitB>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityB;

  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  initializeDistribution<1,void,void>( distribution );

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwarePowerDistribution<1,IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwarePowerDistribution<1,IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::PowerDistribution<1>*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwarePowerDistribution<1,IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.0 );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 0.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b( inv_indep_quantity_a );
  DepQuantityB dep_quantity_b( dep_quantity_a );

  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );

  Utility::setQuantity( indep_quantity_a, 1.0 );
  Utility::setQuantity( inv_indep_quantity_a, 2.0 );
  Utility::setQuantity( dep_quantity_a, 2.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwarePowerDistribution,
				   explicit_conversion_2,
                                   TestUnitTypeQuads )
{
  FETCH_TEMPLATE_PARAM( 0, RawIndepUnitA );
  FETCH_TEMPLATE_PARAM( 1, RawDepUnitA );
  FETCH_TEMPLATE_PARAM( 2, RawIndepUnitB );
  FETCH_TEMPLATE_PARAM( 3, RawDepUnitB );

  typedef typename std::remove_pointer<RawIndepUnitA>::type IndepUnitA;
  typedef typename std::remove_pointer<RawDepUnitA>::type DepUnitA;
  typedef typename std::remove_pointer<RawIndepUnitB>::type IndepUnitB;
  typedef typename std::remove_pointer<RawDepUnitB>::type DepUnitB;
  
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitA>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityA;

  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitB>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityB;

  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  initializeDistribution<2,void,void>( distribution );

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwarePowerDistribution<2,IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwarePowerDistribution<2,IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::PowerDistribution<2>*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwarePowerDistribution<2,IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.0 );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 0.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b( inv_indep_quantity_a );
  DepQuantityB dep_quantity_b( dep_quantity_a );

  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );

  Utility::setQuantity( indep_quantity_a, 1.0 );
  Utility::setQuantity( inv_indep_quantity_a, 3.0 );
  Utility::setQuantity( dep_quantity_a, 3.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dists_json_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_OPTION( "test_dists_json_file",
              boost::program_options::value<std::string>(&test_dists_json_file_name)->default_value(""),
              "Test distributions json file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Load the property tree from the json file
  test_dists_ptree.reset( new Utility::PropertyTree );

  std::ifstream test_dists_json_file( test_dists_json_file_name );
  test_dists_json_file >> *test_dists_ptree;
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPowerDistribution.cpp
//---------------------------------------------------------------------------//
