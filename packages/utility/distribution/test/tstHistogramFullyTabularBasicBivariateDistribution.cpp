//---------------------------------------------------------------------------//
//!
//! \file   tstHistogramFullyTabularBasicBivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The histogram fully tabular two-dimensional dist. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
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
std::shared_ptr<Utility::UnitAwareBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
  unit_aware_distribution;

std::shared_ptr<Utility::UnitAwareFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
  unit_aware_tab_distribution;

std::shared_ptr<Utility::BasicBivariateDistribution> distribution;

std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> tab_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution primary independent variable
// can be returned
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfPrimaryIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution primary
// independent variable can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfPrimaryIndepVar(), 2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution primary independent variable
// can be returned
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfPrimaryIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution primary
// independent variable can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfPrimaryIndepVar(), 0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   getUpperBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL(
                 distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
                 distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL(
                 distribution->getUpperBoundOfSecondaryConditionalIndepVar(0.0), 10.0 );


  // In the second bin
  FRENSIE_CHECK_EQUAL(
                 distribution->getUpperBoundOfSecondaryConditionalIndepVar(0.5), 10.0 );

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
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
                  distribution->getUpperBoundOfSecondaryConditionalIndepVar(3.0), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware conditional distribution
// independent variable can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   getUpperBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0*MeV), 0.0*cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0*MeV), 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(0.0*MeV), 10.0*cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(0.5*MeV), 10.0*cgs::centimeter );

  // On the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(1.0*MeV), 10.0*cgs::centimeter );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(1.5*MeV), 10.0*cgs::centimeter );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(2.0*MeV), 10.0*cgs::centimeter );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(3.0*MeV), 0.0*cgs::centimeter );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(3.0*MeV), 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   getLowerBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL(
                 distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
                 distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

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
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL(
                  distribution->getLowerBoundOfSecondaryConditionalIndepVar(3.0), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware conditional distribution
// independent variable can be returned
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   getLowerBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0*MeV), 0.0*cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0*MeV), 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(0.0*MeV), 0.0*cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(0.5*MeV), 0.0*cgs::centimeter );

  // On the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(1.0*MeV), 0.0*cgs::centimeter );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(1.5*MeV), 0.0*cgs::centimeter );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(2.0*MeV), 0.0*cgs::centimeter );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(3.0*MeV), 0.0*cgs::centimeter );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(3.0*MeV), 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   isPrimaryDimensionTabular )
{
  FRENSIE_CHECK( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   isPrimaryDimensionTabular )
{
  FRENSIE_CHECK( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous in the primary dimension
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   isPrimaryDimensionContinuous )
{
  FRENSIE_CHECK( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous in the primary dimension
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   isPrimaryDimensionContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution has the same bounds as another distribution
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   hasSamePrimaryBounds )
{
  std::shared_ptr<Utility::BasicBivariateDistribution> other_distribution;

  {
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 2 );

    primary_grid[0] = 0.0;
    secondary_dists[0].reset( new Utility::DeltaDistribution( 0.0 ) );

    primary_grid[1] = 2.0;
    secondary_dists[1].reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
                  new Utility::HistogramFullyTabularBasicBivariateDistribution(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 2 );

    primary_grid[0] = -1.0;
    secondary_dists[0].reset( new Utility::DeltaDistribution( 0.0 ) );

    primary_grid[1] = 2.0;
    secondary_dists[1].reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
                  new Utility::HistogramFullyTabularBasicBivariateDistribution(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 2 );

    primary_grid[0] = 0.0;
    secondary_dists[0].reset( new Utility::DeltaDistribution( 0.0 ) );

    primary_grid[1] = 3.0;
    secondary_dists[1].reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
                  new Utility::HistogramFullyTabularBasicBivariateDistribution(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 2 );

    primary_grid[0] = -1.0;
    secondary_dists[0].reset( new Utility::DeltaDistribution( 0.0 ) );

    primary_grid[1] = 3.0;
    secondary_dists[1].reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
                  new Utility::HistogramFullyTabularBasicBivariateDistribution(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *other_distribution ) );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution has the same bounds as another
// distribution
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   hasSamePrimaryBounds )
{
  std::shared_ptr<Utility::UnitAwareBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> > other_distribution;

  {
    std::vector<quantity<MegaElectronVolt> > primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 2 );

    primary_grid[0] = 0.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    primary_grid[1] = 2.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
                       new Utility::UnitAwareHistogramFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<quantity<MegaElectronVolt> > primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 2 );

    primary_grid[0] = -1.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    primary_grid[1] = 2.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
                       new Utility::UnitAwareHistogramFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<quantity<MegaElectronVolt> > primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 2 );

    primary_grid[0] = 0.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    primary_grid[1] = 3.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
                       new Utility::UnitAwareHistogramFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    std::vector<quantity<MegaElectronVolt> > primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 2 );

    primary_grid[0] = -1.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    primary_grid[1] = 3.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
                       new Utility::UnitAwareHistogramFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution, evaluate )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 1.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 0.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 1.0 ), 2.0 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5, 0.0 ), 2.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5, 1.0 ), 2.0 );

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
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 1.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution, evaluate )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 1.0*cgs::centimeter ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 1.0*cgs::centimeter ), 0.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 2.0*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 1.0*cgs::centimeter ), 2.0*barns );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5*MeV, 0.0*cgs::centimeter ), 2.0*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.5*MeV, 1.0*cgs::centimeter ), 2.0*barns );

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
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 1.0*cgs::centimeter ), 0.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 1.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 1.0 ), 0.1 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.5, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.5, 1.0 ), 0.1 );

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
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 1.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 1.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::centimeter ), 0.1/cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 1.0*cgs::centimeter ), 0.1/cgs::centimeter );

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
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::centimeter ), 1.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalCDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 1.0 ), 0.1 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.5, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.5, 1.0 ), 0.1 );

  // On the third bin
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 1.0 ), 0.1 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 1.0 ), 0.1 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 1.0 ), 0.1 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 1.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalCDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 1.0*cgs::centimeter ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 0.0*cgs::centimeter ), 1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 1.0*cgs::centimeter ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 1.0*cgs::centimeter ), 0.1 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.5*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.5*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.5*MeV, 1.0*cgs::centimeter ), 0.1 );

  // On the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 1.0*cgs::centimeter ), 0.1 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 1.0*cgs::centimeter ), 0.1 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 1.0*cgs::centimeter ), 0.1 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 1.0*cgs::centimeter ), 0.0 );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::centimeter ), 1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 1.0*cgs::centimeter ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( -1.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = distribution->sampleSecondaryConditional( -1.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // On the third bin
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
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = distribution->sampleSecondaryConditional( 3.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // On the third bin
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
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 7u );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 8u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 9u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 10u );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 11u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 12u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 13u );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 14u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 15u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 16u );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 17u );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 7u );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 8u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 9u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 10u );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 11u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 12u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 13u );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 14u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 15u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 16u );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 17u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices )
{
  size_t primary_bin_index = 0, secondary_bin_index = 0;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, primary_bin_index, secondary_bin_index ),
                       std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices )
{
  size_t primary_bin_index = 0u, secondary_bin_index = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw )
{
  size_t primary_bin_index = 0u, secondary_bin_index = 0u;
  double raw_sample;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw )
{
  size_t primary_bin_index = 0u, secondary_bin_index = 0u;
  quantity<cgs::length> raw_sample;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumber )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // In the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // On the third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // In the third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumber )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0*MeV, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // In the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // On the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // In the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalInSubrange )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( -1.0, 1.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalInSubrange( -1.0, 1.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-9 );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.5, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.5, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.5, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-9 );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-9 );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-9 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-9 );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 1.0 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 1.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalInSubrange )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( -1.0*MeV, 1.0*cgs::centimeter ),
              std::logic_error );

  // Before the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( -1.0*MeV, 1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-9 );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.5*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.5*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.5*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-9 );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-9 );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-9 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 5.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-9 );

  // After the third bin - no extension
  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 1.0*cgs::centimeter ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0, 0.0, 1.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0, 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-9 );

  // In the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5, 0.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5, 0.5, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5, 1.0-1e-15, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-9 );

  // On the third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.5, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-9 );

  // In the third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.5, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-9 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.5, 5.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-9 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 1.0 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 1.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0*MeV, 0.0, 1.0*cgs::centimeter ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0*MeV, 0.0, 1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin (first bin boundary = second bin boundary)
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 5.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-9 );

  // In the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5*MeV, 0.0, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5*MeV, 0.5, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5*MeV, 1.0-1e-15, 5.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-9 );

  // On the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.5, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 5.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-9 );

  // In the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.5, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 5.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-9 );

  // On the upper bin boundary - this should be treated as part of the third
  // bin (special case)
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.5, 5.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 5.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-9 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 1.0*cgs::centimeter ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( HistogramFullyTabularBasicBivariateDistribution,
                   ostream_operator )
{
  std::ostringstream oss;

  oss << *distribution;

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "HistogramFullyTabularBasicBivariateDistribution",
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
                       "Uniform Distribution",
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
FRENSIE_UNIT_TEST( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                   ostream_operator )
{
  std::ostringstream oss;

  oss << *unit_aware_distribution;

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "HistogramFullyTabularBasicBivariateDistribution",
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
                       "Uniform Distribution",
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
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( HistogramFullyTabularBasicBivariateDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_histogram_fully_tabular_basic_bivariate_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<Utility::HistogramFullyTabularBasicBivariateDistribution>
      concrete_distribution = std::dynamic_pointer_cast<Utility::HistogramFullyTabularBasicBivariateDistribution>( distribution );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( tab_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::HistogramFullyTabularBasicBivariateDistribution>
    concrete_distribution;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_distribution ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *concrete_distribution ),
                       Utility::toString( *distribution ),
                       SHOW_BOTH );

  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>
    local_tab_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "tab_distribution", local_tab_dist ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *local_tab_dist ),
                       Utility::toString( *tab_distribution ),
                       SHOW_BOTH );

  std::shared_ptr<Utility::BasicBivariateDistribution> local_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "distribution", local_dist ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *local_dist ),
                       Utility::toString( *distribution ),
                       SHOW_BOTH );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareHistogramFullyTabularBasicBivariateDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_unit_aware_histogram_fully_tabular_basic_bivariate_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<Utility::UnitAwareHistogramFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
      concrete_distribution = std::dynamic_pointer_cast<Utility::UnitAwareHistogramFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >( unit_aware_distribution );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "tab_distribution", unit_aware_tab_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "distribution", unit_aware_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::UnitAwareHistogramFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
    concrete_distribution;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_distribution ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *concrete_distribution ),
                       Utility::toString( *unit_aware_distribution ),
                       SHOW_BOTH );

  std::shared_ptr<Utility::UnitAwareFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
    local_tab_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "tab_distribution", local_tab_dist ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *local_tab_dist ),
                       Utility::toString( *unit_aware_tab_distribution ),
                       SHOW_BOTH );

  std::shared_ptr<Utility::UnitAwareBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> > local_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "distribution", local_dist ) );
  FRENSIE_CHECK_EQUAL( Utility::toString( *local_dist ),
                       Utility::toString( *unit_aware_distribution ),
                       SHOW_BOTH );
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
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 4 );

    // Create the secondary distribution in the first bin
    primary_grid[0] = 0.0;
    secondary_dists[0].reset( new Utility::DeltaDistribution( 0.0 ) );


    // Create the secondary distribution in the second bin
    primary_grid[1] = 0.0;
    secondary_dists[1].reset( new Utility::UniformDistribution( 0.0, 10.0, 2.0 ) );

    // Create the secondary distribution in the third bin
    primary_grid[2] = 1.0;
    secondary_dists[2].reset( new Utility::UniformDistribution( 0.0, 10.0, 1.0 ) );

    // Create the secondary distribution beyond the third bin
    primary_grid[3] = 2.0;
    secondary_dists[3] = secondary_dists[0];

    tab_distribution.reset( new Utility::HistogramFullyTabularBasicBivariateDistribution(
                                             primary_grid, secondary_dists ) );

    distribution = tab_distribution;
  }

  // Create the unit-aware two-dimensional distribution
  {
    std::vector<quantity<MegaElectronVolt> > primary_bins( 4 );

    std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 4 );

    // Create the secondary distribution in the first bin
    primary_bins[0] = 0.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    // Create the secondary distribution in the second bin
    primary_bins[1] = 0.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 2.0*barn ) );

    // Create the secondary distribution in the third bin
    primary_bins[2] = 1.0*MeV;
    secondary_dists[2].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 1.0*barn ) );

    // Create the secondary distribution beyond the third bin
    primary_bins[3] = 2.0*MeV;
    secondary_dists[3] = secondary_dists[0];

    unit_aware_tab_distribution.reset( new Utility::UnitAwareHistogramFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>( primary_bins, secondary_dists ) );

    unit_aware_distribution = unit_aware_tab_distribution;
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHistogramFullyTabularBasicBivariateDistribution.hpp
//---------------------------------------------------------------------------//
