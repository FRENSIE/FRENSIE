//---------------------------------------------------------------------------//
//!
//! \file   tstNormalDistribution.cpp
//! \author Alex Robinson
//! \brief  Normal distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_NormalDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
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
				 new Utility::NormalDistribution( 0.0, 1.0 ) );

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<cgs::length,si::amount> > unit_aware_distribution( new Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 0.0*si::meter, 0.01*si::meter, 0.5*si::mole, -Utility::QuantityTraits<quantity<si::length> >::inf(), Utility::QuantityTraits<quantity<si::length> >::inf() ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( NormalDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), exp( -4.0/2.0 ) );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -2.0 ), exp( -4.0/2.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*cgs::centimeter ),
		       0.5*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*cgs::centimeter ),
		       0.5*exp( -4.0/2.0 )*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -2.0*cgs::centimeter ),
		       0.5*exp( -4.0/2.0 )*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( NormalDistribution, evaluatePDF )
{
  double center_value = 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi );
  double off_center_value = center_value*exp( -4.0/2.0 );

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), center_value);
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), off_center_value );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -2.0 ), off_center_value );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, evaluatePDF )
{
  double center_value = 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*cgs::centimeter ),
		       center_value/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 2.0*cgs::centimeter ),
		       center_value*exp( -4.0/2.0 )/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( -2.0*cgs::centimeter ),
		       center_value*exp( -4.0/2.0 )/cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( NormalDistribution, sample_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::NormalDistribution::sample( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );

  sample = Utility::NormalDistribution::sample( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  sample = Utility::NormalDistribution::sample( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, sample_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample =
    Utility::UnitAwareNormalDistribution<cgs::length>::sample(
				    0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sample(
				    0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sample(
				    0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( NormalDistribution, sampleAndRecordTrials_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = Utility::NormalDistribution::sampleAndRecordTrials(
							    trials, 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = Utility::NormalDistribution::sampleAndRecordTrials(
							    trials, 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = Utility::NormalDistribution::sampleAndRecordTrials(
							    trials, 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, sampleAndRecordTrials_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<cgs::length> sample =
    Utility::UnitAwareNormalDistribution<cgs::length>::sampleAndRecordTrials(
			    trials, 0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sampleAndRecordTrials(
			    trials, 0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sampleAndRecordTrials(
			    trials, 0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( NormalDistribution, sample )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, sample )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( NormalDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( NormalDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       Utility::QuantityTraits<quantity<cgs::length> >::inf());
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( NormalDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(),
		       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       -Utility::QuantityTraits<quantity<cgs::length> >::inf());
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( NormalDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::NORMAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::NORMAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( NormalDistribution, isTabular )
{
  FRENSIE_CHECK( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, isTabular )
{
  FRENSIE_CHECK( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( NormalDistribution, isContinuous )
{
  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( NormalDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::NormalDistribution test_dist( 10.0, 1.0, 1.0, 19.0 );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UnitAwareNormalDistribution<cgs::length,si::amount>
    test_dist( 10.0*si::meter,
               1.0*si::meter,
               1.0*si::mole,
               1.0*si::meter,
               19.0*si::meter );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( NormalDistribution, ostream_operator )
{
  std::ostringstream oss;
  
  oss << Utility::NormalDistribution();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(),
                       -Utility::QuantityTraits<double>::inf(), SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(),
                       Utility::QuantityTraits<double>::inf(), SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::NormalDistribution( 2.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(),
                       -Utility::QuantityTraits<double>::inf(), SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(),
                       Utility::QuantityTraits<double>::inf(), SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::NormalDistribution( 2.0, 3.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toDouble(), 3.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(),
                       -Utility::QuantityTraits<double>::inf(), SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(),
                       Utility::QuantityTraits<double>::inf(), SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::NormalDistribution( 2.0, 3.0, 4.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toDouble(), 3.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(),
                       -Utility::QuantityTraits<double>::inf(), SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(),
                       Utility::QuantityTraits<double>::inf(), SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 4.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::NormalDistribution( -2.0, 3.0, 4.0, -1.0, 1.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toDouble(), -2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toDouble(), 3.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), -1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 4.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << *distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(),
                       -Utility::QuantityTraits<double>::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(),
                       Utility::QuantityTraits<double>::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, ostream_operator )
{
  std::ostringstream oss;
  
  oss << Utility::UnitAwareNormalDistribution<cgs::length,si::amount>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toType<quantity<cgs::length> >(),
                       0.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toType<quantity<cgs::length> >(),
                       1.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       -Utility::QuantityTraits<quantity<cgs::length> >::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       Utility::QuantityTraits<quantity<cgs::length> >::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       1.0*si::mole,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toType<quantity<cgs::length> >(),
                       2.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toType<quantity<cgs::length> >(),
                       1.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       -Utility::QuantityTraits<quantity<cgs::length> >::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       Utility::QuantityTraits<quantity<cgs::length> >::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       1.0*si::mole,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toType<quantity<cgs::length> >(),
                       2.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toType<quantity<cgs::length> >(),
                       3.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       -Utility::QuantityTraits<quantity<cgs::length> >::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       Utility::QuantityTraits<quantity<cgs::length> >::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       1.0*si::mole,
                       SHOW_LHS );
  
  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toType<quantity<cgs::length> >(),
                       2.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toType<quantity<cgs::length> >(),
                       3.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       -Utility::QuantityTraits<quantity<cgs::length> >::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       Utility::QuantityTraits<quantity<cgs::length> >::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       4.0*si::mole,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( -2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toType<quantity<cgs::length> >(),
                       -2.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toType<quantity<cgs::length> >(),
                       3.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       -1.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       1.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       4.0*si::mole,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["mean"].toType<quantity<cgs::length> >(),
                       0.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["standard dev"].toType<quantity<cgs::length> >(),
                       1.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       -Utility::QuantityTraits<quantity<cgs::length> >::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       Utility::QuantityTraits<quantity<cgs::length> >::inf(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::amount> >(),
                       0.5*si::mole,
                       SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( NormalDistribution, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_normal_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some normal distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::NormalDistribution dist_a;
    Utility::NormalDistribution dist_b( 2.0 );
    Utility::NormalDistribution dist_c( 2.0, 3.0 );
    Utility::NormalDistribution dist_d( 2.0, 3.0, 4.0 );
    Utility::NormalDistribution dist_e( 2.0, 3.0, 4.0, -1.0 );
    Utility::NormalDistribution dist_f( 2.0, 3.0, 4.0, -1.0, 1.0 );

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
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_f ) );
    FRENSIE_REQUIRE_NO_THROW(
                          (*oarchive) << BOOST_SERIALIZATION_NVP( distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::NormalDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::NormalDistribution() );

  Utility::NormalDistribution dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::NormalDistribution( 2.0 ) );

  Utility::NormalDistribution dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, Utility::NormalDistribution( 2.0, 3.0 ) );

  Utility::NormalDistribution dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_d ) );
  FRENSIE_CHECK_EQUAL( dist_d, Utility::NormalDistribution( 2.0, 3.0, 4.0 ) );

  Utility::NormalDistribution dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_e ) );
  FRENSIE_CHECK_EQUAL( dist_e, Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0 ) );

  Utility::NormalDistribution dist_f;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_f ) );
  FRENSIE_CHECK_EQUAL( dist_f, Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0, 1.0 ) );

  std::shared_ptr<Utility::UnivariateDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::NormalDistribution*>( shared_dist.get() ),
                       *dynamic_cast<Utility::NormalDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareNormalDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_unit_aware_normal_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some normal distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_a;
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_b( 2.0*cgs::centimeter );
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_c( 2.0*cgs::centimeter, 3.0*cgs::centimeter );
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_d( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole );
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_e( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter );
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_f( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter );

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
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_f ) );
    FRENSIE_REQUIRE_NO_THROW(
               (*oarchive) << BOOST_SERIALIZATION_NVP( unit_aware_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );
  
  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>()) );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter )) );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter )) );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_d ) );
  FRENSIE_CHECK_EQUAL( dist_d, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole )) );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_e ) );
  FRENSIE_CHECK_EQUAL( dist_e, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter )) );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_f;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_f ) );
  FRENSIE_CHECK_EQUAL( dist_f, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<cgs::length,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "unit_aware_distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>*>( shared_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareNormalDistribution,
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
  Utility::UnitAwareNormalDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareNormalDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::NormalDistribution*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwareNormalDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi ) );
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

  Utility::setQuantity( indep_quantity_a, 2.0 );
  Utility::setQuantity( inv_indep_quantity_a, exp( -4.0/2.0 )/sqrt( 2.0*Utility::PhysicalConstants::pi ) );
  Utility::setQuantity( dep_quantity_a, exp( -4.0/2.0 ) );

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
// end tstNormalDistribution.cpp
//---------------------------------------------------------------------------//

