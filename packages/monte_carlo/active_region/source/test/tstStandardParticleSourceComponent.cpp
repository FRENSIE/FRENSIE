//---------------------------------------------------------------------------//
//!
//! \file   tstStandardParticleSourceComponent.cpp
//! \author Alex Robinson
//! \brief  The standard particle source component unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSourceComponent.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using namespace MonteCarlo;

typedef std::tuple<MonteCarlo::NeutronState,
                   MonteCarlo::PhotonState,
                   MonteCarlo::ElectronState,
                   MonteCarlo::PositronState
                  > TestParticleStateTypes;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Geometry::Model> model;
std::shared_ptr<const MonteCarlo::ParticleDistribution> particle_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the source component can be constructed
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSourceComponent,
                            constructor,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  
  // Construct a source component
  std::unique_ptr<const MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 0, 1.0, model, particle_distribution ) );

  FRENSIE_CHECK_EQUAL( source_component->getId(), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getSelectionWeight(), 1.0 );

  MonteCarlo::ParticleSourceComponent::CellIdSet starting_cells;
  source_component->getStartingCells( starting_cells );
  
  FRENSIE_CHECK( starting_cells.empty() );
}

//---------------------------------------------------------------------------//
// Check that the source component can be constructed
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSourceComponent,
                            constructor_rejection_cells,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  
  // Construct a source component
  std::unique_ptr<const MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 0, 1.0, MonteCarlo::ParticleSourceComponent::CellIdSet( {1} ), model, particle_distribution ) );

  FRENSIE_CHECK_EQUAL( source_component->getId(), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getSelectionWeight(), 1.0 );

  MonteCarlo::ParticleSourceComponent::CellIdSet starting_cells;
  source_component->getStartingCells( starting_cells );
  
  FRENSIE_REQUIRE( !starting_cells.empty() );
  FRENSIE_CHECK( starting_cells.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the particle state can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSourceComponent,
                            sampleParticleState,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  
  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 2, 1.0, model, particle_distribution ) );

  constexpr const MonteCarlo::ParticleType particle_type =
    ParticleStateType::type;

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

  source_component->sampleParticleState( bank, 0ull );

  FRENSIE_REQUIRE_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), particle_type );
  FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), -1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getCell(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  bank.pop();

  // Set the random number generator stream
  fake_stream[0] = 0.5; // x
  fake_stream[1] = 0.5; // energy 
  fake_stream[2] = 0.0; // y
  fake_stream[3] = 0.5; // z
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source_component->sampleParticleState( bank, 1ull );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 1ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), particle_type );
  FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), -1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getZPosition(), 0.0 );
  FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getCell(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  bank.pop();

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // x
  fake_stream[1] = 1.0-1e-15; // energy 
  fake_stream[2] = 1.0-1e-15; // y
  fake_stream[3] = 0.0; // z
  fake_stream[4] = 0.5; // theta
  fake_stream[5] = 0.5; // mu
  fake_stream[6] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source_component->sampleParticleState( bank, 2ull );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 2ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), particle_type );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getYPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getZPosition(), -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getZDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getSourceTime(), 1.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getTime(), 1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getCell(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the source can accumulate sampling statistics
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSourceComponent,
                            sampling_statistics,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  
  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 2, 1.0, model, particle_distribution ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source_component->sampleParticleState( bank, i );

  FRENSIE_CHECK_EQUAL( bank.size(), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfTrials(), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfSamples(), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getSamplingEfficiency(), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 1000 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a summary of the source data can be printed
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSourceComponent,
                            printSummary,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  
  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 2, 1.0, model, particle_distribution ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source_component->sampleParticleState( bank, i );

  std::ostringstream oss;

  FRENSIE_CHECK_NO_THROW( source_component->printSummary( oss ) );
  FRENSIE_CHECK( oss.str().size() > 0 );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a summary of the source data can be logged
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSourceComponent,
                            logSummary,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  
  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 2, 1.0, model, particle_distribution ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source_component->sampleParticleState( bank, i );

  FRENSIE_CHECK_NO_THROW( source_component->logSummary() );
}

//---------------------------------------------------------------------------//
// Check that the source sampling statistics can be reset
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSourceComponent,
                            resetData,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  
  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 2, 1.0, model, particle_distribution ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source_component->sampleParticleState( bank, i );

  source_component->resetData();

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfTrials(), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfSamples(), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getSamplingEfficiency(), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardParticleSourceComponent,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_standard_particle_source_component" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    // Construct a neutron source component
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      neutron_source_component( new MonteCarlo::StandardNeutronSourceComponent( 0, 1.0, model, particle_distribution ) );

    // Construct a photon source component
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      photon_source_component( new MonteCarlo::StandardPhotonSourceComponent( 1, 1.0, model, particle_distribution ) );

    // Construct an electron source component
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      electron_source_component( new MonteCarlo::StandardElectronSourceComponent( 2, 1.0, MonteCarlo::ParticleSourceComponent::CellIdSet( {1} ), model, particle_distribution ) );

    // Construct a positron source component
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      positron_source_component( new MonteCarlo::StandardPositronSourceComponent( 3, 1.0, std::vector<Geometry::Model::EntityId>({1}), model, particle_distribution ) );

    MonteCarlo::ParticleBank bank;

    for( int i = 0; i < 1000; ++i )
      positron_source_component->sampleParticleState( bank, i );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(neutron_source_component) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(photon_source_component) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(electron_source_component) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(positron_source_component) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::ParticleSourceComponent>
    neutron_source_component, photon_source_component,
    electron_source_component, positron_source_component;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(neutron_source_component) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(photon_source_component) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(electron_source_component) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(positron_source_component) );

  iarchive.reset();

  {
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfTrials(), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfSamples(), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getSamplingEfficiency(), 1.0 );
    
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( neutron_source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
    
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
    
    neutron_source_component->sampleParticleState( bank, 0ull );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
    FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::NEUTRON );
    FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), -1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZPosition(), 1.0, 1e-12 );
    FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-7 );
    FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 1.0, 1e-12 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 5.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 0 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getCell(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfTrials(), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfSamples(), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getSamplingEfficiency(), 1.0 );
    
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
    
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
    
    photon_source_component->sampleParticleState( bank, 0ull );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
    FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::PHOTON );
    FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), -1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZPosition(), 1.0, 1e-12 );
    FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-7 );
    FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 1.0, 1e-12 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 5.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getCell(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfTrials(), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfSamples(), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getSamplingEfficiency(), 1.0 );
    
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
    
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
    
    electron_source_component->sampleParticleState( bank, 0ull );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
    FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
    FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), -1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZPosition(), 1.0, 1e-12 );
    FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-7 );
    FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 1.0, 1e-12 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 5.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 2 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getCell(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfTrials(), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfSamples(), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getSamplingEfficiency(), 1.0 );
    
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
    
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( positron_source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
    
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
    
    positron_source_component->sampleParticleState( bank, 0ull );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
    FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::POSITRON );
    FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), -1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZPosition(), 1.0, 1e-12 );
    FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-7 );
    FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 1.0, 1e-12 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 5.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 3 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getCell(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the model
  model.reset( new Geometry::InfiniteMediumModel( 1 ) );
  
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
                                       "source distribution",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );
  }

  // Set the dimension distributions
  {
    std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_a(
                          new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );
    std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_b(
                           new Utility::UniformDistribution( 0.0, 1.0, 1.0 ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      x_dimension_dist( new MonteCarlo::IndependentPrimarySpatialDimensionDistribution( raw_uniform_dist_a ) );
    tmp_particle_distribution->setDimensionDistribution( x_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      y_dimension_dist( new MonteCarlo::IndependentSecondarySpatialDimensionDistribution( raw_uniform_dist_a ) );
    tmp_particle_distribution->setDimensionDistribution( y_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      z_dimension_dist( new MonteCarlo::IndependentTertiarySpatialDimensionDistribution( raw_uniform_dist_a ) );
    tmp_particle_distribution->setDimensionDistribution( z_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dimension_dist( new MonteCarlo::IndependentTimeDimensionDistribution( raw_uniform_dist_b ) );
    tmp_particle_distribution->setDimensionDistribution( time_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dimension_dist;

    // Create the fully tabular energy distribution
    {
      std::vector<double> primary_grid( {-1.0, 0.0, 1.0} );
      std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
        secondary_dists( 3 );

      secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.5 ) );
      secondary_dists[1].reset( new Utility::UniformDistribution( 0.0, 20.0, 0.25 ) );
      secondary_dists[2] = secondary_dists[1];

      std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>
        raw_dependent_dist( new Utility::HistogramFullyTabularBasicBivariateDistribution( primary_grid, secondary_dists ) );
      raw_dependent_dist->limitToPrimaryIndepLimits();

      energy_dimension_dist.reset( new MonteCarlo::PrimarySpatialDependentEnergyDimensionDistribution( raw_dependent_dist ) );
    }

    tmp_particle_distribution->setDimensionDistribution( energy_dimension_dist );
    tmp_particle_distribution->constructDimensionDistributionDependencyTree();

    particle_distribution = tmp_particle_distribution;
  }
    
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardParticleSourceComponent.cpp
//---------------------------------------------------------------------------//
