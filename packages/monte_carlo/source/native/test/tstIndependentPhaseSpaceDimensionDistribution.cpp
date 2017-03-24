//---------------------------------------------------------------------------//
//!
//! \file   tstIndependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Independent phase space dimension distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
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

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )   \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, SECONDARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, TERTIARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, PRIMARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, SECONDARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, TERTIARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ENERGY_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, TIME_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, WEIGHT_DIMENSION )

#define UNIT_TEST_INSTANTIATION_NO_WEIGHT_DIM( type, name )   \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, PRIMARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, SECONDARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, TERTIARY_SPATIAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, PRIMARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, SECONDARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, TERTIARY_DIRECTIONAL_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ENERGY_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, TIME_DIMENSION )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test that the dimension can be returned
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  getDimension,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getDimension(), Dimension );
}

UNIT_TEST_INSTANTIATION( IndependentPhaseSpaceDimensionDistribution,
                         getDimension );
                         
//---------------------------------------------------------------------------//
// Test that the dimension class can be returned
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  getDimensionClass,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getDimensionClass(),
                       MonteCarlo::PhaseSpaceDimensionTraits<Dimension>::getClass() );
}

UNIT_TEST_INSTANTIATION( IndependentPhaseSpaceDimensionDistribution,
                         getDimensionClass );

//---------------------------------------------------------------------------//
// Test that the distribution type name can be returned
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  getDistributionTypeName,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getDistributionTypeName(),
                       "Uniform Distribution" );
}

UNIT_TEST_INSTANTIATION( IndependentPhaseSpaceDimensionDistribution,
                         getDistributionTypeName );

//---------------------------------------------------------------------------//
// Test if the distribution is independent
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  isIndependent,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_ASSERT( dimension_distribution->isIndependent() );
}

UNIT_TEST_INSTANTIATION( IndependentPhaseSpaceDimensionDistribution,
                         isIndependent );

//---------------------------------------------------------------------------//
// Test if the distribution is dependent on another dimension
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  isDependentOnDimension,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_ASSERT( !dimension_distribution->isDependentOnDimension( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ) );
  TEST_ASSERT( !dimension_distribution->isDependentOnDimension( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ) );
  TEST_ASSERT( !dimension_distribution->isDependentOnDimension( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ) );
  TEST_ASSERT( !dimension_distribution->isDependentOnDimension( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ) );
  TEST_ASSERT( !dimension_distribution->isDependentOnDimension( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ) );
  TEST_ASSERT( !dimension_distribution->isDependentOnDimension( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ) );
  TEST_ASSERT( !dimension_distribution->isDependentOnDimension( MonteCarlo::ENERGY_DIMENSION ) );
  TEST_ASSERT( !dimension_distribution->isDependentOnDimension( MonteCarlo::TIME_DIMENSION ) );
  TEST_ASSERT( !dimension_distribution->isDependentOnDimension( MonteCarlo::WEIGHT_DIMENSION ) );
}

UNIT_TEST_INSTANTIATION( IndependentPhaseSpaceDimensionDistribution,
                         isDependentOnDimension );

//---------------------------------------------------------------------------//
// Test if the distribution is continuous
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  isContinuous,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_ASSERT( dimension_distribution->isContinuous() );

  basic_distribution.reset( new Utility::DeltaDistribution( 1.0 ) );

  dimension_distribution.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_ASSERT( !dimension_distribution->isContinuous() );
}

UNIT_TEST_INSTANTIATION( IndependentPhaseSpaceDimensionDistribution,
                         isContinuous );

//---------------------------------------------------------------------------//
// Test if the distribution is tabular
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  isTabular,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_ASSERT( dimension_distribution->isTabular() );

  basic_distribution.reset( new Utility::ExponentialDistribution( 1.0, 1.0 ) );

  dimension_distribution.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_ASSERT( !dimension_distribution->isTabular() );
}

UNIT_TEST_INSTANTIATION( IndependentPhaseSpaceDimensionDistribution,
                         isTabular );

//---------------------------------------------------------------------------//
// Test if the distribution is uniform
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  isUniform,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_ASSERT( dimension_distribution->isUniform() );

  basic_distribution.reset( new Utility::ExponentialDistribution( 1.0, 1.0 ) );

  dimension_distribution.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_ASSERT( !dimension_distribution->isUniform() );
}

UNIT_TEST_INSTANTIATION( IndependentPhaseSpaceDimensionDistribution,
                         isUniform );

//---------------------------------------------------------------------------//
// Test if the distribution has the specified form
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  hasForm,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_ASSERT( dimension_distribution->hasForm( Utility::UNIFORM_DISTRIBUTION ) );
  TEST_ASSERT( !dimension_distribution->hasForm( Utility::EXPONENTIAL_DISTRIBUTION ) );

  basic_distribution.reset( new Utility::ExponentialDistribution( 1.0, 1.0 ) );

  dimension_distribution.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  TEST_ASSERT( !dimension_distribution->hasForm( Utility::UNIFORM_DISTRIBUTION ) );
  TEST_ASSERT( dimension_distribution->hasForm( Utility::EXPONENTIAL_DISTRIBUTION ) );
}

UNIT_TEST_INSTANTIATION( IndependentPhaseSpaceDimensionDistribution,
                         hasForm );

//---------------------------------------------------------------------------//
// Test if the distribution can be evaluated without a cascade
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  evaluateWithoutCascade,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );
  setCoordinate<Dimension>( point, 0.1 );
  
  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.5 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 0.7 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 0.9 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 1.0 );

  TEST_EQUALITY_CONST( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );
}

UNIT_TEST_INSTANTIATION( IndependentPhaseSpaceDimensionDistribution,
                         evaluateWithoutCascade );

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  sampleWithoutCascade,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.1 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 1.0 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 1.0 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 1.0 );
}

UNIT_TEST_INSTANTIATION_NO_WEIGHT_DIM( IndependentPhaseSpaceDimensionDistribution, sampleWithoutCascade );

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade and the
// trials can be counted
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  sampleAndRecordTrialsWithoutCascade,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  MonteCarlo::ModuleTraits::InternalCounter trials = 0;

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.1 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials, 1 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials, 2 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 1.0 );
  TEST_EQUALITY_CONST( trials, 3 );
}

UNIT_TEST_INSTANTIATION_NO_WEIGHT_DIM( IndependentPhaseSpaceDimensionDistribution, sampleAndRecordTrialsWithoutCascade );

//---------------------------------------------------------------------------//
// Test that the dimension value can be set and weighted appropriately
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL( IndependentPhaseSpaceDimensionDistribution,
                                  setDimensionValueAndApplyWeight,
                                  Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> basic_distribution(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<Dimension>( basic_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.1 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.1 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 1.25 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.5 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 1.25 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.9 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.9 );
  TEST_EQUALITY_CONST( getCoordinateWeight<Dimension>( point ), 1.25 );
}

UNIT_TEST_INSTANTIATION_NO_WEIGHT_DIM( IndependentPhaseSpaceDimensionDistribution, setDimensionValueAndApplyWeight );

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
// end tstIndependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
