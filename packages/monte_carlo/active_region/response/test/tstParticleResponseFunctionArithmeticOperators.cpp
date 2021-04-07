//---------------------------------------------------------------------------//
//!
//! \file   tstParticleResponseFunctionArithmeticOperators.cpp
//! \author Alex Robinson
//! \brief  Particle response function arithmetic operators unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
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
// Check that the addition operator behaves as expected
FRENSIE_UNIT_TEST( ParticleResponseFunction, addition_operator )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    energy_response_function, time_response_function;
  
  {
    std::shared_ptr<const Utility::UnivariateDistribution>
      response_distribution(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    energy_response_function.reset( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );

    time_response_function.reset( new MonteCarlo::TimeParticleResponseFunction( response_distribution ) );
  }

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    total_response_function = energy_response_function + time_response_function;

  FRENSIE_CHECK( total_response_function->isSpatiallyUniform() );
  FRENSIE_CHECK_LESS( total_response_function->description().find( '+' ),
                      total_response_function->description().size() );
  
  MonteCarlo::PhotonState photon( 1ull );
  photon.setEnergy( 1.0 );
  photon.setTime( 2.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( total_response_function->evaluate( photon ),
                                   0.503214724408055,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the subtraction operator behaves as expected
FRENSIE_UNIT_TEST( ParticleResponseFunction, subtraction_operator )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    energy_response_function, time_response_function;
  
  {
    std::shared_ptr<const Utility::UnivariateDistribution>
      response_distribution(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    energy_response_function.reset( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );

    time_response_function.reset( new MonteCarlo::TimeParticleResponseFunction( response_distribution ) );
  }

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    total_response_function = energy_response_function - time_response_function;

  FRENSIE_CHECK( total_response_function->isSpatiallyUniform() );
  FRENSIE_CHECK_LESS( total_response_function->description().find( '-' ),
                      total_response_function->description().size() );
  
  MonteCarlo::PhotonState photon( 1ull );
  photon.setEnergy( 1.0 );
  photon.setTime( 2.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( total_response_function->evaluate( photon ),
                                   0.23254415793482963,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the multiplication operator behaves as expected
FRENSIE_UNIT_TEST( ParticleResponseFunction, multiplication_operator )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    energy_response_function, time_response_function;
  
  {
    std::shared_ptr<const Utility::UnivariateDistribution>
      response_distribution(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    energy_response_function.reset( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );

    time_response_function.reset( new MonteCarlo::TimeParticleResponseFunction( response_distribution ) );
  }

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    total_response_function = energy_response_function * time_response_function;

  FRENSIE_CHECK( total_response_function->isSpatiallyUniform() );
  FRENSIE_CHECK_LESS( total_response_function->description().find( '*' ),
                      total_response_function->description().size() );

  MonteCarlo::PhotonState photon( 1ull );
  photon.setEnergy( 1.0 );
  photon.setTime( 2.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( total_response_function->evaluate( photon ),
                                   0.04978706836786395,
                                   1e-15 );

  // Check scalar multiplication
  total_response_function = 2.0 * energy_response_function;

  FRENSIE_CHECK( total_response_function->isSpatiallyUniform() );
  FRENSIE_CHECK_LESS( total_response_function->description().find( '*' ),
                      total_response_function->description().size() );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_response_function->evaluate( photon ),
                                   0.7357588823428847,
                                   1e-15 );

  total_response_function = energy_response_function * 0.5;

  FRENSIE_CHECK( total_response_function->isSpatiallyUniform() );
  FRENSIE_CHECK_LESS( total_response_function->description().find( '*' ),
                      total_response_function->description().size() );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_response_function->evaluate( photon ),
                                   0.18393972058572117,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the division operator behaves as expected
FRENSIE_UNIT_TEST( ParticleResponseFunction, division_operator )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    energy_response_function, time_response_function;
  
  {
    std::shared_ptr<const Utility::UnivariateDistribution>
      response_distribution(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    energy_response_function.reset( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );

    time_response_function.reset( new MonteCarlo::TimeParticleResponseFunction( response_distribution ) );
  }

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    total_response_function = energy_response_function / time_response_function;

  FRENSIE_CHECK( total_response_function->isSpatiallyUniform() );
  FRENSIE_CHECK_LESS( total_response_function->description().find( '/' ),
                      total_response_function->description().size() );
  
  MonteCarlo::PhotonState photon( 1ull );
  photon.setEnergy( 1.0 );
  photon.setTime( 2.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( total_response_function->evaluate( photon ),
                                   2.718281828459045,
                                   1e-15 );

  // Check scalar division
  total_response_function = 2.0 / energy_response_function;

  FRENSIE_CHECK( total_response_function->isSpatiallyUniform() );
  FRENSIE_CHECK_LESS( total_response_function->description().find( '/' ),
                      total_response_function->description().size() );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_response_function->evaluate( photon ),
                                   5.43656365691809,
                                   1e-15 );

  total_response_function = energy_response_function / 2.0;

  FRENSIE_CHECK( total_response_function->isSpatiallyUniform() );
  FRENSIE_CHECK_LESS( total_response_function->description().find( '/' ),
                      total_response_function->description().size() );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_response_function->evaluate( photon ),
                                   0.18393972058572117,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that multiple arithmetic operators can be combined
FRENSIE_UNIT_TEST( ParticleResponseFunction, multiple_operators )
{
  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    energy_response_function, time_response_function;
  
  {
    std::shared_ptr<const Utility::UnivariateDistribution>
      response_distribution(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    energy_response_function.reset( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );

    time_response_function.reset( new MonteCarlo::TimeParticleResponseFunction( response_distribution ) );
  }

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    total_response_function = 2*(energy_response_function-time_response_function)*time_response_function + (energy_response_function+time_response_function)/energy_response_function/2;
  
  FRENSIE_CHECK( total_response_function->isSpatiallyUniform() );
  
  MonteCarlo::PhotonState photon( 1ull );
  photon.setEnergy( 1.0 );
  photon.setTime( 2.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( (*total_response_function)( photon ),
                                   0.7468825795439807,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the response function can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ParticleResponseFunction,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_particle_response_function" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      energy_response_function, time_response_function;
  
    {
      std::shared_ptr<const Utility::UnivariateDistribution>
        response_distribution(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );

      energy_response_function.reset( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );

      time_response_function.reset( new MonteCarlo::TimeParticleResponseFunction( response_distribution ) );
    }

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      total_response_function = 2*(energy_response_function-time_response_function)*time_response_function + (energy_response_function+time_response_function)/energy_response_function/2;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(total_response_function) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    total_response_function;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(total_response_function) );

  iarchive.reset();

  MonteCarlo::PhotonState photon( 1ull );
  photon.setEnergy( 1.0 );
  photon.setTime( 2.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( (*total_response_function)( photon ),
                                   0.7468825795439807,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// end tstParticleResponseFunctionArithmeticOperators.cpp
//---------------------------------------------------------------------------//
