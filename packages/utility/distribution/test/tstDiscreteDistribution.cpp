//---------------------------------------------------------------------------//
//!
//! \file   tstDiscreteDistribution.cpp
//! \author Alex Robinson
//! \brief  Discrete distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
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

std::unique_ptr<Utility::PropertyTree> test_dists_ptree;

std::shared_ptr<Utility::OneDDistribution> distribution;
std::shared_ptr<Utility::TabularOneDDistribution> tab_distribution;
std::shared_ptr<Utility::OneDDistribution> cdf_cons_distribution;
std::shared_ptr<Utility::TabularOneDDistribution> tab_cdf_cons_distribution;
std::shared_ptr<Utility::OneDDistribution> repeat_vals_distribution;
std::shared_ptr<Utility::TabularOneDDistribution> tab_repeat_vals_distribution;

std::shared_ptr<Utility::UnitAwareOneDDistribution<ElectronVolt,si::amount> >
  unit_aware_distribution;
std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<ElectronVolt,si::amount> >
  unit_aware_tab_distribution;

std::shared_ptr<Utility::UnitAwareOneDDistribution<ElectronVolt,si::amount> >
  unit_aware_cdf_cons_distribution;
std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<ElectronVolt,si::amount> >
  unit_aware_tab_cdf_cons_distribution;


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( DiscreteDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( 0.0 ), 2.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*eV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.1*eV ),
		       0.25*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*eV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*eV ),
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.5*eV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 5.0*eV ),
		       2.7*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 100.0*eV ),
		       0.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1e3*eV ),
				  0.05*si::mole,
				  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2e3*eV ),
		       0.0*si::mole );

  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 0.0*eV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 0.1*eV ),
		       0.0625*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 0.5*eV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 1.0*eV ),
		       0.25*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 2.5*eV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 5.0*eV ),
		       0.675*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 100.0*eV ),
		       0.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY(
			  unit_aware_cdf_cons_distribution->evaluate( 1e3*eV ),
			  0.0125*si::mole,
			  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 2e3*eV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( DiscreteDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.50 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 0.0 ), 0.50 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*eV ),
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.1*eV ),
		       0.0625/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.5*eV ),
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.0*eV ),
		       0.25/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 2.5*eV ),
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 5.0*eV ),
		       0.675/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 100.0*eV ),
		       0.0/eV );
  UTILITY_TEST_FLOATING_EQUALITY(
			        unit_aware_distribution->evaluatePDF( 1e3*eV ),
				0.0125/eV,
				1e-14 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 2e3*eV ),
		       0.0/eV );

  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 0.0*eV ),
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 0.1*eV ),
		       0.0625/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 0.5*eV ),
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 1.0*eV ),
		       0.25/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 2.5*eV ),
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 5.0*eV ),
		       0.675/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF(100.0*eV),
		       0.0/eV );
  UTILITY_TEST_FLOATING_EQUALITY(
		       unit_aware_cdf_cons_distribution->evaluatePDF( 1e3*eV ),
		       0.0125/eV,
		       1e-14 );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 2e3*eV ),
		       0.0/eV );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( DiscreteDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -0.5 ), 0.25 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.0 ), 0.75 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.5 ), 0.75 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 2.0 ), 1.0 );

  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( -0.5 ), 0.25 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( 0.0 ), 0.75 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( 0.5 ), 0.75 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( 2.0 ), 1.0 );

  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( -0.5 ), 0.25 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( 0.0 ), 0.75 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( 0.5 ), 0.75 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( 2.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 0.0*eV ),
		       0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 0.1*eV ),
		       0.0625 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 0.5*eV ),
		       0.0625 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 1.0*eV ),
		       0.3125 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 2.5*eV ),
		       0.3125 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 5.0*eV ),
		       0.9875 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF(100.0*eV),
		       0.9875 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 1e3*eV ),
		       1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 2e3*eV ),
		       1.0 );

  TEST_EQUALITY_CONST(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 0.0*eV ),
		   0.0 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 0.1*eV ),
		   0.0625 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 0.5*eV ),
		   0.0625 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 1.0*eV ),
		   0.3125 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 2.5*eV ),
		   0.3125 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 5.0*eV ),
		   0.9875 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF(100.0*eV),
		   0.9875 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 1e3*eV ),
		   1.0 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 2e3*eV ),
		   1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sample )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0/4.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 3.0/4.0;
  fake_stream[5] = 0.85;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  // Test the third bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  // Test the third bin
  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  fake_stream.resize( 10 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.25;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.75;
  fake_stream[6] = 0.85;
  fake_stream[7] = 0.9375;
  fake_stream[8] = 0.95;
  fake_stream[9] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the third bin
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  // Test the fourth bin
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );

  // Test the fifth bin
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, sample )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.3;
  fake_stream[3] = 0.3125;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.9875;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  quantity<ElectronVolt> sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  // Test the third bin
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0*eV );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0*eV );

  // Test the fourth bin
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1e3*eV );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  // Test the third bin
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0*eV );

  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0*eV );

  // Test the fourth bin
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1e3*eV );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0/4.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 3.0/4.0;
  fake_stream[5] = 0.85;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  // Test the first bin
  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 2 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 3 );

  // Test the second bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 4 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 5 );

  // Test the third bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 6 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 7 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Test the first bin
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1 );

  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 2 );

  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 3 );

  // Test the second bin
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 4 );

  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 5 );

  // Test the third bin
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 6 );

  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 7 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  fake_stream.resize( 10 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.25;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.75;
  fake_stream[6] = 0.85;
  fake_stream[7] = 0.9375;
  fake_stream[8] = 0.95;
  fake_stream[9] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Test the first bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1 );

  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 2 );

  // Test the second bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 3 );

  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 4 );

  // Test the third bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 5 );

  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 6 );

  // Test the fourth bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 7 );

  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 8 );

  // Test the fifth bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 9 );

  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 10 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.3;
  fake_stream[3] = 0.3125;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.9875;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  // Test the first bin
  quantity<ElectronVolt> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( trials, 2u );

  // Test the second bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( trials, 4u );

  // Test the third bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( trials, 6u );

  // Test the fourth bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
  TEST_EQUALITY_CONST( trials, 7u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Test the first bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( trials, 2u );

  // Test the second bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( trials, 4u );

  // Test the third bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( trials, 6u );

  // Test the fourth bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
  TEST_EQUALITY_CONST( trials, 7u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0/4.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 3.0/4.0;
  fake_stream[5] = 0.85;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  // Test the first bin
  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  fake_stream.resize( 10 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.25;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.75;
  fake_stream[6] = 0.85;
  fake_stream[7] = 0.9375;
  fake_stream[8] = 0.95;
  fake_stream[9] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  // Test the fourth bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 3u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 3u );

  // Test the fifth bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 4u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 4u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.3;
  fake_stream[3] = 0.3125;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.9875;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index = 0;

  // Test the first bin
  quantity<ElectronVolt> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( bin_index, 2u );

  // Test the fourth bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
  TEST_EQUALITY_CONST( bin_index, 3u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( bin_index, 2u );

  // Test the fourth bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
  TEST_EQUALITY_CONST( bin_index, 3u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sampleWithRandomNumber )
{
  // Test the first bin
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.2 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.25 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = tab_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.75 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  // Test the third bin
  sample = tab_distribution->sampleWithRandomNumber( 0.85 );
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 );
  TEST_EQUALITY_CONST( sample, 1.0 );

  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.2 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.25 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.75 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  // Test the third bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.85 );
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 1.0 );
  TEST_EQUALITY_CONST( sample, 1.0 );

  // Test the first bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.0625 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.2 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.25 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.75 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  // Test the fourth bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.85 );
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.9375 );
  TEST_EQUALITY_CONST( sample, 1.0 );

  // Test the fifth bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.95 );
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 1.0 );
  TEST_EQUALITY_CONST( sample, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, sampleWithRandomNumber )
{
  // Test the first bin
  quantity<ElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.0625 );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.3 );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.3125 );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  // Test the third bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.9 );
  TEST_EQUALITY_CONST( sample, 5.0*eV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.9875 );
  TEST_EQUALITY_CONST( sample, 5.0*eV );

  // Test the fourth bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0-1e-15 );
  TEST_EQUALITY_CONST( sample, 1e3*eV );

  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.0625 );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.3 );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.3125 );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  // Test the third bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.9 );
  TEST_EQUALITY_CONST( sample, 5.0*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.9875 );
  TEST_EQUALITY_CONST( sample, 5.0*eV );

  // Test the fourth bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 1.0-1e-15 );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0/3.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  double sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.25/3.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.6;
  fake_stream[3] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  quantity<ElectronVolt> sample =
    unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sampleWithRandomNumberInSubrange )
{
  // Test the first bin
  double sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.2, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0/3.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.2, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 1.0/3.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  // Test the first bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 1.0/12, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 0.2, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 1.0/3, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution,
		   sampleWithRandomNumberInSubrange )
{
  // Test the first bin
  quantity<ElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.2, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.6, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.99, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.0, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.2, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.6, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.99, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(), 1e3*eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->getUpperBoundOfIndepVar(), 1e3*eV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution dependent variable can be
// returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->getLowerBoundOfIndepVar(),-1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution dependent variable
// can be returned
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(), 0.1*eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->getLowerBoundOfIndepVar(), 0.1*eV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
  TEST_EQUALITY_CONST( cdf_cons_distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getDistributionTypeName )
{
  TEST_EQUALITY_CONST( Utility::DiscreteDistribution::getDistributionTypeName(),
                       "Discrete Distribution" );
  TEST_EQUALITY_CONST( Utility::DiscreteDistribution::getDistributionTypeName( false ),
                       "Discrete" );
  TEST_EQUALITY_CONST( Utility::DiscreteDistribution::getDistributionTypeName( true, true ),
                       "discrete distribution" );
  TEST_EQUALITY_CONST( Utility::DiscreteDistribution::getDistributionTypeName( false, true ),
                       "discrete" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution,
                   getDistributionTypeName )
{
  TEST_EQUALITY_CONST( (Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>::getDistributionTypeName()),
                       "Discrete Distribution" );
  TEST_EQUALITY_CONST( (Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>::getDistributionTypeName( false )),
                       "Discrete" );
  TEST_EQUALITY_CONST( (Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>::getDistributionTypeName( true, true )),
                       "discrete distribution" );
  TEST_EQUALITY_CONST( (Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>::getDistributionTypeName( false, true )),
                       "discrete" );
}

//---------------------------------------------------------------------------//
// Check if the type name matches the distribution type name
TEUCHOS_UNIT_TEST( DiscreteDistribution, doesTypeNameMatch )
{
  TEST_ASSERT( Utility::DiscreteDistribution::doesTypeNameMatch( "Discrete Distribution" ) );
  TEST_ASSERT( Utility::DiscreteDistribution::doesTypeNameMatch( "Discrete" ) );
  TEST_ASSERT( Utility::DiscreteDistribution::doesTypeNameMatch( "discrete" ) );
  TEST_ASSERT( Utility::DiscreteDistribution::doesTypeNameMatch( "DISCRETE" ) );
  TEST_ASSERT( !Utility::DiscreteDistribution::doesTypeNameMatch( "DISC" ) );
}

//---------------------------------------------------------------------------//
// Check if the type name matches the unit-aware distribution type name
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, doesTypeNameMatch )
{
  TEST_ASSERT( (Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>::doesTypeNameMatch( "Discrete Distribution" )) );
  TEST_ASSERT( (Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>::doesTypeNameMatch( "Discrete" )) );
  TEST_ASSERT( (Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>::doesTypeNameMatch( "discrete" )) );
  TEST_ASSERT( (Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>::doesTypeNameMatch( "DISCRETE" )) );
  TEST_ASSERT( !(Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>::doesTypeNameMatch( "DISC" )) );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( DiscreteDistribution, isTabular )
{
  TEST_ASSERT( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, isTabular )
{
  TEST_ASSERT( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( DiscreteDistribution, isContinuous )
{
  TEST_ASSERT( !distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, isContinuous )
{
  TEST_ASSERT( !unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( DiscreteDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
TEUCHOS_UNIT_TEST( DiscreteDistribution, toString )
{
  std::string dist_string = Utility::toString( *distribution );

  TEST_EQUALITY_CONST( dist_string, "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {1.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  dist_string = Utility::toString( *cdf_cons_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 5.000000000000000000e-01, 2.500000000000000000e-01}}" );

  dist_string = Utility::toString( *repeat_vals_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Discrete Distribution, {-1.000000000000000000e+00, -1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 7.500000000000000000e-01, 2.000000000000000000e+00, 7.500000000000000000e-01, 2.500000000000000000e-01}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distributio can be converted to a string
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, toString )
{
  std::string dist_string = Utility::toString( *unit_aware_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {2.500000000000000000e-01, 1.000000000000000000e+00, 2.700000000000000178e+00, 4.999999999999982236e-02}}" );

  dist_string = Utility::toString( *unit_aware_cdf_cons_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {6.250000000000000000e-02, 2.500000000000000000e-01, 6.750000000000000444e-01, 1.249999999999995559e-02}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
TEUCHOS_UNIT_TEST( DiscreteDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {1.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *cdf_cons_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 5.000000000000000000e-01, 2.500000000000000000e-01}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *repeat_vals_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Discrete Distribution, {-1.000000000000000000e+00, -1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 7.500000000000000000e-01, 2.000000000000000000e+00, 7.500000000000000000e-01, 2.500000000000000000e-01}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *unit_aware_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {2.500000000000000000e-01, 1.000000000000000000e+00, 2.700000000000000178e+00, 4.999999999999982236e-02}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *unit_aware_cdf_cons_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {6.250000000000000000e-02, 2.500000000000000000e-01, 6.750000000000000444e-01, 1.249999999999995559e-02}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
TEUCHOS_UNIT_TEST( DiscreteDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {1.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << *cdf_cons_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 5.000000000000000000e-01, 2.500000000000000000e-01}}" );

  oss.str( "" );
  oss.clear();

  oss << *repeat_vals_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Discrete Distribution, {-1.000000000000000000e+00, -1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 7.500000000000000000e-01, 2.000000000000000000e+00, 7.500000000000000000e-01, 2.500000000000000000e-01}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *unit_aware_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {2.500000000000000000e-01, 1.000000000000000000e+00, 2.700000000000000178e+00, 4.999999999999982236e-02}}" );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_cdf_cons_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {6.250000000000000000e-02, 2.500000000000000000e-01, 6.750000000000000444e-01, 1.249999999999995559e-02}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a string
TEUCHOS_UNIT_TEST( DiscreteDistribution, fromString )
{
  Utility::DiscreteDistribution test_dist =
    Utility::fromString<Utility::DiscreteDistribution>( "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {1.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DiscreteDistribution*>( distribution.get() ) );

  test_dist = Utility::fromString<Utility::DiscreteDistribution>( "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 5.000000000000000000e-01, 2.500000000000000000e-01}}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DiscreteDistribution*>( cdf_cons_distribution.get() ) );

  test_dist = Utility::fromString<Utility::DiscreteDistribution>( "{Discrete Distribution, {-1.000000000000000000e+00, -1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 7.500000000000000000e-01, 2.000000000000000000e+00, 7.500000000000000000e-01, 2.500000000000000000e-01}}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DiscreteDistribution*>( repeat_vals_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a string
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, fromString )
{
  Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> test_dist;

  test_dist = Utility::fromString<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {2.500000000000000000e-01, 1.000000000000000000e+00, 2.700000000000000178e+00, 4.999999999999982236e-02}}" );

  TEST_EQUALITY_CONST( test_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  test_dist = Utility::fromString<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {6.250000000000000000e-02, 2.500000000000000000e-01, 6.750000000000000444e-01, 1.249999999999995559e-02}}" );

  TEST_EQUALITY_CONST( test_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_cdf_cons_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( DiscreteDistribution, fromStream )
{
  std::istringstream iss( "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {1.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  Utility::DiscreteDistribution test_dist;
  
  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DiscreteDistribution*>( distribution.get() ) );

  iss.str( "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 5.000000000000000000e-01, 2.500000000000000000e-01}}" );
  iss.clear();
  
  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DiscreteDistribution*>( cdf_cons_distribution.get() ) );

  iss.str( "{Discrete Distribution, {-1.000000000000000000e+00, -1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 7.500000000000000000e-01, 2.000000000000000000e+00, 7.500000000000000000e-01, 2.500000000000000000e-01}}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DiscreteDistribution*>( repeat_vals_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, fromStream )
{
  std::istringstream iss( "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {2.500000000000000000e-01, 1.000000000000000000e+00, 2.700000000000000178e+00, 4.999999999999982236e-02}}" );
  
  Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> test_dist;

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  iss.str( "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {6.250000000000000000e-02, 2.500000000000000000e-01, 6.750000000000000444e-01, 1.249999999999995559e-02}}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_cdf_cons_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( DiscreteDistribution, istream_operator )
{
  std::istringstream iss( "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {1.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  Utility::DiscreteDistribution test_dist;

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DiscreteDistribution*>( distribution.get() ) );

  iss.str( "{Discrete Distribution, {-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 5.000000000000000000e-01, 2.500000000000000000e-01}}" );
  iss.clear();

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DiscreteDistribution*>( cdf_cons_distribution.get() ) );

  iss.str( "{Discrete Distribution, {-1.000000000000000000e+00, -1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}, {2.500000000000000000e-01, 7.500000000000000000e-01, 2.000000000000000000e+00, 7.500000000000000000e-01, 2.500000000000000000e-01}}" );
  iss.clear();

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DiscreteDistribution*>( repeat_vals_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, istream_operator )
{
  std::istringstream iss( "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {2.500000000000000000e-01, 1.000000000000000000e+00, 2.700000000000000178e+00, 4.999999999999982236e-02}}" );
  
  Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> test_dist;

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  iss.str( "{Discrete Distribution, {1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+03}, {6.250000000000000000e-02, 2.500000000000000000e-01, 6.750000000000000444e-01, 1.249999999999995559e-02}}" );
  iss.clear();

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_cdf_cons_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree
TEUCHOS_UNIT_TEST( DiscreteDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *distribution );

  Utility::DiscreteDistribution copy_dist =
    ptree.get<Utility::DiscreteDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::DiscreteDistribution*>( distribution.get() ) );

  ptree.put( "test distribution", *tab_distribution );

  copy_dist = ptree.get<Utility::DiscreteDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::DiscreteDistribution*>( tab_distribution.get() ) );

  ptree.clear();
  
  // Use the PropertyTreeCompatibleObject interface
  ptree = distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::DiscreteDistribution>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::DiscreteDistribution*>( distribution.get() ) );

  ptree = distribution->toPropertyTree( false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({1.0, 2.0, 1.0}) );

  ptree = distribution->toPropertyTree();

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({1.0, 2.0, 1.0}) );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( *distribution, true );

  copy_dist = ptree.get_value<Utility::DiscreteDistribution>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::DiscreteDistribution*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *tab_distribution, true );

  copy_dist = ptree.get_value<Utility::DiscreteDistribution>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::DiscreteDistribution*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({1.0, 2.0, 1.0}) );

  ptree = Utility::toPropertyTree( *tab_distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({1.0, 2.0, 1.0}) );

  ptree = Utility::toPropertyTree( *distribution );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({1.0, 2.0, 1.0}) );

  ptree = Utility::toPropertyTree( *tab_distribution );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({1.0, 2.0, 1.0}) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to a property tree
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *unit_aware_distribution );

  Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> copy_dist =
    ptree.get<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  ptree.put( "test distribution", *unit_aware_tab_distribution );

  copy_dist = ptree.get<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_tab_distribution.get() )) );

  ptree.clear();
  
  // Use the PropertTreeCompatibleObject interface
  ptree = unit_aware_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = unit_aware_distribution->toPropertyTree( false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({0.1, 1.0, 5.0, 1000.0}) );
  TEST_COMPARE_FLOATING_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({0.25, 1.0, 2.7, 0.05}), 1e-14 );

  ptree = unit_aware_distribution->toPropertyTree();

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({0.1, 1.0, 5.0, 1000.0}) );
  TEST_COMPARE_FLOATING_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({0.25, 1.0, 2.7, 0.05}), 1e-14 );

  // Use the PropertyTree helper methods
  ptree = Utility::toPropertyTree( *unit_aware_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, (*dynamic_cast<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({0.1, 1.0, 5.0, 1000.0}) );
  TEST_COMPARE_FLOATING_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({0.25, 1.0, 2.7, 0.05}), 1e-14 );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({0.1, 1.0, 5.0, 1000.0}) );
  TEST_COMPARE_FLOATING_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({0.25, 1.0, 2.7, 0.05}), 1e-14 );

  ptree = Utility::toPropertyTree( *unit_aware_distribution );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({0.1, 1.0, 5.0, 1000.0}) );
  TEST_COMPARE_FLOATING_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({0.25, 1.0, 2.7, 0.05}), 1e-14 );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Discrete Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "independent values" ), std::vector<double>({0.1, 1.0, 5.0, 1000.0}) );
  TEST_COMPARE_FLOATING_CONTAINERS( ptree.get<std::vector<double> >( "dependent values" ), std::vector<double>({0.25, 1.0, 2.7, 0.05}), 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be read from a property tree
TEUCHOS_UNIT_TEST( DiscreteDistribution, fromPropertyTree )
{
  Utility::DiscreteDistribution dist;

  std::vector<std::string> unused_children;

  dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution A" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist, *dynamic_cast<Utility::DiscreteDistribution*>( distribution.get() ) );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution B" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       -Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi );
  TEST_FLOATING_EQUALITY( dist.evaluate( -Utility::PhysicalConstants::pi/2 ), 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi ), 1.0, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution C" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.1 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 10.0 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 0.1 ), 2.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 1.0 ), 6.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 10.0 ), 2.0, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution D" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi );
  TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi/2 ), 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi ), 1.0, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution E" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution F" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution G" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution H" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution I" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution J" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution K" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution L" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution M" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution N" ) ),
              Utility::PropertyTreeConversionException );

  unused_children.clear();
  
  // Use the property tree helper methods
  dist = Utility::fromPropertyTree<Utility::DiscreteDistribution>(
                      test_dists_ptree->get_child( "Discrete Distribution A" ),
                      unused_children );

  TEST_EQUALITY_CONST( dist, *dynamic_cast<Utility::DiscreteDistribution*>( distribution.get() ) );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<Utility::DiscreteDistribution>(
                      test_dists_ptree->get_child( "Discrete Distribution B" ),
                      unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       -Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi );
  TEST_FLOATING_EQUALITY( dist.evaluate( -Utility::PhysicalConstants::pi/2 ), 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi ), 1.0, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<Utility::DiscreteDistribution>(
                      test_dists_ptree->get_child( "Discrete Distribution C" ),
                      unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.1 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 10.0 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 0.1 ), 2.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 1.0 ), 6.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 10.0 ), 2.0, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<Utility::DiscreteDistribution>(
                      test_dists_ptree->get_child( "Discrete Distribution D" ),
                      unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi );
  TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi/2 ), 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi ), 1.0, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  TEST_THROW( Utility::fromPropertyTree<Utility::DiscreteDistribution>( test_dists_ptree->get_child( "Discrete Distribution E" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::DiscreteDistribution>( test_dists_ptree->get_child( "Discrete Distribution F" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::DiscreteDistribution>( test_dists_ptree->get_child( "Discrete Distribution G" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::DiscreteDistribution>( test_dists_ptree->get_child( "Discrete Distribution H" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::DiscreteDistribution>( test_dists_ptree->get_child( "Discrete Distribution I" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::DiscreteDistribution>( test_dists_ptree->get_child( "Discrete Distribution J" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::DiscreteDistribution>( test_dists_ptree->get_child( "Discrete Distribution K" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::DiscreteDistribution>( test_dists_ptree->get_child( "Discrete Distribution L" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::DiscreteDistribution>( test_dists_ptree->get_child( "Discrete Distribution M" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::DiscreteDistribution>( test_dists_ptree->get_child( "Discrete Distribution N" ) ),
              Utility::PropertyTreeConversionException );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be read from a property tree
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, fromPropertyTree )
{
  Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> dist;

  std::vector<std::string> unused_children;

  dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution A" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), -1.0*eV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*eV );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution B" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       -Utility::PhysicalConstants::pi/2*eV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi*eV );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( -Utility::PhysicalConstants::pi/2*eV ), 1.0*si::mole, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi*eV ), 1.0*si::mole, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution C" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.1*eV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 10.0*eV );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( 0.1*eV ), 2.0*si::mole, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( 1.0*eV ), 6.0*si::mole, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( 10.0*eV ), 2.0*si::mole, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution D" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi/2*eV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi*eV );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi/2*eV ), 1.0*si::mole, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi*eV ), 1.0*si::mole, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution E" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution F" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution G" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution H" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution I" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution J" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution K" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution L" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution M" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Discrete Distribution N" ) ),
              Utility::PropertyTreeConversionException );

  unused_children.clear();

  // Use the property tree helper methods
  dist = Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >(
                      test_dists_ptree->get_child( "Discrete Distribution A" ),
                      unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), -1.0*eV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*eV );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >(
                      test_dists_ptree->get_child( "Discrete Distribution B" ),
                      unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       -Utility::PhysicalConstants::pi/2*eV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi*eV );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( -Utility::PhysicalConstants::pi/2*eV ), 1.0*si::mole, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi*eV ), 1.0*si::mole, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >(
                      test_dists_ptree->get_child( "Discrete Distribution C" ),
                      unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.1*eV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 10.0*eV );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( 0.1*eV ), 2.0*si::mole, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( 1.0*eV ), 6.0*si::mole, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( 10.0*eV ), 2.0*si::mole, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >(
                      test_dists_ptree->get_child( "Discrete Distribution D" ),
                      unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi/2*eV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi*eV );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi/2*eV ), 1.0*si::mole, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist.evaluate( Utility::PhysicalConstants::pi*eV ), 1.0*si::mole, 1e-15 );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  TEST_THROW( (Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( test_dists_ptree->get_child( "Discrete Distribution E" ) )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( test_dists_ptree->get_child( "Discrete Distribution F" ) )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( test_dists_ptree->get_child( "Discrete Distribution G" ) )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( test_dists_ptree->get_child( "Discrete Distribution H" ) )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( test_dists_ptree->get_child( "Discrete Distribution I" ) )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( test_dists_ptree->get_child( "Discrete Distribution J" ) )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( test_dists_ptree->get_child( "Discrete Distribution K" ) )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( test_dists_ptree->get_child( "Discrete Distribution L" ) )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( test_dists_ptree->get_child( "Discrete Distribution M" ) )),
              Utility::PropertyTreeConversionException );
  TEST_THROW( (Utility::fromPropertyTree<Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> >( test_dists_ptree->get_child( "Discrete Distribution N" ) )),
              Utility::PropertyTreeConversionException );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareDiscreteDistribution,
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

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwareDiscreteDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareDiscreteDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::DiscreteDistribution*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareDiscreteDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.5 );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 2.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b =
    Utility::QuantityTraits<InverseIndepQuantityB>::initializeQuantity( 0.5 );
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

  Utility::setQuantity( indep_quantity_a, 0.5 );
  Utility::setQuantity( inv_indep_quantity_a, 0.0 );
  Utility::setQuantity( dep_quantity_a, 0.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  Utility::setQuantity( inv_indep_quantity_b, 0.0 );
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

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      void,
				      MegaElectronVolt,
				      void,
				      KiloElectronVolt );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_dists_json_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_dists_json_file",
                   &test_dists_json_file_name,
                   "Test distributions json file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Load the property tree from the json file
  test_dists_ptree.reset( new Utility::PropertyTree );

  std::ifstream test_dists_json_file( test_dists_json_file_name );

  test_dists_json_file >> *test_dists_ptree;

  // Create a distribution using the standard constructor
  std::vector<double> independent_values( 3 );
  independent_values[0] = -1.0;
  independent_values[1] = 0.0;
  independent_values[2] = 1.0;

  std::vector<double> dependent_values( 3 );
  dependent_values[0] = 1.0;
  dependent_values[1] = 2.0;
  dependent_values[2] = 1.0;

  tab_distribution.reset(
		      new Utility::DiscreteDistribution( independent_values,
							 dependent_values ) );

  distribution = tab_distribution;

  // Create a distribution using the cdf constructor
  std::vector<double> cdf_values( 3 );
  cdf_values[0] = 0.25;
  cdf_values[1] = 0.75;
  cdf_values[2] = 1.0;

  tab_cdf_cons_distribution.reset( new Utility::DiscreteDistribution(
							  independent_values,
							  cdf_values,
							  true ) );

  cdf_cons_distribution = tab_cdf_cons_distribution;

  // Create a distribution with repeated values
  independent_values.resize( 5 );
  independent_values[0] = -1.0;
  independent_values[1] = -1.0;
  independent_values[2] = 0.0;
  independent_values[3] = 1.0;
  independent_values[4] = 1.0;

  dependent_values.resize( 5 );
  dependent_values[0] = 0.25;
  dependent_values[1] = 0.75;
  dependent_values[2] = 2.0;
  dependent_values[3] = 0.75;
  dependent_values[4] = 0.25;

  tab_repeat_vals_distribution.reset( new Utility::DiscreteDistribution(
							  independent_values,
							  dependent_values ) );

  repeat_vals_distribution = tab_repeat_vals_distribution;

  // Create a unit aware distribution using quantities
  std::vector<quantity<ElectronVolt> > independent_quantities( 4 );
  independent_quantities[0] = 0.1*eV;
  independent_quantities[1] = 1.0*eV;
  independent_quantities[2] = 5.0*eV;
  independent_quantities[3] = quantity<ElectronVolt>( 1.0*keV );

  std::vector<quantity<si::amount> > dependent_quantities( 4 );
  dependent_quantities[0] = 0.25*si::mole;
  dependent_quantities[1] = 1.0*si::mole;
  dependent_quantities[2] = 2.7*si::mole;
  dependent_quantities[3] = 0.05*si::mole;

  unit_aware_tab_distribution.reset(
	   new Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>(
  						      independent_quantities,
  						      dependent_quantities ) );

  unit_aware_distribution = unit_aware_tab_distribution;

  // Create a unit aware distribution using quantities and the cdf constructor
  dependent_values.resize( 4 );
  dependent_values[0] = 0.0625;
  dependent_values[1] = 0.3125;
  dependent_values[2] = 0.9875;
  dependent_values[3] = 1.0;

  unit_aware_tab_cdf_cons_distribution.reset(
	   new Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>(
  							independent_quantities,
  							dependent_values ) );

  unit_aware_cdf_cons_distribution = unit_aware_tab_cdf_cons_distribution;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDiscreteDistribution.cpp
//---------------------------------------------------------------------------//
