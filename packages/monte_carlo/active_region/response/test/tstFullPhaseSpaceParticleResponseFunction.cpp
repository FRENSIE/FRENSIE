//---------------------------------------------------------------------------//
//!
//! \file   tstFullPhaseSpaceParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Full phase-space particle response function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_FullPhaseSpaceParticleResponseFunction.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::ParticleDistribution> particle_distribution;

//---------------------------------------------------------------------------//
// Check if the response function is spatially uniform
FRENSIE_UNIT_TEST( FullPhaseSpaceParticleResponseFunction,
                   isSpatiallyUniform )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    response_function( new MonteCarlo::FullPhaseSpaceParticleResponseFunction( particle_distribution ) );

  FRENSIE_CHECK_EQUAL( response_function->isSpatiallyUniform(),
                       particle_distribution->isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check that the response function description can be returned
FRENSIE_UNIT_TEST( FullPhaseSpaceParticleResponseFunction, description )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    response_function( new MonteCarlo::FullPhaseSpaceParticleResponseFunction( particle_distribution ) );

  FRENSIE_CHECK_LESS( response_function->description().find( particle_distribution->getName() ),
                      response_function->description().size() );
}

//---------------------------------------------------------------------------//
// Check that the response function can be evaluated
FRENSIE_UNIT_TEST( FullPhaseSpaceParticleResponseFunction, evaluate )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    response_function( new MonteCarlo::FullPhaseSpaceParticleResponseFunction( particle_distribution ) );
  
  MonteCarlo::PhotonState photon( 1ull );
  photon.setPosition( 1.0, 2.0, 3.0 );
  photon.setDirection( 0.2672612419124244, 0.5345224838248488, 0.8017837257372732 );
  photon.setEnergy( 4.0 );
  photon.setTime( 5.0 );
  photon.setWeight( 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( response_function->evaluate( photon ),
                                   7.898227461547490183e-03,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the response function can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( FullPhaseSpaceParticleResponseFunction,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_full_phase_space_particle_response_function" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Utility::UnivariateDistribution>
      uniform_response_dist( new Utility::UniformDistribution( -10.0, 10.0, 2.0 ) );

    std::shared_ptr<const Utility::UnivariateDistribution>
      exponential_response_dist( new Utility::ExponentialDistribution( 1.0, 1.0 ) );
      
    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      x_dimension_dist( new MonteCarlo::IndependentPrimarySpatialDimensionDistribution( uniform_response_dist ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      y_dimension_dist( new MonteCarlo::IndependentSecondarySpatialDimensionDistribution( uniform_response_dist ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      z_dimension_dist( new MonteCarlo::IndependentTertiarySpatialDimensionDistribution( uniform_response_dist ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      u_dimension_dist( new MonteCarlo::IndependentPrimaryDirectionalDimensionDistribution( uniform_response_dist ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      v_dimension_dist( new MonteCarlo::IndependentSecondaryDirectionalDimensionDistribution( uniform_response_dist ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      w_dimension_dist( new MonteCarlo::IndependentTertiaryDirectionalDimensionDistribution( uniform_response_dist ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dimension_dist( new MonteCarlo::IndependentEnergyDimensionDistribution( exponential_response_dist ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dimension_dist( new MonteCarlo::IndependentTimeDimensionDistribution( exponential_response_dist ) );

    std::shared_ptr<MonteCarlo::StandardParticleDistribution>
      local_particle_distribution( new MonteCarlo::StandardParticleDistribution( "archived phase space dist" ) );

    local_particle_distribution->setDimensionDistribution( x_dimension_dist );
    local_particle_distribution->setDimensionDistribution( y_dimension_dist );
    local_particle_distribution->setDimensionDistribution( z_dimension_dist );
    local_particle_distribution->setDimensionDistribution( u_dimension_dist );
    local_particle_distribution->setDimensionDistribution( v_dimension_dist );
    local_particle_distribution->setDimensionDistribution( w_dimension_dist );
    local_particle_distribution->setDimensionDistribution( energy_dimension_dist );
    local_particle_distribution->setDimensionDistribution( time_dimension_dist );
    
    local_particle_distribution->constructDimensionDistributionDependencyTree();

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      response_function( new MonteCarlo::FullPhaseSpaceParticleResponseFunction( local_particle_distribution ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( response_function ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    response_function;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( response_function ) );

  iarchive.reset();

  MonteCarlo::PhotonState photon( 1ull );
  photon.setPosition( 1.0, 2.0, 3.0 );
  photon.setDirection( 0.2672612419124244, 0.5345224838248488, 0.8017837257372732 );
  photon.setEnergy( 4.0 );
  photon.setTime( 5.0 );
  photon.setWeight( 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( response_function->evaluate( photon ),
                                   7.898227461547490183e-03,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  std::shared_ptr<const Utility::UnivariateDistribution>
    uniform_response_dist( new Utility::UniformDistribution( -10.0, 10.0, 2.0 ) );

  std::shared_ptr<const Utility::UnivariateDistribution>
    exponential_response_dist( new Utility::ExponentialDistribution( 1.0, 1.0 ) );
  
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    x_dimension_dist( new MonteCarlo::IndependentPrimarySpatialDimensionDistribution( uniform_response_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    y_dimension_dist( new MonteCarlo::IndependentSecondarySpatialDimensionDistribution( uniform_response_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    z_dimension_dist( new MonteCarlo::IndependentTertiarySpatialDimensionDistribution( uniform_response_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    u_dimension_dist( new MonteCarlo::IndependentPrimaryDirectionalDimensionDistribution( uniform_response_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    v_dimension_dist( new MonteCarlo::IndependentSecondaryDirectionalDimensionDistribution( uniform_response_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    w_dimension_dist( new MonteCarlo::IndependentTertiaryDirectionalDimensionDistribution( uniform_response_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    energy_dimension_dist( new MonteCarlo::IndependentEnergyDimensionDistribution( exponential_response_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    time_dimension_dist( new MonteCarlo::IndependentTimeDimensionDistribution( exponential_response_dist ) );

  MonteCarlo::StandardParticleDistribution* local_particle_distribution =
    new MonteCarlo::StandardParticleDistribution( "phase space dist" );

  local_particle_distribution->setDimensionDistribution( x_dimension_dist );
  local_particle_distribution->setDimensionDistribution( y_dimension_dist );
  local_particle_distribution->setDimensionDistribution( z_dimension_dist );
  local_particle_distribution->setDimensionDistribution( u_dimension_dist );
  local_particle_distribution->setDimensionDistribution( v_dimension_dist );
  local_particle_distribution->setDimensionDistribution( w_dimension_dist );
  local_particle_distribution->setDimensionDistribution( energy_dimension_dist );
  local_particle_distribution->setDimensionDistribution( time_dimension_dist );
    
  local_particle_distribution->constructDimensionDistributionDependencyTree();
    
  particle_distribution.reset( local_particle_distribution );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFullPhaseSpaceParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
