//---------------------------------------------------------------------------//
//!
//! \file   tstExponentialDistribution.cpp
//! \author Alex Robinson
//! \brief  Histogram distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <cmath>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

typedef TestArchiveHelper::TestArchives TestArchives;

typedef std::tuple<
  std::tuple<si::energy,si::amount,cgs::energy,si::amount>,
  std::tuple<cgs::energy,si::amount,si::energy,si::amount>,
  std::tuple<si::energy,si::length,cgs::energy,cgs::length>,
  std::tuple<cgs::energy,cgs::length,si::energy,si::length>,
  std::tuple<si::energy,si::mass,cgs::energy,cgs::mass>,
  std::tuple<cgs::energy,cgs::mass,si::energy,si::mass>,
  std::tuple<si::energy,si::dimensionless,cgs::energy,cgs::dimensionless>,
  std::tuple<cgs::energy,cgs::dimensionless,si::energy,si::dimensionless>,
  std::tuple<si::energy,void*,cgs::energy,void*>,
  std::tuple<cgs::energy,void*,si::energy,void*>,
  std::tuple<ElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<ElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<ElectronVolt,si::amount,KiloElectronVolt,si::amount>,
  std::tuple<ElectronVolt,si::amount,MegaElectronVolt,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,ElectronVolt,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,MegaElectronVolt,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,ElectronVolt,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,KiloElectronVolt,si::amount>,
  std::tuple<void*,MegaElectronVolt,void*,KiloElectronVolt>
 > TestUnitTypeQuads;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Utility::UnivariateDistribution> distribution(
			     new Utility::ExponentialDistribution( 2.0, 3.0 ) );
std::shared_ptr<Utility::UnitAwareUnivariateDistribution<cgs::length,si::amount> > unit_aware_distribution( new Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>( 2.0*si::mole, 300.0/si::meter, 0.0*si::meter ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( ExponentialDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(distribution->evaluate( 1.0 ), 2.0*exp(-3.0), 1e-12);
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate(-1.0*cgs::centimeter),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*cgs::centimeter),
		       2.0*si::mole );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		       unit_aware_distribution->evaluate( 1.0*cgs::centimeter),
		       2.0*exp(-3.0)*si::mole,
		       1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( ExponentialDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(distribution->evaluatePDF(1.0), 3.0*exp(-3.0), 1e-12);
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL(
		  unit_aware_distribution->evaluatePDF( -1.0*cgs::centimeter ),
		  0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_distribution->evaluatePDF( 0.0*cgs::centimeter ),
		   3.0/cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		   unit_aware_distribution->evaluatePDF( 1.0*cgs::centimeter ),
		   3.0*exp(-3.0)/cgs::centimeter,
		   1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( ExponentialDistribution, sample_basic_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::ExponentialDistribution::sample( 3.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = Utility::ExponentialDistribution::sample( 3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );

  sample = Utility::ExponentialDistribution::sample( 3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -std::log(0.5)/3.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, sample_basic_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample =
    Utility::UnitAwareExponentialDistribution<cgs::length>::sample( 3.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = Utility::UnitAwareExponentialDistribution<cgs::length>::sample( 3.0/cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  11.5131919974469596*cgs::centimeter,
				  1e-15 );

  sample = Utility::UnitAwareExponentialDistribution<cgs::length>::sample( 3.0/cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -std::log(0.5)/3.0*cgs::centimeter,
				  1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( ExponentialDistribution, sample_static )
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
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = Utility::ExponentialDistribution::sample( 3.0, 0.0, inf );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );

  sample = Utility::ExponentialDistribution::sample( 3.0, 0.0, inf );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -std::log(0.5)/3.0, 1e-12 );

  sample = Utility::ExponentialDistribution::sample( 3.0, 1.0, inf );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.2310490601866484, 1e-12 );

  sample = Utility::ExponentialDistribution::sample( 3.0, 1.0, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.2148532763287345, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, sample_static )
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
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = Utility::UnitAwareExponentialDistribution<cgs::length>::sample(
			       3.0/cgs::centimeter, 0.0*cgs::centimeter, inf );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  11.5131919974469596*cgs::centimeter,
				  1e-15 );

  sample = Utility::UnitAwareExponentialDistribution<cgs::length>::sample(
			       3.0/cgs::centimeter, 0.0*cgs::centimeter, inf );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -std::log(0.5)/3.0*cgs::centimeter,
				  1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( ExponentialDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -std::log(0.5)/3.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  11.5131919974469596*cgs::centimeter,
				  1e-15 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -std::log(0.5)/3.0*cgs::centimeter,
				  1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( ExponentialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 11.5131919974469596, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -std::log(0.5)/3.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  11.5131919974469596*cgs::centimeter,
				  1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -std::log(0.5)/3.0*cgs::centimeter,
				  1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( ExponentialDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       Utility::QuantityTraits<quantity<cgs::length> >::inf());
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( ExponentialDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       Utility::QuantityTraits<quantity<cgs::length> >::zero());
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( ExponentialDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::EXPONENTIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::EXPONENTIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( ExponentialDistribution, isTabular )
{
  FRENSIE_CHECK( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, isTabular )
{
  FRENSIE_CHECK( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( ExponentialDistribution, isContinuous )
{
  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( ExponentialDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::ExponentialDistribution test_dist( 1.0, 1.0, 0.1, 1.0 );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution,
                   isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>
    test_dist( 1.0*si::mole, 1.0/si::meter, 0.1*si::meter, 1.0*si::meter );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be placed in a stream
FRENSIE_UNIT_TEST( ExponentialDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::ExponentialDistribution();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(),
                       Utility::QuantityTraits<double>::inf() );

  oss.str( "" );
  oss.clear();

  oss << Utility::ExponentialDistribution( 2.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 2.0 );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(),
                       Utility::QuantityTraits<double>::inf() );

  oss.str( "" );
  oss.clear();

  oss << Utility::ExponentialDistribution( 2.0, 3.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toDouble(), 3.0 );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 2.0 );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(),
                       Utility::QuantityTraits<double>::inf() );

  oss.str( "" );
  oss.clear();

  oss << Utility::ExponentialDistribution( 2.0, 3.0, 1.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toDouble(), 3.0 );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 2.0 );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(),
                       Utility::QuantityTraits<double>::inf() );

  oss.str( "" );
  oss.clear();

  oss << Utility::ExponentialDistribution( 2.0, 3.0, 1.0, 2.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toDouble(), 3.0 );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 2.0 );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 2.0 );

  oss.str( "" );
  oss.clear();

  oss << *distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toDouble(), 3.0 );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 2.0 );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(),
                       Utility::QuantityTraits<double>::inf() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareExponentialDistribution, ostream_operator )
{
  std::ostringstream oss;
  
  oss << Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toType<quantity<Utility::UnitTraits<cgs::length>::InverseUnit> >(),
                       1.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       Utility::QuantityTraits<quantity<cgs::length> >::inf() );
  
  oss.str( "" );
  oss.clear();
  
  oss << Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>( 2.0*si::mole );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toType<quantity<Utility::UnitTraits<cgs::length>::InverseUnit> >(),
                       1.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       Utility::QuantityTraits<quantity<cgs::length> >::inf() );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>( 2.0*si::mole, 3.0/cgs::centimeter );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toType<quantity<Utility::UnitTraits<cgs::length>::InverseUnit> >(),
                       3.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       Utility::QuantityTraits<quantity<cgs::length> >::inf() );
  
  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>( 2.0*si::mole, 3.0/cgs::centimeter, 1.0*cgs::centimeter );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toType<quantity<Utility::UnitTraits<cgs::length>::InverseUnit> >(),
                       3.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       Utility::QuantityTraits<quantity<cgs::length> >::inf() );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>( 2.0*si::mole, 3.0/cgs::centimeter, 1.0*cgs::centimeter, 2.0*cgs::centimeter );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toType<quantity<Utility::UnitTraits<cgs::length>::InverseUnit> >(),
                       3.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       2.0*cgs::centimeter );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_distribution;
  
  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Exponential Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["exponent multiplier"].toType<quantity<Utility::UnitTraits<cgs::length>::InverseUnit> >(),
                       3.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       Utility::QuantityTraits<quantity<cgs::length> >::inf() );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ExponentialDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_exponential_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some exponential distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::ExponentialDistribution dist_a;
    Utility::ExponentialDistribution dist_b( 2.0 );
    Utility::ExponentialDistribution dist_c( 2.0, 3.0 );
    Utility::ExponentialDistribution dist_d( 2.0, 3.0, 1.0 );
    Utility::ExponentialDistribution dist_e( 2.0, 3.0, 1.0, 2.0 );

    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_c ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_d ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_e ) );
    FRENSIE_REQUIRE_NO_THROW(
                      (*oarchive) << BOOST_SERIALIZATION_NVP( distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );
  
  Utility::ExponentialDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::ExponentialDistribution() );

  Utility::ExponentialDistribution dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::ExponentialDistribution( 2.0 ) );

  Utility::ExponentialDistribution dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, Utility::ExponentialDistribution( 2.0, 3.0 ) );
  FRENSIE_CHECK_EQUAL( dist_c.evaluatePDF( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( dist_c.evaluatePDF( 0.0 ), 3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(dist_c.evaluatePDF(1.0), 3.0*exp(-3.0), 1e-12);

  Utility::ExponentialDistribution dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_d ) );
  FRENSIE_CHECK_EQUAL( dist_d, Utility::ExponentialDistribution( 2.0, 3.0, 1.0 ) );

  Utility::ExponentialDistribution dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_e ) );
  FRENSIE_CHECK_EQUAL( dist_e, Utility::ExponentialDistribution( 2.0, 3.0, 1.0, 2.0 ) );

  std::shared_ptr<Utility::UnivariateDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::ExponentialDistribution*>( shared_dist.get() ),
                       *dynamic_cast<Utility::ExponentialDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareExponentialDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_unit_aware_exponential_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some exponential distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> dist_a;
    Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> dist_b( 2.0*si::mole );
    Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> dist_c( 2.0*si::mole, 3.0/cgs::centimeter );
    Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> dist_d( 2.0*si::mole, 3.0/cgs::centimeter, 1.0*cgs::centimeter );
    Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> dist_e( 2.0*si::mole, 3.0/cgs::centimeter, 1.0*cgs::centimeter, 2.0*cgs::centimeter );

    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_c ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_d ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_e ) );
    FRENSIE_REQUIRE_NO_THROW(
           (*oarchive) << BOOST_SERIALIZATION_NVP( unit_aware_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>()) );

  Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>( 2.0*si::mole )) );

  Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, (Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>( 2.0*si::mole, 3.0/cgs::centimeter )) );

  Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_d ) );
  FRENSIE_CHECK_EQUAL( dist_d, (Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>( 2.0*si::mole, 3.0/cgs::centimeter, 1.0*cgs::centimeter )) );

  Utility::UnitAwareExponentialDistribution<cgs::length,si::amount> dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_e ) );
  FRENSIE_CHECK_EQUAL( dist_e, (Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>( 2.0*si::mole, 3.0/cgs::centimeter, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<cgs::length,si::amount>> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "unit_aware_distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>*>( shared_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwareExponentialDistribution<cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareExponentialDistribution,
				   explicit_conversion,
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

  // Copy from unitless distribution to distribution type A (static method)
  Utility::UnitAwareExponentialDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareExponentialDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::ExponentialDistribution*>( distribution.get() ) );

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
  Utility::setQuantity( inv_indep_quantity_a, 3.0*exp(-3.0) );
  Utility::setQuantity( dep_quantity_a, 2.0*exp(-3.0) );

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

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstExponentialDistribution.cpp
//---------------------------------------------------------------------------//
