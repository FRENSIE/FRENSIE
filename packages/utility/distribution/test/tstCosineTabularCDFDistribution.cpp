//---------------------------------------------------------------------------//
//!
//! \file   tstTabularCDFDistribution.cpp
//! \author Luke Kerting
//! \brief  TabularCDF distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
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
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_TabularCDFDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution;
Teuchos::RCP<Utility::TabularOneDDistribution> tab_distribution;

Teuchos::RCP<Utility::UnitAwareOneDDistribution<cgs::dimensionless,si::amount> >
  unit_aware_distribution;
Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<cgs::dimensionless,si::amount> >
  unit_aware_tab_distribution;

double norm_const = 1.0/1.999999;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )                    \
typedef Utility::LogLogCos LogLogCos;                            \
typedef Utility::LinLogCos LinLogCos;                            \
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LogLogCos )    \
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LinLogCos )

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the pdf distribution
template<typename InterpolationPolicy, typename BaseDistribution>
void initialize( Teuchos::RCP<BaseDistribution>& dist )
{
  // Use the basic constructor
  Teuchos::Array<typename BaseDistribution::IndepQuantity>
    independent_values( 4 );
  Utility::setQuantity( independent_values[0], -1.0 );
  Utility::setQuantity( independent_values[1], 0.0 );
  Utility::setQuantity( independent_values[2], 0.5 );
  Utility::setQuantity( independent_values[3], 0.999999 );

  Teuchos::Array<typename BaseDistribution::DepQuantity> dependent_values( 4 );
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
void initializeCDF( Teuchos::RCP<BaseDistribution>& dist )
{
  // Use the basic constructor
  Teuchos::Array<typename BaseDistribution::IndepQuantity>
    independent_values( 4 );
  Utility::setQuantity( independent_values[0], -1.0 );
  Utility::setQuantity( independent_values[1], 0.0 );
  Utility::setQuantity( independent_values[2], 0.5 );
  Utility::setQuantity( independent_values[3], 0.999999 );

  Teuchos::Array<double> dependent_values( 4 );
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
void initializeUnitAwareCDF( Teuchos::RCP<BaseDistribution>& dist )
{
  // Use the basic constructor
  Teuchos::Array<typename BaseDistribution::IndepQuantity>
    independent_values( 4 );
  Utility::setQuantity( independent_values[0], -1.0 );
  Utility::setQuantity( independent_values[1], 0.0 );
  Utility::setQuantity( independent_values[2], 0.5 );
  Utility::setQuantity( independent_values[3], 0.999999 );

  Teuchos::Array<double> dependent_values( 4 );
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
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   evaluate,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-3 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );

  initializeCDF<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-3 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   evaluate,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );
  
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.001*cgs::dimensionless() ),
    0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*cgs::dimensionless() ),
    0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.999999*cgs::dimensionless() ),
    0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.001*cgs::dimensionless() ),
    0.0*si::mole );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.001*cgs::dimensionless() ),
    0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*cgs::dimensionless() ),
    0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.999999*cgs::dimensionless() ),
    0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.001*cgs::dimensionless() ),
    0.0*si::mole );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   evaluatePDF,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );
  
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1e-3 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );

  initializeCDF<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1e-3 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, evaluatePDF );

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   evaluatePDF,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );
  
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( -1.001*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF(1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.001*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( -1.001*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF(1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.001*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution, evaluatePDF );

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   evaluateCDF,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -1.001 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( -1.0 ), 0.0, 1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.0 ), norm_const, 1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.5 ), 1.5*norm_const, 1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1.0 ), 1.0, 1e-10 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 1.001 ), 1.0 );

  initializeCDF<InterpolationPolicy>( tab_distribution );

  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -1.001 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( -1.0 ), 0.0, 1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.0 ), 1e-3, 1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.5 ), 1e-2, 1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1.0 ), 1.0, 1e-10 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 1.001 ), 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, evaluateCDF );

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   evaluateCDF,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( -1.001*cgs::dimensionless() ),
                       0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( -1.0*cgs::dimensionless() ),
                          0.0,
                          1e-10 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.0*cgs::dimensionless() ),
                          norm_const,
                          1e-10 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.5*cgs::dimensionless() ),
                          1.5*norm_const,
                          1e-10 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.999999*cgs::dimensionless() ),
                          1.0,
                          1e-10 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 1.001*cgs::dimensionless() ),
                       1.0 );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_tab_distribution );

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( -1.001*cgs::dimensionless() ),
                       0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( -1.0*cgs::dimensionless() ),
                          0.0,
                          1e-10 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.0*cgs::dimensionless() ),
                          1e-3,
                          1e-10 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.5*cgs::dimensionless() ),
                          1e-2,
                          1e-10 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 0.999999*cgs::dimensionless() ),
                          1.0,
                          1e-10 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 1.001*cgs::dimensionless() ),
                       1.0 );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution, evaluateCDF );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   sample,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sample();
  TEST_COMPARE( sample, >=, -1.0 );
  TEST_COMPARE( sample, <=, 0.999999 );

  initializeCDF<InterpolationPolicy>( distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-12 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.5, 1e-12 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sample();
  TEST_COMPARE( sample, >=, -1.0 );
  TEST_COMPARE( sample, <=, 0.999999 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, sample );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   sample,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sample();
  TEST_COMPARE( sample, >=, -1.0*cgs::dimensionless() );
  TEST_COMPARE( sample, <=, 0.999999*cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sample();
  TEST_COMPARE( sample, >=, -1.0*cgs::dimensionless() );
  TEST_COMPARE( sample, <=, 0.999999*cgs::dimensionless() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution, sample );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                          sampleAndRecordTrials,
                          InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_COMPARE( sample, >=, -1.0 );
  TEST_COMPARE( sample, <=, 0.999999 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  initializeCDF<InterpolationPolicy>( distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( 4.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-12 );
  TEST_EQUALITY_CONST( 5.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 0.5, 1e-12 );
  TEST_EQUALITY_CONST( 6.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
  TEST_EQUALITY_CONST( 7.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_COMPARE( sample, >=, -1.0 );
  TEST_COMPARE( sample, <=,0.999999 );
  TEST_EQUALITY_CONST( 8.0/trials, 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, sampleAndRecordTrials );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   sampleAndRecordTrials,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  quantity<cgs::dimensionless> sample =
  unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_COMPARE( sample, >=, -1.0*cgs::dimensionless() );
  TEST_COMPARE( sample, <=, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );
  TEST_EQUALITY_CONST( 4.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_COMPARE( sample, >=, -1.0*cgs::dimensionless() );
  TEST_COMPARE( sample, <=, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( 5.0/trials, 1.0 );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution, sampleAndRecordTrials );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   sampleAndRecordBinIndex,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_COMPARE( sample, >=, -1.0 );
  TEST_COMPARE( sample, <=,0.999999 );

  initializeCDF<InterpolationPolicy>( tab_distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.5, 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_COMPARE( sample, >=, -1.0 );
  TEST_COMPARE( sample, <=,0.999999 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, sampleAndRecordBinIndex );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   sampleAndRecordBinIndex,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  quantity<cgs::dimensionless> sample =
  unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_COMPARE( sample, >=, -1.0*cgs::dimensionless() );
  TEST_COMPARE( sample, <=, 0.999999*cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_tab_distribution );

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-3;
  fake_stream[2] = 1e-2;
  fake_stream[3] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_COMPARE( sample, >=, -1.0*cgs::dimensionless() );
  TEST_COMPARE( sample, <=, 0.999999*cgs::dimensionless() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution,
                         sampleAndRecordBinIndex );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                          sampleWithRandomNumber,
                          InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );

  initializeCDF<InterpolationPolicy>( tab_distribution );

  sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1e-3 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-12 );

  sample = tab_distribution->sampleWithRandomNumber( 1e-2 );
  TEST_FLOATING_EQUALITY( sample, 0.5, 1e-12 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-12 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, sampleWithRandomNumber );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   sampleWithRandomNumber,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<cgs::dimensionless> sample =
  unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_tab_distribution );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1e-3 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-12 );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution,
                         sampleWithRandomNumber );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   sampleInSubrange,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_FLOATING_EQUALITY( sample, 0.5, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_COMPARE( sample, >=, -1.0 );
  TEST_COMPARE( sample, <=, 0.5 );

  initializeCDF<InterpolationPolicy>( tab_distribution );

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-1;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-12 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_FLOATING_EQUALITY( sample, 0.5, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_COMPARE( sample, >=, -1.0 );
  TEST_COMPARE( sample, <=, 0.5 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, sampleInSubrange );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   sampleInSubrange,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
  unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless()  );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless() );
  TEST_COMPARE( sample, >=, -1.0*cgs::dimensionless() );
  TEST_COMPARE( sample, <=, 0.5*cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_tab_distribution );

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1e-1;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless()  );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*cgs::dimensionless() );
  TEST_COMPARE( sample, >=, -1.0*cgs::dimensionless() );
  TEST_COMPARE( sample, <=, 0.5*cgs::dimensionless() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution, sampleInSubrange );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   sampleWithRandomNumberInSubrange,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  double sample =
  tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  TEST_FLOATING_EQUALITY( sample, 0.5, 1e-12 );

  initializeCDF<InterpolationPolicy>( tab_distribution );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1e-1, 0.5 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-12 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  TEST_FLOATING_EQUALITY( sample, 0.5, 1e-12 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution,
                         sampleWithRandomNumberInSubrange );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                          sampleWithRandomNumberInSubrange,
                          InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<cgs::dimensionless> sample =
  unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
              0.0, 0.5*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
              1.0, 0.5*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_tab_distribution );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
              0.0, 0.5*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
              1e-1, 0.5*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-12 );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
              1.0, 0.5*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*cgs::dimensionless(), 1e-12 );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution,
                         sampleWithRandomNumberInSubrange );

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   getUpperBoundOfIndepVar,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(),0.999999 );

  initializeCDF<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(),0.999999 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, getUpperBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   getUpperBoundOfIndepVar,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
    0.999999*cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
    0.999999*cgs::dimensionless() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution,
                         getUpperBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   getLowerBoundOfIndepVar,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -1.0 );

  initializeCDF<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -1.0 );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, getLowerBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   getLowerBoundOfIndepVar,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
    -1.0*cgs::dimensionless() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
    -1.0*cgs::dimensionless() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution,
getLowerBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   getDistributionType,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getDistributionType(),
    Utility::TABULAR_CDF_DISTRIBUTION );

  initializeCDF<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getDistributionType(),
    Utility::TABULAR_CDF_DISTRIBUTION );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, getDistributionType );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   getDistributionType,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
    Utility::TABULAR_CDF_DISTRIBUTION );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
    Utility::TABULAR_CDF_DISTRIBUTION );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution, getDistributionType );

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   isTabular,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_ASSERT( distribution->isTabular() );

  initializeCDF<InterpolationPolicy>( distribution );

  TEST_ASSERT( distribution->isTabular() );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, isTabular );

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   isTabular,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_ASSERT( unit_aware_distribution->isTabular() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  TEST_ASSERT( unit_aware_distribution->isTabular() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution, isTabular );

//---------------------------------------------------------------------------//
// Check that the distribution is continuous
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   isContinuous,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_ASSERT( distribution->isContinuous() );

  initializeCDF<InterpolationPolicy>( distribution );

  TEST_ASSERT( distribution->isContinuous() );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, isContinuous );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   isContinuous,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_ASSERT( unit_aware_distribution->isContinuous() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution, isContinuous );

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   isCompatibleWithInterpType,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  if( boost::is_same<InterpolationPolicy,Utility::LogLogCos>::value )
  {
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }
  else
  {
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LinLogCos>::value )
  {
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }
  else
  {
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }

  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogCosLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );

  initializeCDF<InterpolationPolicy>( distribution );

  if( boost::is_same<InterpolationPolicy,Utility::LogLogCos>::value )
  {
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }
  else
  {
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LinLogCos>::value )
  {
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }
  else
  {
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }

  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogCosLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, isCompatibleWithInterpType );

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   isCompatibleWithInterpType,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  if( boost::is_same<InterpolationPolicy,Utility::LogLogCos>::value )
  {
    TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
    TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
    TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }
  else
  {
    TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
    TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
    TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LinLogCos>::value )
  {
    TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
    TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }
  else
  {
    TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
    TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }

  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );

  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  if( boost::is_same<InterpolationPolicy,Utility::LogLogCos>::value )
  {
    TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
    TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
    TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }
  else
  {
    TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLogCos>() );
    TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLog>() );
    TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LinLogCos>::value )
  {
    TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
    TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }
  else
  {
    TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLogCos>() );
    TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }

  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogCosLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution,
                         isCompatibleWithInterpType );

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularCDFDistribution,
                                   toParameterList,
                                   InterpolationPolicy )
{
  initializeCDF<InterpolationPolicy>( distribution );

  typedef Utility::TabularCDFDistribution<InterpolationPolicy> Distribution;

  Teuchos::RCP<Distribution> true_distribution =
  Teuchos::rcp_dynamic_cast<Distribution>( distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Distribution>( "test distribution",
                                    *true_distribution );

  std::ostringstream xml_file_name;
  xml_file_name << "tabular_" << InterpolationPolicy::name()
                << "cdf_dist_test_list.xml";

  Teuchos::writeParameterListToXmlFile( parameter_list,
  xml_file_name.str() );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
  Teuchos::getParametersFromXmlFile( xml_file_name.str() );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Distribution>
  copy_distribution( new Distribution );

  *copy_distribution = read_parameter_list->get<Distribution>(
        "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

UNIT_TEST_INSTANTIATION( TabularCDFDistribution, toParameterList );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularCDFDistribution,
                                   toParameterList,
                                   InterpolationPolicy )
{
  initializeUnitAwareCDF<InterpolationPolicy>( unit_aware_distribution );

  typedef Utility::UnitAwareTabularCDFDistribution<InterpolationPolicy,cgs::dimensionless,si::amount> Distribution;

  Teuchos::RCP<Distribution> true_distribution =
  Teuchos::rcp_dynamic_cast<Distribution>( unit_aware_distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Distribution>( "test distribution",
                                    *true_distribution );

  std::ostringstream xml_file_name;
  xml_file_name << "unit_aware_tabular_" << InterpolationPolicy::name()
                << "_cdf_dist_test_list.xml";

  Teuchos::writeParameterListToXmlFile( parameter_list,
  xml_file_name.str() );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
  Teuchos::getParametersFromXmlFile( xml_file_name.str() );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Distribution>
  copy_distribution( new Distribution );

  *copy_distribution = read_parameter_list->get<Distribution>(
        "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularCDFDistribution, toParameterList );

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( TabularCDFDistribution, fromParameterList )
{
  Utility::TabularCDFDistribution<Utility::LogLogCos> distribution_1 =
  test_dists_list->get<Utility::TabularCDFDistribution<Utility::LogLogCos> >( "Tabular CDF Distribution A" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 0.999999 );

  distribution_1 =
  test_dists_list->get<Utility::TabularCDFDistribution<Utility::LogLogCos> >( "Tabular CDF Distribution B" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 0.9 );

  Utility::TabularCDFDistribution<Utility::LinLogCos> distribution_2 =
  test_dists_list->get<Utility::TabularCDFDistribution<Utility::LinLogCos> >( "Tabular CDF Distribution C" );

  TEST_EQUALITY_CONST( distribution_2.getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( distribution_2.getUpperBoundOfIndepVar(), 0.999999 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareTabularCDFDistribution, fromParameterList )
{
  Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,cgs::dimensionless,si::amount>
  distribution_1 =
  test_dists_list->get<Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,cgs::dimensionless,si::amount> >( "Unit-Aware Tabular CDF Distribution A" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 0.999999*cgs::dimensionless() );

  distribution_1 =
  test_dists_list->get<Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,cgs::dimensionless,si::amount> >( "Unit-Aware Tabular CDF Distribution B" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 0.9*cgs::dimensionless() );

  Utility::UnitAwareTabularCDFDistribution<Utility::LinLogCos,cgs::dimensionless,si::amount>
  distribution_2 =
  test_dists_list->get<Utility::UnitAwareTabularCDFDistribution<Utility::LinLogCos,cgs::dimensionless,si::amount> >( "Unit-Aware Tabular CDF Distribution C" );

  TEST_EQUALITY_CONST( distribution_2.getLowerBoundOfIndepVar(), -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( distribution_2.getUpperBoundOfIndepVar(), 0.999999*cgs::dimensionless() );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareTabularCDFDistribution,
                                   explicit_conversion,
                                   IndepUnitA,
                                   DepUnitA,
                                   IndepUnitB,
                                   DepUnitB )
{
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;

  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;

  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  initializeCDF<Utility::LogLogCos>( distribution );

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,IndepUnitA,DepUnitA>
  unit_aware_dist_a_copy = Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::TabularCDFDistribution<Utility::LogLogCos> >( distribution ) );

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

  UTILITY_TEST_FLOATING_EQUALITY(
      unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
      dep_quantity_a,
      1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
      unit_aware_dist_a_copy.evaluateCDF( indep_quantity_a ),
      cdf_quantity_a,
      1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
      unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
      dep_quantity_b,
      1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
      unit_aware_dist_b_copy.evaluateCDF( indep_quantity_b ),
      cdf_quantity_b,
      1e-15 );

  Utility::setQuantity( indep_quantity_a, 0.5 );
  Utility::setQuantity( cdf_quantity_a, 1e-2 );
  Utility::setQuantity( dep_quantity_a, 0.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  cdf_quantity_b = cdf_quantity_a;
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY(
      unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
      dep_quantity_a,
      1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
      unit_aware_dist_a_copy.evaluateCDF( indep_quantity_a ),
      cdf_quantity_a,
      1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY(
      unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
      dep_quantity_b,
      1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
      unit_aware_dist_b_copy.evaluateCDF( indep_quantity_b ),
      cdf_quantity_b,
      1e-6 );
}

typedef si::amount si_amount;
typedef si::dimensionless si_dimensionless;
typedef cgs::dimensionless cgs_dimensionless;

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularCDFDistribution,
                                      explicit_conversion,
                                      si_dimensionless,
                                      si_amount,
                                      cgs_dimensionless,
                                      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularCDFDistribution,
                                      explicit_conversion,
                                      cgs_dimensionless,
                                      si_amount,
                                      si_dimensionless,
                                      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularCDFDistribution,
                                      explicit_conversion,
                                      void,
                                      cgs_dimensionless,
                                      void,
                                      si_dimensionless );

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
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::TabularCDFDistribution<Utility::LogLogCos> );
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::TabularCDFDistribution<Utility::LinLogCos> );
  typedef Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,cgs::dimensionless,si::amount> UnitAwareTabularCDFLogLogCosDist;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareTabularCDFLogLogCosDist );
  typedef Utility::UnitAwareTabularCDFDistribution<Utility::LinLogCos,cgs::dimensionless,si::amount> UnitAwareTabularCDFLinLogCosDist;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareTabularCDFLinLogCosDist );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstTabularCDFDistribution.cpp
//---------------------------------------------------------------------------//
