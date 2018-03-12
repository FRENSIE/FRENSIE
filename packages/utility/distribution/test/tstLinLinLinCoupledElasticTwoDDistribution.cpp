//---------------------------------------------------------------------------//
//!
//! \file   tstLinLinLinCoupledElasticTwoDDistribution.cpp
//! \author Luke Kersting
//! \brief  The elastic two-dimensional dist. unit tests
//!         (Coupled with LinLinLin interpolation)
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Boost Includes
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DynamicOutputFormatter.hpp"
#include "Utility_CoupledElasticDistribution.hpp"
#include "Utility_ElasticTwoDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_BarnUnit.hpp"

using boost::units::quantity;
using Utility::Units::MegaElectronVolt;
using Utility::Units::MeV;
using Utility::Units::Barn;
using Utility::Units::barn;
using Utility::Units::barns;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<Utility::UnitAwareTwoDDistribution<MegaElectronVolt,cgs::dimensionless,Barn> >
  unit_aware_distribution;

std::shared_ptr<Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::dimensionless,Barn> >
  unit_aware_tab_distribution;

std::shared_ptr<Utility::TwoDDistribution> distribution;

std::shared_ptr<Utility::FullyTabularTwoDDistribution> tab_distribution;

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
  double moliere_eta = 1.0;
  double cutoff_ratio = 0.9;
  typename BaseTabDistribution::SecondaryIndepQuantity cutoff;
  Utility::setQuantity( cutoff, 1.0 );

  // Create the unit-aware two-dimensional distribution
  {
    std::vector<typename BaseTabDistribution::PrimaryIndepQuantity> primary_bins( 2 );

    Teuchos::Array<std::shared_ptr<const Utility::UnitAwareTabularOneDDistribution<typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit> > > secondary_dists( 2 );

    // Create the secondary distribution in the first bin
    Teuchos::Array<typename BaseTabDistribution::SecondaryIndepQuantity> bin_boundaries( 3 );
    Utility::setQuantity( bin_boundaries[0], -1.0 );
    Utility::setQuantity( bin_boundaries[1], 0.0 );
    Utility::setQuantity( bin_boundaries[2], 0.999999 );

    Teuchos::Array<typename BaseTabDistribution::DepQuantity> values( 3 );
    Utility::setQuantity( values[0], 0.1 );
    Utility::setQuantity( values[1], 0.5 );
    Utility::setQuantity( values[2], 1.0 );

    Utility::setQuantity( primary_bins[0], 1.0 );
    secondary_dists[0].reset( new Utility::UnitAwareCoupledElasticDistribution<Utility::LinLin,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>( bin_boundaries, values, moliere_eta, cutoff_ratio ) );

    // Create the secondary distribution In the first bin
    Utility::setQuantity( values[0], 1.0 );
    Utility::setQuantity( values[1], 5.0 );
    Utility::setQuantity( values[2], 10.0 );

    Utility::setQuantity( primary_bins[1], 2.0 );
    secondary_dists[1].reset( new Utility::UnitAwareCoupledElasticDistribution<Utility::LinLin,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>( bin_boundaries, values, moliere_eta, cutoff_ratio ) );

    tab_dist.reset( new Utility::UnitAwareElasticTwoDDistribution<TwoDGridPolicy<Utility::LinLinLin>,typename BaseTabDistribution::PrimaryIndepUnit,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>(
        primary_bins, secondary_dists, cutoff, 1e-3, 1e-7 ) );

    dist = tab_dist;
  }
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  TEST_ASSERT( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous in the primary dimension
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  TEST_ASSERT( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous in the primary
// dimension
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary lower bound can be returned
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfPrimaryIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary lower bound can be
// returned
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfPrimaryIndepVar(), 1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary dimension upper bound can be returned
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfPrimaryIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary dimension upper bound can
// be returned
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfPrimaryIndepVar(), 2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional distribution can be returned
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   getLowerBoundOfConditionalIndepVar )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 0.0 ),
                       0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 0.0 ),
                       -1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 1.0 ),
                       -1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 1.5 ),
                       -1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 2.0 ),
                       -1.0 );

  // Beyond the second bin - no extension
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 3.0 ),
                       -1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional unit-aware distribution can be
// returned
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   getLowerBoundOfConditionalIndepVar )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 0.0*MeV ),
                       0.0*cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 0.0*MeV ),
                       -1.0*cgs::dimensionless() );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 1.0*MeV ),
                       -1.0*cgs::dimensionless() );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 1.5*MeV ),
                       -1.0*cgs::dimensionless() );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 2.0*MeV ),
                       -1.0*cgs::dimensionless() );

  // Beyond the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::dimensionless() );

  // Beyond the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 3.0*MeV ),
                       -1.0*cgs::dimensionless() );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional distribution can be returned
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   getUpperBoundOfConditionalIndepVar )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 0.0 ),
                       0.0 );
  
  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 0.0 ),
                       1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 1.0 ),
                       1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 1.5 ),
                       1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 2.0 ),
                       1.0 );

  // Beyond the second bin - no extension
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 3.0 ),
                       1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional unit-aware distribution can be
// returned
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   getUpperBoundOfConditionalIndepVar )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 0.0*MeV ),
                       0.0*cgs::dimensionless() );
  
  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 0.0*MeV ),
                       1.0*cgs::dimensionless() );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 1.0*MeV ),
                       1.0*cgs::dimensionless() );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 1.5*MeV ),
                       1.0*cgs::dimensionless() );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 2.0*MeV ),
                       1.0*cgs::dimensionless() );

  // Beyond the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::dimensionless() );

  // Beyond the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 3.0*MeV ),
                       1.0*cgs::dimensionless() );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the bounds of two distribution can be compared
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   hasSamePrimaryBounds )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  // Self test
  TEST_ASSERT( distribution->hasSamePrimaryBounds( *distribution ) );

  // Create a test distribution with same lower bound, different upper bound
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> test_dist;

  {
    Utility::FullyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 0.0;
    distribution_data[0].second.reset( new Utility::UniformDistribution( 0.1, 1.0, 0.1 ) );

    // Create the secondary distribution In the first bin
    distribution_data[1].first = 2.0;
    distribution_data[1].second = distribution_data[0].second;

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::UnitBase<Utility::LinLinLin> >(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *test_dist ) );

  // Create a test distribution with different lower bound, same upper bound
  {
    Utility::FullyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 1.0;
    distribution_data[0].second.reset( new Utility::UniformDistribution( 0.1, 1.0, 0.1 ) );

    // Create the secondary distribution In the first bin
    distribution_data[1].first = 3.0;
    distribution_data[1].second = distribution_data[0].second;

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::UnitBase<Utility::LinLinLin> >(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *test_dist ) );

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
    secondary_grids[0][1] = 1.0;   values[0][1] = 0.1;

    secondary_grids[1].resize( 3 ); values[1].resize( 3 );
    secondary_grids[1][0] = 0.1;    values[1][0] = 0.1;
    secondary_grids[1][1] = 0.5;    values[1][1] = 1.0;
    secondary_grids[1][2] = 1.0;    values[1][2] = 0.5;

    secondary_grids[2].resize( 2 ); values[2].resize( 2 );
    secondary_grids[2][0] = 0.1;    values[2][0] = 0.5;
    secondary_grids[2][1] = 1.0;    values[2][1] = 0.5;

    secondary_grids[3] = secondary_grids[0];
    values[3] = values[0];

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::UnitBase<Utility::LinLinLin> >(
                                                               primary_grid,
                                                               secondary_grids,
                                                               values ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *test_dist ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution, evaluate_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.0, -1.0 ), 0.09, 1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.0 ), 0.45 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.0, 0.999999 ), 0.9, 1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.0, 1.0 ), 9.00001800000899910e-01, 1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.0, -1.0 ), 0.09, 1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 0.0 ), 0.45 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.0, 0.999999 ), 0.9, 1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.0, 1.0 ), 9.00001800000899910e-01, 1e-15 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, -1.0 ),
                          0.495,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.0 ),
                          2.475,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.999999 ),
                          4.95,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 1.0 ),
                          4.95000990000494844878,
                          1e-15 );

  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( distribution->evaluate( 2.0, -1.0 ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 0.0 ), 4.5 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 2.0, 0.999999 ), 9.0, 1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 2.0, 1.0 ), 9.00001800000899910, 1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, -1.0 ), 0.9 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.0 ), 4.5 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.999999 ), 9.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 3.0, 1.0 ), 9.00001800000899910, 1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluate_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.09*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.45*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.9*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.00001800000899910e-1*barn,
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.09*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.45*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 0.9*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.0*MeV, 1.0*cgs::dimensionless() ), 9.00001800000899910e-1*barn, 1e-15 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  0.495*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.475*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  4.95*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  4.95000990000494844878*barn,
                                  1e-15 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.9*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 4.5*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 9.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 2.0*MeV, 1.0*cgs::dimensionless() ), 9.00001800000899910*barn, 1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.9*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 4.5*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 9.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 3.0*MeV, 1.0*cgs::dimensionless() ), 9.00001800000899910*barn, 1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution, evaluate_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 0.0, -1.0 ), 0.09, 1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, 0.0 ), 0.45 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, 0.999999 ), 0.9 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 0.0, 1.0 ), 9.00001800000899910e-01, 1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.0, -1.0 ), 0.09, 1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 1.0, 0.0 ), 0.45 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 1.0, 0.999999 ), 0.9 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.0, 1.0 ), 9.00001800000899910e-01, 1e-15 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, -1.0 ),
                          0.495,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.0 ),
                          2.475,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.999999 ),
                          4.95,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 1.0 ),
                          4.95000990000494844878,
                          1e-15 );

  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 2.0, -1.0 ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 2.0, 0.0 ), 4.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 2.0, 0.999999 ), 9.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 2.0, 1.0 ),
                          9.000018000008997987,
                          1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, -1.0 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, 0.0 ), 4.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, 0.999999 ), 9.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 3.0, 1.0 ),
                          9.000018000008997987,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluate_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.09*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.45*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.9*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 0.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987e-01*barn,
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.09*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.45*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 0.9*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987e-01*barn,
                                  1e-15 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  0.495*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.475*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  4.95*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  4.95000990000494844878*barn,
                                  1e-15 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.9*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 4.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 9.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987*barn,
                                  1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.9*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 4.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 9.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987*barn,
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution, evaluate_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 0.0, -1.0 ), 0.09, 1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, 0.0 ), 0.45 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 0.0, 0.999999 ), 0.9 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 0.0, 1.0 ), 9.00001800000899910e-01, 1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.0, -1.0 ), 0.09, 1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 1.0, 0.0 ), 0.45 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 1.0, 0.999999 ), 0.9 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.0, 1.0 ), 9.00001800000899910e-01, 1e-15 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, -1.0 ),
                          1.6363636363636364e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.0 ),
                          8.1818181818181812e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.999999 ),
                          1.6363636363636362,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 1.0 ),
                          1.6363669090925452,
                          1e-15 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 2.0, -1.0 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 2.0, 0.0 ), 4.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 2.0, 0.999999 ), 9.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 2.0, 1.0 ),
                          9.000018000008997987,
                          1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, -1.0 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, 0.0 ), 4.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluate( 3.0, 0.999999 ), 9.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 3.0, 1.0 ),
                          9.000018000008997987,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluate_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.09*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.45*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.9*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 0.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987e-01*barn,
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.09*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.45*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 0.9*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987e-01*barn,
                                  1e-15 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  1.6363636363636364e-01*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  8.1818181818181812e-01*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  1.6363636363636362*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  1.6363669090925452*barn,
                                  1e-15 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.9*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 4.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 9.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987*barn,
                                  1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.9*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 4.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 9.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluate( 3.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987*barn,
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDF_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ),
                          8.57143469388192414e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          4.28571734694096207e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ),
                          8.57143469388192414e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ),
                          8.57143469388192414e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ),
                          4.28571734694096207e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.999999 ),
                          8.57143469388192414e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, -1.0 ),
                          8.5714346938819227506e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.0 ),
                          0.42857173469409620692,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.999999 ),
                          0.85714346938819230282,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ),
                          8.57143469388192275e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ),
                          4.28571734694096151e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.999999 ),
                          8.57143469388192303e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ),
                          8.57143469388192275e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ),
                          4.28571734694096151e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ),
                          8.57143469388192303e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDF_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192414e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096207e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192414e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192414e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096207e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192414e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  8.5714346938819227506e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  0.42857173469409620692/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  0.85714346938819230282/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192275e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096151e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192303e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192275e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096151e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192303e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDF_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ),
                          8.57143469388192414e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          4.28571734694096207e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ),
                          8.57143469388192414e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ),
                          8.57143469388192414e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ),
                          4.28571734694096207e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.999999 ),
                          8.57143469388192414e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, -1.0 ),
                          8.5714346938819227506e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.0 ),
                          0.42857173469409620692,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.999999 ),
                          0.85714346938819230282,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );


  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ),
                          8.57143469388192275e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ),
                          4.28571734694096151e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.999999 ),
                          8.57143469388192303e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ),
                          8.57143469388192275e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ),
                          4.28571734694096151e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ),
                          8.57143469388192303e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDF_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192414e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096207e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192414e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192414e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096207e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192414e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  8.5714346938819227506e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  0.42857173469409620692/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  0.85714346938819230282/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192275e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096151e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192303e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192275e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096151e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192303e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDF_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ),
                          8.57143469388192414e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          4.28571734694096207e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ),
                          8.57143469388192414e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ),
                          8.57143469388192414e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ),
                          4.28571734694096207e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.999999 ),
                          8.57143469388192414e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, -1.0 ),
                          8.5714346938819227506e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.0 ),
                          0.42857173469409620692,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.999999 ),
                          0.85714346938819230282,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );


  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ),
                          8.57143469388192275e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ),
                          4.28571734694096151e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.999999 ),
                          8.57143469388192303e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ),
                          8.57143469388192275e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ),
                          4.28571734694096151e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ),
                          8.57143469388192303e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDF_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192414e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096207e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192414e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192414e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096207e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192414e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  8.5714346938819227506e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  0.42857173469409620692/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  0.85714346938819230282/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192275e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096151e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192303e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192275e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096151e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192303e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDF_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 1.0 ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 1.0 ), 1.0 );


  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 1.0 ), 1.0 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDF_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDF_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 1.0 ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 1.0 ), 1.0 );


  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 1.0 ), 1.0 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDF_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDF_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 1.0 ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 1.0 ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 1.0 ), 1.0 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDF_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditional_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.5; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 2.57143040816457724151e-01;
  fake_stream[11] = 0.49; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.49; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditional_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  quantity<cgs::dimensionless> sample =
                unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.5; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 2.57143040816457724151e-01;
  fake_stream[11] = 0.49; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.49; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  unsigned trials = 0u;

  // Before the first bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 1u );

  trials = 0u;

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.5; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 2.57143040816457724151e-01;
  fake_stream[11] = 0.49; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.49; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 6u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( trials, 7u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 8u );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  // After the second bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 5u );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  trials = 0u;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  unsigned trials = 0u;

  // Before the first bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 1u );

  trials = 0u;

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.5; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 2.57143040816457724151e-01;
  fake_stream[11] = 0.49; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.49; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 6u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 7u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 8u );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  // After the second bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 5u );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  trials = 0u;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  unsigned primary_bin_index = 0u, secondary_bin_index = 0u;

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.0;
  fake_stream[7] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.5; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.49; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.49; // use upper bin boundary
  fake_stream[15] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.0;
  fake_stream[7] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  unsigned primary_bin_index = 0u, secondary_bin_index = 0u;

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.0;
  fake_stream[7] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.5; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.49; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.49; // use upper bin boundary
  fake_stream[15] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.0;
  fake_stream[7] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  unsigned primary_bin_index = 0u, secondary_bin_index = 0u;
  double raw_sample;

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( raw_sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.0;
  fake_stream[7] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( raw_sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.5; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.49; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.49; // use upper bin boundary
  fake_stream[15] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( raw_sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( raw_sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.0;
  fake_stream[7] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( raw_sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( raw_sample, -1.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  unsigned primary_bin_index = 0u, secondary_bin_index = 0u;
  quantity<cgs::dimensionless> raw_sample;

//  // Before the first bin - no extension
//  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
//              std::logic_error );
//  TEST_EQUALITY_CONST( primary_bin_index, 0u );
//  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.0;
  fake_stream[7] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.5; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.49; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.49; // use upper bin boundary
  fake_stream[15] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.0;
  fake_stream[7] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( raw_sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalInSubrange_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0;
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.5; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 0.2;
  fake_stream[11] = 0.49; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.49; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0;
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalInSubrange_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-15 );

  // Beyond full range - check that expected range will be used
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0;
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.5; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 0.2;
  fake_stream[11] = 0.49; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.49; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0;
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_unit_base )
{
  initialize<Utility::UnitBase>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 2.57143040816457724151e-01, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.9, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 0.9),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_unit_base )
{
  initialize<Utility::UnitBase>( unit_aware_tab_distribution,
                                 unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-15 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 2.57143040816457724151e-01, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.9, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.49; // use upper bin boundary

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditional_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.5; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 2.57143040816457724151e-01;
  fake_stream[11] = 0.49; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.49; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditional_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  quantity<cgs::dimensionless> sample =
                unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.5; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 2.57143040816457724151e-01;
  fake_stream[11] = 0.49; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.49; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0; // Sample the bin boundary
  fake_stream[2] = 2.57143040816457724151e-01;
  fake_stream[3] = 0.0; // Sample the bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0; // Sample the bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0; // Sample the bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalInSubrange_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0;
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.5; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 0.2;
  fake_stream[11] = 0.49; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.49; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0;
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalInSubrange_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-15 );

  // Beyond full range - check that expected range will be used
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0;
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.5; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 0.2;
  fake_stream[11] = 0.49; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.49; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.0;
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF an be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_direct )
{
  initialize<Utility::Direct>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 2.57143040816457724151e-01, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.9, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 0.9),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF an be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_direct )
{
  initialize<Utility::Direct>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-15 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 2.57143040816457724151e-01, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.9, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditional_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditional( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditional_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.9 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalInSubrange_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.57143040816457724151e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalInSubrange_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-15 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.57143040816457724151e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_correlated )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 2.57143040816457724151e-01, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.9, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 0.9),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange_correlated )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-15 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 2.57143040816457724151e-01, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.9, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLinLinLinCoupledElasticTwoDDistribution.cpp
//---------------------------------------------------------------------------//
