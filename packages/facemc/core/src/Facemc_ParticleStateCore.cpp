//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleStateCore.cpp
//! \author Alex Robinson
//! \brief  Particle state core struct definition
//!
//---------------------------------------------------------------------------//

// // HDF5 Includes
#include <H5Cpp.h>

// FRENSIE Includes
#include "Facemc_ParticleStateCore.hpp"
#include "Utility_HDF5TypeTraits.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Facemc{

// Constructor
ParticleStateCore::ParticleStateCore( 
	       const ParticleStateCore::historyNumberType history_number,
	       const ParticleType particle_type,
	       const ParticleStateCore::positionType x_position,
	       const ParticleStateCore::positionType y_position,
	       const ParticleStateCore::positionType z_position,
	       const ParticleStateCore::directionType x_direction,
	       const ParticleStateCore::directionType y_direction,
	       const ParticleStateCore::directionType z_direction,
	       const ParticleStateCore::energyType energy,
	       const ParticleStateCore::timeType time,
	       const ParticleStateCore::collisionNumberType collision_number,
	       const ParticleStateCore::generationNumberType generation_number,
	       const ParticleStateCore::weightType weight )
  : history_number( history_number ),
    particle_type( particle_type ),
    x_position( x_position ),
    y_position( y_position ),
    z_position( z_position ),
    x_direction( x_direction ),
    y_direction( y_direction ),
    z_direction( z_direction ),
    energy( energy ),
    time( time ),
    collision_number( collision_number ),
    generation_number( generation_number ),
    weight( weight )
{ /* ... */ }

// Default Constructor
ParticleStateCore::ParticleStateCore()
  : history_number( 0 ),
    particle_type( PHOTON ),
    x_position( 0.0 ),
    y_position( 0.0 ),
    z_position( 0.0 ),
    x_direction( 0.0 ),
    y_direction( 0.0 ),
    z_direction( 0.0 ),
    energy( 0.0 ),
    time( 0.0 ),
    collision_number( 0u ),
    generation_number( 0u ),
    weight( 0.0 )
{ /* ... */ }

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleStateCore.cpp
//---------------------------------------------------------------------------//
