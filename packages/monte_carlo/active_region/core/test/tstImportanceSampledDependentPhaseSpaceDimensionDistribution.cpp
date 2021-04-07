//---------------------------------------------------------------------------//
//!
//! \file   tstImportanceSampledDependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Importance sampled dependent phase space dimension dist. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using namespace MonteCarlo;

typedef std::tuple<
  /* primary spatial dimension */
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION> >,
  /* secondary spatial dimension */
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION> >,
  /* tertiary spatial dimension */
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION> >,
  /* primary directional dimension */
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION> >,
  /* secondary directional dimension */
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION> >,
  /* tertiary directional dimension */
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION> >,
  /* energy dimension */
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION> >,
  /* time dimension */
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION> >,
  std::tuple<std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION>,
             std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION> >
 > TestPhaseSpaceDimensions;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::BasicBivariateDistribution> raw_distribution;

std::shared_ptr<const Utility::BasicBivariateDistribution>
raw_importance_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test that the dimension can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     getDimension,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                                               raw_distribution,
                                               raw_importance_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getDimension(), Dimension );
}

//---------------------------------------------------------------------------//
// Test that the dimension class can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     getDimensionClass,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getDimensionClass(),
                       MonteCarlo::PhaseSpaceDimensionTraits<Dimension>::getClass() );
}

//---------------------------------------------------------------------------//
// Test that the indep. dimension can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     getParentDimension,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension> >
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getParentDimension(),
                       ParentDimension );
}

//---------------------------------------------------------------------------//
// Test that the indep. dimension class can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     getParentDimensionClass,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension> >
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getParentDimensionClass(),
                       MonteCarlo::PhaseSpaceDimensionTraits<ParentDimension>::getClass() );
}

//---------------------------------------------------------------------------//
// Test that the distribution type name can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     getDistributionTypeName,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getDistributionTypeName(),
                       "BasicBivariateDistribution" );
}

//---------------------------------------------------------------------------//
// Test that the distribution type name can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     isIndependent,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  FRENSIE_CHECK( !dimension_distribution->isIndependent() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is dependent on another dimension
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     isDependentOnDimension,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  FRENSIE_CHECK( dimension_distribution->isDependentOnDimension( ParentDimension ) );
  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( Dimension ) );
}

//---------------------------------------------------------------------------//
// Test if the distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     isContinuous,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  FRENSIE_CHECK( dimension_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     isTabular,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  FRENSIE_CHECK( dimension_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is uniform
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     isUniform,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  FRENSIE_CHECK( !dimension_distribution->isUniform() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is uniform
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     hasForm,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  FRENSIE_CHECK( !dimension_distribution->hasForm( Utility::DELTA_DISTRIBUTION) );
  FRENSIE_CHECK( !dimension_distribution->hasForm( Utility::UNIFORM_DISTRIBUTION ) );
}

//---------------------------------------------------------------------------//
// Test if the distribution can be evaluated without a cascade
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     evaluateWithoutCascade,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );
  setCoordinate<Dimension>( point, 0.1 );
  
  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension value on first bin
  setCoordinate<ParentDimension>( point, 0.1 );
  setCoordinate<Dimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension value inside of first bin
  setCoordinate<ParentDimension>( point, 0.3 );
  setCoordinate<Dimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension value on second bin
  setCoordinate<ParentDimension>( point, 0.5 );
  setCoordinate<Dimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.6 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       exp(-0.6) );

  setCoordinate<Dimension>( point, 0.8 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       exp(-0.8) );

  setCoordinate<Dimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension value in second bin
  setCoordinate<ParentDimension>( point, 0.7 );
  setCoordinate<Dimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.6 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       exp(-0.6) );

  setCoordinate<Dimension>( point, 0.8 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       exp(-0.8) );

  setCoordinate<Dimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension value on distribution upper bound
  setCoordinate<ParentDimension>( point, 0.9 );
  setCoordinate<Dimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.6 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       exp(-0.6) );

  setCoordinate<Dimension>( point, 0.8 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       exp(-0.8) );

  setCoordinate<Dimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );
  setCoordinate<Dimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     sampleWithoutCascade,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );

  FRENSIE_CHECK_THROW( dimension_distribution->sampleWithoutCascade( point ),
              std::logic_error );

  // Parent dimension value on first bin
  setCoordinate<ParentDimension>( point, 0.1 );
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );

  // Parent dimension value in first bin
  setCoordinate<ParentDimension>( point, 0.3 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );

  // Parent dimension value on second bin
  setCoordinate<ParentDimension>( point, 0.5 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.1033311132253991,
                          1e-12 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.9983352757296112,
                          1e-12 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.903331113225399,
                          1e-12 );

  // Parent dimension value in second bin
  setCoordinate<ParentDimension>( point, 0.7 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.1033311132253991,
                          1e-12 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.9983352757296112,
                          1e-12 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.903331113225399,
                          1e-12 );

  // Parent dimension value on distribution upper bound
  setCoordinate<ParentDimension>( point, 0.9 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.1033311132253991,
                          1e-12 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.9983352757296112,
                          1e-12 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.903331113225399,
                          1e-12 );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );

  FRENSIE_CHECK_THROW( dimension_distribution->sampleWithoutCascade( point ),
              std::logic_error );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     sampleAndRecordTrialsWithoutCascade,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  MonteCarlo::PhaseSpaceDimensionDistribution::Counter trials = 0;

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );

  FRENSIE_CHECK_THROW( dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials ),
              std::logic_error );

  trials = 0;

  // Parent dimension value on first bin
  setCoordinate<ParentDimension>( point, 0.1 );
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  // Parent dimension value in first bin
  setCoordinate<ParentDimension>( point, 0.3 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 4 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 5 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 6 );

  // Parent dimension value on second bin
  setCoordinate<ParentDimension>( point, 0.5 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.1033311132253991,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 7 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.9983352757296112,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 8 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.903331113225399,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 9 );

  // Parent dimension value in second bin
  setCoordinate<ParentDimension>( point, 0.7 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.1033311132253991,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 10 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.9983352757296112,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.903331113225399,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 12 );

  // Parent dimension value on distribution upper bound
  setCoordinate<ParentDimension>( point, 0.9 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.1033311132253991,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 13 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.9983352757296112,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 14 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.903331113225399,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 15 );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );

  FRENSIE_CHECK_THROW( dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials ),
              std::logic_error );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Test that the dimension value can be set and weighed approperiately
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                     ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                     setDimensionValueAndApplyWeight,
                     TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>(
                             raw_distribution, raw_importance_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );

  FRENSIE_CHECK_THROW( dimension_distribution->setDimensionValueAndApplyWeight( point, 0.1 ),
              std::logic_error );

  // Parent dimension value on first bin
  setCoordinate<ParentDimension>( point, 0.1 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.5 );
  
  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.5 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<Dimension>( point ), 2.5 );
  
  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.7 );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<Dimension>( point ), 2.5 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.9 );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.9 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<Dimension>( point ), 2.5 );

  // Parent dimension value on second bin
  setCoordinate<ParentDimension>( point, 0.5 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.6 );
  
  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          5.516655566126995,
                          1e-12 );
  
  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.7 );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          4.991676378648056,
                          1e-12 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.8 );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          4.516655566126995,
                          1e-12 );

  // Parent dimension value on distribution upper bound
  setCoordinate<ParentDimension>( point, 0.9 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.6 );
  
  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          5.516655566126995,
                          1e-12 );
  
  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.7 );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          4.991676378648056,
                          1e-12 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.8 );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          4.516655566126995,
                          1e-12 );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );

  FRENSIE_CHECK_THROW( dimension_distribution->setDimensionValueAndApplyWeight( point, 0.1 ),
              std::logic_error );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ImportanceSampledDependentPhaseSpaceDimensionDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_importance_sampled_dependent_phase_dimension_distribution" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    // Create the raw distribution
    std::shared_ptr<const Utility::BasicBivariateDistribution>
      raw_distribution;

    {
      std::vector<double> primary_grid( {0.1, 0.5, 0.9} );

      std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
        secondary_dists( 3 );

      secondary_dists[0].reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );
      secondary_dists[1].reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.6, 0.8 ) );
      secondary_dists[2] = secondary_dists[1];

      Utility::HistogramPartiallyTabularBasicBivariateDistribution* local_raw_distribution =
        new Utility::HistogramPartiallyTabularBasicBivariateDistribution( primary_grid, secondary_dists );

      local_raw_distribution->limitToPrimaryIndepLimits();
    
      raw_distribution.reset( local_raw_distribution );
    }

    // Create the importance distribution
    std::shared_ptr<const Utility::BasicBivariateDistribution>
      importance_distribution;
    
    {
      std::vector<double> primary_grid( {0.1, 0.5, 0.9} );
      std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
        secondary_dists( 3 );

      secondary_dists[0].reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );
      secondary_dists[1].reset( new Utility::UniformDistribution( 0.6, 0.8, 0.4 ) );
      secondary_dists[2] = secondary_dists[1];
    
      Utility::HistogramFullyTabularBasicBivariateDistribution*
        local_importance_distribution =
        new Utility::HistogramFullyTabularBasicBivariateDistribution( primary_grid, secondary_dists );
    
      local_importance_distribution->limitToPrimaryIndepLimits();
    
      importance_distribution.reset( local_importance_distribution );
    }

    // Create the dependent primary spatial distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_primary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledSecondarySpatialDependentPrimarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_primary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledTertiarySpatialDependentPrimarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_primary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledPrimaryDirectionalDependentPrimarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_primary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledSecondaryDirectionalDependentPrimarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_primary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledTertiaryDirectionalDependentPrimarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_primary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledEnergyDependentPrimarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_primary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledTimeDependentPrimarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    // Create the dependent secondary spatial distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledPrimarySpatialDependentSecondarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledTertiarySpatialDependentSecondarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledPrimaryDirectionalDependentSecondarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledSecondaryDirectionalDependentSecondarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledTertiaryDirectionalDependentSecondarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledEnergyDependentSecondarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledTimeDependentSecondarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    // Create the dependent tertiary spatial distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledPrimarySpatialDependentTertiarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledSecondarySpatialDependentTertiarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledPrimaryDirectionalDependentTertiarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledSecondaryDirectionalDependentTertiarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledTertiaryDirectionalDependentTertiarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledEnergyDependentTertiarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledTimeDependentTertiarySpatialDimensionDistribution( raw_distribution, importance_distribution ) );

    // Create the dependent primary directional distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_primary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledPrimarySpatialDependentPrimaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_primary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledSecondarySpatialDependentPrimaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_primary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledTertiarySpatialDependentPrimaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_primary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledSecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_primary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledTertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_primary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledEnergyDependentPrimaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_primary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledTimeDependentPrimaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    // Create the dependent secondary directional distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_secondary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledPrimarySpatialDependentSecondaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_secondary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledSecondarySpatialDependentSecondaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_secondary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledTertiarySpatialDependentSecondaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_secondary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledPrimaryDirectionalDependentSecondaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_secondary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledTertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_secondary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledEnergyDependentSecondaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_secondary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledTimeDependentSecondaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    // Create the dependent tertiary directional distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledPrimarySpatialDependentTertiaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledSecondarySpatialDependentTertiaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledTertiarySpatialDependentTertiaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledPrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledSecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledEnergyDependentTertiaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledTimeDependentTertiaryDirectionalDimensionDistribution( raw_distribution, importance_distribution ) );

    // Create the dependent energy distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_energy_dimension_distribution( new MonteCarlo::ImportanceSampledPrimarySpatialDependentEnergyDimensionDistribution( raw_distribution, importance_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_energy_dimension_distribution( new MonteCarlo::ImportanceSampledSecondarySpatialDependentEnergyDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_energy_dimension_distribution( new MonteCarlo::ImportanceSampledTertiarySpatialDependentEnergyDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_energy_dimension_distribution( new MonteCarlo::ImportanceSampledPrimaryDirectionalDependentEnergyDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_energy_dimension_distribution( new MonteCarlo::ImportanceSampledSecondaryDirectionalDependentEnergyDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_energy_dimension_distribution( new MonteCarlo::ImportanceSampledTertiaryDirectionalDependentEnergyDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_energy_dimension_distribution( new MonteCarlo::ImportanceSampledTimeDependentEnergyDimensionDistribution( raw_distribution, importance_distribution ) );

    // Create the dependent time distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_time_dimension_distribution( new MonteCarlo::ImportanceSampledPrimarySpatialDependentTimeDimensionDistribution( raw_distribution, importance_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_time_dimension_distribution( new MonteCarlo::ImportanceSampledSecondarySpatialDependentTimeDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_time_dimension_distribution( new MonteCarlo::ImportanceSampledTertiarySpatialDependentTimeDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_time_dimension_distribution( new MonteCarlo::ImportanceSampledPrimaryDirectionalDependentTimeDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_time_dimension_distribution( new MonteCarlo::ImportanceSampledSecondaryDirectionalDependentTimeDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_time_dimension_distribution( new MonteCarlo::ImportanceSampledTertiaryDirectionalDependentTimeDimensionDistribution( raw_distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_time_dimension_distribution( new MonteCarlo::ImportanceSampledEnergyDependentTimeDimensionDistribution( raw_distribution, importance_distribution ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_directional_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_directional_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(energy_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(time_dependent_primary_spatial_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_spatial_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_directional_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_directional_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(energy_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(time_dependent_secondary_spatial_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_spatial_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_directional_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_directional_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(energy_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(time_dependent_tertiary_spatial_dimension_distribution) );
    
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_spatial_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_directional_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(energy_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(time_dependent_primary_directional_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_spatial_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_directional_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(energy_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(time_dependent_secondary_directional_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_spatial_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_directional_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_directional_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(energy_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(time_dependent_tertiary_directional_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_spatial_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_directional_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_directional_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(time_dependent_energy_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_spatial_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_directional_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_directional_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(energy_dependent_time_dimension_distribution) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    secondary_spatial_dependent_primary_spatial_dimension_distribution,
    tertiary_spatial_dependent_primary_spatial_dimension_distribution,
    primary_directional_dependent_primary_spatial_dimension_distribution,
    secondary_directional_dependent_primary_spatial_dimension_distribution,
    tertiary_directional_dependent_primary_spatial_dimension_distribution,
    energy_dependent_primary_spatial_dimension_distribution,
    time_dependent_primary_spatial_dimension_distribution;

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    primary_spatial_dependent_secondary_spatial_dimension_distribution,
    tertiary_spatial_dependent_secondary_spatial_dimension_distribution,
    primary_directional_dependent_secondary_spatial_dimension_distribution,
    secondary_directional_dependent_secondary_spatial_dimension_distribution,
    tertiary_directional_dependent_secondary_spatial_dimension_distribution,
    energy_dependent_secondary_spatial_dimension_distribution,
    time_dependent_secondary_spatial_dimension_distribution;

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    primary_spatial_dependent_tertiary_spatial_dimension_distribution,
    secondary_spatial_dependent_tertiary_spatial_dimension_distribution,
    primary_directional_dependent_tertiary_spatial_dimension_distribution,
    secondary_directional_dependent_tertiary_spatial_dimension_distribution,
    tertiary_directional_dependent_tertiary_spatial_dimension_distribution,
    energy_dependent_tertiary_spatial_dimension_distribution,
    time_dependent_tertiary_spatial_dimension_distribution;

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    primary_spatial_dependent_primary_directional_dimension_distribution,
    secondary_spatial_dependent_primary_directional_dimension_distribution,
    tertiary_spatial_dependent_primary_directional_dimension_distribution,
    secondary_directional_dependent_primary_directional_dimension_distribution,
    tertiary_directional_dependent_primary_directional_dimension_distribution,
    energy_dependent_primary_directional_dimension_distribution,
    time_dependent_primary_directional_dimension_distribution;

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    primary_spatial_dependent_secondary_directional_dimension_distribution,
    secondary_spatial_dependent_secondary_directional_dimension_distribution,
    tertiary_spatial_dependent_secondary_directional_dimension_distribution,
    primary_directional_dependent_secondary_directional_dimension_distribution,
    tertiary_directional_dependent_secondary_directional_dimension_distribution,
    energy_dependent_secondary_directional_dimension_distribution,
    time_dependent_secondary_directional_dimension_distribution;

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    primary_spatial_dependent_tertiary_directional_dimension_distribution,
    secondary_spatial_dependent_tertiary_directional_dimension_distribution,
    tertiary_spatial_dependent_tertiary_directional_dimension_distribution,
    primary_directional_dependent_tertiary_directional_dimension_distribution,
    secondary_directional_dependent_tertiary_directional_dimension_distribution,
    energy_dependent_tertiary_directional_dimension_distribution,
    time_dependent_tertiary_directional_dimension_distribution;

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    primary_spatial_dependent_energy_dimension_distribution,
    secondary_spatial_dependent_energy_dimension_distribution,
    tertiary_spatial_dependent_energy_dimension_distribution,
    primary_directional_dependent_energy_dimension_distribution,
    secondary_directional_dependent_energy_dimension_distribution,
    tertiary_directional_dependent_energy_dimension_distribution,
    time_dependent_energy_dimension_distribution;

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    primary_spatial_dependent_time_dimension_distribution,
    secondary_spatial_dependent_time_dimension_distribution,
    tertiary_spatial_dependent_time_dimension_distribution,
    primary_directional_dependent_time_dimension_distribution,
    secondary_directional_dependent_time_dimension_distribution,
    tertiary_directional_dependent_time_dimension_distribution,
    energy_dependent_time_dimension_distribution;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_directional_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_directional_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(energy_dependent_primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(time_dependent_primary_spatial_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_spatial_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_directional_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_directional_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(energy_dependent_secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(time_dependent_secondary_spatial_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_spatial_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_directional_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_directional_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(energy_dependent_tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(time_dependent_tertiary_spatial_dimension_distribution) );
    
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_spatial_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_directional_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(energy_dependent_primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(time_dependent_primary_directional_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_spatial_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_directional_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(energy_dependent_secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(time_dependent_secondary_directional_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_spatial_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_directional_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_directional_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(energy_dependent_tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(time_dependent_tertiary_directional_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_spatial_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_directional_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_directional_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(time_dependent_energy_dimension_distribution) );

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_spatial_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_spatial_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_spatial_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_directional_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_directional_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_directional_dependent_time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(energy_dependent_time_dimension_distribution) );

    iarchive.reset();

    {
      FRENSIE_CHECK_EQUAL( secondary_spatial_dependent_primary_spatial_dimension_distribution->getDimension(),
                           PRIMARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_spatial_dependent_primary_spatial_dimension_distribution->getDimension(),
                           PRIMARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( primary_directional_dependent_primary_spatial_dimension_distribution->getDimension(),
                           PRIMARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_directional_dependent_primary_spatial_dimension_distribution->getDimension(),
                           PRIMARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_directional_dependent_primary_spatial_dimension_distribution->getDimension(),
                           PRIMARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( energy_dependent_primary_spatial_dimension_distribution->getDimension(),
                           PRIMARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( time_dependent_primary_spatial_dimension_distribution->getDimension(),
                           PRIMARY_SPATIAL_DIMENSION );

      auto concrete_secondary_spatial_dependent_primary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::SecondarySpatialDependentPrimarySpatialDimensionDistribution*>( secondary_spatial_dependent_primary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_spatial_dependent_primary_spatial_dimension_distribution->getParentDimension(),
                           SECONDARY_SPATIAL_DIMENSION );

      auto concrete_tertiary_spatial_dependent_primary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::TertiarySpatialDependentPrimarySpatialDimensionDistribution*>( tertiary_spatial_dependent_primary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_spatial_dependent_primary_spatial_dimension_distribution->getParentDimension(),
                           TERTIARY_SPATIAL_DIMENSION );

      auto concrete_primary_directional_dependent_primary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::PrimaryDirectionalDependentPrimarySpatialDimensionDistribution*>( primary_directional_dependent_primary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_directional_dependent_primary_spatial_dimension_distribution->getParentDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );

      auto concrete_secondary_directional_dependent_primary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::SecondaryDirectionalDependentPrimarySpatialDimensionDistribution*>( secondary_directional_dependent_primary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_directional_dependent_primary_spatial_dimension_distribution->getParentDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );

      auto concrete_tertiary_directional_dependent_primary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::TertiaryDirectionalDependentPrimarySpatialDimensionDistribution*>( tertiary_directional_dependent_primary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_directional_dependent_primary_spatial_dimension_distribution->getParentDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );

      auto concrete_energy_dependent_primary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::EnergyDependentPrimarySpatialDimensionDistribution*>( energy_dependent_primary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_energy_dependent_primary_spatial_dimension_distribution->getParentDimension(),
                           ENERGY_DIMENSION );

      auto concrete_time_dependent_primary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::TimeDependentPrimarySpatialDimensionDistribution*>( time_dependent_primary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_time_dependent_primary_spatial_dimension_distribution->getParentDimension(),
                           TIME_DIMENSION );

      MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                         directional_coord_conversion_policy );

      // Parent dimension value outside of distribution bounds
      setCoordinate<ENERGY_DIMENSION>( point, 0.05 );

      FRENSIE_CHECK_THROW( energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point ),
                           std::logic_error );

      // Parent dimension value on first bin
      setCoordinate<ENERGY_DIMENSION>( point, 0.1 );
      
      std::vector<double> fake_stream( 3 );
      fake_stream[0] = 0.0;
      fake_stream[1] = 0.5;
      fake_stream[2] = 1.0-1e-15;
      
      Utility::RandomNumberGenerator::setFakeStream( fake_stream );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.5 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       1.0,
                                       1e-15 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );

      FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.7 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       1.0,
                                       1e-15 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.9, 1e-15 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       1.0,
                                       1e-15 );
      
      // Parent dimension value in first bin
      setCoordinate<ENERGY_DIMENSION>( point, 0.3 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.5 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                          1.0,
                                       1e-15 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.7 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       1.0,
                                       1e-15 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.9, 1e-15 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       1.0,
                                       1e-15 );
      
      // Parent dimension value on second bin
      setCoordinate<ENERGY_DIMENSION>( point, 0.5 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.6 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       1.1033311132253991,
                                       1e-12 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.7 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       0.9983352757296112,
                                       1e-12 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.8, 1e-15 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       0.903331113225399,
                                       1e-12 );
      
      // Parent dimension value in second bin
      setCoordinate<ENERGY_DIMENSION>( point, 0.7 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.6 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       1.1033311132253991,
                                       1e-12 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.7 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       0.9983352757296112,
                                       1e-12 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.8, 1e-15 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       0.903331113225399,
                                       1e-12 );
      
      // Parent dimension value on distribution upper bound
      setCoordinate<ENERGY_DIMENSION>( point, 0.9 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.6 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       1.1033311132253991,
                                       1e-12 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.7 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       0.9983352757296112,
                                       1e-12 );
      
      energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.8, 1e-15 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                       0.903331113225399,
                                       1e-12 );

      // Parent dimension value outside of distribution bounds
      setCoordinate<ENERGY_DIMENSION>( point, 1.0 );
      
      FRENSIE_CHECK_THROW( energy_dependent_primary_spatial_dimension_distribution->sampleWithoutCascade( point ),
                           std::logic_error );
      
      Utility::RandomNumberGenerator::unsetFakeStream();
    }

    {
      FRENSIE_CHECK_EQUAL( primary_spatial_dependent_secondary_spatial_dimension_distribution->getDimension(),
                           SECONDARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_spatial_dependent_secondary_spatial_dimension_distribution->getDimension(),
                           SECONDARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( primary_directional_dependent_secondary_spatial_dimension_distribution->getDimension(),
                           SECONDARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_directional_dependent_secondary_spatial_dimension_distribution->getDimension(),
                           SECONDARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_directional_dependent_secondary_spatial_dimension_distribution->getDimension(),
                           SECONDARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( energy_dependent_secondary_spatial_dimension_distribution->getDimension(),
                           SECONDARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( time_dependent_secondary_spatial_dimension_distribution->getDimension(),
                           SECONDARY_SPATIAL_DIMENSION );

      auto concrete_primary_spatial_dependent_secondary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::PrimarySpatialDependentSecondarySpatialDimensionDistribution*>( primary_spatial_dependent_secondary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_spatial_dependent_secondary_spatial_dimension_distribution->getParentDimension(),
                           PRIMARY_SPATIAL_DIMENSION );

      auto concrete_tertiary_spatial_dependent_secondary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::TertiarySpatialDependentSecondarySpatialDimensionDistribution*>( tertiary_spatial_dependent_secondary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_spatial_dependent_secondary_spatial_dimension_distribution->getParentDimension(),
                           TERTIARY_SPATIAL_DIMENSION );

      auto concrete_primary_directional_dependent_secondary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::PrimaryDirectionalDependentSecondarySpatialDimensionDistribution*>( primary_directional_dependent_secondary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_directional_dependent_secondary_spatial_dimension_distribution->getParentDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );

      auto concrete_secondary_directional_dependent_secondary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::SecondaryDirectionalDependentSecondarySpatialDimensionDistribution*>( secondary_directional_dependent_secondary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_directional_dependent_secondary_spatial_dimension_distribution->getParentDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );

      auto concrete_tertiary_directional_dependent_secondary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::TertiaryDirectionalDependentSecondarySpatialDimensionDistribution*>( tertiary_directional_dependent_secondary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_directional_dependent_secondary_spatial_dimension_distribution->getParentDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );

      auto concrete_energy_dependent_secondary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::EnergyDependentSecondarySpatialDimensionDistribution*>( energy_dependent_secondary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_energy_dependent_secondary_spatial_dimension_distribution->getParentDimension(),
                           ENERGY_DIMENSION );

      auto concrete_time_dependent_secondary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::TimeDependentSecondarySpatialDimensionDistribution*>( time_dependent_secondary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_time_dependent_secondary_spatial_dimension_distribution->getParentDimension(),
                           TIME_DIMENSION );
    }

    {
      FRENSIE_CHECK_EQUAL( primary_spatial_dependent_tertiary_spatial_dimension_distribution->getDimension(),
                           TERTIARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_spatial_dependent_tertiary_spatial_dimension_distribution->getDimension(),
                           TERTIARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( primary_directional_dependent_tertiary_spatial_dimension_distribution->getDimension(),
                           TERTIARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_directional_dependent_tertiary_spatial_dimension_distribution->getDimension(),
                           TERTIARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_directional_dependent_tertiary_spatial_dimension_distribution->getDimension(),
                           TERTIARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( energy_dependent_tertiary_spatial_dimension_distribution->getDimension(),
                           TERTIARY_SPATIAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( time_dependent_tertiary_spatial_dimension_distribution->getDimension(),
                           TERTIARY_SPATIAL_DIMENSION );

      auto concrete_primary_spatial_dependent_tertiary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::PrimarySpatialDependentTertiarySpatialDimensionDistribution*>( primary_spatial_dependent_tertiary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_spatial_dependent_tertiary_spatial_dimension_distribution->getParentDimension(),
                           PRIMARY_SPATIAL_DIMENSION );

      auto concrete_secondary_spatial_dependent_tertiary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::SecondarySpatialDependentTertiarySpatialDimensionDistribution*>( secondary_spatial_dependent_tertiary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_spatial_dependent_tertiary_spatial_dimension_distribution->getParentDimension(),
                           SECONDARY_SPATIAL_DIMENSION );

      auto concrete_primary_directional_dependent_tertiary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::PrimaryDirectionalDependentTertiarySpatialDimensionDistribution*>( primary_directional_dependent_tertiary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_directional_dependent_tertiary_spatial_dimension_distribution->getParentDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );

      auto concrete_secondary_directional_dependent_tertiary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::SecondaryDirectionalDependentTertiarySpatialDimensionDistribution*>( secondary_directional_dependent_tertiary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_directional_dependent_tertiary_spatial_dimension_distribution->getParentDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );

      auto concrete_tertiary_directional_dependent_tertiary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::TertiaryDirectionalDependentTertiarySpatialDimensionDistribution*>( tertiary_directional_dependent_tertiary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_directional_dependent_tertiary_spatial_dimension_distribution->getParentDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );

      auto concrete_energy_dependent_tertiary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::EnergyDependentTertiarySpatialDimensionDistribution*>( energy_dependent_tertiary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_energy_dependent_tertiary_spatial_dimension_distribution->getParentDimension(),
                           ENERGY_DIMENSION );

      auto concrete_time_dependent_tertiary_spatial_dimension_distribution = dynamic_cast<const MonteCarlo::TimeDependentTertiarySpatialDimensionDistribution*>( time_dependent_tertiary_spatial_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_time_dependent_tertiary_spatial_dimension_distribution->getParentDimension(),
                           TIME_DIMENSION );
    }

    {
      FRENSIE_CHECK_EQUAL( primary_spatial_dependent_primary_directional_dimension_distribution->getDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_spatial_dependent_primary_directional_dimension_distribution->getDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_spatial_dependent_primary_directional_dimension_distribution->getDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_directional_dependent_primary_directional_dimension_distribution->getDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_directional_dependent_primary_directional_dimension_distribution->getDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( energy_dependent_primary_directional_dimension_distribution->getDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( time_dependent_primary_directional_dimension_distribution->getDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );

      auto concrete_primary_spatial_dependent_primary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::PrimarySpatialDependentPrimaryDirectionalDimensionDistribution*>( primary_spatial_dependent_primary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_spatial_dependent_primary_directional_dimension_distribution->getParentDimension(),
                           PRIMARY_SPATIAL_DIMENSION );

      auto concrete_secondary_spatial_dependent_primary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::SecondarySpatialDependentPrimaryDirectionalDimensionDistribution*>( secondary_spatial_dependent_primary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_spatial_dependent_primary_directional_dimension_distribution->getParentDimension(),
                           SECONDARY_SPATIAL_DIMENSION );

      auto concrete_tertiary_spatial_dependent_primary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::TertiarySpatialDependentPrimaryDirectionalDimensionDistribution*>( tertiary_spatial_dependent_primary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_spatial_dependent_primary_directional_dimension_distribution->getParentDimension(),
                           TERTIARY_SPATIAL_DIMENSION );

      auto concrete_secondary_directional_dependent_primary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::SecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution*>( secondary_directional_dependent_primary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_directional_dependent_primary_directional_dimension_distribution->getParentDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );

      auto concrete_tertiary_directional_dependent_primary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::TertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution*>( tertiary_directional_dependent_primary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_directional_dependent_primary_directional_dimension_distribution->getParentDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );

      auto concrete_energy_dependent_primary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::EnergyDependentPrimaryDirectionalDimensionDistribution*>( energy_dependent_primary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_energy_dependent_primary_directional_dimension_distribution->getParentDimension(),
                           ENERGY_DIMENSION );

      auto concrete_time_dependent_primary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::TimeDependentPrimaryDirectionalDimensionDistribution*>( time_dependent_primary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_time_dependent_primary_directional_dimension_distribution->getParentDimension(),
                           TIME_DIMENSION );
    }

    {
      FRENSIE_CHECK_EQUAL( primary_spatial_dependent_secondary_directional_dimension_distribution->getDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_spatial_dependent_secondary_directional_dimension_distribution->getDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_spatial_dependent_secondary_directional_dimension_distribution->getDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( primary_directional_dependent_secondary_directional_dimension_distribution->getDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_directional_dependent_secondary_directional_dimension_distribution->getDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( energy_dependent_secondary_directional_dimension_distribution->getDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( time_dependent_secondary_directional_dimension_distribution->getDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );

      auto concrete_primary_spatial_dependent_secondary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::PrimarySpatialDependentSecondaryDirectionalDimensionDistribution*>( primary_spatial_dependent_secondary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_spatial_dependent_secondary_directional_dimension_distribution->getParentDimension(),
                           PRIMARY_SPATIAL_DIMENSION );

      auto concrete_secondary_spatial_dependent_secondary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::SecondarySpatialDependentSecondaryDirectionalDimensionDistribution*>( secondary_spatial_dependent_secondary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_spatial_dependent_secondary_directional_dimension_distribution->getParentDimension(),
                           SECONDARY_SPATIAL_DIMENSION );

      auto concrete_tertiary_spatial_dependent_secondary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::TertiarySpatialDependentSecondaryDirectionalDimensionDistribution*>( tertiary_spatial_dependent_secondary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_spatial_dependent_secondary_directional_dimension_distribution->getParentDimension(),
                           TERTIARY_SPATIAL_DIMENSION );

      auto concrete_primary_directional_dependent_secondary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::PrimaryDirectionalDependentSecondaryDirectionalDimensionDistribution*>( primary_directional_dependent_secondary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_directional_dependent_secondary_directional_dimension_distribution->getParentDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );

      auto concrete_tertiary_directional_dependent_secondary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::TertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution*>( tertiary_directional_dependent_secondary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_directional_dependent_secondary_directional_dimension_distribution->getParentDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );

      auto concrete_energy_dependent_secondary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::EnergyDependentSecondaryDirectionalDimensionDistribution*>( energy_dependent_secondary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_energy_dependent_secondary_directional_dimension_distribution->getParentDimension(),
                           ENERGY_DIMENSION );

      auto concrete_time_dependent_secondary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::TimeDependentSecondaryDirectionalDimensionDistribution*>( time_dependent_secondary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_time_dependent_secondary_directional_dimension_distribution->getParentDimension(),
                           TIME_DIMENSION );
    }

    {
      FRENSIE_CHECK_EQUAL( primary_spatial_dependent_tertiary_directional_dimension_distribution->getDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_spatial_dependent_tertiary_directional_dimension_distribution->getDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_spatial_dependent_tertiary_directional_dimension_distribution->getDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( primary_directional_dependent_tertiary_directional_dimension_distribution->getDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_directional_dependent_tertiary_directional_dimension_distribution->getDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( energy_dependent_tertiary_directional_dimension_distribution->getDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );
      FRENSIE_CHECK_EQUAL( time_dependent_tertiary_directional_dimension_distribution->getDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );

      auto concrete_primary_spatial_dependent_tertiary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::PrimarySpatialDependentTertiaryDirectionalDimensionDistribution*>( primary_spatial_dependent_tertiary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_spatial_dependent_tertiary_directional_dimension_distribution->getParentDimension(),
                           PRIMARY_SPATIAL_DIMENSION );

      auto concrete_secondary_spatial_dependent_tertiary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::SecondarySpatialDependentTertiaryDirectionalDimensionDistribution*>( secondary_spatial_dependent_tertiary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_spatial_dependent_tertiary_directional_dimension_distribution->getParentDimension(),
                           SECONDARY_SPATIAL_DIMENSION );

      auto concrete_tertiary_spatial_dependent_tertiary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::TertiarySpatialDependentTertiaryDirectionalDimensionDistribution*>( tertiary_spatial_dependent_tertiary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_spatial_dependent_tertiary_directional_dimension_distribution->getParentDimension(),
                           TERTIARY_SPATIAL_DIMENSION );

      auto concrete_primary_directional_dependent_tertiary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::PrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution*>( primary_directional_dependent_tertiary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_directional_dependent_tertiary_directional_dimension_distribution->getParentDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );

      auto concrete_secondary_directional_dependent_tertiary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::SecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution*>( secondary_directional_dependent_tertiary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_directional_dependent_tertiary_directional_dimension_distribution->getParentDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );

      auto concrete_energy_dependent_tertiary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::EnergyDependentTertiaryDirectionalDimensionDistribution*>( energy_dependent_tertiary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_energy_dependent_tertiary_directional_dimension_distribution->getParentDimension(),
                           ENERGY_DIMENSION );

      auto concrete_time_dependent_tertiary_directional_dimension_distribution = dynamic_cast<const MonteCarlo::TimeDependentTertiaryDirectionalDimensionDistribution*>( time_dependent_tertiary_directional_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_time_dependent_tertiary_directional_dimension_distribution->getParentDimension(),
                           TIME_DIMENSION );
    }

    {
      FRENSIE_CHECK_EQUAL( primary_spatial_dependent_energy_dimension_distribution->getDimension(),
                           ENERGY_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_spatial_dependent_energy_dimension_distribution->getDimension(),
                           ENERGY_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_spatial_dependent_energy_dimension_distribution->getDimension(),
                           ENERGY_DIMENSION );
      FRENSIE_CHECK_EQUAL( primary_directional_dependent_energy_dimension_distribution->getDimension(),
                           ENERGY_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_directional_dependent_energy_dimension_distribution->getDimension(),
                           ENERGY_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_directional_dependent_energy_dimension_distribution->getDimension(),
                           ENERGY_DIMENSION );
      FRENSIE_CHECK_EQUAL( time_dependent_energy_dimension_distribution->getDimension(),
                           ENERGY_DIMENSION );

      auto concrete_primary_spatial_dependent_energy_dimension_distribution = dynamic_cast<const MonteCarlo::PrimarySpatialDependentEnergyDimensionDistribution*>( primary_spatial_dependent_energy_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_spatial_dependent_energy_dimension_distribution->getParentDimension(),
                           PRIMARY_SPATIAL_DIMENSION );

      auto concrete_secondary_spatial_dependent_energy_dimension_distribution = dynamic_cast<const MonteCarlo::SecondarySpatialDependentEnergyDimensionDistribution*>( secondary_spatial_dependent_energy_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_spatial_dependent_energy_dimension_distribution->getParentDimension(),
                           SECONDARY_SPATIAL_DIMENSION );

      auto concrete_tertiary_spatial_dependent_energy_dimension_distribution = dynamic_cast<const MonteCarlo::TertiarySpatialDependentEnergyDimensionDistribution*>( tertiary_spatial_dependent_energy_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_spatial_dependent_energy_dimension_distribution->getParentDimension(),
                           TERTIARY_SPATIAL_DIMENSION );

      auto concrete_primary_directional_dependent_energy_dimension_distribution = dynamic_cast<const MonteCarlo::PrimaryDirectionalDependentEnergyDimensionDistribution*>( primary_directional_dependent_energy_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_directional_dependent_energy_dimension_distribution->getParentDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );

      auto concrete_secondary_directional_dependent_energy_dimension_distribution = dynamic_cast<const MonteCarlo::SecondaryDirectionalDependentEnergyDimensionDistribution*>( secondary_directional_dependent_energy_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_directional_dependent_energy_dimension_distribution->getParentDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );

      auto concrete_tertiary_directional_dependent_energy_dimension_distribution = dynamic_cast<const MonteCarlo::TertiaryDirectionalDependentEnergyDimensionDistribution*>( tertiary_directional_dependent_energy_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_directional_dependent_energy_dimension_distribution->getParentDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );

      auto concrete_time_dependent_energy_dimension_distribution = dynamic_cast<const MonteCarlo::TimeDependentEnergyDimensionDistribution*>( time_dependent_energy_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_time_dependent_energy_dimension_distribution->getParentDimension(),
                           TIME_DIMENSION );
    }

    {
      FRENSIE_CHECK_EQUAL( primary_spatial_dependent_time_dimension_distribution->getDimension(),
                           TIME_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_spatial_dependent_time_dimension_distribution->getDimension(),
                           TIME_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_spatial_dependent_time_dimension_distribution->getDimension(),
                           TIME_DIMENSION );
      FRENSIE_CHECK_EQUAL( primary_directional_dependent_time_dimension_distribution->getDimension(),
                           TIME_DIMENSION );
      FRENSIE_CHECK_EQUAL( secondary_directional_dependent_time_dimension_distribution->getDimension(),
                           TIME_DIMENSION );
      FRENSIE_CHECK_EQUAL( tertiary_directional_dependent_time_dimension_distribution->getDimension(),
                           TIME_DIMENSION );
      FRENSIE_CHECK_EQUAL( energy_dependent_time_dimension_distribution->getDimension(),
                           TIME_DIMENSION );

      auto concrete_primary_spatial_dependent_time_dimension_distribution = dynamic_cast<const MonteCarlo::PrimarySpatialDependentTimeDimensionDistribution*>( primary_spatial_dependent_time_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_spatial_dependent_time_dimension_distribution->getParentDimension(),
                           PRIMARY_SPATIAL_DIMENSION );

      auto concrete_secondary_spatial_dependent_time_dimension_distribution = dynamic_cast<const MonteCarlo::SecondarySpatialDependentTimeDimensionDistribution*>( secondary_spatial_dependent_time_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_spatial_dependent_time_dimension_distribution->getParentDimension(),
                           SECONDARY_SPATIAL_DIMENSION );

      auto concrete_tertiary_spatial_dependent_time_dimension_distribution = dynamic_cast<const MonteCarlo::TertiarySpatialDependentTimeDimensionDistribution*>( tertiary_spatial_dependent_time_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_spatial_dependent_time_dimension_distribution->getParentDimension(),
                           TERTIARY_SPATIAL_DIMENSION );

      auto concrete_primary_directional_dependent_time_dimension_distribution = dynamic_cast<const MonteCarlo::PrimaryDirectionalDependentTimeDimensionDistribution*>( primary_directional_dependent_time_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_primary_directional_dependent_time_dimension_distribution->getParentDimension(),
                           PRIMARY_DIRECTIONAL_DIMENSION );

      auto concrete_secondary_directional_dependent_time_dimension_distribution = dynamic_cast<const MonteCarlo::SecondaryDirectionalDependentTimeDimensionDistribution*>( secondary_directional_dependent_time_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_secondary_directional_dependent_time_dimension_distribution->getParentDimension(),
                           SECONDARY_DIRECTIONAL_DIMENSION );

      auto concrete_tertiary_directional_dependent_time_dimension_distribution = dynamic_cast<const MonteCarlo::TertiaryDirectionalDependentTimeDimensionDistribution*>( tertiary_directional_dependent_time_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_tertiary_directional_dependent_time_dimension_distribution->getParentDimension(),
                           TERTIARY_DIRECTIONAL_DIMENSION );

      auto concrete_energy_dependent_time_dimension_distribution = dynamic_cast<const MonteCarlo::EnergyDependentTimeDimensionDistribution*>( energy_dependent_time_dimension_distribution.get() );

      FRENSIE_CHECK_EQUAL( concrete_energy_dependent_time_dimension_distribution->getParentDimension(),
                           ENERGY_DIMENSION );

      MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                         directional_coord_conversion_policy );

      // Parent dimension value outside of distribution bounds
      setCoordinate<ENERGY_DIMENSION>( point, 0.05 );

      FRENSIE_CHECK_THROW( energy_dependent_time_dimension_distribution->sampleWithoutCascade( point ),
                           std::logic_error );

      // Parent dimension value on first bin
      setCoordinate<ENERGY_DIMENSION>( point, 0.1 );
      
      std::vector<double> fake_stream( 3 );
      fake_stream[0] = 0.0;
      fake_stream[1] = 0.5;
      fake_stream[2] = 1.0-1e-15;
      
      Utility::RandomNumberGenerator::setFakeStream( fake_stream );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.5 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       1.0,
                                       1e-15 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );

      FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.7 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       1.0,
                                       1e-15 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<TIME_DIMENSION>( point ), 0.9, 1e-15 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       1.0,
                                       1e-15 );
      
      // Parent dimension value in first bin
      setCoordinate<ENERGY_DIMENSION>( point, 0.3 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.5 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                          1.0,
                                       1e-15 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.7 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       1.0,
                                       1e-15 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<TIME_DIMENSION>( point ), 0.9, 1e-15 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       1.0,
                                       1e-15 );
      
      // Parent dimension value on second bin
      setCoordinate<ENERGY_DIMENSION>( point, 0.5 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.6 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       1.1033311132253991,
                                       1e-12 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.7 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       0.9983352757296112,
                                       1e-12 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<TIME_DIMENSION>( point ), 0.8, 1e-15 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       0.903331113225399,
                                       1e-12 );
      
      // Parent dimension value in second bin
      setCoordinate<ENERGY_DIMENSION>( point, 0.7 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.6 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       1.1033311132253991,
                                       1e-12 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.7 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       0.9983352757296112,
                                       1e-12 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<TIME_DIMENSION>( point ), 0.8, 1e-15 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       0.903331113225399,
                                       1e-12 );
      
      // Parent dimension value on distribution upper bound
      setCoordinate<ENERGY_DIMENSION>( point, 0.9 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.6 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       1.1033311132253991,
                                       1e-12 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.7 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       0.9983352757296112,
                                       1e-12 );
      
      energy_dependent_time_dimension_distribution->sampleWithoutCascade( point );
      
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<TIME_DIMENSION>( point ), 0.8, 1e-15 );
      FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                       0.903331113225399,
                                       1e-12 );

      // Parent dimension value outside of distribution bounds
      setCoordinate<ENERGY_DIMENSION>( point, 1.0 );
      
      FRENSIE_CHECK_THROW( energy_dependent_time_dimension_distribution->sampleWithoutCascade( point ),
                           std::logic_error );
      
      Utility::RandomNumberGenerator::unsetFakeStream();
    }    
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the distribution
  {
    std::vector<double> primary_grid( {0.1, 0.5, 0.9} );

    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 3 );

    // Create the secondary distribution in the first bin
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );
    
    // Create the secondary distribution in the second bin
    secondary_dists[1].reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.6, 0.8 ) );

    // Create the secondary distribution in the third bin
    secondary_dists[2] = secondary_dists[1];

    Utility::HistogramPartiallyTabularBasicBivariateDistribution* local_raw_distribution =
      new Utility::HistogramPartiallyTabularBasicBivariateDistribution( primary_grid, secondary_dists );

    local_raw_distribution->limitToPrimaryIndepLimits();
    
    raw_distribution.reset( local_raw_distribution );
  }

  // Create the fully tabular importance distribution
  {
    std::vector<double> primary_grid( {0.1, 0.5, 0.9} );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 3 );

    // Create the secondary distribution in the first bin
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );

    // Create the secondary distribution in the second bin
    secondary_dists[1].reset( new Utility::UniformDistribution( 0.6, 0.8, 0.4 ) );
    
    // Create the secondary distribution in the third bin
    secondary_dists[2] = secondary_dists[1];
    
    Utility::HistogramFullyTabularBasicBivariateDistribution*
      local_raw_importance_distribution =
      new Utility::HistogramFullyTabularBasicBivariateDistribution( primary_grid, secondary_dists );
    
    local_raw_importance_distribution->limitToPrimaryIndepLimits();
    
    raw_importance_distribution.reset( local_raw_importance_distribution );
  }
    
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstImportanceSampledDependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
