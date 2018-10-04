//---------------------------------------------------------------------------//
//!
//! \file   tstStandardAdjointParticleSourceComponent.cpp
//! \author Alex Robinson
//! \brief  The standard adjoint particle source component unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardAdjointParticleSourceComponent.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
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

using boost::units::cgs::cubic_centimeter;

typedef std::tuple<
  std::tuple<MonteCarlo::AdjointPhotonState,MonteCarlo::AdjointPhotonProbeState>,
  std::tuple<MonteCarlo::AdjointElectronState,MonteCarlo::AdjointElectronProbeState>
                  > TestParticleStateTypes;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::FilledGeometryModel> adjoint_photon_model;
std::shared_ptr<const MonteCarlo::FilledGeometryModel> adjoint_electron_model;
std::shared_ptr<const MonteCarlo::ParticleDistribution> particle_distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//

template<typename ParticleStateType>
struct ModelHelper;

template<>
struct ModelHelper<MonteCarlo::AdjointPhotonState>
{
  static inline std::shared_ptr<const MonteCarlo::FilledGeometryModel>& model()
  { return adjoint_photon_model; }
};

template<>
struct ModelHelper<MonteCarlo::AdjointElectronState>
{
  static inline std::shared_ptr<const MonteCarlo::FilledGeometryModel>& model()
  { return adjoint_electron_model; }
};

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the source component can be constructed
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardAdjointParticleSourceComponent,
                                   constructor,
                                   TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  FETCH_TEMPLATE_PARAM( 1, ProbeParticleStateType );

  // Construct a source component
  std::unique_ptr<const MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>( 0, 1.0, ModelHelper<ParticleStateType>::model(), particle_distribution ) );

  FRENSIE_CHECK_EQUAL( source_component->getId(), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getSelectionWeight(), 1.0 );

  MonteCarlo::ParticleSourceComponent::CellIdSet starting_cells;
  source_component->getStartingCells( starting_cells );

  FRENSIE_CHECK( starting_cells.empty() );
}

//---------------------------------------------------------------------------//
// Check that the source component can be constructed
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardAdjointParticleSourceComponent,
                                   constructor_rejection_cells,
                                   TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  FETCH_TEMPLATE_PARAM( 1, ProbeParticleStateType );

  // Construct a source component
  std::unique_ptr<const MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>( 0, 1.0, MonteCarlo::ParticleSourceComponent::CellIdSet( {1} ), ModelHelper<ParticleStateType>::model(), particle_distribution ) );

  FRENSIE_CHECK_EQUAL( source_component->getId(), 0 );
  FRENSIE_CHECK_EQUAL( source_component->getSelectionWeight(), 1.0 );

  MonteCarlo::ParticleSourceComponent::CellIdSet starting_cells;
  source_component->getStartingCells( starting_cells );

  FRENSIE_REQUIRE( !starting_cells.empty() );
  FRENSIE_CHECK( starting_cells.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the particle state can be sampled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardAdjointParticleSourceComponent,
                                   sampleParticleState,
                                   TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  FETCH_TEMPLATE_PARAM( 1, ProbeParticleStateType );

  constexpr const MonteCarlo::ParticleType particle_type =
    ParticleStateType::type;

  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component;

  if( particle_type == MonteCarlo::ADJOINT_PHOTON )
  {
    source_component.reset( new MonteCarlo::StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>( 0, 1.0, ModelHelper<ParticleStateType>::model(), particle_distribution ) );
  }
  else
  {
    source_component.reset( new MonteCarlo::StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>( 0, 1.0, static_cast<std::shared_ptr<const Geometry::Model> >(*ModelHelper<ParticleStateType>::model()), particle_distribution, std::vector<double>( {Utility::PhysicalConstants::electron_rest_mass_energy} ) ) );
  }

  MonteCarlo::ParticleBank bank;

  // Set the random number generator stream
  std::vector<double> fake_stream( 13 );
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

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source_component->sampleParticleState( bank, 0ull );

  FRENSIE_REQUIRE_EQUAL( bank.size(), 2 );

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
  FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getCell(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), particle_type );
  FRENSIE_CHECK( dynamic_cast<const ProbeParticleStateType&>( bank.top() ).isProbe() );
  FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getZPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getCell(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 0.05 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 0.05 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the source can accumulate sampling statistics
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardAdjointParticleSourceComponent,
                                   sampling_statistics,
                                   TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  FETCH_TEMPLATE_PARAM( 1, ProbeParticleStateType );

  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>( 0, 1.0, ModelHelper<ParticleStateType>::model(), particle_distribution ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source_component->sampleParticleState( bank, i );

  int samples = 0, trials = 0, bank_size = 0;
  int energy_dimension_samples = 0, energy_dimension_trials = 0;

  if( ParticleStateType::type == MonteCarlo::ADJOINT_PHOTON )
  {
    samples = 2000;
    trials = 2000;
    bank_size = 2000;

    energy_dimension_samples = 1000;
    energy_dimension_trials = 1000;
  }
  else
  {
    samples = 1000;
    trials = 1000;
    bank_size = 1000;

    energy_dimension_samples = 1000;
    energy_dimension_trials = 1000;
  }

  FRENSIE_CHECK_EQUAL( bank.size(), bank_size );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfTrials(), trials );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfSamples(), samples );
  FRENSIE_CHECK_EQUAL( source_component->getSamplingEfficiency(), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), trials );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), samples );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), trials );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), samples );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), trials );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), samples );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), trials );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), samples );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), trials );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), samples );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), trials );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), samples );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), energy_dimension_trials );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), energy_dimension_samples );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), trials );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), samples );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), trials );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), samples );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a summary of the source data can be printed
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardAdjointParticleSourceComponent,
                                   printSummary,
                                   TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  FETCH_TEMPLATE_PARAM( 1, ProbeParticleStateType );

  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>( 0, 1.0, ModelHelper<ParticleStateType>::model(), particle_distribution ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source_component->sampleParticleState( bank, i );

  std::ostringstream oss;

  FRENSIE_CHECK_NO_THROW( source_component->printSummary( oss ) );
  FRENSIE_CHECK( oss.str().size() > 0 );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a summary of the source data can be printed
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardAdjointParticleSourceComponent,
                                   logSummary,
                                   TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  FETCH_TEMPLATE_PARAM( 1, ProbeParticleStateType );

  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>( 0, 1.0, ModelHelper<ParticleStateType>::model(), particle_distribution ) );

  MonteCarlo::ParticleBank bank;

  for( int i = 0; i < 1000; ++i )
    source_component->sampleParticleState( bank, i );

  FRENSIE_CHECK_NO_THROW( source_component->logSummary() );
}

//---------------------------------------------------------------------------//
// Check that a summary of the source data can be printed
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardAdjointParticleSourceComponent,
                                   resetData,
                                   TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );
  FETCH_TEMPLATE_PARAM( 1, ProbeParticleStateType );

  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>( 0, 1.0, ModelHelper<ParticleStateType>::model(), particle_distribution ) );

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
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardAdjointParticleSourceComponent,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_standard_adjoint_particle_source_component" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    // Construct an adjoint photon source component
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      adjoint_photon_source_component( new MonteCarlo::StandardAdjointPhotonSourceComponent( 0, 1.0, adjoint_photon_model, particle_distribution ) );

    MonteCarlo::ParticleBank bank;

    for( int i = 0; i < 1000; ++i )
      adjoint_photon_source_component->sampleParticleState( bank, i );

    // Construct an adjoint electron source component
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      adjoint_electron_source_component( new MonteCarlo::StandardAdjointElectronSourceComponent( 1, 1.0, adjoint_electron_model, particle_distribution ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(adjoint_photon_source_component) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(adjoint_electron_source_component) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(adjoint_photon_model) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> model;

  std::shared_ptr<MonteCarlo::ParticleSourceComponent>
    adjoint_photon_source_component, adjoint_electron_source_component;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(adjoint_photon_source_component) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(adjoint_electron_source_component) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "adjoint_photon_model", model ) );

  iarchive.reset();

  {
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfTrials(), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfSamples(), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getSamplingEfficiency(), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 1000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 2000 );
    FRENSIE_CHECK_EQUAL( adjoint_photon_source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );

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

    adjoint_photon_source_component->sampleParticleState( bank, 0ull );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 2 );
    FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
    FRENSIE_CHECK_EQUAL( bank.top().getParticleType(),
                         MonteCarlo::ADJOINT_PHOTON );
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

    bank.pop();

    FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
    FRENSIE_CHECK_EQUAL( bank.top().getParticleType(),
                         MonteCarlo::ADJOINT_PHOTON );
    FRENSIE_CHECK( dynamic_cast<const MonteCarlo::AdjointPhotonProbeState&>( bank.top() ).isProbe() );
    FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getZPosition(), 0.0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(), -1.0, 1e-12 );
    FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
    FRENSIE_CHECK_SMALL( bank.top().getZDirection(), 1e-12 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(),
                         Utility::PhysicalConstants::electron_rest_mass_energy );
    FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
                         Utility::PhysicalConstants::electron_rest_mass_energy );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.5 );
    FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.5 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 0 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getCell(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 0.05 );
    FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 0.05 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfTrials(), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfSamples(), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getSamplingEfficiency(), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );

    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( adjoint_electron_source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );

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

    adjoint_electron_source_component->sampleParticleState( bank, 0ull );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 1 );
    FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
    FRENSIE_CHECK_EQUAL( bank.top().getParticleType(),
                         MonteCarlo::ADJOINT_ELECTRON );
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
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_scattering_center_database_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_database",
                                        test_scattering_center_database_name, "",
                                        "Test scattering center database name "
                                        "with path" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the models
  {
    // Determine the database directory
    boost::filesystem::path database_path =
      test_scattering_center_database_name;

    // Load the database
    const Data::ScatteringCenterPropertiesDatabase database( database_path );

    const Data::AtomProperties& h_properties =
      database.getAtomProperties( 1001 );

    // Set the sattering center definitions
    std::shared_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase>
      scattering_center_definition_database(
                          new MonteCarlo::ScatteringCenterDefinitionDatabase );

    MonteCarlo::ScatteringCenterDefinition& h_definition =
      scattering_center_definition_database->createDefinition( "H1 @ 293.6K", 1001 );

    h_definition.setAdjointPhotoatomicDataProperties(
          h_properties.getSharedAdjointPhotoatomicDataProperties(
                Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 0 ) );

    h_definition.setAdjointElectroatomicDataProperties(
          h_properties.getSharedAdjointElectroatomicDataProperties(
              Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

    // Set the material definitions
    std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
      material_definition_database( new MonteCarlo::MaterialDefinitionDatabase );

    material_definition_database->addDefinition( "H1 @ 293.6K", 2,
                                                 {"H1 @ 293.6K"}, {1.0} );

    // Create the unfilled model
    std::shared_ptr<const Geometry::Model> unfilled_model(
             new Geometry::InfiniteMediumModel( 1, 2, 1e24/cubic_centimeter ) );

    // Create the adjoint photon model
    {
      std::shared_ptr<MonteCarlo::SimulationProperties>
        properties( new MonteCarlo::SimulationProperties );
      properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );
      properties->setMaxAdjointPhotonEnergy( 10.0 );

      adjoint_photon_model.reset( new MonteCarlo::FilledGeometryModel(
                                         database_path,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );
    }

    // Create the adjoint electron model
    {
      std::shared_ptr<MonteCarlo::SimulationProperties>
        properties( new MonteCarlo::SimulationProperties );
      properties->setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );
      properties->setMaxAdjointElectronEnergy( 10.0 );

      adjoint_electron_model.reset( new MonteCarlo::FilledGeometryModel(
                                         database_path,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );
    }
  }

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
// end tstStandardAdjointParticleSourceComponent.cpp
//---------------------------------------------------------------------------//
