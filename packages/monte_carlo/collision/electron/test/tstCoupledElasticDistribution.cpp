//---------------------------------------------------------------------------//
//!
//! \file   tstCoupledElasticDistribution.cpp
//! \author Luke Kersting
//! \brief  Coupled elastic distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/dimensionless.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoupledElasticDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//
using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

typedef quantity<si::dimensionless> dl;

typedef std::tuple<Utility::LinLin,Utility::LogLin,Utility::LinNudgedLogCos,Utility::LogNudgedLogCos > InterpTypes;

typedef TestArchiveHelper::TestArchives TestArchives;

typedef std::tuple<
  std::tuple<si::dimensionless,si::amount,cgs::dimensionless,si::amount>,
  std::tuple<cgs::dimensionless,si::amount,si::dimensionless,si::amount>,
  std::tuple<si::dimensionless,si::length,cgs::dimensionless,cgs::length>,
  std::tuple<cgs::dimensionless,cgs::length,si::dimensionless,si::length>,
  std::tuple<si::dimensionless,si::mass,cgs::dimensionless,cgs::mass>,
  std::tuple<cgs::dimensionless,cgs::mass,si::dimensionless,si::mass>,
  std::tuple<si::dimensionless,si::dimensionless,cgs::dimensionless,cgs::dimensionless>,
  std::tuple<cgs::dimensionless,cgs::dimensionless,si::dimensionless,si::dimensionless>,
  std::tuple<si::dimensionless,void*,cgs::dimensionless,void*>,
  std::tuple<cgs::dimensionless,void*,si::dimensionless,void*>
  > TestUnitTypeQuads;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Utility::UnivariateDistribution> distribution;
std::shared_ptr<Utility::TabularUnivariateDistribution> tab_distribution;

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<si::dimensionless,si::amount> >
  unit_aware_distribution;
std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<si::dimensionless,si::amount> >
unit_aware_tab_distribution;

double eta = 1e-12;
double cross_section_ratio = 0.1;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<typename InterpolationPolicy, typename BaseDistribution>
void initialize( std::shared_ptr<BaseDistribution>& dist )
{
  // Use the basic constructor
  std::vector<typename BaseDistribution::IndepQuantity>
    independent_values( 4 );
  Utility::setQuantity( independent_values[0], -1.0 );
  Utility::setQuantity( independent_values[1], 0.0 );
  Utility::setQuantity( independent_values[2], 0.5 );
  Utility::setQuantity( independent_values[3], 0.999999 );

  std::vector<typename BaseDistribution::DepQuantity> dependent_values( 4 );
  Utility::setQuantity( dependent_values[0], 1e2 );
  Utility::setQuantity( dependent_values[1], 1e1 );
  Utility::setQuantity( dependent_values[2], 1.0 );
  Utility::setQuantity( dependent_values[3], 1e-1 );

  dist.reset(new MonteCarlo::UnitAwareCoupledElasticDistribution<InterpolationPolicy,typename BaseDistribution::IndepUnit, typename BaseDistribution::DepUnit>(
                                                      independent_values,
                                                      dependent_values,
                                                      eta,
                                                      cross_section_ratio ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            evaluate,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0 ), 1e1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5 ), 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 0.999999 ), 1e-2, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 1.0 ), 1.00000200000100021e+10, 1e-15 );

  double sample = distribution->evaluate( distribution->sample() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            evaluate,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0 ),
                       1e1*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0 ),
                       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5 ),
                       1e-1*si::mole );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.999999 ),
                                  1e-2*si::mole,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.0 ),
                                  1.00000200000100021e+10*si::mole,
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            evaluatePDF,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( -1.0 ),
                          1.7233951046594968293e-1,
                          1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 0.0 ),
                          1.7233951046594968293e-2,
                          1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 0.5 ),
                          1.7233951046594968293e-3,
                          1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 0.999999 ),
                          1.7233951046594968293e-4,
                          1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 1.0 ),
                          1.7233985514514300972e9,
                          1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            evaluatePDF,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                             unit_aware_distribution->evaluatePDF( -1.0*si::dimensionless() ),
                             1.7233951046594968293e-1/si::dimensionless(),
                             1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                             unit_aware_distribution->evaluatePDF( 0.0*si::dimensionless() ),
                             1.7233951046594968293e-2/si::dimensionless(),
                             1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                             unit_aware_distribution->evaluatePDF( 0.5*si::dimensionless() ),
                             1.7233951046594968293e-3/si::dimensionless(),
                             1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                              unit_aware_distribution->evaluatePDF( 0.999999*si::dimensionless() ),
                              1.7233951046594968293e-4/si::dimensionless(),
                              1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                              unit_aware_distribution->evaluatePDF( 1.0*si::dimensionless() ),
                              1.7233985514514300972e9/si::dimensionless(),
                              1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            evaluateCDF,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( tab_distribution );

  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( -1.0 ),
                          0.0000000000,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.0 ),
                          0.094786730756272336018,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.5 ),
                          0.09952606729408594588,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.999999 ),
                          0.1,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1.0 ),
                          1.0000000000,
                          1e-10 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            evaluateCDF,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( -1.0*si::dimensionless() ),
                          0.0000000000,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.0*si::dimensionless() ),
                          0.094786730756272336018,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.5*si::dimensionless() ),
                          0.09952606729408594588,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.999999*si::dimensionless() ),
                          0.1,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1.0*si::dimensionless() ),
                          1.0,
                          1e-10 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            sample,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = cross_section_ratio;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sample();
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            sample,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = cross_section_ratio;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<si::dimensionless> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0*si::dimensionless() );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*si::dimensionless(), 1e-12 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::dimensionless(), 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*si::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0*si::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            sampleAndRecordTrials,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = cross_section_ratio;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( 4.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            sampleAndRecordTrials,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = cross_section_ratio;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<si::dimensionless> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*si::dimensionless() );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*si::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*si::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0*si::dimensionless() );
  FRENSIE_CHECK_EQUAL( 4.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            sampleAndRecordBinIndex,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = cross_section_ratio;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  size_t bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 3u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 3u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            sampleAndRecordBinIndex,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = cross_section_ratio;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  size_t bin_index;

  quantity<si::dimensionless> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*si::dimensionless() );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*si::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 3u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 3u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*si::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0*si::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            sampleWithRandomNumber,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( tab_distribution );

  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( cross_section_ratio );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            sampleWithRandomNumber,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<si::dimensionless> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*si::dimensionless() );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( cross_section_ratio );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*si::dimensionless(), 1e-12 );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*si::dimensionless(), 1e-12 );

  double random_number = cross_section_ratio/2.0;
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( random_number );
  FRENSIE_CHECK_GREATER( sample.value(), -1.0 );
  FRENSIE_CHECK_LESS( sample.value(), 0.999999 );

  random_number = (1.0 - cross_section_ratio)/2.0;
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( random_number );
  FRENSIE_CHECK_GREATER( sample.value(), 0.999999 );
  FRENSIE_CHECK_LESS( sample.value(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            sampleInSubrange,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleInSubrange( 1e-1  );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleInSubrange( 1e-1 );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1e-1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            sampleInSubrange,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<si::dimensionless> sample =
    unit_aware_tab_distribution->sampleInSubrange( 1e-1*si::dimensionless()  );
  FRENSIE_CHECK_EQUAL( sample, -1.0*si::dimensionless() );

  sample = unit_aware_tab_distribution->sampleInSubrange( 1e-1*si::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1*si::dimensionless(), 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleInSubrange( 1e-1*si::dimensionless() );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*si::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1e-1*si::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            sampleWithRandomNumberInSubrange,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( tab_distribution );

  double sample =
    tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 1e-1  );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            sampleWithRandomNumberInSubrange,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<si::dimensionless> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
                                                               0.0, 1e-1*si::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*si::dimensionless() );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
                                                               1.0, 1e-1*si::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1*si::dimensionless(), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            getUpperBoundOfIndepVar,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            getUpperBoundOfIndepVar,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
                       1.0*si::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the cutoff bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            getCutoffBoundOfIndepVar,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::shared_ptr<MonteCarlo::CoupledElasticDistribution<InterpolationPolicy> >
                coupled_distribution;

  initialize<InterpolationPolicy>( coupled_distribution );

  FRENSIE_CHECK_EQUAL( coupled_distribution->getCutoffBoundOfIndepVar(), 0.999999 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            getCutoffBoundOfIndepVar,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

std::shared_ptr<MonteCarlo::UnitAwareCoupledElasticDistribution<InterpolationPolicy,si::dimensionless,si::amount> >
unit_aware_coupled_distribution;

  initialize<InterpolationPolicy>( unit_aware_coupled_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_coupled_distribution->getCutoffBoundOfIndepVar(),
                       0.999999*si::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            getLowerBoundOfIndepVar,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            getLowerBoundOfIndepVar,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
                       -1.0*si::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            getDistributionType,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
                       Utility::COUPLED_ELASTIC_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            getDistributionType,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
                       Utility::COUPLED_ELASTIC_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            isTabular,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            isTabular,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            isContinuous,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            isContinuous,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST_TEMPLATE( CoupledElasticDistribution,
                            isCompatibleWithInterpType,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogNudgedLogCos >() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinNudgedLogCos >() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );

  // if( boost::is_same<InterpolationPolicy,Utility::LinLin>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LinLog>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LogLin>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LogLog>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // }
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareCoupledElasticDistribution,
                            isCompatibleWithInterpType,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogNudgedLogCos >() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinNudgedLogCos >() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );

  // if( boost::is_same<InterpolationPolicy,Utility::LinLin>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LinLog>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LogLin>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LogLog>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // }
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareCoupledElasticDistribution,
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

  initialize<Utility::LinLin>( distribution );

  // Copy from unitless distribution to distribution type A
  MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinLin,IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinLin,IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<MonteCarlo::CoupledElasticDistribution<Utility::LinLin>*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinLin,IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.017233951046594968293 );
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

  Utility::setQuantity( indep_quantity_a, 0.5 );
  Utility::setQuantity( inv_indep_quantity_a, 0.0017233951046594968293 );
  Utility::setQuantity( dep_quantity_a, 0.1 );

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
                        1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                           unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
                           dep_quantity_b,
                           1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                        unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
                        inv_indep_quantity_b,
                        1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( CoupledElasticDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_coupled_elastic_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::CoupledElasticDistribution<Utility::LinLin> >
      concrete_dist;
    initialize<Utility::LinLin>( concrete_dist );

    std::shared_ptr<Utility::TabularUnivariateDistribution>
      intermediate_base_dist;

    initialize<Utility::LogLin>( intermediate_base_dist );

    std::shared_ptr<Utility::UnivariateDistribution>
      base_dist_a;

    initialize<Utility::LinNudgedLogCos >( base_dist_a );

    std::shared_ptr<Utility::UnivariateDistribution>
      base_dist_b;

    initialize<Utility::LogNudgedLogCos >( base_dist_b );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "concrete_dist", *concrete_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( intermediate_base_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( base_dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( base_dist_b ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::CoupledElasticDistribution<Utility::LinLin> concrete_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_dist ) );

  FRENSIE_CHECK_EQUAL( concrete_dist.evaluate( -1.0 ), 1e1 );
  FRENSIE_CHECK_EQUAL( concrete_dist.evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist.evaluate( 0.5 ), 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist.evaluate( 0.999999 ), 1e-2, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist.evaluate( 1.0 ), 1.00000200000100021e+10, 1e-15 );

  std::shared_ptr<Utility::TabularUnivariateDistribution>
    intermediate_base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( intermediate_base_dist ) );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( -1.0 ), 1e1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.5 ), 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 0.999999 ), 1e-2, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.0 ), 1.00000200000100021e+10, 1e-15 );

  std::shared_ptr<Utility::UnivariateDistribution> base_dist_a;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist_a ) );

  FRENSIE_CHECK_EQUAL( base_dist_a->evaluate( -1.0 ), 1e1 );
  FRENSIE_CHECK_EQUAL( base_dist_a->evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist_a->evaluate( 0.5 ), 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist_a->evaluate( 0.999999 ), 1e-2, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist_a->evaluate( 1.0 ), 1.00000200000100021e+10, 1e-15 );

  std::shared_ptr<Utility::UnivariateDistribution> base_dist_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist_b ) );

  FRENSIE_CHECK_EQUAL( base_dist_b->evaluate( -1.0 ), 1e1 );
  FRENSIE_CHECK_EQUAL( base_dist_b->evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist_b->evaluate( 0.5 ), 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist_b->evaluate( 0.999999 ), 1e-2, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist_b->evaluate( 1.0 ), 1.00000200000100021e+10, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareCoupledElasticDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_coupled_elastic_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinLin,si::dimensionless,si::amount> >
      concrete_dist;
    initialize<Utility::LinLin>( concrete_dist );

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<si::dimensionless,si::amount> >
      intermediate_base_dist;

    initialize<Utility::LogLin>( intermediate_base_dist );

    std::shared_ptr<Utility::UnitAwareUnivariateDistribution<si::dimensionless,si::amount> >
      base_dist_a;

    initialize<Utility::LinNudgedLogCos >( base_dist_a );

    std::shared_ptr<Utility::UnitAwareUnivariateDistribution<si::dimensionless,si::amount> >
      base_dist_b;

    initialize<Utility::LogNudgedLogCos >( base_dist_b );

    FRENSIE_CHECK_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "concrete_dist", *concrete_dist ) );
    FRENSIE_CHECK_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( intermediate_base_dist ) );
    FRENSIE_CHECK_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( base_dist_a ) );
    FRENSIE_CHECK_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( base_dist_b ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinLin,si::dimensionless,si::amount> concrete_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_dist ) );

  FRENSIE_CHECK_EQUAL( concrete_dist.evaluate( -1.0 ), 1e1*si::mole );
  FRENSIE_CHECK_EQUAL( concrete_dist.evaluate( 0.0 ), 1.0*si::mole );
  FRENSIE_CHECK_EQUAL( concrete_dist.evaluate( 0.5 ), 1e-1*si::mole );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist.evaluate( 0.999999 ), 1e-2*si::mole, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist.evaluate( 1.0 ), 1.00000200000100021e+10*si::mole, 1e-15 );

  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<si::dimensionless,si::amount> >
    intermediate_base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( intermediate_base_dist ) );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( -1.0 ), 1e1*si::mole );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0 ), 1.0*si::mole );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.5 ), 1e-1*si::mole );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 0.999999 ), 1e-2*si::mole, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.0 ), 1.00000200000100021e+10*si::mole, 1e-15 );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<si::dimensionless,si::amount> > base_dist_a;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist_a ) );

  FRENSIE_CHECK_EQUAL( base_dist_a->evaluate( -1.0 ), 1e1*si::mole );
  FRENSIE_CHECK_EQUAL( base_dist_a->evaluate( 0.0 ), 1.0*si::mole );
  FRENSIE_CHECK_EQUAL( base_dist_a->evaluate( 0.5 ), 1e-1*si::mole );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist_a->evaluate( 0.999999 ), 1e-2*si::mole, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist_a->evaluate( 1.0 ), 1.00000200000100021e+10*si::mole, 1e-15 );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<si::dimensionless,si::amount> > base_dist_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist_b ) );

  FRENSIE_CHECK_EQUAL( base_dist_b->evaluate( -1.0 ), 1e1*si::mole );
  FRENSIE_CHECK_EQUAL( base_dist_b->evaluate( 0.0 ), 1.0*si::mole );
  FRENSIE_CHECK_EQUAL( base_dist_b->evaluate( 0.5 ), 1e-1*si::mole );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist_b->evaluate( 0.999999 ), 1e-2*si::mole, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist_b->evaluate( 1.0 ), 1.00000200000100021e+10*si::mole, 1e-15 );
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
// end tstCoupledElasticDistribution.cpp
//---------------------------------------------------------------------------//
