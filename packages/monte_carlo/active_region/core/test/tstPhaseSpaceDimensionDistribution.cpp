//---------------------------------------------------------------------------//
//!
//! \file   tstPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
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
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::UnivariateDistribution> raw_indep_distribution;
std::shared_ptr<const Utility::BasicBivariateDistribution> raw_dep_distribution_a;
std::shared_ptr<const Utility::BasicBivariateDistribution> raw_dep_distribution_b;

//---------------------------------------------------------------------------//
// Check that the parent distribution can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhaseSpaceDimensionDistribution,
                                   getParentDistribution,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndepDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDepDimension );

  constexpr PhaseSpaceDimension IndepDimension = WrappedIndepDimension::value;
  constexpr PhaseSpaceDimension DepDimension = WrappedDepDimension::value;
  
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  // The indep dimension will not have a parent
  FRENSIE_CHECK( !indep_dimension_distribution->hasParentDistribution() );
  FRENSIE_REQUIRE( dep_dimension_distribution->hasParentDistribution() );
  FRENSIE_CHECK( &dep_dimension_distribution->getParentDistribution() ==
                 indep_dimension_distribution.get() );
}

//---------------------------------------------------------------------------//
// Check that the dependent distributions can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhaseSpaceDimensionDistribution,
                                   getDependentDimensions,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndepDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDepDimension );

  constexpr PhaseSpaceDimension IndepDimension = WrappedIndepDimension::value;
  constexpr PhaseSpaceDimension DepDimension = WrappedDepDimension::value;
  
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  // Get the dimensions that are dependent on the independent dimension
  MonteCarlo::PhaseSpaceDimensionDistribution::DependentDimensionSet
    dependent_dimensions;

  indep_dimension_distribution->getDependentDimensions( dependent_dimensions );

  FRENSIE_CHECK_EQUAL( dependent_dimensions.size(), 1 );
  FRENSIE_CHECK( dependent_dimensions.count( DepDimension ) );

  // Get the dimensions that are dependent on the dependent dimension
  dependent_dimensions.clear();

  dep_dimension_distribution->getDependentDimensions( dependent_dimensions );

  FRENSIE_CHECK_EQUAL( dependent_dimensions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the dependent distributions can be returned
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhaseSpaceDimensionDistribution,
                                   removeDependentDistributions,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndepDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDepDimension );

  constexpr PhaseSpaceDimension IndepDimension = WrappedIndepDimension::value;
  constexpr PhaseSpaceDimension DepDimension = WrappedDepDimension::value;
  
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  FRENSIE_REQUIRE( dep_dimension_distribution->hasParentDistribution() );
  FRENSIE_CHECK( &dep_dimension_distribution->getParentDistribution() ==
                 indep_dimension_distribution.get() );

  // Remove the dep dimension distribution from the indep dimension dist.
  indep_dimension_distribution->removeDependentDistributions();

  FRENSIE_CHECK( !dep_dimension_distribution->hasParentDistribution() );

  // Get the dimensions that are dependent on the independent dimension
  MonteCarlo::PhaseSpaceDimensionDistribution::DependentDimensionSet
    dependent_dimensions;

  indep_dimension_distribution->getDependentDimensions( dependent_dimensions );

  FRENSIE_CHECK_EQUAL( dependent_dimensions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated with a cascade to dependent
// distributions
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhaseSpaceDimensionDistribution,
                                   evaluateWithCascade,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndepDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDepDimension );

  constexpr PhaseSpaceDimension IndepDimension = WrappedIndepDimension::value;
  constexpr PhaseSpaceDimension DepDimension = WrappedDepDimension::value;
  
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Indep dimension value outside of distribution bounds
  setCoordinate<IndepDimension>( point, 0.05 );
  setCoordinate<DepDimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.9 );
  
  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value on first bin
  setCoordinate<IndepDimension>( point, 0.1 );
  setCoordinate<DepDimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.25 );

  setCoordinate<DepDimension>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.25 );

  setCoordinate<DepDimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value inside of first bin
  setCoordinate<IndepDimension>( point, 0.3 );
  setCoordinate<DepDimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.25 );

  setCoordinate<DepDimension>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.25 );

  setCoordinate<DepDimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value on second bin
  setCoordinate<IndepDimension>( point, 0.5 );
  setCoordinate<DepDimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.6 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 0.8 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value in second bin
  setCoordinate<IndepDimension>( point, 0.7 );
  setCoordinate<DepDimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.6 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 0.8 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value on distribution upper bound
  setCoordinate<IndepDimension>( point, 0.9 );
  setCoordinate<DepDimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.6 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 0.8 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value outside of distribution bounds
  setCoordinate<IndepDimension>( point, 1.0 );
  setCoordinate<DepDimension>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.9 );
  
  FRENSIE_CHECK_EQUAL( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled with a cascade to dependent
// distributions
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhaseSpaceDimensionDistribution,
                                   sampleWithCascade,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndepDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDepDimension );

  constexpr PhaseSpaceDimension IndepDimension = WrappedIndepDimension::value;
  constexpr PhaseSpaceDimension DepDimension = WrappedDepDimension::value;
  
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Indep dimension value on first bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0; 
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.5 );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );

  // Indep dimension in first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.25; 
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.25;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.25;
  fake_stream[5] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.5 );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );

  // Indep dimension on second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.5; 
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );

  // Parent dimension value in second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.75; 
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.75;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.75;
  fake_stream[5] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );

  // Parent dimension value in second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 1.0-1e-15; 
  fake_stream[1] = 0.0;
  fake_stream[2] = 1.0-1e-15;
  fake_stream[3] = 0.5;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );

  indep_dimension_distribution->sampleWithCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled with a cascade to dependent
// distributions
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhaseSpaceDimensionDistribution,
                                   sampleAndRecordTrialsWithCascade,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndepDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDepDimension );

  constexpr PhaseSpaceDimension IndepDimension = WrappedIndepDimension::value;
  constexpr PhaseSpaceDimension DepDimension = WrappedDepDimension::value;
  
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  MonteCarlo::PhaseSpaceDimensionDistribution::DimensionCounterMap trials;
  trials[IndepDimension] = 0;
  trials[DepDimension] = 0;

  // Indep dimension value on first bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0; 
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.5 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 1 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 1 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 2 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 2 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 3 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 3 );

  // Indep dimension in first bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.25; 
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.25;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.25;
  fake_stream[5] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.5 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 4 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 4 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 5 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 5 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 6 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 6 );

  // Indep dimension on second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.5; 
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 7 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 7 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 8 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 8 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 9 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 9 );

  // Parent dimension value in second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.75; 
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.75;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.75;
  fake_stream[5] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 10 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 10 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 11 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 11 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 12 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 12 );

  // Parent dimension value in second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 1.0-1e-15; 
  fake_stream[1] = 0.0;
  fake_stream[2] = 1.0-1e-15;
  fake_stream[3] = 0.5;
  fake_stream[4] = 1.0-1e-15;
  fake_stream[5] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 13 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 13 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 14 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 14 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 15 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled with a cascade to dependent
// distributions
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhaseSpaceDimensionDistribution,
                                   sampleWithCascadeUsingDimensionValue,
                                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndepDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDepDimension );

  constexpr PhaseSpaceDimension IndepDimension = WrappedIndepDimension::value;
  constexpr PhaseSpaceDimension DepDimension = WrappedDepDimension::value;
  
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Indep dimension value on first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.1 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.5 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.1 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.1 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                       1.25,
                       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  // Indep dimension value in first bin
  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.3 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.5 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.3 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.3 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  // Indep dimension value on second bin
  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.5 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.5 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.5 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  // Indep dimension value in second bin
  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.7 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.7 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.7 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  // Parent dimension value on distribution upper bound
  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.9 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.9 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.9 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );

  // Dependent dimension value fixed
  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                    point, DepDimension, 0.5 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          2.5,
                          1e-15 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                    point, DepDimension, 0.6 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.5 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          5.0,
                          1e-15 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                    point, DepDimension, 0.8 );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          5.0,
                          1e-15 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled with a cascade to dependent
// distributions
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND(
                           PhaseSpaceDimensionDistribution,
                           sampleAndRecordTrialsWithCascadeUsingDimensionValue,
                           TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndepDimension );
  FETCH_TEMPLATE_PARAM( 1, WrappedDepDimension );

  constexpr PhaseSpaceDimension IndepDimension = WrappedIndepDimension::value;
  constexpr PhaseSpaceDimension DepDimension = WrappedDepDimension::value;
  
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  MonteCarlo::PhaseSpaceDimensionDistribution::DimensionCounterMap trials;
  trials[IndepDimension] = 0;
  trials[DepDimension] = 0;

  // Indep dimension value on first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.1 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.5 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 1 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.1 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 2 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.1 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                       1.25,
                       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 3 );

  // Indep dimension value in first bin
  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.3 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.5 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 4 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.3 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 5 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.3 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 6 );

  // Indep dimension value on second bin
  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.5 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 7 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.5 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 8 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.5 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 9 );

  // Indep dimension value in second bin
  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.7 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 10 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.7 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 11 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.7 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 12 );

  // Parent dimension value on distribution upper bound
  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.9 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 13 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.9 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.7 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 14 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.9 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<DepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 0 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 15 );

  // Dependent dimension value fixed
  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, DepDimension, 0.5 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.1 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          2.5,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 1 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 15 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, DepDimension, 0.6 );

  FRENSIE_CHECK_EQUAL( getCoordinate<IndepDimension>( point ), 0.5 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          5.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 2 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 15 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, DepDimension, 0.8 );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_EQUAL( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( getCoordinate<DepDimension>( point ), 0.8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          5.0,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( trials[IndepDimension], 3 );
  FRENSIE_CHECK_EQUAL( trials[DepDimension], 15 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhaseSpaceDimensionDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_phase_dimension_distribution" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Utility::UnivariateDistribution>
      raw_independent_distribution( new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dimension_distribution( new MonteCarlo::IndependentEnergyDimensionDistribution( raw_independent_distribution ) );

    std::shared_ptr<const Utility::BasicBivariateDistribution>
      raw_dep_distribution;

    {
      // Create the fully tabular distribution
      std::vector<double> primary_grid( {0.1, 0.5, 0.9} );
      std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
        secondary_dists( 3 );
    
      secondary_dists[0].reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );
      
      secondary_dists[1].reset( new Utility::UniformDistribution( 0.6, 0.8, 0.4 ) );
      secondary_dists[2] = secondary_dists[1];
    
      Utility::HistogramFullyTabularBasicBivariateDistribution* local_raw_dep_distribution =
        new Utility::HistogramFullyTabularBasicBivariateDistribution( primary_grid, secondary_dists );
    
      local_raw_dep_distribution->limitToPrimaryIndepLimits();
    
      raw_dep_distribution.reset( local_raw_dep_distribution );
    }

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dependent_secondary_directional_dimension_distribution( new MonteCarlo::EnergyDependentSecondaryDirectionalDimensionDistribution( raw_dep_distribution ) );

    // Assign the dep dimension dist. to the indep dimension dist.
    energy_dimension_distribution->addDependentDistribution(
               energy_dependent_secondary_directional_dimension_distribution );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(energy_dependent_secondary_directional_dimension_distribution) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    energy_dimension_distribution,
    energy_dependent_secondary_directional_dimension_distribution;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(energy_dimension_distribution) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(energy_dependent_secondary_directional_dimension_distribution) );

  iarchive.reset();

  // Check that the dependent dimensions are preserved
  FRENSIE_CHECK( !energy_dimension_distribution->hasParentDistribution() );
  FRENSIE_REQUIRE( energy_dependent_secondary_directional_dimension_distribution->hasParentDistribution() );
  FRENSIE_CHECK( &energy_dependent_secondary_directional_dimension_distribution->getParentDistribution() ==
                 energy_dimension_distribution.get() );

  MonteCarlo::PhaseSpaceDimensionDistribution::DependentDimensionSet
    dependent_dimensions;

  energy_dimension_distribution->getDependentDimensions( dependent_dimensions );

  FRENSIE_CHECK_EQUAL( dependent_dimensions.size(), 1 );
  FRENSIE_CHECK( dependent_dimensions.count( SECONDARY_DIRECTIONAL_DIMENSION ) );

  dependent_dimensions.clear();

  energy_dependent_secondary_directional_dimension_distribution->getDependentDimensions( dependent_dimensions );

  FRENSIE_CHECK_EQUAL( dependent_dimensions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the raw independent distribution
  raw_indep_distribution.reset(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

  // Create the raw fully-tabular dependent distribution
  {
    // Create the fully tabular distribution
    std::vector<double> primary_grid( {0.1, 0.5, 0.9} );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 3 );
    
    // Create the secondary distribution in the first bin
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );
      
    // Create the secondary distribution in the second bin
    secondary_dists[1].reset( new Utility::UniformDistribution( 0.6, 0.8, 0.4 ) );
    
    // Create the secondary distribution in the third bin
    secondary_dists[2] = secondary_dists[1];
    
    Utility::HistogramFullyTabularBasicBivariateDistribution* local_raw_distribution =
      new Utility::HistogramFullyTabularBasicBivariateDistribution( primary_grid, secondary_dists );
    
    local_raw_distribution->limitToPrimaryIndepLimits();
    
    raw_dep_distribution_a.reset( local_raw_distribution );
  }

  // Create the raw partially-tabular dependent distribution
  {
    // Create the partially tabular distribution
    std::vector<double> primary_grid( {0.1, 0.5, 0.9} );
    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
      secondary_dists( 3 );

    // Create the secondary distribution in the first bin
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );

    // Create the secondary distribution in the second bin
    secondary_dists[1].reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.6, 0.8 ) );
    
    // Create the secondary distribution in the third bin
    secondary_dists[2] = secondary_dists[1];
    
    Utility::HistogramPartiallyTabularBasicBivariateDistribution*
      local_raw_distribution =
      new Utility::HistogramPartiallyTabularBasicBivariateDistribution( primary_grid, secondary_dists );

    local_raw_distribution->limitToPrimaryIndepLimits();
    
    raw_dep_distribution_b.reset( local_raw_distribution );
  }
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
