//---------------------------------------------------------------------------//
//!
//! \file   tstLinLinLinInterpolatedFullyTabularTwoDDistribution.cpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular two-dimensional dist. unit tests
//!         (LinLinLin interpolation)
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
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"
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
std::shared_ptr<Utility::UnitAwareTwoDDistribution<MegaElectronVolt,cgs::length,Barn> >
  unit_aware_distribution;

std::shared_ptr<Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn> >
  unit_aware_tab_distribution;

std::shared_ptr<Utility::TwoDDistribution> distribution;

std::shared_ptr<Utility::FullyTabularTwoDDistribution> tab_distribution;

std::function<double (double)> lower_func, upper_func;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<typename TwoDSamplingPolicy,
         typename BaseTabDistribution,
         typename BaseDistribution>
void initialize( std::shared_ptr<BaseTabDistribution>& tab_dist,
                 std::shared_ptr<BaseDistribution>& dist )
{
  std::vector<typename BaseTabDistribution::PrimaryIndepQuantity> primary_bins( 4 );

  Teuchos::Array<std::shared_ptr<const Utility::UnitAwareTabularOneDDistribution<typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit> > > secondary_dists( 4 );

  // Create the secondary distribution in the first bin
  Utility::setQuantity( primary_bins[0], 0.0 );

  typename BaseTabDistribution::SecondaryIndepQuantity y_min, y_max;
  Utility::setQuantity( y_min, 0.0 );
  Utility::setQuantity( y_max, 10.0 );

  typename BaseTabDistribution::DepQuantity value;
  Utility::setQuantity( value, 0.1 );

  secondary_dists[0].reset( new Utility::UnitAwareUniformDistribution<typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>( y_min, y_max, value ) );

  // Create the secondary distribution in the second bin
  Utility::setQuantity( primary_bins[1], 0.0 );
  Utility::setQuantity( value, 1.0 );
  secondary_dists[1].reset( new Utility::UnitAwareUniformDistribution<typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>( y_min, y_max, value ) );

  // Create the secondary distribution in the third bin
  Teuchos::Array<typename BaseTabDistribution::SecondaryIndepQuantity> bin_boundaries( 3 );
  Utility::setQuantity( bin_boundaries[0], 2.5 );
  Utility::setQuantity( bin_boundaries[1], 5.0 );
  Utility::setQuantity( bin_boundaries[2], 7.5 );

  Teuchos::Array<typename BaseTabDistribution::DepQuantity> values( 3 );
  Utility::setQuantity( values[0], 0.1 );
  Utility::setQuantity( values[1], 1.0 );
  Utility::setQuantity( values[2], 0.5 );

  Utility::setQuantity( primary_bins[2], 1.0 );
  secondary_dists[2].reset( new Utility::UnitAwareTabularDistribution<Utility::LinLin,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>( bin_boundaries, values ) );

  // Create the secondary distribution beyond the third bin
  Utility::setQuantity( primary_bins[3], 2.0 );
  secondary_dists[3] = secondary_dists[0];

  tab_dist.reset( new Utility::UnitAwareInterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin,TwoDSamplingPolicy,typename BaseTabDistribution::PrimaryIndepUnit,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>(
      primary_bins, secondary_dists, 1e-3, 1e-7 ) );

  dist = tab_dist;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );
  TEST_ASSERT( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous in the primary dimension
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );
  TEST_ASSERT( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous in the primary
// dimension
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary lower bound can be returned
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfPrimaryIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary lower bound can be
// returned
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfPrimaryIndepVar(), 0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary dimension upper bound can be returned
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfPrimaryIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary dimension upper bound can
// be returned
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfPrimaryIndepVar(), 2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional distribution can be returned
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   getLowerBoundOfConditionalIndepVar )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar(-1.0),
                       0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar(-1.0),
                       0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 0.0 ),
                       0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 0.5 ),
                       1.25 );

  // On the third bin
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 1.0 ),
                       2.5 );

  // On the fourth bin
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 1.5 ),
                       1.25 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 2.0 ),
                       0.0 );

  // Beyond the third bin - no extension
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 3.0 ),
                       0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional unit-aware distribution can be
// returned
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   getLowerBoundOfConditionalIndepVar )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar(-1.0*MeV),
                       0.0*cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar(-1.0*MeV),
                       0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 0.0*MeV ),
                       0.0*cgs::centimeter );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 0.5*MeV ),
                       1.25*cgs::centimeter );

  // On the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 1.0*MeV ),
                       2.5*cgs::centimeter );

  // On the fourth bin
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 1.5*MeV ),
                       1.25*cgs::centimeter );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 2.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional distribution can be returned
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   getUpperBoundOfConditionalIndepVar )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar(-1.0),
                       0.0 );
  
  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar(-1.0),
                       10.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 0.0 ),
                       10.0 );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 0.5 ),
                       8.75 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 1.0 ),
                       7.5 );

  // In the third bin
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 1.5 ),
                       8.75 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 2.0 ),
                       10.0 );

  // Beyond the third bin - no extension
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 3.0 ),
                       10.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional unit-aware distribution can be
// returned
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   getUpperBoundOfConditionalIndepVar )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar(-1.0*MeV),
                       0.0*cgs::centimeter );
  
  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar(-1.0*MeV),
                       10.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 0.0*MeV ),
                       10.0*cgs::centimeter );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 0.5*MeV ),
                       8.75*cgs::centimeter );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 1.0*MeV ),
                       7.5*cgs::centimeter );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 1.5*MeV ),
                       8.75*cgs::centimeter );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 2.0*MeV ),
                       10.0*cgs::centimeter );

  // Beyond the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 3.0*MeV ),
                       10.0*cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the bounds of two distribution can be compared
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   hasSamePrimaryBounds )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Self test
  TEST_ASSERT( distribution->hasSamePrimaryBounds( *distribution ) );

  // Create a test distribution with same lower bound, different upper bound
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> test_dist;

  {
    Utility::FullyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 0.0;
    distribution_data[0].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );
    
    // Create the secondary distribution in the second bin
    distribution_data[1].first = 1.0;
    distribution_data[1].second = distribution_data[0].second;

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin,Utility::Stochastic>(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *test_dist ) );

  // Create a test distribution with different lower bound, same upper bound
  {
    Utility::FullyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 1.0;
    distribution_data[0].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );
    
    // Create the secondary distribution in the second bin
    distribution_data[1].first = 2.0;
    distribution_data[1].second = distribution_data[0].second;

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin,Utility::Stochastic>(
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
    secondary_grids[0][0] = 0.0;    values[0][0] = 0.1;
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

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin,Utility::Stochastic>(
                                                               primary_grid,
                                                               secondary_grids,
                                                               values ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *test_dist ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution, evaluate )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 5.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 11.0 ), 0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.5, 1.25 ),
                          0.7,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.5, 5.0 ),
                          1.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.5, 8.75 ),
                          0.8333333333333334,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, 9.0 ), 0.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 2.5 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 5.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 7.5 ), 0.5 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 8.0 ), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.5, 1.25 ),
                          0.1,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.5, 5.0 ),
                          0.4,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.5, 8.75 ),
                          0.23333333333333334,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 9.0 ), 0.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 11.0 ), 0.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   evaluate )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 5.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV, 1.0*cgs::centimeter ), 0.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 1.25*cgs::centimeter ),
                                  0.7*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 5.0*cgs::centimeter ),
                                  1.0*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 8.75*cgs::centimeter ),
                                  0.8333333333333334*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV, 9.0*cgs::centimeter ), 0.0*barn );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 0.5*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 1.25*cgs::centimeter ),
                                  0.1*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 5.0*cgs::centimeter ),
                                  0.4*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 8.75*cgs::centimeter ),
                                  0.23333333333333334*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.0*barn );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution, evaluateExact )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( -1.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( -1.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( -1.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( -1.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( -1.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( -1.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 5.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 11.0 ), 0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 0.5, 1.25 ),
                          0.55,
                          1e-16 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 0.5, 5.0 ),
                          0.98085546162288850258,
                          1e-6 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 0.5, 8.75 ),
                          0.75,
                          1e-16 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.5, 9.0 ), 0.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.0, 2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.0, 2.5 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.0, 5.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.0, 7.5 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.0, 8.0 ), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.5, 1.25 ),
                          0.1,
                          1e-16 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.5, 5.0 ),
                          0.53085546162288843597,
                          1e-6 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.5, 8.75 ),
                          0.3,
                          1e-16 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.5, 9.0 ), 0.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 2.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 2.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 2.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 2.0, 11.0 ), 0.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   evaluateExact )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( -1.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( -1.0*MeV, 5.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( -1.0*MeV, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( -1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( -1.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( -1.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( -1.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( -1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 10.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.5*MeV, 1.0*cgs::centimeter ), 0.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 0.5*MeV, 1.25*cgs::centimeter ),
                                  0.55*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 0.5*MeV, 5.0*cgs::centimeter ),
                                  0.98085546162288850258*barn,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 0.5*MeV, 8.75*cgs::centimeter ),
                                  0.75*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.5*MeV, 9.0*cgs::centimeter ), 0.0*barn );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, 2.5*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, 7.5*cgs::centimeter ), 0.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, 1.0*cgs::centimeter ), 0.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, 1.25*cgs::centimeter ),
                                  0.1*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, 5.0*cgs::centimeter ),
                                  0.53085546162288843597*barn,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, 8.75*cgs::centimeter ),
                                  0.3*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, 9.0*cgs::centimeter ), 0.0*barn );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 5.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution, correlatedEvaluate )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( -1.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( -1.0, 0.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( -1.0, 5.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( -1.0, 10.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( -1.0, 11.0, 0.0, 10.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( -1.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( -1.0, 0.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( -1.0, 5.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( -1.0, 10.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( -1.0, 11.0, 0.0, 10.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 0.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 0.0, 0.0, 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 0.0, 5.0, 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 0.0, 10.0, 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 0.0, 11.0, 0.0, 10.0 ), 0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 0.5, 1.0, 1.25, 8.75 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateInBoundaries( 0.5, 1.25, 1.25, 8.75 ),
                          0.55,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateInBoundaries( 0.5, 5.0, 1.25, 8.75 ),
                          0.98470673703508238006,
                          1e-6 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateInBoundaries( 0.5, 8.75, 1.25, 8.75 ),
                          0.75,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 0.5, 9.0, 1.25, 8.75 ), 0.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 1.0, 2.0, 1.25, 8.75 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 1.0, 2.5, 1.25, 8.75 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 1.0, 5.0, 1.25, 8.75 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 1.0, 7.5, 1.25, 8.75 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 1.0, 8.0, 1.25, 8.75 ), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 1.5, 1.0, 1.25, 8.75 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateInBoundaries( 1.5, 1.25, 1.25, 8.75 ),
                          0.1,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateInBoundaries( 1.5, 5.0, 1.25, 8.75 ),
                          0.53470673703508242447,
                          1e-6 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateInBoundaries( 1.5, 8.75, 1.25, 8.75 ),
                          0.3,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 1.5, 9.0, 1.25, 8.75 ), 0.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 2.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 2.0, 0.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 2.0, 5.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 2.0, 10.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 2.0, 11.0, 0.0, 10.0 ), 0.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 3.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 3.0, 0.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 3.0, 5.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 3.0, 10.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 3.0, 11.0, 0.0, 10.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 3.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 3.0, 0.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 3.0, 5.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 3.0, 10.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateInBoundaries( 3.0, 11.0, 0.0, 10.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   correlatedEvaluate )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( -1.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( -1.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( -1.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( -1.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( -1.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( -1.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( -1.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( -1.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 0.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 0.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 0.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 0.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 0.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 0.5*MeV, 1.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 0.5*MeV, 1.25*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.55*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 0.5*MeV, 5.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.98470673703508238006*barn,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 0.5*MeV, 8.75*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.75*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 0.5*MeV, 9.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0*barn );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 1.0*MeV, 2.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 1.0*MeV, 2.5*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 1.0*MeV, 5.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 1.0*MeV, 7.5*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 1.0*MeV, 8.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0*barn );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 1.5*MeV, 1.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 1.5*MeV, 1.25*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.1*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 1.5*MeV, 5.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.53470673703508242447*barn,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 1.5*MeV, 8.75*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.3*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 1.5*MeV, 9.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0*barn );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 2.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 2.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 2.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 2.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 2.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 3.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 3.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 3.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 3.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 3.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 3.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 3.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 3.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 3.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateInBoundaries( 3.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   evaluateSecondaryConditionalPDF )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, 11.0 ), 0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 1.25 ),
                          0.07692307692307691,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 5.0 ),
                          0.1692307692307692,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 8.75 ),
                          0.11794871794871795,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.5, 9.0 ), 0.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 2.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.0, 2.5 ),
                          0.03076923076923077,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.0, 5.0 ),
                          0.3076923076923077,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.0, 7.5 ),
                          0.15384615384615385,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 8.0 ), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.5, 1.25 ),
                          0.07692307692307691,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.5, 5.0 ),
                          0.1692307692307692,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.5, 8.75 ),
                          0.11794871794871795,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, 9.0 ), 0.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, 11.0 ), 0.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   evaluateSecondaryConditionalPDF )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 5.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 1.25*cgs::centimeter ),
                                  0.07692307692307691/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 5.0*cgs::centimeter ),
                                  0.1692307692307692/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 8.75*cgs::centimeter ),
                                  0.11794871794871795/cgs::centimeter,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 9.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 2.0*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 2.5*cgs::centimeter ),
                                  0.03076923076923077/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 5.0*cgs::centimeter ),
                                  0.3076923076923077/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 7.5*cgs::centimeter ),
                                  0.15384615384615385/cgs::centimeter,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 8.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.25*cgs::centimeter ),
                                  0.07692307692307691/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 5.0*cgs::centimeter ),
                                  0.1692307692307692/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 8.75*cgs::centimeter ),
                                  0.11794871794871795/cgs::centimeter,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 9.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 5.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   evaluateSecondaryConditionalPDFExact )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 11.0 ), 0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5, 1.25 ),
                          6.53846153846153882e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5, 5.0 ),
                          0.19795552665319648966,
                          1e-6 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5, 8.75 ),
                          1.26923076923076916e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5, 9.0 ), 0.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, 2.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, 2.5 ),
                          0.03076923076923077,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, 5.0 ),
                          0.3076923076923077,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, 7.5 ),
                          0.15384615384615385,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, 8.0 ), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5, 1.0 ), 0.00 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5, 1.25 ),
                          6.53846153846153882e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5, 5.0 ),
                          0.19795552665319648966,
                          1e-6 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5, 8.75 ),
                          1.26923076923076916e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5, 9.0 ), 0.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, 11.0 ), 0.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 11.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   evaluateSecondaryConditionalPDFExact )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0*MeV, 5.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0*MeV, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( -1.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5*MeV, 1.25*cgs::centimeter ),
                                  6.53846153846153882e-02/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5*MeV, 5.0*cgs::centimeter ),
                                  0.19795552665319648966/cgs::centimeter,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5*MeV, 8.75*cgs::centimeter ),
                                  1.26923076923076916e-01/cgs::centimeter,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.5*MeV, 9.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, 2.0*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, 2.5*cgs::centimeter ),
                                  0.03076923076923077/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, 5.0*cgs::centimeter ),
                                  0.3076923076923077/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, 7.5*cgs::centimeter ),
                                  0.15384615384615385/cgs::centimeter,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, 8.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, 1.25*cgs::centimeter ),
                                  6.53846153846153882e-02/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, 5.0*cgs::centimeter ),
                                  0.19795552665319648966/cgs::centimeter,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, 8.75*cgs::centimeter ),
                                  1.26923076923076916e-01/cgs::centimeter,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, 9.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 5.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalPDF )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0, 0.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0, 5.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0, 10.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0, 11.0, 0.0, 10.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0, 0.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0, 5.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0, 10.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0, 11.0, 0.0, 10.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.0, 0.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.0, 5.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.0, 10.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.0, 11.0, 0.0, 10.0 ), 0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.5, 1.0, 1.25, 8.75 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.5, 1.25, 1.25, 8.75 ),
                          6.53846153846154E-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.5, 5.0, 1.25, 8.75 ),
                          0.19914053447233304173,
                          1e-6 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.5, 8.75, 1.25, 8.75 ),
                          1.26923076923077E-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.5, 9.0, 1.25, 8.75 ), 0.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.0, 2.0, 1.25, 8.75 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.0, 2.5, 1.25, 8.75 ),
                          0.03076923076923077,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.0, 5.0, 1.25, 8.75 ),
                          0.3076923076923077,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.0, 7.5, 1.25, 8.75 ),
                          0.15384615384615385,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.0, 8.0, 1.25, 8.75 ), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.5, 1.0, 1.25, 8.75 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.5, 1.25, 1.25, 8.75 ),
                          6.53846153846154E-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.5, 5.0, 1.25, 8.75 ),
                          0.19914053447233304173,
                          1e-6 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.5, 8.75, 1.25, 8.75 ),
                          1.26923076923077E-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.5, 9.0, 1.25, 8.75 ), 0.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 2.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 2.0, 0.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 2.0, 5.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 2.0, 10.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 2.0, 11.0, 0.0, 10.0 ), 0.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0, 0.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0, 5.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0, 10.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0, 11.0, 0.0, 10.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0, 0.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0, 5.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0, 10.0, 0.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0, 11.0, 0.0, 10.0 ), 0.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalPDF )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( -1.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.5*MeV, 1.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.5*MeV, 1.25*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  6.53846153846154E-02/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.5*MeV, 5.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.19914053447233304173/cgs::centimeter,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.5*MeV, 8.75*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  1.26923076923077E-01/cgs::centimeter,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 0.5*MeV, 9.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0/cgs::centimeter );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.0*MeV, 2.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.0*MeV, 2.5*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.03076923076923077/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.0*MeV, 5.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.3076923076923077/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.0*MeV, 7.5*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.15384615384615385/cgs::centimeter,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.0*MeV, 8.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.5*MeV, 1.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.5*MeV, 1.25*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  6.53846153846154E-02/cgs::centimeter,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.5*MeV, 5.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  0.19914053447233304173/cgs::centimeter,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.5*MeV, 8.75*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                                  1.26923076923077E-01/cgs::centimeter,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 1.5*MeV, 9.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0/cgs::centimeter );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 2.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 2.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 2.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 2.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 2.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDFInBoundaries( 3.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   evaluateSecondaryConditionalCDF )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( -1.0, 11.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 11.0 ), 1.0 );

  // In the second bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.5, 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.5, 1.25 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 0.5, 5.0 ),
                          0.47435897435897434,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.5, 8.75 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.5, 9.0 ), 1.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 2.5 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 5.0 ),
                          0.4230769230769231,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 7.5 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 8.0 ), 1.0 );

  // In the third bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 1.25 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 5.0 ),
                          0.47435897435897434,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 8.75 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 9.0 ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 11.0 ), 1.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 11.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   evaluateSecondaryConditionalCDF )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 5.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 11.0*cgs::centimeter ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( -1.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.5*MeV, 1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.5*MeV, 1.25*cgs::centimeter ), 0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.5*MeV, 5.0*cgs::centimeter ),
                          0.47435897435897434,
                          1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.5*MeV, 8.75*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.5*MeV, 9.0*cgs::centimeter ), 1.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 2.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 2.5*cgs::centimeter ), 0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 5.0*cgs::centimeter ),
                          0.4230769230769231,
                          1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 7.5*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 8.0*cgs::centimeter ), 1.0 );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 1.25*cgs::centimeter ), 0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 5.0*cgs::centimeter ),
                          0.47435897435897434,
                          1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 8.75*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 9.0*cgs::centimeter ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 5.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 11.0*cgs::centimeter ), 0.0 );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   evaluateSecondaryConditionalCDFExact )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0, 11.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 11.0 ), 1.0 );

  // In the second bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.5, 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.5, 1.25 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.5, 5.0 ),
                          0.48085546162288905769,
                          1e-6 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.5, 8.75 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.5, 9.0 ), 1.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, 2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, 2.5 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, 5.0 ),
                          0.4230769230769231,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, 7.5 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, 8.0 ), 1.0 );

  // In the third bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, 1.25 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, 5.0 ),
                          0.48085546162288905769,
                          1e-6 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, 8.75 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, 9.0 ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, 11.0 ), 1.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 11.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   evaluateSecondaryConditionalCDFExact )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0*MeV, 5.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0*MeV, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0*MeV, 11.0*cgs::centimeter ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( -1.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.5*MeV, 1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.5*MeV, 1.25*cgs::centimeter ), 0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.5*MeV, 5.0*cgs::centimeter ),
                          0.48085546162288905769,
                          1e-6 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.5*MeV, 8.75*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.5*MeV, 9.0*cgs::centimeter ), 1.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, 2.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, 2.5*cgs::centimeter ), 0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, 5.0*cgs::centimeter ),
                          0.4230769230769231,
                          1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, 7.5*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, 8.0*cgs::centimeter ), 1.0 );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, 1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, 1.25*cgs::centimeter ), 0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, 5.0*cgs::centimeter ),
                          0.48085546162288905769,
                          1e-6 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, 8.75*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, 9.0*cgs::centimeter ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 5.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 11.0*cgs::centimeter ), 0.0 );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalCDF )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0, 0.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0, 5.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0, 10.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0, 11.0, 0.0, 10.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0, 0.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0, 5.0, 0.0, 10.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0, 10.0, 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0, 11.0, 0.0, 10.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.0, 0.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.0, 5.0, 0.0, 10.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.0, 10.0, 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.0, 11.0, 0.0, 10.0 ), 1.0 );

  // In the second bin
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.5, 1.0, 1.25, 8.75 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.5, 1.25, 1.25, 8.75 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.5, 5.0, 1.25, 8.75 ),
                          0.4694134740701646491,
                          1e-6 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.5, 8.75, 1.25, 8.75 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.5, 9.0, 1.25, 8.75 ), 1.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.0, 2.0, 1.25, 8.75 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.0, 2.5, 1.25, 8.75 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.0, 5.0, 1.25, 8.75 ),
                          0.4230769230769231,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.0, 7.5, 1.25, 8.75 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.0, 8.0, 1.25, 8.75 ), 1.0 );

  // In the third bin
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.5, 1.0, 1.25, 8.75 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.5, 1.25, 1.25, 8.75 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.5, 5.0, 1.25, 8.75 ),
                          0.4694134740701646491,
                          1e-6 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.5, 8.75, 1.25, 8.75 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.5, 9.0, 1.25, 8.75 ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 2.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 2.0, 0.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 2.0, 5.0, 0.0, 10.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 2.0, 10.0, 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 2.0, 11.0, 0.0, 10.0 ), 1.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0, 0.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0, 5.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0, 10.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0, 11.0, 0.0, 10.0 ), 0.0 );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0, -1.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0, 0.0, 0.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0, 5.0, 0.0, 10.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0, 10.0, 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0, 11.0, 0.0, 10.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalCDF )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( -1.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0 );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.5*MeV, 1.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.5*MeV, 1.25*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.5*MeV, 5.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                          0.4694134740701646491,
                          1e-6 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.5*MeV, 8.75*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 0.5*MeV, 9.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 1.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.0*MeV, 2.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.0*MeV, 2.5*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.0*MeV, 5.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                          0.4230769230769231,
                          1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.0*MeV, 7.5*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.0*MeV, 8.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 1.0 );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.5*MeV, 1.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.5*MeV, 1.25*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.5*MeV, 5.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ),
                          0.4694134740701646491,
                          1e-6 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.5*MeV, 8.75*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 1.5*MeV, 9.0*cgs::centimeter, 1.25*cgs::centimeter, 8.75*cgs::centimeter ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 2.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 2.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 2.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 2.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 2.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0*MeV, -1.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0*MeV, 0.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0*MeV, 5.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0*MeV, 10.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDFInBoundaries( 3.0*MeV, 11.0*cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditional )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditional( -1.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = distribution->sampleSecondaryConditional( -1.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( -1.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( -1.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

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

  sample = distribution->sampleSecondaryConditional( 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0; 
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // Samples from upper boundary of third bin
  sample = distribution->sampleSecondaryConditional( 1.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

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

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 3.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditional )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  quantity<cgs::length> sample =
    unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

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

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0; 
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of third bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

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

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  unsigned trials = 0u;
  
  // Before the first bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );
  TEST_EQUALITY_CONST( trials, 3u );

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

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6u );

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
  
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  TEST_EQUALITY_CONST( sample, 2.5 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );
  TEST_EQUALITY_CONST( trials, 3u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0; 
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  // Samples from upper boundary of third bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6u );

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

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  // After the third bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  unsigned trials = 0u;
  
  // Before the first bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  quantity<cgs::length> sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );
  TEST_EQUALITY_CONST( trials, 3u );

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

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6u );

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
  
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( trials, 3u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0; 
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  // Samples from upper boundary of third bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6u );

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

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  // After the third bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  unsigned primary_bin_index = 0u, secondary_bin_index = 0u;
  
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

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

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 2.5 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0; 
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // Samples from upper boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  unsigned primary_bin_index = 0u, secondary_bin_index = 0u;
  
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

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

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0; 
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // Samples from upper boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  unsigned primary_bin_index = 0u, secondary_bin_index = 0u;
  double raw_sample;
  
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-12 ); 
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

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

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 2.5 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 7.5, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 2.5 );
  TEST_EQUALITY_CONST( raw_sample, 2.5 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 7.5, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0; 
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 2.5 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 7.5, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // Samples from upper boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  unsigned primary_bin_index = 0u, secondary_bin_index = 0u;
  quantity<cgs::length> raw_sample;
  
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( -1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-12 ); 
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

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

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 2.5*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 2.5*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0; 
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 2.5*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 2u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // Samples from upper boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.5*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 2.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 3u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // In the second bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.49; // use upper bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5, 0.4230769230769231 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // On the third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );

  TEST_EQUALITY_CONST( sample, 2.5 );
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.4230769230769231 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.49; // use upper bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.4230769230769231 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // Samples from upper boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0*MeV, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0*MeV, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( -1.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // In the second bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.49; // use upper bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5*MeV, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5*MeV, 0.4230769230769231 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.5*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // On the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.4230769230769231 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.49; // use upper bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.4230769230769231 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalInSubrange )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( -1.0, 7.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalInSubrange( -1.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( -1.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( -1.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( -1.0, 11.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( -1.0, 11.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( -1.0, 11.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

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
  
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.49; // use upper bin boundary
  fake_stream[8] = 0.49748743718592964;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 4.375, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.4230769230769231;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.49748743718592964;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.49; // use upper bin boundary
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from upper boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 4.375, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 7.5 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalInSubrange )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( -1.0*MeV, 7.5*cgs::centimeter ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( -1.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( -1.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( -1.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( -1.0*MeV, 11.0*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( -1.0*MeV, 11.0*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( -1.0*MeV, 11.0*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

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
  
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // In the second bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.49; // use upper bin boundary
  fake_stream[8] = 0.49748743718592964;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.5*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.375*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.5*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // On the third bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.4230769230769231;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.49748743718592964;
  fake_stream[3] = 0.5; // use lower bin boundary
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.5; // use lower bin boundary
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.49; // use upper bin boundary
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.49; // use upper bin boundary
  fake_stream[10] = 1.0-1e-15;
  fake_stream[11] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.375*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.0;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 7.5*cgs::centimeter ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange )
{ 
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0, 0.0, 7.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0, 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0, 0.0, 11.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0, 0.5, 11.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0, 1.0-1e-15, 11.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin  
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // In the second bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.49; // use upper bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5, 0.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 4.375, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5, 0.49748743718592964, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.4230769230769231, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.49; // use upper bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.49748743718592964, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from upper boundary of third bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 4.375, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 7.5 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange )
{ 
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0*MeV, 0.0, 7.5*cgs::centimeter ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0*MeV, 0.0, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0*MeV, 0.5, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0*MeV, 0.0, 11.0*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0*MeV, 0.5, 11.0*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( -1.0*MeV, 1.0-1e-15, 11.0*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin  
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // In the second bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.49; // use upper bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5*MeV, 0.0, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5*MeV, 0.5, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.375*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5*MeV, 0.0, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5*MeV, 0.49748743718592964, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.5*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.4230769230769231, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.5; // use lower bin boundary
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.49; // use upper bin boundary
  fake_stream[4] = 0.49; // use upper bin boundary
  fake_stream[5] = 0.49; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.49748743718592964, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.5, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.375*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.5, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.0, 7.5*cgs::centimeter ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.0, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalExact )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExact( -1.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditionalExact( -1.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( -1.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( -1.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExact( 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 0.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 0.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  // In the second bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExact( 0.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 0.5 );

  TEST_FLOATING_EQUALITY( sample, 4.615384615384615, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 0.5 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-12 );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.0 );

  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.0 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.0 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.5 );

  TEST_FLOATING_EQUALITY( sample, 4.615384615384615, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.5 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-12 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExact( 2.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 2.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 2.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExact( 3.0 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExact( 3.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 3.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 3.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalExact )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExact( -1.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( -1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( -1.0*MeV );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( -1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  // In the second bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.5*MeV );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.615384615384615*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-12 );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.615384615384615*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-12 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExact( 3.0*MeV ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumber )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( -1.0, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  double sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( -1.0, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( -1.0, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( -1.0, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  // In the second bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.5, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.5, 0.4230769230769231 );

  TEST_FLOATING_EQUALITY( sample, 4.615384615384615, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.5, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-12 );

  // On the third bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0, 0.0 );

  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0, 0.4230769230769231 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // In the third bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5, 0.4230769230769231 );

  TEST_FLOATING_EQUALITY( sample, 4.615384615384615, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-12 );

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0, 0.0 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0, 1.0-1e-15 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumber )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( -1.0*MeV, 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( -1.0*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( -1.0*MeV, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( -1.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0*MeV, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  // In the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.5*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.5*MeV, 0.4230769230769231 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.615384615384615*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.5*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-12 );

  // On the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0*MeV, 0.4230769230769231 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // In the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5*MeV, 0.4230769230769231 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.615384615384615*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-12 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0*MeV, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0*MeV, 0.0 ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0*MeV, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0*MeV, 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalExactInSubrange )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0, 7.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // Full Range
  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0, 11.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0, 11.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0, 11.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // In the second bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 4.5032917548737154689, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // On the third bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // In the third bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 4.5032917548737154689, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0, 7.5 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalExactInSubrange )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0*MeV, 7.5*cgs::centimeter ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // Full Range
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0*MeV, 11.0*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0*MeV, 11.0*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( -1.0*MeV, 11.0*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // In the second bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.5*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.5032917548737154689*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // On the third bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // In the third bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.5032917548737154689*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0*MeV, 7.5*cgs::centimeter ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0*MeV, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0*MeV, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF an be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumberInSubrange )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0, 0.0, 7.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 3 );

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0, 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // Full Range
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0, 0.0, 11.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0, 0.5, 11.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0, 1.0-1e-15, 11.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // In the second bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.5, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.5, 0.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 4.5032917548737154689, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.5, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // On the third bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0, 0.4230769230769231, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // In the third bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5, 0.5, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 4.5032917548737154689, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0, 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0, 0.0, 7.5 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0, 0.0, 7.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0, 0.5, 7.5 );

  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 7.5 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF an be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumberInSubrange )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0*MeV, 0.0, 7.5*cgs::centimeter ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 3 );


  // Subrange
  quantity<cgs::length> sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0*MeV, 0.0, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0*MeV, 0.5, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );


  // Full Range
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0*MeV, 0.0, 11.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0*MeV, 0.5, 11.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( -1.0*MeV, 1.0-1e-15, 11.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();


  // On the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 0.0, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 0.5, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );


  // In the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.5*MeV, 0.0, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.5*MeV, 0.5, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.5032917548737154689*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.5*MeV, 1.0-1e-15, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );


  // On the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0*MeV, 0.0, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0*MeV, 0.4230769230769231, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );


  // In the third bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5*MeV, 0.0, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5*MeV, 0.5, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.5032917548737154689*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );


  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0*MeV, 0.0, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0*MeV, 0.5, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );


  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0*MeV, 0.0, 7.5*cgs::centimeter ),
              std::logic_error );


  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0*MeV, 0.0, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0*MeV, 0.5, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   correlatedSampleSecondaryConditional )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( -1.0, lower_func, upper_func ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  lower_func = [](double x){return 0.0;}; upper_func = [](double x){return 10.0;};
  double sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( -1.0, lower_func, upper_func );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( -1.0, lower_func, upper_func );
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( -1.0, lower_func, upper_func );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();


  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 0.0, lower_func, upper_func );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 0.0, lower_func, upper_func );
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 0.0, lower_func, upper_func );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );


  // In the second bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  lower_func = [](double x){return 1.25;}; upper_func = [](double x){return 8.75;};

  sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 0.5, lower_func, upper_func );
  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 0.5, lower_func, upper_func );
  TEST_FLOATING_EQUALITY( sample, 4.711538461538, 1e-12 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 0.5, lower_func, upper_func );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-12 );


  // // On the third bin
  // Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 1.0, 2.5, 7.5 );
  // TEST_EQUALITY_CONST( sample, 2.5 );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 1.0, 2.5, 7.5 );
  // TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 1.0, 2.5, 7.5 );
  // TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );


  // // In the third bin
  // Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 1.5, lower_func, upper_func );
  // TEST_EQUALITY_CONST( sample, 1.25 );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 1.5, lower_func, upper_func );
  // TEST_FLOATING_EQUALITY( sample, 4.711538461538, 1e-12 );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 1.5, lower_func, upper_func );
  // TEST_FLOATING_EQUALITY( sample, 8.75, 1e-12 );


  // // On the upper bin boundary
  // fake_stream[0] = 0.0;
  // fake_stream[1] = 0.5;
  // fake_stream[2] = 1.0-1e-15;
  // Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 2.0, 0.0, 10.0 );
  // TEST_EQUALITY_CONST( sample, 0.0 );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 2.0, 0.0, 10.0 );
  // TEST_EQUALITY_CONST( sample, 5.0 );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 2.0, 0.0, 10.0 );
  // TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  // // After the third bin - no extension
  // TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 3.0, 0.0, 10.0 ),
  //             std::logic_error );


  // // After the third bin - with extension
  // tab_distribution->extendBeyondPrimaryIndepLimits();

  // Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 3.0, 0.0, 10.0 );
  // TEST_EQUALITY_CONST( sample, 0.0 );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 3.0, 0.0, 10.0 );
  // TEST_EQUALITY_CONST( sample, 5.0 );

  // sample = tab_distribution->correlatedSampleSecondaryConditionalInBoundaries( 3.0, 0.0, 10.0 );
  // TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  // tab_distribution->limitToPrimaryIndepLimits();

  // Utility::RandomNumberGenerator::unsetFakeStream();
}

// //---------------------------------------------------------------------------//
// // Check that a unit-aware secondary conditional PDF can be sampled
// TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
//                    correlatedSampleSecondaryConditional )
// {
//   initialize<Utility::Correlated>( unit_aware_tab_distribution,
//                                    unit_aware_distribution );

//   // Before the first bin - no extension
//   TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//               -1.0*MeV,
//               0.0*cgs::centimeter,
//               10.0*cgs::centimeter ),
//               std::logic_error );


//   // Before the first bin - with extension
//   unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
//   std::vector<double> fake_stream( 3 );
//   fake_stream[0] = 0.0;
//   fake_stream[1] = 0.5;
//   fake_stream[2] = 1.0-1e-15;
//   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//   quantity<cgs::length> sample =
//     unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         -1.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         -1.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         -1.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

//   unit_aware_tab_distribution->limitToPrimaryIndepLimits();


//   // On the second bin
//   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         0.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         0.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         0.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );


//   // In the second bin
//   fake_stream[0] = 0.0;
//   fake_stream[1] = 0.4230769230769231;
//   fake_stream[2] = 1.0-1e-15;
//   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         0.5*MeV,
//                         1.25*cgs::centimeter,
//                         8.75*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         0.5*MeV,
//                         1.25*cgs::centimeter,
//                         8.75*cgs::centimeter );
//   UTILITY_TEST_FLOATING_EQUALITY( sample, 4.711538461538*cgs::centimeter, 1e-12 );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         0.5*MeV,
//                         1.25*cgs::centimeter,
//                         8.75*cgs::centimeter );
//   UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-12 );


//   // On the third bin
//   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         1.0*MeV,
//                         2.5*cgs::centimeter,
//                         7.5*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         1.0*MeV,
//                         2.5*cgs::centimeter,
//                         7.5*cgs::centimeter );
//   UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-12 );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         1.0*MeV,
//                         2.5*cgs::centimeter,
//                         7.5*cgs::centimeter );
//   UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );


//   // In the third bin
//   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         1.5*MeV,
//                         1.25*cgs::centimeter,
//                         8.75*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         1.5*MeV,
//                         1.25*cgs::centimeter,
//                         8.75*cgs::centimeter );
//   UTILITY_TEST_FLOATING_EQUALITY( sample, 4.711538461538*cgs::centimeter, 1e-12 );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         1.5*MeV,
//                         1.25*cgs::centimeter,
//                         8.75*cgs::centimeter );
//   UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-12 );


//   // On the upper bin boundary
//   fake_stream[0] = 0.0;
//   fake_stream[1] = 0.5;
//   fake_stream[2] = 1.0-1e-15;
//   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         2.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         2.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         2.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );


//   // After the third bin - no extension
//   TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//               3.0*MeV,
//               0.0*cgs::centimeter,
//                         10.0*cgs::centimeter ),
//               std::logic_error );


//   // After the third bin - with extension
//   unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

//   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         3.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         3.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

//   sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInBoundaries(
//                         3.0*MeV,
//                         0.0*cgs::centimeter,
//                         10.0*cgs::centimeter );
//   UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

//   unit_aware_tab_distribution->limitToPrimaryIndepLimits();

//   Utility::RandomNumberGenerator::unsetFakeStream();
// }

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( -1.0, 0.0, 0.0, 10.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( -1.0, 0.0, 0.0, 10.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( -1.0, 0.5, 0.0, 10.0 );
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( -1.0, 1.0-1e-15, 0.0, 10.0 );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.0, 0.0, 0.0, 10.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.0, 0.5, 0.0, 10.0 );
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.0, 1.0-1e-15, 0.0, 10.0 );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // In the second bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.5, 0.0, 1.25, 8.75 );
  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.5, 0.4230769230769231, 1.25, 8.75 );
  TEST_FLOATING_EQUALITY( sample, 4.711538461538, 1e-12 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.5, 1.0-1e-15, 1.25, 8.75 );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // On the third bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.0, 0.0, 2.5, 7.5 );
  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.0, 0.4230769230769231, 2.5, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.0, 1.0-1e-15, 2.5, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.5, 0.0, 1.25, 8.75 );
  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.5, 0.4230769230769231, 1.25, 8.75 );
  TEST_FLOATING_EQUALITY( sample, 4.711538461538, 1e-12 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.5, 1.0-1e-15, 1.25, 8.75 );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // On the upper bin boundary
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 2.0, 0.0, 0.0, 10.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 2.0, 0.5, 0.0, 10.0 );
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 2.0, 1.0-1e-15, 0.0, 10.0 );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 3.0, 0.0, 0.0, 10.0 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 3.0, 0.0, 0.0, 10.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 3.0, 0.5, 0.0, 10.0 );
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 3.0, 1.0-1e-15, 0.0, 10.0 );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( -1.0*MeV, 0.0, 0.0*cgs::centimeter, 10.0*cgs::centimeter ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::length> sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( -1.0*MeV, 0.0, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( -1.0*MeV, 0.5, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( -1.0*MeV, 1.0-1e-15, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.0*MeV, 0.0, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.0*MeV, 0.5, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.0*MeV, 1.0-1e-15, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // In the second bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.5*MeV, 0.0, 1.25*cgs::centimeter, 8.75*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.5*MeV, 0.4230769230769231, 1.25*cgs::centimeter, 8.75*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.711538461538*cgs::centimeter, 1e-12 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 0.5*MeV, 1.0-1e-15, 1.25*cgs::centimeter, 8.75*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // On the third bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.0*MeV, 0.0, 2.5*cgs::centimeter, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.0*MeV, 0.4230769230769231, 2.5*cgs::centimeter, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.0*MeV, 1.0-1e-15, 2.5*cgs::centimeter, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.5*MeV, 0.0, 1.25*cgs::centimeter, 8.75*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.5*MeV, 0.4230769230769231, 1.25*cgs::centimeter, 8.75*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.711538461538*cgs::centimeter, 1e-12 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 1.5*MeV, 1.0-1e-15, 1.25*cgs::centimeter, 8.75*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 2.0*MeV, 0.0, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 2.0*MeV, 0.5, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 2.0*MeV, 1.0-1e-15, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 3.0*MeV, 0.0, 0.0*cgs::centimeter, 10.0*cgs::centimeter ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 3.0*MeV, 0.0, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 3.0*MeV, 0.5, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInBoundaries( 3.0*MeV, 1.0-1e-15, 0.0*cgs::centimeter, 10.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   correlatedSampleSecondaryConditionalInSubrangeInBoundaries )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0, 0.0, 7.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  double sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0, 0.0, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0, 0.0, 11.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0, 0.0, 11.0 );
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0, 0.0, 11.0 );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.0, 0.0, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // In the second bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.5, 1.25, 7.5 );
  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.5, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 4.13461538461539, 1e-12 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.5, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.0, 1.25, 7.5 );
  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.0, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.0, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.5, 1.25, 7.5 );
  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.5, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 4.13461538461539, 1e-12 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.5, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 2.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 2.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 2.0, 0.0, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 3.0, 0.0, 7.5 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 3.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 3.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 3.0, 0.0, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   correlatedSampleSecondaryConditionalInSubrangeInBoundaries )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Subrange
  quantity<cgs::length> sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 11.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 11.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( -1.0*MeV, 0.0*cgs::centimeter, 11.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // In the second bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.5*MeV, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.5*MeV, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.13461538461539*cgs::centimeter, 1e-12 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 0.5*MeV, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // On the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.0*MeV, 2.5*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.0*MeV, 2.5*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.0*MeV, 2.5*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.5*MeV, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.5*MeV, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.13461538461539*cgs::centimeter, 1e-12 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 1.5*MeV, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 2.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 2.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 2.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 3.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 3.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 3.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrangeInBoundaries( 3.0*MeV, 0.0*cgs::centimeter, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedFullyTabularTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0, 0.0, 0.0, 7.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0, 0.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0, 0.5, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0, 1.0-1e-15, 0.0, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0, 0.0, 0.0, 11.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0, 0.5, 0.0, 11.0 );
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0, 1.0-1e-15, 0.0, 11.0 );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-12 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.0, 0.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.0, 0.5, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.0, 1.0-1e-15, 0.0, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // In the second bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.5, 0.0, 1.25, 7.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.5, 0.4230769230769231, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 4.13461538461539, 1e-12 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.5, 1.0-1e-15, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the third bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.0, 0.0, 1.25, 7.5 );
  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.0, 0.4230769230769231, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.0, 1.0-1e-15, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the third bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.5, 0.0, 1.25, 7.5 );
  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.5, 0.4230769230769231, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 4.13461538461539, 1e-12 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.5, 1.0-1e-15, 1.25, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the upper bin boundary
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 2.0, 0.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 2.0, 0.5, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 2.0, 1.0-1e-15, 0.0, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 3.0, 0.0, 0.0, 7.5 ),
              std::logic_error );

  // After the third bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 3.0, 0.0, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 3.0, 0.5, 0.0, 7.5 );
  TEST_EQUALITY_CONST( sample, 3.75 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 3.0, 1.0-1e-15, 0.0, 7.5 );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedFullyTabularTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0*MeV, 0.0, 0.0*cgs::centimeter, 7.5*cgs::centimeter ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::length> sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0*MeV, 0.0, 0.0*cgs::centimeter, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0*MeV, 0.5, 0.0*cgs::centimeter, 7.5*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0*MeV, 1.0-1e-15, 0.0*cgs::centimeter, 7.5*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-12 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0*MeV, 0.0, 0.0*cgs::centimeter, 11.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0*MeV, 0.5, 0.0*cgs::centimeter, 11.0*cgs::centimeter );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( -1.0*MeV, 1.0-1e-15, 0.0*cgs::centimeter, 11.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the second bin  
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.0*MeV, 0.0, 0.0*cgs::centimeter, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.0*MeV, 0.5, 0.0*cgs::centimeter, 7.5*cgs::centimeter );

  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.0*MeV, 1.0-1e-15, 0.0*cgs::centimeter, 7.5*cgs::centimeter );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // In the second bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.5*MeV, 0.0, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.5*MeV, 0.4230769230769231, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.13461538461539*cgs::centimeter, 1e-12 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 0.5*MeV, 1.0-1e-15, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the third bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.0*MeV, 0.0, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.0*MeV, 0.4230769230769231, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.0*MeV, 1.0-1e-15, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the third bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.5*MeV, 0.0, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.5*MeV, 0.4230769230769231, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.13461538461539*cgs::centimeter, 1e-12 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 1.5*MeV, 1.0-1e-15, 1.25*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 2.0*MeV, 0.0, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 2.0*MeV, 0.5, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 2.0*MeV, 1.0-1e-15, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // After the third bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 3.0*MeV, 0.0, 0.0*cgs::centimeter, 7.5*cgs::centimeter ),
              std::logic_error );

  // After the third bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 3.0*MeV, 0.0, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 3.0*MeV, 0.5, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  TEST_EQUALITY_CONST( sample, 3.75*cgs::centimeter );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrangeInBoundaries( 3.0*MeV, 1.0-1e-15, 0.0*cgs::centimeter, 7.5*cgs::centimeter);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // // Create the two-dimensional distribution
  // {
  //   Utility::FullyTabularTwoDDistribution::DistributionType
  //     distribution_data( 4 );

  //   // Create the secondary distribution in the first bin
  //   distribution_data[0].first = 0.0;
  //   distribution_data[0].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );

  //   // Create the secondary distribution in the second bin
  //   distribution_data[1].first = 0.0;
  //   distribution_data[1].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 1.0 ) );

  //   // Create the secondary distribution in the third bin
  //   std::vector<double> bin_boundaries( 3 ), values( 3 );
  //   bin_boundaries[0] = 2.5; values[0] = 0.1;
  //   bin_boundaries[1] = 5.0; values[1] = 1.0;
  //   bin_boundaries[2] = 7.5; values[2] = 0.5;

  //   distribution_data[2].first = 1.0;
  //   distribution_data[2].second.reset( new Utility::TabularDistribution<Utility::LinLin>( bin_boundaries, values ) );

  //   // Create the secondary distribution beyond the third bin
  //   distribution_data[3].first = 2.0;
  //   distribution_data[3].second = distribution_data[0].second;

  //   tab_distribution.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin,Utility::Stochastic>(
  //                                                           distribution_data,
  //                                                           1e-3,
  //                                                           1e-7 ) );
  //   distribution = tab_distribution;
  // }

  // // Create the unit-aware two-dimensional distribution
  // {
  //   std::vector<quantity<MegaElectronVolt> > primary_bins( 4 );

  //   Teuchos::Array<std::shared_ptr<const Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn> > > secondary_dists( 4 );

  //   // Create the secondary distribution in the first bin
  //   primary_bins[0] = 0.0*MeV;
  //   secondary_dists[0].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 0.1*barn ) );

  //   // Create the secondary distribution in the second bin
  //   primary_bins[1] = 0.0*MeV;
  //   secondary_dists[1].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 1.0*barn ) );

  //   // Create the secondary distribution in the third bin
  //   Teuchos::Array<quantity<cgs::length> > bin_boundaries( 3 );
  //   Teuchos::Array<quantity<Barn> > values( 3 );
  //   bin_boundaries[0] = 2.5*cgs::centimeter; values[0] = 0.1*barn;
  //   bin_boundaries[1] = 5.0*cgs::centimeter; values[1] = 1.0*barn;
  //   bin_boundaries[2] = 7.5*cgs::centimeter; values[2] = 0.5*barn;

  //   primary_bins[2] = 1.0*MeV;
  //   secondary_dists[2].reset( new Utility::UnitAwareTabularDistribution<Utility::LinLin,cgs::length,Barn>( bin_boundaries, values ) );

  //   // Create the secondary distribution beyond the third bin
  //   primary_bins[3] = 2.0*MeV;
  //   secondary_dists[3] = secondary_dists[0];

  //   unit_aware_tab_distribution.reset( new Utility::UnitAwareInterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin,Utility::Stochastic,MegaElectronVolt,cgs::length,Barn>( primary_bins, secondary_dists, 1e-3, 1e-7 ) );

  //   unit_aware_distribution = unit_aware_tab_distribution;
  // }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLinLinLinInterpolatedFullyTabularTwoDDistribution.cpp
//---------------------------------------------------------------------------//
