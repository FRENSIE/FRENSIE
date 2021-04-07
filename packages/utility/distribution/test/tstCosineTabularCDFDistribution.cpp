//---------------------------------------------------------------------------//
//!
//! \file   tstTabularCDFDistribution.cpp
//! \author Luke Kersting
//! \brief  TabularCDF distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_TabularCDFDistribution.hpp"
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

typedef std::tuple<Utility::LogLogCos,Utility::LinLogCos,Utility::LogNudgedLogCos,Utility::LinNudgedLogCos > InterpTypes;

typedef TestArchiveHelper::TestArchives TestArchives;

typedef std::tuple<
  std::tuple<si::dimensionless,si::amount,cgs::dimensionless,si::amount>,
  std::tuple<cgs::dimensionless,si::amount,si::dimensionless,si::amount>,
  std::tuple<void*,cgs::dimensionless,void*,si::dimensionless>
  > TestUnitTypeQuads;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Utility::UnivariateDistribution> distribution;
std::shared_ptr<Utility::TabularUnivariateDistribution> tab_distribution;

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<cgs::dimensionless,si::amount> >
  unit_aware_distribution;
std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<cgs::dimensionless,si::amount> >
  unit_aware_tab_distribution;

double norm_const = 1.0/1.999999;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the pdf distribution
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
  Utility::setQuantity( dependent_values[0], 1.0 );
  Utility::setQuantity( dependent_values[1], 1.0 );
  Utility::setQuantity( dependent_values[2], 1.0 );
  Utility::setQuantity( dependent_values[3], 1.0 );

  dist.reset(new Utility::UnitAwareTabularCDFDistribution<InterpolationPolicy,typename BaseDistribution::IndepUnit, typename BaseDistribution::DepUnit>(
                                                          independent_values,
                                                          dependent_values ) );
}

//---------------------------------------------------------------------------//
// Initialize the cdf distribution
template<typename InterpolationPolicy, typename BaseDistribution>
void initializeCDF( std::shared_ptr<BaseDistribution>& dist )
{
  // Use the basic constructor
  std::vector<typename BaseDistribution::IndepQuantity>
    independent_values( 4 );
  Utility::setQuantity( independent_values[0], -1.0 );
  Utility::setQuantity( independent_values[1], 0.0 );
  Utility::setQuantity( independent_values[2], 0.5 );
  Utility::setQuantity( independent_values[3], 0.999999 );

  std::vector<double> dependent_values( 4 );
  dependent_values[0] = 0.0;
  dependent_values[1] = 1e-1;
  dependent_values[2] = 1.0;
  dependent_values[3] = 1e2;

  dist.reset(new Utility::UnitAwareTabularCDFDistribution<InterpolationPolicy,typename BaseDistribution::IndepUnit, typename BaseDistribution::DepUnit>(
                                                          independent_values,
                                                          dependent_values,
                                                          true ) );
}

//---------------------------------------------------------------------------//
// Initialize the cdf distribution
template<typename InterpolationPolicy, typename BaseDistribution>
void initializeUnitAwareCDF( std::shared_ptr<BaseDistribution>& dist )
{
  // Use the basic constructor
  std::vector<typename BaseDistribution::IndepQuantity>
    independent_values( 4 );
  Utility::setQuantity( independent_values[0], -1.0 );
  Utility::setQuantity( independent_values[1], 0.0 );
  Utility::setQuantity( independent_values[2], 0.5 );
  Utility::setQuantity( independent_values[3], 0.999999 );

  std::vector<double> dependent_values( 4 );
  dependent_values[0] = 0.0;
  dependent_values[1] = 1e-1;
  dependent_values[2] = 1.0;
  dependent_values[3] = 1e2;

  dist.reset(new Utility::UnitAwareTabularCDFDistribution<InterpolationPolicy,typename BaseDistribution::IndepUnit, typename BaseDistribution::DepUnit>(
                                                          independent_values,
                                                          dependent_values ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            evaluate,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1e-3 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), 0.0 );

  initializeCDF<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1e-3 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            evaluate,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.001*cgs::dimensionless() ),
    0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*cgs::dimensionless() ),
    0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.999999*cgs::dimensionless() ),
    0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.001*cgs::dimensionless() ),
    0.0*si::mole );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.001*cgs::dimensionless() ),
    0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*cgs::dimensionless() ),
    0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.999999*cgs::dimensionless() ),
    0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.001*cgs::dimensionless() ),
    0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            evaluatePDF,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1e-3 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 0.0 );

  initializeCDF<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1e-3 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            evaluatePDF,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( -1.001*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF(1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 1.001*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( -1.001*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF(1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 1.001*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            evaluateCDF,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( tab_distribution );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -1.001 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( -1.0 ), 0.0, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.0 ), norm_const, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.5 ), 1.5*norm_const, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1.0 ), 1.0, 1e-10 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 1.001 ), 1.0 );

  initializeCDF<InterpolationPolicy>( tab_distribution );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -1.001 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( -1.0 ), 0.0, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.0 ), 1e-3, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.5 ), 1e-2, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1.0 ), 1.0, 1e-10 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 1.001 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            evaluateCDF,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( -1.001*cgs::dimensionless() ),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( -1.0*cgs::dimensionless() ),
                          0.0,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.0*cgs::dimensionless() ),
                          norm_const,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.5*cgs::dimensionless() ),
                          1.5*norm_const,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.999999*cgs::dimensionless() ),
                          1.0,
                          1e-10 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 1.001*cgs::dimensionless() ),
                       1.0 );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_tab_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( -1.001*cgs::dimensionless() ),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( -1.0*cgs::dimensionless() ),
                          0.0,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.0*cgs::dimensionless() ),
                          1e-3,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.5*cgs::dimensionless() ),
                          1e-2,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.999999*cgs::dimensionless() ),
                          1.0,
                          1e-10 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 1.001*cgs::dimensionless() ),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            sample,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sample();
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999 );

  initializeCDF<InterpolationPolicy>( distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-12 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5, 1e-12 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sample();
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            sample,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999*cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999*cgs::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            sampleAndRecordTrials,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  initializeCDF<InterpolationPolicy>( distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( 4.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( 5.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5, 1e-12 );
  FRENSIE_CHECK_EQUAL( 6.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
  FRENSIE_CHECK_EQUAL( 7.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999 );
  FRENSIE_CHECK_EQUAL( 8.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            sampleAndRecordTrials,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<cgs::dimensionless> sample =
  unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( 4.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( 5.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            sampleAndRecordBinIndex,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  size_t bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999 );

  initializeCDF<InterpolationPolicy>( tab_distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5, 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            sampleAndRecordBinIndex,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  size_t bin_index;

  quantity<cgs::dimensionless> sample =
  unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999*cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_tab_distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.999999*cgs::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            sampleWithRandomNumber,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( tab_distribution );

  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );

  initializeCDF<InterpolationPolicy>( tab_distribution );

  sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-12 );

  sample = tab_distribution->sampleWithRandomNumber( 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5, 1e-12 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            sampleWithRandomNumber,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<cgs::dimensionless> sample =
  unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_tab_distribution );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            sampleInSubrange,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.5 );

  initializeCDF<InterpolationPolicy>( tab_distribution );

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-1;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-12 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            sampleInSubrange,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
  unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless()  );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless() );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.5*cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_tab_distribution );

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-1;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless()  );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless() );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 0.5*cgs::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            sampleWithRandomNumberInSubrange,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( tab_distribution );

  double sample =
  tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5, 1e-12 );

  initializeCDF<InterpolationPolicy>( tab_distribution );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1e-1, 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-12 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            sampleWithRandomNumberInSubrange,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<cgs::dimensionless> sample =
  unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
              0.0, 0.5*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
              1.0, 0.5*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_tab_distribution );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
              0.0, 0.5*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
              1e-1, 0.5*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
              1.0, 0.5*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            getUpperBoundOfIndepVar,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(),0.999999 );

  initializeCDF<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(),0.999999 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            getUpperBoundOfIndepVar,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
    0.999999*cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
    0.999999*cgs::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            getLowerBoundOfIndepVar,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), -1.0 );

  initializeCDF<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            getLowerBoundOfIndepVar,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
    -1.0*cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
    -1.0*cgs::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            getDistributionType,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
    Utility::TABULAR_CDF_DISTRIBUTION );

  initializeCDF<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
    Utility::TABULAR_CDF_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            getDistributionType,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
    Utility::TABULAR_CDF_DISTRIBUTION );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
    Utility::TABULAR_CDF_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            isTabular,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isTabular() );

  initializeCDF<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            isTabular,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isTabular() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            isContinuous,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isContinuous() );

  initializeCDF<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            isContinuous,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST_TEMPLATE( TabularCDFDistribution,
                            isCompatibleWithInterpType,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLogCos >() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLogCos >() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogCosLog >() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogCosLin >() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogNudgedLogCos >() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinNudgedLogCos >() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::NudgedLogCosLog >() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::NudgedLogCosLin >() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );

  // if( boost::is_same<InterpolationPolicy,Utility::LogLogCos>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LinLogCos>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
  // }

  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogCosLin>() );
  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );

  initializeCDF<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLogCos >() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLogCos >() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogCosLog >() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogCosLin >() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );

  // if( boost::is_same<InterpolationPolicy,Utility::LogLogCos>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LinLogCos>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
  // }

  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogCosLin>() );
  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularCDFDistribution,
                            isCompatibleWithInterpType,
                            InterpTypes )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLogCos >() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLogCos >() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLog >() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLin >() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );

  // if( boost::is_same<InterpolationPolicy,Utility::LogLogCos>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LinLogCos>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
  // }

  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLin>() );
  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLogCos >() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLogCos >() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLog >() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLin >() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );

  // if( boost::is_same<InterpolationPolicy,Utility::LogLogCos>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LinLogCos>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
  // }

  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLin>() );
  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareTabularCDFDistribution,
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

  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;

  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  initializeCDF<Utility::LogLogCos >( distribution );

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::TabularCDFDistribution<Utility::LogLogCos >*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,IndepUnitB,DepUnitB>
  unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
  Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  double cdf_quantity_a =
  Utility::QuantityTraits<double>::initializeQuantity( 1e-3 );
  DepQuantityA dep_quantity_a =
  Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 0.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  double cdf_quantity_b( cdf_quantity_a );
  DepQuantityB dep_quantity_b( dep_quantity_a );

  FRENSIE_CHECK_FLOATING_EQUALITY(
      unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
      dep_quantity_a,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      unit_aware_dist_a_copy.evaluateCDF( indep_quantity_a ),
      cdf_quantity_a,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
      dep_quantity_b,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      unit_aware_dist_b_copy.evaluateCDF( indep_quantity_b ),
      cdf_quantity_b,
      1e-15 );

  Utility::setQuantity( indep_quantity_a, 0.5 );
  Utility::setQuantity( cdf_quantity_a, 1e-2 );
  Utility::setQuantity( dep_quantity_a, 0.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  cdf_quantity_b = cdf_quantity_a;
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  FRENSIE_CHECK_FLOATING_EQUALITY(
      unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
      dep_quantity_a,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      unit_aware_dist_a_copy.evaluateCDF( indep_quantity_a ),
      cdf_quantity_a,
      1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
      dep_quantity_b,
      1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
      unit_aware_dist_b_copy.evaluateCDF( indep_quantity_b ),
      cdf_quantity_b,
      1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( TabularCDFDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_tabular_cdf_dist_cosine" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<Utility::UnivariateDistribution> base_dist_a;

    initialize<Utility::LogLogCos >( base_dist_a );

    std::shared_ptr<Utility::UnivariateDistribution> base_dist_b;

    initialize<Utility::LinLogCos >( base_dist_b );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( base_dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( base_dist_b ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::UnivariateDistribution> base_dist_a;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist_a ) );

  Utility::TabularUnivariateDistribution* downcast_base_dist =
    dynamic_cast<Utility::TabularUnivariateDistribution*>( base_dist_a.get() );

  FRENSIE_REQUIRE( downcast_base_dist != NULL );

  FRENSIE_CHECK_EQUAL( downcast_base_dist->evaluateCDF( -1.001 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( -1.0 ), 0.0, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 0.0 ), norm_const, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 0.5 ), 1.5*norm_const, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 1.0 ), 1.0, 1e-10 );
  FRENSIE_CHECK_EQUAL( downcast_base_dist->evaluateCDF( 1.001 ), 1.0 );

  std::shared_ptr<Utility::UnivariateDistribution> base_dist_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist_b ) );

  downcast_base_dist =
    dynamic_cast<Utility::TabularUnivariateDistribution*>( base_dist_b.get() );

  FRENSIE_REQUIRE( downcast_base_dist != NULL );

  FRENSIE_CHECK_EQUAL( downcast_base_dist->evaluateCDF( -1.001 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( -1.0 ), 0.0, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 0.0 ), norm_const, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 0.5 ), 1.5*norm_const, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 1.0 ), 1.0, 1e-10 );
  FRENSIE_CHECK_EQUAL( downcast_base_dist->evaluateCDF( 1.001 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareTabularCDFDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "unit_aware_test_tabular_cdf_dist_cosine" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<Utility::UnitAwareUnivariateDistribution<void,si::amount> > base_dist_a;

    initialize<Utility::LogLogCos >( base_dist_a );

    std::shared_ptr<Utility::UnitAwareUnivariateDistribution<void,si::amount> > base_dist_b;

    initialize<Utility::LinLogCos >( base_dist_b );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( base_dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( base_dist_b ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  std::cout << archive_ostream.str() << std::endl;

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<void,si::amount> > base_dist_a;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist_a ) );

  Utility::UnitAwareTabularUnivariateDistribution<void,si::amount>* downcast_base_dist =
    dynamic_cast<Utility::UnitAwareTabularUnivariateDistribution<void,si::amount>*>( base_dist_a.get() );

  FRENSIE_REQUIRE( downcast_base_dist != NULL );

  FRENSIE_CHECK_EQUAL( downcast_base_dist->evaluateCDF( -1.001*cgs::dimensionless() ),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( -1.0*cgs::dimensionless() ),
                          0.0,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 0.0*cgs::dimensionless() ),
                          norm_const,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 0.5*cgs::dimensionless() ),
                          1.5*norm_const,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 0.999999*cgs::dimensionless() ),
                          1.0,
                          1e-10 );
  FRENSIE_CHECK_EQUAL( downcast_base_dist->evaluateCDF( 1.001*cgs::dimensionless() ),
                       1.0 );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<void,si::amount> > base_dist_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist_b ) );

  downcast_base_dist =
    dynamic_cast<Utility::UnitAwareTabularUnivariateDistribution<void,si::amount>*>( base_dist_b.get() );

  FRENSIE_REQUIRE( downcast_base_dist != NULL );

  FRENSIE_CHECK_EQUAL( downcast_base_dist->evaluateCDF( -1.001*cgs::dimensionless() ),
                       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( -1.0*cgs::dimensionless() ),
                          0.0,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 0.0*cgs::dimensionless() ),
                          norm_const,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 0.5*cgs::dimensionless() ),
                          1.5*norm_const,
                          1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( downcast_base_dist->evaluateCDF( 0.999999*cgs::dimensionless() ),
                          1.0,
                          1e-10 );
  FRENSIE_CHECK_EQUAL( downcast_base_dist->evaluateCDF( 1.001*cgs::dimensionless() ),
                       1.0 );
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
// end tstTabularCDFDistribution.cpp
//---------------------------------------------------------------------------//
