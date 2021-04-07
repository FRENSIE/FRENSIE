//---------------------------------------------------------------------------//
//!
//! \file   tstPolynomialDistribution.cpp
//! \author Alex Robinson
//! \brief  Polynomial distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_PolynomialDistribution.hpp"
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
  std::tuple<si::length,si::energy,cgs::length,cgs::energy>,
  std::tuple<cgs::length,cgs::energy,si::length,si::energy>,
  std::tuple<si::length,si::mass,cgs::length,cgs::mass>,
  std::tuple<cgs::length,cgs::mass,si::length,si::mass>,
  std::tuple<si::length,void*,cgs::length,void*>,
  std::tuple<cgs::length,void*,si::length,void*>,
  std::tuple<void*,si::mass,void*,cgs::mass>,
  std::tuple<void*,cgs::mass,void*,si::mass>,
  std::tuple<si::length,si::dimensionless,cgs::length,cgs::dimensionless>,
  std::tuple<cgs::length,cgs::dimensionless,si::length,si::dimensionless>,
  std::tuple<si::dimensionless,si::length,cgs::dimensionless,cgs::length>,
  std::tuple<cgs::dimensionless,cgs::length,si::dimensionless,si::length>
 > TestUnitTypeQuads;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Utility::UnivariateDistribution> distribution;

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( PolynomialDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5 ), 2.75 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), 6.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV ),
		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5*MeV ),
		       2.75*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV ),
		       6.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( PolynomialDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.5 ), 2.75/3.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( -1.0*MeV ),
		       0.0/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.5*MeV ),
		       (2.75/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
		       2.0/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 2.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( PolynomialDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.5 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, sqrt(0.5) );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, pow( 0.5, 1.0/3.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.5*MeV );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, sqrt(0.5)*MeV );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, pow( 0.5, (1.0/3.0) )*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( PolynomialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.5 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, sqrt(0.5) );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, pow( 0.5, 1.0/3.0 ) );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<MegaElectronVolt> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.5*MeV );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, sqrt(0.5)*MeV );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, pow( 0.5, 1.0/3.0 )*MeV );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( PolynomialDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( PolynomialDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::POLYNOMIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::POLYNOMIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( PolynomialDistribution, isTabular )
{
  FRENSIE_CHECK( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, isTabular )
{
  FRENSIE_CHECK( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( PolynomialDistribution, isContinuous )
{
  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( PolynomialDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  std::vector<double> coeffs( 4 );
  coeffs[0] = 1.0;
  coeffs[1] = 2.0;
  coeffs[2] = 3.0;
  coeffs[3] = 0.0;

  std::shared_ptr<Utility::PolynomialDistribution>
    test_dist( new Utility::PolynomialDistribution( coeffs, 1.0, 2.0 ) );

  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is only compatible with lin-lin interp
  coeffs[0] = 0.0;

  test_dist.reset( new Utility::PolynomialDistribution( coeffs, 0.0, 1.0 ) );

  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !test_dist->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !test_dist->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution,
                   isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  std::vector<double> coeffs( 4 );
  coeffs[0] = 1.0;
  coeffs[1] = 2.0;
  coeffs[2] = 3.0;
  coeffs[3] = 0.0;

  std::shared_ptr<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> >
    test_dist( new Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( coeffs, 1.0*MeV, 2.0*MeV ) );

  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is only compatible with lin-lin interp
  coeffs[0] = 0.0;

  test_dist.reset( new Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( coeffs, 0.0*MeV, 1.0*MeV ) );

  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !test_dist->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !test_dist->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be placed in a stream
FRENSIE_UNIT_TEST( PolynomialDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::PolynomialDistribution();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["coefficients"].toType<std::vector<double> >(),
                       std::vector<double>({1.0}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::PolynomialDistribution( {0.0, 1.0, 0.0, 1.0} );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["coefficients"].toType<std::vector<double> >(),
                       std::vector<double>({0.0, 1.0, 0.0, 1.0}) );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 1.0 );

  oss.str( "" );
  oss.clear();

  oss << Utility::PolynomialDistribution( {0.0, 1.0, 0.0, 1.0}, 1.0, 2.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["coefficients"].toType<std::vector<double> >(),
                       std::vector<double>({0.0, 1.0, 0.0, 1.0}) );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 2.0 );

  oss.str( "" );
  oss.clear();

  oss << *distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["coefficients"].toType<std::vector<double> >(),
                       std::vector<double>({1.0, 2.0, 3.0, 0.0}) );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["coefficients"].toType<std::vector<double> >(),
                       std::vector<double>({1.0}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<MegaElectronVolt> >(),
                       0.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<MegaElectronVolt> >(),
                       1.0*MeV,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 0.0, 1.0} );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["coefficients"].toType<std::vector<double> >(),
                       std::vector<double>({0.0, 1.0, 0.0, 1.0}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<MegaElectronVolt> >(),
                       0.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<MegaElectronVolt> >(),
                       1.0*MeV,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 0.0, 1.0}, 1.0*MeV, 2.0*MeV );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["coefficients"].toType<std::vector<double> >(),
                       std::vector<double>({0.0, 1.0, 0.0, 1.0}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<MegaElectronVolt> >(),
                       1.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<MegaElectronVolt> >(),
                       2.0*MeV,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["coefficients"].toType<std::vector<double> >(),
                       std::vector<double>({1.0, 2.0, 3.0, 0.0}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<MegaElectronVolt> >(),
                       0.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<MegaElectronVolt> >(),
                       1.0*MeV,
                       SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PolynomialDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_polynomial_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some polynomial distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Utility::PolynomialDistribution dist_a( {3.0, 2.0, 1.0}, 1.0, 2.0 );

    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "dist_b", distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::PolynomialDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP(dist_a) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::PolynomialDistribution( {3.0, 2.0, 1.0}, 1.0, 2.0 ) );

  std::shared_ptr<Utility::UnivariateDistribution> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP(dist_b) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::PolynomialDistribution*>(dist_b.get()),
                       *dynamic_cast<Utility::PolynomialDistribution*>(distribution.get()) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwarePolynomialDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_unit_aware_polynomial_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some polynomial distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> dist_a( {3.0, 2.0, 1.0}, 1.0*MeV, 2.0*MeV );

    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "dist_b", unit_aware_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP(dist_a) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {3.0, 2.0, 1.0}, 1.0*MeV, 2.0*MeV )) );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount> > dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP(dist_b) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>*>(dist_b.get())),
                       (*dynamic_cast<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>*>(unit_aware_distribution.get())) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwarePolynomialDistribution,
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

  // Copy from a unitless distribution to distribution type A (static method)
  Utility::UnitAwarePolynomialDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwarePolynomialDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::PolynomialDistribution*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwarePolynomialDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1/3. );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 1.0 );

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
  Utility::setQuantity( dep_quantity_a, 6.0 );

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
  // Initialize the polynomial distribution
  std::vector<double> coeffs( 4 );
  coeffs[0] = 1.0;
  coeffs[1] = 2.0;
  coeffs[2] = 3.0;
  coeffs[3] = 0.0;

  distribution.reset( new Utility::PolynomialDistribution( coeffs, 0.0, 1.0 ));

  // Initialize the unit-aware polynomial distribution
  unit_aware_distribution.reset(
     new Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>(
						  coeffs, 0.0*eV, 1e6*eV ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPolynomialDistribution.cpp
//---------------------------------------------------------------------------//
