//---------------------------------------------------------------------------//
//!
//! \file   tstNormalDistribution.cpp
//! \author Alex Robinson
//! \brief  Normal distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_NormalDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
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

std::shared_ptr<Utility::OneDDistribution> distribution(
				 new Utility::NormalDistribution( 0.0, 1.0 ) );

std::shared_ptr<Utility::UnitAwareOneDDistribution<cgs::length,si::amount> > unit_aware_distribution( new Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 0.0*si::meter, 0.01*si::meter, 0.5*si::mole, -Utility::QuantityTraits<quantity<si::length> >::inf(), Utility::QuantityTraits<quantity<si::length> >::inf() ) );

//---------------------------------------------------------------------------//
// Testing Tables
//---------------------------------------------------------------------------//
// This table describes the data in the property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since all
  // distributions are serialized the same
  Utility::NormalDistribution dummy_dist;

  const double& pi = Utility::PhysicalConstants::pi;
  const double inf = Utility::QuantityTraits<double>::inf();

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_5_args" ) << "Distribution A" << true << no_unused_children << Utility::NormalDistribution( 0.0, 1.0, 3.0 );
  NEW_ROW( "inline_4_args" ) << "Distribution B" << true << no_unused_children << Utility::NormalDistribution( 0.0, 1.0, 1.0, -pi, pi );
  NEW_ROW( "inline_3_args" ) << "Distribution C" << true << no_unused_children << Utility::NormalDistribution( 0.0, 1.0, 1.0, 0.0 );
  NEW_ROW( "inline_2_args" ) << "Distribution D" << true << no_unused_children << Utility::NormalDistribution( 1.0, 1.0 );
  NEW_ROW( "inline_1_arg" ) << "Distribution E" << true << no_unused_children << Utility::NormalDistribution( -pi );
  NEW_ROW( "inline_0_args" ) << "Distribution F" << true << no_unused_children << Utility::NormalDistribution();
  NEW_ROW( "inline_bad_type" ) << "Distribution G" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_mult" ) << "Distribution H" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_mult" ) << "Distribution I" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_mean" ) << "Distribution J" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_std_dev" ) << "Distribution K" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_std_dev" ) << "Distribution L" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_std_dev" ) << "Distribution M" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_bad_limits" ) << "Distribution N" << false << no_unused_children << dummy_dist;

  NEW_ROW( "0_args" ) << "Distribution O" << true << no_unused_children << Utility::NormalDistribution();
  NEW_ROW( "1_arg" ) << "Distribution P" << true << no_unused_children << Utility::NormalDistribution( -2.0 );
  NEW_ROW( "2_args" ) << "Distribution Q" << true << no_unused_children << Utility::NormalDistribution( 0.0, 2.0 );
  NEW_ROW( "3_args" ) << "Distribution R" << true << no_unused_children << Utility::NormalDistribution( 1.0, 1.0, 1.0, -1.0 );
  NEW_ROW( "4_args" ) << "Distribution S" << true << no_unused_children << Utility::NormalDistribution( 10.0, 2.0, 1.0, -inf, 20.0 );
  NEW_ROW( "5_args" ) << "Distribution T" << true << std::vector<std::string>( {"dummy"} ) << Utility::NormalDistribution( 1.0, 2.0, 3.0, -2.0, 2.0 );
  NEW_ROW( "duplicate_args" ) << "Distribution U" << true << std::vector<std::string>( {"mean", "standard deviation", "lower bound", "upper bound", "multiplier"} ) << Utility::NormalDistribution( 1.0, 2.0, 2.0, -1.0, 1.0 );
  NEW_ROW( "bad_type" ) << "Distribution V" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_mult" ) << "Distribution W" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_mult" ) << "Distribution X" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_mean" ) << "Distribution Y" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_std_dev" ) << "Distribution Z" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_std_dev" ) << "Distribution AA" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_std_dev" ) << "Distribution AB" << false << no_unused_children << dummy_dist;
  NEW_ROW( "bad_limits" ) << "Distribution AC" << false << no_unused_children << dummy_dist;
  
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( NormalDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), exp( -4.0/2.0 ) );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -2.0 ), exp( -4.0/2.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*cgs::centimeter ),
		       0.5*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*cgs::centimeter ),
		       0.5*exp( -4.0/2.0 )*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -2.0*cgs::centimeter ),
		       0.5*exp( -4.0/2.0 )*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( NormalDistribution, evaluatePDF )
{
  double center_value = 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi );
  double off_center_value = center_value*exp( -4.0/2.0 );

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), center_value);
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), off_center_value );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -2.0 ), off_center_value );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, evaluatePDF )
{
  double center_value = 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*cgs::centimeter ),
		       center_value/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 2.0*cgs::centimeter ),
		       center_value*exp( -4.0/2.0 )/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( -2.0*cgs::centimeter ),
		       center_value*exp( -4.0/2.0 )/cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( NormalDistribution, sample_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::NormalDistribution::sample( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );

  sample = Utility::NormalDistribution::sample( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  sample = Utility::NormalDistribution::sample( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, sample_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample =
    Utility::UnitAwareNormalDistribution<cgs::length>::sample(
				    0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sample(
				    0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sample(
				    0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( NormalDistribution, sampleAndRecordTrials_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = Utility::NormalDistribution::sampleAndRecordTrials(
							    trials, 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = Utility::NormalDistribution::sampleAndRecordTrials(
							    trials, 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = Utility::NormalDistribution::sampleAndRecordTrials(
							    trials, 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, sampleAndRecordTrials_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<cgs::length> sample =
    Utility::UnitAwareNormalDistribution<cgs::length>::sampleAndRecordTrials(
			    trials, 0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sampleAndRecordTrials(
			    trials, 0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sampleAndRecordTrials(
			    trials, 0.0*cgs::centimeter, 1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( NormalDistribution, sample )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, sample )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( NormalDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( NormalDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       Utility::QuantityTraits<quantity<cgs::length> >::inf());
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( NormalDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(),
		       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       -Utility::QuantityTraits<quantity<cgs::length> >::inf());
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( NormalDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::NORMAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::NORMAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
FRENSIE_UNIT_TEST( NormalDistribution, getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( Utility::NormalDistribution::typeName( true, false, " " ),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( Utility::NormalDistribution::typeName( false ),
                       "Normal" );
  FRENSIE_CHECK_EQUAL( Utility::typeName<Utility::NormalDistribution>(),
                       "NormalDistribution" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>::typeName( true, false, " " )),
                       "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>::typeName( false )),
                       "Normal" );
  FRENSIE_CHECK_EQUAL( (Utility::typeName<Utility::UnitAwareNormalDistribution<cgs::length,si::amount> >()),
                       (std::string("UnitAwareNormalDistribution<")+Utility::typeName<cgs::length,si::amount>()+">"));
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( NormalDistribution, isTabular )
{
  FRENSIE_CHECK( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, isTabular )
{
  FRENSIE_CHECK( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( NormalDistribution, isContinuous )
{
  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( NormalDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::NormalDistribution test_dist( 10.0, 1.0, 1.0, 19.0 );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UnitAwareNormalDistribution<cgs::length,si::amount>
    test_dist( 10.0*si::meter,
               1.0*si::meter,
               1.0*si::mole,
               1.0*si::meter,
               19.0*si::meter );

  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
FRENSIE_UNIT_TEST( NormalDistribution, toString )
{
  std::string dist_string = Utility::toString( Utility::NormalDistribution() );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::NormalDistribution( 2.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::NormalDistribution( 2.0, 3.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::NormalDistribution( 2.0, 3.0, 4.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 4.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::NormalDistribution( -2.0, 3.0, 4.0, -1.0, 1.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, -2.000000000000000000e+00, 3.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 4.000000000000000000e+00}" );

  dist_string = Utility::toString( *distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be converted to a string
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, toString )
{
  std::string dist_string = Utility::toString( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>() );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 4.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( -2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, -2.000000000000000000e+00, 3.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 4.000000000000000000e+00}" );

  dist_string = Utility::toString( *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( NormalDistribution, toStream )
{
  std::ostringstream oss;
  Utility::toStream( oss, Utility::NormalDistribution() );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::NormalDistribution( 2.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::NormalDistribution( 2.0, 3.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::NormalDistribution( 2.0, 3.0, 4.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 4.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::NormalDistribution( -2.0, 3.0, 4.0, -1.0, 1.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, -2.000000000000000000e+00, 3.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 4.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, toStream )
{
  std::ostringstream oss;
  
  Utility::toStream( oss, Utility::UnitAwareNormalDistribution<cgs::length,si::amount>() );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 4.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( -2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, -2.000000000000000000e+00, 3.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 4.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( NormalDistribution, ostream_operator )
{
  std::ostringstream oss;
  oss << Utility::NormalDistribution();

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::NormalDistribution( 2.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::NormalDistribution( 2.0, 3.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::NormalDistribution( 2.0, 3.0, 4.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 4.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::NormalDistribution( -2.0, 3.0, 4.0, -1.0, 1.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, -2.000000000000000000e+00, 3.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 4.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << *distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, ostream_operator )
{
  std::ostringstream oss;
  
  oss << Utility::UnitAwareNormalDistribution<cgs::length,si::amount>();

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 2.000000000000000000e+00, 3.000000000000000000e+00, -inf, inf, 4.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( -2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, -2.000000000000000000e+00, 3.000000000000000000e+00, -1.000000000000000000e+00, 1.000000000000000000e+00, 4.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Normal Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00, -inf, inf, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a string
FRENSIE_UNIT_TEST( NormalDistribution, fromString )
{
  Utility::NormalDistribution test_dist =
    Utility::fromString<Utility::NormalDistribution>( "{Normal Distribution}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution() );

  test_dist = Utility::fromString<Utility::NormalDistribution>( "{Normal Distribution, 3.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0 ) );

  test_dist = Utility::fromString<Utility::NormalDistribution>( "{Normal Distribution, 3.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0 ) );

  test_dist = Utility::fromString<Utility::NormalDistribution>( "{Normal Distribution, 3.0, 2.0, -1.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0, 1.0, -1.0 ) );

  test_dist = Utility::fromString<Utility::NormalDistribution>( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0, 1.0, -1.0, 1.0 ) );

  test_dist = Utility::fromString<Utility::NormalDistribution>( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0, 4.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0, 4.0, -1.0, 1.0 ) );

  test_dist = Utility::fromString<Utility::NormalDistribution>( Utility::toString(*distribution) );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::NormalDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a string
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, fromString )
{
  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> test_dist =
    Utility::fromString<Utility::UnitAwareNormalDistribution<cgs::length,si::amount> >( "{Normal Distribution}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>()) );

  test_dist = Utility::fromString<Utility::UnitAwareNormalDistribution<cgs::length,si::amount> >( "{Normal Distribution, 3.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter )) );

  test_dist = Utility::fromString<Utility::UnitAwareNormalDistribution<cgs::length,si::amount> >( "{Normal Distribution, 3.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  test_dist = Utility::fromString<Utility::UnitAwareNormalDistribution<cgs::length,si::amount> >( "{Normal Distribution, 3.0, 2.0, -1.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter, 1.0*si::mole, -1.0*cgs::centimeter )) );

  test_dist = Utility::fromString<Utility::UnitAwareNormalDistribution<cgs::length,si::amount> >( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter, 1.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  test_dist = Utility::fromString<Utility::UnitAwareNormalDistribution<cgs::length,si::amount> >( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0, 4.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  test_dist = Utility::fromString<Utility::UnitAwareNormalDistribution<cgs::length,si::amount> >( Utility::toString(*unit_aware_distribution) );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( NormalDistribution, fromStream )
{  
  Utility::NormalDistribution test_dist;

  std::istringstream iss( "{Normal Distribution}" );
  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution() );

  iss.str( "{Normal Distribution, 3.0}" );
  iss.clear();
  
  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0 ) );

  iss.str( "{Normal Distribution, 3.0, 2.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0 ) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0, 1.0, -1.0 ) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0, 1.0, -1.0, 1.0 ) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0, 4.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0, 4.0, -1.0, 1.0 ) );

  iss.str( Utility::toString(*distribution) );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::NormalDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, fromStream )
{
  std::istringstream iss( "{Normal Distribution}" );
  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>()) );

  iss.str( "{Normal Distribution, 3.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter )) );

  iss.str( "{Normal Distribution, 3.0, 2.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter, 1.0*si::mole, -1.0*cgs::centimeter )) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter, 1.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0, 4.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  iss.str( Utility::toString(*unit_aware_distribution) );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( NormalDistribution, istream_operator )
{  
  Utility::NormalDistribution test_dist;

  std::istringstream iss( "{Normal Distribution}" );
  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution() );

  iss.str( "{Normal Distribution, 3.0}" );
  iss.clear();
  
  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0 ) );

  iss.str( "{Normal Distribution, 3.0, 2.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0 ) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0, 1.0, -1.0 ) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0, 1.0, -1.0, 1.0 ) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0, 4.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::NormalDistribution( 3.0, 2.0, 4.0, -1.0, 1.0 ) );

  iss.str( Utility::toString(*distribution) );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::NormalDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, istream_operator )
{
  std::istringstream iss( "{Normal Distribution}" );
  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>()) );

  iss.str( "{Normal Distribution, 3.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter )) );

  iss.str( "{Normal Distribution, 3.0, 2.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter, 1.0*si::mole, -1.0*cgs::centimeter )) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter, 1.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  iss.str( "{Normal Distribution, 3.0, 2.0, -1.0, 1.0, 4.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 3.0*cgs::centimeter, 2.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  iss.str( Utility::toString(*unit_aware_distribution) );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be written to a property tree
FRENSIE_UNIT_TEST( NormalDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", Utility::NormalDistribution() );

  Utility::NormalDistribution copy_dist =
    ptree.get<Utility::NormalDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution() );

  ptree.put( "test distribution", Utility::NormalDistribution( 2.0 ) );

  copy_dist = ptree.get<Utility::NormalDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0 ) );

  ptree.put( "test distribution", Utility::NormalDistribution( 2.0, 3.0 ) );

  copy_dist = ptree.get<Utility::NormalDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0 ) );

  ptree.put( "test distribution", Utility::NormalDistribution( 2.0, 3.0, 4.0 ) );

  copy_dist = ptree.get<Utility::NormalDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0, 4.0 ) );

  ptree.put( "test distribution", Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0 ) );

  copy_dist = ptree.get<Utility::NormalDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0 ) );

  ptree.put( "test distribution", Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0, 1.0 ) );

  copy_dist = ptree.get<Utility::NormalDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0, 1.0 ) );

  ptree.put( "test distribution", *distribution );

  copy_dist = ptree.get<Utility::NormalDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::NormalDistribution*>( distribution.get() ) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::NormalDistribution().toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution() );

  ptree = Utility::NormalDistribution().toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::NormalDistribution( 2.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0 ) );

  ptree = Utility::NormalDistribution( 2.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::NormalDistribution( 2.0, 3.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0 ) );

  ptree = Utility::NormalDistribution( 2.0, 3.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::NormalDistribution( 2.0, 3.0, 4.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0, 4.0 ) );

  ptree = Utility::NormalDistribution( 2.0, 3.0, 4.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0 ) );

  ptree = Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0, 1.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0, 1.0 ) );

  ptree = Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0, 1.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::NormalDistribution*>( distribution.get() ) );

  ptree = distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::NormalDistribution(), true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution() );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution(), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution( 2.0 ), true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0 ) );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution( 2.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution( 2.0, 3.0 ), true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0 ) );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution( 2.0, 3.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution( 2.0, 3.0, 4.0 ), true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0, 4.0 ) );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution( 2.0, 3.0, 4.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0 ), true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0 ) );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0 ), false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0, 1.0 ), true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0, 1.0 ) );

  ptree = Utility::toPropertyTree( Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0, 1.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = Utility::toPropertyTree( *distribution, true );

  copy_dist = ptree.get_value<Utility::NormalDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::NormalDistribution*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be written to a property tree
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", Utility::UnitAwareNormalDistribution<cgs::length,si::amount>() );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> copy_dist =
    ptree.get<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>()) );

  ptree.put( "test distribution", (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter )) );

  copy_dist = ptree.get<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter )) );

  ptree.put( "test distribution", Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter ) );

  copy_dist = ptree.get<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter )) );

  ptree.put( "test distribution", Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole ) );

  copy_dist = ptree.get<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole )) );

  ptree.put( "test distribution", Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter ) );

  copy_dist = ptree.get<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter )) );

  ptree.put( "test distribution", Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter ) );

  copy_dist = ptree.get<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  ptree.put( "test distribution", *unit_aware_distribution );

  copy_dist = ptree.get<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>*>( unit_aware_distribution.get() )) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>().toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>()) );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>().toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter )) );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter )) );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole )) );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter )) );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  ptree = Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = unit_aware_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = unit_aware_distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 0.5 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>(), true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>()) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>(), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter ), false );
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Normal Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 0.5 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "mean" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "standard deviation" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ),
                       -Utility::QuantityTraits<double>::inf() );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ),
                       Utility::QuantityTraits<double>::inf() );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( NormalDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  FETCH_FROM_TABLE( std::string, dist_name );                           
  FETCH_FROM_TABLE( bool, valid_dist_rep );                             
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children ); 
  FETCH_FROM_TABLE( Utility::NormalDistribution, expected_dist );     
                                                   
  Utility::NormalDistribution dist;                         
  std::vector<std::string> unused_children;        

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
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
    FRENSIE_CHECK_NO_THROW(
            dist = Utility::fromPropertyTree<Utility::NormalDistribution>(
                                      test_dists_ptree->get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW(
                 Utility::fromPropertyTree<Utility::NormalDistribution>(
                                  test_dists_ptree->get_child( dist_name ) ), 
                 Utility::PropertyTreeConversionException );    
  }
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwareNormalDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  typedef Utility::UnitAwareNormalDistribution<cgs::length,si::amount> Distribution;
  
  FETCH_FROM_TABLE( std::string, dist_name );                           
  FETCH_FROM_TABLE( bool, valid_dist_rep );                             
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children ); 
  FETCH_FROM_TABLE( Distribution, expected_dist );     
                                                   
  Distribution dist;                         
  std::vector<std::string> unused_children;        

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
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
    FRENSIE_CHECK_NO_THROW( dist = Utility::fromPropertyTree<Distribution>(
                                      test_dists_ptree->get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::fromPropertyTree<Distribution>(
                                    test_dists_ptree->get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST( NormalDistribution, archive )
{
  std::string archive_name( "test_normal_dist.h5a" );

  // Create and archive some normal distributions
  {
    Utility::NormalDistribution dist_a;
    Utility::NormalDistribution dist_b( 2.0 );
    Utility::NormalDistribution dist_c( 2.0, 3.0 );
    Utility::NormalDistribution dist_d( 2.0, 3.0, 4.0 );
    Utility::NormalDistribution dist_e( 2.0, 3.0, 4.0, -1.0 );
    Utility::NormalDistribution dist_f( 2.0, 3.0, 4.0, -1.0, 1.0 );

    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_c ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_d ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_e ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_f ) );
    FRENSIE_REQUIRE_NO_THROW(
                          archive << BOOST_SERIALIZATION_NVP( distribution ) );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::NormalDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::NormalDistribution() );

  Utility::NormalDistribution dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::NormalDistribution( 2.0 ) );

  Utility::NormalDistribution dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, Utility::NormalDistribution( 2.0, 3.0 ) );

  Utility::NormalDistribution dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_d ) );
  FRENSIE_CHECK_EQUAL( dist_d, Utility::NormalDistribution( 2.0, 3.0, 4.0 ) );

  Utility::NormalDistribution dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_e ) );
  FRENSIE_CHECK_EQUAL( dist_e, Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0 ) );

  Utility::NormalDistribution dist_f;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_f ) );
  FRENSIE_CHECK_EQUAL( dist_f, Utility::NormalDistribution( 2.0, 3.0, 4.0, -1.0, 1.0 ) );

  std::shared_ptr<Utility::OneDDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::NormalDistribution*>( shared_dist.get() ),
                       *dynamic_cast<Utility::NormalDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST( UnitAwareNormalDistribution, archive )
{
  std::string archive_name( "test_unit_aware_normal_dist.h5a" );

  // Create and archive some normal distributions
  {
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_a;
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_b( 2.0*cgs::centimeter );
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_c( 2.0*cgs::centimeter, 3.0*cgs::centimeter );
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_d( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole );
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_e( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter );
    Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_f( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter );

    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_c ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_d ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_e ) );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_f ) );
    FRENSIE_REQUIRE_NO_THROW(
               archive << BOOST_SERIALIZATION_NVP( unit_aware_distribution ) );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>()) );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter )) );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter )) );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_d ) );
  FRENSIE_CHECK_EQUAL( dist_d, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole )) );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_e ) );
  FRENSIE_CHECK_EQUAL( dist_e, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter )) );

  Utility::UnitAwareNormalDistribution<cgs::length,si::amount> dist_f;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_f ) );
  FRENSIE_CHECK_EQUAL( dist_f, (Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 2.0*cgs::centimeter, 3.0*cgs::centimeter, 4.0*si::mole, -1.0*cgs::centimeter, 1.0*cgs::centimeter )) );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<cgs::length,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "unit_aware_distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>*>( shared_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwareNormalDistribution<cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareNormalDistribution,
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

  // Copy from unitless distribution to distribution type A (static method)
  Utility::UnitAwareNormalDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareNormalDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::NormalDistribution*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwareNormalDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi ) );
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

  Utility::setQuantity( indep_quantity_a, 2.0 );
  Utility::setQuantity( inv_indep_quantity_a, exp( -4.0/2.0 )/sqrt( 2.0*Utility::PhysicalConstants::pi ) );
  Utility::setQuantity( dep_quantity_a, exp( -4.0/2.0 ) );

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

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNormalDistribution.cpp
//---------------------------------------------------------------------------//

