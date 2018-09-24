//---------------------------------------------------------------------------//
//!
//! \file   tstLogLogLogCutoffElasticBasicBivariateDistribution.cpp
//! \author Luke Kersting
//! \brief  The elastic two-dimensional dist. unit tests
//!         (Cutoff with LogLogLog interpolation)
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
#include "MonteCarlo_ElasticBasicBivariateDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
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
std::shared_ptr<Utility::UnitAwareBasicBivariateDistribution<MegaElectronVolt,cgs::dimensionless,Barn> >
  unit_aware_distribution;

std::shared_ptr<Utility::UnitAwareFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::dimensionless,Barn> >
  unit_aware_tab_distribution;

std::shared_ptr<Utility::BasicBivariateDistribution> distribution;

std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> tab_distribution;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<template<typename> class TwoDGridPolicy,
         typename BaseTabDistribution,
         typename BaseDistribution>
void initialize( std::shared_ptr<BaseTabDistribution>& tab_dist,
                 std::shared_ptr<BaseDistribution>& dist )
{
  typename BaseTabDistribution::SecondaryIndepQuantity cutoff;
  Utility::setQuantity( cutoff, 0.999999 );

  std::vector<typename BaseTabDistribution::PrimaryIndepQuantity> primary_bins( 2 );

  std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit> > > secondary_dists( 2 );

  // Create the secondary distribution in the first bin
  std::vector<typename BaseTabDistribution::SecondaryIndepQuantity> bin_boundaries( 3 );
  Utility::setQuantity( bin_boundaries[0], -1.0 );
  Utility::setQuantity( bin_boundaries[1], 0.0 );
  Utility::setQuantity( bin_boundaries[2], 0.999999 );

  std::vector<typename BaseTabDistribution::DepQuantity> values( 3 );
  Utility::setQuantity( values[0], 0.1 );
  Utility::setQuantity( values[1], 0.5 );
  Utility::setQuantity( values[2], 1.0 );

  Utility::setQuantity( primary_bins[0], 1.0 );
  secondary_dists[0].reset( new Utility::UnitAwareTabularDistribution<Utility::LinLin,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>( bin_boundaries, values ) );

  // Create the secondary distribution beyond the second bin
  Utility::setQuantity( values[0], 1.0 );
  Utility::setQuantity( values[1], 5.0 );
  Utility::setQuantity( values[2], 10.0 );

  Utility::setQuantity( primary_bins[1], 2.0 );
  secondary_dists[1].reset( new Utility::UnitAwareTabularDistribution<Utility::LinLin,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>( bin_boundaries, values ) );

  tab_dist.reset( new MonteCarlo::UnitAwareElasticBasicBivariateDistribution<TwoDGridPolicy<Utility::LogLogCosLog >,typename BaseTabDistribution::PrimaryIndepUnit,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>(
      primary_bins, secondary_dists, cutoff, 1e-3, 1e-7 ) );

  dist = tab_dist;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   isPrimaryDimensionTabular )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  FRENSIE_CHECK( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   isPrimaryDimensionTabular )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  FRENSIE_CHECK( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous in the primary dimension
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   isPrimaryDimensionContinuous )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  FRENSIE_CHECK( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous in the primary
// dimension
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   isPrimaryDimensionContinuous )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  FRENSIE_CHECK( unit_aware_distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary lower bound can be returned
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfPrimaryIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary lower bound can be
// returned
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfPrimaryIndepVar(), 1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary dimension upper bound can be returned
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfPrimaryIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary dimension upper bound can
// be returned
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfPrimaryIndepVar(), 2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional distribution can be returned
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   getLowerBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 0.0 ),
                       0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 0.0 ),
                       -1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.0 ),
                       -1.0 );

  // In the first bin
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.5 ),
                       -1.0 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 2.0 ),
                       -1.0 );

  // Beyond the second bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 3.0 ),
                       -1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional unit-aware distribution can be
// returned
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   getLowerBoundOfSecondaryConditionalIndepVar )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 0.0*MeV ),
                       0.0*cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 0.0*MeV ),
                       -1.0*cgs::dimensionless() );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.0*MeV ),
                       -1.0*cgs::dimensionless() );

  // In the first bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.5*MeV ),
                       -1.0*cgs::dimensionless() );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 2.0*MeV ),
                       -1.0*cgs::dimensionless() );

  // Beyond the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::dimensionless() );

  // Beyond the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 3.0*MeV ),
                       -1.0*cgs::dimensionless() );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional distribution can be returned
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   getUpperBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 0.0 ),
                       0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 0.0 ),
                       0.999999 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.0 ),
                       0.999999 );

  // In the first bin
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.5 ),
                       0.999999 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 2.0 ),
                       0.999999 );

  // Beyond the second bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 3.0 ),
                       0.999999 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional unit-aware distribution can be
// returned
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   getUpperBoundOfSecondaryConditionalIndepVar )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 0.0*MeV ),
                       0.0*cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 0.0*MeV ),
                       0.999999*cgs::dimensionless() );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.0*MeV ),
                       0.999999*cgs::dimensionless() );

  // In the first bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.5*MeV ),
                       0.999999*cgs::dimensionless() );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 2.0*MeV ),
                       0.999999*cgs::dimensionless() );

  // Beyond the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::dimensionless() );

  // Beyond the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 3.0*MeV ),
                       0.999999*cgs::dimensionless() );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the bounds of two distribution can be compared
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   hasSamePrimaryBounds )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

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
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.1, 0.999999, 0.1 ) );

    // Create the secondary distribution In the first bin
    primary_grid[1] = 2.0;
    secondary_dists[1] = secondary_dists[0];

    test_dist.reset( new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogCosLog > >(
                                             primary_grid, secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *test_dist ) );

  // Create a test distribution with different lower bound, same upper bound
  {
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 2 );

    // Create the secondary distribution in the first bin
    primary_grid[0] = 1.0;
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.1, 0.999999, 0.1 ) );

    // Create the secondary distribution In the first bin
    primary_grid[1] = 3.0;
    secondary_dists[1] = secondary_dists[0];

    test_dist.reset( new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogCosLog > >(
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
    secondary_grids[0][1] = 0.999999;   values[0][1] = 0.1;

    secondary_grids[1].resize( 3 ); values[1].resize( 3 );
    secondary_grids[1][0] = 0.1;    values[1][0] = 0.1;
    secondary_grids[1][1] = 0.5;    values[1][1] = 1.0;
    secondary_grids[1][2] = 0.999999;    values[1][2] = 0.5;

    secondary_grids[2].resize( 2 ); values[2].resize( 2 );
    secondary_grids[2][0] = 0.1;    values[2][0] = 0.5;
    secondary_grids[2][1] = 0.999999;    values[2][1] = 0.5;

    secondary_grids[3] = secondary_grids[0];
    values[3] = values[0];

    test_dist.reset( new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogCosLog > >(
                                                               primary_grid,
                                                               secondary_grids,
                                                               values ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *test_dist ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution, evaluate_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 0.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 0.0, 0.999999 ), 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 1.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 1.0, 0.999999 ), 1.0, 1e-14 );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 1.5, -1.0 ),
                          3.84558575793691015399e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 1.5, 0.0 ),
                          1.92279287896845474393,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 1.5, 0.999999 ),
                          3.84558575793690993194e+00,
                          1e-14 );

  // On the upper bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 2.0, -1.0 ), 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 2.0, 0.999999 ), 10.0, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 0.999999 ), 10.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   evaluate_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  3.84558575793691015399e-01*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.92279287896845474393*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.84558575793690993194e+00*barn,
                                  1e-14 );

  // On the upper bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  1.0*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution, evaluate_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 0.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 0.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 0.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 1.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 1.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 1.0, 0.999999 ), 1.0 );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, -1.0 ),
                          3.84558575793691015399e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.0 ),
                          1.92279287896845474393,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.999999 ),
                          3.84558575793690993194e+00,
                          1e-14 );

  // On the upper bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 2.0, -1.0 ), 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 2.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 2.0, 0.999999 ), 10.0 );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, 0.999999 ), 10.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   evaluate_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  3.84558575793691015399e-01*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.92279287896845474393*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.84558575793690993194e+00*barn,
                                  1e-14 );

  // On the upper bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  1.0*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution, evaluate_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 0.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 0.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 0.0, 0.999999 ), 1.0 );


  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 1.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 1.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 1.0, 0.999999 ), 1.0 );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, -1.0 ),
                          2.1117818980603434e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.0 ),
                          1.0558909490301716,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.999999 ),
                          2.1117818980603431,
                          1e-14 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 2.0, -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 2.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 2.0, 0.999999 ), 10.0 );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluate( 3.0, 0.999999 ), 10.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   evaluate_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  2.1117818980603434e-01*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.0558909490301716*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  2.1117818980603431*barn,
                                  1e-14 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 2.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.0 ),
                          4.761908163267735139e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.999999 ),
                          9.523816326535470278e-01,
                          1e-14 );

  // On the upper bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // On the upper bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );


  // On the upper bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );


  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // On the upper bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );


  // On the upper bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );


  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  // In the first bin
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // On the upper bin boundary
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalCDF_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.999999 ), 1.0 );

  // In the first bin
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.999999 ), 1.0 );


  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 1.0 );


  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalCDF_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // In the first bin
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalCDF_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.999999 ), 1.0 );

  // In the first bin
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.999999 ), 1.0 );


  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 1.0 );


  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalCDF_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // In the first bin
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalCDF_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.999999 ), 1.0 );

  // In the first bin
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.999999 ), 1.0 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 1.0 );


  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   evaluateSecondaryConditionalCDF_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // In the first bin
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditional_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 2.85714489796064063931e-01;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064063931e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditional_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
                unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 2.85714489796064063931e-01;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064063931e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordTrials_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

  Utility::DistributionTraits::Counter trials = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  trials = 0u;

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 2.85714489796064063931e-01;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064063931e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;

  trials = 0u;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordTrials_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  Utility::DistributionTraits::Counter trials = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  trials = 0u;

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 2.85714489796064063931e-01;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064063931e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;

  trials = 0u;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

  size_t primary_bin_index = 0u, secondary_bin_index = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.85714489796064174953e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.85714489796064174953e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 2.85714489796064063931e-01;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.85714489796064063931e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  size_t primary_bin_index = 0u, secondary_bin_index = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.85714489796064174953e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.85714489796064174953e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 2.85714489796064063931e-01;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.85714489796064063931e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

  size_t primary_bin_index = 0u, secondary_bin_index = 0u;
  double raw_sample;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.85714489796064174953e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.85714489796064174953e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 2.85714489796064063931e-01;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.85714489796064063931e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  size_t primary_bin_index = 0u, secondary_bin_index = 0u;
  quantity<cgs::dimensionless> raw_sample;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.85714489796064174953e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.85714489796064174953e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.584; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 2.85714489796064063931e-01;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 0u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.85714489796064063931e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, -1.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  FRENSIE_CHECK_EQUAL( primary_bin_index, 1u );
  FRENSIE_CHECK_EQUAL( secondary_bin_index, 1u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumber_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // In the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.584; // use upper bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.85714489796064175e-01 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.85714489796064064e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 2.85714489796064063931e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 2.85714489796064063931e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumber_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.584; // use upper bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.85714489796064175e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.85714489796064064e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 2.85714489796064063931e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 2.85714489796064063931e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalInSubrange_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 0.2;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalInSubrange_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 0.2;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 2.85714489796064174953e-01, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.584; // use upper bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 2.85714489796064174953e-01, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.584; // use upper bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditional_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 2.85714489796064063931e-01;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064063931e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditional_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
                unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 2.85714489796064174953e-01;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 2.85714489796064063931e-01;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample bin boundary
  fake_stream[2] = 2.85714489796064063931e-01;
  fake_stream[3] = 0.0; // Sample bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0; // Sample bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumber_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.85714489796064064e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 2.85714489796064064e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 2.85714489796064064e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumber_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.85714489796064064e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 2.85714489796064064e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 2.85714489796064064e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalInSubrange_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 0.2;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalInSubrange_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.584; // use upper bin boundary
  fake_stream[8] = 0.2;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF an be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 2.85714489796064174953e-01, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF an be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 2.85714489796064174953e-01, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditional_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064064e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // On the upper bin boundary
  fake_stream[1] = 2.85714489796064063931e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 3.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditional_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064064e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream[1] = 2.85714489796064063931e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 3.0*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumber_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.85714489796064064e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 2.85714489796064063931e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 2.85714489796064063931e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumber_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 2.85714489796064174953e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.85714489796064064e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 2.85714489796064063931e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 2.85714489796064063931e-01 );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalInSubrange_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.85714489796064174953e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalInSubrange_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.85714489796064174953e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( ElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 2.85714489796064174953e-01, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  FRENSIE_CHECK_EQUAL( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareElasticBasicBivariateDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                 unit_aware_distribution );

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 2.85714489796064174953e-01, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_EQUAL( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ElasticBasicBivariateDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_LogLogLog_cutoff_elastic_basic_bivariate_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    initialize<Utility::UnitBase>( tab_distribution, distribution );

    auto concrete_dist = std::dynamic_pointer_cast<MonteCarlo::ElasticBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogCosLog > > >( distribution );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "intermediate_base_dist", tab_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "base_dist", distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::ElasticBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogCosLog > > > concrete_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_dist ) );

  concrete_dist->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.0, 0.999999 ), 1.0, 1e-14 );

  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.0, 0.999999 ), 1.0, 1e-14 );

  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.5, -1.0 ),
                          3.84558575793691015399e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.5, 0.0 ),
                          1.92279287896845474393,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.5, 0.999999 ),
                          3.84558575793690993194e+00,
                          1e-14 );

  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 2.0, -1.0 ), 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 2.0, 0.999999 ), 10.0, 1e-14 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, 0.999999 ), 10.0 );

  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>
    intermediate_base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( intermediate_base_dist ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 0.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 0.0, 0.999999 ), 1.0, 1e-14 );

  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.0, 0.999999 ), 1.0, 1e-14 );

  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.5, -1.0 ),
                          3.84558575793691015399e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.5, 0.0 ),
                          1.92279287896845474393,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.5, 0.999999 ),
                          3.84558575793690993194e+00,
                          1e-14 );

  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 2.0, -1.0 ), 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 2.0, 0.999999 ), 10.0, 1e-14 );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0, -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0, 0.999999 ), 10.0 );

  std::shared_ptr<Utility::BasicBivariateDistribution> base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.0, 0.999999 ), 1.0, 1e-14 );

  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.0, -1.0 ), 0.1, 1e-14 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, 0.0 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.0, 0.999999 ), 1.0, 1e-14 );

  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.5, -1.0 ),
                          3.84558575793691015399e-01,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.5, 0.0 ),
                          1.92279287896845474393,
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.5, 0.999999 ),
                          3.84558575793690993194e+00,
                          1e-14 );

  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 2.0, -1.0 ), 1.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 2.0, 0.999999 ), 10.0, 1e-14 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, -1.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, 0.0 ), 5.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, 0.999999 ), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareElasticBasicBivariateDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_LinLinLin_cutoff_unit_aware_elastic_basic_bivariate_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

    auto concrete_dist = std::dynamic_pointer_cast<MonteCarlo::UnitAwareElasticBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogCosLog >,MegaElectronVolt,cgs::dimensionless,Barn> >( unit_aware_distribution );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "intermediate_base_dist", unit_aware_tab_distribution ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "base_dist", unit_aware_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::UnitAwareElasticBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogCosLog >,MegaElectronVolt,cgs::dimensionless,Barn> > concrete_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_dist ) );

  concrete_dist->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  3.84558575793691015399e-01*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.92279287896845474393*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.84558575793690993194e+00*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  1.0*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  std::shared_ptr<Utility::UnitAwareFullyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::dimensionless,Barn> >
    intermediate_base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( intermediate_base_dist ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  3.84558575793691015399e-01*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.92279287896845474393*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.84558575793690993194e+00*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( intermediate_base_dist->evaluate( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  1.0*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( intermediate_base_dist->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  std::shared_ptr<Utility::UnitAwareBasicBivariateDistribution<MegaElectronVolt,cgs::dimensionless,Barn> > base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  3.84558575793691015399e-01*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.92279287896845474393*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.84558575793690993194e+00*barn,
                                  1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  1.0*barn,
                                  1e-14 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLogLogLogCutoffElasticBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
