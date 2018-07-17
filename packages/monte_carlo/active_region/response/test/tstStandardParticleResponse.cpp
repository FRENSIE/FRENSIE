//---------------------------------------------------------------------------//
//!
//! \file   tstStandardParticleResponse.cpp
//! \author Alex Robinson
//! \brief  Standard particle response unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleResponse.hpp"
#include "MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp"
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
// Check that the response name can be returned
FRENSIE_UNIT_TEST( StandardParticleResponse, getName )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    energy_response_function;

  {
    std::shared_ptr<const Utility::UnivariateDistribution>
      response_distribution(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    energy_response_function.reset( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );
  }

  std::shared_ptr<const MonteCarlo::ParticleResponse>
    particle_response( new MonteCarlo::StandardParticleResponse( energy_response_function ) );

  FRENSIE_CHECK_EQUAL( particle_response->getName(),
                       energy_response_function->description() );

  particle_response.reset( new MonteCarlo::StandardParticleResponse( "test response", energy_response_function ) );

  FRENSIE_CHECK_EQUAL( particle_response->getName(), "test response" );
}

//---------------------------------------------------------------------------//
// Check if the response is spatially uniform
FRENSIE_UNIT_TEST( StandardParticleResponse, isSpatiallyUniform )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    energy_response_function;

  {
    std::shared_ptr<const Utility::UnivariateDistribution>
      response_distribution(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    energy_response_function.reset( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );
  }

  std::shared_ptr<const MonteCarlo::ParticleResponse>
    particle_response( new MonteCarlo::StandardParticleResponse( energy_response_function ) );

  FRENSIE_CHECK_EQUAL( particle_response->isSpatiallyUniform(),
                       energy_response_function->isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check that the response can be evaluated
FRENSIE_UNIT_TEST( StandardParticleResponse, evaluate )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    energy_response_function;

  {
    std::shared_ptr<const Utility::UnivariateDistribution>
      response_distribution(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    energy_response_function.reset( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );
  }

  std::shared_ptr<const MonteCarlo::ParticleResponse>
    particle_response( new MonteCarlo::StandardParticleResponse( energy_response_function ) );

  MonteCarlo::PhotonState photon( 1ull );
  photon.setEnergy( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_response->evaluate( photon ),
                                   0.36787944117144233,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the default response behaves as expected
FRENSIE_UNIT_TEST( StandardParticleResponse, default_response )
{
  std::shared_ptr<const MonteCarlo::ParticleResponse>
    particle_response = MonteCarlo::ParticleResponse::getDefault();

  FRENSIE_CHECK_EQUAL( particle_response->getName(), "f(particle) = 1" );

  MonteCarlo::PhotonState photon( 1ull );
  photon.setEnergy( 1.0 );
  
  FRENSIE_CHECK_EQUAL( particle_response->evaluate( photon ), 1.0 );

  photon.setEnergy( 10.0 );

  FRENSIE_CHECK_EQUAL( particle_response->evaluate( photon ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the response function can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardParticleResponse,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_standard_particle_response" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      energy_response_function;

    {
      std::shared_ptr<const Utility::UnivariateDistribution>
        response_distribution(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );

      energy_response_function.reset( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );
    }

    std::shared_ptr<const MonteCarlo::ParticleResponse>
      particle_energy_response( new MonteCarlo::StandardParticleResponse( energy_response_function ) );

    std::shared_ptr<const MonteCarlo::ParticleResponse>
      default_particle_response = MonteCarlo::ParticleResponse::getDefault();

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(particle_energy_response) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(default_particle_response) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::ParticleResponse>
    particle_energy_response, default_particle_response;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(particle_energy_response) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(default_particle_response) );

  iarchive.reset();

  MonteCarlo::PhotonState photon( 1ull );
  photon.setEnergy( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_energy_response->evaluate( photon ),
                                   0.36787944117144233,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( default_particle_response->evaluate( photon ), 1.0 );
}

//---------------------------------------------------------------------------//
// end tstStandardParticleResponse.cpp
//---------------------------------------------------------------------------//
