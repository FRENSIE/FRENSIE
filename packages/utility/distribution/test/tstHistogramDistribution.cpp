//---------------------------------------------------------------------------//
//!
//! \file   tstHistogramDistribution.cpp
//! \author Alex Robinson
//! \brief  Histogram distribution unit tests.
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

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
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

std::shared_ptr<Utility::OneDDistribution> pdf_distribution;
std::shared_ptr<Utility::TabularOneDDistribution> tab_pdf_distribution;

std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_pdf_distribution;
std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_tab_pdf_distribution;


std::shared_ptr<Utility::OneDDistribution> cdf_distribution;
std::shared_ptr<Utility::TabularOneDDistribution> tab_cdf_distribution;

std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_cdf_distribution;
std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_tab_cdf_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evalute )
{
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -2.0 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -1.5 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 1.5 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 2.0 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 3.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -2.0 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -1.5 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 1.5 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 2.0 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, evalute )
{
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( -3.0*MeV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( -2.0*MeV ),
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( -1.5*MeV ),
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( -1.0*MeV ),
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( 0.0*MeV ),
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( 1.0*MeV ),
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( 1.5*MeV ),
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( 2.0*MeV ),
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( 3.0*MeV ),
		       0.0*si::mole );

  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( -3.0*MeV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( -2.0*MeV ),
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( -1.5*MeV ),
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( -1.0*MeV ),
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( 0.0*MeV ),
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( 1.0*MeV ),
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( 1.5*MeV ),
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( 2.0*MeV ),
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( 3.0*MeV ),
		       0.0*si::mole);
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -1.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 0.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 1.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 3.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -1.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 0.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 1.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( -3.0*MeV ),
		       0.0/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( -2.0*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( -1.5*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( -1.0*MeV ),
		       (1.0/6.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( 0.0*MeV ),
		       (1.0/6.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( 1.0*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( 1.5*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( 2.0*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( 3.0*MeV ),
		       0.0/MeV );

  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( -3.0*MeV ),
		       0.0/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( -2.0*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( -1.5*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( -1.0*MeV ),
		       (1.0/6.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( 0.0*MeV ),
		       (1.0/6.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( 1.0*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( 1.5*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( 2.0*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( 3.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF(-3.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF(-2.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_pdf_distribution->evaluateCDF(-1.5 ), 1.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF(-1.0 ), 1.0/3.0 );
  TEST_FLOATING_EQUALITY( tab_pdf_distribution->evaluateCDF( 0.0 ), 0.5, 1e-14 );
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF( 1.0 ), 2.0/3.0 );
  TEST_FLOATING_EQUALITY( tab_pdf_distribution->evaluateCDF( 1.5 ), 5.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF( 2.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF( 3.0 ), 1.0 );

  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF(-3.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF(-2.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_cdf_distribution->evaluateCDF(-1.5 ), 1.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF(-1.0 ), 1.0/3.0 );
  TEST_FLOATING_EQUALITY( tab_cdf_distribution->evaluateCDF( 0.0 ), 0.5, 1e-14 );
  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF( 1.0 ), 2.0/3.0 );
  TEST_FLOATING_EQUALITY( tab_cdf_distribution->evaluateCDF( 1.5 ), 5.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF( 2.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF( 3.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST(unit_aware_tab_pdf_distribution->evaluateCDF( -3.0*MeV ),
		      0.0 );
  TEST_EQUALITY_CONST(unit_aware_tab_pdf_distribution->evaluateCDF( -2.0*MeV ),
		      0.0 );
  TEST_FLOATING_EQUALITY(
		      unit_aware_tab_pdf_distribution->evaluateCDF( -1.5*MeV ),
		      1.0/6.0,
		      1e-14 );
  TEST_EQUALITY_CONST(unit_aware_tab_pdf_distribution->evaluateCDF( -1.0*MeV ),
		      1.0/3.0 );
  TEST_FLOATING_EQUALITY(
		       unit_aware_tab_pdf_distribution->evaluateCDF( 0.0*MeV ),
		       0.5,
		       1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_pdf_distribution->evaluateCDF( 1.0*MeV ),
		       2.0/3.0 );
  TEST_FLOATING_EQUALITY(
		       unit_aware_tab_pdf_distribution->evaluateCDF( 1.5*MeV ),
		       5.0/6.0,
		       1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_pdf_distribution->evaluateCDF( 2.0*MeV ),
		       1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_pdf_distribution->evaluateCDF( 3.0*MeV ),
		       1.0 );

  TEST_EQUALITY_CONST(unit_aware_tab_cdf_distribution->evaluateCDF( -3.0*MeV ),
		      0.0 );
  TEST_EQUALITY_CONST(unit_aware_tab_cdf_distribution->evaluateCDF( -2.0*MeV ),
		      0.0 );
  TEST_FLOATING_EQUALITY(
		      unit_aware_tab_cdf_distribution->evaluateCDF( -1.5*MeV ),
		      1.0/6.0,
		      1e-14 );
  TEST_EQUALITY_CONST(unit_aware_tab_cdf_distribution->evaluateCDF( -1.0*MeV ),
		      1.0/3.0 );
  TEST_FLOATING_EQUALITY(
		       unit_aware_tab_cdf_distribution->evaluateCDF( 0.0*MeV ),
		       0.5,
		       1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_cdf_distribution->evaluateCDF( 1.0*MeV ),
		       2.0/3.0 );
  TEST_FLOATING_EQUALITY(
		       unit_aware_tab_cdf_distribution->evaluateCDF( 1.5*MeV ),
		       5.0/6.0,
		       1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_cdf_distribution->evaluateCDF( 2.0*MeV ),
		      1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_cdf_distribution->evaluateCDF( 3.0*MeV ),
		      1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  double sample = pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0 );

  sample = pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.5 );

  sample = pdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // Test the second bin
  sample = pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = pdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Test the third bin
  sample = pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = pdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );

  sample = pdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0 );

  sample = cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.5 );

  sample = cdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // Test the second bin
  sample = cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = cdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Test the third bin
  sample = cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = cdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );

  sample = cdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  quantity<MegaElectronVolt> sample = unit_aware_pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0*MeV );

  sample = unit_aware_pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.5*MeV );

  sample = unit_aware_pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // Test the second bin
  sample = unit_aware_pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0*MeV );

  sample = unit_aware_pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );

  sample = unit_aware_pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  // Test the third bin
  sample = unit_aware_pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*MeV );

  sample = unit_aware_pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );

  sample = unit_aware_pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0*MeV );

  sample = unit_aware_cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.5*MeV );

  sample = unit_aware_cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // Test the second bin
  sample = unit_aware_cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0*MeV );

  sample = unit_aware_cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );

  sample = unit_aware_cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  // Test the third bin
  sample = unit_aware_cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*MeV );

  sample = unit_aware_cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );

  sample = unit_aware_cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  // Test the first bin
  double sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( trials, 1 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.5 );
  TEST_EQUALITY_CONST( trials, 2 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3 );

  // Test the second bin
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 4 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 5 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6 );

  // Test the third bin
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 7 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  TEST_EQUALITY_CONST( trials, 8 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 9 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Test the first bin
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( trials, 1 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.5 );
  TEST_EQUALITY_CONST( trials, 2 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3 );

  // Test the second bin
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 4 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 5 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6 );

  // Test the third bin
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 7 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  TEST_EQUALITY_CONST( trials, 8 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 9 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  // Test the first bin
  quantity<MegaElectronVolt> sample =
    unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  TEST_EQUALITY_CONST( trials, 1 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  TEST_EQUALITY_CONST( trials, 2 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3 );

  // Test the second bin
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  TEST_EQUALITY_CONST( trials, 4 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 5 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6 );

  // Test the third bin
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
  TEST_EQUALITY_CONST( trials, 7 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 8 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 9 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Test the first bin
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  TEST_EQUALITY_CONST( trials, 1 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  TEST_EQUALITY_CONST( trials, 2 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3 );

  // Test the second bin
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  TEST_EQUALITY_CONST( trials, 4 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 5 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6 );

  // Test the third bin
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
  TEST_EQUALITY_CONST( trials, 7 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 8 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 9 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  // Test the first bin
  double sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.5 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.5 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  // Test the first bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleWithRandomNumber )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;

  // Test the first bin
  double sample = tab_pdf_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -2.0 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  TEST_EQUALITY_CONST( sample, -1.5 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // Test the second bin
  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 0.5 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Test the third bin
  sample = tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_cdf_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -2.0 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  TEST_EQUALITY_CONST( sample, -1.5 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // Test the second bin
  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 0.5 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Test the third bin
  sample = tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  TEST_EQUALITY_CONST( sample, 1.0 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, sampleWithRandomNumber )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;

  // Test the first bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );

  sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // Test the second bin
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 0.5 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );

  sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  // Test the third bin
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );

  sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );

  sample =
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // Test the second bin
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 0.5 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );

  sample =
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  // Test the third bin
  sample =
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );

  sample =
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );

  sample =
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
//Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15 ;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // PDF Histogram: test max independent value 2nd bin
  double sample = tab_pdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // PDF Histogram: test max independent value 3rd bin
  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // CDF Histogram: test max independent value 2nd bin
  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // CDF Histogram: test max independent value 3rd bin
  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15 ;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // PDF Histogram: test max independent value 2nd bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_pdf_distribution->sampleInSubrange( -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleInSubrange( -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.5*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleInSubrange( -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // PDF Histogram: test max independent value 3rd bin
  sample = unit_aware_tab_pdf_distribution->sampleInSubrange( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleInSubrange( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleInSubrange( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // CDF Histogram: test max independent value 2nd bin
  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.5*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // CDF Histogram: test max independent value 3rd bin
  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleWithRandomNumberInSubrange )
{
  // PDF Histogram: test max independent value 2nd bin
  double sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.0, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.5, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // PDF Histogram: test max independent value 3rd bin
  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.5, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // CDF Histogram: test max independent value 2nd bin
  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.0, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.5, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // Test max independent value 3rd bin
  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.5, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution,
		   sampleWithRandomNumberInSubrange )
{
  // PDF Histogram: test max independent value 2nd bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
							       0.0, -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
							       0.5, -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.5*MeV, 1e-14 );

  sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
						       1.0 - 1e-15, -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // PDF Histogram: test max independent value 3rd bin
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
								0.0, 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
								0.5, 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
							1.0 - 1e-15, 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  // CDF Histogram: test max independent value 2nd bin
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
							       0.0, -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
							       0.5, -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.5*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
						       1.0 - 1e-15, -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // Test max independent value 3rd bin
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
							        0.0, 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
								0.5, 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
							1.0 - 1e-15, 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( pdf_distribution->getUpperBoundOfIndepVar(), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->getUpperBoundOfIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->getUpperBoundOfIndepVar(),
		       2.0*MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->getUpperBoundOfIndepVar(),
		       2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution dependent variable can be
// returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( pdf_distribution->getLowerBoundOfIndepVar(), -2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->getLowerBoundOfIndepVar(), -2.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution dependent variable
// can be returned
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->getLowerBoundOfIndepVar(),
		       -2.0*MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->getLowerBoundOfIndepVar(),
		       -2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( pdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );

  TEST_EQUALITY_CONST( cdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );

  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getDistributionTypeName )
{
  TEST_EQUALITY_CONST( Utility::HistogramDistribution::getDistributionTypeName(),
                       "Histogram Distribution" );
  TEST_EQUALITY_CONST( Utility::HistogramDistribution::getDistributionTypeName( false ),
                       "Histogram" );
  TEST_EQUALITY_CONST( Utility::HistogramDistribution::getDistributionTypeName( true, true ),
                       "histogram distribution" );
  TEST_EQUALITY_CONST( Utility::HistogramDistribution::getDistributionTypeName( false, true ),
                       "histogram" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution,
                   getDistributionTypeName )
{
  TEST_EQUALITY_CONST( (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::getDistributionTypeName()),
                       "Histogram Distribution" );
  TEST_EQUALITY_CONST( (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::getDistributionTypeName( false )),
                       "Histogram" );
  TEST_EQUALITY_CONST( (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::getDistributionTypeName( true, true )),
                       "histogram distribution" );
  TEST_EQUALITY_CONST( (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::getDistributionTypeName( false, true )),
                       "histogram" );
}

//---------------------------------------------------------------------------//
// Check if the type name matches the distribution type name
TEUCHOS_UNIT_TEST( HistogramDistribution, doesTypeNameMatch )
{
  TEST_ASSERT( Utility::HistogramDistribution::doesTypeNameMatch( "Histogram Distribution" ) );
  TEST_ASSERT( Utility::HistogramDistribution::doesTypeNameMatch( "Histogram" ) );
  TEST_ASSERT( Utility::HistogramDistribution::doesTypeNameMatch( "histogram" ) );
  TEST_ASSERT( Utility::HistogramDistribution::doesTypeNameMatch( "HISTOGRAM" ) );
  TEST_ASSERT( !Utility::HistogramDistribution::doesTypeNameMatch( "HIST" ) );
}

//---------------------------------------------------------------------------//
// Check if the type name matches the unit-aware distribution type name
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, doesTypeNameMatch )
{
  TEST_ASSERT( (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::doesTypeNameMatch( "Histogram Distribution" )) );
  TEST_ASSERT( (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::doesTypeNameMatch( "Histogram" )) );
  TEST_ASSERT( (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::doesTypeNameMatch( "histogram" )) );
  TEST_ASSERT( (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::doesTypeNameMatch( "HISTOGRAM" )) );
  TEST_ASSERT( !(Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::doesTypeNameMatch( "HIST" )) );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( HistogramDistribution, isTabular )
{
  TEST_ASSERT( pdf_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, isTabular )
{
  TEST_ASSERT( unit_aware_pdf_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( HistogramDistribution, isContinuous )
{
  TEST_ASSERT( pdf_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, isContinuous )
{
  TEST_ASSERT( unit_aware_pdf_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( HistogramDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( pdf_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !pdf_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( pdf_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !pdf_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  std::vector<double> bin_boundaries( 3 ), bin_values( 2 );
  bin_boundaries[0] = 1.0;
  bin_boundaries[1] = 2.0;
  bin_boundaries[2] = 3.0;

  bin_values[0] = 0.5;
  bin_values[1] = 1.0;
  
  Utility::HistogramDistribution test_dist( bin_boundaries, bin_values );

  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( unit_aware_pdf_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !unit_aware_pdf_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( unit_aware_pdf_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_pdf_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  std::vector<double> bin_boundaries( 3 ), bin_values( 2 );
  bin_boundaries[0] = 1.0;
  bin_boundaries[1] = 2.0;
  bin_boundaries[2] = 3.0;

  bin_values[0] = 0.5;
  bin_values[1] = 1.0;
  
  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>
    test_dist( bin_boundaries, bin_values );

  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
TEUCHOS_UNIT_TEST( HistogramDistribution, toString )
{
  std::string dist_string = Utility::toString( *pdf_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  dist_string = Utility::toString( *cdf_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be converted to a string
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, toString )
{
  std::string dist_string = Utility::toString( *unit_aware_pdf_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  dist_string = Utility::toString( *unit_aware_cdf_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
TEUCHOS_UNIT_TEST( HistogramDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *pdf_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();
  
  Utility::toStream( oss, *cdf_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, toStream )
{
  std::ostringstream oss;
  
  Utility::toStream( oss, *unit_aware_pdf_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *unit_aware_cdf_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
TEUCHOS_UNIT_TEST( HistogramDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *pdf_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();
  
  oss << *cdf_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, ostream_operator )
{
  std::ostringstream oss;
  
  oss << *unit_aware_pdf_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_cdf_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a string
TEUCHOS_UNIT_TEST( HistogramDistribution, fromString )
{
  Utility::HistogramDistribution test_dist =
    Utility::fromString<Utility::HistogramDistribution>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  test_dist = Utility::fromString<Utility::HistogramDistribution>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  test_dist = Utility::fromString<Utility::HistogramDistribution>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a string
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, fromString )
{
  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> test_dist =
    Utility::fromString<decltype(test_dist)>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  test_dist = Utility::fromString<decltype(test_dist)>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  test_dist = Utility::fromString<decltype(test_dist)>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( HistogramDistribution, fromStream )
{
  std::istringstream iss( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
  Utility::HistogramDistribution test_dist;

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );  

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, fromStream )
{
  std::istringstream iss( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>
    test_dist;

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( HistogramDistribution, istream_operator )
{
  std::istringstream iss( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
  Utility::HistogramDistribution test_dist;

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );
  iss.clear();

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );
  iss.clear();

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, istream_operator )
{
  std::istringstream iss( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>
    test_dist;

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );
  iss.clear();

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );
  iss.clear();

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree
TEUCHOS_UNIT_TEST( HistogramDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *pdf_distribution );

  Utility::HistogramDistribution copy_dist =
    ptree.get<Utility::HistogramDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );

  ptree.put( "test distribution", *tab_pdf_distribution );

  copy_dist = ptree.get<Utility::HistogramDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( tab_pdf_distribution.get() ) );

  ptree.put( "test distribution", *cdf_distribution );

  copy_dist = ptree.get<Utility::HistogramDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  ptree.put( "test distribution", *tab_cdf_distribution );

  copy_dist = ptree.get<Utility::HistogramDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( tab_cdf_distribution.get() ) );

  ptree.clear();

  // Use the PropertyTreeCompatibleOjbect interface
  ptree = pdf_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::HistogramDistribution>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );

  ptree = pdf_distribution->toPropertyTree( false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = pdf_distribution->toPropertyTree();

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = cdf_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::HistogramDistribution>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  ptree = cdf_distribution->toPropertyTree( false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = cdf_distribution->toPropertyTree();

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( *pdf_distribution, true );

  copy_dist = ptree.get_value<Utility::HistogramDistribution>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );

  ptree = Utility::toPropertyTree( *pdf_distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *pdf_distribution );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *tab_pdf_distribution, true );

  copy_dist = ptree.get_value<Utility::HistogramDistribution>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( tab_pdf_distribution.get() ) );

  ptree = Utility::toPropertyTree( *tab_pdf_distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *tab_pdf_distribution );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to a property tree
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *unit_aware_pdf_distribution );

  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> copy_dist =
    ptree.get<decltype(copy_dist)>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_pdf_distribution.get() ) );

  ptree.put( "test distribution", *unit_aware_tab_pdf_distribution );

  copy_dist = ptree.get<decltype(copy_dist)>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_tab_pdf_distribution.get() ) );

  ptree.put( "test distribution", *unit_aware_cdf_distribution );

  copy_dist = ptree.get<decltype(copy_dist)>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_cdf_distribution.get() ) );

  ptree.put( "test distribution", *unit_aware_tab_cdf_distribution );

  copy_dist = ptree.get<decltype(copy_dist)>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_tab_cdf_distribution.get() ) );

  ptree.clear();

  // Use the PropertyTreeCompatibleOjbect interface
  ptree = unit_aware_pdf_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<decltype(copy_dist)>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_pdf_distribution.get() ) );

  ptree = unit_aware_pdf_distribution->toPropertyTree( false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = unit_aware_pdf_distribution->toPropertyTree();

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = unit_aware_cdf_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<decltype(copy_dist)>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_cdf_distribution.get() ) );

  ptree = unit_aware_cdf_distribution->toPropertyTree( false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = unit_aware_cdf_distribution->toPropertyTree();

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( *unit_aware_pdf_distribution, true );

  copy_dist = ptree.get_value<decltype(copy_dist)>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_pdf_distribution.get() ) );

  ptree = Utility::toPropertyTree( *unit_aware_pdf_distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *unit_aware_pdf_distribution );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_pdf_distribution, true );

  copy_dist = ptree.get_value<decltype(copy_dist)>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_tab_pdf_distribution.get() ) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_pdf_distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_pdf_distribution );

  TEST_EQUALITY_CONST( ptree.size(), 3 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be read from a property tree
TEUCHOS_UNIT_TEST( HistogramDistribution, fromPropertyTree )
{
  Utility::HistogramDistribution dist;

  std::vector<std::string> unused_children;

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution A" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution B" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8 ), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution C" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8 ), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution D" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), -2.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( dist.evaluate( -1.5 ), 2.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 1.5 ), 2.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution E" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8 ), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  unused_children.clear();

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution F" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8 ), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "Dummy" );

  unused_children.clear();

  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution G" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution H" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution I" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution J" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution K" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution L" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution M" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution N" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution O" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution P" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution Q" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution R" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution S" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution T" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution U" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution V" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution W" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution X" ) ),
              Utility::PropertyTreeConversionException );  

  // Use the property tree helper methds
  dist = Utility::fromPropertyTree<Utility::HistogramDistribution>(
                     test_dists_ptree->get_child( "Histogram Distribution A" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<Utility::HistogramDistribution>(
                     test_dists_ptree->get_child( "Histogram Distribution B" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8 ), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<Utility::HistogramDistribution>(
                     test_dists_ptree->get_child( "Histogram Distribution C" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8 ), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<Utility::HistogramDistribution>(
                     test_dists_ptree->get_child( "Histogram Distribution D" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), -2.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( dist.evaluate( -1.5 ), 2.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 1.5 ), 2.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<Utility::HistogramDistribution>(
                     test_dists_ptree->get_child( "Histogram Distribution E" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8 ), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  unused_children.clear();

  dist = Utility::fromPropertyTree<Utility::HistogramDistribution>(
                     test_dists_ptree->get_child( "Histogram Distribution F" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6 ), 1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8 ), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "Dummy" );

  unused_children.clear();

  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution G" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution H" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution I" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution J" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution K" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution L" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution M" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution N" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution O" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution P" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution Q" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution R" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution S" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution T" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution U" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution V" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution W" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<Utility::HistogramDistribution>( test_dists_ptree->get_child( "Histogram Distribution X" ) ),
              Utility::PropertyTreeConversionException );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be read from a property tree
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, fromPropertyTree )
{
  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> dist;

  std::vector<std::string> unused_children;

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution A" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist, *dynamic_cast<decltype(dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution B" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*MeV );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution C" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*MeV );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution D" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), -2.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi*MeV );
  TEST_EQUALITY_CONST( dist.evaluate( -1.5*MeV ), 2.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.0*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 1.5*MeV ), 2.0*si::mole );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution E" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*MeV );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  unused_children.clear();

  dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution F" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*MeV );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "Dummy" );

  unused_children.clear();

  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution G" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution H" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution I" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution J" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution K" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution L" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution M" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution N" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution O" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution P" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution Q" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution R" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution S" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution T" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution U" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution V" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution W" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Histogram Distribution X" ) ),
              Utility::PropertyTreeConversionException );  

  // Use the property tree helper methds
  dist = Utility::fromPropertyTree<decltype(dist)>(
                     test_dists_ptree->get_child( "Histogram Distribution A" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist, *dynamic_cast<decltype(dist)*>( unit_aware_pdf_distribution.get() ) );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<decltype(dist)>(
                     test_dists_ptree->get_child( "Histogram Distribution B" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*MeV );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<decltype(dist)>(
                     test_dists_ptree->get_child( "Histogram Distribution C" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*MeV );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<decltype(dist)>(
                     test_dists_ptree->get_child( "Histogram Distribution D" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), -2.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi*MeV );
  TEST_EQUALITY_CONST( dist.evaluate( -1.5*MeV ), 2.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.0*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 1.5*MeV ), 2.0*si::mole );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist = Utility::fromPropertyTree<decltype(dist)>(
                     test_dists_ptree->get_child( "Histogram Distribution E" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*MeV );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  unused_children.clear();

  dist = Utility::fromPropertyTree<decltype(dist)>(
                     test_dists_ptree->get_child( "Histogram Distribution F" ),
                     unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*MeV );
  TEST_EQUALITY_CONST( dist.evaluate( 0.2*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.4*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.6*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( dist.evaluate( 0.8*MeV ), 1.0*si::mole );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "Dummy" );

  unused_children.clear();

  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution G" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution H" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution I" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution J" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution K" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution L" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution M" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution N" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution O" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution P" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution Q" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution R" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution S" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution T" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution U" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution V" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution W" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( Utility::fromPropertyTree<decltype(dist)>( test_dists_ptree->get_child( "Histogram Distribution X" ) ),
              Utility::PropertyTreeConversionException );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareHistogramDistribution,
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
  Utility::UnitAwareHistogramDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareHistogramDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareHistogramDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1.0/6);
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 1.0 );

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
  Utility::setQuantity( inv_indep_quantity_a, 1.0/3.0 );
  Utility::setQuantity( dep_quantity_a, 2.0 );

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
			1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-6 );
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

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareHistogramDistribution,
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
  {
    std::vector<double> bin_boundaries( 4 );
    bin_boundaries[0] = -2.0;
    bin_boundaries[1] = -1.0;
    bin_boundaries[2] = 1.0;
    bin_boundaries[3] = 2.0;

    std::vector<double> bin_values( 3 );
    bin_values[0] = 2.0;
    bin_values[1] = 1.0;
    bin_values[2] = 2.0;

    tab_pdf_distribution.reset(
			   new Utility::HistogramDistribution( bin_boundaries,
							       bin_values) );

    pdf_distribution = tab_pdf_distribution;
  }

  // Create a distribution using the cdf constructor
  {
    std::vector<double> bin_boundaries( 4 );
    bin_boundaries[0] = -2.0;
    bin_boundaries[1] = -1.0;
    bin_boundaries[2] = 1.0;
    bin_boundaries[3] = 2.0;

    std::vector<double> cdf_values( 3 );
    cdf_values[0] = 2.0;
    cdf_values[1] = 4.0;
    cdf_values[2] = 6.0;

    tab_cdf_distribution.reset(
			  new Utility::HistogramDistribution( bin_boundaries,
							      cdf_values,
                                                              true ) );

    cdf_distribution = tab_cdf_distribution;
  }

  // Create a unit-aware distribution using the standard constructor
  {
    std::vector<quantity<MegaElectronVolt> > bin_boundaries( 4 );
    bin_boundaries[0] = -2.0*MeV;
    bin_boundaries[1] = -1.0*MeV;
    bin_boundaries[2] = 1.0*MeV;
    bin_boundaries[3] = 2.0*MeV;

    std::vector<quantity<si::amount> > bin_values( 3 );
    bin_values[0] = 2.0*si::mole;
    bin_values[1] = 1.0*si::mole;
    bin_values[2] = 2.0*si::mole;

    unit_aware_tab_pdf_distribution.reset(
      new Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>(
								bin_boundaries,
								bin_values) );

    unit_aware_pdf_distribution = unit_aware_tab_pdf_distribution;
  }

  // Create a unit-aware distribution using the cdf constructor
  {
    std::vector<quantity<MegaElectronVolt> > bin_boundaries( 4 );
    bin_boundaries[0] = -2.0*MeV;
    bin_boundaries[1] = -1.0*MeV;
    bin_boundaries[2] = 1.0*MeV;
    bin_boundaries[3] = 2.0*MeV;

    std::vector<double> cdf_values( 3 );
    cdf_values[0] = 2.0;
    cdf_values[1] = 4.0;
    cdf_values[2] = 6.0;

    unit_aware_tab_cdf_distribution.reset(
      new Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>(
								bin_boundaries,
								cdf_values ) );

    unit_aware_cdf_distribution = unit_aware_tab_cdf_distribution;
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHistogramDistribution.cpp
//---------------------------------------------------------------------------//
