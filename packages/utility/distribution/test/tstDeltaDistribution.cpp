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
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
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

std::shared_ptr<Utility::TabularUnivariateDistribution>
  tab_distribution( new Utility::DeltaDistribution );

std::shared_ptr<Utility::UnivariateDistribution>
  distribution( tab_distribution );

std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<si::time,si::length> >
  unit_aware_tab_distribution( new Utility::UnitAwareDeltaDistribution<si::time,si::length>( 3.0*si::seconds ) );

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<si::time,si::length> >
  unit_aware_distribution( unit_aware_tab_distribution );

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
  size_t bin_index = 0;
  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( bin_index, 0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, sampleAndRecordBinIndex )
{
  size_t bin_index = 0;

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
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( DeltaDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::DeltaDistribution();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["location"].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0 );

  oss.str( "" );
  oss.clear();

  oss << Utility::DeltaDistribution( 1.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["location"].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0 );

  oss.str( "" );
  oss.clear();

  oss << Utility::DeltaDistribution( 1.0, 2.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["location"].toDouble(), 1.0 );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 2.0 );

  oss.str( "" );
  oss.clear();

  oss << *distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void" );
  FRENSIE_CHECK_EQUAL( dist_data["location"].toDouble(), 0.0 );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareDeltaDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::UnitAwareDeltaDistribution<si::time,si::length>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<si::time>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::length>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["location"].toType<quantity<si::time> >(),
                       0.0*si::seconds );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::length> >(),
                       1.0*si::meter );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<si::time>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::length>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["location"].toType<quantity<si::time> >(),
                       1.0*si::second );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::length> >(),
                       1.0*si::meter );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds, 2.0*si::meters );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<si::time>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::length>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["location"].toType<quantity<si::time> >(),
                       1.0*si::second );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::length> >(),
                       2.0*si::meters );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(), "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<si::time>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::length>::name() );
  FRENSIE_CHECK_EQUAL( dist_data["location"].toType<quantity<si::time> >(),
                       3.0*si::seconds );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toType<quantity<si::length> >(),
                       1.0*si::meter );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DeltaDistribution, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_delta_dist" );
  std::ostringstream archive_ostream;
  
  // Create and archive some delta distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
                    
    Utility::DeltaDistribution delta_dist_a( 0.0, 1.0 );

    std::shared_ptr<Utility::UnivariateDistribution> delta_dist_b( new Utility::DeltaDistribution( 1.0, 2.0 ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "delta_dist_a", delta_dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "delta_dist_b", delta_dist_b ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );
  
  Utility::DeltaDistribution delta_dist_a;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "delta_dist_a", delta_dist_a ) );
  FRENSIE_CHECK_EQUAL( delta_dist_a.getUpperBoundOfIndepVar(), 0.0 );
  FRENSIE_CHECK_EQUAL( delta_dist_a.getLowerBoundOfIndepVar(), 0.0 );
  FRENSIE_CHECK_EQUAL( delta_dist_a.evaluate( 0.0 ), 1.0 );

  std::shared_ptr<Utility::UnivariateDistribution> delta_dist_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "delta_dist_b", delta_dist_b ) );
  FRENSIE_CHECK_EQUAL( delta_dist_b->getUpperBoundOfIndepVar(), 1.0 );
  FRENSIE_CHECK_EQUAL( delta_dist_b->getLowerBoundOfIndepVar(), 1.0 );
  FRENSIE_CHECK_EQUAL( delta_dist_b->evaluate( 1.0 ), 2.0 );  
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareDeltaDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_unit_aware_delta_dist" );
  std::ostringstream archive_ostream;
  
  // Create and archive some delta distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::UnitAwareDeltaDistribution<si::time,si::length>
      delta_dist_a( 0.0*si::seconds, 1.0*si::meters );

    std::shared_ptr<Utility::UnitAwareUnivariateDistribution<si::time,si::length> > delta_dist_b( new Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds, 2.0*si::meters ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "delta_dist_a", delta_dist_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "delta_dist_b", delta_dist_b ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );
  
  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );
  
  Utility::UnitAwareDeltaDistribution<si::time,si::length> delta_dist_a;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "delta_dist_a", delta_dist_a ) );
  FRENSIE_CHECK_EQUAL( delta_dist_a.getUpperBoundOfIndepVar(), 0.0*si::seconds );
  FRENSIE_CHECK_EQUAL( delta_dist_a.getLowerBoundOfIndepVar(), 0.0*si::seconds );
  FRENSIE_CHECK_EQUAL( delta_dist_a.evaluate( 0.0*si::seconds ), 1.0*si::meters );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<si::time,si::length> >
    delta_dist_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "delta_dist_b", delta_dist_b ) );
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
// end tstDeltaDistribution.cpp
//---------------------------------------------------------------------------//
