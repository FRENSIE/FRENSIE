//---------------------------------------------------------------------------//
//!
//! \file   tstLinLinLinInterpolatedPartiallyTabularTwoDDistribution.cpp
//! \author Alex Robinson
//! \brief  The interpolated partially tabular two-dimensional dist. unit tests
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
#include "Utility_InterpolatedPartiallyTabularTwoDDistribution.hpp"
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
std::shared_ptr<Utility::UnitAwarePartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn> >
  unit_aware_distribution;

std::shared_ptr<Utility::PartiallyTabularTwoDDistribution> distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  TEST_ASSERT( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous in the primary dimension
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  TEST_ASSERT( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous in the primary dim.
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary dimension lower bound can be returned
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfPrimaryIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary dimension lower bound can
// be returned
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularTwoDDistribution,
                   getLowerBoundOfPrimaryIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfPrimaryIndepVar(), 0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution's primary dimension upper bound can be returned
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfPrimaryIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution's primary dimension upper bound can
// be returned
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularTwoDDistribution,
                   getUpperBoundOfPrimaryIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfPrimaryIndepVar(), 2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional distribution can be returned
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   getLowerBoundOfConditionalIndepVar )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar(-1.0),
                       0.0 );
  
  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar(-1.0),
                       0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 0.0 ),
                       0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 0.5 ),
                       1.25 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 1.0 ),
                       2.5 );

  // In the third bin
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 1.5 ),
                       1.25 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 2.0 ),
                       0.0 );

  // Beyond the third bin - no extension
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 3.0 ),
                       0.0 );

  // Beyond the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfConditionalIndepVar( 3.0 ),
                       0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware conditional distribution can be
// returned
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularTwoDDistribution,
                   getLowerBoundOfConditionalIndepVar )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( -1.0*MeV ),
                       0.0*cgs::centimeter );
  
  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( -1.0*MeV ),
                       0.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 0.0*MeV ),
                       0.0*cgs::centimeter );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 0.5*MeV ),
                       1.25*cgs::centimeter );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 1.0*MeV ),
                       2.5*cgs::centimeter );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 1.5*MeV ),
                       1.25*cgs::centimeter );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 2.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::centimeter );

  // Beyond the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfConditionalIndepVar( 3.0*MeV ),
                       0.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional distribution can be returned
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   getUpperBoundOfConditionalIndepVar )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar(-1.0),
                       0.0 );
  
  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar(-1.0),
                       10.0 );

  distribution->limitToPrimaryIndepLimits();

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
  distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar( 3.0 ),
                       10.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware conditional distribution can be
// returned
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularTwoDDistribution,
                   getUpperBoundOfConditionalIndepVar )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( -1.0*MeV ),
                       0.0*cgs::centimeter );
  
  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( -1.0*MeV ),
                       10.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();

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
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfConditionalIndepVar( 3.0*MeV ),
                       10.0*cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the bounds of two distributions can be compared
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   hasSamePrimaryBounds )
{
  // Self test
  TEST_ASSERT( distribution->hasSamePrimaryBounds( *distribution ) );

  // Create a test distribution with same lower bound, different upper bound
  std::shared_ptr<Utility::PartiallyTabularTwoDDistribution> test_dist;

  {
    Utility::PartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 0.0;
    distribution_data[0].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );
    
    // Create the secondary distribution in the second bin
    distribution_data[1].first = 1.0;
    distribution_data[1].second.reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.0, 10.0 ) );

    test_dist.reset( new Utility::InterpolatedPartiallyTabularTwoDDistribution<Utility::LinLinLin,Utility::UnitBase>(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *test_dist ) );

  // Create a test distribution with different lower bound, same upper bound
  {
    Utility::PartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 1.0;
    distribution_data[0].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );
    
    // Create the secondary distribution in the second bin
    distribution_data[1].first = 2.0;
    distribution_data[1].second.reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.0, 10.0 ) );

    test_dist.reset( new Utility::InterpolatedPartiallyTabularTwoDDistribution<Utility::LinLinLin,Utility::UnitBase>(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *test_dist ) );

  // Create a test distribution with different bounds
  {
    Utility::PartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 0.5;
    distribution_data[0].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );
    
    // Create the secondary distribution in the second bin
    distribution_data[1].first = 1.5;
    distribution_data[1].second.reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.0, 10.0 ) );

    test_dist.reset( new Utility::InterpolatedPartiallyTabularTwoDDistribution<Utility::LinLinLin,Utility::UnitBase>(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *test_dist ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution, evaluate )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 10.0 ), exp( -10.0 ) );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 11.0 ), 0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.5, 1.25 ),
                          1.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.5, 5.0 ),
                          0.33782529799939026,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.5, 8.75 ),
                          0.33336359995317505,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, 9.0 ), 0.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 2.5 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 5.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 7.5 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 8.0 ), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 1.25 ), 0.4 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 5.0 ), 0.4 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 8.75 ), 0.4 );
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
  distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularTwoDDistribution,
                   evaluate )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 5.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 10.0*cgs::centimeter ), exp( -10.0 )*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV, 1.0*cgs::centimeter ), 0.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 1.25*cgs::centimeter ),
                          1.0*barns,
                          1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 5.0*cgs::centimeter ),
                          0.33782529799939026*barns,
                          1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 0.5*MeV, 8.75*cgs::centimeter ),
                          0.33336359995317505*barns,
                          1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV, 9.0*cgs::centimeter ), 0.0*barn );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.5*MeV, 1.25*cgs::centimeter ), 0.4*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.5*MeV, 5.0*cgs::centimeter ), 0.4*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.5*MeV, 8.75*cgs::centimeter ), 0.4*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.0*barn );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // After the third bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 0.0*cgs::centimeter ), 0.1*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 5.0*cgs::centimeter ), 0.1*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 10.0*cgs::centimeter ), 0.1*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          1.0000454019910097,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.0, 10.0 ),
                          4.540199100968777e-05,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, 11.0 ), 0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 1.25 ),
                          0.7333636013273398,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 5.0 ),
                          0.07115883527686304,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 8.75 ),
                          0.06669693466067313,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.5, 9.0 ), 0.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 2.5 ), 0.2 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 5.0 ), 0.2 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 7.5 ), 0.2 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 8.0 ), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.5, 1.25 ),
                          0.13333333333333333,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.5, 5.0 ),
                          0.13333333333333333,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 1.5, 8.75 ),
                          0.13333333333333333,
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
  distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularTwoDDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 5.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 10.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::centimeter ),
                          1.0000454019910097/cgs::centimeter,
                          1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 10.0*cgs::centimeter ),
                          4.540199100968777e-05/cgs::centimeter,
                          1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 1.25*cgs::centimeter ),
                          0.7333636013273398/cgs::centimeter,
                          1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 5.0*cgs::centimeter ),
                          0.07115883527686304/cgs::centimeter,
                          1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 8.75*cgs::centimeter ),
                          0.06669693466067313/cgs::centimeter,
                          1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 9.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // On the third bin boundary
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 2.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 2.5*cgs::centimeter ), 0.2/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 5.0*cgs::centimeter ), 0.2/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 7.5*cgs::centimeter ), 0.2/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 8.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.25*cgs::centimeter ),
                          0.13333333333333333/cgs::centimeter,
                          1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 5.0*cgs::centimeter ),
                          0.13333333333333333/cgs::centimeter,
                          1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 8.75*cgs::centimeter ),
                          0.13333333333333333/cgs::centimeter,
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
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 5.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 10.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 3.0*MeV, 11.0*cgs::centimeter ), 0.0/cgs::centimeter );

  unit_aware_distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditional( -1.0 ),
              std::logic_error );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();
  
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

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  TEST_FLOATING_EQUALITY( sample, 0.6931017816607284, 1e-15 );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

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

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_FLOATING_EQUALITY( sample, 1.7698263362455464, 1e-15 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-9 );

  // Samples from upper boundary of second bin
  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

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

  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

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

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  TEST_EQUALITY_CONST( sample, 5.0 );

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
  distribution->extendBeyondPrimaryIndepLimits();

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

  distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularTwoDDistribution,
                   sampleSecondaryConditional )
{
   // Before the first bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV ),
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

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-12 );

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

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.6931017816607284*cgs::centimeter, 1e-15 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

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

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.7698263362455464*cgs::centimeter, 1e-15 );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-9 );

  // Samples from upper boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

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

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

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

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

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
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

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

  unit_aware_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  unsigned trials = 0u;
  
  // Before the first bin - no extension
  TEST_THROW( distribution->sampleSecondaryConditionalAndRecordTrials( -1.0, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 0u );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();
  
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

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  TEST_FLOATING_EQUALITY( sample, 0.6931017816607284, 1e-15 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
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
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_FLOATING_EQUALITY( sample, 1.7698263362455464, 1e-15 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-9 );
  TEST_EQUALITY_CONST( trials, 3u );

  // Samples from upper boundary of second bin
  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6u );

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

  TEST_EQUALITY_CONST( sample, 2.5 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

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

  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  TEST_EQUALITY_CONST( sample, 5.0 );
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
  distribution->extendBeyondPrimaryIndepLimits();

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
  
  distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareInterpolatedPartiallyTabularTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  unsigned trials = 0u;
  
  // Before the first bin - no extension
  TEST_THROW( unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials ),
              std::logic_error );
  TEST_EQUALITY_CONST( trials, 0u );

  // Before the first bin - with extension
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();
  
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

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.6931017816607284*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
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
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;

  // Samples from lower boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.7698263362455464*cgs::centimeter, 1e-15 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-9 );
  TEST_EQUALITY_CONST( trials, 3u );

  // Samples from upper boundary of second bin
  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 5u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6u );

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

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3u );

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

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
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
  unit_aware_distribution->extendBeyondPrimaryIndepLimits();

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
  
  unit_aware_distribution->limitToPrimaryIndepLimits();

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the two-dimensional distribution
  {
    Utility::PartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 4 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 0.0;
    distribution_data[0].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );
    
    // Create the secondary distribution in the second bin
    distribution_data[1].first = 0.0;
    distribution_data[1].second.reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.0, 10.0 ) );
    
    // Create the secondary distribution in the third bin
    distribution_data[2].first = 1.0;
    distribution_data[2].second.reset( new Utility::UniformDistribution( 2.5, 7.5, 1.0 ) );
    
    // Create the secondary distribution beyond the third bin
    distribution_data[3].first = 2.0;
    distribution_data[3].second = distribution_data[0].second;
    
    distribution.reset( new Utility::InterpolatedPartiallyTabularTwoDDistribution<Utility::LinLinLin,Utility::UnitBase>(
                                                         distribution_data ) );
  }

  // Create the unit-aware two-dimensional distribution
  {
    std::vector<quantity<MegaElectronVolt> > primary_bins( 4 );
    
    Teuchos::Array<std::shared_ptr<const Utility::UnitAwareOneDDistribution<cgs::length,Barn> > > secondary_dists( 4 );
    
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
    
    unit_aware_distribution.reset( new Utility::UnitAwareInterpolatedPartiallyTabularTwoDDistribution<Utility::LinLinLin,Utility::UnitBase,MegaElectronVolt,cgs::length,Barn>( primary_bins, secondary_dists ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLinLinLinInterpolatedPartiallyTabularTwoDDistribution.cpp
//---------------------------------------------------------------------------//
