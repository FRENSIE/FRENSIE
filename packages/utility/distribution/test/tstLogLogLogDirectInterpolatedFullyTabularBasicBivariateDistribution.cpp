//---------------------------------------------------------------------------//
//!
//! \file   tstLogLogLogDirectInterpolatedFullyTabularBasicBivariateDistribution.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The interpolated fully tabular two-dimensional dist. unit tests
//!         (LogLogLog Direct interpolation)
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Boost Includes
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"
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

using UnitAwareDist = Utility::UnitAwareBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>;
using UnitAwareTabDist = Utility::UnitAwareFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn>;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<UnitAwareDist> unit_aware_distribution;
std::shared_ptr<UnitAwareTabDist> unit_aware_tab_distribution;

std::shared_ptr<Utility::BasicBivariateDistribution> distribution;
std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> tab_distribution;

std::function<double (double)> lower_func, upper_func;
std::function<quantity<cgs::length>(UnitAwareDist::PrimaryIndepQuantity)>
ua_lower_func, ua_upper_func;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   isPrimaryDimensionTabular )
{
  FRENSIE_CHECK( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   isPrimaryDimensionTabular )
{
  FRENSIE_CHECK( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous in the primary dimension
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   isPrimaryDimensionContinuous )
{
  FRENSIE_CHECK( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous in the primary
// dimension
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   isPrimaryDimensionContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary lower bound can be returned
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfPrimaryIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary lower bound can be
// returned
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfPrimaryIndepVar(), 1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary dimension upper bound can be returned
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfPrimaryIndepVar(), 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary dimension upper bound can
// be returned
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfPrimaryIndepVar(), 3.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional distribution can be returned
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   getLowerBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0),
                       0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0),
                       0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.0 ),
                       0.0 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.5 ),
                       0.0 );

  // On the third bin
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 2.0 ),
                       2.5 );

  // On the fourth bin
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 2.5 ),
                       0.0 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the third bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 4.0 ),
                       0.0 );

  // Beyond the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 4.0 ),
                       0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional unit-aware distribution can be
// returned
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   getLowerBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0*MeV),
                       0.0*cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0*MeV),
                       0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.0*MeV ),
                       0.0*cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.5*MeV ),
                       0.0*cgs::centimeter );

  // On the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 2.0*MeV ),
                       2.5*cgs::centimeter );

  // On the fourth bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 2.5*MeV ),
                       0.0*cgs::centimeter );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 4.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 4.0*MeV ),
                       0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional distribution can be returned
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   getUpperBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0),
                       0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0),
                       10.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.0 ),
                       10.0 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.5 ),
                       10.0 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 2.0 ),
                       7.5 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 2.5 ),
                       10.0 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 3.0 ),
                       10.0 );

  // Beyond the third bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 4.0 ),
                       0.0 );

  // Beyond the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 4.0 ),
                       10.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional unit-aware distribution can be
// returned
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   getUpperBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0*MeV),
                       0.0*cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0*MeV),
                       10.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.0*MeV ),
                       10.0*cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.5*MeV ),
                       10.0*cgs::centimeter );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 2.0*MeV ),
                       7.5*cgs::centimeter );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 2.5*MeV ),
                       10.0*cgs::centimeter );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 3.0*MeV ),
                       10.0*cgs::centimeter );

  // Beyond the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 4.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 4.0*MeV ),
                       10.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the bounds of two distribution can be compared
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   hasSamePrimaryBounds )
{
  // Self test
  FRENSIE_CHECK( distribution->hasSamePrimaryBounds( *distribution ) );

  // Create a test distribution with same lower bound, different upper bound
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> test_dist;

  {
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 2 );

    // Create the secondary distribution in the first bin
    primary_grid[0] = 0.0;
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );

    // Create the secondary distribution in the second bin
    primary_grid[1] = 3.0;
    secondary_dists[1] = secondary_dists[0];

    test_dist.reset( new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Direct<Utility::LogLogLog> >(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *test_dist ) );

  // Create a test distribution with different lower bound, same upper bound
  {
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 2 );

    // Create the secondary distribution in the first bin
    primary_grid[0] = 1.5;
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );

    // Create the secondary distribution in the second bin
    primary_grid[1] = 2.5;
    secondary_dists[1] = secondary_dists[0];

    test_dist.reset( new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Direct<Utility::LogLogLog> >(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *test_dist ) );

  // Create a test distribution with different bounds
  {
    std::vector<double> primary_grid( 4 );
    primary_grid[0] = 0.5;
    primary_grid[1] = 1.0;
    primary_grid[2] = 1.0;
    primary_grid[3] = 1.5;

    std::vector<std::vector<double> > secondary_grids( 4 ), values( 4 );
    secondary_grids[0].resize( 2 ); values[0].resize( 2 );
    secondary_grids[0][0] = 0.1;    values[0][0] = 0.1;
    secondary_grids[0][1] = 10.0;   values[0][1] = 0.1;

    secondary_grids[1].resize( 3 ); values[1].resize( 3 );
    secondary_grids[1][0] = 2.5;    values[1][0] = 0.1;
    secondary_grids[1][1] = 5.0;    values[1][1] = 1.0;
    secondary_grids[1][2] = 7.5;    values[1][2] = 0.5;

    secondary_grids[2].resize( 2 ); values[2].resize( 2 );
    secondary_grids[2][0] = 2.5;    values[2][0] = 0.5;
    secondary_grids[2][1] = 7.5;    values[2][1] = 0.5;

    secondary_grids[3] = secondary_grids[0];
    values[3] = values[0];

    test_dist.reset( new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Direct<Utility::LogLogLog> >(
                                                               primary_grid,
                                                               secondary_grids,
                                                               values ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *test_dist ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution, evaluate )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 5.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 10.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 11.0 ), 0.0 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 1.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 1.25 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 1.5, 5.0 ),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 8.75 ), 0.5 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 9.0 ), 0.5 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 2.5 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 7.5 ), 0.5 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 8.0 ), 0.0 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.5, 1.25 ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 2.5, 5.0 ),
                          2.81617920177974E-01,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.5, 8.75 ), 0.05 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.5, 9.0 ), 0.05 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 11.0 ), 0.0 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0, 5.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0, 10.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 4.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   evaluate )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 10.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 1.25*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 5.0*cgs::centimeter ),
                                  1.0*barn,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 8.75*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.5*barn );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 2.5*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 7.5*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.5*MeV, 1.0*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.5*MeV, 1.25*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 2.5*MeV, 5.0*cgs::centimeter ),
                                  2.81617920177974E-01*barn,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.5*MeV, 8.75*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.5*MeV, 9.0*cgs::centimeter ), 0.05*barn );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 4.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 4.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 4.0*MeV, 5.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 4.0*MeV, 10.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 4.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 4.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 4.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 4.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 4.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 4.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 5.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 10.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 11.0 ), 0.0 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.5, 1.25 ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.5, 5.0 ),
                          1.92987833095478E-01,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.5, 8.75 ), 0.05 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.5, 9.0 ), 0.05 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 2.0, 2.5 ),
                          0.03076923076923077,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 2.0, 5.0 ),
                          0.3076923076923077,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 2.0, 7.5 ),
                          0.15384615384615385,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.0, 8.0 ), 0.0 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.5, 2.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.5, 1.25 ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 2.5, 5.0 ),
                          1.65762644971536E-01,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.5, 8.75 ), 0.05 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.5, 9.0 ), 0.05 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 11.0 ), 0.0 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 4.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 4.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 4.0, 5.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 4.0, 10.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 4.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 4.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 4.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 4.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 4.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 4.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 5.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.0*cgs::centimeter ), 0.05/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.25*cgs::centimeter ), 0.05/cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 5.0*cgs::centimeter ),
                                  1.92987833095478E-01/cgs::centimeter,
                                  1e-12 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 8.75*cgs::centimeter ), 0.05/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 9.0*cgs::centimeter ), 0.05/cgs::centimeter );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 2.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 2.5*cgs::centimeter ),
                                  0.03076923076923077/cgs::centimeter,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 5.0*cgs::centimeter ),
                                  0.3076923076923077/cgs::centimeter,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 7.5*cgs::centimeter ),
                                  0.15384615384615385/cgs::centimeter,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 8.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.5*MeV, 2.0*cgs::centimeter ), 0.05/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.5*MeV, 1.25*cgs::centimeter ), 0.05/cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.5*MeV, 5.0*cgs::centimeter ),
                                  1.65762644971536E-01/cgs::centimeter,
                                  1e-12 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.5*MeV, 8.75*cgs::centimeter ), 0.05/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.5*MeV, 9.0*cgs::centimeter ), 0.05/cgs::centimeter );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 4.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 4.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 4.0*MeV, 5.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 4.0*MeV, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 4.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 4.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 4.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 4.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 4.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 4.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalCDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 5.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 10.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 5.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 11.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 5.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 11.0 ), 1.0 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 1.25 ), 0.0625 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 5.0 ),
                          4.534512303966930E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 8.75 ),
                          9.46087201247317822e-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 9.0 ),
                          9.57213743582549070e-01,
                          1e-15 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 2.5 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 5.0 ),
                          0.4230769230769231,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 7.5 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 8.0 ), 1.0 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.5, 1.25 ), 0.0625 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.5, 5.0 ),
                          4.638172007975040E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.5, 8.75 ),
                          9.291476408358950E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.5, 9.0 ),
                          9.436649742654540E-01,
                          1e-15 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 5.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 11.0 ), 1.0 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 4.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 4.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 4.0, 5.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 4.0, 10.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 4.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 4.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 4.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 4.0, 5.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 4.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 4.0, 11.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalCDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 5.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 10.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 11.0*cgs::centimeter ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 1.0*cgs::centimeter ), 0.05 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 1.25*cgs::centimeter ), 0.0625 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 5.0*cgs::centimeter ),
                          4.534512303966930E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 8.75*cgs::centimeter ),
                          9.46087201247317822e-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 9.0*cgs::centimeter ),
                          9.57213743582549070e-01,
                          1e-15 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 2.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 2.5*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 5.0*cgs::centimeter ),
                          0.4230769230769231,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 7.5*cgs::centimeter ), 1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 8.0*cgs::centimeter ), 1.0 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.5*MeV, 1.0*cgs::centimeter ), 0.05 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.5*MeV, 1.25*cgs::centimeter ), 0.0625 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.5*MeV, 5.0*cgs::centimeter ),
                          4.638172007975040E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.5*MeV, 8.75*cgs::centimeter ),
                          9.291476408358950E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.5*MeV, 9.0*cgs::centimeter ),
                          9.436649742654540E-01,
                          1e-15 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 4.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 4.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 4.0*MeV, 5.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 4.0*MeV, 10.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 4.0*MeV, 11.0*cgs::centimeter ), 0.0 );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 4.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 4.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 4.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 4.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 4.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.551; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.55; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.55; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.55; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = distribution->sampleSecondaryConditional( 2.5 );
  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = distribution->sampleSecondaryConditional( 2.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = distribution->sampleSecondaryConditional( 2.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from upper boundary of third bin
  sample = distribution->sampleSecondaryConditional( 2.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 2.5 );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 2.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( 4.0 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 4.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 4.0 );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 4.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.551; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.55; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.55; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.55; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 2.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of third bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 2.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( 4.0*MeV ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 4.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 4.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 4.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 0u );
  trials = 0u;

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.551; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.55; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.55; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.55; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of third bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // Samples from upper boundary of third bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 4.0, trials ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 4.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 4.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 4.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 0u );
  trials = 0u;

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.551; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.55; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.55; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.55; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of third bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // Samples from upper boundary of third bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 4.0*MeV, trials ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 4.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 4.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 4.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices )
{
  size_t primary_bin_index = 0u, secondary_bin_index = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.551; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.55; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.55; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.55; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // Samples from upper boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices )
{
  size_t primary_bin_index = 0u, secondary_bin_index = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.551; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.55; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.55; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.55; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // Samples from upper boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0*MeV, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw )
{
  size_t primary_bin_index = 0u, secondary_bin_index = 0u;
  double raw_sample;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.551; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.55; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.55; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.55; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // Samples from upper boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw )
{
  size_t primary_bin_index = 0u, secondary_bin_index = 0u;
  quantity<cgs::length> raw_sample;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-12 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.551; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.55; // use lower bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.55; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.55; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 2u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // Samples from upper boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 4.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 3u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumber )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // In the second bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.584; // use upper bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.4230769230769231 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.4230769230769231 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.551; // use lower bin boundary
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.55; // use upper bin boundary
  fake_stream[4] = 0.55; // use upper bin boundary
  fake_stream[5] = 0.55; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5, 0.4230769230769231 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from upper boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 4.0, 0.0 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 4.0, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 4.0, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 4.0, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumber )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // In the second bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.584; // use upper bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.4230769230769231 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // On the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.4230769230769231 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.551; // use lower bin boundary
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.55; // use upper bin boundary
  fake_stream[4] = 0.55; // use upper bin boundary
  fake_stream[5] = 0.55; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5*MeV, 0.4230769230769231 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.5*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 4.0*MeV, 0.0 ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 4.0*MeV, 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 4.0*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 4.0*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalInSubrange )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 7.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 7.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 7.5 );
  FRENSIE_CHECK_EQUAL( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 7.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 11.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 11.0 );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 11.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 7.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 7.5 );
  FRENSIE_CHECK_EQUAL( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 7.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 0.4230769230769231;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 3.75, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );
  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.4230769230769231;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.551; // use lower bin boundary
  fake_stream[2] = 0.4230769230769231;
  fake_stream[3] = 0.551; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.551; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.55; // use upper bin boundary
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.55; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.55; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.5, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.5, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.5, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from upper boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.5, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.5, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 3.75, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.5, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 4.0, 7.5 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 4.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 4.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 4.0, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalInSubrange )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 7.5*cgs::centimeter ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 11.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 11.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 11.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 0.4230769230769231;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 3.75*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.4230769230769231;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.551; // use lower bin boundary
  fake_stream[2] = 0.4230769230769231;
  fake_stream[3] = 0.551; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.551; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.55; // use upper bin boundary
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.55; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.55; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 3.75*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.5*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 4.0*MeV, 7.5*cgs::centimeter ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 4.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 4.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 4.0*MeV, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( InterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange )
{


  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 7.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 11.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 11.0 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 11.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.5, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // In the second bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.584; // use upper bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.5, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 3.75, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.4230769230769231, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.4230769230769231, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.551; // use lower bin boundary
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.55; // use upper bin boundary
  fake_stream[4] = 0.55; // use upper bin boundary
  fake_stream[5] = 0.55; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5, 0.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5, 0.4230769230769231, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5, 1.0-1e-15, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from upper boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5, 0.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5, 0.5, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 3.75, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5, 1.0-1e-15, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 4.0, 0.0, 7.5 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 4.0, 0.0, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 4.0, 0.5, 7.5 );

  FRENSIE_CHECK_EQUAL( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 4.0, 1.0-1e-15, 7.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange )
{


  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 7.5*cgs::centimeter ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // Beyond full range - check that expected range will be used
  // Before the first bin - with extension
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 11.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 11.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 11.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  // On the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 11.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.5, 11.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 11.0*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.5, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // In the second bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.584; // use upper bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.5, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 3.75*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.4230769230769231, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.4230769230769231, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.551; // use lower bin boundary
  fake_stream[1] = 0.551; // use lower bin boundary
  fake_stream[2] = 0.551; // use lower bin boundary
  fake_stream[3] = 0.55; // use upper bin boundary
  fake_stream[4] = 0.55; // use upper bin boundary
  fake_stream[5] = 0.55; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5*MeV, 0.0, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5*MeV, 0.4230769230769231, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5*MeV, 0.0, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5*MeV, 0.5, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 3.75*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.5*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.0, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 4.0*MeV, 0.0, 7.5*cgs::centimeter ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 4.0*MeV, 0.0, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 4.0*MeV, 0.5, 7.5*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 4.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( InterpolatedFullyTabularBasicBivariateDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_LogLogLog_direct_interpolated_fully_tabular_basic_bivariate_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    auto concrete_dist = std::dynamic_pointer_cast<Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Direct<Utility::LogLogLog> > >( distribution );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "intermediate_base_dist", tab_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "base_dist", distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Direct<Utility::LogLogLog> > > concrete_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_dist ) );

  concrete_dist->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5, 1.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5, 1.25 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.5, 5.0 ),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5, 8.75 ), 0.5 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5, 9.0 ), 0.5 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, 2.5 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, 7.5 ), 0.5 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, 8.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.5, 1.25 ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 2.5, 5.0 ),
                          2.81617920177974E-01,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.5, 8.75 ), 0.05 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.5, 9.0 ), 0.05 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 4.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 4.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 4.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 4.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 4.0, 11.0 ), 0.0 );

  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>
    intermediate_base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( intermediate_base_dist ) );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.5, 1.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.5, 1.25 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.5, 5.0 ),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.5, 8.75 ), 0.5 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.5, 9.0 ), 0.5 );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0, 2.5 ), 0.1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0, 7.5 ), 0.5 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0, 8.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.5, 1.25 ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 2.5, 5.0 ),
                          2.81617920177974E-01,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.5, 8.75 ), 0.05 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.5, 9.0 ), 0.05 );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 4.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 4.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 4.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 4.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 4.0, 11.0 ), 0.0 );

  std::shared_ptr<Utility::BasicBivariateDistribution> base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist ) );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5, 1.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5, 1.25 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.5, 5.0 ),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5, 8.75 ), 0.5 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5, 9.0 ), 0.5 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, 2.5 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, 7.5 ), 0.5 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, 8.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.5, 1.25 ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 2.5, 5.0 ),
                          2.81617920177974E-01,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.5, 8.75 ), 0.05 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.5, 9.0 ), 0.05 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 4.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 4.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 4.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 4.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 4.0, 11.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_LogLogLog_direct_unit_aware_interpolated_fully_tabular_basic_bivariate_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    auto concrete_dist = std::dynamic_pointer_cast<Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::Direct<Utility::LogLogLog>,MegaElectronVolt,cgs::length,Barn> >( unit_aware_distribution );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "intermediate_base_dist", unit_aware_tab_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "base_dist", unit_aware_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::Direct<Utility::LogLogLog>,MegaElectronVolt,cgs::length,Barn> > concrete_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_dist ) );

  concrete_dist->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 10.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5*MeV, 1.25*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.5*MeV, 5.0*cgs::centimeter ),
                                  1.0*barn,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5*MeV, 8.75*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.5*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 2.5*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 7.5*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.5*MeV, 1.0*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.5*MeV, 1.25*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 2.5*MeV, 5.0*cgs::centimeter ),
                                  2.81617920177974E-01*barn,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.5*MeV, 8.75*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.5*MeV, 9.0*cgs::centimeter ), 0.05*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 4.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 4.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 4.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 4.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 4.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  std::shared_ptr<Utility::UnitAwareFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
    intermediate_base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( intermediate_base_dist ) );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0*MeV, 10.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.5*MeV, 1.25*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.5*MeV, 5.0*cgs::centimeter ),
                                  1.0*barn,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.5*MeV, 8.75*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.5*barn );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0*MeV, 2.5*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0*MeV, 7.5*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.5*MeV, 1.0*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.5*MeV, 1.25*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 2.5*MeV, 5.0*cgs::centimeter ),
                                  2.81617920177974E-01*barn,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.5*MeV, 8.75*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.5*MeV, 9.0*cgs::centimeter ), 0.05*barn );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 4.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 4.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 4.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 4.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 4.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  std::shared_ptr<Utility::UnitAwareBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> > base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist ) );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 10.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5*MeV, 1.25*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.5*MeV, 5.0*cgs::centimeter ),
                                  1.0*barn,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5*MeV, 8.75*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.5*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 2.5*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 7.5*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.5*MeV, 1.0*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.5*MeV, 1.25*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 2.5*MeV, 5.0*cgs::centimeter ),
                                  2.81617920177974E-01*barn,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.5*MeV, 8.75*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.5*MeV, 9.0*cgs::centimeter ), 0.05*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 4.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 4.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 4.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 4.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 4.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );
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
    primary_grid[0] = 1.0;
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );

    // Create the secondary distribution in the second bin
    primary_grid[1] = 1.0;
    secondary_dists[1].reset( new Utility::UniformDistribution( 0.0, 10.0, 1.0 ) );

    // Create the secondary distribution in the third bin
    std::vector<double> bin_boundaries( 3 ), values( 3 );
    bin_boundaries[0] = 2.5; values[0] = 0.1;
    bin_boundaries[1] = 5.0; values[1] = 1.0;
    bin_boundaries[2] = 7.5; values[2] = 0.5;

    primary_grid[2] = 2.0;
    secondary_dists[2].reset( new Utility::TabularDistribution<Utility::LinLin>( bin_boundaries, values ) );

    // Create the secondary distribution beyond the third bin
    primary_grid[3] = 3.0;
    secondary_dists[3] = secondary_dists[0];

    tab_distribution.reset( new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Direct<Utility::LogLogLog> >(
                                                            primary_grid,
                                                            secondary_dists,
                                                            1e-3,
                                                            1e-7 ) );
    distribution = tab_distribution;
  }

  // Create the unit-aware two-dimensional distribution
  {
    std::vector<quantity<MegaElectronVolt> > primary_bins( 4 );

    std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 4 );

    // Create the secondary distribution in the first bin
    primary_bins[0] = 1.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 0.1*barn ) );

    // Create the secondary distribution in the second bin
    primary_bins[1] = 1.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 1.0*barn ) );

    // Create the secondary distribution in the third bin
    std::vector<quantity<cgs::length> > bin_boundaries( 3 );
    std::vector<quantity<Barn> > values( 3 );
    bin_boundaries[0] = 2.5*cgs::centimeter; values[0] = 0.1*barn;
    bin_boundaries[1] = 5.0*cgs::centimeter; values[1] = 1.0*barn;
    bin_boundaries[2] = 7.5*cgs::centimeter; values[2] = 0.5*barn;

    primary_bins[2] = 2.0*MeV;
    secondary_dists[2].reset( new Utility::UnitAwareTabularDistribution<Utility::LinLin,cgs::length,Barn>( bin_boundaries, values ) );

    // Create the secondary distribution beyond the third bin
    primary_bins[3] = 3.0*MeV;
    secondary_dists[3] = secondary_dists[0];

    unit_aware_tab_distribution.reset( new Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::Direct<Utility::LogLogLog>,MegaElectronVolt,cgs::length,Barn>( primary_bins, secondary_dists, 1e-3, 1e-7 ) );

    unit_aware_distribution = unit_aware_tab_distribution;
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLogLogLogDirectInterpolatedFullyTabularBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
