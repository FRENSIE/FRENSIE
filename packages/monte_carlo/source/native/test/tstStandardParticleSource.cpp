//---------------------------------------------------------------------------//
//!
//! \file   tstStandardParticleSource.cpp
//! \author Alex Robinson
//! \brief  Standard particle source unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_FullyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PartiallyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_HistogramFullyTabularTwoDDistribution.hpp"
#include "Utility_HistogramPartiallyTabularTwoDDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//
std::shared_ptr<const ParticleDistribution> particle_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the source id can be returned
TEUCHOS_UNIT_TEST( StandardParticleSource, getId )
{
  MonteCarlo::StandardParticleSource source( particle_distribution,
                                             MonteCarlo::PHOTON );
  
  TEST_EQUALITY_CONST( source.getId(), particle_distribution->getId() );
}

//---------------------------------------------------------------------------//
// Check that the particle type can be returned
TEUCHOS_UNIT_TEST( StandardParticleSource, getParticleType )
{
  std::shared_ptr<MonteCarlo::StandardParticleSource> source(
                new MonteCarlo::StandardParticleSource( particle_distribution,
                                                        MonteCarlo::PHOTON ) );

  TEST_EQUALITY_CONST( source->getParticleType(), MonteCarlo::PHOTON );

  source.reset(
               new MonteCarlo::StandardParticleSource( particle_distribution,
                                                       MonteCarlo::NEUTRON ) );

  TEST_EQUALITY_CONST( source->getParticleType(), MonteCarlo::NEUTRON );

  source.reset(
              new MonteCarlo::StandardParticleSource( particle_distribution,
                                                      MonteCarlo::ELECTRON ) );

  TEST_EQUALITY_CONST( source->getParticleType(), MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be sampled
TEUCHOS_UNIT_TEST( StandardParticleSource, sampleParticleState )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source(
                new MonteCarlo::StandardParticleSource( particle_distribution,
                                                        MonteCarlo::PHOTON ) );

  MonteCarlo::ParticleBank bank;

  // Set the random number generator stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0; // x
  fake_stream[1] = 0.5; // energy 
  fake_stream[2] = 0.5; // y
  fake_stream[3] = 1.0-1e-15; // z
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 1.0-1e-15; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source->sampleParticleState( bank, 0ull );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( bank.top().getXPosition(), -1.0 );
  TEST_EQUALITY_CONST( bank.top().getYPosition(), 0.0 );
  TEST_FLOATING_EQUALITY( bank.top().getZPosition(), 1.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 2 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  bank.pop();

  source.reset(
        new MonteCarlo::StandardParticleSource( particle_distribution,
                                                MonteCarlo::ADJOINT_PHOTON ) );

  source->sampleParticleState( bank, 0ull );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(),
                       MonteCarlo::ADJOINT_PHOTON );
  TEST_EQUALITY_CONST( bank.top().getXPosition(), -1.0 );
  TEST_EQUALITY_CONST( bank.top().getYPosition(), 0.0 );
  TEST_FLOATING_EQUALITY( bank.top().getZPosition(), 1.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 2 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  bank.pop();

  source.reset(
              new MonteCarlo::StandardParticleSource( particle_distribution,
                                                      MonteCarlo::NEUTRON ) );

  // Set the random number generator stream
  fake_stream[0] = 0.5; // x
  fake_stream[1] = 0.5; // energy 
  fake_stream[2] = 0.0; // y
  fake_stream[3] = 0.5; // z
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source->sampleParticleState( bank, 1ull );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY_CONST( bank.top().getXPosition(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getYPosition(), -1.0 );
  TEST_EQUALITY_CONST( bank.top().getZPosition(), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 10.0 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 10.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.5 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.5 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 2 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  bank.pop();

  source.reset(
       new MonteCarlo::StandardParticleSource( particle_distribution,
                                               MonteCarlo::ADJOINT_NEUTRON ) );

  TEST_THROW( source->sampleParticleState( bank, 1ull ),
              std::logic_error );

  // TEST_EQUALITY_CONST( bank.size(), 1 );
  // TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );
  // TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  // TEST_EQUALITY_CONST( bank.top().getXPosition(), 0.0 );
  // TEST_EQUALITY_CONST( bank.top().getYPosition(), -1.0 );
  // TEST_EQUALITY_CONST( bank.top().getZPosition(), 0.0 );
  // UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-12 );
  // UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  // TEST_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  // TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 10.0 );
  // TEST_EQUALITY_CONST( bank.top().getEnergy(), 10.0 );
  // TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.5 );
  // TEST_EQUALITY_CONST( bank.top().getTime(), 0.5 );
  // TEST_EQUALITY_CONST( bank.top().getSourceId(), 2 );
  // TEST_EQUALITY_CONST( bank.top().getSourceCell(), 0 );
  // TEST_EQUALITY_CONST( bank.top().getCell(), 0 );
  // TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  // TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  // bank.pop();
  
  source.reset(
              new MonteCarlo::StandardParticleSource( particle_distribution,
                                                      MonteCarlo::ELECTRON ) );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // x
  fake_stream[1] = 1.0-1e-15; // energy 
  fake_stream[2] = 1.0-1e-15; // y
  fake_stream[3] = 0.0; // z
  fake_stream[4] = 0.5; // theta
  fake_stream[5] = 0.5; // mu
  fake_stream[6] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source->sampleParticleState( bank, 2ull );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top().getXPosition(), 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getYPosition(), 1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getZPosition(), -1.0 );
  TEST_FLOATING_EQUALITY( bank.top().getXDirection(), -1.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getSourceEnergy(), 20.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 20.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getSourceTime(), 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getTime(), 1.0, 1e-15 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 2 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a particle state can be sampled
TEUCHOS_UNIT_TEST( StandardParticleSource,
                   sampleParticleState_critical_energies )
{
  std::shared_ptr<MonteCarlo::StandardParticleSource> source(
        new MonteCarlo::StandardParticleSource( particle_distribution,
                                                MonteCarlo::ADJOINT_PHOTON ) );

  {
    Teuchos::ArrayRCP<double> critical_line_energies( 2 );
    critical_line_energies[0] =
      Utility::PhysicalConstants::electron_rest_mass_energy;
    critical_line_energies[1] = 1.0;
    
    source->setCriticalLineEnergies( critical_line_energies );
  }

  MonteCarlo::ParticleBank bank;

  // Set the random number generator stream
  std::vector<double> fake_stream( 19 );
  fake_stream[0] = 0.0; // x
  fake_stream[1] = 0.5; // energy 
  fake_stream[2] = 0.5; // y
  fake_stream[3] = 1.0-1e-15; // z
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 1.0-1e-15; // mu
  fake_stream[6] = 0.0; // time
  
  fake_stream[7] = 0.5; // x
  fake_stream[8] = 0.5; // y
  fake_stream[9] = 0.5; // z
  fake_stream[10] = 0.5; // theta
  fake_stream[11] = 0.5; // mu
  fake_stream[12] = 0.5; // time

  fake_stream[13] = 0.0; // x
  fake_stream[14] = 1.0-1e-15; // y
  fake_stream[15] = 0.0; // z
  fake_stream[16] = 0.0; // theta
  fake_stream[17] = 1.0-1e-15; // mu
  fake_stream[18] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source->sampleParticleState( bank, 0ull );

  TEST_EQUALITY_CONST( bank.size(), 3 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(),
                       MonteCarlo::ADJOINT_PHOTON );
  TEST_EQUALITY_CONST( bank.top().getXPosition(), -1.0 );
  TEST_EQUALITY_CONST( bank.top().getYPosition(), 0.0 );
  TEST_FLOATING_EQUALITY( bank.top().getZPosition(), 1.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 2 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(),
                       MonteCarlo::ADJOINT_PHOTON );
  TEST_EQUALITY_CONST( bank.top().getXPosition(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getYPosition(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getZPosition(), 0.0 );
  TEST_FLOATING_EQUALITY( bank.top().getXDirection(), -1.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.5 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.5 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 2 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 0.05 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 0.05 );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(),
                       MonteCarlo::ADJOINT_PHOTON );
  TEST_EQUALITY_CONST( bank.top().getXPosition(), -1.0 );
  TEST_FLOATING_EQUALITY( bank.top().getYPosition(), 1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getZPosition(), -1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 1.0 );
  TEST_FLOATING_EQUALITY( bank.top().getSourceTime(), 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getTime(), 1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 2 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 0 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 0.1 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 0.1 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the source can accumulate sampling statistics
TEUCHOS_UNIT_TEST( StandardParticleSource, sampling_statistics )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source(
               new MonteCarlo::StandardParticleSource( particle_distribution,
                                                       MonteCarlo::NEUTRON ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source->sampleParticleState( bank, i );

  TEST_EQUALITY_CONST( bank.size(), 1000 );
  
  TEST_EQUALITY_CONST( source->getNumberOfTrials(), 1000 );
  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 1000 );
  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );

  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a summary of the source data can be printed
TEUCHOS_UNIT_TEST( StandardParticleSource, printSummary )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source(
               new MonteCarlo::StandardParticleSource( particle_distribution,
                                                       MonteCarlo::NEUTRON ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source->sampleParticleState( bank, i );

  std::ostringstream oss;

  source->printSummary( oss );

  TEST_ASSERT( oss.str().size() > 0 );
}

//---------------------------------------------------------------------------//
// Check that the source data can be exported
TEUCHOS_UNIT_TEST( StandardParticleSource, exportData )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source(
               new MonteCarlo::StandardParticleSource( particle_distribution,
                                                       MonteCarlo::NEUTRON ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source->sampleParticleState( bank, i );

  // Export the source data
  {
    std::shared_ptr<Utility::HDF5FileHandler>
      hdf5_file( new Utility::HDF5FileHandler );

    hdf5_file->openHDF5FileAndOverwrite( "test_source_hdf5_file.h5" );
    
    source->exportData( hdf5_file );
    
    hdf5_file->closeHDF5File();
  }

  // Load the exported source data
  MonteCarlo::SourceHDF5FileHandler exported_source_data(
                                 "test_source_hdf5_file.h5",
                                 MonteCarlo::HDF5FileHandler::READ_ONLY_FILE );

  TEST_ASSERT( exported_source_data.doesSourceExist( 2 ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceSamplingTrials( 2 ), 1000 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceSamples( 2 ), 1000 );

  TEST_ASSERT( exported_source_data.doesSourceDimensionExist( 2, MonteCarlo::PRIMARY_SPATIAL_DIMENSION ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamplingTrials( 2, MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamples( 2, MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000 );

  TEST_ASSERT( exported_source_data.doesSourceDimensionExist( 2, MonteCarlo::SECONDARY_SPATIAL_DIMENSION ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamplingTrials( 2, MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamples( 2, MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000 );
  
  TEST_ASSERT( exported_source_data.doesSourceDimensionExist( 2, MonteCarlo::TERTIARY_SPATIAL_DIMENSION ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamplingTrials( 2, MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamples( 2, MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000 );
  
  TEST_ASSERT( exported_source_data.doesSourceDimensionExist( 2, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamplingTrials( 2, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamples( 2, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000 );

  TEST_ASSERT( exported_source_data.doesSourceDimensionExist( 2, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamplingTrials( 2, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamples( 2, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000 );
  
  TEST_ASSERT( exported_source_data.doesSourceDimensionExist( 2, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamplingTrials( 2, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamples( 2, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000 );
  
  TEST_ASSERT( exported_source_data.doesSourceDimensionExist( 2, MonteCarlo::ENERGY_DIMENSION ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamplingTrials( 2, MonteCarlo::ENERGY_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamples( 2, MonteCarlo::ENERGY_DIMENSION ), 1000 );
  
  TEST_ASSERT( exported_source_data.doesSourceDimensionExist( 2, MonteCarlo::TIME_DIMENSION ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamplingTrials( 2, MonteCarlo::TIME_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamples( 2, MonteCarlo::TIME_DIMENSION ), 1000 );
  
  TEST_ASSERT( exported_source_data.doesSourceDimensionExist( 2, MonteCarlo::WEIGHT_DIMENSION ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamplingTrials( 2, MonteCarlo::WEIGHT_DIMENSION ), 1000 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceDimensionSamples( 2, MonteCarlo::WEIGHT_DIMENSION ), 1000 );

  std::set<Geometry::ModuleTraits::InternalCellHandle> start_cell_cache;

  exported_source_data.getStartCellCache( 2, start_cell_cache );

  TEST_EQUALITY_CONST( start_cell_cache.size(), 1 );
  TEST_ASSERT( start_cell_cache.count( 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the source data can be reset
TEUCHOS_UNIT_TEST( StandardParticleSource, resetData )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source(
               new MonteCarlo::StandardParticleSource( particle_distribution,
                                                       MonteCarlo::NEUTRON ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source->sampleParticleState( bank, i );

  source->resetData();
  
  TEST_EQUALITY_CONST( source->getNumberOfTrials(), 0 );
  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 0 );
  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );

  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
  
  TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 0 );
  TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_geom_xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_geom_xml_file",
                   &test_geom_xml_file_name,
                   "Test xml geometry file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the particle distribution
  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    tmp_particle_distribution;

  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );
  
    tmp_particle_distribution.reset(
                                  new MonteCarlo::StandardParticleDistribution(
                                       2,
                                       "source distribution",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );
  }

  // Set the dimension distributions
  {
    std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_a(
                          new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );
    std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_b(
                           new Utility::UniformDistribution( 0.0, 1.0, 1.0 ) );

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
      energy_dimension_dist;

    // Create the fully tabular energy distribution
    {
      Utility::HistogramFullyTabularTwoDDistribution::DistributionType
        distribution_data( 3 );
      
      // Create the secondary distribution in the first bin
      Utility::get<0>( distribution_data[0] ) = -1.0;
      Utility::get<1>( distribution_data[0] ).reset( new Utility::UniformDistribution( 0.0, 10.0, 0.5 ) );
      
      
      // Create the secondary distribution in the second bin
      Utility::get<0>( distribution_data[1] ) = 0.0;
      Utility::get<1>( distribution_data[1] ).reset( new Utility::UniformDistribution( 0.0, 20.0, 0.25 ) );
      
      // Create the secondary distribution in the third bin
      Utility::get<0>( distribution_data[2] ) = 1.0;
      Utility::get<1>( distribution_data[2] ) =
        Utility::get<1>( distribution_data[1] );

      std::shared_ptr<Utility::HistogramFullyTabularTwoDDistribution>
        raw_dependent_distribution( new Utility::HistogramFullyTabularTwoDDistribution( distribution_data ) );

      raw_dependent_distribution->limitToPrimaryIndepLimits();
      
      energy_dimension_dist.reset( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION>( raw_dependent_distribution ) );
    }
    
    tmp_particle_distribution->setDimensionDistribution( energy_dimension_dist );
    tmp_particle_distribution->constructDimensionDistributionDependencyTree();
    
    particle_distribution = tmp_particle_distribution;
  }
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardParticleSource.cpp
//---------------------------------------------------------------------------//
