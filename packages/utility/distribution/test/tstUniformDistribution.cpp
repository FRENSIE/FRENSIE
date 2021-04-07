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
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_UniformDistribution.hpp"
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

std::shared_ptr<Utility::TabularUnivariateDistribution> tab_distribution(
			  new Utility::UniformDistribution( -1.0, 1.0, 2.0 ) );

std::shared_ptr<Utility::UnivariateDistribution> distribution = tab_distribution;

std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<si::energy,si::amount> >
  unit_aware_tab_distribution;

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<si::energy,si::amount> >
  unit_aware_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( UniformDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*si::joule ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*si::joule ),
  		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5*si::joule ),
  		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*si::joule ),
  		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*si::joule ),
  		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( UniformDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -1.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( -1.0*si::joule ),
  		       0.0/si::joule );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*si::joule ),
  		       1.0/si::joule );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.5*si::joule ),
  		       1.0/si::joule );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 1.0*si::joule ),
  		       1.0/si::joule );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 2.0*si::joule ),
  		       0.0/si::joule );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
FRENSIE_UNIT_TEST( UniformDistribution, evaluateCDF )
{
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 0.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 2.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware CDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, evaluateCDF )
{
  FRENSIE_CHECK_EQUAL(unit_aware_tab_distribution->evaluateCDF(-1.0*si::joule),
		      0.0 );
  FRENSIE_CHECK_EQUAL(unit_aware_tab_distribution->evaluateCDF(0.0*si::joule),
		      0.0 );
  FRENSIE_CHECK_EQUAL(unit_aware_tab_distribution->evaluateCDF(0.5*si::joule),
		      0.5 );
  FRENSIE_CHECK_EQUAL(unit_aware_tab_distribution->evaluateCDF(1.0*si::joule),
		      1.0 );
  FRENSIE_CHECK_EQUAL(unit_aware_tab_distribution->evaluateCDF(2.0*si::joule),
		      1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( UniformDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<si::energy> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*si::joule );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.5*si::joule );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled w/o an instance
FRENSIE_UNIT_TEST( UniformDistribution, sample_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::UniformDistribution::sample( -1.0, 1.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = Utility::UniformDistribution::sample( -1.0, 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = Utility::UniformDistribution::sample( -1.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled w/o an instance
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, sample_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<si::energy> sample =
    Utility::UnitAwareUniformDistribution<si::energy>::sample(
					        0.0*si::joule, 1.0*si::joule );
  FRENSIE_CHECK_EQUAL( sample, 0.0*si::joule );

  sample =
    Utility::UnitAwareUniformDistribution<si::energy>::sample(
					        0.0*si::joule, 1.0*si::joule );
  FRENSIE_CHECK_EQUAL( sample, 0.5*si::joule );

  sample =
    Utility::UnitAwareUniformDistribution<si::energy>::sample(
					        0.0*si::joule, 1.0*si::joule );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( UniformDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<si::energy> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*si::joule );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.5*si::joule );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled w/o an instance
FRENSIE_UNIT_TEST( UniformDistribution, sampleAndRecordTrials_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = Utility::UniformDistribution::sampleAndRecordTrials(
							   -1.0, 1.0, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = Utility::UniformDistribution::sampleAndRecordTrials(
							   -1.0, 1.0, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = Utility::UniformDistribution::sampleAndRecordTrials(
							   -1.0, 1.0, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled w/o an instance
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, sampleAndRecordTrials_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<si::energy> sample = Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleAndRecordTrials(
				        0.0*si::joule, 1.0*si::joule, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*si::joule );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample =
    Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleAndRecordTrials(
				        0.0*si::joule, 1.0*si::joule, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.5*si::joule );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample =
    Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleAndRecordTrials(
				        0.0*si::joule, 1.0*si::joule, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( UniformDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  size_t bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0.0 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0.0 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  size_t bin_index;

  quantity<si::energy> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*si::joule );
  FRENSIE_CHECK_EQUAL( bin_index, 0.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.5*si::joule );
  FRENSIE_CHECK_EQUAL( bin_index, 0.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( UniformDistribution, sampleWithRandomNumber )
{
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, sampleWithRandomNumber )
{
  quantity<si::energy> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*si::joule );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.5*si::joule );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled w/o an instance
FRENSIE_UNIT_TEST( UniformDistribution, sampleWithRandomNumber_static )
{
  double sample = Utility::UniformDistribution::sampleWithRandomNumber(
							      -1.0, 1.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = Utility::UniformDistribution::sampleWithRandomNumber(
							      -1.0, 1.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = Utility::UniformDistribution::sampleWithRandomNumber(
							      -1.0, 1.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled w/o an instance
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution,
		   sampleWithRandomNumber_static )
{
  quantity<si::energy> sample = Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleWithRandomNumber(
					   0.0*si::joule, 1.0*si::joule, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*si::joule );

  sample = Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleWithRandomNumber(
					   0.0*si::joule, 1.0*si::joule, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.5*si::joule );

  sample = Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleWithRandomNumber(
					   0.0*si::joule, 1.0*si::joule, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( UniformDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleInSubrange( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -0.5 );

  sample = tab_distribution->sampleInSubrange( 0.0 );
  FRENSIE_CHECK_SMALL( sample, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<si::energy> sample =
    unit_aware_tab_distribution->sampleInSubrange( 0.5*si::joule );
  FRENSIE_CHECK_EQUAL( sample, 0.0*si::joule );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*si::joule );
  FRENSIE_CHECK_EQUAL( sample, 0.25*si::joule );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*si::joule );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5*si::joule, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( UniformDistribution, sampleWithRandomNumberInSubrange )
{
  double sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -0.5 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution,
		   sampleWithRandomNumberInSubrange )
{
  quantity<si::energy> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
							  0.0, 0.5*si::joule );
  FRENSIE_CHECK_EQUAL( sample, 0.0*si::joule );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
							  0.5, 0.5*si::joule );
  FRENSIE_CHECK_EQUAL( sample, 0.25*si::joule );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
							  1.0, 0.5*si::joule );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5*si::joule, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( UniformDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       1.0*si::joule );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( UniformDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*si::joule );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( UniformDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::UNIFORM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::UNIFORM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( UniformDistribution, isTabular )
{
  FRENSIE_CHECK( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, isTabular )
{
  FRENSIE_CHECK( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( UniformDistribution, isContinuous )
{
  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( UniformDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UniformDistribution test_dist( 1.0, 2.0, 1.0 );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UnitAwareUniformDistribution<si::energy,si::amount>
    test_dist( 1.0*si::joule, 2.0*si::joule, 1.0*si::mole );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( UniformDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::UniformDistribution();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Uniform Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent value"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UniformDistribution( -2.0, 2.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Uniform Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent value"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), -2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 2.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UniformDistribution( -2.0, 2.0, 3.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Uniform Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent value"].toDouble(), 3.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), -2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 2.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << *distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Uniform Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent value"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), -1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 1.0, SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::UnitAwareUniformDistribution<si::energy,si::amount>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Uniform Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<si::energy>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent value"].toType<quantity<si::amount> >(),
                       1.0*si::mole,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<si::energy> >(),
                       0.0*si::joule,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<si::energy> >(),
                       1.0*si::joule,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareUniformDistribution<si::energy,si::amount>( -2.0*si::joule, 2.0*si::joule );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Uniform Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<si::energy>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent value"].toType<quantity<si::amount> >(),
                       1.0*si::mole,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<si::energy> >(),
                       -2.0*si::joule,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<si::energy> >(),
                       2.0*si::joule,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareUniformDistribution<si::energy,si::amount>( -2.0*si::joule, 2.0*si::joule, 3.0*si::mole );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Uniform Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<si::energy>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent value"].toType<quantity<si::amount> >(),
                       3.0*si::mole,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<si::energy> >(),
                       -2.0*si::joule,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<si::energy> >(),
                       2.0*si::joule,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Uniform Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<si::energy>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent value"].toType<quantity<si::amount> >(),
                       1.0*si::mole,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<si::energy> >(),
                       0.0*si::joule,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<si::energy> >(),
                       1.0*si::joule,
                       SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UniformDistribution, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_uniform_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::UniformDistribution dist_a( -1.0, 1.0, 0.5 );
    Utility::UniformDistribution dist_b( 0.0, 2.0, 1.0 );

    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
                  (*oarchive) << BOOST_SERIALIZATION_NVP( tab_distribution ) );
    FRENSIE_REQUIRE_NO_THROW(
                      (*oarchive) << BOOST_SERIALIZATION_NVP( distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::UniformDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  Utility::UniformDistribution dist_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::UniformDistribution( 0.0, 2.0, 1.0 ) );

  std::shared_ptr<Utility::TabularUnivariateDistribution> shared_tab_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "tab_distribution", shared_tab_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::UniformDistribution*>( shared_tab_dist.get() ),
                       *dynamic_cast<Utility::UniformDistribution*>( tab_distribution.get() ) );

  std::shared_ptr<Utility::UnivariateDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::UniformDistribution*>( shared_dist.get() ),
                       *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareUniformDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_uniform_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> dist_a( -1.0*si::joule, 1.0*si::joule, 0.5*si::mole );
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> dist_b( 0.0*si::joule, 2.0*si::joule, 1.0*si::mole );

    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
       (*oarchive) << BOOST_SERIALIZATION_NVP( unit_aware_tab_distribution ) );
    FRENSIE_REQUIRE_NO_THROW(
           (*oarchive) << BOOST_SERIALIZATION_NVP( unit_aware_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );
  
  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );
  
  Utility::UnitAwareUniformDistribution<si::energy,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareUniformDistribution<si::energy,si::amount>( -1.0*si::joule, 1.0*si::joule, 0.5*si::mole )) );

  Utility::UnitAwareUniformDistribution<si::energy,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwareUniformDistribution<si::energy,si::amount>( 0.0*si::joule, 2.0*si::joule, 1.0*si::mole )) );

  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<si::energy,si::amount> > shared_tab_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "unit_aware_tab_distribution", shared_tab_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( shared_tab_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_tab_distribution.get() )) );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<si::energy,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "unit_aware_distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( shared_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareUniformDistribution,
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
  Utility::UnitAwareUniformDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareUniformDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwareUniformDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( -1.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.5 );
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
  Utility::setQuantity( inv_indep_quantity_a, 0.5 );
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
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the unit-aware distributions
  unit_aware_tab_distribution.reset(
	     new Utility::UnitAwareUniformDistribution<si::energy,si::amount>(
				      quantity<si::energy>( 0.0*si::joule ),
				      quantity<si::energy>( 1.0*si::joule ),
				      quantity<si::amount>( 1.0*si::mole ) ) );

  unit_aware_distribution = unit_aware_tab_distribution;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstUniformDistribution.cpp
//---------------------------------------------------------------------------//

