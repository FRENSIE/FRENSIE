//---------------------------------------------------------------------------//
//!
//! \file   tstLogLogLogCutoffElasticTwoDDistribution.cpp
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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DynamicOutputFormatter.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ElasticTwoDDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
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
template<typename TwoDSamplingPolicy,
         typename BaseTabDistribution,
         typename BaseDistribution>
void initialize( std::shared_ptr<BaseTabDistribution>& tab_dist,
                 std::shared_ptr<BaseDistribution>& dist )
{
  typename BaseTabDistribution::SecondaryIndepQuantity cutoff;
  Utility::setQuantity( cutoff, 0.999999 );

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
  secondary_dists[0].reset( new Utility::UnitAwareTabularDistribution<Utility::LinLin,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>( bin_boundaries, values ) );

  // Create the secondary distribution beyond the second bin
  Utility::setQuantity( values[0], 1.0 );
  Utility::setQuantity( values[1], 5.0 );
  Utility::setQuantity( values[2], 10.0 );

  Utility::setQuantity( primary_bins[1], 2.0 );
  secondary_dists[1].reset( new Utility::UnitAwareTabularDistribution<Utility::LinLin,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>( bin_boundaries, values ) );

  tab_dist.reset( new Utility::UnitAwareElasticTwoDDistribution<Utility::LogLogCosLog,TwoDSamplingPolicy,typename BaseTabDistribution::PrimaryIndepUnit,typename BaseTabDistribution::SecondaryIndepUnit,typename BaseTabDistribution::DepUnit>(
      primary_bins, secondary_dists, cutoff, 1e-3, 1e-7 ) );

  dist = tab_dist;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );
  TEST_ASSERT( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous in the primary dimension
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );
  TEST_ASSERT( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous in the primary
// dimension
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary lower bound can be returned
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfPrimaryIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary lower bound can be
// returned
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfPrimaryIndepVar(), 1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary dimension upper bound can be returned
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfPrimaryIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary dimension upper bound can
// be returned
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfPrimaryIndepVar(), 2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional distribution can be returned
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   getLowerBoundOfConditionalIndepVar )
{
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
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
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
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 0.0 ),
                       0.0 );
  
  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 0.0 ),
                       0.999999 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 1.0 ),
                       0.999999 );

  // In the first bin
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 1.5 ),
                       0.999999 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 2.0 ),
                       0.999999 );

  // Beyond the second bin - no extension
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 3.0 ),
                       0.999999 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional unit-aware distribution can be
// returned
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   getUpperBoundOfConditionalIndepVar )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 0.0*MeV ),
                       0.0*cgs::dimensionless() );
  
  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 0.0*MeV ),
                       0.999999*cgs::dimensionless() );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 1.0*MeV ),
                       0.999999*cgs::dimensionless() );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 1.5*MeV ),
                       0.999999*cgs::dimensionless() );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 2.0*MeV ),
                       0.999999*cgs::dimensionless() );

  // Beyond the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::dimensionless() );

  // Beyond the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 3.0*MeV ),
                       0.999999*cgs::dimensionless() );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the bounds of two distribution can be compared
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
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
    distribution_data[0].second.reset( new Utility::UniformDistribution( 0.1, 1.0, 0.1 ) );

    // Create the secondary distribution In the first bin
    distribution_data[1].first = 2.0;
    distribution_data[1].second = distribution_data[0].second;

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogCosLog,Utility::Stochastic>(
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

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogCosLog,Utility::Stochastic>(
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

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogCosLog,Utility::Stochastic>(
                                                               primary_grid,
                                                               secondary_grids,
                                                               values ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *test_dist ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution, evaluate )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.0, -1.0 ), 0.1, 1e-14 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.0 ), 0.5 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.0, 0.999999 ), 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.0, -1.0 ), 0.1, 1e-14 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 0.0 ), 0.5 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.0, 0.999999 ), 1.0, 1e-14 );

  // In the first bin
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.5, -1.0 ),
                          3.84558575793691015399e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.5, 0.0 ),
                          1.92279287896845474393,
                          1e-14 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.5, 0.999999 ),
                          3.84558575793690993194e+00,
                          1e-14 );

  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( distribution->evaluate( 2.0, -1.0 ), 1.0, 1e-14 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 0.0 ), 5.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 2.0, 0.999999 ), 10.0, 1e-14 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.0 ), 5.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.999999 ), 10.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluate )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  3.84558575793691015399e-01*barn,
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.92279287896845474393*barn,
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.84558575793690993194e+00*barn,
                                  1e-14 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  1.0*barn,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution, evaluateExact )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 0.0, -1.0 ), 0.1, 1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.0, -1.0 ), 0.1, 1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.0, 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.0, 0.999999 ), 1.0 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.5, -1.0 ),
                          3.84558575793691015399e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.5, 0.0 ),
                          1.92279287896845474393,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.5, 0.999999 ),
                          3.84558575793690993194e+00,
                          1e-14 );

  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 2.0, -1.0 ), 1.0, 1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 2.0, 0.0 ), 5.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 2.0, 0.999999 ), 10.0 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 0.0 ), 5.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 0.999999 ), 10.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateExact )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  3.84558575793691015399e-01*barn,
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.92279287896845474393*barn,
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.84558575793690993194e+00*barn,
                                  1e-14 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  1.0*barn,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution, correlatedEvaluate )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 0.0, -1.0 ), 0.1, 1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, 0.999999 ), 1.0 );


  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 1.0, -1.0 ), 0.1, 1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 1.0, 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 1.0, 0.999999 ), 1.0 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 1.5, -1.0 ),
                          3.84558575793691015399e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 1.5, 0.0 ),
                          1.92279287896845474393,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 1.5, 0.999999 ),
                          3.84558575793690993194e+00,
                          1e-14 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 2.0, -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 2.0, 0.0 ), 5.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 2.0, 0.999999 ), 10.0 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, 0.0 ), 5.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, 0.999999 ), 10.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedEvaluate )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.1*barn,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0*barn );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  3.84558575793691015399e-01*barn,
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.92279287896845474393*barn,
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.84558575793690993194e+00*barn,
                                  1e-14 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 2.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 5.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 10.0*barn );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDF )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 0.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.0 ),
                          4.761908163267735139e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 1.5, 0.999999 ),
                          9.523816326535470278e-01,
                          1e-14 );

  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 2.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDF( 3.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDF )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDFExact )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );


  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDFExact )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact     ( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalPDF )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0, -1.0 ),
                          9.52381632653547249845e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0, 0.0 ),
                          4.76190816326773569411e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0, 0.999999 ),
                          9.52381632653547138823e-01,
                          1e-14 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );


  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, -1.0 ),
                          9.52381632653546972289e-02,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, 0.0 ),
                          4.76190816326773513900e-01,
                          1e-14 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, 0.999999 ),
                          9.52381632653547027800e-01,
                          1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalPDF )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF     ( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653547249845e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773569411e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547138823e-01/cgs::dimensionless(),
                                  1e-14 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  9.52381632653546972289e-02/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.76190816326773513900e-01/cgs::dimensionless(),
                                  1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  9.52381632653547027800e-01/cgs::dimensionless(),
                                  1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDF )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.0, 0.999999 ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 1.5, 0.999999 ), 1.0 );


  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 1.0 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDF )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 1.5*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 2.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDFExact )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, 0.999999 ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, 0.999999 ), 1.0 );


  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, 0.999999 ), 1.0 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDFExact )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalCDF )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );

  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0, 0.999999 ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5, 0.0 ),
                          2.85714489796064174953e-01,
                          1e-14 );

  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5, 0.999999 ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 1.0 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0, 0.999999 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.85714489796064063931e-01,
                          1e-14 );

  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalCDF )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064174953e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.85714489796064063931e-01,
                                  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditional )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditional )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV ),
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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

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
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
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
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

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
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6u );

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
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  // After the second bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 4u );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;

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

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
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
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 6u );

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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

  // After the second bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 4u );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;

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

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

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
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;
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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
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
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;
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
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

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
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

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
  TEST_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  TEST_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;
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
  TEST_FLOATING_EQUALITY( raw_sample, 0.999999, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  unsigned primary_bin_index = 0u, secondary_bin_index = 0u;
  quantity<cgs::dimensionless> raw_sample;

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 0.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 0u );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;

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
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

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
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 3.0*MeV, raw_sample, primary_bin_index, secondary_bin_index ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064063931e-01;
  fake_stream[2] = 1.0-1e-15;
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
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 0.999999*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 1u );
  TEST_EQUALITY_CONST( secondary_bin_index, 1u );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.85714489796064175e-01 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.85714489796064064e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 2.85714489796064063931e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 2.85714489796064063931e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.85714489796064175e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.85714489796064064e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 2.85714489796064063931e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 2.85714489796064063931e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalInSubrange )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.0 ),
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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalInSubrange )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange )
{
  initialize<Utility::Stochastic>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 2.85714489796064174953e-01, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347745e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumberInSubrange )
{
  initialize<Utility::Stochastic>( unit_aware_tab_distribution,
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
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347745e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 2.85714489796064174953e-01, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347745e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

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
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalExact )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064064e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

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

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalExact )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064064e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream[1] = 2.85714489796064063931e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

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

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumber )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.85714489796064064e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 2.85714489796064064e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 2.85714489796064064e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumber )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.85714489796064064e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 2.85714489796064064e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 2.85714489796064064e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalExactInSubrange )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.0 ),
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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.85714489796064174953e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

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
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalExactInSubrange )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.85714489796064174953e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

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
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF an be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumberInSubrange )
{
  initialize<Utility::Exact>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 2.85714489796064174953e-01, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF an be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumberInSubrange )
{
  initialize<Utility::Exact>( unit_aware_tab_distribution,
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
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 2.85714489796064174953e-01, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

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
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedSampleSecondaryConditional )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064064e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // On the upper bin boundary
  fake_stream[1] = 2.85714489796064063931e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditional( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

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

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedSampleSecondaryConditional )
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
  fake_stream[1] = 2.85714489796064174953e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 0.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.85714489796064064e-01;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  fake_stream[1] = 2.85714489796064063931e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditional( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

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

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumber )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.85714489796064064e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 2.85714489796064063931e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 2.85714489796064063931e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumber )
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

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 2.85714489796064174953e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.85714489796064064e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 2.85714489796064063931e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 2.85714489796064063931e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalInSubrange )
{
  initialize<Utility::Correlated>( tab_distribution, distribution );

  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 ),
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
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.85714489796064174953e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

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
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalInSubrange )
{
  initialize<Utility::Correlated>( unit_aware_tab_distribution,
                                   unit_aware_distribution );

  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
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
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.85714489796064174953e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

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
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumberInSubrange )
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
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 2.85714489796064174953e-01, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumberInSubrange )
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
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 2.85714489796064174953e-01, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

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
  UTILITY_TEST_FLOATING_EQUALITY( sample, -2.42527815520347634e-01*cgs::dimensionless(), 1e-14 );

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
// end tstLogLogLogCutoffElasticTwoDDistribution.cpp
//---------------------------------------------------------------------------//
