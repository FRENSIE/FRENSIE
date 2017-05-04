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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_FullyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PartiallyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_HistogramFullyTabularTwoDDistribution.hpp"
#include "Utility_HistogramPartiallyTabularTwoDDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::OneDDistribution> raw_indep_distribution;
std::shared_ptr<const Utility::FullyTabularTwoDDistribution> raw_dep_distribution_a;
std::shared_ptr<const Utility::PartiallyTabularTwoDDistribution> raw_dep_distribution_b;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION, SECONDARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION, TERTIARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION, PRIMARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION, SECONDARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION, TERTIARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION, ENERGY_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION, TIME_DIMENSION ) \
                                                                        \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_SPATIAL_DIMENSION, PRIMARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_SPATIAL_DIMENSION, TERTIARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_SPATIAL_DIMENSION, PRIMARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_SPATIAL_DIMENSION, SECONDARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_SPATIAL_DIMENSION, TERTIARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_SPATIAL_DIMENSION, ENERGY_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_SPATIAL_DIMENSION, TIME_DIMENSION ) \
                                                                        \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_SPATIAL_DIMENSION, PRIMARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_SPATIAL_DIMENSION, SECONDARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_SPATIAL_DIMENSION, PRIMARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_SPATIAL_DIMENSION, SECONDARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_SPATIAL_DIMENSION, TERTIARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_SPATIAL_DIMENSION, ENERGY_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_SPATIAL_DIMENSION, TIME_DIMENSION ) \
                                                                        \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_DIRECTIONAL_DIMENSION, PRIMARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_DIRECTIONAL_DIMENSION, SECONDARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_DIRECTIONAL_DIMENSION, TERTIARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_DIRECTIONAL_DIMENSION, SECONDARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_DIRECTIONAL_DIMENSION, TERTIARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_DIRECTIONAL_DIMENSION, ENERGY_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, PRIMARY_DIRECTIONAL_DIMENSION, TIME_DIMENSION ) \
                                                                        \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_DIRECTIONAL_DIMENSION, PRIMARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_DIRECTIONAL_DIMENSION, SECONDARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_DIRECTIONAL_DIMENSION, TERTIARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_DIRECTIONAL_DIMENSION, PRIMARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_DIRECTIONAL_DIMENSION, TERTIARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_DIRECTIONAL_DIMENSION, ENERGY_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, SECONDARY_DIRECTIONAL_DIMENSION, TIME_DIMENSION ) \
                                                                        \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_DIRECTIONAL_DIMENSION, PRIMARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_DIRECTIONAL_DIMENSION, SECONDARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_DIRECTIONAL_DIMENSION, TERTIARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_DIRECTIONAL_DIMENSION, PRIMARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_DIRECTIONAL_DIMENSION, SECONDARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_DIRECTIONAL_DIMENSION, ENERGY_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TERTIARY_DIRECTIONAL_DIMENSION, TIME_DIMENSION ) \
                                                                        \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ENERGY_DIMENSION, PRIMARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ENERGY_DIMENSION, SECONDARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ENERGY_DIMENSION, TERTIARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ENERGY_DIMENSION, PRIMARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ENERGY_DIMENSION, SECONDARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ENERGY_DIMENSION, TERTIARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ENERGY_DIMENSION, TIME_DIMENSION ) \
                                                                        \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TIME_DIMENSION, PRIMARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TIME_DIMENSION, SECONDARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TIME_DIMENSION, TERTIARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TIME_DIMENSION, PRIMARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TIME_DIMENSION, SECONDARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TIME_DIMENSION, TERTIARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, TIME_DIMENSION, ENERGY_DIMENSION ) 

//---------------------------------------------------------------------------//
// Check that the parent distribution can be returned
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( PhaseSpaceDimensionDistribution,
                                  getParentDistribution,
                                  IndepDimension,
                                  DepDimension )
{
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  // The indep dimension will not have a parent
  TEST_ASSERT( !indep_dimension_distribution->getParentDistribution() );
  TEST_EQUALITY_CONST( dep_dimension_distribution->getParentDistribution(),
                       indep_dimension_distribution.get() );
}

UNIT_TEST_INSTANTIATION( PhaseSpaceDimensionDistribution,
                         getParentDistribution );

//---------------------------------------------------------------------------//
// Check that the dependent distributions can be returned
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( PhaseSpaceDimensionDistribution,
                                  getDependentDimensions,
                                  IndepDimension,
                                  DepDimension )
{
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  // Get the dimensions that are dependent on the independent dimension
  MonteCarlo::PhaseSpaceDimensionDistribution::DependentDimensionSet
    dependent_dimensions;

  indep_dimension_distribution->getDependentDimensions( dependent_dimensions );

  TEST_EQUALITY_CONST( dependent_dimensions.size(), 1 );
  TEST_ASSERT( dependent_dimensions.count( DepDimension ) );

  // Get the dimensions that are dependent on the dependent dimension
  dependent_dimensions.clear();

  dep_dimension_distribution->getDependentDimensions( dependent_dimensions );

  TEST_EQUALITY_CONST( dependent_dimensions.size(), 0 );
}

UNIT_TEST_INSTANTIATION( PhaseSpaceDimensionDistribution,
                         getDependentDimensions );

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated with a cascade to dependent
// distributions
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( PhaseSpaceDimensionDistribution,
                                  evaluateWithCascade,
                                  IndepDimension,
                                  DepDimension )
{
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

  // Assign the dep dimension distribution to the indep dimension distribution
  indep_dimension_distribution->addDependentDistribution(
                                                  dep_dimension_distribution );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Indep dimension value outside of distribution bounds
  setCoordinate<IndepDimension>( point, 0.05 );
  setCoordinate<DepDimension>( point, 0.1 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.5 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.9 );
  
  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value on first bin
  setCoordinate<IndepDimension>( point, 0.1 );
  setCoordinate<DepDimension>( point, 0.1 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.5 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.25 );

  setCoordinate<DepDimension>( point, 0.9 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.25 );

  setCoordinate<DepDimension>( point, 1.0 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value inside of first bin
  setCoordinate<IndepDimension>( point, 0.3 );
  setCoordinate<DepDimension>( point, 0.1 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.5 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.25 );

  setCoordinate<DepDimension>( point, 0.9 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.25 );

  setCoordinate<DepDimension>( point, 1.0 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value on second bin
  setCoordinate<IndepDimension>( point, 0.5 );
  setCoordinate<DepDimension>( point, 0.1 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.6 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 0.8 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 1.0 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value in second bin
  setCoordinate<IndepDimension>( point, 0.7 );
  setCoordinate<DepDimension>( point, 0.1 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.6 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 0.8 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 1.0 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value on distribution upper bound
  setCoordinate<IndepDimension>( point, 0.9 );
  setCoordinate<DepDimension>( point, 0.1 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.6 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 0.8 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.2 );

  setCoordinate<DepDimension>( point, 1.0 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  // Indep dimension value outside of distribution bounds
  setCoordinate<IndepDimension>( point, 1.0 );
  setCoordinate<DepDimension>( point, 0.1 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.5 );

  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );

  setCoordinate<DepDimension>( point, 0.9 );
  
  TEST_EQUALITY_CONST( indep_dimension_distribution->evaluateWithCascade( point ),
                       0.0 );
}

UNIT_TEST_INSTANTIATION( PhaseSpaceDimensionDistribution,
                         evaluateWithCascade );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled with a cascade to dependent
// distributions
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( PhaseSpaceDimensionDistribution,
                                  sampleWithCascade,
                                  IndepDimension,
                                  DepDimension )
{
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

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

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.5 );

  indep_dimension_distribution->sampleWithCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );

  indep_dimension_distribution->sampleWithCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );

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

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.5 );

  indep_dimension_distribution->sampleWithCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );

  indep_dimension_distribution->sampleWithCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );

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

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );

  indep_dimension_distribution->sampleWithCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );

  indep_dimension_distribution->sampleWithCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );

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

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );

  indep_dimension_distribution->sampleWithCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );

  indep_dimension_distribution->sampleWithCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );

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

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );

  indep_dimension_distribution->sampleWithCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );

  indep_dimension_distribution->sampleWithCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION( PhaseSpaceDimensionDistribution,
                         sampleWithCascade );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled with a cascade to dependent
// distributions
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( PhaseSpaceDimensionDistribution,
                                  sampleAndRecordTrialsWithCascade,
                                  IndepDimension,
                                  DepDimension )
{
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

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

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 1 );
  TEST_EQUALITY_CONST( trials[DepDimension], 1 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 2 );
  TEST_EQUALITY_CONST( trials[DepDimension], 2 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 3 );
  TEST_EQUALITY_CONST( trials[DepDimension], 3 );

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

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 4 );
  TEST_EQUALITY_CONST( trials[DepDimension], 4 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 5 );
  TEST_EQUALITY_CONST( trials[DepDimension], 5 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.3, 1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 6 );
  TEST_EQUALITY_CONST( trials[DepDimension], 6 );

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

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 7 );
  TEST_EQUALITY_CONST( trials[DepDimension], 7 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 8 );
  TEST_EQUALITY_CONST( trials[DepDimension], 8 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.5, 1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 9 );
  TEST_EQUALITY_CONST( trials[DepDimension], 9 );

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

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 10 );
  TEST_EQUALITY_CONST( trials[DepDimension], 10 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 11 );
  TEST_EQUALITY_CONST( trials[DepDimension], 11 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.7, 1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 12 );
  TEST_EQUALITY_CONST( trials[DepDimension], 12 );

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

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 13 );
  TEST_EQUALITY_CONST( trials[DepDimension], 13 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 14 );
  TEST_EQUALITY_CONST( trials[DepDimension], 14 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 15 );
  TEST_EQUALITY_CONST( trials[DepDimension], 15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION( PhaseSpaceDimensionDistribution,
                         sampleAndRecordTrialsWithCascade );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled with a cascade to dependent
// distributions
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( PhaseSpaceDimensionDistribution,
                                  sampleWithCascadeUsingDimensionValue,
                                  IndepDimension,
                                  DepDimension )
{
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

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

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.1 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.1 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                       1.25,
                       1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  // Indep dimension value in first bin
  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.3 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.3 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.3 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.3 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.3 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.3 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  // Indep dimension value on second bin
  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.5 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.5 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.5 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  // Indep dimension value in second bin
  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.7 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.7 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.7 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.7 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.7 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.7 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  // Parent dimension value on distribution upper bound
  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.9 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.9 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.9 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.9 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                  point, IndepDimension, 0.9 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.9 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );

  // Dependent dimension value fixed
  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                    point, DepDimension, 0.5 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_EQUALITY_CONST( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          2.5,
                          1e-15 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                    point, DepDimension, 0.6 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          5.0,
                          1e-15 );

  indep_dimension_distribution->sampleWithCascadeUsingDimensionValue(
                                                    point, DepDimension, 0.8 );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.8 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          5.0,
                          1e-15 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION( PhaseSpaceDimensionDistribution,
                         sampleWithCascadeUsingDimensionValue );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled with a cascade to dependent
// distributions
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL(
                           PhaseSpaceDimensionDistribution,
                           sampleAndRecordTrialsWithCascadeUsingDimensionValue,
                           IndepDimension,
                           DepDimension )
{
  // Create the distribution for the independent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    indep_dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<IndepDimension>( raw_indep_distribution ) );

  // Create the distribution for the dependent dimension
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    dep_dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<IndepDimension,DepDimension>( raw_dep_distribution_a ) );

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

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 1 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.1 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 2 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.1 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                       1.25,
                       1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 3 );

  // Indep dimension value in first bin
  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.3 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.3 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 4 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.3 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.3 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 5 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.3 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.3 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 6 );

  // Indep dimension value on second bin
  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.5 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 7 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.5 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 8 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.5 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 9 );

  // Indep dimension value in second bin
  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.7 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.7 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 10 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.7 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.7 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 11 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.7 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.7 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 12 );

  // Parent dimension value on distribution upper bound
  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.9 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.9 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 13 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.9 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.9 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 14 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, IndepDimension, 0.9 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.9 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<IndepDimension>( point ),
                          1.25,
                          1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinate<DepDimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<DepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 0 );
  TEST_EQUALITY_CONST( trials[DepDimension], 15 );

  // Dependent dimension value fixed
  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, DepDimension, 0.5 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.1 );
  TEST_EQUALITY_CONST( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          2.5,
                          1e-15 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 1 );
  TEST_EQUALITY_CONST( trials[DepDimension], 15 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, DepDimension, 0.6 );

  TEST_EQUALITY_CONST( getCoordinate<IndepDimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.6 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          5.0,
                          1e-15 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 2 );
  TEST_EQUALITY_CONST( trials[DepDimension], 15 );

  indep_dimension_distribution->sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          point, trials, DepDimension, 0.8 );

  TEST_FLOATING_EQUALITY( getCoordinate<IndepDimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<IndepDimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( getCoordinate<DepDimension>( point ), 0.8 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<DepDimension>( point ),
                          5.0,
                          1e-15 );
  TEST_EQUALITY_CONST( trials[IndepDimension], 3 );
  TEST_EQUALITY_CONST( trials[DepDimension], 15 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION( PhaseSpaceDimensionDistribution,
                         sampleAndRecordTrialsWithCascadeUsingDimensionValue );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the raw independent distribution
  raw_indep_distribution.reset(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

  // Create the raw fully-tabular dependent distribution
  {
    // Create the fully tabular distribution
    Utility::HistogramFullyTabularTwoDDistribution::DistributionType
      distribution_data( 3 );
    
    // Create the secondary distribution in the first bin
    Utility::get<0>( distribution_data[0] ) = 0.1;
    Utility::get<1>( distribution_data[0] ).reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );

      
    // Create the secondary distribution in the second bin
    Utility::get<0>( distribution_data[1] ) = 0.5;
    Utility::get<1>( distribution_data[1] ).reset( new Utility::UniformDistribution( 0.6, 0.8, 0.4 ) );
    
    // Create the secondary distribution in the third bin
    Utility::get<0>( distribution_data[2] ) = 0.9;
    Utility::get<1>( distribution_data[2] ) =
      Utility::get<1>( distribution_data[1] );
    
    Utility::HistogramFullyTabularTwoDDistribution* local_raw_distribution =
      new Utility::HistogramFullyTabularTwoDDistribution( distribution_data );
    
    local_raw_distribution->limitToPrimaryIndepLimits();
    
    raw_dep_distribution_a.reset( local_raw_distribution );
  }

  // Create the raw partially-tabular dependent distribution
  {
    // Create the partially tabular distribution
    Utility::HistogramPartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 3 );

    // Create the secondary distribution in the first bin
    Utility::get<0>( distribution_data[0] ) = 0.1;
    Utility::get<1>( distribution_data[0] ).reset( new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );

    // Create the secondary distribution in the second bin
    Utility::get<0>( distribution_data[1] ) = 0.5;
    Utility::get<1>( distribution_data[1] ).reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.6, 0.8 ) );
    
    // Create the secondary distribution in the third bin
    Utility::get<0>( distribution_data[2] ) = 0.9;
    Utility::get<1>( distribution_data[2] ) =
      Utility::get<1>( distribution_data[1] );
    
    Utility::HistogramPartiallyTabularTwoDDistribution*
      local_raw_distribution =
      new Utility::HistogramPartiallyTabularTwoDDistribution( distribution_data );

    local_raw_distribution->limitToPrimaryIndepLimits();
    
    raw_dep_distribution_b.reset( local_raw_distribution );
  }
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();


//---------------------------------------------------------------------------//
// end tstPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
