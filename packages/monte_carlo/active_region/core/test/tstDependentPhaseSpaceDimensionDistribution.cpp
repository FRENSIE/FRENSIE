//---------------------------------------------------------------------------//
//!
//! \file   tstDependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Dependent phase space dimension dist. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"
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

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test that the dimension can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   getDimension,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getDimension(), Dimension );
}

//---------------------------------------------------------------------------//
// Test that the dimension class can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   getDimensionClass,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getDimensionClass(),
                       MonteCarlo::PhaseSpaceDimensionTraits<Dimension>::getClass() );
}

//---------------------------------------------------------------------------//
// Test that the indep. dimension can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   getParentDimension,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension> >
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getParentDimension(),
                       ParentDimension );
}

//---------------------------------------------------------------------------//
// Test that the indep. dimension class can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   getParentDimensionClass,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension> >
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getParentDimensionClass(),
                       MonteCarlo::PhaseSpaceDimensionTraits<ParentDimension>::getClass() );
}

//---------------------------------------------------------------------------//
// Test that the distribution type name can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   getDistributionTypeName,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getDistributionTypeName(),
                       "BasicBivariateDistribution" );
}

//---------------------------------------------------------------------------//
// Test that the distribution type name can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   isIndependent,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK( !dimension_distribution->isIndependent() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is dependent on another dimension
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   isDependentOnDimension,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK( dimension_distribution->isDependentOnDimension( ParentDimension ) );
  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( Dimension ) );
}

//---------------------------------------------------------------------------//
// Test if the distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   isContinuous,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK( dimension_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   isTabular,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK( dimension_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is uniform
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   isUniform,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK( !dimension_distribution->isUniform() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is uniform
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   hasForm,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  FRENSIE_CHECK( !dimension_distribution->hasForm( Utility::DELTA_DISTRIBUTION) );
  FRENSIE_CHECK( !dimension_distribution->hasForm( Utility::UNIFORM_DISTRIBUTION ) );
}

//---------------------------------------------------------------------------//
// Test if the distribution can be evaluated without a cascade
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   evaluateWithoutCascade,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  double parent_dim[7] = {
      0.05,  // Parent dimension value outside of distribution bounds
      0.1,   // Parent dimension value on first bin
      0.3,   // Parent dimension value inside of first bin
      0.5,   // Parent dimension value on second bin
      0.7,   // Parent dimension value in second bin
      0.9,   // Parent dimension value on distribution upper bound
      1.0,   // Parent dimension outside of distribution bounds
  };

  std::vector<std::vector<double>> vals_to_test[7] = {
      // Parent dimension value outside of distribution bounds
      {{0.1, 0.0}, {0.5, 0.0}, {0.9, 0.0}},
      // Parent dimension value on first bin
      {{0.1, 0.0}, {0.5, 0.5}, {0.9, 0.5}, {1.0, 0.0}},
      // Parent dimension value inside of first bin
      {{0.1, 0.0}, {0.5, 0.5}, {0.9, 0.5}, {1.0, 0.0}},
      // Parent dimension value on second bin
      {{0.1, 0.0}, {0.6, 0.4}, {0.8, 0.4}, {1.0, 0.0}},
      // Parent dimension value in second bin
      {{0.1, 0.0}, {0.6, 0.4}, {0.8, 0.4}, {1.0, 0.0}},
      // Parent dimension value on distribution upper bound
      {{0.1, 0.0}, {0.6, 0.4}, {0.8, 0.4}, {1.0, 0.0}},
      // Parent dimension outside of distribution bounds
      {{0.1, 0.0}, {0.5, 0.0}, {0.9, 0.0}}};

  for (int i = 0; i < 7; i++) {
    setCoordinate<ParentDimension>(point, parent_dim[i]);
    for (auto vals : vals_to_test[i]) {
      setCoordinate<Dimension>(point, vals[0]);
      FRENSIE_CHECK_EQUAL(dimension_distribution->evaluateWithoutCascade(point),
                          vals[1]);
    }
  }
}

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   sampleWithoutCascade,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );
  FRENSIE_CHECK_THROW( dimension_distribution->sampleWithoutCascade( point ),
              std::logic_error );

  // Set Fake Stream
  std::vector<double> fake_stream = {0.0, 0.5, 1.0 - 1e-15};
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );


  // Testing Valid Parent Dimensions 
  double parent_dim[5] = {
      0.1,  // Parent dimension value on first bin
      0.3,  // Parent dimension value in first bin
      0.5,  // Parent dimension value on second bin
      0.7,  // Parent dimension value in second bin
      0.9   // Parent dimension value on distribution upper bound
  };
  double vals_to_test[5][3] = {
      {0.5, 0.7, 0.9},  // Parent dimension value on first bin
      {0.5, 0.7, 0.9},  // Parent dimension value in first bin
      {0.6, 0.7, 0.8},  // Parent dimension value on second bin
      {0.6, 0.7, 0.8},  // Parent dimension value in second bin
      {0.6, 0.7, 0.8}   // Parent dimension value on distribution upper bound
  };

  for (int i = 0; i < 5; i++) {
    setCoordinate<ParentDimension>(point, parent_dim[i]);
    for (int j = 0; j < 3; j++) {
      dimension_distribution->sampleWithoutCascade(point);
      FRENSIE_CHECK_FLOATING_EQUALITY(getCoordinate<Dimension>(point), vals_to_test[i][j], 1e-15);
    }
  }

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );
  FRENSIE_CHECK_THROW( dimension_distribution->sampleWithoutCascade( point ),
              std::logic_error );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade and the trials
// can be counted
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   sampleAndRecordTrialsWithoutCascade,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );
  MonteCarlo::PhaseSpaceDimensionDistribution::Counter trials = 0;

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );
  FRENSIE_CHECK_THROW( dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials ),
              std::logic_error );
  trials = 0; // reseting trials counter ??

  std::vector<double> fake_stream = {0.0, 0.5, 1.0 - 1e-15};
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double parent_dim[5] = {
      0.1,  // Parent dimension value on first bin
      0.3,  // Parent dimension value in first bin
      0.5,  // Parent dimension value on second bin
      0.7,  // Parent dimension value in second bin
      0.9   // Parent dimension value on distribution upper bound
  };
  double vals_to_test[5][3][2] = {
      // Parent dimension value on first bin
      {{0.5, 1}, {0.7, 2}, {0.9, 3}},
      // Parent dimension value in first bin
      {{0.5, 4}, {0.7, 5}, {0.9, 6}},
      // Parent dimension value on second bin
      {{0.6, 7}, {0.7, 8}, {0.8, 9}},
      // Parent dimension value in second bin
      {{0.6, 10}, {0.7, 11}, {0.8, 12}},
      // Parent dimension value on distribution upper bound
      {{0.6, 13}, {0.7, 14}, {0.8, 15}}};
  for (int i = 0; i < 5; i++) {
    setCoordinate<ParentDimension>(point, parent_dim[i]);
    for (int j = 0; j < 3; j++) {
      dimension_distribution->sampleAndRecordTrialsWithoutCascade(point,
                                                                  trials);
      FRENSIE_CHECK_FLOATING_EQUALITY(getCoordinate<Dimension>(point),
                          vals_to_test[i][j][0], 1e-15);
      FRENSIE_CHECK_EQUAL(trials, vals_to_test[i][j][1]);

    }
  }

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );
  FRENSIE_CHECK_THROW( dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials ),
              std::logic_error );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Test that the dimension value can be set and weighed appropriately
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   setDimensionValueAndApplyWeight,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedParentDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDimension );

  constexpr PhaseSpaceDimension ParentDimension = WrappedParentDimension::value;
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );
  FRENSIE_CHECK_THROW( dimension_distribution->setDimensionValueAndApplyWeight( point, 0.1 ),
              std::logic_error );

  double parent_dim[3] = {
      0.1,  // Parent dimension value on first bin
      0.5,  // Parent dimension value on second bin
      0.9   // Parent dimension value on distribution upper bound
  };
  double vals_to_test[3][3][2] = {
      // Parent dimension value on first bin
      {{0.5, 2.5}, {0.7, 2.5}, {0.9, 2.5}},
      // Parent dimension value on second bin
      {{0.6, 5.0}, {0.7, 5.0}, {0.8, 5.0}},
      // Parent dimension value on distribution upper bound
      {{0.6, 5.0}, {0.7, 5.0}, {0.8, 5.0}}};

  for (int i = 0; i < 3; i++) {
    setCoordinate<ParentDimension>(point, parent_dim[i]);
    for (int j = 0; j < 3; j++) {
      dimension_distribution->setDimensionValueAndApplyWeight(point, vals_to_test[i][j][0]);
      FRENSIE_CHECK_FLOATING_EQUALITY(getCoordinate<Dimension>(point), vals_to_test[i][j][0], 1e-15);
      FRENSIE_CHECK_FLOATING_EQUALITY(getCoordinateWeight<Dimension>(point), vals_to_test[i][j][1], 1e-15);
    }
  }

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );
  FRENSIE_CHECK_THROW( dimension_distribution->setDimensionValueAndApplyWeight( point, 0.1 ),
              std::logic_error );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DependentPhaseSpaceDimensionDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_dependent_phase_dimension_distribution" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    // Create the fully tabular distribution
    std::shared_ptr<const Utility::BasicBivariateDistribution>
      raw_distribution;
    
    {
      std::vector<double> primary_grid( {0.1, 0.5, 0.9} );
  
      std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
        secondary_dists( 3 );

      secondary_dists[0].reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );
      secondary_dists[1].reset( new Utility::UniformDistribution( 0.6, 0.8, 0.4 ) );
      secondary_dists[2] = secondary_dists[0];

      Utility::HistogramFullyTabularBasicBivariateDistribution*
        local_raw_distribution = new Utility::HistogramFullyTabularBasicBivariateDistribution( primary_grid, secondary_dists );

      local_raw_distribution->limitToPrimaryIndepLimits();

      raw_distribution.reset( local_raw_distribution );
    }

    // Create the dependent primary spatial distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_primary_spatial_dimension_distribution( new MonteCarlo::SecondarySpatialDependentPrimarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_primary_spatial_dimension_distribution( new MonteCarlo::TertiarySpatialDependentPrimarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_primary_spatial_dimension_distribution( new MonteCarlo::PrimaryDirectionalDependentPrimarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_primary_spatial_dimension_distribution( new MonteCarlo::SecondaryDirectionalDependentPrimarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_primary_spatial_dimension_distribution( new MonteCarlo::TertiaryDirectionalDependentPrimarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_primary_spatial_dimension_distribution( new MonteCarlo::EnergyDependentPrimarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_primary_spatial_dimension_distribution( new MonteCarlo::TimeDependentPrimarySpatialDimensionDistribution( raw_distribution ) );

    // Create the dependent secondary spatial distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::PrimarySpatialDependentSecondarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::TertiarySpatialDependentSecondarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::PrimaryDirectionalDependentSecondarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::SecondaryDirectionalDependentSecondarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::TertiaryDirectionalDependentSecondarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::EnergyDependentSecondarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_secondary_spatial_dimension_distribution( new MonteCarlo::TimeDependentSecondarySpatialDimensionDistribution( raw_distribution ) );

    // Create the dependent tertiary spatial distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::PrimarySpatialDependentTertiarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::SecondarySpatialDependentTertiarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::PrimaryDirectionalDependentTertiarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::SecondaryDirectionalDependentTertiarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::TertiaryDirectionalDependentTertiarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::EnergyDependentTertiarySpatialDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_tertiary_spatial_dimension_distribution( new MonteCarlo::TimeDependentTertiarySpatialDimensionDistribution( raw_distribution ) );

    // Create the dependent primary directional distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_primary_directional_dimension_distribution( new MonteCarlo::PrimarySpatialDependentPrimaryDirectionalDimensionDistribution( raw_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_primary_directional_dimension_distribution( new MonteCarlo::SecondarySpatialDependentPrimaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_primary_directional_dimension_distribution( new MonteCarlo::TertiarySpatialDependentPrimaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_primary_directional_dimension_distribution( new MonteCarlo::SecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_primary_directional_dimension_distribution( new MonteCarlo::TertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_primary_directional_dimension_distribution( new MonteCarlo::EnergyDependentPrimaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_primary_directional_dimension_distribution( new MonteCarlo::TimeDependentPrimaryDirectionalDimensionDistribution( raw_distribution ) );

    // Create the dependent secondary directional distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial( new MonteCarlo::PrimarySpatialDependentSecondaryDirectionalDimensionDistribution( raw_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial( new MonteCarlo::SecondarySpatialDependentSecondaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial( new MonteCarlo::TertiarySpatialDependentSecondaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional( new MonteCarlo::PrimaryDirectionalDependentSecondaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional( new MonteCarlo::TertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy( new MonteCarlo::EnergyDependentSecondaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time( new MonteCarlo::TimeDependentSecondaryDirectionalDimensionDistribution( raw_distribution ) );

    // Create the dependent tertiary directional distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::PrimarySpatialDependentTertiaryDirectionalDimensionDistribution( raw_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::SecondarySpatialDependentTertiaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::TertiarySpatialDependentTertiaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::PrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::SecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::EnergyDependentTertiaryDirectionalDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_tertiary_directional_dimension_distribution( new MonteCarlo::TimeDependentTertiaryDirectionalDimensionDistribution( raw_distribution ) );

    // Create the dependent energy distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_energy_dimension_distribution( new MonteCarlo::PrimarySpatialDependentEnergyDimensionDistribution( raw_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_energy_dimension_distribution( new MonteCarlo::SecondarySpatialDependentEnergyDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_energy_dimension_distribution( new MonteCarlo::TertiarySpatialDependentEnergyDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_energy_dimension_distribution( new MonteCarlo::PrimaryDirectionalDependentEnergyDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_energy_dimension_distribution( new MonteCarlo::SecondaryDirectionalDependentEnergyDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_energy_dimension_distribution( new MonteCarlo::TertiaryDirectionalDependentEnergyDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dependent_energy_dimension_distribution( new MonteCarlo::TimeDependentEnergyDimensionDistribution( raw_distribution ) );

    // Create the dependent time distributions
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dependent_time_dimension_distribution( new MonteCarlo::PrimarySpatialDependentTimeDimensionDistribution( raw_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dependent_time_dimension_distribution( new MonteCarlo::SecondarySpatialDependentTimeDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dependent_time_dimension_distribution( new MonteCarlo::TertiarySpatialDependentTimeDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dependent_time_dimension_distribution( new MonteCarlo::PrimaryDirectionalDependentTimeDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dependent_time_dimension_distribution( new MonteCarlo::SecondaryDirectionalDependentTimeDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dependent_time_dimension_distribution( new MonteCarlo::TertiaryDirectionalDependentTimeDimensionDistribution( raw_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_time_dimension_distribution( new MonteCarlo::EnergyDependentTimeDimensionDistribution( raw_distribution ) );

    std::vector<std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>> nrj_dim_dist_vector =
        {secondary_spatial_dependent_primary_spatial_dimension_distribution,
         tertiary_spatial_dependent_primary_spatial_dimension_distribution,
         primary_directional_dependent_primary_spatial_dimension_distribution,
         secondary_directional_dependent_primary_spatial_dimension_distribution,
         tertiary_directional_dependent_primary_spatial_dimension_distribution,
         energy_dependent_primary_spatial_dimension_distribution,
         time_dependent_primary_spatial_dimension_distribution,

         primary_spatial_dependent_secondary_spatial_dimension_distribution,
         tertiary_spatial_dependent_secondary_spatial_dimension_distribution,
         primary_directional_dependent_secondary_spatial_dimension_distribution,
         secondary_directional_dependent_secondary_spatial_dimension_distribution,
         tertiary_directional_dependent_secondary_spatial_dimension_distribution,
         energy_dependent_secondary_spatial_dimension_distribution,
         time_dependent_secondary_spatial_dimension_distribution,

         primary_spatial_dependent_tertiary_spatial_dimension_distribution,
         secondary_spatial_dependent_tertiary_spatial_dimension_distribution,
         primary_directional_dependent_tertiary_spatial_dimension_distribution,
         secondary_directional_dependent_tertiary_spatial_dimension_distribution,
         tertiary_directional_dependent_tertiary_spatial_dimension_distribution,
         energy_dependent_tertiary_spatial_dimension_distribution,
         time_dependent_tertiary_spatial_dimension_distribution,

         primary_spatial_dependent_primary_directional_dimension_distribution,
         secondary_spatial_dependent_primary_directional_dimension_distribution,
         tertiary_spatial_dependent_primary_directional_dimension_distribution,
         secondary_directional_dependent_primary_directional_dimension_distribution,
         tertiary_directional_dependent_primary_directional_dimension_distribution,
         energy_dependent_primary_directional_dimension_distribution,
         time_dependent_primary_directional_dimension_distribution,

         primary_spatial,
         secondary_spatial,
         tertiary_spatial,
         primary_directional,
         tertiary_directional,
         energy,
         time,

         primary_spatial_dependent_tertiary_directional_dimension_distribution,
         secondary_spatial_dependent_tertiary_directional_dimension_distribution,
         tertiary_spatial_dependent_tertiary_directional_dimension_distribution,
         primary_directional_dependent_tertiary_directional_dimension_distribution,
         secondary_directional_dependent_tertiary_directional_dimension_distribution,
         energy_dependent_tertiary_directional_dimension_distribution,
         time_dependent_tertiary_directional_dimension_distribution,

         primary_spatial_dependent_energy_dimension_distribution,
         secondary_spatial_dependent_energy_dimension_distribution,
         tertiary_spatial_dependent_energy_dimension_distribution,
         primary_directional_dependent_energy_dimension_distribution,
         secondary_directional_dependent_energy_dimension_distribution,
         tertiary_directional_dependent_energy_dimension_distribution,
         time_dependent_energy_dimension_distribution,

         primary_spatial_dependent_time_dimension_distribution,
         secondary_spatial_dependent_time_dimension_distribution,
         tertiary_spatial_dependent_time_dimension_distribution,
         primary_directional_dependent_time_dimension_distribution,
         secondary_directional_dependent_time_dimension_distribution,
         tertiary_directional_dependent_time_dimension_distribution,
         energy_dependent_time_dimension_distribution};

    for (auto nrj_dim_dist : nrj_dim_dist_vector) {
      FRENSIE_REQUIRE_NO_THROW((*oarchive)
                               << BOOST_SERIALIZATION_NVP(nrj_dim_dist));
    }
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream(archive_ostream.str());

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive(archive_istream, iarchive);

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      nrj_dim_dist_array[8][7];

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 7; j++) {
      FRENSIE_REQUIRE_NO_THROW(
          (*iarchive) >> BOOST_SERIALIZATION_NVP(nrj_dim_dist_array[i][j]));
    }
  }

  iarchive.reset();

  double parent_dim[7] = {
      0.05,  // Parent dimension value outside of distribution bounds
      0.1,   // Parent dimension value on first bin
      0.3,   // Parent dimension value inside of first bin
      0.5,   // Parent dimension value on second bin
      0.7,   // Parent dimension value in second bin
      0.9,   // Parent dimension value on distribution upper bound
      1.0    // Parent dimension outside of distribution bounds
  };

  std::vector<std::vector<double>> vals_to_check[7] = {
      // Parent dimension value outside of distribution bounds
      {{0.1, 0.0}, {0.5, 0.0}, {0.9, 0.0}},
      // Parent dimension value on first bin
      {{0.1, 0.0}, {0.5, 0.5}, {0.9, 0.5}, {1.0, 0.0}},
      // Parent dimension value inside of first bin
      {{0.1, 0.0}, {0.5, 0.5}, {0.9, 0.5}, {1.0, 0.0}},
      // Parent dimension value on second bin
      {{0.1, 0.0}, {0.6, 0.4}, {0.8, 0.4}, {1.0, 0.0}},
      // Parent dimension value in second bin
      {{0.1, 0.0}, {0.6, 0.4}, {0.8, 0.4}, {1.0, 0.0}},
      // Parent dimension value on distribution upper bound
      {{0.1, 0.0}, {0.6, 0.4}, {0.8, 0.4}, {1.0, 0.0}},
      // Parent dimension outside of distribution bounds
      {{0.1, 0.0}, {0.5, 0.0}, {0.9, 0.0}}};

  {
    int i = 0;

    for (int j = 0; j < 7; j++) {
      FRENSIE_CHECK_EQUAL(nrj_dim_dist_array[i][j]->getDimension(),
                          PRIMARY_SPATIAL_DIMENSION);
    }
    {
      auto secondary_spatial = dynamic_cast<
          const MonteCarlo::
              SecondarySpatialDependentPrimarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][0].get());
      auto tertiary_spatial = dynamic_cast<
          const MonteCarlo::
              TertiarySpatialDependentPrimarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][1].get());
      auto primary_directional = dynamic_cast<
          const MonteCarlo::
              PrimaryDirectionalDependentPrimarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][2].get());
      auto secondary_directional = dynamic_cast<
          const MonteCarlo::
              SecondaryDirectionalDependentPrimarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][3].get());
      auto tertiary_directional = dynamic_cast<
          const MonteCarlo::
              TertiaryDirectionalDependentPrimarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][4].get());
      auto energy =
          dynamic_cast<const MonteCarlo::
                           EnergyDependentPrimarySpatialDimensionDistribution*>(
              nrj_dim_dist_array[i][5].get());
      auto time = dynamic_cast<
          const MonteCarlo::TimeDependentPrimarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][6].get());

      FRENSIE_CHECK_EQUAL(secondary_spatial->getParentDimension(),
                          SECONDARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_spatial->getParentDimension(),
                          TERTIARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(primary_directional->getParentDimension(),
                          PRIMARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_directional->getParentDimension(),
                          SECONDARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_directional->getParentDimension(),
                          TERTIARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(energy->getParentDimension(), ENERGY_DIMENSION);
      FRENSIE_CHECK_EQUAL(time->getParentDimension(), TIME_DIMENSION);
    }

    MonteCarlo::PhaseSpacePoint point(spatial_coord_conversion_policy,
                                      directional_coord_conversion_policy);

    for (int k = 0; k < 7; k++) {
      setCoordinate<ENERGY_DIMENSION>(point, parent_dim[k]);
      for (auto vals : vals_to_check[k]) {
        setCoordinate<PRIMARY_SPATIAL_DIMENSION>(point, vals[0]);
        FRENSIE_CHECK_FLOATING_EQUALITY(
            nrj_dim_dist_array[i][5]->evaluateWithoutCascade(point), vals[1], 1e-15);
      }
    }
  }

  {
    int i = 1;
    for (int j = 0; j < 7; j++) {
      FRENSIE_CHECK_EQUAL(nrj_dim_dist_array[i][j]->getDimension(),
                          SECONDARY_SPATIAL_DIMENSION);
    }
    {
      auto primary_spatial = dynamic_cast<
          const MonteCarlo::
              PrimarySpatialDependentSecondarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][0].get());
      auto tertiary_spatial = dynamic_cast<
          const MonteCarlo::
              TertiarySpatialDependentSecondarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][1].get());
      auto primary_directional = dynamic_cast<
          const MonteCarlo::
              PrimaryDirectionalDependentSecondarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][2].get());
      auto secondary_directional = dynamic_cast<
          const MonteCarlo::
              SecondaryDirectionalDependentSecondarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][3].get());
      auto tertiary_directional = dynamic_cast<
          const MonteCarlo::
              TertiaryDirectionalDependentSecondarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][4].get());
      auto energy = dynamic_cast<
          const MonteCarlo::
              EnergyDependentSecondarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][5].get());
      auto time =
          dynamic_cast<const MonteCarlo::
                           TimeDependentSecondarySpatialDimensionDistribution*>(
              nrj_dim_dist_array[i][6].get());

      FRENSIE_CHECK_EQUAL(primary_spatial->getParentDimension(),
                          PRIMARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_spatial->getParentDimension(),
                          TERTIARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(primary_directional->getParentDimension(),
                          PRIMARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_directional->getParentDimension(),
                          SECONDARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_directional->getParentDimension(),
                          TERTIARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(energy->getParentDimension(), ENERGY_DIMENSION);
      FRENSIE_CHECK_EQUAL(time->getParentDimension(), TIME_DIMENSION);
    }

    MonteCarlo::PhaseSpacePoint point(spatial_coord_conversion_policy,
                                      directional_coord_conversion_policy);

    for (int k = 0; k < 7; k++) {
      setCoordinate<ENERGY_DIMENSION>(point, parent_dim[k]);
      for (auto vals : vals_to_check[k]) {
        setCoordinate<SECONDARY_SPATIAL_DIMENSION>(point, vals[0]);
        FRENSIE_CHECK_FLOATING_EQUALITY(
            nrj_dim_dist_array[i][5]->evaluateWithoutCascade(point), vals[1], 1e-15);
      }
    }
  }

  {
    int i = 2;
    for (int j = 0; j < 7; j++) {
      FRENSIE_CHECK_EQUAL(nrj_dim_dist_array[i][j]->getDimension(),
                          TERTIARY_SPATIAL_DIMENSION);
    }
    {
      auto primary_spatial = dynamic_cast<
          const MonteCarlo::
              PrimarySpatialDependentTertiarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][0].get());
      auto secondary_spatial = dynamic_cast<
          const MonteCarlo::
              SecondarySpatialDependentTertiarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][1].get());
      auto primary_directional = dynamic_cast<
          const MonteCarlo::
              PrimaryDirectionalDependentTertiarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][2].get());
      auto secondary_directional = dynamic_cast<
          const MonteCarlo::
              SecondaryDirectionalDependentTertiarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][3].get());
      auto tertiary_directional = dynamic_cast<
          const MonteCarlo::
              TertiaryDirectionalDependentTertiarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][4].get());
      auto energy = dynamic_cast<
          const MonteCarlo::
              EnergyDependentTertiarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][5].get());
      auto time = dynamic_cast<
          const MonteCarlo::TimeDependentTertiarySpatialDimensionDistribution*>(
          nrj_dim_dist_array[i][6].get());

      FRENSIE_CHECK_EQUAL(primary_spatial->getParentDimension(),
                          PRIMARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_spatial->getParentDimension(),
                          SECONDARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(primary_directional->getParentDimension(),
                          PRIMARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_directional->getParentDimension(),
                          SECONDARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_directional->getParentDimension(),
                          TERTIARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(energy->getParentDimension(), ENERGY_DIMENSION);
      FRENSIE_CHECK_EQUAL(time->getParentDimension(), TIME_DIMENSION);
    }

    MonteCarlo::PhaseSpacePoint point(spatial_coord_conversion_policy,
                                      directional_coord_conversion_policy);

    for (int k = 0; k < 7; k++) {
      setCoordinate<ENERGY_DIMENSION>(point, parent_dim[k]);
      for (auto vals : vals_to_check[k]) {
        setCoordinate<TERTIARY_SPATIAL_DIMENSION>(point, vals[0]);
        FRENSIE_CHECK_FLOATING_EQUALITY(
            nrj_dim_dist_array[i][5]->evaluateWithoutCascade(point), vals[1], 1e-15);
      }
    }
  }

  {
    int i = 3;
    for (int j = 0; j < 7; j++) {
      FRENSIE_CHECK_EQUAL(nrj_dim_dist_array[i][j]->getDimension(),
                          PRIMARY_DIRECTIONAL_DIMENSION);
    }

    {
      auto primary_spatial = dynamic_cast<
          const MonteCarlo::
              PrimarySpatialDependentPrimaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][0].get());
      auto secondary_spatial = dynamic_cast<
          const MonteCarlo::
              SecondarySpatialDependentPrimaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][1].get());
      auto tertiary_spatial = dynamic_cast<
          const MonteCarlo::
              TertiarySpatialDependentPrimaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][2].get());
      auto secondary_directional = dynamic_cast<
          const MonteCarlo::
              SecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][3].get());
      auto tertiary_directional = dynamic_cast<
          const MonteCarlo::
              TertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][4].get());
      auto energy = dynamic_cast<
          const MonteCarlo::
              EnergyDependentPrimaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][5].get());
      auto time = dynamic_cast<
          const MonteCarlo::
              TimeDependentPrimaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][6].get());

      FRENSIE_CHECK_EQUAL(primary_spatial->getParentDimension(),
                          PRIMARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_spatial->getParentDimension(),
                          SECONDARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_spatial->getParentDimension(),
                          TERTIARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_directional->getParentDimension(),
                          SECONDARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_directional->getParentDimension(),
                          TERTIARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(energy->getParentDimension(), ENERGY_DIMENSION);
      FRENSIE_CHECK_EQUAL(time->getParentDimension(), TIME_DIMENSION);
    }

    MonteCarlo::PhaseSpacePoint point(spatial_coord_conversion_policy,
                                      directional_coord_conversion_policy);
    for (int k = 0; k < 7; k++) {
      setCoordinate<ENERGY_DIMENSION>(point, parent_dim[k]);
      for (auto vals : vals_to_check[k]) {
        setCoordinate<PRIMARY_DIRECTIONAL_DIMENSION>(point, vals[0]);
        FRENSIE_CHECK_FLOATING_EQUALITY(
            nrj_dim_dist_array[i][5]->evaluateWithoutCascade(point), vals[1], 1e-15);
      }
    }
  }

  {
    int i = 4;
    for (int j = 0; j < 7; j++) {
      FRENSIE_CHECK_EQUAL(nrj_dim_dist_array[i][j]->getDimension(),
                          SECONDARY_DIRECTIONAL_DIMENSION);
    }

    {
      auto primary_spatial = dynamic_cast<
          const MonteCarlo::
              PrimarySpatialDependentSecondaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][0].get());
      auto secondary_spatial = dynamic_cast<
          const MonteCarlo::
              SecondarySpatialDependentSecondaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][1].get());
      auto tertiary_spatial = dynamic_cast<
          const MonteCarlo::
              TertiarySpatialDependentSecondaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][2].get());
      auto primary_directional = dynamic_cast<
          const MonteCarlo::
              PrimaryDirectionalDependentSecondaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][3].get());
      auto tertiary_directional = dynamic_cast<
          const MonteCarlo::
              TertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][4].get());
      auto energy = dynamic_cast<
          const MonteCarlo::
              EnergyDependentSecondaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][5].get());
      auto time = dynamic_cast<
          const MonteCarlo::
              TimeDependentSecondaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][6].get());

      FRENSIE_CHECK_EQUAL(primary_spatial->getParentDimension(),
                          PRIMARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_spatial->getParentDimension(),
                          SECONDARY_SPATIAL_DIMENSION);

      FRENSIE_CHECK_EQUAL(tertiary_spatial->getParentDimension(),
                          TERTIARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(primary_directional->getParentDimension(),
                          PRIMARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_directional->getParentDimension(),
                          TERTIARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(energy->getParentDimension(), ENERGY_DIMENSION);
      FRENSIE_CHECK_EQUAL(time->getParentDimension(), TIME_DIMENSION);
    }

    MonteCarlo::PhaseSpacePoint point(spatial_coord_conversion_policy,
                                      directional_coord_conversion_policy);

    for (int k = 0; k < 7; k++) {
      setCoordinate<ENERGY_DIMENSION>(point, parent_dim[k]);
      for (auto vals : vals_to_check[k]) {
        setCoordinate<SECONDARY_DIRECTIONAL_DIMENSION>(point, vals[0]);
        FRENSIE_CHECK_FLOATING_EQUALITY(
            nrj_dim_dist_array[i][5]->evaluateWithoutCascade(point), vals[1], 1e-15);
      }
    }
  }

  {
    int i = 5;
    for (int j = 0; j < 7; j++) {
      FRENSIE_CHECK_EQUAL(nrj_dim_dist_array[i][j]->getDimension(),
                          TERTIARY_DIRECTIONAL_DIMENSION);
    }
    {
      auto primary_spatial = dynamic_cast<
          const MonteCarlo::
              PrimarySpatialDependentTertiaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][0].get());
      auto secondary_spatial = dynamic_cast<
          const MonteCarlo::
              SecondarySpatialDependentTertiaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][1].get());
      auto tertiary_spatial = dynamic_cast<
          const MonteCarlo::
              TertiarySpatialDependentTertiaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][2].get());
      auto primary_directional = dynamic_cast<
          const MonteCarlo::
              PrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][3].get());
      auto secondary_directional = dynamic_cast<
          const MonteCarlo::
              SecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][4].get());
      auto energy = dynamic_cast<
          const MonteCarlo::
              EnergyDependentTertiaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][5].get());
      auto time = dynamic_cast<
          const MonteCarlo::
              TimeDependentTertiaryDirectionalDimensionDistribution*>(
          nrj_dim_dist_array[i][6].get());

      FRENSIE_CHECK_EQUAL(primary_spatial->getParentDimension(),
                          PRIMARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_spatial->getParentDimension(),
                          SECONDARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_spatial->getParentDimension(),
                          TERTIARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(primary_directional->getParentDimension(),
                          PRIMARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_directional->getParentDimension(),
                          SECONDARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(energy->getParentDimension(), ENERGY_DIMENSION);
      FRENSIE_CHECK_EQUAL(time->getParentDimension(), TIME_DIMENSION);
    }

    MonteCarlo::PhaseSpacePoint point(spatial_coord_conversion_policy,
                                      directional_coord_conversion_policy);

    for (int k = 0; k < 7; k++) {
      setCoordinate<ENERGY_DIMENSION>(point, parent_dim[k]);
      for (auto vals : vals_to_check[k]) {
        setCoordinate<TERTIARY_DIRECTIONAL_DIMENSION>(point, vals[0]);
        FRENSIE_CHECK_FLOATING_EQUALITY(
            nrj_dim_dist_array[i][5]->evaluateWithoutCascade(point), vals[1], 1e-15);
      }
    }
  }

  {
    int i = 6;
    for (int j = 0; j < 7; j++) {
      FRENSIE_CHECK_EQUAL(nrj_dim_dist_array[i][j]->getDimension(),
                          ENERGY_DIMENSION);
    }
    {
      auto primary_spatial =
          dynamic_cast<const MonteCarlo::
                           PrimarySpatialDependentEnergyDimensionDistribution*>(
              nrj_dim_dist_array[i][0].get());
      auto secondary_spatial = dynamic_cast<
          const MonteCarlo::
              SecondarySpatialDependentEnergyDimensionDistribution*>(
          nrj_dim_dist_array[i][1].get());
      auto tertiary_spatial = dynamic_cast<
          const MonteCarlo::
              TertiarySpatialDependentEnergyDimensionDistribution*>(
          nrj_dim_dist_array[i][2].get());
      auto primary_directional = dynamic_cast<
          const MonteCarlo::
              PrimaryDirectionalDependentEnergyDimensionDistribution*>(
          nrj_dim_dist_array[i][3].get());
      auto secondary_directional = dynamic_cast<
          const MonteCarlo::
              SecondaryDirectionalDependentEnergyDimensionDistribution*>(
          nrj_dim_dist_array[i][4].get());
      auto tertiary_directional = dynamic_cast<
          const MonteCarlo::
              TertiaryDirectionalDependentEnergyDimensionDistribution*>(
          nrj_dim_dist_array[i][5].get());
      auto time = dynamic_cast<
          const MonteCarlo::TimeDependentEnergyDimensionDistribution*>(
          nrj_dim_dist_array[i][6].get());

      FRENSIE_CHECK_EQUAL(primary_spatial->getParentDimension(),
                          PRIMARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_spatial->getParentDimension(),
                          SECONDARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_spatial->getParentDimension(),
                          TERTIARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(primary_directional->getParentDimension(),
                          PRIMARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_directional->getParentDimension(),
                          SECONDARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_directional->getParentDimension(),
                          TERTIARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(time->getParentDimension(), TIME_DIMENSION);
    }
    MonteCarlo::PhaseSpacePoint point(spatial_coord_conversion_policy,
                                      directional_coord_conversion_policy);

    for (int k = 0; k < 7; k++) {
      setCoordinate<TIME_DIMENSION>(point, parent_dim[k]);
      for (auto vals : vals_to_check[k]) {
        setCoordinate<ENERGY_DIMENSION>(point, vals[0]);
        FRENSIE_CHECK_FLOATING_EQUALITY(
            nrj_dim_dist_array[i][6]->evaluateWithoutCascade(point), vals[1], 1e-15);
      }
    }
  }
  {
    int i = 7;
    for (int j = 0; j < 7; j++) {
      FRENSIE_CHECK_EQUAL(nrj_dim_dist_array[i][j]->getDimension(),
                          TIME_DIMENSION);
    }

    {
      auto primary_spatial = dynamic_cast<
          const MonteCarlo::PrimarySpatialDependentTimeDimensionDistribution*>(
          nrj_dim_dist_array[i][0].get());
      auto secondary_spatial =
          dynamic_cast<const MonteCarlo::
                           SecondarySpatialDependentTimeDimensionDistribution*>(
              nrj_dim_dist_array[i][1].get());
      auto tertiary_spatial = dynamic_cast<
          const MonteCarlo::TertiarySpatialDependentTimeDimensionDistribution*>(
          nrj_dim_dist_array[i][2].get());
      auto primary_directional = dynamic_cast<
          const MonteCarlo::
              PrimaryDirectionalDependentTimeDimensionDistribution*>(
          nrj_dim_dist_array[i][3].get());
      auto secondary_directional = dynamic_cast<
          const MonteCarlo::
              SecondaryDirectionalDependentTimeDimensionDistribution*>(
          nrj_dim_dist_array[i][4].get());
      auto tertiary_directional = dynamic_cast<
          const MonteCarlo::
              TertiaryDirectionalDependentTimeDimensionDistribution*>(
          nrj_dim_dist_array[i][5].get());
      auto energy = dynamic_cast<
          const MonteCarlo::EnergyDependentTimeDimensionDistribution*>(
          nrj_dim_dist_array[i][6].get());

      FRENSIE_CHECK_EQUAL(primary_spatial->getParentDimension(),
                          PRIMARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_spatial->getParentDimension(),
                          SECONDARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_spatial->getParentDimension(),
                          TERTIARY_SPATIAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(primary_directional->getParentDimension(),
                          PRIMARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(secondary_directional->getParentDimension(),
                          SECONDARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(tertiary_directional->getParentDimension(),
                          TERTIARY_DIRECTIONAL_DIMENSION);
      FRENSIE_CHECK_EQUAL(energy->getParentDimension(), ENERGY_DIMENSION);
    }

    MonteCarlo::PhaseSpacePoint point(spatial_coord_conversion_policy,
                                      directional_coord_conversion_policy);

    for (int k = 0; k < 7; k++) {
      setCoordinate<PRIMARY_SPATIAL_DIMENSION>(point, parent_dim[k]);
      for (auto vals : vals_to_check[k]) {
        setCoordinate<TIME_DIMENSION>(point, vals[0]);
        FRENSIE_CHECK_FLOATING_EQUALITY(
            nrj_dim_dist_array[i][0]->evaluateWithoutCascade(point), vals[1], 1e-15);
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT() {
  // Create the fully tabular distribution
  std::vector<double> primary_grid({0.1, 0.5, 0.9});

  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution>>
      secondary_dists(3);

  // Create the secondary distribution in the first bin
  secondary_dists[0].reset(new Utility::UniformDistribution(0.5, 0.9, 0.5));

  // Create the secondary distribution in the second bin
  secondary_dists[1].reset(new Utility::UniformDistribution(0.6, 0.8, 0.4));

  // Create the secondary distribution in the third bin
  secondary_dists[2] = secondary_dists[0];

  Utility::HistogramFullyTabularBasicBivariateDistribution*
      local_raw_distribution =
          new Utility::HistogramFullyTabularBasicBivariateDistribution(
              primary_grid, secondary_dists);

  local_raw_distribution->limitToPrimaryIndepLimits();

  raw_distribution.reset(local_raw_distribution);

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
    }

    FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

    //---------------------------------------------------------------------------//
    // end tstDependentPhaseSpaceDimensionDistribution.cpp
    //---------------------------------------------------------------------------//
