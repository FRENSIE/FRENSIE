//---------------------------------------------------------------------------//
//!
//! \file   tstThirtyTwoEquiprobableBinDistribution.cpp
//! \author Alex Robinson
//! \brief  Thirty-two equiprobable bin distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_EquiprobableBinDistribution.hpp"
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

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution;
std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<MegaElectronVolt,si::amount> >
  unit_aware_tab_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -17.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -16.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -14.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -13.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -12.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -11.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -10.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -9.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -8.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -7.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -6.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -5.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -4.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -3.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -2.0 ), 1.0/48 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -0.5 ), 1.0/16 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 1.0/16 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5 ), 1.0/48 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 5.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 6.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 7.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 8.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 9.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 10.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 11.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 12.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 13.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 14.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 16.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 17.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV ),
		       2.5*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.1*MeV ),
		       0.25/0.9*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV ),
		       0.0625*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 5.0*MeV ),
		       0.05*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 10.0*MeV ),
		       0.05*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 11.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -17.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -16.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -14.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -13.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -12.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -11.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -10.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -9.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -8.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -7.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -6.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -5.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -4.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -3.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -2.0 ), 1.0/48 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -0.5 ), 1.0/16 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 1.0/16 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.5 ), 1.0/48 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 3.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 4.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 5.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 6.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 7.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 8.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 9.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 10.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 11.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 12.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 13.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 14.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 16.0 ), 1.0/32 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( -1.0*MeV ),
		       0.0/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       2.5/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.1*MeV ),
		       0.25/0.9/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
		       0.0625/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 5.0*MeV ),
		       0.05/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 10.0*MeV ),
		       0.05/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 11.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, evaluateCDF )
{
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -17.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -16.0 ), 0.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -14.0 ), 2.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -13.0 ), 3.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -12.0 ), 4.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -11.0 ), 5.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -10.0 ), 6.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -9.0 ), 7.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -8.0 ), 8.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -7.0 ), 9.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -6.0 ), 10.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -5.0 ), 11.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -4.0 ), 12.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -3.0 ), 13.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -2.0 ), 14.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -0.5 ), 15.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -0.25 ), 31.0/64 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 0.0 ), 16.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 0.25 ), 33.0/64 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 0.5 ), 17.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 2.0 ), 18.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 3.0 ), 19.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 4.0 ), 20.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 5.0 ), 21.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 6.0 ), 22.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 7.0 ), 23.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 8.0 ), 24.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 9.0 ), 25.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 10.0 ), 26.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 11.0 ), 27.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 12.0 ), 28.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 13.0 ), 29.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 14.0 ), 30.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 15.0 ), 31.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 16.0 ), 32.0/32 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 17.0 ), 32.0/32 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution, evaluateCDF )
{
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( -1.0*MeV ),
		       0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 0.0*MeV ),
		       0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 0.1*MeV ),
		       0.25 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 1.0*MeV ),
		       0.5 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 5.0*MeV ),
		       0.75 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 10.0*MeV ),
		       1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 11.0*MeV ),
		       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, sample )
{
  std::vector<double> fake_stream( 65 );
  // First bin
  fake_stream[0] = 0.0;      fake_stream[1] = 1.0/64;
  // Second bin
  fake_stream[2] = 2.0/64;   fake_stream[3] = 3.0/64;
  // Third bin
  fake_stream[4] = 4.0/64;   fake_stream[5] = 5.0/64;
  // Fourth bin
  fake_stream[6] = 6.0/64;   fake_stream[7] = 7.0/64;
  // Fifth bin
  fake_stream[8] = 8.0/64;   fake_stream[9] = 9.0/64;
  // Sixth bin
  fake_stream[10] = 10.0/64; fake_stream[11] = 11.0/64;
  // Seventh bin
  fake_stream[12] = 12.0/64; fake_stream[13] = 13.0/64;
  // Eighth bin
  fake_stream[14] = 14.0/64; fake_stream[15] = 15.0/64;
  // Ninth bin
  fake_stream[16] = 16.0/64; fake_stream[17] = 17.0/64;
  // Tenth bin
  fake_stream[18] = 18.0/64; fake_stream[19] = 19.0/64;
  // Eleventh bin
  fake_stream[20] = 20.0/64; fake_stream[21] = 21.0/64;
  // Twelfth bin
  fake_stream[22] = 22.0/64; fake_stream[23] = 23.0/64;
  // Thirteenth bin
  fake_stream[24] = 24.0/64; fake_stream[25] = 25.0/64;
  // Fourteenth bin
  fake_stream[26] = 26.0/64; fake_stream[27] = 27.0/64;
  // Fifteenth bin
  fake_stream[28] = 28.0/64; fake_stream[29] = 29.0/64;
  // Sixteenth bin
  fake_stream[30] = 30.0/64; fake_stream[31] = 31.0/64;
  // Seventeenth bin
  fake_stream[32] = 32.0/64; fake_stream[33] = 33.0/64;
  // Eighteenth bin
  fake_stream[34] = 34.0/64; fake_stream[35] = 35.0/64;
  // Nineteenth bin
  fake_stream[36] = 36.0/64; fake_stream[37] = 37.0/64;
  // Twentieth bin
  fake_stream[38] = 38.0/64; fake_stream[39] = 39.0/64;
  // Twenty-first bin
  fake_stream[40] = 40.0/64; fake_stream[41] = 41.0/64;
  // Twenty-second bin
  fake_stream[42] = 42.0/64; fake_stream[43] = 43.0/64;
  // Twenty-third bin
  fake_stream[44] = 44.0/64; fake_stream[45] = 45.0/64;
  // Twenty-fourth bin
  fake_stream[46] = 46.0/64; fake_stream[47] = 47.0/64;
  // Twenty-fifth bin
  fake_stream[48] = 48.0/64; fake_stream[49] = 49.0/64;
  // Twenty-sixth bin
  fake_stream[50] = 50.0/64; fake_stream[51] = 51.0/64;
  // Twenty-seventh bin
  fake_stream[52] = 52.0/64; fake_stream[53] = 53.0/64;
  // Twenty-eighth bin
  fake_stream[54] = 54.0/64; fake_stream[55] = 55.0/64;
  // Twenty-ninth bin
  fake_stream[56] = 56.0/64; fake_stream[57] = 57.0/64;
  // Thirtieth bin
  fake_stream[58] = 58.0/64; fake_stream[59] = 59.0/64;
  // Thirty-first bin
  fake_stream[60] = 60.0/64; fake_stream[61] = 61.0/64;
  // Thirty-second bin
  fake_stream[62] = 62.0/64; fake_stream[63] = 63.0/64;
  fake_stream[64] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // First bin
  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -16.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -15.5 );

  // Second bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -15.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -14.5 );

  // Third bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -14.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -13.5 );

  // Fourth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -13.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -12.5 );

  // Fifth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -12.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -11.5 );

  // Sixth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -11.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -10.5 );

  // Seventh bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -10.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -9.5 );

  // Eighth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -9.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -8.5 );

  // Ninth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -8.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -7.5 );

  // Tenth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -7.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -6.5 );

  // Eleventh bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -6.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -5.5 );

  // Twelfth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -5.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -4.5 );

  // Thirteenth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -4.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -3.5 );

  // Fourteenth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -3.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -2.5 );

  // Fifteenth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -2.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.25 );

  // Sixteenth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -0.5 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -0.25 );

  // Seventeenth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.25 );

  // Eighteenth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.5 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.25 );

  // Nineteenth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 2.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  // Twentieth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 3.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 3.5 );

  // Twenty-first bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 4.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 4.5 );

  // Twenty-second bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 5.5 );

  // Twenty-third bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 6.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 6.5 );

  // Twenty-fourth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 7.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 7.5 );

  // Twenty-fifth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 8.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 8.5 );

  // Twenty-sixth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 9.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 9.5 );

  // Twenty-seventh bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 10.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 10.5 );

  // Twenty-eighth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 11.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 11.5 );

  // Twenty-ninth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 12.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 12.5 );

  // Thirtieth bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 13.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 13.5 );

  // Thirty-first bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 14.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 14.5 );

  // Thirty-second bin
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 15.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 15.5 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 16.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.125;
  fake_stream[2] = 0.25;
  fake_stream[3] = 0.375;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.625;
  fake_stream[6] = 0.75;
  fake_stream[7] = 0.875;
  fake_stream[8] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // First bin
  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.05*MeV );

  // Second bin
  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.1*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.55*MeV );

  // Third bin
  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 3.0*MeV );

  // Fourth bin
  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 5.0*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 7.5*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 65 );
  // First bin
  fake_stream[0] = 0.0;      fake_stream[1] = 1.0/64;
  // Second bin
  fake_stream[2] = 2.0/64;   fake_stream[3] = 3.0/64;
  // Third bin
  fake_stream[4] = 4.0/64;   fake_stream[5] = 5.0/64;
  // Fourth bin
  fake_stream[6] = 6.0/64;   fake_stream[7] = 7.0/64;
  // Fifth bin
  fake_stream[8] = 8.0/64;   fake_stream[9] = 9.0/64;
  // Sixth bin
  fake_stream[10] = 10.0/64; fake_stream[11] = 11.0/64;
  // Seventh bin
  fake_stream[12] = 12.0/64; fake_stream[13] = 13.0/64;
  // Eighth bin
  fake_stream[14] = 14.0/64; fake_stream[15] = 15.0/64;
  // Ninth bin
  fake_stream[16] = 16.0/64; fake_stream[17] = 17.0/64;
  // Tenth bin
  fake_stream[18] = 18.0/64; fake_stream[19] = 19.0/64;
  // Eleventh bin
  fake_stream[20] = 20.0/64; fake_stream[21] = 21.0/64;
  // Twelfth bin
  fake_stream[22] = 22.0/64; fake_stream[23] = 23.0/64;
  // Thirteenth bin
  fake_stream[24] = 24.0/64; fake_stream[25] = 25.0/64;
  // Fourteenth bin
  fake_stream[26] = 26.0/64; fake_stream[27] = 27.0/64;
  // Fifteenth bin
  fake_stream[28] = 28.0/64; fake_stream[29] = 29.0/64;
  // Sixteenth bin
  fake_stream[30] = 30.0/64; fake_stream[31] = 31.0/64;
  // Seventeenth bin
  fake_stream[32] = 32.0/64; fake_stream[33] = 33.0/64;
  // Eighteenth bin
  fake_stream[34] = 34.0/64; fake_stream[35] = 35.0/64;
  // Nineteenth bin
  fake_stream[36] = 36.0/64; fake_stream[37] = 37.0/64;
  // Twentieth bin
  fake_stream[38] = 38.0/64; fake_stream[39] = 39.0/64;
  // Twenty-first bin
  fake_stream[40] = 40.0/64; fake_stream[41] = 41.0/64;
  // Twenty-second bin
  fake_stream[42] = 42.0/64; fake_stream[43] = 43.0/64;
  // Twenty-third bin
  fake_stream[44] = 44.0/64; fake_stream[45] = 45.0/64;
  // Twenty-fourth bin
  fake_stream[46] = 46.0/64; fake_stream[47] = 47.0/64;
  // Twenty-fifth bin
  fake_stream[48] = 48.0/64; fake_stream[49] = 49.0/64;
  // Twenty-sixth bin
  fake_stream[50] = 50.0/64; fake_stream[51] = 51.0/64;
  // Twenty-seventh bin
  fake_stream[52] = 52.0/64; fake_stream[53] = 53.0/64;
  // Twenty-eighth bin
  fake_stream[54] = 54.0/64; fake_stream[55] = 55.0/64;
  // Twenty-ninth bin
  fake_stream[56] = 56.0/64; fake_stream[57] = 57.0/64;
  // Thirtieth bin
  fake_stream[58] = 58.0/64; fake_stream[59] = 59.0/64;
  // Thirty-first bin
  fake_stream[60] = 60.0/64; fake_stream[61] = 61.0/64;
  // Thirty-second bin
  fake_stream[62] = 62.0/64; fake_stream[63] = 63.0/64;
  fake_stream[64] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  // First bin
  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -16.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -15.5 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  // Second bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -15.0 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -14.5 );
  FRENSIE_CHECK_EQUAL( 4.0/trials, 1.0 );

  // Third bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -14.0 );
  FRENSIE_CHECK_EQUAL( 5.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -13.5 );
  FRENSIE_CHECK_EQUAL( 6.0/trials, 1.0 );

  // Fourth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -13.0 );
  FRENSIE_CHECK_EQUAL( 7.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -12.5 );
  FRENSIE_CHECK_EQUAL( 8.0/trials, 1.0 );

  // Fifth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -12.0 );
  FRENSIE_CHECK_EQUAL( 9.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -11.5 );
  FRENSIE_CHECK_EQUAL( 10.0/trials, 1.0 );

  // Sixth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -11.0 );
  FRENSIE_CHECK_EQUAL( 11.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -10.5 );
  FRENSIE_CHECK_EQUAL( 12.0/trials, 1.0 );

  // Seventh bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -10.0 );
  FRENSIE_CHECK_EQUAL( 13.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -9.5 );
  FRENSIE_CHECK_EQUAL( 14.0/trials, 1.0 );

  // Eighth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -9.0 );
  FRENSIE_CHECK_EQUAL( 15.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -8.5 );
  FRENSIE_CHECK_EQUAL( 16.0/trials, 1.0 );

  // Ninth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -8.0 );
  FRENSIE_CHECK_EQUAL( 17.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -7.5 );
  FRENSIE_CHECK_EQUAL( 18.0/trials, 1.0 );

  // Tenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -7.0 );
  FRENSIE_CHECK_EQUAL( 19.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -6.5 );
  FRENSIE_CHECK_EQUAL( 20.0/trials, 1.0 );

  // Eleventh bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -6.0 );
  FRENSIE_CHECK_EQUAL( 21.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -5.5 );
  FRENSIE_CHECK_EQUAL( 22.0/trials, 1.0 );

  // Twelfth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -5.0 );
  FRENSIE_CHECK_EQUAL( 23.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -4.5 );
  FRENSIE_CHECK_EQUAL( 24.0/trials, 1.0 );

  // Thirteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -4.0 );
  FRENSIE_CHECK_EQUAL( 25.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -3.5 );
  FRENSIE_CHECK_EQUAL( 26.0/trials, 1.0 );

  // Fourteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -3.0 );
  FRENSIE_CHECK_EQUAL( 27.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -2.5 );
  FRENSIE_CHECK_EQUAL( 28.0/trials, 1.0 );

  // Fifteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -2.0 );
  FRENSIE_CHECK_EQUAL( 29.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.25 );
  FRENSIE_CHECK_EQUAL( 30.0/trials, 1.0 );

  // Sixteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -0.5 );
  FRENSIE_CHECK_EQUAL( 31.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -0.25 );
  FRENSIE_CHECK_EQUAL( 32.0/trials, 1.0 );

  // Seventeenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 33.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.25 );
  FRENSIE_CHECK_EQUAL( 34.0/trials, 1.0 );

  // Eighteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.5 );
  FRENSIE_CHECK_EQUAL( 35.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.25 );
  FRENSIE_CHECK_EQUAL( 36.0/trials, 1.0 );

  // Nineteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 2.0 );
  FRENSIE_CHECK_EQUAL( 37.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( 38.0/trials, 1.0 );

  // Twentieth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 3.0 );
  FRENSIE_CHECK_EQUAL( 39.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 3.5 );
  FRENSIE_CHECK_EQUAL( 40.0/trials, 1.0 );

  // Twenty-first bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 4.0 );
  FRENSIE_CHECK_EQUAL( 41.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 4.5 );
  FRENSIE_CHECK_EQUAL( 42.0/trials, 1.0 );

  // Twenty-second bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( 43.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 5.5 );
  FRENSIE_CHECK_EQUAL( 44.0/trials, 1.0 );

  // Twenty-third bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 6.0 );
  FRENSIE_CHECK_EQUAL( 45.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 6.5 );
  FRENSIE_CHECK_EQUAL( 46.0/trials, 1.0 );

  // Twenty-fourth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 7.0 );
  FRENSIE_CHECK_EQUAL( 47.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 7.5 );
  FRENSIE_CHECK_EQUAL( 48.0/trials, 1.0 );

  // Twenty-fifth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 8.0 );
  FRENSIE_CHECK_EQUAL( 49.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 8.5 );
  FRENSIE_CHECK_EQUAL( 50.0/trials, 1.0 );

  // Twenty-sixth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 9.0 );
  FRENSIE_CHECK_EQUAL( 51.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 9.5 );
  FRENSIE_CHECK_EQUAL( 52.0/trials, 1.0 );

  // Twenty-seventh bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 10.0 );
  FRENSIE_CHECK_EQUAL( 53.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 10.5 );
  FRENSIE_CHECK_EQUAL( 54.0/trials, 1.0 );

  // Twenty-eighth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 11.0 );
  FRENSIE_CHECK_EQUAL( 55.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 11.5 );
  FRENSIE_CHECK_EQUAL( 56.0/trials, 1.0 );

  // Twenty-ninth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 12.0 );
  FRENSIE_CHECK_EQUAL( 57.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 12.5 );
  FRENSIE_CHECK_EQUAL( 58.0/trials, 1.0 );

  // Thirtieth bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 13.0 );
  FRENSIE_CHECK_EQUAL( 59.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 13.5 );
  FRENSIE_CHECK_EQUAL( 60.0/trials, 1.0 );

  // Thirty-first bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 14.0 );
  FRENSIE_CHECK_EQUAL( 61.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 14.5 );
  FRENSIE_CHECK_EQUAL( 62.0/trials, 1.0 );

  // Thirty-second bin
  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 15.0 );
  FRENSIE_CHECK_EQUAL( 63.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 15.5 );
  FRENSIE_CHECK_EQUAL( 64.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 16.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( 65.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.125;
  fake_stream[2] = 0.25;
  fake_stream[3] = 0.375;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.625;
  fake_stream[6] = 0.75;
  fake_stream[7] = 0.875;
  fake_stream[8] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0u;

  // First bin
  quantity<MegaElectronVolt> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.05*MeV );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  // Second bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.1*MeV );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.55*MeV );
  FRENSIE_CHECK_EQUAL( 4.0/trials, 1.0 );

  // Third bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );
  FRENSIE_CHECK_EQUAL( 5.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 3.0*MeV );
  FRENSIE_CHECK_EQUAL( 6.0/trials, 1.0 );

  // Fourth bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 5.0*MeV );
  FRENSIE_CHECK_EQUAL( 7.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 7.5*MeV );
  FRENSIE_CHECK_EQUAL( 8.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( 9.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 65 );
  // First bin
  fake_stream[0] = 0.0;      fake_stream[1] = 1.0/64;
  // Second bin
  fake_stream[2] = 2.0/64;   fake_stream[3] = 3.0/64;
  // Third bin
  fake_stream[4] = 4.0/64;   fake_stream[5] = 5.0/64;
  // Fourth bin
  fake_stream[6] = 6.0/64;   fake_stream[7] = 7.0/64;
  // Fifth bin
  fake_stream[8] = 8.0/64;   fake_stream[9] = 9.0/64;
  // Sixth bin
  fake_stream[10] = 10.0/64; fake_stream[11] = 11.0/64;
  // Seventh bin
  fake_stream[12] = 12.0/64; fake_stream[13] = 13.0/64;
  // Eighth bin
  fake_stream[14] = 14.0/64; fake_stream[15] = 15.0/64;
  // Ninth bin
  fake_stream[16] = 16.0/64; fake_stream[17] = 17.0/64;
  // Tenth bin
  fake_stream[18] = 18.0/64; fake_stream[19] = 19.0/64;
  // Eleventh bin
  fake_stream[20] = 20.0/64; fake_stream[21] = 21.0/64;
  // Twelfth bin
  fake_stream[22] = 22.0/64; fake_stream[23] = 23.0/64;
  // Thirteenth bin
  fake_stream[24] = 24.0/64; fake_stream[25] = 25.0/64;
  // Fourteenth bin
  fake_stream[26] = 26.0/64; fake_stream[27] = 27.0/64;
  // Fifteenth bin
  fake_stream[28] = 28.0/64; fake_stream[29] = 29.0/64;
  // Sixteenth bin
  fake_stream[30] = 30.0/64; fake_stream[31] = 31.0/64;
  // Seventeenth bin
  fake_stream[32] = 32.0/64; fake_stream[33] = 33.0/64;
  // Eighteenth bin
  fake_stream[34] = 34.0/64; fake_stream[35] = 35.0/64;
  // Nineteenth bin
  fake_stream[36] = 36.0/64; fake_stream[37] = 37.0/64;
  // Twentieth bin
  fake_stream[38] = 38.0/64; fake_stream[39] = 39.0/64;
  // Twenty-first bin
  fake_stream[40] = 40.0/64; fake_stream[41] = 41.0/64;
  // Twenty-second bin
  fake_stream[42] = 42.0/64; fake_stream[43] = 43.0/64;
  // Twenty-third bin
  fake_stream[44] = 44.0/64; fake_stream[45] = 45.0/64;
  // Twenty-fourth bin
  fake_stream[46] = 46.0/64; fake_stream[47] = 47.0/64;
  // Twenty-fifth bin
  fake_stream[48] = 48.0/64; fake_stream[49] = 49.0/64;
  // Twenty-sixth bin
  fake_stream[50] = 50.0/64; fake_stream[51] = 51.0/64;
  // Twenty-seventh bin
  fake_stream[52] = 52.0/64; fake_stream[53] = 53.0/64;
  // Twenty-eighth bin
  fake_stream[54] = 54.0/64; fake_stream[55] = 55.0/64;
  // Twenty-ninth bin
  fake_stream[56] = 56.0/64; fake_stream[57] = 57.0/64;
  // Thirtieth bin
  fake_stream[58] = 58.0/64; fake_stream[59] = 59.0/64;
  // Thirty-first bin
  fake_stream[60] = 60.0/64; fake_stream[61] = 61.0/64;
  // Thirty-second bin
  fake_stream[62] = 62.0/64; fake_stream[63] = 63.0/64;
  fake_stream[64] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  size_t bin_index;

  // First bin
  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -16.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -15.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 0 );

  // Second bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -15.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 1 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -14.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 1 );

  // Third bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -14.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 2 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -13.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 2 );

  // Fourth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -13.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 3 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -12.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 3 );

  // Fifth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -12.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 4 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -11.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 4 );

  // Sixth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -11.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 5 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -10.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 5 );

  // Seventh bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -10.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 6 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -9.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 6 );

  // Eighth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -9.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 7 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -8.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 7 );

  // Ninth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -8.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 8 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -7.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 8 );

  // Tenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -7.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 9 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -6.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 9 );

  // Eleventh bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -6.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 10 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -5.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 10 );

  // Twelfth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -5.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 11 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -4.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 11 );

  // Thirteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -4.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 12 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -3.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 12 );

  // Fourteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -3.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 13 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -2.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 13 );

  // Fifteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -2.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 14 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.25 );
  FRENSIE_CHECK_EQUAL( bin_index, 14 );

  // Sixteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -0.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 15 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -0.25 );
  FRENSIE_CHECK_EQUAL( bin_index, 15 );

  // Seventeenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 16 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.25 );
  FRENSIE_CHECK_EQUAL( bin_index, 16 );

  // Eighteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 17 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.25 );
  FRENSIE_CHECK_EQUAL( bin_index, 17 );

  // Nineteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 2.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 18 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 18 );

  // Twentieth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 3.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 19 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 3.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 19 );

  // Twenty-first bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 4.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 20 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 4.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 20 );

  // Twenty-second bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 21 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 5.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 21 );

  // Twenty-third bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 6.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 22 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 6.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 22 );

  // Twenty-fourth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 7.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 23 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 7.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 23 );

  // Twenty-fifth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 8.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 24 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 8.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 24 );

  // Twenty-sixth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 9.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 25 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 9.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 25 );

  // Twenty-seventh bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 10.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 26 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 10.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 26 );

  // Twenty-eighth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 11.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 27 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 11.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 27 );

  // Twenty-ninth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 12.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 28 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 12.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 28 );

  // Thirtieth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 13.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 29 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 13.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 29 );

  // Thirty-first bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 14.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 30 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 14.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 30 );

  // Thirty-second bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 15.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 31 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 15.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 31 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 16.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 31 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.125;
  fake_stream[2] = 0.25;
  fake_stream[3] = 0.375;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.625;
  fake_stream[6] = 0.75;
  fake_stream[7] = 0.875;
  fake_stream[8] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  size_t bin_index;

  // First bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 0.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.05*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 0.0 );

  // Second bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.1*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 1.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.55*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 1.0 );

  // Third bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 2.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 3.0*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 2.0 );

  // Fourth bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 5.0*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 3.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 7.5*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 3.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, sampleWithRandomNumber )
{
  // First bin
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -16.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -15.5 );

  // Second bin
  sample = tab_distribution->sampleWithRandomNumber( 2.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -15.0 );

  sample = tab_distribution->sampleWithRandomNumber( 3.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -14.5 );

  // Third bin
  sample = tab_distribution->sampleWithRandomNumber( 4.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -14.0 );

  sample = tab_distribution->sampleWithRandomNumber( 5.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -13.5 );

  // Fourth bin
  sample = tab_distribution->sampleWithRandomNumber( 6.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -13.0 );

  sample = tab_distribution->sampleWithRandomNumber( 7.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -12.5 );

  // Fifth bin
  sample = tab_distribution->sampleWithRandomNumber( 8.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -12.0 );

  sample = tab_distribution->sampleWithRandomNumber( 9.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -11.5 );

  // Sixth bin
  sample = tab_distribution->sampleWithRandomNumber( 10.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -11.0 );

  sample = tab_distribution->sampleWithRandomNumber( 11.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -10.5 );

  // Seventh bin
  sample = tab_distribution->sampleWithRandomNumber( 12.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -10.0 );

  sample = tab_distribution->sampleWithRandomNumber( 13.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -9.5 );

  // Eighth bin
  sample = tab_distribution->sampleWithRandomNumber( 14.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -9.0 );

  sample = tab_distribution->sampleWithRandomNumber( 15.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -8.5 );

  // Ninth bin
  sample = tab_distribution->sampleWithRandomNumber( 16.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -8.0 );

  sample = tab_distribution->sampleWithRandomNumber( 17.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -7.5 );

  // Tenth bin
  sample = tab_distribution->sampleWithRandomNumber( 18.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -7.0 );

  sample = tab_distribution->sampleWithRandomNumber( 19.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -6.5 );

  // Eleventh bin
  sample = tab_distribution->sampleWithRandomNumber( 20.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -6.0 );

  sample = tab_distribution->sampleWithRandomNumber( 21.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -5.5 );

  // Twelfth bin
  sample = tab_distribution->sampleWithRandomNumber( 22.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -5.0 );

  sample = tab_distribution->sampleWithRandomNumber( 23.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -4.5 );

  // Thirteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 24.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -4.0 );

  sample = tab_distribution->sampleWithRandomNumber( 25.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -3.5 );

  // Fourteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 26.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -3.0 );

  sample = tab_distribution->sampleWithRandomNumber( 27.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -2.5 );

  // Fifteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 28.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -2.0 );

  sample = tab_distribution->sampleWithRandomNumber( 29.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -1.25 );

  // Sixteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 30.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -0.5 );

  sample = tab_distribution->sampleWithRandomNumber( 31.0/64 );
  FRENSIE_CHECK_EQUAL( sample, -0.25 );

  // Seventeenth bin
  sample = tab_distribution->sampleWithRandomNumber( 32.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 33.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 0.25 );

  // Eighteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 34.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 0.5 );

  sample = tab_distribution->sampleWithRandomNumber( 35.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 1.25 );

  // Nineteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 36.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 2.0 );

  sample = tab_distribution->sampleWithRandomNumber( 37.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  // Twentieth bin
  sample = tab_distribution->sampleWithRandomNumber( 38.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 3.0 );

  sample = tab_distribution->sampleWithRandomNumber( 39.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 3.5 );

  // Twenty-first bin
  sample = tab_distribution->sampleWithRandomNumber( 40.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 4.0 );

  sample = tab_distribution->sampleWithRandomNumber( 41.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 4.5 );

  // Twenty-second bin
  sample = tab_distribution->sampleWithRandomNumber( 42.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleWithRandomNumber( 43.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 5.5 );

  // Twenty-third bin
  sample = tab_distribution->sampleWithRandomNumber( 44.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 6.0 );

  sample = tab_distribution->sampleWithRandomNumber( 45.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 6.5 );

  // Twenty-fourth bin
  sample = tab_distribution->sampleWithRandomNumber( 46.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 7.0 );

  sample = tab_distribution->sampleWithRandomNumber( 47.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 7.5 );

  // Twenty-fifth bin
  sample = tab_distribution->sampleWithRandomNumber( 48.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 8.0 );

  sample = tab_distribution->sampleWithRandomNumber( 49.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 8.5 );

  // Twenty-sixth bin
  sample = tab_distribution->sampleWithRandomNumber( 50.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 9.0 );

  sample = tab_distribution->sampleWithRandomNumber( 51.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 9.5 );

  // Twenty-seventh bin
  sample = tab_distribution->sampleWithRandomNumber( 52.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 10.0 );

  sample = tab_distribution->sampleWithRandomNumber( 53.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 10.5 );

  // Twenty-eighth bin
  sample = tab_distribution->sampleWithRandomNumber( 54.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 11.0 );

  sample = tab_distribution->sampleWithRandomNumber( 55.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 11.5 );

  // Twenty-ninth bin
  sample = tab_distribution->sampleWithRandomNumber( 56.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 12.0 );

  sample = tab_distribution->sampleWithRandomNumber( 57.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 12.5 );

  // Thirtieth bin
  sample = tab_distribution->sampleWithRandomNumber( 58.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 13.0 );

  sample = tab_distribution->sampleWithRandomNumber( 59.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 13.5 );

  // Thirty-first bin
  sample = tab_distribution->sampleWithRandomNumber( 60.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 14.0 );

  sample = tab_distribution->sampleWithRandomNumber( 61.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 14.5 );

  // Thirty-second bin
  sample = tab_distribution->sampleWithRandomNumber( 62.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 15.0 );

  sample = tab_distribution->sampleWithRandomNumber( 63.0/64 );
  FRENSIE_CHECK_EQUAL( sample, 15.5 );

  sample = tab_distribution->sampleWithRandomNumber( 64.0/64 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 16.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   sampleWithRandomNumber )
{
  // First bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.125 );
  FRENSIE_CHECK_EQUAL( sample, 0.05*MeV );

  // Second bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.25 );
  FRENSIE_CHECK_EQUAL( sample, 0.1*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.375 );
  FRENSIE_CHECK_EQUAL( sample, 0.55*MeV );

  // Third bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.5 );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.625 );
  FRENSIE_CHECK_EQUAL( sample, 3.0*MeV );

  // Fourth bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.75 );
  FRENSIE_CHECK_EQUAL( sample, 5.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.875 );
  FRENSIE_CHECK_EQUAL( sample, 7.5*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*MeV, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 13 );
  // First bin
  fake_stream[0] = 0.0;      fake_stream[1] = 1.0/12;
  // Second bin
  fake_stream[2] = 2.0/12;   fake_stream[3] = 3.0/12;
  // Third bin
  fake_stream[4] = 4.0/12;   fake_stream[5] = 5.0/12;
  // Fourth bin
  fake_stream[6] = 6.0/12;   fake_stream[7] = 7.0/12;
  // Fifth bin
  fake_stream[8] = 8.0/12;   fake_stream[9] = 9.0/12;
  // Sixth bin
  fake_stream[10] = 10.0/12; fake_stream[11] = 11.0/12;
  fake_stream[12] = 12.0/12 - 1e-12;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // First bin
  double sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -16.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -15.5 );

  // Second bin
  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -15.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -14.5 );

  // Third bin
  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -14.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -13.5 );

  // Fourth bin
  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -13.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -12.5 );

  // Fifth bin
  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -12.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -11.5 );

  // Sixth bin
  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -11.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -10.5 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -10.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6;
  fake_stream[2] = 2.0/6;
  fake_stream[3] = 3.0/6;
  fake_stream[4] = 4.0/6;
  fake_stream[5] = 5.0/6;
  fake_stream[6] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // First bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.05*MeV );

  // Second bin
  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.1*MeV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.55*MeV );

  // Third bin
  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 3.0*MeV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( EquiprobableBinDistribution,
		   sampleWithRandomNumberInSubrange )
{
  // First bin
  double sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.0, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -16.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -15.5 );

  // Second bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 2.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -15.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 3.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -14.5 );

  // Third bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 4.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -14.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 5.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -13.5 );

  // Fourth bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 6.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -13.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 7.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -12.5 );

  // Fifth bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 8.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -12.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 9.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -11.5 );

  // Sixth bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 10.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -11.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 11.0/12, -10.0 );
  FRENSIE_CHECK_EQUAL( sample, -10.5 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, -10.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -10.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   sampleWithRandomNumberInSubrange )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6;
  fake_stream[2] = 2.0/6;
  fake_stream[3] = 3.0/6;
  fake_stream[4] = 4.0/6;
  fake_stream[5] = 5.0/6;
  fake_stream[6] = 1.0-1e-15;

  // First bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 1.0/6, 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.05*MeV );

  // Second bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 2.0/6, 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.1*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 3.0/6, 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.55*MeV );

  // Third bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 4.0/6, 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 5.0/6, 5.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 3.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 1.0-1e-15, 5.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*MeV, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( EquiprobableBinDistribution,
		   getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 16.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       10.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( EquiprobableBinDistribution,
		   getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), -16.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( EquiprobableBinDistribution,
		   getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::EQUIPROBABLE_BIN_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::EQUIPROBABLE_BIN_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, isTabular )
{
  FRENSIE_CHECK( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution, isTabular )
{
  FRENSIE_CHECK( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, isContinuous )
{
  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Check an alternative distribution that is compatible with all interp types
  std::vector<double> bin_boundaries( 4 );

  bin_boundaries[0] = 1.0;
  bin_boundaries[1] = 2.0;
  bin_boundaries[2] = 3.0;
  bin_boundaries[3] = 4.0;

  Utility::EquiprobableBinDistribution test_dist( bin_boundaries );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
                   isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Check an alternative distribution that is compatible with all interp types
  std::vector<double> bin_boundaries( 4 );

  bin_boundaries[0] = 1.0;
  bin_boundaries[1] = 2.0;
  bin_boundaries[2] = 3.0;
  bin_boundaries[3] = 4.0;

  Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>
    test_dist( bin_boundaries );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( EquiprobableBinDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::EquiprobableBinDistribution();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Equiprobable Bin Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["bin boundaries"].toType<std::vector<double> >(),
                       std::vector<double>({0.0, 1.0}) );

  oss.str( "" );
  oss.clear();

  oss << *distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Equiprobable Bin Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["bin boundaries"].toType<std::vector<double> >(),
                       std::vector<double>({-16.0, -15.0, -14.0, -13.0, -12.0, -11.0, -10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -0.5, 0.0, 0.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0}) );

  oss.str( "" );
  oss.clear();

  oss << *tab_distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Equiprobable Bin Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["bin boundaries"].toType<std::vector<double> >(),
                       std::vector<double>({-16.0, -15.0, -14.0, -13.0, -12.0, -11.0, -10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -0.5, 0.0, 0.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0}) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareEquiprobableBinDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Equiprobable Bin Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["bin boundaries"].toType<std::vector<quantity<MegaElectronVolt> > >(),
                       std::vector<quantity<MegaElectronVolt> >({0.0*MeV, 1.0*MeV}) );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Equiprobable Bin Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["bin boundaries"].toType<std::vector<quantity<MegaElectronVolt> > >(),
                       std::vector<quantity<MegaElectronVolt> >({0.0*MeV, 0.1*MeV, 1.0*MeV, 5.0*MeV, 10.0*MeV}) );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_tab_distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Equiprobable Bin Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["bin boundaries"].toType<std::vector<quantity<MegaElectronVolt> > >(),
                       std::vector<quantity<MegaElectronVolt> >({0.0*MeV, 0.1*MeV, 1.0*MeV, 5.0*MeV, 10.0*MeV}) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( EquiprobableBinDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_equiprobable_bin_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some equiprobable bin distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::vector<double> bin_boundaries( {-16.0, -15.0, -14.0, -13.0, -12.0, -11.0, -10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -0.5, 0.0, 0.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0} );

    Utility::EquiprobableBinDistribution distribution_a( bin_boundaries );

    FRENSIE_REQUIRE_NO_THROW(
                         (*oarchive) << BOOST_SERIALIZATION_NVP(distribution_a)
                             );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "distribution_b", distribution ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "distribution_c", tab_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::EquiprobableBinDistribution distribution_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP(distribution_a)
                           );
  FRENSIE_CHECK_EQUAL( distribution_a.getLowerBoundOfIndepVar(), -16.0 );
  FRENSIE_CHECK_EQUAL( distribution_a.getUpperBoundOfIndepVar(), 16.0 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -17.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -16.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -14.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -13.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -12.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -11.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -10.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -9.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -8.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -7.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -6.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -5.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -4.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -3.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -2.0 ), 1.0/48 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -0.5 ), 1.0/16 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 0.0 ), 1.0/16 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 0.5 ), 1.0/48 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 2.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 3.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 4.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 5.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 6.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 7.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 8.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 9.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 10.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 11.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 12.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 13.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 14.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 16.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 17.0 ), 0.0 );

  std::shared_ptr<Utility::UnivariateDistribution> distribution_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP(distribution_b)
                           );
  FRENSIE_CHECK_EQUAL( distribution_b->getLowerBoundOfIndepVar(), -16.0 );
  FRENSIE_CHECK_EQUAL( distribution_b->getUpperBoundOfIndepVar(), 16.0 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -17.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -16.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -14.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -13.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -12.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -11.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -10.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -9.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -8.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -7.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -6.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -5.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -4.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -3.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -2.0 ), 1.0/48 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -0.5 ), 1.0/16 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 0.0 ), 1.0/16 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 0.5 ), 1.0/48 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 2.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 3.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 4.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 5.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 6.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 7.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 8.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 9.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 10.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 11.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 12.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 13.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 14.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 16.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 17.0 ), 0.0 );

  std::shared_ptr<Utility::TabularUnivariateDistribution> distribution_c;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP(distribution_c)
                           );
  FRENSIE_CHECK_EQUAL( distribution_c->getLowerBoundOfIndepVar(), -16.0 );
  FRENSIE_CHECK_EQUAL( distribution_c->getUpperBoundOfIndepVar(), 16.0 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -17.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -16.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -14.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -13.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -12.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -11.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -10.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -9.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -8.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -7.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -6.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -5.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -4.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -3.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -2.0 ), 1.0/48 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -0.5 ), 1.0/16 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 0.0 ), 1.0/16 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 0.5 ), 1.0/48 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 2.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 3.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 4.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 5.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 6.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 7.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 8.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 9.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 10.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 11.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 12.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 13.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 14.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 15.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 16.0 ), 1.0/32 );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 17.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareEquiprobableBinDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_unit_aware_equiprobable_bin_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some equiprobable bin distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::vector<quantity<KiloElectronVolt> > bin_boundaries( 5 );
    bin_boundaries[0] = 0.0*keV;
    bin_boundaries[1] = 1e2*keV;
    bin_boundaries[2] = 1e3*keV;
    bin_boundaries[3] = 5e3*keV;
    bin_boundaries[4] = 1e4*keV;

    Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>
      distribution_a( bin_boundaries );

    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP(distribution_a)
                             );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "distribution_b", unit_aware_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "distribution_c", unit_aware_tab_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>
    distribution_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP(distribution_a)
                           );
  FRENSIE_CHECK_EQUAL( distribution_a.getLowerBoundOfIndepVar(), 0.0*MeV );
  FRENSIE_CHECK_EQUAL( distribution_a.getUpperBoundOfIndepVar(), 10*MeV );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( -1.0*MeV ), 0.0*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 0.0*MeV ), 2.5*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 0.1*MeV ), 0.25/0.9*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 1.0*MeV ), 0.0625*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 5.0*MeV ), 0.05*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 10.0*MeV ), 0.05*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_a.evaluate( 11.0*MeV ), 0.0*si::mole );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount> > distribution_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP(distribution_b)
                           );
  FRENSIE_CHECK_EQUAL( distribution_b->getLowerBoundOfIndepVar(), 0.0*MeV );
  FRENSIE_CHECK_EQUAL( distribution_b->getUpperBoundOfIndepVar(), 10*MeV );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( -1.0*MeV ), 0.0*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 0.0*MeV ), 2.5*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 0.1*MeV ), 0.25/0.9*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 1.0*MeV ), 0.0625*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 5.0*MeV ), 0.05*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 10.0*MeV ), 0.05*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_b->evaluate( 11.0*MeV ), 0.0*si::mole );

  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<MegaElectronVolt,si::amount> > distribution_c;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP(distribution_c)
                           );
  FRENSIE_CHECK_EQUAL( distribution_c->getLowerBoundOfIndepVar(), 0.0*MeV );
  FRENSIE_CHECK_EQUAL( distribution_c->getUpperBoundOfIndepVar(), 10*MeV );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( -1.0*MeV ), 0.0*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 0.0*MeV ), 2.5*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 0.1*MeV ), 0.25/0.9*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 1.0*MeV ), 0.0625*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 5.0*MeV ), 0.05*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 10.0*MeV ), 0.05*si::mole );
  FRENSIE_CHECK_EQUAL( distribution_c->evaluate( 11.0*MeV ), 0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareEquiprobableBinDistribution,
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
  Utility::UnitAwareEquiprobableBinDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareEquiprobableBinDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::EquiprobableBinDistribution*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareEquiprobableBinDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1./16);
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 1./16 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b( inv_indep_quantity_a );
  DepQuantityB dep_quantity_b =
    Utility::QuantityTraits<DepQuantityB>::initializeQuantity(
			     Utility::getRawQuantity( inv_indep_quantity_b ) );

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

  Utility::setQuantity( indep_quantity_a, 17.0 );
  Utility::setQuantity( inv_indep_quantity_a, 0.0 );
  Utility::setQuantity( dep_quantity_a, 0.0 );

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
  // Initialize the distribution
  std::vector<double> bin_boundaries( 33 );

  bin_boundaries[0] = -16.0;
  bin_boundaries[1] = -15.0;
  bin_boundaries[2] = -14.0;
  bin_boundaries[3] = -13.0;
  bin_boundaries[4] = -12.0;
  bin_boundaries[5] = -11.0;
  bin_boundaries[6] = -10.0;
  bin_boundaries[7] = -9.0;
  bin_boundaries[8] = -8.0;
  bin_boundaries[9] = -7.0;
  bin_boundaries[10] = -6.0;
  bin_boundaries[11] = -5.0;
  bin_boundaries[12] = -4.0;
  bin_boundaries[13] = -3.0;
  bin_boundaries[14] = -2.0;
  bin_boundaries[15] = -0.5;
  bin_boundaries[16] = 0.0;
  bin_boundaries[17] = 0.5;
  bin_boundaries[18] = 2.0;
  bin_boundaries[19] = 3.0;
  bin_boundaries[20] = 4.0;
  bin_boundaries[21] = 5.0;
  bin_boundaries[22] = 6.0;
  bin_boundaries[23] = 7.0;
  bin_boundaries[24] = 8.0;
  bin_boundaries[25] = 9.0;
  bin_boundaries[26] = 10.0;
  bin_boundaries[27] = 11.0;
  bin_boundaries[28] = 12.0;
  bin_boundaries[29] = 13.0;
  bin_boundaries[30] = 14.0;
  bin_boundaries[31] = 15.0;
  bin_boundaries[32] = 16.0;

  tab_distribution.reset(
	  new Utility::EquiprobableBinDistribution( bin_boundaries ) );

  distribution = tab_distribution;

  // Initialize the unit-aware distribution
  std::vector<quantity<KiloElectronVolt> > bin_boundary_quantities( 5 );
  bin_boundary_quantities[0] = 0.0*keV;
  bin_boundary_quantities[1] = 1e2*keV;
  bin_boundary_quantities[2] = 1e3*keV;
  bin_boundary_quantities[3] = 5e3*keV;
  bin_boundary_quantities[4] = 1e4*keV;

  unit_aware_tab_distribution.reset(
   new Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>( bin_boundary_quantities ) );

  unit_aware_distribution = unit_aware_tab_distribution;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEquiprobableBinDistribution.cpp
//---------------------------------------------------------------------------//
