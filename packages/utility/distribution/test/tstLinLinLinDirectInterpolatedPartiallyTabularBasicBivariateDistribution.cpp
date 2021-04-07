//---------------------------------------------------------------------------//
//!
//! \file   tstLinLinLinDirectInterpolatedPartiallyTabularBasicBivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The interpolated partially tabular two-dimensional dist. unit tests
//!         (LinLinLin Direct interpolation)
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
#include "Utility_InterpolatedPartiallyTabularBasicBivariateDistribution.hpp"
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
// Check that the distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution,
                   isPrimaryDimensionTabular )
{
  FRENSIE_CHECK( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                   isPrimaryDimensionTabular )
{
  FRENSIE_CHECK( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous in the primary dimension
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution,
                   isPrimaryDimensionContinuous )
{
  FRENSIE_CHECK( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous in the primary dim.
FRENSIE_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                   isPrimaryDimensionContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary dimension lower bound can be returned
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfPrimaryIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary dimension lower bound can
// be returned
FRENSIE_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfPrimaryIndepVar(), 0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary dimension upper bound can be returned
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfPrimaryIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary dimension upper bound can
// be returned
FRENSIE_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfPrimaryIndepVar(), 2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional distribution can be returned
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution,
                   getLowerBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0),
                       0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar(-1.0),
                       0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 0.0 ),
                       0.0 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 0.5 ),
                       0.0 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.0 ),
                       2.5 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.5 ),
                       0.0 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 2.0 ),
                       0.0 );

  // Beyond the third bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfSecondaryConditionalIndepVar( 3.0 ),
                       0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware conditional distribution can be
// returned
FRENSIE_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                   getLowerBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( -1.0*MeV ),
                       0.0*cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( -1.0*MeV ),
                       0.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 0.0*MeV ),
                       0.0*cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 0.5*MeV ),
                       0.0*cgs::centimeter );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.0*MeV ),
                       2.5*cgs::centimeter );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 1.5*MeV ),
                       0.0*cgs::centimeter );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 2.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfSecondaryConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional distribution can be returned
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution,
                   getUpperBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0),
                       0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar(-1.0),
                       10.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 0.0 ),
                       10.0 );

  // In the second bin
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 0.5 ),
                       10.0 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.0 ),
                       7.5 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.5 ),
                       10.0 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 2.0 ),
                       10.0 );

  // Beyond the third bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfSecondaryConditionalIndepVar( 3.0 ),
                       10.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware conditional distribution can be
// returned
FRENSIE_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                   getUpperBoundOfSecondaryConditionalIndepVar )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( -1.0*MeV ),
                       0.0*cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( -1.0*MeV ),
                       10.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 0.0*MeV ),
                       10.0*cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 0.5*MeV ),
                       10.0*cgs::centimeter );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.0*MeV ),
                       7.5*cgs::centimeter );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 1.5*MeV ),
                       10.0*cgs::centimeter );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 2.0*MeV ),
                       10.0*cgs::centimeter );

  // Beyond the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfSecondaryConditionalIndepVar( 3.0*MeV ),
                       10.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the bounds of two distributions can be compared
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution,
                   hasSamePrimaryBounds )
{
  // Self test
  FRENSIE_CHECK( distribution->hasSamePrimaryBounds( *distribution ) );

  // Create a test distribution with same lower bound, different upper bound
  std::shared_ptr<Utility::PartiallyTabularBasicBivariateDistribution> test_dist;

  {
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 2 );

    // Create the secondary distribution in the first bin
    primary_grid[0] = 0.0;
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );

    // Create the secondary distribution in the second bin
    primary_grid[1] = 1.0;
    secondary_dists[1].reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.0, 10.0 ) );

    test_dist.reset( new Utility::InterpolatedPartiallyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LinLinLin> >(
                                                        primary_grid,
                                                        secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *test_dist ) );

  // Create a test distribution with different lower bound, same upper bound
  {
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 2 );

    // Create the secondary distribution in the first bin
    primary_grid[0] = 1.0;
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );

    // Create the secondary distribution in the second bin
    primary_grid[1] = 2.0;
    secondary_dists[1].reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.0, 10.0 ) );

    test_dist.reset( new Utility::InterpolatedPartiallyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LinLinLin> >(
                                                       primary_grid,
                                                       secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *test_dist ) );

  // Create a test distribution with different bounds
  {
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 2 );

    // Create the secondary distribution in the first bin
    primary_grid[0] = 0.5;
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );

    // Create the secondary distribution in the second bin
    primary_grid[1] = 1.5;
    secondary_dists[1].reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.0, 10.0 ) );

    test_dist.reset( new Utility::InterpolatedPartiallyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LinLinLin> >(
                                                    primary_grid,
                                                    secondary_dists ) );
  }

  FRENSIE_CHECK( !distribution->hasSamePrimaryBounds( *test_dist ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution, evaluate )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 5.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 10.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 10.0 ), exp( -10.0 ) );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0, 11.0 ), 0.0 );

  // In the second bin
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 0.5, 1.0 ),
                          1.83939720585721167e-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 0.5, 2.5 ),
                          5.410424993119490E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 0.5, 5.0 ),
                          5.033689734995430E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 0.5, 7.5 ),
                          5.002765421850740E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( 0.5, 9.0 ),
                          6.170490204333980E-05,
                          1e-15 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 2.5 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 7.5 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0, 8.0 ), 0.0 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 2.5 ), 0.55 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 5.0 ), 0.55 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 7.5 ), 0.55 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.5, 9.0 ), 0.05 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0, 11.0 ), 0.0 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 5.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 10.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 3.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                   evaluate )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 5.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 10.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( -1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 10.0*cgs::centimeter ), exp( -10.0 )*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // In the second bin
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 1.0*cgs::centimeter ),
                          1.83939720585721167e-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 2.5*cgs::centimeter ),
                          5.410424993119490E-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 5.0*cgs::centimeter ),
                          5.033689734995430E-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 7.5*cgs::centimeter ),
                          5.002765421850740E-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 9.0*cgs::centimeter ),
                          6.170490204333980E-05*barns,
                          1e-15 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 2.5*cgs::centimeter ), 0.55*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 5.0*cgs::centimeter ), 0.55*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 7.5*cgs::centimeter ), 0.55*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.05*barn );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 5.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 10.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( -1.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          1.0000454019910097,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.0, 10.0 ),
                          4.540199100968777e-05,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 0.0, 11.0 ), 0.0 );

  // In the second bin
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 1.0 ),
                          1.83948071815261516e-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 2.5 ),
                          1.410443627231340E-01,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 5.0 ),
                          1.033691264576470E-01,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 7.5 ),
                          1.002765547406400E-01,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 9.0 ),
                          6.17077035687476114e-05,
                          1e-15 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 2.5 ), 0.2 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 5.0 ), 0.2 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 7.5 ), 0.2 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.0, 8.0 ), 0.0 );

  // In the third bin
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.5, 2.5 ),
                          0.15,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.5, 5.0 ),
                          0.15,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.5, 7.5 ),
                          0.15,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 1.5, 9.0 ), 0.05 );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 2.0, 11.0 ), 0.0 );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 5.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 10.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluateSecondaryConditionalPDF( 3.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 5.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::centimeter ),
                          1.0000454019910097/cgs::centimeter,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 10.0*cgs::centimeter ),
                          4.540199100968777e-05/cgs::centimeter,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the second bin
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 1.0*cgs::centimeter ),
                          1.83948071815261516e-01/cgs::centimeter,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 2.5*cgs::centimeter ),
                          1.410443627231340E-01/cgs::centimeter,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 5.0*cgs::centimeter ),
                          1.033691264576470E-01/cgs::centimeter,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 7.5*cgs::centimeter ),
                          1.002765547406400E-01/cgs::centimeter,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 9.0*cgs::centimeter ),
                          6.17077035687476114e-05/cgs::centimeter,
                          1e-15 );

  // On the third bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 2.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 2.5*cgs::centimeter ), 0.2/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 5.0*cgs::centimeter ), 0.2/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 7.5*cgs::centimeter ), 0.2/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 8.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the third bin
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.0*cgs::centimeter ), 0.05/cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 2.5*cgs::centimeter ),
                          0.15/cgs::centimeter,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 5.0*cgs::centimeter ),
                          0.15/cgs::centimeter,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 7.5*cgs::centimeter ),
                          0.15/cgs::centimeter,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 9.0*cgs::centimeter ), 0.05/cgs::centimeter );

  // On the upper bin boundary
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - no extension
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 5.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( -1.0 ),
              std::logic_error );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sampleSecondaryConditional( -1.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( -1.0 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931017816607284, 1e-15 );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931017816607284, 1e-15 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // Samples from upper boundary of second bin
  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = distribution->sampleSecondaryConditional( 1.5 );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from upper boundary of third bin
  sample = distribution->sampleSecondaryConditional( 1.5 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

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

  sample = distribution->sampleSecondaryConditional( 2.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 3.0 );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                   sampleSecondaryConditional )
{
   // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931017816607284*cgs::centimeter, 1e-15 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931017816607284*cgs::centimeter, 1e-15 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // Samples from upper boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of third bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

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

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( InterpolatedPartiallyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 0u );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  distribution->limitToPrimaryIndepLimits();

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

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931017816607284, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931017816607284, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // Samples from upper boundary of second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  // On the third bin
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

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of third bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // Samples from upper boundary of third bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

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

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials ),
              std::logic_error );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
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

  distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  Utility::DistributionTraits::Counter trials = 0u;

  // Before the first bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials ),
              std::logic_error );
  FRENSIE_CHECK_EQUAL( trials, 0u );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  unit_aware_distribution->limitToPrimaryIndepLimits();

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

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931017816607284*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.6931017816607284*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // Samples from upper boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 6u );

  // On the third bin
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

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of third bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // Samples from upper boundary of third bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

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

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3u );

  // After the third bin - no extension
  FRENSIE_CHECK_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
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

  unit_aware_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( InterpolatedPartiallyTabularBasicBivariateDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_LinLinLin_direct_interpolated_partially_tabular_basic_bivariate_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    auto concrete_dist = std::dynamic_pointer_cast<Utility::InterpolatedPartiallyTabularBasicBivariateDistribution<Utility::Direct<Utility::LinLinLin> > >( distribution );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "base_dist", distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::InterpolatedPartiallyTabularBasicBivariateDistribution<Utility::Direct<Utility::LinLinLin> > > concrete_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_dist ) );

  concrete_dist->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( -1.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( -1.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( -1.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( -1.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0, 10.0 ), exp( -10.0 ) );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.5, 1.0 ),
                          1.83939720585721167e-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.5, 2.5 ),
                          5.410424993119490E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.5, 5.0 ),
                          5.033689734995430E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.5, 7.5 ),
                          5.002765421850740E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.5, 9.0 ),
                          6.170490204333980E-05,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, 2.5 ), 1.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, 7.5 ), 1.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0, 8.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5, 2.5 ), 0.55 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5, 5.0 ), 0.55 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5, 7.5 ), 0.55 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5, 9.0 ), 0.05 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0, 11.0 ), 0.0 );

  std::shared_ptr<Utility::PartiallyTabularBasicBivariateDistribution>
    base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist ) );

  base_dist->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( -1.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( -1.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( -1.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( -1.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( -1.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0, 10.0 ), exp( -10.0 ) );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.5, 1.0 ),
                          1.83939720585721167e-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.5, 2.5 ),
                          5.410424993119490E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.5, 5.0 ),
                          5.033689734995430E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.5, 7.5 ),
                          5.002765421850740E-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.5, 9.0 ),
                          6.170490204333980E-05,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, 2.5 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, 7.5 ), 1.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0, 8.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5, 2.5 ), 0.55 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5, 5.0 ), 0.55 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5, 7.5 ), 0.55 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5, 9.0 ), 0.05 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0, 11.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0, 11.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_LinLinLin_direct_interpolated_partially_tabular_basic_bivariate_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    auto concrete_dist = std::dynamic_pointer_cast<Utility::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::Direct<Utility::LinLinLin>,MegaElectronVolt,cgs::length,Barn> >( unit_aware_distribution );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_dist ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "base_dist", unit_aware_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::Direct<Utility::LinLinLin>,MegaElectronVolt,cgs::length,Barn> > concrete_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_dist ) );

  concrete_dist->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( -1.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( -1.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( -1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, 10.0*cgs::centimeter ), exp( -10.0 )*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.5*MeV, 1.0*cgs::centimeter ),
                          1.83939720585721167e-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.5*MeV, 2.5*cgs::centimeter ),
                          5.410424993119490E-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.5*MeV, 5.0*cgs::centimeter ),
                          5.033689734995430E-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.5*MeV, 7.5*cgs::centimeter ),
                          5.002765421850740E-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( concrete_dist->evaluate( 0.5*MeV, 9.0*cgs::centimeter ),
                          6.170490204333980E-05*barns,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5*MeV, 2.5*cgs::centimeter ), 0.55*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5*MeV, 5.0*cgs::centimeter ), 0.55*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5*MeV, 7.5*cgs::centimeter ), 0.55*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.05*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( concrete_dist->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  std::shared_ptr<Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<MegaElectronVolt,cgs::length,Barn> >
    base_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_dist ) );

  base_dist->extendBeyondPrimaryIndepLimits();

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( -1.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( -1.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( -1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, 10.0*cgs::centimeter ), exp( -10.0 )*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.5*MeV, 1.0*cgs::centimeter ),
                          1.83939720585721167e-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.5*MeV, 2.5*cgs::centimeter ),
                          5.410424993119490E-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.5*MeV, 5.0*cgs::centimeter ),
                          5.033689734995430E-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.5*MeV, 7.5*cgs::centimeter ),
                          5.002765421850740E-01*barns,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( base_dist->evaluate( 0.5*MeV, 9.0*cgs::centimeter ),
                          6.170490204333980E-05*barns,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5*MeV, 2.5*cgs::centimeter ), 0.55*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5*MeV, 5.0*cgs::centimeter ), 0.55*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5*MeV, 7.5*cgs::centimeter ), 0.55*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.05*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  FRENSIE_CHECK_EQUAL( base_dist->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );
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
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );

    // Create the secondary distribution in the second bin
    primary_grid[1] = 0.0;
    secondary_dists[1].reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.0, 10.0 ) );

    // Create the secondary distribution in the third bin
    primary_grid[2] = 1.0;
    secondary_dists[2].reset( new Utility::UniformDistribution( 2.5, 7.5, 1.0 ) );

    // Create the secondary distribution beyond the third bin
    primary_grid[3] = 2.0;
    secondary_dists[3] = secondary_dists[0];

    distribution.reset( new Utility::InterpolatedPartiallyTabularBasicBivariateDistribution<Utility::Direct<Utility::LinLinLin> >(
                                                           primary_grid,
                                                           secondary_dists ) );
  }

  // Create the unit-aware two-dimensional distribution
  {
    std::vector<quantity<MegaElectronVolt> > primary_bins( 4 );

    std::vector<std::shared_ptr<const Utility::UnitAwareUnivariateDistribution<cgs::length,Barn> > > secondary_dists( 4 );

    // Create the secondary distribution in the first bin
    primary_bins[0] = 0.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 0.1*barn ) );

    // Create the secondary distribution in the second bin
    primary_bins[1] = 0.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareExponentialDistribution<cgs::length,Barn>( 1.0*barn, 1.0/cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ) );

    // Create the secondary distribution in the third bin
    primary_bins[2] = 1.0*MeV;
    secondary_dists[2].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 2.5*cgs::centimeter, 7.5*cgs::centimeter, 1.0*barn ) );

    // Create the secondary distribution beyond the third bin
    primary_bins[3] = 2.0*MeV;
    secondary_dists[3] = secondary_dists[0];

    unit_aware_distribution.reset( new Utility::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::Direct<Utility::LinLinLin>,MegaElectronVolt,cgs::length,Barn>( primary_bins, secondary_dists ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLinLinLinDirectInterpolatedPartiallyTabularBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
