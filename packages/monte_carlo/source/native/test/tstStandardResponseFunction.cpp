//---------------------------------------------------------------------------//
//!
//! \file   tstStandardResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Standard response function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardResponseFunction.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//
MonteCarlo::StandardResponseFunction::ParticleDistributionPointer
  particle_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the name of the response function can be returned
TEUCHOS_UNIT_TEST( StandardResponseFunction, getName )
{
  TEST_EQUALITY_CONST( particle_distribution->getName(), "test_dist" );
}

//---------------------------------------------------------------------------//
// Check that the response function id can be returned
TEUCHOS_UNIT_TEST( StandardResponseFunction, getId )
{
  TEST_EQUALITY_CONST( particle_distribution->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the response function can be evaluated
TEUCHOS_UNIT_TEST( StandardResponseFunction, evaluate )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setPosition( 0.0, 0.0, 0.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 0.1 );
  photon.setTime( 0.0 );
  photon.setWeight( 0.5 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.5 );

  photon.setEnergy( 10.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 1.5 );

  photon.setEnergy( 20.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 1.5 );
}

//---------------------------------------------------------------------------//
// Check that the response function is spatially uniform
TEUCHOS_UNIT_TEST( StandardResponseFunction, isSpatiallyUniform )
{
  TEST_ASSERT( particle_distribution->isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    tmp_particle_distribution( new MonteCarlo::StandardParticleDistribution(
                                                            0, "test_dist" ) );
  
  // Create the particle distribution
  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_a(
                          new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_b(
                         new Utility::UniformDistribution( 0.0, 100.0, 1.0 ) );

  Teuchos::Array<double> hist_bin_bounds( 3 );
  hist_bin_bounds[0] = 0.0;
  hist_bin_bounds[1] = 10.0;
  hist_bin_bounds[2] = 20.0;
  
  Teuchos::Array<double> hist_bin_values( 2 );
  hist_bin_values[0] = 0.5;
  hist_bin_values[1] = 1.5;
  
  std::shared_ptr<const Utility::OneDDistribution> raw_histogram_dist(
                                          new Utility::HistogramDistribution(
                                                           hist_bin_bounds,
                                                           hist_bin_values ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    x_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  tmp_particle_distribution->setDimensionDistribution( x_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    y_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  tmp_particle_distribution->setDimensionDistribution( y_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    z_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  tmp_particle_distribution->setDimensionDistribution( z_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    time_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION>( raw_uniform_dist_b ) );
  tmp_particle_distribution->setDimensionDistribution( time_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    energy_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION>( raw_histogram_dist ) );
  tmp_particle_distribution->setDimensionDistribution( energy_dimension_dist );

  tmp_particle_distribution->constructDimensionDistributionDependencyTree();
  
  particle_distribution = tmp_particle_distribution;
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardResponseFunction.cpp
//---------------------------------------------------------------------------//
