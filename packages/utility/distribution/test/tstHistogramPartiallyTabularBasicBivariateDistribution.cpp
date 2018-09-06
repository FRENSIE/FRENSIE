//---------------------------------------------------------------------------//
//!
//! \file   tstHistogramPartiallyTabularBivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The histogram partially tabular two-dimensional dist. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_BarnUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
using Utility::Units::MegaElectronVolt;
using Utility::Units::MeV;
using Utility::Units::Barn;
using Utility::Units::barn;
using Utility::Units::barns;
namespace cgs = boost::units::cgs;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
  unit_aware_distribution;

std::shared_ptr<Utility::PartiallyTabularBasicBivariateDistribution> distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution primary independent variable
// can be returned
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfPrimaryIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution primary
// independent variable can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfPrimaryIndepVar(), 2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution primary independent variable
// can be returned
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfPrimaryIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution primary
// independent variable can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfPrimaryIndepVar(), 0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   getUpperBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL(
                 distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0), 0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0),
                       0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar(0.0),
                       std::numeric_limits<double>::infinity() );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar(0.5),
                       std::numeric_limits<double>::infinity() );

  // On the third bin
  FRENSIE_CHECK_EQUAL(
                 distribution->getUpperBoundOfSecondaryConditionalIndepVar(1.0), 10.0 );

  // In the third bin
  FRENSIE_CHECK_EQUAL(
                 distribution->getUpperBoundOfSecondaryConditionalIndepVar(1.5), 10.0 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL(
                 distribution->getUpperBoundOfSecondaryConditionalIndepVar(2.0), 10.0 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL(
                  distribution->getUpperBoundOfSecondaryConditionalIndepVar(3.0), 0.0 );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
                  distribution->getUpperBoundOfSecondaryConditionalIndepVar(3.0), 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware conditional distribution
// independent variable can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   getUpperBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0*MeV),
         0.0*cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0*MeV),
         0.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(0.0*MeV),
         std::numeric_limits<double>::infinity()*cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(0.5*MeV),
         std::numeric_limits<double>::infinity()*cgs::centimeter );

  // On the third bin
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(1.0*MeV),
         10.0*cgs::centimeter );

  // In the third bin
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(1.5*MeV),
         10.0*cgs::centimeter );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(2.0*MeV),
         10.0*cgs::centimeter );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(3.0*MeV),
         0.0*cgs::centimeter );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(3.0*MeV),
         0.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   getLowerBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL(
                 distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0), 0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
                 distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0), 0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL(
                  distribution->getLowerBoundOfSecondaryConditionalIndepVar(0.0), 0.0 );


  // In the second bin
  FRENSIE_CHECK_EQUAL(
                  distribution->getLowerBoundOfSecondaryConditionalIndepVar(0.5), 0.0 );

  // On the third bin
  FRENSIE_CHECK_EQUAL(
                  distribution->getLowerBoundOfSecondaryConditionalIndepVar(1.0), 0.0 );

  // In the third bin
  FRENSIE_CHECK_EQUAL(
                  distribution->getLowerBoundOfSecondaryConditionalIndepVar(1.5), 0.0 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL(
                  distribution->getLowerBoundOfSecondaryConditionalIndepVar(2.0), 0.0 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL(
                  distribution->getLowerBoundOfSecondaryConditionalIndepVar(3.0), 0.0 );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
                  distribution->getLowerBoundOfSecondaryConditionalIndepVar(3.0), 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware conditional distribution
// independent variable can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   getLowerBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0*MeV),
         0.0*cgs::centimeter );

  // Before the first bin - with extensino
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0*MeV),
         0.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(0.0*MeV),
         0.0*cgs::centimeter );


  // In the second bin
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(0.5*MeV),
         0.0*cgs::centimeter );

  // On the third bin
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(1.0*MeV),
         0.0*cgs::centimeter );

  // In the third bin
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(1.5*MeV),
         0.0*cgs::centimeter );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(2.0*MeV),
         0.0*cgs::centimeter );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(3.0*MeV),
         0.0*cgs::centimeter );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
         unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(2.0*MeV),
         0.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   isPrimaryDimensionTabular )
{
  FRENSIE_CHECK( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   isPrimaryDimensionTabular )
{
  FRENSIE_CHECK( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous in the primary dimension
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   isPrimaryDimensionContinuous )
{
  FRENSIE_CHECK( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous in the primary dimension
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   isPrimaryDimensionContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution has the same bounds as another distribution
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   hasSamePrimaryBounds )
{
  std::unique_ptr<Utility::BasicBivariateDistribution> other_distribution;

  {
    std::vector<double> primary_grid( {0.0, 2.0} );

    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 2 );

    secondary_dists[0].reset( new Utility::DeltaDistribution( 0.0 ) );
    secondary_dists[1].reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
             new Utility::HistogramPartiallyTabularBasicBivariateDistribution(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<double> primary_grid( {-1.0, 2.0} );

    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 2 );

    secondary_dists[0].reset( new Utility::DeltaDistribution( 0.0 ) );
    secondary_dists[1].reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
              new Utility::HistogramPartiallyTabularBasicBivariateDistribution(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<double> primary_grid( {0.0, 3.0} );

    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 2 );

    secondary_dists[0].reset( new Utility::DeltaDistribution( 0.0 ) );
    secondary_dists[1].reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
             new Utility::HistogramPartiallyTabularBasicBivariateDistribution(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<double> primary_grid( {-1.0, 3.0} );

    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 2 );

    secondary_dists[0].reset( new Utility::DeltaDistribution( 0.0 ) );
    secondary_dists[1].reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
              new Utility::HistogramPartiallyTabularBasicBivariateDistribution(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *other_distribution ) );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution has the same bounds as another
// distribution
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   hasSamePrimaryBounds )
{
  std::unique_ptr<Utility::UnitAwareBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> > other_distribution;

  {
    std::vector<quantity<MegaElectronVolt> >
      primary_grid( {0.0*MeV, 2.0*MeV} );

    std::vector<std::shared_ptr<const Utility::UnitAwareUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 2 );

    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );
    secondary_dists[1].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
          new Utility::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<quantity<MegaElectronVolt> >
      primary_grid( {-1.0*MeV, 2.0*MeV} );

    std::vector<std::shared_ptr<const Utility::UnitAwareUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 2 );

    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );
    secondary_dists[1].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
          new Utility::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<quantity<MegaElectronVolt> >
      primary_grid( {0.0*MeV, 3.0*MeV} );

    std::vector<std::shared_ptr<const Utility::UnitAwareUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 2 );

    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );
    secondary_dists[1].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
          new Utility::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<quantity<MegaElectronVolt> >
      primary_grid( {-1.0*MeV, 3.0*MeV} );

    std::vector<std::shared_ptr<const Utility::UnitAwareUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 2 );

    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );
    secondary_dists[1].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
          new Utility::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution, evaluate )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 1.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 1.0 ), exp( -1.0 ) );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5, 1.0 ), exp( -1.0 ) );

  // On the third bin
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 1.0 ), 1.0 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 1.0 ), 1.0 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 1.0 ), 1.0 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 1.0 ), 0.0 );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 1.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   evaluate )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 1.0*cgs::centimeter ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 1.0*cgs::centimeter ), 0.0*barn );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 1.0*cgs::centimeter ), exp( -1.0 )*barns );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5*MeV, 1.0*cgs::centimeter ), exp( -1.0 )*barns );

  // On the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 1.0*cgs::centimeter ), 1.0*barn );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 1.0*barn );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 1.0*cgs::centimeter ), 1.0*barn );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 1.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 1.0*cgs::centimeter ), 0.0*barn );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 1.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 1.0 ), exp( -1.0 ) );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.5, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.5, 1.0 ), exp( -1.0 ) );

  // On the third bin
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 1.0 ), 0.1 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.5, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.5, 1.0 ), 0.1 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.0, 1.0 ), 0.1 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 1.0 ), 0.0 );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 1.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 1.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::centimeter ), 1.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::centimeter ), exp( -1.0 )/cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 0.0*cgs::centimeter ), 1.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 1.0*cgs::centimeter ), exp( -1.0 )/cgs::centimeter );

  // On the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 1.0*cgs::centimeter ), 0.1/cgs::centimeter );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.0*cgs::centimeter ), 0.1/cgs::centimeter );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 1.0*cgs::centimeter ), 0.1/cgs::centimeter );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::centimeter ), 1.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( -1.0 ),
              std::logic_error );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  double sample = distribution->sampleSecondaryConditional( -1.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931471805599453, 1e-9 );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931471805599453, 1e-9 );

  // On the third bin
  fake_stream.push_back( 1.0 - 1e-15 );
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 2.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  sample = distribution->sampleSecondaryConditional( 3.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample = unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931471805599453*cgs::centimeter, 1e-9 );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931471805599453*cgs::centimeter, 1e-9 );

  // On the third bin
  fake_stream.push_back( 1.0 - 1e-15 );
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 0u );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  double sample = distribution->sampleSecondaryConditionalAndRecordTrials( -1.0 , trials );

  distribution->limitToPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931471805599453, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931471805599453, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  // On the third bin
  fake_stream.push_back( 1.0 - 1e-15 );
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 7u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 8u );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 9u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 10u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 11u );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 12u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 13u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 14u );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials ),
              std::logic_error );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 15u );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 0u );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931471805599453*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931471805599453*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  // On the third bin
  fake_stream.push_back( 1.0 - 1e-15 );
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 7u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 8u );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 9u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 10u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 11u );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 12u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 13u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 14u );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 15u );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( HistogramPartiallyTabularBasicBivariateDistribution,
                   ostream_operator )
{
  std::ostringstream oss;

  oss << *distribution;

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "HistogramPartiallyTabularBasicBivariateDistribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["primary independent unit"].toString(),
                       "void",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["secondary independent unit"].toString(),
                       "void",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       "void",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["primary grid"].toType<std::vector<double> >(),
                       std::vector<double>( {0.0, 0.0, 1.0, 2.0} ),
                       SHOW_LHS );

  Utility::VariantVector secondary_dists =
    dist_data["secondary dists"].toVector();

  FRENSIE_REQUIRE_EQUAL( secondary_dists.size(), 4, SHOW_LHS );

  Utility::VariantMap secondary_dist_data = secondary_dists[0].toMap();

  FRENSIE_CHECK_EQUAL( secondary_dist_data["type"].toString(),
                       "Delta Distribution",
                       SHOW_LHS );

  secondary_dist_data = secondary_dists[1].toMap();

  FRENSIE_CHECK_EQUAL( secondary_dist_data["type"].toString(),
                       "Exponential Distribution",
                       SHOW_LHS );

  secondary_dist_data = secondary_dists[2].toMap();

  FRENSIE_CHECK_EQUAL( secondary_dist_data["type"].toString(),
                       "Uniform Distribution",
                       SHOW_LHS );

  FRENSIE_CHECK_EQUAL( secondary_dists[0].toMap(),
                       secondary_dists[3].toMap(),
                       SHOW_BOTH );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                   ostream_operator )
{
  std::ostringstream oss;

  oss << *unit_aware_distribution;

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "HistogramPartiallyTabularBasicBivariateDistribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["primary independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["secondary independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<Barn>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["primary grid"].toType<std::vector<quantity<MegaElectronVolt> > >(),
                       std::vector<quantity<MegaElectronVolt> >( {0.0*MeV, 0.0*MeV, 1.0*MeV, 2.0*MeV} ),
                       SHOW_LHS );

  Utility::VariantVector secondary_dists =
    dist_data["secondary dists"].toVector();

  FRENSIE_REQUIRE_EQUAL( secondary_dists.size(), 4, SHOW_LHS );

  Utility::VariantMap secondary_dist_data = secondary_dists[0].toMap();

  FRENSIE_CHECK_EQUAL( secondary_dist_data["type"].toString(),
                       "Delta Distribution",
                       SHOW_LHS );

  secondary_dist_data = secondary_dists[1].toMap();

  FRENSIE_CHECK_EQUAL( secondary_dist_data["type"].toString(),
                       "Exponential Distribution",
                       SHOW_LHS );

  secondary_dist_data = secondary_dists[2].toMap();

  FRENSIE_CHECK_EQUAL( secondary_dist_data["type"].toString(),
                       "Uniform Distribution",
                       SHOW_LHS );

  FRENSIE_CHECK_EQUAL( secondary_dists[0].toMap(),
                       secondary_dists[3].toMap(),
                       SHOW_BOTH );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( HistogramPartiallyTabularBasicBivariateDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_histogram_partially_tabular_basic_bivariate_dist" );
  std::ostringstream archive_ostream;

  std::string test_dist_string;

  // Create and archive some distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::vector<double> primary_grid( {-1.0, 1.0} );
    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 2 );

    secondary_dists[0].reset( new Utility::DeltaDistribution( -1.0 ) );
    secondary_dists[1].reset( new Utility::DeltaDistribution( 1.0 ) );

    std::shared_ptr<Utility::HistogramPartiallyTabularBasicBivariateDistribution>
      concrete_dist( new Utility::HistogramPartiallyTabularBasicBivariateDistribution( primary_grid, secondary_dists ) );

    test_dist_string = Utility::toString( *concrete_dist );

    std::shared_ptr<Utility::BasicBivariateDistribution>
      basic_dist( concrete_dist );

    std::shared_ptr<Utility::PartiallyTabularBasicBivariateDistribution>
      partially_tabular_dist( concrete_dist );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( basic_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( partially_tabular_dist ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::HistogramPartiallyTabularBasicBivariateDistribution> concrete_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_dist ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *concrete_dist ),
                       test_dist_string,
                       SHOW_LHS );

  std::shared_ptr<Utility::BasicBivariateDistribution> basic_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( basic_dist ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *basic_dist ),
                       test_dist_string,
                       SHOW_LHS );

  std::shared_ptr<Utility::PartiallyTabularBasicBivariateDistribution> partially_tabular_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( partially_tabular_dist ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *partially_tabular_dist ),
                       test_dist_string,
                       SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_unit_aware_histogram_partially_tabular_basic_bivariate_dist" );
  std::ostringstream archive_ostream;

  std::string test_dist_string;

  // Create and archive some distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::vector<quantity<MegaElectronVolt> > primary_grid( {0.0*MeV, 1.0*MeV} );
    std::vector<std::shared_ptr<const Utility::UnitAwareUnivariateDistribution<cgs::length,Barn> > >
      secondary_dists( 2 );

    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( -1.0*cgs::centimeter ) );
    secondary_dists[1].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    std::shared_ptr<Utility::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
      concrete_dist( new Utility::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>( primary_grid, secondary_dists ) );

    test_dist_string = Utility::toString( *concrete_dist );

    std::shared_ptr<Utility::UnitAwareBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
      basic_dist( concrete_dist );

    std::shared_ptr<Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
      partially_tabular_dist( concrete_dist );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( basic_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( partially_tabular_dist ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> > concrete_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_dist ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *concrete_dist ),
                       test_dist_string,
                       SHOW_LHS );

  std::shared_ptr<Utility::UnitAwareBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> > basic_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( basic_dist ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *basic_dist ),
                       test_dist_string,
                       SHOW_LHS );

  std::shared_ptr<Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> > partially_tabular_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( partially_tabular_dist ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *partially_tabular_dist ),
                       test_dist_string,
                       SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the two-dimensional distribution
  {
    std::vector<double> primary_grid( 4 );
    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 4 );

    // Create the secondary distribution in the first bin
    primary_grid[0] = 0.0;
    secondary_dists[0].reset( new Utility::DeltaDistribution( 0.0 ) );

    // Create the secondary distribution in the second bin
    primary_grid[1] = 0.0;
    secondary_dists[1].reset( new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    // Create the secondary distribution in the third bin
    primary_grid[2] = 1.0;
    secondary_dists[2].reset( new Utility::UniformDistribution( 0.0, 10.0, 1.0 ) );
    // Create the secondary distribution beyond the third bin
    primary_grid[3] = 2.0;
    secondary_dists[3] = secondary_dists[0];

    distribution.reset(
              new Utility::HistogramPartiallyTabularBasicBivariateDistribution(
                                                           primary_grid,
                                                           secondary_dists ) );
  }

  // Create the unit-aware two-dimensional distribution
  {
    std::vector<quantity<MegaElectronVolt> > primary_bins( 4 );

    std::vector<std::shared_ptr<const Utility::UnitAwareUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 4 );

    // Create the secondary distribution in the first bin
    primary_bins[0] = 0.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    // Create the secondary distribution in the second bin
    primary_bins[1] = 0.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareExponentialDistribution<cgs::length,Barn>( 1.0*barn, 1.0/cgs::centimeter ) );

    // Create the secondary distribution in the third bin
    primary_bins[2] = 1.0*MeV;
    secondary_dists[2].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 1.0*barn ) );

    // Create the secondary distribution beyond the third bin
    primary_bins[3] = 2.0*MeV;
    secondary_dists[3] = secondary_dists[0];

    unit_aware_distribution.reset( new Utility::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>( primary_bins, secondary_dists ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHistogramPartiallyTabularBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
