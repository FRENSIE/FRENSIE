//---------------------------------------------------------------------------//
//!
//! \file   tstStandardParticleDistribution.cpp
//! \author Alex Robinson
//! \brief  Standard particle distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleDistribution.hpp"
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
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const ParticleDistribution> particle_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cartesian_spatial_cartesian_directional )
{
  
}

//---------------------------------------------------------------------------//
// CHeck that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cartesian_spatial_spherical_directional )
{

}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cylindrical_spatial_cartesian_directional )
{
  
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cylindrical_spatial_spherical_directional )
{
  
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_spherical_spatial_cartesian_directional )
{
  
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_spherical_spatial_spherical_directional )
{
  
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // MonteCarlo::StandardParticleDistribution::DimensionDistributionMap
  //   dimension_distributions;

  // MonteCarlo::StandardParticleDistribution::DimensionSet indep_dimensions;
  
  // // Create the primary spatial dimension distribution
  // {
  //   std::shared_ptr<const Utility::OneDDistribution> raw_distribution(
  //                         new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  //   dimension_distribution[MonteCarlo::PRIMARY_SPATIAL_DIMENSION].reset(
  //     new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_distribution ) );
  // }

  // // Create the secondary spatial dimension distribution
  // {
  //   std::shared_ptr<const Utility::OneDDistribution> raw_distribution(
  //                         new Utility::UniformDistribution( -2.0, 2.0, 1.0 ) );

  //   dimension_distribution[MonteCarlo::SECONDARY_SPATIAL_DIMENSION].reset(
  //      new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_distribution ) );  
  // }
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardParticleDistribution.cpp
//---------------------------------------------------------------------------//
