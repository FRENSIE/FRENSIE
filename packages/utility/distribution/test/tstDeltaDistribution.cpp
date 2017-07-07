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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
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

std::shared_ptr<Utility::TabularOneDDistribution>
  tab_distribution( new Utility::DeltaDistribution( 0.0 ) );

std::shared_ptr<Utility::OneDDistribution>
  distribution( tab_distribution );

std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<si::time,si::length> >
  unit_aware_tab_distribution( new Utility::UnitAwareDeltaDistribution<si::time,si::length>( 3.0*si::seconds ) );

std::shared_ptr<Utility::UnitAwareOneDDistribution<si::time,si::length> >
  unit_aware_distribution( unit_aware_tab_distribution );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( DeltaDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*si::seconds ),
		       0.0*si::meters );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*si::seconds ),
		       1.0*si::meters );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 6.0*si::seconds ),
		       0.0*si::meters );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( DeltaDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*si::seconds ),
		       0.0/si::seconds );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 3.0*si::seconds ),
		       1.0/si::seconds );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 6.0*si::seconds ),
		       0.0/si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( DeltaDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 1.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST(
		   unit_aware_tab_distribution->evaluateCDF( 0.0*si::seconds ),
		   0.0 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_distribution->evaluateCDF( 3.0*si::seconds ),
		   1.0 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_distribution->evaluateCDF( 6.0*si::seconds ),
		   1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sample )
{
  TEST_EQUALITY_CONST( distribution->sample(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sample )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->sample(), 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0;
  double sample = distribution->sampleAndRecordTrials( trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0;

  quantity<si::time> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
  TEST_EQUALITY_CONST( trials, 1 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleAndRecordBinIndex )
{
  unsigned bin_index = 0;
  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleAndRecordBinIndex )
{
  unsigned bin_index = 0;

  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
  TEST_EQUALITY_CONST( bin_index, 0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleWithRandomNumber )
{
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleWithRandomNumber )
{
  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.5 );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleInSubrange )
{
  double sample = tab_distribution->sampleInSubrange( 1.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleInSubrange( 0.1 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleInSubrange )
{
  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleInSubrange( 4.0*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleInSubrange( 3.1*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleWithRandomNumberInSubrange )
{
  double sample =
    tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 1.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 2.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution,
		   sampleWithRandomNumberInSubrange )
{
  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 4.0*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 3.1*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can
// be returned
TEUCHOS_UNIT_TEST( DeltaDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can
// be returned
TEUCHOS_UNIT_TEST( DeltaDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( DeltaDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::DELTA_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::DELTA_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( DeltaDistribution, isTabular )
{
  TEST_ASSERT( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, isTabular )
{
  TEST_ASSERT( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( DeltaDistribution, isContinuous )
{
  TEST_ASSERT( !distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, isContinuous )
{
  TEST_ASSERT( !unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( DeltaDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
TEUCHOS_UNIT_TEST( DeltaDistribution, toString )
{
  std::string dist_string = Utility::toString( *distribution );

  TEST_EQUALITY_CONST( dist_string, "{Delta Distribution, 0.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::DeltaDistribution( 1.0, 0.5 ) );

  TEST_EQUALITY_CONST( dist_string, "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be converted to a string
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, toString )
{
  std::string dist_string = Utility::toString( *unit_aware_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Delta Distribution, 3.000000000000000000e+00}" );
  dist_string = Utility::toString( Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds, 0.5*si::meters ) );

  TEST_EQUALITY_CONST( dist_string, "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
TEUCHOS_UNIT_TEST( DeltaDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Delta Distribution, 0.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::DeltaDistribution( 1.0, 0.5 ) );

  TEST_EQUALITY_CONST( oss.str(), "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *unit_aware_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Delta Distribution, 3.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds, 0.5*si::meters ) );

  TEST_EQUALITY_CONST( oss.str(), "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
TEUCHOS_UNIT_TEST( DeltaDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Delta Distribution, 0.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::DeltaDistribution( 1.0, 0.5 );

  TEST_EQUALITY_CONST( oss.str(), "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *unit_aware_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Delta Distribution, 3.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareDeltaDistribution<si::time,si::length>( 1.0*si::seconds, 0.5*si::meters );

  TEST_EQUALITY_CONST( oss.str(), "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a string
TEUCHOS_UNIT_TEST( DeltaDistribution, fromString )
{
  Utility::DeltaDistribution test_dist =
    Utility::fromString<Utility::DeltaDistribution>( "{Delta Distribution, 0.000000000000000000e+00}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  test_dist = Utility::fromString<Utility::DeltaDistribution>( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );

  TEST_ASSERT( test_dist != *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist.getLowerBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( test_dist.evaluate( 1.0 ), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialize from a string
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, fromString )
{
  Utility::UnitAwareDeltaDistribution<si::time,si::length> test_dist =
    Utility::fromString<Utility::UnitAwareDeltaDistribution<si::time,si::length> >( "{Delta Distribution, 3.000000000000000000e+00}" );

  TEST_EQUALITY_CONST( test_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  test_dist = Utility::fromString<Utility::UnitAwareDeltaDistribution<si::time,si::length> >( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );

  TEST_ASSERT( test_dist != (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );
  TEST_EQUALITY_CONST( test_dist.getLowerBoundOfIndepVar(), 1.0*si::seconds );
  TEST_EQUALITY_CONST( test_dist.evaluate( 1.0*si::seconds ), 0.5*si::meters );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( DeltaDistribution, fromStream )
{
  std::istringstream iss( "{Delta Distribution, 0.000000000000000000e+00}" );

  Utility::DeltaDistribution test_dist;

  Utility::fromStream( iss, test_dist );
  
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  iss.str( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  TEST_ASSERT( test_dist != *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist.getLowerBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( test_dist.evaluate( 1.0 ), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, fromStream )
{
  std::istringstream iss( "{Delta Distribution, 3.000000000000000000e+00}" );
  
  Utility::UnitAwareDeltaDistribution<si::time,si::length> test_dist;

  Utility::fromStream( iss, test_dist );
  
  TEST_EQUALITY_CONST( test_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  iss.str( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  TEST_ASSERT( test_dist != (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );
  TEST_EQUALITY_CONST( test_dist.getLowerBoundOfIndepVar(), 1.0*si::seconds );
  TEST_EQUALITY_CONST( test_dist.evaluate( 1.0*si::seconds ), 0.5*si::meters );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( DeltaDistribution, istream_operator )
{
  std::istringstream iss( "{Delta Distribution, 0.000000000000000000e+00}" );

  Utility::DeltaDistribution test_dist;

  iss >> test_dist;
  
  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  iss.str( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
  iss.clear();

  iss >> test_dist;

  TEST_ASSERT( test_dist != *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );
  TEST_EQUALITY_CONST( test_dist.getLowerBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( test_dist.evaluate( 1.0 ), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, istream_operator )
{
  std::istringstream iss( "{Delta Distribution, 3.000000000000000000e+00}" );
  
  Utility::UnitAwareDeltaDistribution<si::time,si::length> test_dist;

  iss >> test_dist;
  
  TEST_EQUALITY_CONST( test_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  iss.str( "{Delta Distribution, 1.000000000000000000e+00, 5.000000000000000000e-01}" );
  iss.clear();

  iss >> test_dist;

  TEST_ASSERT( test_dist != (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );
  TEST_EQUALITY_CONST( test_dist.getLowerBoundOfIndepVar(), 1.0*si::seconds );
  TEST_EQUALITY_CONST( test_dist.evaluate( 1.0*si::seconds ), 0.5*si::meters );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree node
TEUCHOS_UNIT_TEST( DeltaDistribution, toNode )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *distribution );

  Utility::DeltaDistribution copy_dist =
    ptree.get<Utility::DeltaDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  ptree.put( "test distribution", *tab_distribution );

  copy_dist = ptree.get<Utility::DeltaDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::DeltaDistribution*>( tab_distribution.get() ) );

  // Use the PropertyTreeCompatibleObject interface
  distribution->toNode( "test distribution", ptree, true );

  TEST_EQUALITY_CONST( ptree.get_child( "test distribution" ).size(), 0 );

  copy_dist = ptree.get<Utility::DeltaDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::DeltaDistribution*>( distribution.get() ) );

  distribution->toNode( "test distribution", ptree, false );

  TEST_EQUALITY_CONST( ptree.get_child("test distribution").size(), 2 );
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").get<std::string>( "type" ), "Delta Distribution" );
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").get<double>( "location" ), 0.0 );

  Utility::DeltaDistribution test_dist( -1.0, 0.5 );

  test_dist.toNode( "test distribution", ptree, true );

  copy_dist = ptree.get<Utility::DeltaDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, test_dist );

  test_dist.toNode( "test distribution", ptree, false );
  
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").size(), 3 );
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").get<std::string>( "type" ), "Delta Distribution" );
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").get<double>( "location" ), -1.0 );
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").get<double>( "multiplier" ), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be written to a property tree node
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, toNode )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *unit_aware_distribution );

  Utility::UnitAwareDeltaDistribution<si::time,si::length> copy_dist =
    ptree.get<Utility::UnitAwareDeltaDistribution<si::time,si::length> >( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  ptree.put( "test distribution", *unit_aware_tab_distribution );

  copy_dist = ptree.get<Utility::UnitAwareDeltaDistribution<si::time,si::length> >( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_tab_distribution.get() )) );

  // Use the PropertyTreeCompatibleObject interface
  unit_aware_distribution->toNode( "test distribution", ptree, true );

  TEST_EQUALITY_CONST( ptree.get_child( "test distribution" ).size(), 0 );

  copy_dist = ptree.get<Utility::UnitAwareDeltaDistribution<si::time,si::length> >( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, (*dynamic_cast<Utility::UnitAwareDeltaDistribution<si::time,si::length>*>( unit_aware_distribution.get() )) );

  unit_aware_distribution->toNode( "test distribution", ptree, false );

  TEST_EQUALITY_CONST( ptree.get_child("test distribution").size(), 2 );
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").get<std::string>( "type" ), "Delta Distribution" );
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").get<double>( "location" ), 3.0 );

  Utility::UnitAwareDeltaDistribution<si::time,si::length>
    test_dist( -1.0*si::seconds, 0.5*si::meters );

  test_dist.toNode( "test distribution", ptree, true );

  copy_dist = ptree.get<Utility::UnitAwareDeltaDistribution<si::time,si::length> >( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, test_dist );

  test_dist.toNode( "test distribution", ptree, false );
  
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").size(), 3 );
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").get<std::string>( "type" ), "Delta Distribution" );
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").get<double>( "location" ), -1.0 );
  TEST_EQUALITY_CONST( ptree.get_child("test distribution").get<double>( "multiplier" ), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be read from a property tree node
TEUCHOS_UNIT_TEST( DeltaDistribution, fromNode )
{
  Utility::DeltaDistribution dist;

  std::vector<std::string> unused_children;

  dist.fromNode( test_dists_ptree->get_child( "Delta Distribution A" ),
                 unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.evaluate( 0.0 ), 2.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromNode( test_dists_ptree->get_child( "Delta Distribution B" ),
                 unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( dist.evaluate( Utility::PhysicalConstants::pi ), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromNode( test_dists_ptree->get_child( "Delta Distribution C" ),
                 unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( dist.evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromNode( test_dists_ptree->get_child( "Delta Distribution D" ),
                 unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       -2*Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( dist.evaluate( -2*Utility::PhysicalConstants::pi ),
                       0.5 );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Delta Distribution E" ) ),
              std::runtime_error );
  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Delta Distribution F" ) ),
              std::runtime_error );
  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Delta Distribution G" ) ),
              std::runtime_error );
  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Delta Distribution H" ) ),
              std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be read from a property tree node
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, fromNode )
{
  Utility::UnitAwareDeltaDistribution<si::time,si::length> dist;

  std::vector<std::string> unused_children;

  dist.fromNode( test_dists_ptree->get_child( "Delta Distribution A" ),
                 unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*si::seconds );
  TEST_EQUALITY_CONST( dist.evaluate( 0.0*si::seconds ), 2.0*si::meters );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromNode( test_dists_ptree->get_child( "Delta Distribution B" ),
                 unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi*si::seconds );
  TEST_EQUALITY_CONST( dist.evaluate( Utility::PhysicalConstants::pi*si::seconds ), 1.0*si::meters );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromNode( test_dists_ptree->get_child( "Delta Distribution C" ),
                 unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), -1.0*si::seconds );
  TEST_EQUALITY_CONST( dist.evaluate( -1.0*si::seconds ), 1.0*si::meters );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromNode( test_dists_ptree->get_child( "Delta Distribution D" ),
                 unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(),
                       -2*Utility::PhysicalConstants::pi*si::seconds );
  TEST_EQUALITY_CONST( dist.evaluate( -2*Utility::PhysicalConstants::pi*si::seconds ), 0.5*si::meters );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Delta Distribution E" ) ),
              std::runtime_error );
  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Delta Distribution F" ) ),
              std::runtime_error );
  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Delta Distribution G" ) ),
              std::runtime_error );
  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Delta Distribution H" ) ),
              std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareDeltaDistribution,
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

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
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
                   "Test distributions xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Load the property tree from the json file
  test_dists_ptree.reset( new Utility::PropertyTree );

  std::ifstream test_dists_json_file( test_dists_json_file_name );

  test_dists_json_file >> *test_dists_ptree;
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDeltaDistribution.cpp
//---------------------------------------------------------------------------//
