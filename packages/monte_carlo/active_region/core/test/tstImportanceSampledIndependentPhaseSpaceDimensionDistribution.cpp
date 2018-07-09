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

// FRENSIE Includes
#include "MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
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

typedef std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION>
                  > TestPhaseSpaceDimensionsNoWeight;

typedef decltype(std::tuple_cat(TestPhaseSpaceDimensionsNoWeight(),std::make_tuple(std::integral_constant<PhaseSpaceDimension,WEIGHT_DIMENSION>()))) TestPhaseSpaceDimensions;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test that the dimension can be returned
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   getDimension,
                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getDimension(), Dimension );
}

//---------------------------------------------------------------------------//
// Test that the dimension can be returned
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   getDimensionClass,
                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getDimensionClass(),
                       MonteCarlo::PhaseSpaceDimensionTraits<Dimension>::getClass() );
}

//---------------------------------------------------------------------------//
// Test that the distribution type name can be returned
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   getDistributionTypeName,
                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  FRENSIE_CHECK_EQUAL( dimension_distribution->getDistributionTypeName(),
                       "Exponential Distribution" );
}

//---------------------------------------------------------------------------//
// Test if the distribution is independent
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isIndependent,
                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  FRENSIE_CHECK( dimension_distribution->isIndependent() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is dependent on another dimension
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isDependentOnDimension,
                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ) );
  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ) );
  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ) );
  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ) );
  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ) );
  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ) );
  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( MonteCarlo::ENERGY_DIMENSION ) );
  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( MonteCarlo::TIME_DIMENSION ) );
  FRENSIE_CHECK( !dimension_distribution->isDependentOnDimension( MonteCarlo::WEIGHT_DIMENSION ) );
}

//---------------------------------------------------------------------------//
// Test if the distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isContinuous,
                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  FRENSIE_CHECK( dimension_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isTabular,
                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution_a(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution_b(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_a, distribution_b ) );

  FRENSIE_CHECK( !dimension_distribution->isTabular() );

  dimension_distribution.reset( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_b, distribution_a ) );

  FRENSIE_CHECK( dimension_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Test if the distribution is uniform
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   isUniform,
                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution_a(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution_b(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_a, distribution_b ) );

  FRENSIE_CHECK( !dimension_distribution->isUniform() );

  dimension_distribution.reset( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_b, distribution_a ) );

  FRENSIE_CHECK( dimension_distribution->isUniform() );
}

//---------------------------------------------------------------------------//
// Test if the distribution has the specified form
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   hasForm,
                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution_a(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 1.5 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution_b(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_a, distribution_b ) );

  FRENSIE_CHECK( !dimension_distribution->hasForm( Utility::UNIFORM_DISTRIBUTION ) );
  FRENSIE_CHECK( dimension_distribution->hasForm( Utility::EXPONENTIAL_DISTRIBUTION ) );

  dimension_distribution.reset( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution_b, distribution_a ) );

  FRENSIE_CHECK( dimension_distribution->hasForm( Utility::UNIFORM_DISTRIBUTION ) );
  FRENSIE_CHECK( !dimension_distribution->hasForm( Utility::EXPONENTIAL_DISTRIBUTION ) );
}

//---------------------------------------------------------------------------//
// Test if the distribution can be evaluated without a cascade
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   evaluateWithoutCascade,
                   TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                           new Utility::UniformDistribution( 0.5, 0.9, 0.5 ) );
    
  std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.5, 0.9 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );
  setCoordinate<Dimension>( point, 0.1 );
  
  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );

  setCoordinate<Dimension>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 0.7 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.5 );

  setCoordinate<Dimension>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( dimension_distribution->evaluateWithoutCascade( point ),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   sampleWithoutCascade,
                   TestPhaseSpaceDimensionsNoWeight )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.1, 0.9 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
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

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.4527729767328754,
                          1e-12 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.9738228486429138,
                          1e-12 );

  dimension_distribution->sampleWithoutCascade( point );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.6527729767328754,
                          1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Test if the distribution can be sampled without a cascade
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   sampleAndRecordTrialsWithoutCascade,
                   TestPhaseSpaceDimensionsNoWeight )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.1, 0.9 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  MonteCarlo::PhaseSpaceDimensionDistribution::Counter trials = 0;

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.4527729767328754,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 1 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.9738228486429138,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  dimension_distribution->sampleAndRecordTrialsWithoutCascade( point, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<Dimension>( point ), 0.9, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.6527729767328754,
                          1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Test that the dimension value can be set and weighted appropriately
FRENSIE_UNIT_TEST_TEMPLATE(
                   ImportanceSampledIndependentPhaseSpaceDimensionDistribution,
                   setDimensionValueAndApplyWeight,
                   TestPhaseSpaceDimensionsNoWeight )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.1, 0.9 ) );
  
  std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<Dimension>( distribution,
                                    importance_distribution ) );

  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.1 );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.8159662209160943,
                          1e-12 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.5 );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          1.2172785608036423,
                          1e-12 );

  dimension_distribution->setDimensionValueAndApplyWeight( point, 0.9 );

  FRENSIE_CHECK_EQUAL( getCoordinate<Dimension>( point ), 0.9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<Dimension>( point ),
                          0.8159662209160943,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhaseSpaceDimension,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_importance_sampled_independent_phase_dimension_distribution" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Utility::UnivariateDistribution> distribution(
                  new Utility::ExponentialDistribution( 1.0, 1.0, 0.1, 0.9 ) );
  
    std::shared_ptr<const Utility::UnivariateDistribution> importance_distribution(
                           new Utility::UniformDistribution( 0.1, 0.9, 0.5 ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPrimarySpatialDimensionDistribution( distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledIndependentSecondarySpatialDimensionDistribution( distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_spatial_dimension_distribution( new MonteCarlo::ImportanceSampledIndependentTertiarySpatialDimensionDistribution( distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      primary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledIndependentPrimaryDirectionalDimensionDistribution( distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      secondary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledIndependentSecondaryDirectionalDimensionDistribution( distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      tertiary_directional_dimension_distribution( new MonteCarlo::ImportanceSampledIndependentTertiaryDirectionalDimensionDistribution( distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dimension_distribution( new MonteCarlo::ImportanceSampledIndependentEnergyDimensionDistribution( distribution, importance_distribution ) );
    
    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dimension_distribution( new MonteCarlo::ImportanceSampledIndependentTimeDimensionDistribution( distribution, importance_distribution ) );

    std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
      weight_dimension_distribution( new MonteCarlo::ImportanceSampledIndependentWeightDimensionDistribution( importance_distribution, distribution ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_spatial_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(primary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(secondary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(tertiary_directional_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(energy_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(time_dimension_distribution) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(weight_dimension_distribution) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::PhaseSpaceDimensionDistribution>
    primary_spatial_dimension_distribution,
    secondary_spatial_dimension_distribution,
    tertiary_spatial_dimension_distribution,
    primary_directional_dimension_distribution,
    secondary_directional_dimension_distribution,
    tertiary_directional_dimension_distribution,
    energy_dimension_distribution,
    time_dimension_distribution,
    weight_dimension_distribution;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_spatial_dimension_distribution) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_spatial_dimension_distribution) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_spatial_dimension_distribution) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(primary_directional_dimension_distribution) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(secondary_directional_dimension_distribution) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(tertiary_directional_dimension_distribution) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(energy_dimension_distribution) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(time_dimension_distribution) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(weight_dimension_distribution) );

  iarchive.reset();

  {
    FRENSIE_CHECK_EQUAL( primary_spatial_dimension_distribution->getDimension(),
                         PRIMARY_SPATIAL_DIMENSION );
    
    std::vector<double> fake_stream( 3 );
    fake_stream[0] = 0.0;
    fake_stream[1] = 0.5;
    fake_stream[2] = 1.0 - 1e-15;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy );
    
    primary_spatial_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                     1.4527729767328754,
                                     1e-12 );
    
    primary_spatial_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                     0.9738228486429138,
                                     1e-12 );
    
    primary_spatial_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<PRIMARY_SPATIAL_DIMENSION>( point ), 0.9, 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_SPATIAL_DIMENSION>( point ),
                                     0.6527729767328754,
                                     1e-12 );
    
    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( secondary_spatial_dimension_distribution->getDimension(),
                         SECONDARY_SPATIAL_DIMENSION );
    
    std::vector<double> fake_stream( 3 );
    fake_stream[0] = 0.0;
    fake_stream[1] = 0.5;
    fake_stream[2] = 1.0 - 1e-15;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy );
    
    secondary_spatial_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<SECONDARY_SPATIAL_DIMENSION>( point ), 0.1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<SECONDARY_SPATIAL_DIMENSION>( point ),
                                     1.4527729767328754,
                                     1e-12 );
    
    secondary_spatial_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<SECONDARY_SPATIAL_DIMENSION>( point ), 0.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<SECONDARY_SPATIAL_DIMENSION>( point ),
                                     0.9738228486429138,
                                     1e-12 );
    
    secondary_spatial_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<SECONDARY_SPATIAL_DIMENSION>( point ), 0.9, 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<SECONDARY_SPATIAL_DIMENSION>( point ),
                                     0.6527729767328754,
                                     1e-12 );
    
    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( tertiary_spatial_dimension_distribution->getDimension(),
                         TERTIARY_SPATIAL_DIMENSION );
    
    std::vector<double> fake_stream( 3 );
    fake_stream[0] = 0.0;
    fake_stream[1] = 0.5;
    fake_stream[2] = 1.0 - 1e-15;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy );
    
    tertiary_spatial_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<TERTIARY_SPATIAL_DIMENSION>( point ), 0.1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TERTIARY_SPATIAL_DIMENSION>( point ),
                                     1.4527729767328754,
                                     1e-12 );
    
    tertiary_spatial_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<TERTIARY_SPATIAL_DIMENSION>( point ), 0.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TERTIARY_SPATIAL_DIMENSION>( point ),
                                     0.9738228486429138,
                                     1e-12 );
    
    tertiary_spatial_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<TERTIARY_SPATIAL_DIMENSION>( point ), 0.9, 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TERTIARY_SPATIAL_DIMENSION>( point ),
                                     0.6527729767328754,
                                     1e-12 );
    
    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( primary_directional_dimension_distribution->getDimension(),
                         PRIMARY_DIRECTIONAL_DIMENSION );
    
    std::vector<double> fake_stream( 3 );
    fake_stream[0] = 0.0;
    fake_stream[1] = 0.5;
    fake_stream[2] = 1.0 - 1e-15;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy );
    
    primary_directional_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_DIRECTIONAL_DIMENSION>( point ), 0.1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_DIRECTIONAL_DIMENSION>( point ),
                                     1.4527729767328754,
                                     1e-12 );
    
    primary_directional_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<PRIMARY_DIRECTIONAL_DIMENSION>( point ), 0.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_DIRECTIONAL_DIMENSION>( point ),
                                     0.9738228486429138,
                                     1e-12 );
    
    primary_directional_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<PRIMARY_DIRECTIONAL_DIMENSION>( point ), 0.9, 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<PRIMARY_DIRECTIONAL_DIMENSION>( point ),
                                     0.6527729767328754,
                                     1e-12 );
    
    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( secondary_directional_dimension_distribution->getDimension(),
                         SECONDARY_DIRECTIONAL_DIMENSION );
    
    std::vector<double> fake_stream( 3 );
    fake_stream[0] = 0.0;
    fake_stream[1] = 0.5;
    fake_stream[2] = 1.0 - 1e-15;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy );
    
    secondary_directional_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<SECONDARY_DIRECTIONAL_DIMENSION>( point ), 0.1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<SECONDARY_DIRECTIONAL_DIMENSION>( point ),
                                     1.4527729767328754,
                                     1e-12 );
    
    secondary_directional_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<SECONDARY_DIRECTIONAL_DIMENSION>( point ), 0.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<SECONDARY_DIRECTIONAL_DIMENSION>( point ),
                                     0.9738228486429138,
                                     1e-12 );
    
    secondary_directional_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<SECONDARY_DIRECTIONAL_DIMENSION>( point ), 0.9, 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<SECONDARY_DIRECTIONAL_DIMENSION>( point ),
                                     0.6527729767328754,
                                     1e-12 );
    
    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( tertiary_directional_dimension_distribution->getDimension(),
                         TERTIARY_DIRECTIONAL_DIMENSION );
    
    std::vector<double> fake_stream( 3 );
    fake_stream[0] = 0.0;
    fake_stream[1] = 0.5;
    fake_stream[2] = 1.0 - 1e-15;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy );
    
    tertiary_directional_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<TERTIARY_DIRECTIONAL_DIMENSION>( point ), 0.1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TERTIARY_DIRECTIONAL_DIMENSION>( point ),
                                     1.4527729767328754,
                                     1e-12 );
    
    tertiary_directional_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<TERTIARY_DIRECTIONAL_DIMENSION>( point ), 0.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TERTIARY_DIRECTIONAL_DIMENSION>( point ),
                                     0.9738228486429138,
                                     1e-12 );
    
    tertiary_directional_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<TERTIARY_DIRECTIONAL_DIMENSION>( point ), 0.9, 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TERTIARY_DIRECTIONAL_DIMENSION>( point ),
                                     0.6527729767328754,
                                     1e-12 );
    
    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( energy_dimension_distribution->getDimension(),
                         ENERGY_DIMENSION );
    
    std::vector<double> fake_stream( 3 );
    fake_stream[0] = 0.0;
    fake_stream[1] = 0.5;
    fake_stream[2] = 1.0 - 1e-15;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy );
    
    energy_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<ENERGY_DIMENSION>( point ), 0.1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<ENERGY_DIMENSION>( point ),
                                     1.4527729767328754,
                                     1e-12 );
    
    energy_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<ENERGY_DIMENSION>( point ), 0.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<ENERGY_DIMENSION>( point ),
                                     0.9738228486429138,
                                     1e-12 );
    
    energy_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<ENERGY_DIMENSION>( point ), 0.9, 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<ENERGY_DIMENSION>( point ),
                                     0.6527729767328754,
                                     1e-12 );
    
    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( time_dimension_distribution->getDimension(),
                         TIME_DIMENSION );
    
    std::vector<double> fake_stream( 3 );
    fake_stream[0] = 0.0;
    fake_stream[1] = 0.5;
    fake_stream[2] = 1.0 - 1e-15;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy );
    
    time_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                     1.4527729767328754,
                                     1e-12 );
    
    time_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_EQUAL( getCoordinate<TIME_DIMENSION>( point ), 0.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                     0.9738228486429138,
                                     1e-12 );
    
    time_dimension_distribution->sampleWithoutCascade( point );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinate<TIME_DIMENSION>( point ), 0.9, 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( getCoordinateWeight<TIME_DIMENSION>( point ),
                                     0.6527729767328754,
                                     1e-12 );
    
    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  // We can't sample from the weight dimension distribution so we will
  // evaluate it to ensure that the serialization/deserialization was
  // successful
  {
    FRENSIE_CHECK_EQUAL( weight_dimension_distribution->getDimension(),
                         WEIGHT_DIMENSION );
    
    MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy );
    setCoordinate<WEIGHT_DIMENSION>( point, 0.1 );
  
    FRENSIE_CHECK_EQUAL( weight_dimension_distribution->evaluateWithoutCascade( point ),
                         0.5 );

    setCoordinate<WEIGHT_DIMENSION>( point, 0.5 );

    FRENSIE_CHECK_EQUAL( weight_dimension_distribution->evaluateWithoutCascade( point ),
                         0.5 );

    setCoordinate<WEIGHT_DIMENSION>( point, 0.7 );

    FRENSIE_CHECK_EQUAL( weight_dimension_distribution->evaluateWithoutCascade( point ),
                         0.5 );

    setCoordinate<WEIGHT_DIMENSION>( point, 0.9 );

    FRENSIE_CHECK_EQUAL( weight_dimension_distribution->evaluateWithoutCascade( point ),
                         0.5 );

    setCoordinate<WEIGHT_DIMENSION>( point, 1.0 );

    FRENSIE_CHECK_EQUAL( weight_dimension_distribution->evaluateWithoutCascade( point ),
                         0.0 );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstImportanceSampledIndependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
