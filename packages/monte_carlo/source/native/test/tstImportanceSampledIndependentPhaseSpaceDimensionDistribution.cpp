//---------------------------------------------------------------------------//
//!
//! \file   tstImportanceSampledIndependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Importance sampled indep. phase space dimension dist. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp"
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
// Testing Variables
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
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   getDimension,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getDimension(), Dimension );
}

UNIT_TEST_INSTANTIATION( ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                         getDimension );

//---------------------------------------------------------------------------//
// Test that the dimension can be returned
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   getDimensionClass,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getDimensionClass(),
                       MonteCarlo::PhaseSpaceDimensionTraits<Dimension>::getClass() );
}

UNIT_TEST_INSTANTIATION(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   getDimensionClass );

//---------------------------------------------------------------------------//
// Test that the distribution type name can be returned
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   getDistributionTypeName,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  TEST_EQUALITY_CONST( dimension_distribution->getDistributionTypeName(),
                       "Exponential Distribution" );
}

UNIT_TEST_INSTANTIATION(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   getDistributionTypeName );

//---------------------------------------------------------------------------//
// Test if the distribution is independent
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isIndependent,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  TEST_ASSERT( dimension_distribution->isIndependent() );
}

UNIT_TEST_INSTANTIATION(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isIndependent );

//---------------------------------------------------------------------------//
// Test if the distribution is dependent on another dimension
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isDependentOnDimension,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

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

UNIT_TEST_INSTANTIATION(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isDependentOnDimension );

//---------------------------------------------------------------------------//
// Test if the distribution is continuous
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isContinuous,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  TEST_ASSERT( dimension_distribution->isContinuous() );
}

UNIT_TEST_INSTANTIATION(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isContinuous );

//---------------------------------------------------------------------------//
// Test if the distribution is tabular
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isTabular,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution_a(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> distribution_b(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_a, distribution_b ) );

  TEST_ASSERT( !dimension_distribution->isTabular() );

  dimension_distribution.reset( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_b, distribution_a ) );

  TEST_ASSERT( dimension_distribution->isTabular() );
}

UNIT_TEST_INSTANTIATION(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isTabular );

//---------------------------------------------------------------------------//
// Test if the distribution is uniform
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isUniform,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution_a(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> distribution_b(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_a, distribution_b ) );

  TEST_ASSERT( !dimension_distribution->isUniform() );

  dimension_distribution.reset( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_b, distribution_a ) );

  TEST_ASSERT( dimension_distribution->isUniform() );
}

UNIT_TEST_INSTANTIATION(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isUniform );

//---------------------------------------------------------------------------//
// Test if the distribution has the specified form
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   hasForm,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution_a(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> distribution_b(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_a, distribution_b ) );

  TEST_ASSERT( !dimension_distribution->hasForm( Utility::UNIFORM_DISTRIBUTION ) );
  TEST_ASSERT( dimension_distribution->hasForm( Utility::EXPONENTIAL_DISTRIBUTION ) );

  dimension_distribution.reset( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_b, distribution_a ) );

  TEST_ASSERT( dimension_distribution->hasForm( Utility::UNIFORM_DISTRIBUTION ) );
  TEST_ASSERT( !dimension_distribution->hasForm( Utility::EXPONENTIAL_DISTRIBUTION ) );
}

UNIT_TEST_INSTANTIATION(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   hasForm );

//---------------------------------------------------------------------------//
// Test if the distribution can be evaluated without a cascade
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   evaluateWithoutCascade,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution(
                           new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );
    
  std::shared_ptr<const Utility::OneDDistribution> importance_distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 0.9 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

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

UNIT_TEST_INSTANTIATION(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   evaluateWithoutCascade );

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   sampleWithoutCascade,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.1, 0.9 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.1 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.4527729767328754,
                          1e-12 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.9738228486429138,
                          1e-12 );

  dimension_distribution->sampleWithoutCascade( point );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.6527729767328754,
                          1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION_NO_WEIGHT_DIM( ImportanceSampledIndependentPhaseSpaceDimensionDistribution, sampleWithoutCascade );

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   sampleAndRecordTrialsWithoutCascade,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.1, 0.9 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

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
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.4527729767328754,
                          1e-12 );
  TEST_EQUALITY_CONST( trials, 1 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.9738228486429138,
                          1e-12 );
  TEST_EQUALITY_CONST( trials, 2 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  TEST_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.6527729767328754,
                          1e-12 );
  TEST_EQUALITY_CONST( trials, 3 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION_NO_WEIGHT_DIM( ImportanceSampledIndependentPhaseSpaceDimensionDistribution, sampleAndRecordTrialsWithoutCascade );

//---------------------------------------------------------------------------//
// Test that the dimension value can be set and weighted appropriately
MC_UNIT_TEST_PSD_TEMPLATE_1_DECL(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   setDimensionValueAndApplyWeight,
                   Dimension )
{
  std::shared_ptr<const Utility::OneDDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.1, 0.9 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.1 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.1 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.8159662209160943,
                          1e-12 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.5 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.5 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.2172785608036423,
                          1e-12 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.9 );

  TEST_EQUALITY_CONST( getCoordinate<Dimension>( point ), 0.9 );
  TEST_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.8159662209160943,
                          1e-12 );
}

UNIT_TEST_INSTANTIATION_NO_WEIGHT_DIM( ImportanceSampledIndependentPhaseSpaceDimensionDistribution, setDimensionValueAndApplyWeight );

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
// end tstImportanceSampledIndependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
