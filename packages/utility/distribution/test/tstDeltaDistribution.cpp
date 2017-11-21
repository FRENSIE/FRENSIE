//---------------------------------------------------------------------------//
//!
//! \file   tstDeltaDistribution.cpp
//! \author Alex Robinson
//! \brief  Delta distribution unit tests.
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
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing types
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

std::shared_ptr<Utility::TabularOneDDistribution>
  tab_distribution( new Utility::DeltaDistribution );

std::shared_ptr<Utility::OneDDistribution>
  distribution( tab_distribution );

std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<si::time,si::length> >
  unit_aware_tab_distribution( new Utility::UnitAwareDeltaDistribution<si::time,si::length>( 3.0*si::seconds ) );

std::shared_ptr<Utility::UnitAwareOneDDistribution<si::time,si::length> >
  unit_aware_distribution( unit_aware_tab_distribution );

//---------------------------------------------------------------------------//
// Testing Tables
//---------------------------------------------------------------------------//
// This table describes the data in the property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since they are
  // serialized the same in the table
  Utility::DeltaDistribution dummy_dist;

  double pi = Utility::PhysicalConstants::pi;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_2_args" ) << "Distribution A" << true << no_unused_children << Utility::DeltaDistribution( 0, 2 );
  NEW_ROW( "inline_1_arg" ) << "Distribution B" << true << no_unused_children << Utility::DeltaDistribution( pi );
  NEW_ROW( "inline_0_args" ) << "Distribution C" << true << no_unused_children << Utility::DeltaDistribution();
  NEW_ROW( "inline_bad_type" ) << "Distribution D" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_bad_loc" ) << "Distribution E" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_mult" ) << "Distribution F" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_mult" ) << "Distribution G" << false << no_unused_children << dummy_dist;

  NEW_ROW( "0_args" ) << "Distribution H" << true << no_unused_children << Utility::DeltaDistribution();
  NEW_ROW( "1_arg" ) << "Distribution I" << true << no_unused_children << Utility::DeltaDistribution( -1.0 );
  NEW_ROW( "extra_args" ) << "Distribution J" << true << std::vector<std::string>( {"dummy"} ) << Utility::DeltaDistribution( -2*pi, 0.5 );
  NEW_ROW( "bad_type" ) << "Distribution K" << false << no_unused_children << dummy_dist;
  NEW_ROW( "bad_loc" ) << "Distribution L" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_mult" ) << "Distribution M" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_mult" ) << "Distribution N" << false << no_unused_children << dummy_dist;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( DeltaDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*si::seconds ),
		       0.0*si::meters );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*si::seconds ),
		       1.0*si::meters );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 6.0*si::seconds ),
		       0.0*si::meters );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( DeltaDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*si::seconds ),
		       0.0/si::seconds );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 3.0*si::seconds ),
		       1.0/si::seconds );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 6.0*si::seconds ),
		       0.0/si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
FRENSIE_UNIT_TEST( DeltaDistribution, evaluateCDF )
{
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 1.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, evaluateCDF )
{
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_distribution->evaluateCDF( 0.0*si::seconds ),
		   0.0 );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_distribution->evaluateCDF( 3.0*si::seconds ),
		   1.0 );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_tab_distribution->evaluateCDF( 6.0*si::seconds ),
		   1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DeltaDistribution, sample )
{
  FRENSIE_CHECK_EQUAL( distribution->sample(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, sample )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->sample(), 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DeltaDistribution, sampleAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0;
  double sample = distribution->sampleAndRecordTrials( trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, sampleAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0;

  quantity<si::time> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );

  FRENSIE_CHECK_EQUAL( sample, 3.0*si::seconds );
  FRENSIE_CHECK_EQUAL( trials, 1 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DeltaDistribution, sampleAndRecordBinIndex )
{
  unsigned bin_index = 0;
  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, sampleAndRecordBinIndex )
{
  unsigned bin_index = 0;

  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );

  FRENSIE_CHECK_EQUAL( sample, 3.0*si::seconds );
  FRENSIE_CHECK_EQUAL( bin_index, 0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DeltaDistribution, sampleWithRandomNumber )
{
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, sampleWithRandomNumber )
{
  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DeltaDistribution, sampleInSubrange )
{
  double sample = tab_distribution->sampleInSubrange( 1.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleInSubrange( 0.1 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, sampleInSubrange )
{
  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleInSubrange( 4.0*si::seconds );

  FRENSIE_CHECK_EQUAL( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleInSubrange( 3.1*si::seconds );

  FRENSIE_CHECK_EQUAL( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( DeltaDistribution, sampleWithRandomNumberInSubrange )
{
  double sample =
    tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 2.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution,
		   sampleWithRandomNumberInSubrange )
{
  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 4.0*si::seconds );

  FRENSIE_CHECK_EQUAL( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 3.1*si::seconds );

  FRENSIE_CHECK_EQUAL( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can
// be returned
FRENSIE_UNIT_TEST( DeltaDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can
// be returned
FRENSIE_UNIT_TEST( DeltaDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( DeltaDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::DELTA_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::DELTA_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
FRENSIE_UNIT_TEST( DeltaDistribution, getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( Utility::DeltaDistribution::typeName( true, false, " "),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( Utility::DeltaDistribution::typeName( false ),
                       "Delta" );
  FRENSIE_CHECK_EQUAL( Utility::typeName<Utility::DeltaDistribution>(),
                       "DeltaDistribution" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution,
                   getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareDeltaDistribution<si::time,si::length>::typeName( true, false, " " )),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareDeltaDistribution<si::time,si::length>::typeName( false )),
                       "Delta" );
  FRENSIE_CHECK_EQUAL( (Utility::typeName<Utility::UnitAwareDeltaDistribution<si::time,si::length> >()),
                       std::string("UnitAwareDeltaDistribution<")+Utility::typeName<si::time>()+","+Utility::typeName<si::length>()+">" );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( DeltaDistribution, isTabular )
{
  FRENSIE_CHECK( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, isTabular )
{
  FRENSIE_CHECK( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( DeltaDistribution, isContinuous )
{
  FRENSIE_CHECK( !distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, isContinuous )
{
  FRENSIE_CHECK( !unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( DeltaDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
FRENSIE_UNIT_TEST( DeltaDistribution, toString )
{
  std::string dist_string = Utility::toString( *distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Delta Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::DeltaDistribution( 1.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Delta Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::DeltaDistribution( 1.0, 0.5 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be converted to a string
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, toString )
{
  std::string dist_string = Utility::toString( *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( dist_string, "{Delta Distribution, 3.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Delta Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00}" );
  
  dist_string = Utility::toString( Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds, 0.5*si::meters ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( DeltaDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Delta Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::DeltaDistribution( 1.0, 0.5 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Delta Distribution, 3.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds, 0.5*si::meters ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( DeltaDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Delta Distribution, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::DeltaDistribution( 1.0, 0.5 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *unit_aware_distribution;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Delta Distribution, 3.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds, 0.5*si::meters );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a string
FRENSIE_UNIT_TEST( DeltaDistribution, fromString )
{
  Utility::DeltaDistribution test_dist =
    Utility::fromString<Utility::DeltaDistribution>( "{Delta Distribution, 0.000000000000000000e+00}" );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  test_dist = Utility::fromString<Utility::DeltaDistribution>( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );

  FRENSIE_CHECK( test_dist != *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist.getLowerBoundOfIndepVar(), 1.0 );
  FRENSIE_CHECK_EQUAL( test_dist.evaluate( 1.0 ), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialize from a string
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, fromString )
{
  Utility::UnitAwareDeltaDistribution<si::time,si::length> test_dist =
    Utility::fromString<Utility::UnitAwareDeltaDistribution<si::time,si::length> >( "{Delta Distribution, 3.000000000000000000e+00}" );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  test_dist = Utility::fromString<Utility::UnitAwareDeltaDistribution<si::time,si::length> >( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );

  FRENSIE_CHECK( test_dist != (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );
  FRENSIE_CHECK_EQUAL( test_dist.getLowerBoundOfIndepVar(), 1.0*si::seconds );
  FRENSIE_CHECK_EQUAL( test_dist.evaluate( 1.0*si::seconds ), 0.5*si::meters );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( DeltaDistribution, fromStream )
{
  std::istringstream iss( "{Delta Distribution, 0.000000000000000000e+00}" );

  Utility::DeltaDistribution test_dist;

  Utility::fromStream( iss, test_dist );
  
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  iss.str( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK( test_dist != *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist.getLowerBoundOfIndepVar(), 1.0 );
  FRENSIE_CHECK_EQUAL( test_dist.evaluate( 1.0 ), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, fromStream )
{
  std::istringstream iss( "{Delta Distribution, 3.000000000000000000e+00}" );
  
  Utility::UnitAwareDeltaDistribution<si::time,si::length> test_dist;

  Utility::fromStream( iss, test_dist );
  
  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  iss.str( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK( test_dist != (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );
  FRENSIE_CHECK_EQUAL( test_dist.getLowerBoundOfIndepVar(), 1.0*si::seconds );
  FRENSIE_CHECK_EQUAL( test_dist.evaluate( 1.0*si::seconds ), 0.5*si::meters );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( DeltaDistribution, istream_operator )
{
  std::istringstream iss( "{Delta Distribution, 0.000000000000000000e+00}" );

  Utility::DeltaDistribution test_dist;

  iss >> test_dist;
  
  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  iss.str( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK( test_dist != *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );
  FRENSIE_CHECK_EQUAL( test_dist.getLowerBoundOfIndepVar(), 1.0 );
  FRENSIE_CHECK_EQUAL( test_dist.evaluate( 1.0 ), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, istream_operator )
{
  std::istringstream iss( "{Delta Distribution, 3.000000000000000000e+00}" );
  
  Utility::UnitAwareDeltaDistribution<si::time,si::length> test_dist;

  iss >> test_dist;
  
  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  iss.str( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK( test_dist != (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );
  FRENSIE_CHECK_EQUAL( test_dist.getLowerBoundOfIndepVar(), 1.0*si::seconds );
  FRENSIE_CHECK_EQUAL( test_dist.evaluate( 1.0*si::seconds ), 0.5*si::meters );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree
FRENSIE_UNIT_TEST( DeltaDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *distribution );

  Utility::DeltaDistribution copy_dist =
    ptree.get<Utility::DeltaDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  ptree.put( "test distribution", *tab_distribution );

  copy_dist = ptree.get<Utility::DeltaDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::DeltaDistribution*>( tab_distribution.get() ) );

  ptree.clear();

  // Use the PropertyTreeCompatibleObject interface
  ptree = distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::DeltaDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  ptree = distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  Utility::DeltaDistribution test_dist( -1.0, 0.5 );

  ptree = test_dist.toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::DeltaDistribution>();

  FRENSIE_CHECK_EQUAL( copy_dist, test_dist );

  ptree = test_dist.toPropertyTree();
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 0.5 );

  // Use the PropertyTree helper methods
  ptree = Utility::toPropertyTree( *distribution, true );

  copy_dist = ptree.get_value<Utility::DeltaDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *tab_distribution, true );

  copy_dist = ptree.get_value<Utility::DeltaDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *tab_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *tab_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be written to a property tree node
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *unit_aware_distribution );

  Utility::UnitAwareDeltaDistribution<si::time,si::length> copy_dist =
    ptree.get<Utility::UnitAwareDeltaDistribution<si::time,si::length> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  ptree.put( "test distribution", *unit_aware_tab_distribution );

  copy_dist = ptree.get<Utility::UnitAwareDeltaDistribution<si::time,si::length> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_tab_distribution.get() )) );

  ptree.clear();
  
  // Use the PropertyTreeCompatibleObject interface
  ptree = unit_aware_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareDeltaDistribution<si::time,si::length> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  ptree = unit_aware_distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  Utility::UnitAwareDeltaDistribution<si::time,si::length>
    test_dist( -1.0*si::seconds, 0.5*si::meters );

  ptree = test_dist.toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareDeltaDistribution<si::time,si::length> >();

  FRENSIE_CHECK_EQUAL( copy_dist, test_dist );

  ptree = test_dist.toPropertyTree();
  
  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), -1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 0.5 );

  // Use the PropertyTree helper methods
  ptree = Utility::toPropertyTree( *unit_aware_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwareDeltaDistribution<si::time,si::length> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwareDeltaDistribution<si::time,si::length> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "location" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be read from a property tree node
FRENSIE_DATA_UNIT_TEST( DeltaDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );
  
  Utility::DeltaDistribution dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::DeltaDistribution, expected_dist );

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
    FETCH_FROM_TABLE( Utility::DeltaDistribution, expected_dist );

    FRENSIE_CHECK_NO_THROW(
                  dist = Utility::fromPropertyTree<Utility::DeltaDistribution>(
                                      test_dists_ptree->get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::fromPropertyTree<Utility::DeltaDistribution>(
                                    test_dists_ptree->get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be read from a property tree node
FRENSIE_DATA_UNIT_TEST( UnitAwareDeltaDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{
  typedef Utility::UnitAwareDeltaDistribution<si::time,si::length> DistributionType;
  
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
FRENSIE_UNIT_TEST( DeltaDistribution, archive )
{
  std::string archive_name( "test_delta_dist.h5a" );
  
  // Create and archive some delta distributions
  {
    Utility::DeltaDistribution delta_dist_a( 0.0, 1.0 );

    std::shared_ptr<Utility::OneDDistribution> delta_dist_b( new Utility::DeltaDistribution( 1.0, 2.0 ) );

    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "delta_dist_a", delta_dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "delta_dist_b", delta_dist_b ) );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );
  
  Utility::DeltaDistribution delta_dist_a;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "delta_dist_a", delta_dist_a ) );
  FRENSIE_CHECK_EQUAL( delta_dist_a.getUpperBoundOfIndepVar(), 0.0 );
  FRENSIE_CHECK_EQUAL( delta_dist_a.getLowerBoundOfIndepVar(), 0.0 );
  FRENSIE_CHECK_EQUAL( delta_dist_a.evaluate( 0.0 ), 1.0 );

  std::shared_ptr<Utility::OneDDistribution> delta_dist_b;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "delta_dist_b", delta_dist_b ) );
  FRENSIE_CHECK_EQUAL( delta_dist_b->getUpperBoundOfIndepVar(), 1.0 );
  FRENSIE_CHECK_EQUAL( delta_dist_b->getLowerBoundOfIndepVar(), 1.0 );
  FRENSIE_CHECK_EQUAL( delta_dist_b->evaluate( 1.0 ), 2.0 );  
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, archive )
{
  std::string archive_name( "test_unit_aware_delta_dist.h5a" );
  
  // Create and archive some delta distributions
  {
    Utility::UnitAwareDeltaDistribution<si::time,si::length>
      delta_dist_a( 0.0*si::seconds, 1.0*si::meters );

    std::shared_ptr<Utility::UnitAwareOneDDistribution<si::time,si::length> > delta_dist_b( new Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds, 2.0*si::meters ) );

    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "delta_dist_a", delta_dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "delta_dist_b", delta_dist_b ) );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );
  
  Utility::UnitAwareDeltaDistribution<si::time,si::length> delta_dist_a;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "delta_dist_a", delta_dist_a ) );
  FRENSIE_CHECK_EQUAL( delta_dist_a.getUpperBoundOfIndepVar(), 0.0*si::seconds );
  FRENSIE_CHECK_EQUAL( delta_dist_a.getLowerBoundOfIndepVar(), 0.0*si::seconds );
  FRENSIE_CHECK_EQUAL( delta_dist_a.evaluate( 0.0*si::seconds ), 1.0*si::meters );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<si::time,si::length> >
    delta_dist_b;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "delta_dist_b", delta_dist_b ) );
  FRENSIE_CHECK_EQUAL( delta_dist_b->getUpperBoundOfIndepVar(), 1.0*si::seconds );
  FRENSIE_CHECK_EQUAL( delta_dist_b->getLowerBoundOfIndepVar(), 1.0*si::seconds );
  FRENSIE_CHECK_EQUAL( delta_dist_b->evaluate( 1.0*si::seconds ), 2.0*si::meters );  
}

//---------------------------------------------------------------------------//
// Check that the distribution can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareDeltaDistribution,
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
  Utility::UnitAwareDeltaDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareDeltaDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareDeltaDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1.0 );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 1.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b =
    Utility::QuantityTraits<InverseIndepQuantityB>::initializeQuantity( 1.0 );
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
              boost::program_options::value<std::string>(&test_dists_json_file_name)->default_value( "" ),
              "Test distributions json file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Load the property tree from the json file
  test_dists_ptree.reset( new Utility::PropertyTree );

  std::ifstream test_dists_json_file( test_dists_json_file_name );

  test_dists_json_file >> *test_dists_ptree;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDeltaDistribution.cpp
//---------------------------------------------------------------------------//
