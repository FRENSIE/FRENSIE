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

// FRENSIE Includes
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing types
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

std::shared_ptr<Utility::UnivariateDistribution> distribution;
std::shared_ptr<Utility::TabularUnivariateDistribution> tab_distribution;
std::shared_ptr<Utility::UnivariateDistribution> cdf_cons_distribution;
std::shared_ptr<Utility::TabularUnivariateDistribution> tab_cdf_cons_distribution;
std::shared_ptr<Utility::UnivariateDistribution> repeat_vals_distribution;
std::shared_ptr<Utility::TabularUnivariateDistribution> tab_repeat_vals_distribution;

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<ElectronVolt,si::amount> >
  unit_aware_distribution;
std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<ElectronVolt,si::amount> >
  unit_aware_tab_distribution;

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<ElectronVolt,si::amount> >
  unit_aware_cdf_cons_distribution;
std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<ElectronVolt,si::amount> >
  unit_aware_tab_cdf_cons_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( DiscreteDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluate( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluate( -1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluate( -0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluate( 0.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluate( 0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluate( 1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluate( 2.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluate( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluate( -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluate( -0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluate( 0.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluate( 0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluate( 1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.1*eV ),
		       0.25*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*eV ),
		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.5*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 5.0*eV ),
		       2.7*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 100.0*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1e3*eV ),
				  0.05*si::mole,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2e3*eV ),
		       0.0*si::mole );

  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluate( 0.0*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluate( 0.1*eV ),
		       0.0625*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluate( 0.5*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluate( 1.0*eV ),
		       0.25*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluate( 2.5*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluate( 5.0*eV ),
		       0.675*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluate( 100.0*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			  unit_aware_cdf_cons_distribution->evaluate( 1e3*eV ),
			  0.0125*si::mole,
			  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluate( 2e3*eV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( DiscreteDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 0.50 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluatePDF( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluatePDF( -1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluatePDF( -0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluatePDF( 0.0 ), 0.50 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluatePDF( 0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluatePDF( 1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->evaluatePDF( 2.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluatePDF( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluatePDF( -1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluatePDF( -0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluatePDF( 0.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluatePDF( 0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluatePDF( 1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( repeat_vals_distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*eV ),
		       0.0/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.1*eV ),
		       0.0625/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.5*eV ),
		       0.0/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 1.0*eV ),
		       0.25/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 2.5*eV ),
		       0.0/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 5.0*eV ),
		       0.675/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 100.0*eV ),
		       0.0/eV );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			        unit_aware_distribution->evaluatePDF( 1e3*eV ),
				0.0125/eV,
				1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 2e3*eV ),
		       0.0/eV );

  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluatePDF( 0.0*eV ),
		       0.0/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluatePDF( 0.1*eV ),
		       0.0625/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluatePDF( 0.5*eV ),
		       0.0/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluatePDF( 1.0*eV ),
		       0.25/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluatePDF( 2.5*eV ),
		       0.0/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluatePDF( 5.0*eV ),
		       0.675/eV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluatePDF(100.0*eV),
		       0.0/eV );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		       unit_aware_cdf_cons_distribution->evaluatePDF( 1e3*eV ),
		       0.0125/eV,
		       1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->evaluatePDF( 2e3*eV ),
		       0.0/eV );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
FRENSIE_UNIT_TEST( DiscreteDistribution, evaluateCDF )
{
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -0.5 ), 0.25 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 0.0 ), 0.75 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 0.5 ), 0.75 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 2.0 ), 1.0 );

  FRENSIE_CHECK_EQUAL( tab_cdf_cons_distribution->evaluateCDF( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_cdf_cons_distribution->evaluateCDF( -1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( tab_cdf_cons_distribution->evaluateCDF( -0.5 ), 0.25 );
  FRENSIE_CHECK_EQUAL( tab_cdf_cons_distribution->evaluateCDF( 0.0 ), 0.75 );
  FRENSIE_CHECK_EQUAL( tab_cdf_cons_distribution->evaluateCDF( 0.5 ), 0.75 );
  FRENSIE_CHECK_EQUAL( tab_cdf_cons_distribution->evaluateCDF( 1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_cdf_cons_distribution->evaluateCDF( 2.0 ), 1.0 );

  FRENSIE_CHECK_EQUAL( tab_repeat_vals_distribution->evaluateCDF( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_repeat_vals_distribution->evaluateCDF( -1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( tab_repeat_vals_distribution->evaluateCDF( -0.5 ), 0.25 );
  FRENSIE_CHECK_EQUAL( tab_repeat_vals_distribution->evaluateCDF( 0.0 ), 0.75 );
  FRENSIE_CHECK_EQUAL( tab_repeat_vals_distribution->evaluateCDF( 0.5 ), 0.75 );
  FRENSIE_CHECK_EQUAL( tab_repeat_vals_distribution->evaluateCDF( 1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_repeat_vals_distribution->evaluateCDF( 2.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, evaluateCDF )
{
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 0.0*eV ),
		       0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 0.1*eV ),
		       0.0625 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 0.5*eV ),
		       0.0625 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 1.0*eV ),
		       0.3125 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 2.5*eV ),
		       0.3125 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 5.0*eV ),
		       0.9875 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF(100.0*eV),
		       0.9875 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 1e3*eV ),
		       1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 2e3*eV ),
		       1.0 );

  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 0.0*eV ),
		   0.0 );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 0.1*eV ),
		   0.0625 );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 0.5*eV ),
		   0.0625 );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 1.0*eV ),
		   0.3125 );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 2.5*eV ),
		   0.3125 );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 5.0*eV ),
		   0.9875 );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF(100.0*eV),
		   0.9875 );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 1e3*eV ),
		   1.0 );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 2e3*eV ),
		   1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DiscreteDistribution, sample )
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
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  // Test the third bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  // Test the third bin
  sample = cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

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
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = repeat_vals_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = repeat_vals_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = repeat_vals_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the third bin
  sample = repeat_vals_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = repeat_vals_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  // Test the fourth bin
  sample = repeat_vals_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = repeat_vals_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  // Test the fifth bin
  sample = repeat_vals_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = repeat_vals_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, sample )
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
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  // Test the third bin
  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );

  // Test the fourth bin
  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1e3*eV );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  sample = unit_aware_cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  sample = unit_aware_cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  // Test the third bin
  sample = unit_aware_cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );

  sample = unit_aware_cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );

  // Test the fourth bin
  sample = unit_aware_cdf_cons_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1e3*eV );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DiscreteDistribution, sampleAndRecordTrials )
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
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  // Test the second bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 4 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 5 );

  // Test the third bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 6 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 7 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Test the first bin
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  // Test the second bin
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 4 );

  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 5 );

  // Test the third bin
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 6 );

  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 7 );

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
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  // Test the second bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 4 );

  // Test the third bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 5 );

  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 6 );

  // Test the fourth bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 7 );

  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 8 );

  // Test the fifth bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 9 );

  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 10 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, sampleAndRecordTrials )
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
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  // Test the second bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  // Test the third bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  // Test the fourth bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1e3*eV );
  FRENSIE_CHECK_EQUAL( trials, 7u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Test the first bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  // Test the second bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  // Test the third bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  // Test the fourth bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1e3*eV );
  FRENSIE_CHECK_EQUAL( trials, 7u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DiscreteDistribution, sampleAndRecordBinIndex )
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

  size_t bin_index;

  // Test the first bin
  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  // Test the second bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  // Test the third bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  // Test the third bin
  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

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
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  // Test the fourth bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 3u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 3u );

  // Test the fifth bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 4u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 4u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, sampleAndRecordBinIndex )
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

  size_t bin_index = 0;

  // Test the first bin
  quantity<ElectronVolt> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  // Test the second bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  // Test the third bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  // Test the fourth bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1e3*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 3u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  // Test the third bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  // Test the fourth bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1e3*eV );
  FRENSIE_CHECK_EQUAL( bin_index, 3u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DiscreteDistribution, sampleWithRandomNumber )
{
  // Test the first bin
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.2 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.25 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = tab_distribution->sampleWithRandomNumber( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.75 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  // Test the third bin
  sample = tab_distribution->sampleWithRandomNumber( 0.85 );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.2 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.25 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.75 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  // Test the third bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.85 );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  // Test the first bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.0625 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.2 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.25 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.75 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  // Test the fourth bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.85 );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.9375 );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  // Test the fifth bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.95 );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, sampleWithRandomNumber )
{
  // Test the first bin
  quantity<ElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.0625 );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.3 );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.3125 );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  // Test the third bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.9 );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.9875 );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );

  // Test the fourth bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0-1e-15 );
  FRENSIE_CHECK_EQUAL( sample, 1e3*eV );

  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.0625 );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.3 );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.3125 );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  // Test the third bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.9 );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.9875 );
  FRENSIE_CHECK_EQUAL( sample, 5.0*eV );

  // Test the fourth bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 1.0-1e-15 );
  FRENSIE_CHECK_EQUAL( sample, 1e3*eV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DiscreteDistribution, sampleInSubrange )
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
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

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
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, sampleInSubrange )
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
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DiscreteDistribution, sampleWithRandomNumberInSubrange )
{
  // Test the first bin
  double sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.2, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0/3.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.2, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 1.0/3.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  // Test the first bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 1.0/12, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 0.2, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 1.0/3, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution,
		   sampleWithRandomNumberInSubrange )
{
  // Test the first bin
  quantity<ElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.2, 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.6, 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.99, 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.0, 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.2, 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 0.1*eV );

  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.6, 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );

  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.99, 3.0*eV );
  FRENSIE_CHECK_EQUAL( sample, 1.0*eV );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( DiscreteDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 1.0 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(), 1e3*eV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->getUpperBoundOfIndepVar(), 1e3*eV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution dependent variable can be
// returned
FRENSIE_UNIT_TEST( DiscreteDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), -1.0 );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->getLowerBoundOfIndepVar(),-1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution dependent variable
// can be returned
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(), 0.1*eV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->getLowerBoundOfIndepVar(), 0.1*eV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( DiscreteDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( cdf_cons_distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_cons_distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( DiscreteDistribution, isTabular )
{
  FRENSIE_CHECK( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, isTabular )
{
  FRENSIE_CHECK( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( DiscreteDistribution, isContinuous )
{
  FRENSIE_CHECK( !distribution->isContinuous() );

  {
    Utility::DiscreteDistribution tmp_dist( {-1.0, 0.0, 1.0},
                                            {1.0, 2.0, 1.0},
                                            false,
                                            true );

    FRENSIE_CHECK( tmp_dist.isContinuous() );

    Utility::DiscreteDistribution copy_tmp_dist( tmp_dist );

    FRENSIE_CHECK( copy_tmp_dist.isContinuous() );
  }
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, isContinuous )
{
  FRENSIE_CHECK( !unit_aware_distribution->isContinuous() );

  {
    Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>
      tmp_dist( std::vector<quantity<ElectronVolt> >({-1.0*eV, 0.0*eV, 1.0*eV}),
                std::vector<quantity<si::amount> >({1.0*si::mole, 2.0*si::mole, 1.0*si::mole}),
                true );

    FRENSIE_CHECK( tmp_dist.isContinuous() );

    Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>
      copy_tmp_dist( tmp_dist );

    FRENSIE_CHECK( copy_tmp_dist.isContinuous() );
  }
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( DiscreteDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( DiscreteDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::DiscreteDistribution();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Discrete Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<double> >(),
                       std::vector<double>({0.0}) );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<double> >(),
                       std::vector<double>({1.0}) );

  oss.str( "" );
  oss.clear();

  oss << *distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Discrete Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<double> >(),
                       std::vector<double>({-1.0, 0.0, 1.0}) );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<double> >(),
                       std::vector<double>({1.0, 2.0, 1.0}) );

  oss.str( "" );
  oss.clear();

  oss << *cdf_cons_distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Discrete Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<double> >(),
                       std::vector<double>({-1.0, 0.0, 1.0}) );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<double> >(),
                       std::vector<double>({0.25, 0.5, 0.25}) );

  oss.str( "" );
  oss.clear();

  oss << *repeat_vals_distribution;

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Discrete Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<double> >(),
                       std::vector<double>({-1.0, 0.0, 1.0}) );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<double> >(),
                       std::vector<double>({0.25, 0.5, 0.25}) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareDiscreteDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Discrete Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<ElectronVolt>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<quantity<ElectronVolt> > >(),
                       std::vector<quantity<ElectronVolt> >({0.0*eV}) );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<quantity<si::amount> > >(),
                       std::vector<quantity<si::amount> >({1.0*si::mole}) );

  oss.str( "" );
  oss.clear();
  
  oss << *unit_aware_distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Discrete Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<ElectronVolt>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<quantity<ElectronVolt> > >(),
                       std::vector<quantity<ElectronVolt> >({0.1*eV, 1.0*eV, 5.0*eV, 1000*eV}) );
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_data["dependent values"].toType<std::vector<quantity<si::amount> > >(),
                                   std::vector<quantity<si::amount> >({0.25*si::mole, 1.0*si::mole, 2.7*si::mole, 0.05*si::mole}),
                                   1e-14 );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_cdf_cons_distribution;

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Discrete Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<ElectronVolt>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<quantity<ElectronVolt> > >(),
                       std::vector<quantity<ElectronVolt> >({0.1*eV, 1.0*eV, 5.0*eV, 1000*eV}) );
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_data["dependent values"].toType<std::vector<quantity<si::amount> > >(),
                                   std::vector<quantity<si::amount> >({0.25*si::mole, 1.0*si::mole, 2.7*si::mole, 0.05*si::mole}),
                                   1e-14 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DiscreteDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_discrete_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some discrete distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    std::vector<double> independent_values( 3 );
    independent_values[0] = -1.0;
    independent_values[1] = 0.0;
    independent_values[2] = 1.0;
    
    std::vector<double> dependent_values( 3 );
    dependent_values[0] = 1.0;
    dependent_values[1] = 2.0;
    dependent_values[2] = 1.0;
    
    Utility::DiscreteDistribution
      discrete_dist_a( independent_values, dependent_values );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "discrete_dist_a", discrete_dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "discrete_dist_b", cdf_cons_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );
  
  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::DiscreteDistribution discrete_dist_a;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "discrete_dist_a", discrete_dist_a ) );
  FRENSIE_CHECK_EQUAL( discrete_dist_a.getLowerBoundOfIndepVar(), -1.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_a.getUpperBoundOfIndepVar(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_a.evaluate( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_a.evaluate( -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_a.evaluate( -0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_a.evaluate( 0.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_a.evaluate( 0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_a.evaluate( 1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_a.evaluate( 2.0 ), 0.0 );

  std::shared_ptr<Utility::UnivariateDistribution> discrete_dist_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "discrete_dist_b", discrete_dist_b ) );
  FRENSIE_CHECK_EQUAL( discrete_dist_b->getLowerBoundOfIndepVar(),-1.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_b->getUpperBoundOfIndepVar(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_b->evaluate( -2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_b->evaluate( -1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( discrete_dist_b->evaluate( -0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_b->evaluate( 0.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( discrete_dist_b->evaluate( 0.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( discrete_dist_b->evaluate( 1.0 ), 0.25 );
  FRENSIE_CHECK_EQUAL( discrete_dist_b->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareDiscreteDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_unit_aware_discrete_dist" );
  std::ostringstream archive_ostream;

  // Createand archive some discrete distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
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
    
    Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>
      unit_aware_discrete_dist_a( independent_quantities, dependent_quantities );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "discrete_dist_a", unit_aware_discrete_dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "discrete_dist_b", unit_aware_cdf_cons_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );
  
  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>
    unit_aware_discrete_dist_a;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "discrete_dist_a", unit_aware_discrete_dist_a ) );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_a.getLowerBoundOfIndepVar(), 0.1*eV );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_a.getUpperBoundOfIndepVar(), 1e3*eV );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_a.evaluate( 0.0*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_a.evaluate( 0.1*eV ),
		       0.25*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_a.evaluate( 0.5*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_a.evaluate( 1.0*eV ),
		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_a.evaluate( 2.5*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_a.evaluate( 5.0*eV ),
		       2.7*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_a.evaluate( 100.0*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_discrete_dist_a.evaluate( 1e3*eV ),
                                   0.05*si::mole,
                                   1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_a.evaluate( 2e3*eV ),
		       0.0*si::mole );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<ElectronVolt,si::amount> >
    unit_aware_discrete_dist_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "discrete_dist_b", unit_aware_discrete_dist_b ) );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_b->getLowerBoundOfIndepVar(), 0.1*eV );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_b->getUpperBoundOfIndepVar(), 1e3*eV );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_b->evaluate( 0.0*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_b->evaluate( 0.1*eV ),
		       0.0625*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_b->evaluate( 0.5*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_b->evaluate( 1.0*eV ),
		       0.25*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_b->evaluate( 2.5*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_b->evaluate( 5.0*eV ),
		       0.675*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_b->evaluate( 100.0*eV ),
		       0.0*si::mole );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			  unit_aware_discrete_dist_b->evaluate( 1e3*eV ),
			  0.0125*si::mole,
			  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_discrete_dist_b->evaluate( 2e3*eV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareDiscreteDistribution,
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
  Utility::setQuantity( inv_indep_quantity_a, 0.0 );
  Utility::setQuantity( dep_quantity_a, 0.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  Utility::setQuantity( inv_indep_quantity_b, 0.0 );
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

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDiscreteDistribution.cpp
//---------------------------------------------------------------------------//
