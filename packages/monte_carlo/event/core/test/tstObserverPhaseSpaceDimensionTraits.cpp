//---------------------------------------------------------------------------//
//!
//! \file   tstObserverPhaseSpaceDimensionTraits.cpp
//! \author Alex Robinson
//! \brief  Observer phase space dimension traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check if the dimension is ordered
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimensionTraits, isOrdered )
{
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_COSINE_DIMENSION>::isOrdered::value );
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ENERGY_DIMENSION>::isOrdered::value );
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_ENERGY_DIMENSION>::isOrdered::value );
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_TIME_DIMENSION>::isOrdered::value );
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_TIME_DIMENSION>::isOrdered::value );
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_COLLISION_NUMBER_DIMENSION>::isOrdered::value );
  FRENSIE_CHECK( !ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ID_DIMENSION>::isOrdered::value );
}

//---------------------------------------------------------------------------//
// Check if the dimension is continuous or discrete
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimensionTraits, isContinuous )
{
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_COSINE_DIMENSION>::isContinuous::value );
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ENERGY_DIMENSION>::isContinuous::value );
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_ENERGY_DIMENSION>::isContinuous::value );
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_TIME_DIMENSION>::isContinuous::value );
  FRENSIE_CHECK( ObserverPhaseSpaceDimensionTraits<OBSERVER_TIME_DIMENSION>::isContinuous::value );
  FRENSIE_CHECK( !ObserverPhaseSpaceDimensionTraits<OBSERVER_COLLISION_NUMBER_DIMENSION>::isContinuous::value );
  FRENSIE_CHECK( !ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ID_DIMENSION>::isContinuous::value );
}

//---------------------------------------------------------------------------//
// Check that the name can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimensionTraits, name )
{
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_COSINE_DIMENSION>::name(), "Cosine" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ENERGY_DIMENSION>::name(), "Source Energy" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_ENERGY_DIMENSION>::name(), "Energy" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_TIME_DIMENSION>::name(), "Source Time" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_TIME_DIMENSION>::name(), "Time" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_COLLISION_NUMBER_DIMENSION>::name(), "Collision Number" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ID_DIMENSION>::name(), "Source Id" );
}

//---------------------------------------------------------------------------//
// Check that the basic name can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimensionTraits, basicName )
{
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_COSINE_DIMENSION>::basicName(), "Cosine" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ENERGY_DIMENSION>::basicName(), "Source_Energy" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_ENERGY_DIMENSION>::basicName(), "Energy" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_TIME_DIMENSION>::basicName(), "Source_Time" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_TIME_DIMENSION>::basicName(), "Time" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_COLLISION_NUMBER_DIMENSION>::basicName(), "Collision_Number" );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ID_DIMENSION>::basicName(), "Source_Id" );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the dimension can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimensionTraits, lowerBound )
{
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_COSINE_DIMENSION>::lowerBound(), -1.0 );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ENERGY_DIMENSION>::lowerBound(), 0.0 );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_ENERGY_DIMENSION>::lowerBound(), 0.0 );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_TIME_DIMENSION>::lowerBound(), 0.0 );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_TIME_DIMENSION>::lowerBound(), 0.0 );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_COLLISION_NUMBER_DIMENSION>::lowerBound(), 0u );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ID_DIMENSION>::lowerBound(), 0u );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the dimension can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimensionTraits, upperBound )
{
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_COSINE_DIMENSION>::upperBound(), 1.0 );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ENERGY_DIMENSION>::upperBound(), std::numeric_limits<double>::infinity() );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_ENERGY_DIMENSION>::upperBound(), std::numeric_limits<double>::infinity() );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_TIME_DIMENSION>::upperBound(), std::numeric_limits<double>::infinity() );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_TIME_DIMENSION>::upperBound(), std::numeric_limits<double>::infinity() );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_COLLISION_NUMBER_DIMENSION>::upperBound(), std::numeric_limits<ParticleState::collisionNumberType>::max() );
  FRENSIE_CHECK_EQUAL( ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ID_DIMENSION>::upperBound(), std::numeric_limits<ParticleState::sourceIdType>::max() );
}

//---------------------------------------------------------------------------//
// Check that the dimension value can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimensionTraits,
                   getDimensionValue_wrapper )
{
  MonteCarlo::PhotonState photon( 0ull );
  photon.setSourceId( 2u );
  photon.setSourceEnergy( 10.0 );
  photon.setEnergy( 1.0 );
  photon.setSourceTime( 0.0 );
  photon.setTime( 0.1 );

  MonteCarlo::ObserverParticleStateWrapper particle_wrapper( photon );
  particle_wrapper.setAngleCosine( -0.5 );
  
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_COSINE_DIMENSION>( particle_wrapper ), -0.5 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_SOURCE_ENERGY_DIMENSION>( particle_wrapper ), 10.0 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_ENERGY_DIMENSION>( particle_wrapper ), 1.0 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_SOURCE_TIME_DIMENSION>( particle_wrapper ), 0.0 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_TIME_DIMENSION>( particle_wrapper ), 0.1 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_COLLISION_NUMBER_DIMENSION>( particle_wrapper ), 0u );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_SOURCE_ID_DIMENSION>( particle_wrapper ), 2u );
}

//---------------------------------------------------------------------------//
// Check that the dimension value can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimensionTraits,
                   getDimensionValue_any )
{
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_COSINE_DIMENSION>( boost::any( -0.5 ) ), -0.5 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_SOURCE_ENERGY_DIMENSION>( boost::any( 10.0 ) ), 10.0 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_ENERGY_DIMENSION>( boost::any( 1.0 ) ), 1.0 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_SOURCE_TIME_DIMENSION>( boost::any( 0.0 ) ), 0.0 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_TIME_DIMENSION>( boost::any( 0.1 ) ), 0.1 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_COLLISION_NUMBER_DIMENSION>( boost::any( (ParticleState::collisionNumberType)0 ) ), 0u );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getDimensionValue<OBSERVER_SOURCE_ID_DIMENSION>( boost::any( (ParticleState::sourceIdType)2 ) ), 2u );
}

//---------------------------------------------------------------------------//
// Check that the dimension range can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimensionTraits, getDimensionRange )
{
  MonteCarlo::PhotonState photon( 0ull );
  photon.setSourceId( 2u );
  photon.setSourceEnergy( 10.0 );
  photon.setEnergy( 1.0 );
  photon.setSourceTime( 0.0 );
  photon.setTime( 0.1 );

  MonteCarlo::ObserverParticleStateWrapper particle_wrapper( photon );
  particle_wrapper.setAngleCosine( -0.5 );
  particle_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( 1.0 );

  {
    double cosine_range_start, cosine_range_end;

    MonteCarlo::getDimensionRange<OBSERVER_COSINE_DIMENSION>( particle_wrapper,
                                                              cosine_range_start,
                                                              cosine_range_end );

    FRENSIE_CHECK_EQUAL( cosine_range_start, -0.5 );
    FRENSIE_CHECK_EQUAL( cosine_range_end, -0.5 );
  }

  {
    double source_energy_range_start, source_energy_range_end;

    MonteCarlo::getDimensionRange<OBSERVER_SOURCE_ENERGY_DIMENSION>(
                                                     particle_wrapper,
                                                     source_energy_range_start,
                                                     source_energy_range_end );

    FRENSIE_CHECK_EQUAL( source_energy_range_start, 10.0 );
    FRENSIE_CHECK_EQUAL( source_energy_range_end, 10.0 );
  }

  {
    double energy_range_start, energy_range_end;

    MonteCarlo::getDimensionRange<OBSERVER_ENERGY_DIMENSION>(
                                                     particle_wrapper,
                                                     energy_range_start,
                                                     energy_range_end );

    FRENSIE_CHECK_EQUAL( energy_range_start, 1.0 );
    FRENSIE_CHECK_EQUAL( energy_range_end, 1.0 );
  }

  {
    double source_time_range_start, source_time_range_end;

    MonteCarlo::getDimensionRange<OBSERVER_SOURCE_TIME_DIMENSION>(
                                                     particle_wrapper,
                                                     source_time_range_start,
                                                     source_time_range_end );

    FRENSIE_CHECK_EQUAL( source_time_range_start, 0.0 );
    FRENSIE_CHECK_EQUAL( source_time_range_end, 0.0 );
  }

  {
    double time_range_start, time_range_end;

    MonteCarlo::getDimensionRange<OBSERVER_TIME_DIMENSION>(
                                                     particle_wrapper,
                                                     time_range_start,
                                                     time_range_end );

    FRENSIE_CHECK_FLOATING_EQUALITY( time_range_start,
                                     0.09999999996664359,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( time_range_end, 0.1 );
  }

  {
    MonteCarlo::ParticleState::collisionNumberType collision_number_range_start, collision_number_range_end;

    MonteCarlo::getDimensionRange<OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                  particle_wrapper,
                                                  collision_number_range_start,
                                                  collision_number_range_end );
    
    FRENSIE_CHECK_EQUAL( collision_number_range_start, 0u );
    FRENSIE_CHECK_EQUAL( collision_number_range_end, 0u );
  }

  {
    MonteCarlo::ParticleState::sourceIdType source_id_range_start, source_id_range_end;

    MonteCarlo::getDimensionRange<OBSERVER_SOURCE_ID_DIMENSION>(
                                                  particle_wrapper,
                                                  source_id_range_start,
                                                  source_id_range_end );
    
    FRENSIE_CHECK_EQUAL( source_id_range_start, 2u );
    FRENSIE_CHECK_EQUAL( source_id_range_end, 2u );
  }
}

//---------------------------------------------------------------------------//
// end tstObserverPhaseSpaceDimensionTraits.cpp
//---------------------------------------------------------------------------//
