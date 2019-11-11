//---------------------------------------------------------------------------//
//!
//! \file   tstSinglePhaseSpaceDimensionParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Single phase-space dimension particle response function unit tests
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

using namespace MonteCarlo;

typedef std::tuple<std::integral_constant<PhaseSpaceDimension,PRIMARY_SPATIAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,SECONDARY_SPATIAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,TERTIARY_SPATIAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,PRIMARY_DIRECTIONAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,SECONDARY_DIRECTIONAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,TERTIARY_DIRECTIONAL_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,ENERGY_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,TIME_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,WEIGHT_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,SOURCE_ENERGY_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,SOURCE_TIME_DIMENSION>,
                   std::integral_constant<PhaseSpaceDimension,SOURCE_WEIGHT_DIMENSION>
                  > TestPhaseSpaceDimensions;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Check if the response function is spatially uniform
FRENSIE_UNIT_TEST_TEMPLATE( SinglePhaseSpaceDimensionParticleResponseFunction,
                            isSpatiallyUniform,
                            TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;

  std::shared_ptr<const Utility::UnivariateDistribution> response_distribution(
                         new Utility::UniformDistribution( 1e-3, 20.0, 0.5 ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    response_function( new MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<Dimension>( response_distribution ) );

  if( MonteCarlo::PhaseSpaceDimensionTraits<Dimension>::getClass() ==
      MonteCarlo::SPATIAL_DIMENSION_CLASS )
  {
    FRENSIE_CHECK( response_function->isSpatiallyUniform() );

    response_distribution.reset(
                            new Utility::ExponentialDistribution( 1.0, 1.0 ) );
    response_function.reset( new MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<Dimension>( response_distribution ) );

    FRENSIE_CHECK( !response_function->isSpatiallyUniform() );
  }
  else
  {
    FRENSIE_CHECK( response_function->isSpatiallyUniform() );
  }
}

//---------------------------------------------------------------------------//
// Check that the response function description can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SinglePhaseSpaceDimensionParticleResponseFunction,
                            description,
                            TestPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedDimension );
  constexpr PhaseSpaceDimension Dimension = WrappedDimension::value;
  
  std::shared_ptr<const Utility::UnivariateDistribution> response_distribution(
                         new Utility::UniformDistribution( 1e-3, 20.0, 0.5 ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    response_function( new MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<Dimension>( response_distribution ) );

  std::string expected_description( "f_custom(" );
  expected_description += Utility::toString( Dimension );
  expected_description += ")";
  
  FRENSIE_CHECK_EQUAL( response_function->description(),
                       expected_description );
}

//---------------------------------------------------------------------------//
// Check that the response function can be evaluated
FRENSIE_UNIT_TEST( SinglePhaseSpaceDimensionParticleResponseFunction,
                   evaluate )
{
  std::shared_ptr<const Utility::UnivariateDistribution> response_distribution(
                           new Utility::ExponentialDistribution( 1.0, 1.0 ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    x_response_function( new MonteCarlo::XPositionParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    y_response_function( new MonteCarlo::YPositionParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    z_response_function( new MonteCarlo::ZPositionParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    u_response_function( new MonteCarlo::XDirectionParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    v_response_function( new MonteCarlo::YDirectionParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    w_response_function( new MonteCarlo::ZDirectionParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    energy_response_function( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    time_response_function( new MonteCarlo::TimeParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    weight_response_function( new MonteCarlo::WeightParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    source_energy_response_function( new MonteCarlo::SourceEnergyParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    source_time_response_function( new MonteCarlo::SourceTimeParticleResponseFunction( response_distribution ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    source_weight_response_function( new MonteCarlo::SourceWeightParticleResponseFunction( response_distribution ) );

  MonteCarlo::PhotonState photon( 1ull );
  photon.setPosition( 1.0, 2.0, 3.0 );
  photon.setDirection( 0.2672612419124244, 0.5345224838248488, 0.8017837257372732 );
  photon.setEnergy( 10.0 );
  photon.setSourceEnergy( 10.1 );
  photon.setTime( 5.0 );
  photon.setSourceTime( 5.1 );
  photon.setWeight( 0.5 );
  photon.setSourceWeight( 0.51 );

  FRENSIE_CHECK_FLOATING_EQUALITY( x_response_function->evaluate( photon ),
                                   0.36787944117144233,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( y_response_function->evaluate( photon ),
                                   0.1353352832366127,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( z_response_function->evaluate( photon ),
                                   0.049787068367863944,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( u_response_function->evaluate( photon ),
                                   0.7654730716931915,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( v_response_function->evaluate( photon ),
                                   0.5859490234874097,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( w_response_function->evaluate( photon ),
                                   0.4485281988645335,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy_response_function->evaluate( photon ),
                                   4.5399929762484854e-05,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( time_response_function->evaluate( photon ),
                                   0.006737946999085467,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( weight_response_function->evaluate( photon ),
                                   0.6065306597126334,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( source_energy_response_function->evaluate( photon ),
                                   4.1079555225300724e-05,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( source_time_response_function->evaluate( photon ),
                                   0.006096746565515638,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( source_weight_response_function->evaluate( photon ),
                                   0.6004955788122659,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the response function can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SinglePhaseSpaceDimensionParticleResponseFunction,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_single_phase_dimension_particle_response_function" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const Utility::UnivariateDistribution> response_distribution(
                           new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      x_response_function( new MonteCarlo::XPositionParticleResponseFunction( response_distribution ) );
    
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      y_response_function( new MonteCarlo::YPositionParticleResponseFunction( response_distribution ) );
    
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      z_response_function( new MonteCarlo::ZPositionParticleResponseFunction( response_distribution ) );
    
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      u_response_function( new MonteCarlo::XDirectionParticleResponseFunction( response_distribution ) );
    
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      v_response_function( new MonteCarlo::YDirectionParticleResponseFunction( response_distribution ) );
    
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      w_response_function( new MonteCarlo::ZDirectionParticleResponseFunction( response_distribution ) );
    
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      energy_response_function( new MonteCarlo::EnergyParticleResponseFunction( response_distribution ) );
    
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      time_response_function( new MonteCarlo::TimeParticleResponseFunction( response_distribution ) );
    
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      weight_response_function( new MonteCarlo::WeightParticleResponseFunction( response_distribution ) );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      source_energy_response_function( new MonteCarlo::SourceEnergyParticleResponseFunction( response_distribution ) );
    
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      source_time_response_function( new MonteCarlo::SourceTimeParticleResponseFunction( response_distribution ) );
    
    std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
      source_weight_response_function( new MonteCarlo::SourceWeightParticleResponseFunction( response_distribution ) );
  
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( x_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( y_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( z_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( u_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( v_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( w_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( energy_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( time_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( weight_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( source_energy_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( source_time_response_function ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( source_weight_response_function ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction>
    x_response_function, y_response_function, z_response_function,
    u_response_function, v_response_function, w_response_function,
    energy_response_function, time_response_function, weight_response_function,
    source_energy_response_function, source_time_response_function,
    source_weight_response_function;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( x_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( y_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( z_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( u_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( v_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( w_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( energy_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( time_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( weight_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( source_energy_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( source_time_response_function ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( source_weight_response_function ) );

  iarchive.reset();

  MonteCarlo::PhotonState photon( 1ull );
  photon.setPosition( 1.0, 2.0, 3.0 );
  photon.setDirection( 0.2672612419124244, 0.5345224838248488, 0.8017837257372732 );
  photon.setSourceEnergy( 10.1 );
  photon.setEnergy( 10.0 );
  photon.setSourceTime( 5.1 );
  photon.setTime( 5.0 );
  photon.setSourceWeight( 0.51 );
  photon.setWeight( 0.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( x_response_function->evaluate( photon ),
                                   0.36787944117144233,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( y_response_function->evaluate( photon ),
                                   0.1353352832366127,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( z_response_function->evaluate( photon ),
                                   0.049787068367863944,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( u_response_function->evaluate( photon ),
                                   0.7654730716931915,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( v_response_function->evaluate( photon ),
                                   0.5859490234874097,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( w_response_function->evaluate( photon ),
                                   0.4485281988645335,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy_response_function->evaluate( photon ),
                                   4.5399929762484854e-05,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( time_response_function->evaluate( photon ),
                                   0.006737946999085467,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( weight_response_function->evaluate( photon ),
                                   0.6065306597126334,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( source_energy_response_function->evaluate( photon ),
                                   4.1079555225300724e-05,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( source_time_response_function->evaluate( photon ),
                                   0.006096746565515638,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( source_weight_response_function->evaluate( photon ),
                                   0.6004955788122659,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// end tstSinglePhaseSpaceDimensionParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
