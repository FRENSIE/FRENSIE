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

// FRENSIE Includes
#include "Utility_HistogramDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

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
// Testing Tables
//---------------------------------------------------------------------------//
// This table describes the data in the property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since they are
  // serialized the same in the table
  Utility::HistogramDistribution dummy_dist;

  double pi = Utility::PhysicalConstants::pi;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_2_args" ) << "Distribution A" << true << no_unused_children << Utility::HistogramDistribution( {-2.0, -1.0, 1.0, 2.0}, {2.0, 1.0, 2.0} );
  NEW_ROW( "inline_3_args" ) << "Distribution B" << true << no_unused_children << Utility::HistogramDistribution( {0.0, 0.25, 0.5, 0.75, 1.0}, {1.0, 1.0, 1.0, 1.0} );
  NEW_ROW( "inline_3_args_cdf" ) << "Distribution C" << true << no_unused_children << Utility::HistogramDistribution( {0.0, 0.25, 0.5, 0.75, 1.0}, {0.25, 0.5, 0.75, 1.0}, true );
  NEW_ROW( "inline_bad_type" ) << "Distribution D" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_too_few_bounds" ) << "Distribution E" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_unsorted_bounds" ) << "Distribution F" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_start_bound" ) << "Distribution G" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_end_bound" ) << "Distribution H" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_too_many_values" ) << "Distribution I" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_unsorted_cdf_values" ) << "Distribution J" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_repeated_cdf_values" ) << "Distribution K" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_value" ) << "Distribution L" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_value" ) << "Distribution M" << false << no_unused_children << dummy_dist;

  NEW_ROW( "2_args" ) << "Distribution N" << true << no_unused_children << Utility::HistogramDistribution( {-2.0, -1.0, 1.0, pi}, {2.0, 1.0, 2.0} );
  NEW_ROW( "4_args_cdf" ) << "Distribution O" << true << std::vector<std::string>( {"dummy"} ) << Utility::HistogramDistribution( {0.0, 0.25, 0.5, 0.75, 1.0}, {0.25, 0.5, 0.75, 1.0}, true );
  NEW_ROW( "4_args" ) << "Distribution P" << true << std::vector<std::string>( {"Dummy"} ) << Utility::HistogramDistribution( {0.0, 0.25, 0.5, 0.75, 1.0}, {1.0, 1.0, 1.0, 1.0} );
  NEW_ROW( "repeated_keys" ) << "Distribution Q" << true << std::vector<std::string>( {"cdf specified", "bin values", "bin boundaries"} ) << Utility::HistogramDistribution( {0.0, 0.25, 0.5, 0.75, 1.0}, {1.0, 1.0, 1.0, 1.0} );
  NEW_ROW( "bad_type" ) << "Distribution R" << false << no_unused_children << dummy_dist;
  NEW_ROW( "too_few_bounds" ) << "Distribution S" << false << no_unused_children << dummy_dist;
  NEW_ROW( "unsorted_bounds" ) << "Distribution T" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_start_bound" ) << "Distribution U" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_end_bound" ) << "Distribution V" << false << no_unused_children << dummy_dist;
  NEW_ROW( "too_many_values" ) << "Distribution W" << false << no_unused_children << dummy_dist;
  NEW_ROW( "unsorted_cdf_values" ) << "Distribution X" << false << no_unused_children << dummy_dist;
  NEW_ROW( "repeated_cdf_values" ) << "Distribution Y" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_value" ) << "Distribution Z" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_value" ) << "Distribution AA" << false << no_unused_children << dummy_dist;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( HistogramDistribution, evalute )
{
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluate( -3.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluate( -2.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluate( -1.5 ), 2.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluate( -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluate( 1.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluate( 1.5 ), 2.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluate( 2.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluate( 3.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluate( -3.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluate( -2.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluate( -1.5 ), 2.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluate( -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluate( 1.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluate( 1.5 ), 2.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluate( 2.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluate( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, evalute )
{
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluate( -3.0*MeV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluate( -2.0*MeV ),
		       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluate( -1.5*MeV ),
		       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluate( -1.0*MeV ),
		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluate( 0.0*MeV ),
		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluate( 1.0*MeV ),
		       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluate( 1.5*MeV ),
		       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluate( 2.0*MeV ),
		       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluate( 3.0*MeV ),
		       0.0*si::mole );

  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluate( -3.0*MeV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluate( -2.0*MeV ),
		       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluate( -1.5*MeV ),
		       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluate( -1.0*MeV ),
		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluate( 0.0*MeV ),
		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluate( 1.0*MeV ),
		       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluate( 1.5*MeV ),
		       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluate( 2.0*MeV ),
		       2.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluate( 3.0*MeV ),
		       0.0*si::mole);
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( HistogramDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluatePDF( -3.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluatePDF( -2.0 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluatePDF( -1.5 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluatePDF( -1.0 ), 1.0/6.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluatePDF( 0.0 ), 1.0/6.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluatePDF( 1.0 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluatePDF( 1.5 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluatePDF( 2.0 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( pdf_distribution->evaluatePDF( 3.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluatePDF( -3.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluatePDF( -2.0 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluatePDF( -1.5 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluatePDF( -1.0 ), 1.0/6.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluatePDF( 0.0 ), 1.0/6.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluatePDF( 1.0 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluatePDF( 1.5 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluatePDF( 2.0 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->evaluatePDF( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluatePDF( -3.0*MeV ),
		       0.0/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluatePDF( -2.0*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluatePDF( -1.5*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluatePDF( -1.0*MeV ),
		       (1.0/6.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluatePDF( 0.0*MeV ),
		       (1.0/6.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluatePDF( 1.0*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluatePDF( 1.5*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluatePDF( 2.0*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->evaluatePDF( 3.0*MeV ),
		       0.0/MeV );

  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluatePDF( -3.0*MeV ),
		       0.0/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluatePDF( -2.0*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluatePDF( -1.5*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluatePDF( -1.0*MeV ),
		       (1.0/6.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluatePDF( 0.0*MeV ),
		       (1.0/6.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluatePDF( 1.0*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluatePDF( 1.5*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluatePDF( 2.0*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->evaluatePDF( 3.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
FRENSIE_UNIT_TEST( HistogramDistribution, evaluateCDF )
{
  FRENSIE_CHECK_EQUAL( tab_pdf_distribution->evaluateCDF(-3.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_pdf_distribution->evaluateCDF(-2.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_pdf_distribution->evaluateCDF(-1.5 ), 1.0/6.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_pdf_distribution->evaluateCDF(-1.0 ), 1.0/3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_pdf_distribution->evaluateCDF( 0.0 ), 0.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_pdf_distribution->evaluateCDF( 1.0 ), 2.0/3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_pdf_distribution->evaluateCDF( 1.5 ), 5.0/6.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_pdf_distribution->evaluateCDF( 2.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_pdf_distribution->evaluateCDF( 3.0 ), 1.0 );

  FRENSIE_CHECK_EQUAL( tab_cdf_distribution->evaluateCDF(-3.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_cdf_distribution->evaluateCDF(-2.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_cdf_distribution->evaluateCDF(-1.5 ), 1.0/6.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_cdf_distribution->evaluateCDF(-1.0 ), 1.0/3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_cdf_distribution->evaluateCDF( 0.0 ), 0.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_cdf_distribution->evaluateCDF( 1.0 ), 2.0/3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_cdf_distribution->evaluateCDF( 1.5 ), 5.0/6.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_cdf_distribution->evaluateCDF( 2.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_cdf_distribution->evaluateCDF( 3.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, evaluateCDF )
{
  FRENSIE_CHECK_EQUAL(unit_aware_tab_pdf_distribution->evaluateCDF( -3.0*MeV ),
		      0.0 );
  FRENSIE_CHECK_EQUAL(unit_aware_tab_pdf_distribution->evaluateCDF( -2.0*MeV ),
		      0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		      unit_aware_tab_pdf_distribution->evaluateCDF( -1.5*MeV ),
		      1.0/6.0,
		      1e-14 );
  FRENSIE_CHECK_EQUAL(unit_aware_tab_pdf_distribution->evaluateCDF( -1.0*MeV ),
		      1.0/3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		       unit_aware_tab_pdf_distribution->evaluateCDF( 0.0*MeV ),
		       0.5,
		       1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_pdf_distribution->evaluateCDF( 1.0*MeV ),
		       2.0/3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		       unit_aware_tab_pdf_distribution->evaluateCDF( 1.5*MeV ),
		       5.0/6.0,
		       1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_pdf_distribution->evaluateCDF( 2.0*MeV ),
		       1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_pdf_distribution->evaluateCDF( 3.0*MeV ),
		       1.0 );

  FRENSIE_CHECK_EQUAL(unit_aware_tab_cdf_distribution->evaluateCDF( -3.0*MeV ),
		      0.0 );
  FRENSIE_CHECK_EQUAL(unit_aware_tab_cdf_distribution->evaluateCDF( -2.0*MeV ),
		      0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		      unit_aware_tab_cdf_distribution->evaluateCDF( -1.5*MeV ),
		      1.0/6.0,
		      1e-14 );
  FRENSIE_CHECK_EQUAL(unit_aware_tab_cdf_distribution->evaluateCDF( -1.0*MeV ),
		      1.0/3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		       unit_aware_tab_cdf_distribution->evaluateCDF( 0.0*MeV ),
		       0.5,
		       1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_cdf_distribution->evaluateCDF( 1.0*MeV ),
		       2.0/3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
		       unit_aware_tab_cdf_distribution->evaluateCDF( 1.5*MeV ),
		       5.0/6.0,
		       1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_cdf_distribution->evaluateCDF( 2.0*MeV ),
		      1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_cdf_distribution->evaluateCDF( 3.0*MeV ),
		      1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( HistogramDistribution, sample )
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
  FRENSIE_CHECK_EQUAL( sample, -2.0 );

  sample = pdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.5 );

  sample = pdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // Test the second bin
  sample = pdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = pdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = pdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Test the third bin
  sample = pdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = pdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5, 1e-14 );

  sample = pdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = cdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -2.0 );

  sample = cdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.5 );

  sample = cdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // Test the second bin
  sample = cdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = cdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = cdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Test the third bin
  sample = cdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = cdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5, 1e-14 );

  sample = cdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, sample )
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
  FRENSIE_CHECK_EQUAL( sample, -2.0*MeV );

  sample = unit_aware_pdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.5*MeV );

  sample = unit_aware_pdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // Test the second bin
  sample = unit_aware_pdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0*MeV );

  sample = unit_aware_pdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );

  sample = unit_aware_pdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  // Test the third bin
  sample = unit_aware_pdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );

  sample = unit_aware_pdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );

  sample = unit_aware_pdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_cdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -2.0*MeV );

  sample = unit_aware_cdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.5*MeV );

  sample = unit_aware_cdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // Test the second bin
  sample = unit_aware_cdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, -1.0*MeV );

  sample = unit_aware_cdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );

  sample = unit_aware_cdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  // Test the third bin
  sample = unit_aware_cdf_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );

  sample = unit_aware_cdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );

  sample = unit_aware_cdf_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( HistogramDistribution, sampleAndRecordTrials )
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
  FRENSIE_CHECK_EQUAL( sample, -2.0 );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.5 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  // Test the second bin
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 4 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 5 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6 );

  // Test the third bin
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 7 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 8 );

  sample = pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 9 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Test the first bin
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -2.0 );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.5 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  // Test the second bin
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 4 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 5 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6 );

  // Test the third bin
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 7 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 8 );

  sample = cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 9 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, sampleAndRecordTrials )
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
  FRENSIE_CHECK_EQUAL( sample, -2.0*MeV );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.5*MeV );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  // Test the second bin
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*MeV );
  FRENSIE_CHECK_EQUAL( trials, 4 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 5 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6 );

  // Test the third bin
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );
  FRENSIE_CHECK_EQUAL( trials, 7 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 8 );

  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 9 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Test the first bin
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -2.0*MeV );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.5*MeV );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  // Test the second bin
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*MeV );
  FRENSIE_CHECK_EQUAL( trials, 4 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 5 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6 );

  // Test the third bin
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );
  FRENSIE_CHECK_EQUAL( trials, 7 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 8 );

  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 9 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( HistogramDistribution, sampleAndRecordBinIndex )
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
  FRENSIE_CHECK_EQUAL( sample, -2.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  // Test the second bin
  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  // Test the third bin
  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -2.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.5 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  // Test the second bin
  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  // Test the third bin
  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, sampleAndRecordBinIndex )
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
  FRENSIE_CHECK_EQUAL( sample, -2.0*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.5*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  // Test the second bin
  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  // Test the third bin
  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample =
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -2.0*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.5*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  // Test the second bin
  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );

  // Test the third bin
  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  sample =
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( HistogramDistribution, sampleWithRandomNumber )
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
  FRENSIE_CHECK_EQUAL( sample, -2.0 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.5 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // Test the second bin
  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Test the third bin
  sample = tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_cdf_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -2.0 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.5 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // Test the second bin
  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Test the third bin
  sample = tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  FRENSIE_CHECK_EQUAL( sample, 1.0 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, sampleWithRandomNumber )
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
  FRENSIE_CHECK_EQUAL( sample, -2.0*MeV );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.5*MeV );

  sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // Test the second bin
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*MeV );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );

  sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  // Test the third bin
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );

  sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -2.0*MeV );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.5*MeV );

  sample =
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // Test the second bin
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*MeV );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );

  sample =
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  // Test the third bin
  sample =
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  FRENSIE_CHECK_EQUAL( sample, 1.0*MeV );

  sample =
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );

  sample =
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
//Check that the distribution can be sampled from a subrange
FRENSIE_UNIT_TEST( HistogramDistribution, sampleInSubrange )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // PDF Histogram: test max independent value 3rd bin
  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // CDF Histogram: test max independent value 2nd bin
  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // CDF Histogram: test max independent value 3rd bin
  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, sampleInSubrange )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleInSubrange( -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.5*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleInSubrange( -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // PDF Histogram: test max independent value 3rd bin
  sample = unit_aware_tab_pdf_distribution->sampleInSubrange( 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleInSubrange( 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleInSubrange( 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // CDF Histogram: test max independent value 2nd bin
  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.5*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // CDF Histogram: test max independent value 3rd bin
  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleInSubrange( 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
FRENSIE_UNIT_TEST( HistogramDistribution, sampleWithRandomNumberInSubrange )
{
  // PDF Histogram: test max independent value 2nd bin
  double sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.0, -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.5, -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // PDF Histogram: test max independent value 3rd bin
  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.5, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // CDF Histogram: test max independent value 2nd bin
  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.0, -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.5, -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  // Test max independent value 3rd bin
  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.5, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution,
		   sampleWithRandomNumberInSubrange )
{
  // PDF Histogram: test max independent value 2nd bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
							       0.0, -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
							       0.5, -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.5*MeV, 1e-14 );

  sample =
    unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
						       1.0 - 1e-15, -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // PDF Histogram: test max independent value 3rd bin
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
								0.0, 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
								0.5, 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumberInSubrange(
							1.0 - 1e-15, 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );

  // CDF Histogram: test max independent value 2nd bin
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
							       0.0, -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
							       0.5, -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.5*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
						       1.0 - 1e-15, -1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  // Test max independent value 3rd bin
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
							        0.0, 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
								0.5, 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );

  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumberInSubrange(
							1.0 - 1e-15, 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( HistogramDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( pdf_distribution->getUpperBoundOfIndepVar(), 2.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->getUpperBoundOfIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->getUpperBoundOfIndepVar(),
		       2.0*MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->getUpperBoundOfIndepVar(),
		       2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution dependent variable can be
// returned
FRENSIE_UNIT_TEST( HistogramDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( pdf_distribution->getLowerBoundOfIndepVar(), -2.0 );
  FRENSIE_CHECK_EQUAL( cdf_distribution->getLowerBoundOfIndepVar(), -2.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution dependent variable
// can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->getLowerBoundOfIndepVar(),
		       -2.0*MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->getLowerBoundOfIndepVar(),
		       -2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( HistogramDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( pdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );

  FRENSIE_CHECK_EQUAL( cdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_pdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );

  FRENSIE_CHECK_EQUAL( unit_aware_cdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
FRENSIE_UNIT_TEST( HistogramDistribution, getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( Utility::HistogramDistribution::typeName( true, false, " " ),
                       "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( Utility::HistogramDistribution::typeName( false ),
                       "Histogram" );
  FRENSIE_CHECK_EQUAL( Utility::typeName<Utility::HistogramDistribution>(),
                       "HistogramDistribution" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution,
                   getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::typeName( true, false, " " )),
                       "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>::typeName( false )),
                       "Histogram" );
  FRENSIE_CHECK_EQUAL( (Utility::typeName<Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> >()),
                       std::string("UnitAwareHistogramDistribution<")+Utility::typeName<MegaElectronVolt>()+","+Utility::typeName<si::amount>()+">" );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( HistogramDistribution, isTabular )
{
  FRENSIE_CHECK( pdf_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, isTabular )
{
  FRENSIE_CHECK( unit_aware_pdf_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( HistogramDistribution, isContinuous )
{
  FRENSIE_CHECK( pdf_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_pdf_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( HistogramDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( pdf_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !pdf_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( pdf_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !pdf_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  std::vector<double> bin_boundaries( 3 ), bin_values( 2 );
  bin_boundaries[0] = 1.0;
  bin_boundaries[1] = 2.0;
  bin_boundaries[2] = 3.0;

  bin_values[0] = 0.5;
  bin_values[1] = 1.0;
  
  Utility::HistogramDistribution test_dist( bin_boundaries, bin_values );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_pdf_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !unit_aware_pdf_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_pdf_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_pdf_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

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

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
FRENSIE_UNIT_TEST( HistogramDistribution, toString )
{
  std::string dist_string = Utility::toString( *pdf_distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  dist_string = Utility::toString( *cdf_distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be converted to a string
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, toString )
{
  std::string dist_string = Utility::toString( *unit_aware_pdf_distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  dist_string = Utility::toString( *unit_aware_cdf_distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( HistogramDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *pdf_distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();
  
  Utility::toStream( oss, *cdf_distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, toStream )
{
  std::ostringstream oss;
  
  Utility::toStream( oss, *unit_aware_pdf_distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *unit_aware_cdf_distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( HistogramDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *pdf_distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();
  
  oss << *cdf_distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, ostream_operator )
{
  std::ostringstream oss;
  
  oss << *unit_aware_pdf_distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_cdf_distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a string
FRENSIE_UNIT_TEST( HistogramDistribution, fromString )
{
  Utility::HistogramDistribution test_dist =
    Utility::fromString<Utility::HistogramDistribution>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  test_dist = Utility::fromString<Utility::HistogramDistribution>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  test_dist = Utility::fromString<Utility::HistogramDistribution>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a string
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, fromString )
{
  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> test_dist =
    Utility::fromString<decltype(test_dist)>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  test_dist = Utility::fromString<decltype(test_dist)>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  test_dist = Utility::fromString<decltype(test_dist)>( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a stream
FRENSIE_UNIT_TEST( HistogramDistribution, fromStream )
{
  std::istringstream iss( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
  Utility::HistogramDistribution test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );  

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, fromStream )
{
  std::istringstream iss( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>
    test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a stream
FRENSIE_UNIT_TEST( HistogramDistribution, istream_operator )
{
  std::istringstream iss( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
  Utility::HistogramDistribution test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, istream_operator )
{
  std::istringstream iss( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}}" );
  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>
    test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, false}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );

  iss.str( "{Histogram Distribution, {-2.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}, {2.0, 4.0, 6.0}, true}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_pdf_distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_cdf_distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree
FRENSIE_UNIT_TEST( HistogramDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *pdf_distribution );

  Utility::HistogramDistribution copy_dist =
    ptree.get<Utility::HistogramDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );

  ptree.put( "test distribution", *tab_pdf_distribution );

  copy_dist = ptree.get<Utility::HistogramDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( tab_pdf_distribution.get() ) );

  ptree.put( "test distribution", *cdf_distribution );

  copy_dist = ptree.get<Utility::HistogramDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  ptree.put( "test distribution", *tab_cdf_distribution );

  copy_dist = ptree.get<Utility::HistogramDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( tab_cdf_distribution.get() ) );

  ptree.clear();

  // Use the PropertyTreeCompatibleOjbect interface
  ptree = pdf_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::HistogramDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );

  ptree = pdf_distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = pdf_distribution->toPropertyTree();

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = cdf_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::HistogramDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( cdf_distribution.get() ) );

  ptree = cdf_distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = cdf_distribution->toPropertyTree();

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( *pdf_distribution, true );

  copy_dist = ptree.get_value<Utility::HistogramDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( pdf_distribution.get() ) );

  ptree = Utility::toPropertyTree( *pdf_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *pdf_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *tab_pdf_distribution, true );

  copy_dist = ptree.get_value<Utility::HistogramDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::HistogramDistribution*>( tab_pdf_distribution.get() ) );

  ptree = Utility::toPropertyTree( *tab_pdf_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *tab_pdf_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to a property tree
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *unit_aware_pdf_distribution );

  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> copy_dist =
    ptree.get<decltype(copy_dist)>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_pdf_distribution.get() ) );

  ptree.put( "test distribution", *unit_aware_tab_pdf_distribution );

  copy_dist = ptree.get<decltype(copy_dist)>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_tab_pdf_distribution.get() ) );

  ptree.put( "test distribution", *unit_aware_cdf_distribution );

  copy_dist = ptree.get<decltype(copy_dist)>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_cdf_distribution.get() ) );

  ptree.put( "test distribution", *unit_aware_tab_cdf_distribution );

  copy_dist = ptree.get<decltype(copy_dist)>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_tab_cdf_distribution.get() ) );

  ptree.clear();

  // Use the PropertyTreeCompatibleOjbect interface
  ptree = unit_aware_pdf_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<decltype(copy_dist)>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_pdf_distribution.get() ) );

  ptree = unit_aware_pdf_distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = unit_aware_pdf_distribution->toPropertyTree();

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = unit_aware_cdf_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<decltype(copy_dist)>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_cdf_distribution.get() ) );

  ptree = unit_aware_cdf_distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = unit_aware_cdf_distribution->toPropertyTree();

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( *unit_aware_pdf_distribution, true );

  copy_dist = ptree.get_value<decltype(copy_dist)>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_pdf_distribution.get() ) );

  ptree = Utility::toPropertyTree( *unit_aware_pdf_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *unit_aware_pdf_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_pdf_distribution, true );

  copy_dist = ptree.get_value<decltype(copy_dist)>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_tab_pdf_distribution.get() ) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_pdf_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_pdf_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Histogram Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin boundaries" ),
                           std::vector<double>({-2.0, -1.0, 1.0, 2.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "bin values" ),
                           std::vector<double>({2.0, 1.0, 2.0}) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( HistogramDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::HistogramDistribution dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::HistogramDistribution, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW(
             dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ) ),
             Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::HistogramDistribution, expected_dist );

    FRENSIE_CHECK_NO_THROW(
        dist = Utility::fromPropertyTree<Utility::HistogramDistribution>(
                                      test_dists_ptree->get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW(
               Utility::fromPropertyTree<Utility::HistogramDistribution>(
                                    test_dists_ptree->get_child( dist_name ) ),
               Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwareHistogramDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  typedef Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> DistributionType;
  
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  DistributionType dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( DistributionType, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( DistributionType, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist = Utility::fromPropertyTree<DistributionType>(
                                      test_dists_ptree->get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::fromPropertyTree<DistributionType>(
                                    test_dists_ptree->get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST( HistogramDistribution, archive )
{
  std::string archive_name( "test_histogram_dist.h5a" );

  // Create and archive some histogram distributions
  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );
    
    Utility::HistogramDistribution dist_a( {-2.0, -1.0, 1.0, 2.0}, {2.0, 1.0, 2.0} );
    Utility::HistogramDistribution dist_b( {-2.0, -1.0, 1.0, 2.0}, {2.0, 4.0, 6.0}, true );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_b ) );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "dist_c", pdf_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "dist_d", tab_pdf_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "dist_e", cdf_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "dist_f", tab_cdf_distribution ) );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::HistogramDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_a) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::HistogramDistribution( {-2.0, -1.0, 1.0, 2.0}, {2.0, 1.0, 2.0} ) );

  Utility::HistogramDistribution dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_b) );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::HistogramDistribution( {-2.0, -1.0, 1.0, 2.0}, {2.0, 4.0, 6.0}, true ) );

  std::shared_ptr<Utility::OneDDistribution> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_c) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::HistogramDistribution*>(dist_c.get()),
                       *dynamic_cast<Utility::HistogramDistribution*>(pdf_distribution.get()) );

  std::shared_ptr<Utility::TabularOneDDistribution> dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_d) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::HistogramDistribution*>(dist_d.get()),
                       *dynamic_cast<Utility::HistogramDistribution*>(tab_pdf_distribution.get()) );

  std::shared_ptr<Utility::OneDDistribution> dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_e) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::HistogramDistribution*>(dist_e.get()),
                       *dynamic_cast<Utility::HistogramDistribution*>(cdf_distribution.get()) );

  std::shared_ptr<Utility::TabularOneDDistribution> dist_f;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_f) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::HistogramDistribution*>(dist_f.get()),
                       *dynamic_cast<Utility::HistogramDistribution*>(tab_cdf_distribution.get()) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST( UnitAwareHistogramDistribution, archive )
{
  std::string archive_name( "test_unit_aware_histogram_dist.h5a" );

  // Create and archive some histogram distributions
  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );
    
    Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> dist_a( {-2.0, -1.0, 1.0, 2.0}, {2.0, 1.0, 2.0} );
    Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> dist_b( {-2.0, -1.0, 1.0, 2.0}, {2.0, 4.0, 6.0}, true );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_b ) );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "dist_c", unit_aware_pdf_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "dist_d", unit_aware_tab_pdf_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "dist_e", unit_aware_cdf_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "dist_f", unit_aware_tab_cdf_distribution ) );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_a) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>( {-2.0, -1.0, 1.0, 2.0}, {2.0, 1.0, 2.0} )) );

  Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_b) );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>( {-2.0, -1.0, 1.0, 2.0}, {2.0, 4.0, 6.0}, true )) );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> > dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_c) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>*>(dist_c.get())),
                       (*dynamic_cast<Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>*>(unit_aware_pdf_distribution.get())) );

  std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> > dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_d) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>*>(dist_d.get())),
                       (*dynamic_cast<Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>*>(unit_aware_tab_pdf_distribution.get())) );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> > dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_e) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>*>(dist_e.get())),
                       (*dynamic_cast<Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>*>(unit_aware_cdf_distribution.get())) );

  std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> > dist_f;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_f) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>*>(dist_f.get())),
                       (*dynamic_cast<Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>*>(unit_aware_tab_cdf_distribution.get())) );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareHistogramDistribution,
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
  Utility::setQuantity( inv_indep_quantity_a, 1.0/3.0 );
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
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dists_json_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_OPTION( "test_dists_json_file",
              boost::program_options::value<std::string>(&test_dists_json_file_name)->default_value(""),
              "Test distributions json file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
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

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHistogramDistribution.cpp
//---------------------------------------------------------------------------//
