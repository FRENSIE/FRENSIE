//---------------------------------------------------------------------------//
//!
//! \file   tstLogLogLogCoupledElasticTwoDDistribution.cpp
//! \author Luke Kersting
//! \brief  The elastic two-dimensional dist. unit tests
//!         (Coupled with LogLogLog interpolation)
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
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  TEST_ASSERT( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous in the primary dimension
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  TEST_ASSERT( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous in the primary
// dimension
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
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

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogLog>(
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

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogLog>(
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

    test_dist.reset( new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogLog>(
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
                          3.46102718214321869450e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.0 ),
                          1.73051359107160940276,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 0.999999 ),
                          3.46102718214321880552,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluate( 1.5, 1.0 ),
                          3.4610341042010435153,
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
                   evaluate )
{
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
                                  3.46102718214321869450e-01*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.73051359107160940276*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.46102718214321880552*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  3.46103410420104351530*barn,
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
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution, evaluateExact )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 0.0, -1.0 ), 0.09, 1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 0.0 ), 0.45 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 0.0, 0.999999 ), 0.9 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 0.0, 1.0 ), 9.00001800000899910e-01, 1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.0, -1.0 ), 0.09, 1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.0, 0.0 ), 0.45 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 1.0, 0.999999 ), 0.9 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.0, 1.0 ), 9.00001800000899910e-01, 1e-15 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.5, -1.0 ),
                          3.46102718214321869450e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.5, 0.0 ),
                          1.73051359107160940276,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.5, 0.999999 ),
                          3.46102718214321880552,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 1.5, 1.0 ),
                          3.46103410420104351530,
                          1e-15 );

  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 2.0, -1.0 ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 2.0, 0.0 ), 4.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 2.0, 0.999999 ), 9.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 2.0, 1.0 ),
                          9.000018000008997987,
                          1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, -1.0 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 0.0 ), 4.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateExact( 3.0, 0.999999 ), 9.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateExact( 3.0, 1.0 ),
                          9.000018000008997987,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateExact )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.09*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.45*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.9*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 0.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987e-01*barn,
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.09*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.45*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, 0.999999*cgs::dimensionless() ), 0.9*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987e-01*barn,
                                  1e-15 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  3.46102718214321869450e-01*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.73051359107160940276*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.46102718214321880552*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  3.46103410420104351530*barn,
                                  1e-15 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.9*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, 0.0*cgs::dimensionless() ), 4.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, 0.999999*cgs::dimensionless() ), 9.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987*barn,
                                  1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.9*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 0.0*cgs::dimensionless() ), 4.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateExact( 3.0*MeV, 0.999999*cgs::dimensionless() ), 9.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateExact( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987*barn,
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution, correlatedEvaluate )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 0.0, -1.0 ), 0.09, 1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, 0.0 ), 0.45 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 0.0, 0.999999 ), 0.9 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 0.0, 1.0 ), 9.00001800000899910e-01, 1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 1.0, -1.0 ), 0.09, 1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 1.0, 0.0 ), 0.45 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 1.0, 0.999999 ), 0.9 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 1.0, 1.0 ), 9.00001800000899910e-01, 1e-15 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 1.5, -1.0 ),
                          3.46102718214321869450e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 1.5, 0.0 ),
                          1.73051359107160940276,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 1.5, 0.999999 ),
                          3.46102718214321880552,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 1.5, 1.0 ),
                          3.46103410420104351530,
                          1e-15 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 2.0, -1.0 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 2.0, 0.0 ), 4.5 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 2.0, 0.999999 ), 9.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 2.0, 1.0 ),
                          9.000018000008997987,
                          1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, -1.0 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, 0.0 ), 4.5 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluate( 3.0, 0.999999 ), 9.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluate( 3.0, 1.0 ),
                          9.000018000008997987,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedEvaluate )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.09*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.45*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.9*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 0.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987e-01*barn,
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  0.09*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 1.0*MeV, 0.0*cgs::dimensionless() ), 0.45*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 1.0*MeV, 0.999999*cgs::dimensionless() ), 0.9*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 1.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987e-01*barn,
                                  1e-15 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  3.46102718214321869450e-01*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  1.73051359107160940276*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  3.46102718214321880552*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  3.46103410420104351530*barn,
                                  1e-15 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.9*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 2.0*MeV, 0.0*cgs::dimensionless() ), 4.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 2.0*MeV, 0.999999*cgs::dimensionless() ), 9.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987*barn,
                                  1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0*barn );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.9*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, 0.0*cgs::dimensionless() ), 4.5*barn );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, 0.999999*cgs::dimensionless() ), 9.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluate( 3.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.000018000008997987*barn,
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDF )
{
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
                   evaluateSecondaryConditionalPDF )
{
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
                   evaluateSecondaryConditionalPDFExact )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, -1.0 ),
                          8.57143469388192414e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 0.0 ),
                          4.28571734694096207e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 0.999999 ),
                          8.57143469388192414e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, -1.0 ),
                          8.57143469388192414e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, 0.0 ),
                          4.28571734694096207e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, 0.999999 ),
                          8.57143469388192414e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5, -1.0 ),
                          8.5714346938819227506e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5, 0.0 ),
                          0.42857173469409620692,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5, 0.999999 ),
                          0.85714346938819230282,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );


  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, -1.0 ),
                          8.57143469388192275e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, 0.0 ),
                          4.28571734694096151e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, 0.999999 ),
                          8.57143469388192303e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, -1.0 ),
                          8.57143469388192275e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 0.0 ),
                          4.28571734694096151e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 0.999999 ),
                          8.57143469388192303e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalPDFExact )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact     ( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192414e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096207e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192414e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 0.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192414e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096207e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192414e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  8.5714346938819227506e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  0.42857173469409620692/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  0.85714346938819230282/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192275e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096151e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192303e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192275e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096151e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192303e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalPDFExact( 3.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, -1.0 ),
                          8.57143469388192414e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          4.28571734694096207e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, 0.999999 ),
                          8.57143469388192414e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0, -1.0 ),
                          8.57143469388192414e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0, 0.0 ),
                          4.28571734694096207e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0, 0.999999 ),
                          8.57143469388192414e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  // In the first bin
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5, -1.0 ),
                          8.5714346938819227506e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5, 0.0 ),
                          0.42857173469409620692,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5, 0.999999 ),
                          0.85714346938819230282,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );


  // On the upper bin boundary
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0, -1.0 ),
                          8.57143469388192275e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0, 0.0 ),
                          4.28571734694096151e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0, 0.999999 ),
                          8.57143469388192303e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, -1.0 ),
                          8.57143469388192275e-02,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, 0.0 ),
                          4.28571734694096151e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, 0.999999 ),
                          8.57143469388192303e-01,
                          1e-15 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0, 1.0 ),
                          9.52383537417764602928e-01,
                          1e-15 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF     ( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192414e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096207e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192414e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192414e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096207e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192414e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // In the first bin
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::dimensionless() ),
                                  8.5714346938819227506e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  0.42857173469409620692/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5*MeV, 0.999999*cgs::dimensionless() ),
                                  0.85714346938819230282/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 1.5*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // On the upper bin boundary
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192275e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096151e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192303e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 2.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0/cgs::dimensionless() );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0/cgs::dimensionless() );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::dimensionless() ),
                                  8.57143469388192275e-02/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  4.28571734694096151e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, 0.999999*cgs::dimensionless() ),
                                  8.57143469388192303e-01/cgs::dimensionless(),
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalPDF( 3.0*MeV, 1.0*cgs::dimensionless() ),
                                  9.52383537417764602928e-01/cgs::dimensionless(),
                                  1e-15 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDF )
{
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
                   evaluateSecondaryConditionalCDF )
{
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
                   evaluateSecondaryConditionalCDFExact )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0, 1.0 ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5, 1.0 ), 1.0 );


  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0, 1.0 ), 1.0 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   evaluateSecondaryConditionalCDFExact )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 0.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 1.5*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 2.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateSecondaryConditionalCDFExact( 3.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalCDF )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, 1.0 ), 0.0 );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0, 1.0 ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5, 1.0 ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, 1.0 ), 1.0 );


  // After the second bin - no extension
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0, 0.999999 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0, 1.0 ), 0.0 );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, 0.0 ),
                          2.57143040816457724151e-01,
                          1e-15 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, 0.999999 ), 0.9 );
  TEST_EQUALITY_CONST( tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0, 1.0 ), 1.0 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedEvaluateSecondaryConditionalCDF )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 0.0 );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 0.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // In the first bin
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 1.5*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 2.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  // After the second bin - no extension
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 0.0 );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, -1.0*cgs::dimensionless() ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, 0.0*cgs::dimensionless() ),
                                  2.57143040816457724151e-01,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, 0.999999*cgs::dimensionless() ), 0.9 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->correlatedEvaluateSecondaryConditionalCDF( 3.0*MeV, 1.0*cgs::dimensionless() ), 1.0 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditional )
{
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
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = distribution->sampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

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

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.585; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.584; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.584; // use upper bin boundary
  fake_stream[15] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

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

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

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
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = distribution->sampleSecondaryConditional( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditional )
{
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
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

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.585; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.584; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.584; // use upper bin boundary
  fake_stream[15] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

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

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_distribution->sampleSecondaryConditional( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  unsigned trials = 0u;

  // Before the first bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 0u );

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
  TEST_EQUALITY_CONST( sample, 0.999999 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

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

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  TEST_EQUALITY_CONST( sample, 0.999999 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.585; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.584; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.584; // use upper bin boundary
  fake_stream[15] = 1.0-1e-15;
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
  TEST_EQUALITY_CONST( trials, 7u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 8u );

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

  trials = 0u;

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  TEST_EQUALITY_CONST( sample, 0.999999 );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  // After the second bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( 3.0, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 4u );

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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
                   sampleSecondaryConditionalAndRecordTrials )
{  unsigned trials = 0u;

  // Before the first bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 0u );

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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

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

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.585; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.584; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.584; // use upper bin boundary
  fake_stream[15] = 1.0-1e-15;
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 7u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 8u );

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

  trials = 0u;

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( trials, 3u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( trials, 4u );

  // After the second bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 3.0*MeV, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 4u );

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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
                   sampleSecondaryConditionalAndRecordBinIndices )
{
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0, primary_bin_index, secondary_bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.585; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.584; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.584; // use upper bin boundary
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
                   sampleSecondaryConditionalAndRecordBinIndices )
{
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalAndRecordBinIndices( 1.0*MeV, primary_bin_index, secondary_bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  TEST_EQUALITY_CONST( primary_bin_index, 0u );
  TEST_EQUALITY_CONST( secondary_bin_index, 2u );

  // In the first bin
  fake_stream.resize( 16 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.585; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.584; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.584; // use upper bin boundary
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw )
{
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.585; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.584; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.584; // use upper bin boundary
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
  TEST_EQUALITY_CONST( sample, 0.999999 );
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
                   sampleSecondaryConditionalAndRecordBinIndices_with_raw )
{
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 2.57143040816457724151e-01;
  fake_stream[4] = 0.585; // use lower bin boundary
  fake_stream[5] = 0.9;
  fake_stream[6] = 0.585; // use lower bin boundary
  fake_stream[7] = 1.0-1e-15;
  fake_stream[8] = 0.584; // use upper bin boundary
  fake_stream[9] = 0.0;
  fake_stream[10] = 0.584; // use upper bin boundary
  fake_stream[11] = 2.57143040816457724151e-01;
  fake_stream[12] = 0.584; // use upper bin boundary
  fake_stream[13] = 0.9;
  fake_stream[14] = 0.584; // use upper bin boundary
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );
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
                   sampleSecondaryConditionalWithRandomNumber )
{
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
  TEST_EQUALITY_CONST( sample, 0.999999 );

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
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  fake_stream[6] = 0.584; // use upper bin boundary
  fake_stream[7] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

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
  TEST_EQUALITY_CONST( sample, 0.999999 );

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
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalWithRandomNumber )
{
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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream.resize( 8 );
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  fake_stream[6] = 0.584; // use upper bin boundary
  fake_stream[7] = 0.584; // use upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Samples from lower boundary of second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // Samples from the upper boundary of the second bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

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
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalInSubrange )
{
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

  // The sampling routine will not be able to sample zero exactly
  double almost_zero = -5.55111512312578270e-16;

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
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.585; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 0.2;
  fake_stream[11] = 0.584; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.584; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.584; // use upper bin boundary
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
                   sampleSecondaryConditionalInSubrange )
{
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
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.585; // use lower bin boundary
  fake_stream[6] = 1.0-1e-15;
  fake_stream[7] = 0.585; // use lower bin boundary
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.584; // use upper bin boundary
  fake_stream[10] = 0.2;
  fake_stream[11] = 0.584; // use upper bin boundary
  fake_stream[12] = 0.9;
  fake_stream[13] = 0.584; // use upper bin boundary
  fake_stream[14] = 1.0-1e-15;
  fake_stream[15] = 0.584; // use upper bin boundary
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
                   sampleSecondaryConditionalWithRandomNumberInSubrange )
{
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
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  fake_stream[6] = 0.584; // use upper bin boundary
  fake_stream[7] = 0.584; // use upper bin boundary
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
                   sampleSecondaryConditionalWithRandomNumberInSubrange )
{
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
  fake_stream[0] = 0.585; // use lower bin boundary
  fake_stream[1] = 0.585; // use lower bin boundary
  fake_stream[2] = 0.585; // use lower bin boundary
  fake_stream[3] = 0.585; // use lower bin boundary
  fake_stream[4] = 0.584; // use upper bin boundary
  fake_stream[5] = 0.584; // use upper bin boundary
  fake_stream[6] = 0.584; // use upper bin boundary
  fake_stream[7] = 0.584; // use upper bin boundary

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
                   sampleSecondaryConditionalExact )
{
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExact( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleSecondaryConditionalExact( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExact( 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExact( 3.0 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExact( 3.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 3.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 3.0 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalExact( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalExact )
{
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.0*MeV ),
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
    unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 0.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExact( 3.0*MeV ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExact( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumber )
{
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumber )
{
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0*MeV, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalExactInSubrange )
{
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 0.0 ),
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
  double sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.57143040816457724151e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalExactInSubrange )
{
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
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
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-15 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.57143040816457724151e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF an be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumberInSubrange )
{
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 0.5, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 2.57143040816457724151e-01, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 0.9, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0, 0.5, 0.9),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF an be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   sampleSecondaryConditionalExactWithRandomNumberInSubrange )
{
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-15 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 2.57143040816457724151e-01, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 0.9, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedSampleSecondaryConditional )
{
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditional( 0.0 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();
  
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->correlatedSampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 0.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 1.0 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 1.5 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 1.5 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 2.0 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditional( 3.0 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 3.0 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->correlatedSampleSecondaryConditional( 3.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedSampleSecondaryConditional )
{
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 0.0*MeV ),
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
    unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 0.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 0.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 1.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 1.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 2.57143040816457724151e-01;
  fake_stream[2] = 0.9;
  fake_stream[3] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 1.5*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 1.5*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 2.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 2.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 3.0*MeV ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 3.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditional( 3.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumber )
{
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 0.0, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  double sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 0.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 0.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 0.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.0, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // In the first bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.5, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.5, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 2.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 2.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 2.0, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 2.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 3.0, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 3.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 3.0, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 3.0, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 3.0, 1.0-1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumber )
{
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.5 ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  quantity<cgs::dimensionless> sample =
    unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 0.0*MeV, 1.0-1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );
  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 1.5*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 2.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.5 ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 2.57143040816457724151e-01 );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 0.9 );
  TEST_EQUALITY_CONST( sample, 0.999999*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumber( 3.0*MeV, 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalInSubrange )
{
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0, 0.0 ),
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
  double sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.57143040816457724151e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.5, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 2.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 3.0, 0.9 ),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 3.0, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalInSubrange )
{
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0*MeV, 0.0*cgs::dimensionless() ),
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
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-15 );

  // Beyond full range - check that expected range will be used
  fake_stream[1] = 2.57143040816457724151e-01;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 0.0*MeV, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  fake_stream[1] = 0.2;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 1.5*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 2.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalInSubrange( 3.0*MeV, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( ElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumberInSubrange )
{
  // Before the first bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.5, 0.9 ),
              std::logic_error );

  // Before the first bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  double sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // Beyond full range - check that expected range will be used
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.0, 2.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 2.57143040816457724151e-01, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 0.9, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 0.999999, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0, 1.0-1e-15, 2.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // In the first bin
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.5, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // On the upper bin boundary
  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 2.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  // After the second bin - no extension
  TEST_THROW( tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.5, 0.9),
              std::logic_error );

  // After the second bin - with extension
  tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.0, 0.9 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.2, 0.9 );
  TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 0.9, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01, 1e-15 );

  sample = tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 3.0, 1.0-1e-15, 0.9 );
  TEST_FLOATING_EQUALITY( sample, 0.9, 1e-14 );

  tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareElasticTwoDDistribution,
                   correlatedSampleSecondaryConditionalWithRandomNumberInSubrange )
{
  // Before the first bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // Before the first bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  // Subrange
  quantity<cgs::dimensionless> sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-15 );

  // Beyond full range - check that expected range will be used
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV,0.0, 2.0*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 2.57143040816457724151e-01, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 0.9, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.999999*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 0.0*MeV, 1.0-1e-15, 2.0*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();

  // On the first bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034774482*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.96941872705888565e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // In the first bin
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.969418727058884544e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 1.5*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // On the upper bin boundary
  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 2.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  // After the second bin - no extension
  TEST_THROW( unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.5, 0.9*cgs::dimensionless() ),
              std::logic_error );

  // After the second bin - with extension
  unit_aware_tab_distribution->extendBeyondPrimaryIndepLimits();

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.0, 0.9*cgs::dimensionless() );
  TEST_EQUALITY_CONST( sample, -1.0*cgs::dimensionless() );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.2, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -0.24252781552034763379*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 0.9, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.9694187270588834338e-01*cgs::dimensionless(), 1e-15 );

  sample = unit_aware_tab_distribution->correlatedSampleSecondaryConditionalWithRandomNumberInSubrange( 3.0*MeV, 1.0-1e-15, 0.9*cgs::dimensionless() );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.9*cgs::dimensionless(), 1e-14 );

  unit_aware_tab_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  double moliere_eta = 1.0;
  double cutoff_ratio = 0.9;

  // Create the two-dimensional distribution
  {
    Utility::ElasticTwoDDistribution<Utility::LogLogLog>::DistributionType
      distribution_data( 2 );

    // Create the secondary distribution in the first bin
    std::vector<double> bin_boundaries( 3 ), values( 3 );
    bin_boundaries[0] = -1.0; values[0] = 0.1;
    bin_boundaries[1] = 0.0; values[1] = 0.5;
    bin_boundaries[2] = 0.999999; values[2] = 1.0;

    distribution_data[0].first = 1.0;
    distribution_data[0].second.reset( new Utility::CoupledElasticDistribution<Utility::LinLin>( bin_boundaries, values, moliere_eta, cutoff_ratio ) );

    // Create the secondary distribution In the first bin
    bin_boundaries[0] = -1.0; values[0] = 1.0;
    bin_boundaries[1] = 0.0; values[1] = 5.0;
    bin_boundaries[2] = 0.999999; values[2] = 10.0;

    distribution_data[1].first = 2.0;
    distribution_data[1].second.reset( new Utility::CoupledElasticDistribution<Utility::LinLin>( bin_boundaries, values, moliere_eta, cutoff_ratio ) );

    tab_distribution.reset( new Utility::ElasticTwoDDistribution<Utility::LogLogLog>( distribution_data, 1.0, 1e-3, 1e-7 ) );
    distribution = tab_distribution;
  }

  // Create the unit-aware two-dimensional distribution
  {
    std::vector<quantity<MegaElectronVolt> > primary_bins( 2 );

    Teuchos::Array<std::shared_ptr<const Utility::UnitAwareTabularOneDDistribution<cgs::dimensionless,Barn> > > secondary_dists( 2 );

    // Create the secondary distribution in the first bin
    Teuchos::Array<quantity<cgs::dimensionless> > bin_boundaries( 3 );
    Teuchos::Array<quantity<Barn> > values( 3 );
    bin_boundaries[0] = -1.0*cgs::dimensionless(); values[0] = 0.1*barn;
    bin_boundaries[1] = 0.0*cgs::dimensionless(); values[1] = 0.5*barn;
    bin_boundaries[2] = 0.999999*cgs::dimensionless(); values[2] = 1.0*barn;

    primary_bins[0] = 1.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareCoupledElasticDistribution<Utility::LinLin,cgs::dimensionless,Barn>( bin_boundaries, values, moliere_eta, cutoff_ratio ) );

    // Create the secondary distribution In the first bin
    bin_boundaries[0] = -1.0*cgs::dimensionless(); values[0] = 1.0*barn;
    bin_boundaries[1] = 0.0*cgs::dimensionless(); values[1] = 5.0*barn;
    bin_boundaries[2] = 0.999999*cgs::dimensionless(); values[2] = 10.0*barn;

    primary_bins[1] = 2.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareCoupledElasticDistribution<Utility::LinLin,cgs::dimensionless,Barn>( bin_boundaries, values, moliere_eta, cutoff_ratio ) );

    unit_aware_tab_distribution.reset( new Utility::UnitAwareElasticTwoDDistribution<Utility::LogLogLog,MegaElectronVolt,cgs::dimensionless,Barn>(
        primary_bins, secondary_dists, 1.0*cgs::dimensionless(), 1e-3, 1e-7 ) );

    unit_aware_distribution = unit_aware_tab_distribution;
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLogLogLogCoupledElasticTwoDDistribution.cpp
//---------------------------------------------------------------------------//
