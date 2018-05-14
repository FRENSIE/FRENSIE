//---------------------------------------------------------------------------//
//!
//! \file   tstFullyTabularDependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Fully-tabular dependent phase space dimension dist. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_FullyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_HistogramFullyTabularTwoDDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::FullyTabularTwoDDistribution> raw_distribution;

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
// Tests.
//---------------------------------------------------------------------------//
// Test that the dimension can be returned
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  getDimension,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getDimension(), Dimension );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         getDimension );

//---------------------------------------------------------------------------//
// Test that the dimension class can be returned
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  getDimensionClass,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getDimensionClass(),
                       MonteCarlo::PhaseSpaceDimensionTraits<Dimension>::getClass() );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         getDimensionClass );

//---------------------------------------------------------------------------//
// Test that the indep. dimension can be returned
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  getParentDimension,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension> >
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getParentDimension(),
                       ParentDimension );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         getParentDimension );

//---------------------------------------------------------------------------//
// Test that the indep. dimension class can be returned
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  getParentDimensionClass,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::DependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension> >
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getParentDimensionClass(),
                       MonteCarlo::PhaseSpaceDimensionTraits<ParentDimension>::getClass() );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         getParentDimensionClass );

//---------------------------------------------------------------------------//
// Test that the distribution type name can be returned
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  getDistributionTypeName,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getDistributionTypeName(),
                       "FullyTabularTwoDDistribution" );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         getDistributionTypeName );

//---------------------------------------------------------------------------//
// Test that the distribution type name can be returned
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  isIndependent,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_ASSERT( !dimension_distribution->isIndependent() );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         isIndependent );

//---------------------------------------------------------------------------//
// Test if the distribution is dependent on another dimension
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  isDependentOnDimension,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_ASSERT( dimension_distribution->isDependentOnDimension( ParentDimension ) );
  TEST_ASSERT( !dimension_distribution->isDependentOnDimension( Dimension ) );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         isDependentOnDimension );

//---------------------------------------------------------------------------//
// Test if the distribution is continuous
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  isContinuous,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_ASSERT( dimension_distribution->isContinuous() );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         isContinuous );

//---------------------------------------------------------------------------//
// Test if the distribution is tabular
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  isTabular,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_ASSERT( dimension_distribution->isTabular() );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         isTabular );

//---------------------------------------------------------------------------//
// Test if the distribution is uniform
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  isUniform,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_ASSERT( !dimension_distribution->isUniform() );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         isUniform );

//---------------------------------------------------------------------------//
// Test if the distribution is uniform
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  hasForm,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  TEST_ASSERT( !dimension_distribution->hasForm( Utility::DELTA_DISTRIBUTION) );
  TEST_ASSERT( !dimension_distribution->hasForm( Utility::UNIFORM_DISTRIBUTION ) );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         hasForm );

//---------------------------------------------------------------------------//
// Test if the distribution can be evaluated without a cascade
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  evaluateWithoutCascade,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );
  setCoordinate<Dimension>( point, 0.1 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.5 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.9 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension value on first bin
  setCoordinate<ParentDimension>( point, 0.1 );
  setCoordinate<Dimension>( point, 0.1 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.5 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 0.9 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 1.0 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension value inside of first bin
  setCoordinate<ParentDimension>( point, 0.3 );
  setCoordinate<Dimension>( point, 0.1 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.5 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 0.9 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 1.0 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension value on second bin
  setCoordinate<ParentDimension>( point, 0.5 );
  setCoordinate<Dimension>( point, 0.1 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.6 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.4 );

  setCoordinate<Dimension>( point, 0.8 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.4 );

  setCoordinate<Dimension>( point, 1.0 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension value in second bin
  setCoordinate<ParentDimension>( point, 0.7 );
  setCoordinate<Dimension>( point, 0.1 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.6 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.4 );

  setCoordinate<Dimension>( point, 0.8 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.4 );

  setCoordinate<Dimension>( point, 1.0 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension value on distribution upper bound
  setCoordinate<ParentDimension>( point, 0.9 );
  setCoordinate<Dimension>( point, 0.1 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.6 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.4 );

  setCoordinate<Dimension>( point, 0.8 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.4 );

  setCoordinate<Dimension>( point, 1.0 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  // Parent dimension outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );
  setCoordinate<Dimension>( point, 0.1 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.5 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.9 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         evaluateWithoutCascade );

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  sampleWithoutCascade,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );

  TEST_THROW( dimension_distribution->sampleWithoutCascade( point ),
              std::logic_error );

  // Parent dimension value on first bin
  setCoordinate<ParentDimension>( point, 0.1 );
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );

  // Parent dimension value in first bin
  setCoordinate<ParentDimension>( point, 0.3 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );

  // Parent dimension value on second bin
  setCoordinate<ParentDimension>( point, 0.5 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.6 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );

  // Parent dimension value in second bin
  setCoordinate<ParentDimension>( point, 0.7 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.6 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );

  // Parent dimension value on distribution upper bound
  setCoordinate<ParentDimension>( point, 0.9 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.6 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );

  TEST_THROW( dimension_distribution->sampleWithoutCascade( point ),
              std::logic_error );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         sampleWithoutCascade );

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade and the trials
// can be counted
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  sampleAndRecordTrialsWithoutCascade,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  MonteCarlo::ModuleTraits::InternalCounter trials = 0;

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );

  TEST_THROW( dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials ),
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

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( trials, 1 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( trials, 2 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( trials, 3 );

  // Parent dimension value in first bin
  setCoordinate<ParentDimension>( point, 0.3 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( trials, 4 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( trials, 5 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( trials, 6 );

  // Parent dimension value on second bin
  setCoordinate<ParentDimension>( point, 0.5 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( trials, 7 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( trials, 8 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( trials, 9 );

  // Parent dimension value in second bin
  setCoordinate<ParentDimension>( point, 0.7 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( trials, 10 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( trials, 11 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( trials, 12 );

  // Parent dimension value on distribution upper bound
  setCoordinate<ParentDimension>( point, 0.9 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.6 );
  TEST_EQUALITY_CONST( trials, 13 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( trials, 14 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.8, 1e-15 );
  TEST_EQUALITY_CONST( trials, 15 );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );

  TEST_THROW( dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials ),
              std::logic_error );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         sampleAndRecordTrialsWithoutCascade );

//---------------------------------------------------------------------------//
// Test that the dimension value can be set and weighed approperiately
MC_UNIT_TEST_PSD_TEMPLATE_2_DECL( DependentPhaseSpaceDimensionDistribution,
                                  setDimensionValueAndApplyWeight,
                                  ParentDimension,
                                  Dimension )
{
  std::unique_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<ParentDimension,Dimension>( raw_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 0.05 );

  TEST_THROW( dimension_distribution->setDimensionValueAndApplyWeight( point, 0.1 ),
              std::logic_error );

  // Parent dimension value on first bin
  setCoordinate<ParentDimension>( point, 0.1 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.5 );
  
  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 2.5 );
  
  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.7 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 2.5 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.9 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.9 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 2.5 );

  // Parent dimension value on second bin
  setCoordinate<ParentDimension>( point, 0.5 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.6 );
  
  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.6 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ), 5.0, 1e-12 );
  
  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.7 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ), 5.0, 1e-12 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.8 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.8 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ), 5.0, 1e-12 );

  // Parent dimension value on distribution upper bound
  setCoordinate<ParentDimension>( point, 0.9 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.6 );
  
  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.6 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ), 5.0, 1e-12 );
  
  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.7 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.7 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ), 5.0, 1e-12 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.8 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.8 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ), 5.0, 1e-12 );

  // Parent dimension value outside of distribution bounds
  setCoordinate<ParentDimension>( point, 1.0 );

  TEST_THROW( dimension_distribution->setDimensionValueAndApplyWeight( point, 0.1 ),
              std::logic_error );
}

UNIT_TEST_INSTANTIATION( DependentPhaseSpaceDimensionDistribution,
                         setDimensionValueAndApplyWeight );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
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
  
  raw_distribution.reset( local_raw_distribution );
    
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFullyTabularDependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
