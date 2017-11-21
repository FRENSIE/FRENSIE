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

std::unique_ptr<Utility::PropertyTree> test_dists_ptree;

std::shared_ptr<Utility::TabularOneDDistribution> tab_distribution(
			  new Utility::UniformDistribution( -1.0, 1.0, 2.0 ) );

std::shared_ptr<Utility::OneDDistribution> distribution = tab_distribution;

std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<si::energy,si::amount> >
  unit_aware_tab_distribution;

std::shared_ptr<Utility::UnitAwareOneDDistribution<si::energy,si::amount> >
  unit_aware_distribution;

//---------------------------------------------------------------------------//
// Testing Tables
//---------------------------------------------------------------------------//
// This table describes the data in the property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since they are
  // serialized the same in the table
  Utility::UniformDistribution dummy_dist;

  double pi = Utility::PhysicalConstants::pi;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_full_ucase_name" ) << "Distribution A" << true << no_unused_children << Utility::UniformDistribution( -1.0, 1.0, 2.0 );
  NEW_ROW( "inline_full_lcase_name" ) << "Distribution B" << true << no_unused_children << Utility::UniformDistribution( 0.0, 2*pi, 3.0 );
  NEW_ROW( "inline_short_ucase_name" ) << "Distribution C" << true << no_unused_children << Utility::UniformDistribution( -1.0, 1.0, 1.0 );
  NEW_ROW( "inline_short_lcase_name" ) << "Distribution D" << true << no_unused_children << Utility::UniformDistribution( 0.0, 2*pi, 1.0 );
  NEW_ROW( "inline_bad_type" ) << "Distribution E" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_0_args" ) << "Distribution F" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_1_arg" ) << "Distribution G" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_lower_limit" ) << "Distribution H" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_upper_limit" ) << "Distribution I" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_same_limits" ) << "Distribution J" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_bad_limits" ) << "Distribution K" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_mult" ) << "Distribution L" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_mult" ) << "Distribution M" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_mult" ) << "Distribution N" << false << no_unused_children << dummy_dist;

  NEW_ROW( "full_ucase_name" ) << "Distribution O" << true << no_unused_children << Utility::UniformDistribution( -1.0, 1.0, 2.0 );
  NEW_ROW( "full_lcase_name" ) << "Distribution P" << true << no_unused_children << Utility::UniformDistribution( 0.0, 2*pi, 3.0 );
  NEW_ROW( "short_ucase_name" ) << "Distribution Q" << true << std::vector<std::string>( {"dummy"} ) << Utility::UniformDistribution( -1.0, 1.0, 1.0 );
  NEW_ROW( "short_lcase_name" ) << "Distribution R" << true << no_unused_children << Utility::UniformDistribution( 0.0, 2*pi, 1.0 );
  NEW_ROW( "repeated_keys" ) << "Distribution T" << true << std::vector<std::string>( {"upper bound", "lower bound", "multiplier"} ) << Utility::UniformDistribution( -1.0, 1.0, 0.5 );
  NEW_ROW( "bad_type" ) << "Distribution U" << false << no_unused_children << dummy_dist;
  NEW_ROW( "0_args" ) << "Distribution V" << false << no_unused_children << dummy_dist;
  NEW_ROW( "no_upper_limit" ) << "Distribution W" << false << no_unused_children << dummy_dist;
  NEW_ROW( "no_lower_limit" ) << "Distribution X" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_lower_limit" ) << "Distribution Y" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_upper_limit" ) << "Distribution Z" << false << no_unused_children << dummy_dist;
  NEW_ROW( "same_limits" ) << "Distribution AA" << false << no_unused_children << dummy_dist;
  NEW_ROW( "bad_limits" ) << "Distribution AB" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_mult" ) << "Distribution AC" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_mult" ) << "Distribution AD" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_mult" ) << "Distribution AE" << false << no_unused_children << dummy_dist;
}

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

  unsigned bin_index;

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

  unsigned bin_index;

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
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

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
// Check that the distribution can be converted to a string
FRENSIE_UNIT_TEST( UniformDistribution, toString )
{
  std::string dist_string = Utility::toString( *distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Uniform Distribution, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be converted to a string
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, toString )
{
  std::string dist_string = Utility::toString( *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Uniform Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( UniformDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Uniform Distribution, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Uniform Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( UniformDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Uniform Distribution, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, ostream_operator )
{
  std::ostringstream oss;
  
  oss << *unit_aware_distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Uniform Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a string
FRENSIE_UNIT_TEST( UniformDistribution, fromString )
{
  Utility::UniformDistribution test_dist =
    Utility::fromString<Utility::UniformDistribution>( "{Uniform Distribution, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
  
  test_dist = Utility::fromString<Utility::UniformDistribution>( "{uniform distribution, -1.0, 1.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );

  test_dist = Utility::fromString<Utility::UniformDistribution>( "{uniform-distribution, -1, 1, 2}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );

  test_dist = Utility::fromString<Utility::UniformDistribution>( "{uniform,-1,1,2}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );

  test_dist = Utility::fromString<Utility::UniformDistribution>( "{Uniform, -1, 1}" );

  FRENSIE_CHECK( test_dist != *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist.getLowerBoundOfIndepVar(), -1.0 );
  FRENSIE_CHECK_EQUAL( test_dist.getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a string
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, fromString )
{
  Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist =
    Utility::fromString<Utility::UnitAwareUniformDistribution<si::energy,si::amount> >( "{Uniform Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );

  test_dist = Utility::fromString<Utility::UnitAwareUniformDistribution<si::energy,si::amount> >( "{uniform distribution, 0.0, 1.0, 1.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );

  test_dist = Utility::fromString<Utility::UnitAwareUniformDistribution<si::energy,si::amount> >( "{uniform-distribution, 0, 1, 1}" );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );

  test_dist = Utility::fromString<Utility::UnitAwareUniformDistribution<si::energy,si::amount> >( "{uniform,0,1,1}" );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );

  test_dist = Utility::fromString<Utility::UnitAwareUniformDistribution<si::energy,si::amount> >( "{Uniform, 0, 1}" );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UniformDistribution, fromStream )
{
  std::istringstream iss( "{Uniform Distribution, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  {
    Utility::UniformDistribution test_dist;

    Utility::fromStream( iss, test_dist );

    FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
  }

  iss.str( "{uniform distribution, -1.0, 1.0, 2.0}" );
  iss.clear();

  {
    Utility::UniformDistribution test_dist;

    Utility::fromStream( iss, test_dist );

    FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
  }

  iss.str( "{uniform-distribution, -1, 1, 2}" );
  iss.clear();

  {
    Utility::UniformDistribution test_dist;

    Utility::fromStream( iss, test_dist );

    FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
  }

  iss.str( "{uniform,-1,1,2}" );
  iss.clear();

  {
    Utility::UniformDistribution test_dist;

    Utility::fromStream( iss, test_dist );

    FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
  }

  iss.str( "{Uniform, -1, 1}" );
  iss.clear();

  {
    Utility::UniformDistribution test_dist;

    Utility::fromStream( iss, test_dist );

    FRENSIE_CHECK( test_dist != *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
    FRENSIE_CHECK_EQUAL( test_dist.getLowerBoundOfIndepVar(), -1.0 );
    FRENSIE_CHECK_EQUAL( test_dist.getUpperBoundOfIndepVar(), 1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, fromStream )
{
  std::istringstream iss( "{Uniform Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  {
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist;

    Utility::fromStream( iss, test_dist );

    FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
  }

  iss.str( "{uniform distribution, 0.0, 1.0, 1.0}" );
  iss.clear();

  {
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist;

    Utility::fromStream( iss, test_dist );

    FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
  }

  iss.str( "{uniform-distribution, 0, 1, 1}" );
  iss.clear();

  {
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist;

    Utility::fromStream( iss, test_dist );

    FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
  }

  iss.str( "{uniform,0,1,1}" );
  iss.clear();

  {
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist;

    Utility::fromStream( iss, test_dist );

    FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
  }

  iss.str( "{Uniform, 0, 1}" );
  iss.clear();

  {
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist;

    Utility::fromStream( iss, test_dist );

    FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
  }
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UniformDistribution, istream_operator )
{
  std::istringstream iss( "{Uniform Distribution, -1.000000000000000000e+00, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  {
    Utility::UniformDistribution test_dist;

    iss >> test_dist;

    FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
  }

  iss.str( "{uniform distribution, -1.0, 1.0, 2.0}" );
  iss.clear();

  {
    Utility::UniformDistribution test_dist;

    iss >> test_dist;

    FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
  }

  iss.str( "{uniform-distribution, -1, 1, 2}" );
  iss.clear();

  {
    Utility::UniformDistribution test_dist;

    iss >> test_dist;

    FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
  }

  iss.str( "{uniform,-1,1,2}" );
  iss.clear();

  {
    Utility::UniformDistribution test_dist;

    iss >> test_dist;

    FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
  }

  iss.str( "{Uniform, -1, 1}" );
  iss.clear();

  {
    Utility::UniformDistribution test_dist;

    iss >> test_dist;

    FRENSIE_CHECK( test_dist != *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
    FRENSIE_CHECK_EQUAL( test_dist.getLowerBoundOfIndepVar(), -1.0 );
    FRENSIE_CHECK_EQUAL( test_dist.getUpperBoundOfIndepVar(), 1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, istream_operator )
{
  std::istringstream iss( "{Uniform Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  {
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist;

    iss >> test_dist;

    FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
  }

  iss.str( "{uniform distribution, 0.0, 1.0, 1.0}" );
  iss.clear();

  {
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist;

    iss >> test_dist;

    FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
  }

  iss.str( "{uniform-distribution, 0, 1, 1}" );
  iss.clear();

  {
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist;

    iss >> test_dist;

    FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
  }

  iss.str( "{uniform,0,1,1}" );
  iss.clear();

  {
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist;

    iss >> test_dist;

    FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
  }

  iss.str( "{Uniform, 0, 1}" );
  iss.clear();

  {
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> test_dist;

    iss >> test_dist;

    FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );
  }
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree
FRENSIE_UNIT_TEST( UniformDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *distribution );

  Utility::UniformDistribution copy_dist =
    ptree.get<Utility::UniformDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );

  ptree.put( "test distribution", *tab_distribution );

  copy_dist = ptree.get<Utility::UniformDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::UniformDistribution*>( tab_distribution.get() ) );

  ptree.clear();
  
  // Use the PropertyTreeCompatibleObject interface
  ptree = distribution->toPropertyTree( true );
  
  copy_dist = ptree.get_value<Utility::UniformDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::UniformDistribution*>( tab_distribution.get() ) );

  ptree = distribution->toPropertyTree( false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );

  ptree = distribution->toPropertyTree();

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );

  // Use the PropertyTree helper methods
  ptree = Utility::toPropertyTree( *distribution, true );

  copy_dist = ptree.get_value<Utility::UniformDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::UniformDistribution*>( tab_distribution.get() ) );

  ptree = Utility::toPropertyTree( *tab_distribution, true );

  copy_dist = ptree.get_value<Utility::UniformDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::UniformDistribution*>( tab_distribution.get() ) );

  ptree = Utility::toPropertyTree( *distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );

  ptree = Utility::toPropertyTree( *tab_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );

  ptree = Utility::toPropertyTree( *distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );

  ptree = Utility::toPropertyTree( *tab_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be written to a property tree
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *unit_aware_distribution );

  Utility::UnitAwareUniformDistribution<si::energy,si::amount> copy_dist =
    ptree.get<Utility::UnitAwareUniformDistribution<si::energy,si::amount> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_distribution.get() )) );

  ptree.put( "test distribution", *unit_aware_tab_distribution );

  copy_dist = ptree.get<Utility::UnitAwareUniformDistribution<si::energy,si::amount> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_tab_distribution.get() )) );

  ptree.clear();
  
  // Use the PropertyTreeCompatibleObject interface
  ptree = unit_aware_distribution->toPropertyTree( true );
  copy_dist = ptree.get_value<Utility::UnitAwareUniformDistribution<si::energy,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_tab_distribution.get() )) );

  ptree = unit_aware_distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = unit_aware_distribution->toPropertyTree();

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  // Use the PropertyTree helper methods
  ptree = Utility::toPropertyTree( *unit_aware_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwareUniformDistribution<si::energy,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_tab_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwareUniformDistribution<si::energy,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_tab_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );  
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UniformDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::UniformDistribution dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::UniformDistribution, expected_dist );

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
    FETCH_FROM_TABLE( Utility::UniformDistribution, expected_dist );

    FRENSIE_CHECK_NO_THROW(
        dist = Utility::fromPropertyTree<Utility::UniformDistribution>(
                                      test_dists_ptree->get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW(
               Utility::fromPropertyTree<Utility::UniformDistribution>(
                                    test_dists_ptree->get_child( dist_name ) ),
               Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwareUniformDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  typedef Utility::UnitAwareUniformDistribution<si::energy,si::amount> DistributionType;
  
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
FRENSIE_UNIT_TEST( UniformDistribution, archive )
{
  std::string archive_name( "test_uniform_dist.h5a" );

  // Create and archive some uniform distributions
  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    Utility::UniformDistribution dist_a( -1.0, 1.0, 0.5 );
    Utility::UniformDistribution dist_b( 0.0, 2.0, 1.0 );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
                      archive << BOOST_SERIALIZATION_NVP( tab_distribution ) );
    FRENSIE_REQUIRE_NO_THROW(
                          archive << BOOST_SERIALIZATION_NVP( distribution ) );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::UniformDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  Utility::UniformDistribution dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::UniformDistribution( 0.0, 2.0, 1.0 ) );

  std::shared_ptr<Utility::TabularOneDDistribution> shared_tab_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "tab_distribution", shared_tab_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::UniformDistribution*>( shared_tab_dist.get() ),
                       *dynamic_cast<Utility::UniformDistribution*>( tab_distribution.get() ) );

  std::shared_ptr<Utility::OneDDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::UniformDistribution*>( shared_dist.get() ),
                       *dynamic_cast<Utility::UniformDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST( UnitAwareUniformDistribution, archive )
{
  std::string archive_name( "test_uniform_dist.h5a" );

  // Create and archive some uniform distributions
  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    Utility::UnitAwareUniformDistribution<si::energy,si::amount> dist_a( -1.0*si::joule, 1.0*si::joule, 0.5*si::mole );
    Utility::UnitAwareUniformDistribution<si::energy,si::amount> dist_b( 0.0*si::joule, 2.0*si::joule, 1.0*si::mole );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
           archive << BOOST_SERIALIZATION_NVP( unit_aware_tab_distribution ) );
    FRENSIE_REQUIRE_NO_THROW(
               archive << BOOST_SERIALIZATION_NVP( unit_aware_distribution ) );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::UnitAwareUniformDistribution<si::energy,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareUniformDistribution<si::energy,si::amount>( -1.0*si::joule, 1.0*si::joule, 0.5*si::mole )) );

  Utility::UnitAwareUniformDistribution<si::energy,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwareUniformDistribution<si::energy,si::amount>( 0.0*si::joule, 2.0*si::joule, 1.0*si::mole )) );

  std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<si::energy,si::amount> > shared_tab_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "unit_aware_tab_distribution", shared_tab_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( shared_tab_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwareUniformDistribution<si::energy,si::amount>*>( unit_aware_tab_distribution.get() )) );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<si::energy,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "unit_aware_distribution", shared_dist ) );
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

