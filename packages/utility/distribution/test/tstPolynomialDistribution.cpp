//---------------------------------------------------------------------------//
//!
//! \file   tstPolynomialDistribution.cpp
//! \author Alex Robinson
//! \brief  Polynomial distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_PolynomialDistribution.hpp"
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

std::shared_ptr<Utility::OneDDistribution> distribution;

std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
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
  Utility::PolynomialDistribution dummy_dist;

  double pi = Utility::PhysicalConstants::pi;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_ucase_full_name" ) << "Distribution A" << true << no_unused_children << Utility::PolynomialDistribution( {1.0, 2.0, 3.0}, 0.0, 1.0 );
  NEW_ROW( "inline_lcase_full_name" ) << "Distribution B" << true << no_unused_children << Utility::PolynomialDistribution( {1.0, 2.0, 3.0}, 1.0, 2.0 );
  NEW_ROW( "inline_ucase_abv_name" ) << "Distribution C" << true << no_unused_children << Utility::PolynomialDistribution( {1.0, 1.0, 1.0, 1.0, 1.0}, 1.0, pi );
  NEW_ROW( "inline_lcase_abv_name" ) << "Distribution D" << true << no_unused_children << Utility::PolynomialDistribution( {0.0, 1.0, 1.0, 1.0}, pi/2, 3*pi/2 );
  NEW_ROW( "inline_bad_type" ) << "Distribution E" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_0_args" ) << "Distribution F" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_1_arg" ) << "Distribution G" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_2_args" ) << "Distribution H" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_no_coeffs" ) << "Distribution I" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_coeffs" ) << "Distribution J" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_coeff" ) << "Distribution K" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_coeff" ) << "Distribution L" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_lower_limit" ) << "Distribution M" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_bad_limits)" ) << "Distribution N" << false << no_unused_children << dummy_dist;

  NEW_ROW( "ucase_full_name" ) << "Distribution O" << true << no_unused_children << Utility::PolynomialDistribution( {1.0, 2.0, 3.0}, 0.0, 1.0 );
  NEW_ROW( "lcase_full_name" ) << "Distribution P" << true << no_unused_children << Utility::PolynomialDistribution( {1.0, 2.0, 3.0}, 1.0, 2.0 );
  NEW_ROW( "ucase_abv_name" ) << "Distribution Q" << true << std::vector<std::string>( {"dummy"} ) << Utility::PolynomialDistribution( {1.0, 1.0, 1.0, 1.0, 1.0}, 1.0, 10.0 );
  NEW_ROW( "repeated_keys" ) << "Distribution R" << true << std::vector<std::string>( {"coefficients", "upper boundary", "lower boundary"} ) << Utility::PolynomialDistribution( {0.0, 0.0, 1.0, 1.0}, 1.0, 10.0 );
  NEW_ROW( "bad_type" ) << "Distribution S" << false << no_unused_children << dummy_dist;
  NEW_ROW( "0_args" ) << "Distribution T" << false << no_unused_children << dummy_dist;
  NEW_ROW( "1_arg" ) << "Distribution U" << false << no_unused_children << dummy_dist;
  NEW_ROW( "no_upper_limit" ) << "Distribution V" << false << no_unused_children << dummy_dist;
  NEW_ROW( "no_lower_limit" ) << "Distribution W" << false << no_unused_children << dummy_dist;
  NEW_ROW( "no_coeffs" ) << "Distribution X" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_coeffs" ) << "Distribution Y" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_coeff" ) << "Distribution Z" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_coeff" ) << "Distribution AA" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_lower_limit" ) << "Distribution AB" << false << no_unused_children << dummy_dist;
  NEW_ROW( "bad_limits" ) << "Distribution AC" << false << no_unused_children << dummy_dist;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( PolynomialDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5 ), 2.75 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), 6.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV ),
		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5*MeV ),
		       2.75*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV ),
		       6.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( PolynomialDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 1.0/3.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.5 ), 2.75/3.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( -1.0*MeV ),
		       0.0/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       (1.0/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.5*MeV ),
		       (2.75/3.0)/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
		       2.0/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 2.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( PolynomialDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.5 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, sqrt(0.5) );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, pow( 0.5, 1.0/3.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.5*MeV );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, sqrt(0.5)*MeV );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, pow( 0.5, (1.0/3.0) )*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( PolynomialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.5 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, sqrt(0.5) );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, pow( 0.5, 1.0/3.0 ) );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<MegaElectronVolt> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.5*MeV );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, sqrt(0.5)*MeV );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*MeV );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, pow( 0.5, 1.0/3.0 )*MeV );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( PolynomialDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( PolynomialDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::POLYNOMIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::POLYNOMIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
FRENSIE_UNIT_TEST( PolynomialDistribution, getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( Utility::PolynomialDistribution::typeName( true, false, " " ),
                       "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( Utility::PolynomialDistribution::typeName( false ),
                       "Polynomial" );
  FRENSIE_CHECK_EQUAL( Utility::typeName<Utility::PolynomialDistribution>(),
                       "PolynomialDistribution" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution,
                   getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>::typeName( true, false, " " )),
                       "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>::typeName( false )),
                       "Polynomial" );
  FRENSIE_CHECK_EQUAL( (Utility::typeName<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> >()),
                       (std::string("UnitAwarePolynomialDistribution<")+Utility::typeName<MegaElectronVolt,si::amount>()+">") );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( PolynomialDistribution, isTabular )
{
  FRENSIE_CHECK( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, isTabular )
{
  FRENSIE_CHECK( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( PolynomialDistribution, isContinuous )
{
  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( PolynomialDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  std::vector<double> coeffs( 4 );
  coeffs[0] = 1.0;
  coeffs[1] = 2.0;
  coeffs[2] = 3.0;
  coeffs[3] = 0.0;

  std::shared_ptr<Utility::PolynomialDistribution>
    test_dist( new Utility::PolynomialDistribution( coeffs, 1.0, 2.0 ) );

  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is only compatible with lin-lin interp
  coeffs[0] = 0.0;

  test_dist.reset( new Utility::PolynomialDistribution( coeffs, 0.0, 1.0 ) );

  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !test_dist->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !test_dist->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !test_dist->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatiblw with the interp type
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution,
                   isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  std::vector<double> coeffs( 4 );
  coeffs[0] = 1.0;
  coeffs[1] = 2.0;
  coeffs[2] = 3.0;
  coeffs[3] = 0.0;

  std::shared_ptr<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> >
    test_dist( new Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( coeffs, 1.0*MeV, 2.0*MeV ) );

  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is only compatible with lin-lin interp
  coeffs[0] = 0.0;

  test_dist.reset( new Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( coeffs, 0.0*MeV, 1.0*MeV ) );

  FRENSIE_CHECK( test_dist->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !test_dist->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !test_dist->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !test_dist->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be converted to a string
FRENSIE_UNIT_TEST( PolynomialDistribution, toString )
{
  std::string dist_string = Utility::toString( Utility::PolynomialDistribution( {0.0, 1.0, 0.0, 1.0}, 1.0, 2.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Polynomial Distribution, {0.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  dist_string = Utility::toString( *distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Polynomial Distribution, {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00}, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be converted to a string
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, toString )
{
  std::string dist_string = Utility::toString( Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 0.0, 1.0}, 1.0*MeV, 2.0*MeV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Polynomial Distribution, {0.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  dist_string = Utility::toString( *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Polynomial Distribution, {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00}, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be placed in a stream
FRENSIE_UNIT_TEST( PolynomialDistribution, toStream )
{
  std::ostringstream oss;
  Utility::toStream( oss, Utility::PolynomialDistribution( {0.0, 1.0, 0.0, 1.0}, 1.0, 2.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Polynomial Distribution, {0.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Polynomial Distribution, {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00}, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, toStream )
{
  std::ostringstream oss;
  Utility::toStream( oss, Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 0.0, 1.0}, 1.0*MeV, 2.0*MeV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Polynomial Distribution, {0.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Polynomial Distribution, {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00}, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be placed in a stream
FRENSIE_UNIT_TEST( PolynomialDistribution, ostream_operator )
{
  std::ostringstream oss;
  oss << Utility::PolynomialDistribution( {0.0, 1.0, 0.0, 1.0}, 1.0, 2.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Polynomial Distribution, {0.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << *distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Polynomial Distribution, {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00}, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, ostream_operator )
{
  std::ostringstream oss;
  oss << Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 0.0, 1.0}, 1.0*MeV, 2.0*MeV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Polynomial Distribution, {0.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}, 1.000000000000000000e+00, 2.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Polynomial Distribution, {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00}, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a string
FRENSIE_UNIT_TEST( PolynomialDistribution, fromString )
{
  Utility::PolynomialDistribution test_dist =
    Utility::fromString<Utility::PolynomialDistribution>( "{Polynomial Distribution, {3.0, 2.0, 1.0, 1.0}, 1.0, 2.0}");

  FRENSIE_CHECK_EQUAL( test_dist, Utility::PolynomialDistribution( {3.0, 2.0, 1.0, 1.0}, 1.0, 2.0 ));

  test_dist = Utility::fromString<Utility::PolynomialDistribution>( Utility::toString( *distribution ) );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::PolynomialDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a string
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, fromString )
{
  Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> test_dist =
    Utility::fromString<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> >( "{Polynomial Distribution, {3.0, 2.0, 1.0, 1.0}, 1.0, 2.0}");

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {3.0, 2.0, 1.0, 1.0}, 1.0*MeV, 2.0*MeV )) );

  test_dist = Utility::fromString<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> >( Utility::toString( *unit_aware_distribution ) );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( PolynomialDistribution, fromStream )
{
  std::istringstream iss( "{Polynomial Distribution, {3.0, 2.0, 1.0, 1.0}, 1.0, 2.0}");
  Utility::PolynomialDistribution test_dist;

  Utility::fromStream( iss, test_dist );
  
  FRENSIE_CHECK_EQUAL( test_dist, Utility::PolynomialDistribution( {3.0, 2.0, 1.0, 1.0}, 1.0, 2.0 ));

  iss.str( Utility::toString( *distribution ) );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::PolynomialDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, fromStream )
{
  std::istringstream iss( "{Polynomial Distribution, {3.0, 2.0, 1.0, 1.0}, 1.0, 2.0}" );
  Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {3.0, 2.0, 1.0, 1.0}, 1.0*MeV, 2.0*MeV )) );

  iss.str( Utility::toString( *unit_aware_distribution ) );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( PolynomialDistribution, istream_operator )
{
  std::istringstream iss( "{Polynomial Distribution, {3.0, 2.0, 1.0, 1.0}, 1.0, 2.0}");
  Utility::PolynomialDistribution test_dist;

  iss >> test_dist;
  
  FRENSIE_CHECK_EQUAL( test_dist, Utility::PolynomialDistribution( {3.0, 2.0, 1.0, 1.0}, 1.0, 2.0 ));

  iss.str( Utility::toString( *distribution ) );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::PolynomialDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, istream_operator )
{
  std::istringstream iss( "{Polynomial Distribution, {3.0, 2.0, 1.0, 1.0}, 1.0, 2.0}" );
  Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {3.0, 2.0, 1.0, 1.0}, 1.0*MeV, 2.0*MeV )) );

  iss.str( Utility::toString( *unit_aware_distribution ) );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be written to a property tree
FRENSIE_UNIT_TEST( PolynomialDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", Utility::PolynomialDistribution( {0.0, 1.0, 2.0, 3.0}, 0.0, 1.0 ) );

  Utility::PolynomialDistribution copy_dist =
    ptree.get<Utility::PolynomialDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PolynomialDistribution( {0.0, 1.0, 2.0, 3.0}, 0.0, 1.0 ) );

  ptree.put( "test distribution", *distribution );

  copy_dist = ptree.get<Utility::PolynomialDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::PolynomialDistribution*>( distribution.get() ) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::PolynomialDistribution( {0.0, 1.0, 2.0, 3.0}, 1.0, 2.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::PolynomialDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PolynomialDistribution( {0.0, 1.0, 2.0, 3.0}, 1.0, 2.0 ) );

  ptree = Utility::PolynomialDistribution( {0.0, 1.0, 2.0, 3.0}, 1.0, 2.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "coefficients" ),
                       std::vector<double>({0.0, 1.0, 2.0, 3.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 2.0 );

  ptree = distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::PolynomialDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::PolynomialDistribution*>( distribution.get() ) );

  ptree = distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "coefficients" ),
                       std::vector<double>({1.0, 2.0, 3.0, 0.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::PolynomialDistribution( {0.0, 1.0, 2.0, 3.0}, 1.0, 2.0 ), true );

  copy_dist = ptree.get_value<Utility::PolynomialDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::PolynomialDistribution( {0.0, 1.0, 2.0, 3.0}, 1.0, 2.0 ) );

  ptree = Utility::toPropertyTree( Utility::PolynomialDistribution( {0.0, 1.0, 2.0, 3.0}, 1.0, 2.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "coefficients" ),
                       std::vector<double>({0.0, 1.0, 2.0, 3.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 2.0 );

  ptree = Utility::toPropertyTree( *distribution, true );

  copy_dist = ptree.get_value<Utility::PolynomialDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::PolynomialDistribution*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "coefficients" ),
                       std::vector<double>({1.0, 2.0, 3.0, 0.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be written to a property tree
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 2.0, 3.0}, 0.0*MeV, 1.0*MeV ) );

  Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> copy_dist =
    ptree.get<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 2.0, 3.0}, 0.0*MeV, 1.0*MeV )) );

  ptree.put( "test distribution", *unit_aware_distribution );

  copy_dist = ptree.get<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 2.0, 3.0}, 1.0*MeV, 2.0*MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 2.0, 3.0}, 1.0*MeV, 2.0*MeV )) );

  ptree = Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 2.0, 3.0}, 1.0*MeV, 2.0*MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "coefficients" ),
                       std::vector<double>({0.0, 1.0, 2.0, 3.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 2.0 );

  ptree = unit_aware_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = unit_aware_distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "coefficients" ),
                       std::vector<double>({1.0, 2.0, 3.0, 0.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 2.0, 3.0}, 1.0*MeV, 2.0*MeV ), true );

  copy_dist = ptree.get_value<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 2.0, 3.0}, 1.0*MeV, 2.0*MeV )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {0.0, 1.0, 2.0, 3.0}, 1.0*MeV, 2.0*MeV ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "coefficients" ),
                       std::vector<double>({0.0, 1.0, 2.0, 3.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 2.0 );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 4 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Polynomial Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "coefficients" ),
                       std::vector<double>({1.0, 2.0, 3.0, 0.0}) );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "lower boundary" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "upper boundary" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( PolynomialDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::PolynomialDistribution dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::PolynomialDistribution, expected_dist );

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
    FETCH_FROM_TABLE( Utility::PolynomialDistribution, expected_dist );

    FRENSIE_CHECK_NO_THROW(
        dist = Utility::fromPropertyTree<Utility::PolynomialDistribution>(
                                      test_dists_ptree->get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW(
               Utility::fromPropertyTree<Utility::PolynomialDistribution>(
                                    test_dists_ptree->get_child( dist_name ) ),
               Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwarePolynomialDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  typedef Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> DistributionType;
  
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
FRENSIE_UNIT_TEST( PolynomialDistribution, archive )
{
  std::string archive_name( "test_polynomial_dist.h5a" );

  // Create and archive some polynomial distributions
  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    Utility::PolynomialDistribution dist_a( {3.0, 2.0, 1.0}, 1.0, 2.0 );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "dist_b", distribution ) );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::PolynomialDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_a) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::PolynomialDistribution( {3.0, 2.0, 1.0}, 1.0, 2.0 ) );

  std::shared_ptr<Utility::OneDDistribution> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_b) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::PolynomialDistribution*>(dist_b.get()),
                       *dynamic_cast<Utility::PolynomialDistribution*>(distribution.get()) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST( UnitAwarePolynomialDistribution, archive )
{
  std::string archive_name( "test_unit_aware_polynomial_dist.h5a" );

  // Create and archive some polynomial distributions
  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> dist_a( {3.0, 2.0, 1.0}, 1.0*MeV, 2.0*MeV );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "dist_b", unit_aware_distribution ) );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_a) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>( {3.0, 2.0, 1.0}, 1.0*MeV, 2.0*MeV )) );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> > dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP(dist_b) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>*>(dist_b.get())),
                       (*dynamic_cast<Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>*>(unit_aware_distribution.get())) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwarePolynomialDistribution,
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
  Utility::UnitAwarePolynomialDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwarePolynomialDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::PolynomialDistribution*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwarePolynomialDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1/3. );
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
  Utility::setQuantity( inv_indep_quantity_a, 2.0 );
  Utility::setQuantity( dep_quantity_a, 6.0 );

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

  // Initialize the polynomial distribution
  std::vector<double> coeffs( 4 );
  coeffs[0] = 1.0;
  coeffs[1] = 2.0;
  coeffs[2] = 3.0;
  coeffs[3] = 0.0;

  distribution.reset( new Utility::PolynomialDistribution( coeffs, 0.0, 1.0 ));

  // Initialize the unit-aware polynomial distribution
  unit_aware_distribution.reset(
     new Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>(
						  coeffs, 0.0*eV, 1e6*eV ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPolynomialDistribution.cpp
//---------------------------------------------------------------------------//
