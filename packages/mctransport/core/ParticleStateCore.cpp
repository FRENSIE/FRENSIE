//---------------------------------------------------------------------------//
//!
//! \file   ParticleStateCore.cpp
//! \author Alex Robinson
//! \brief  Particle state core struct definition
//!
//---------------------------------------------------------------------------//

// // HDF5 Includes
#include <H5Cpp.h>

// FACEMC Includes
#include "ParticleStateCore.hpp"
#include "HDF5TypeTraits.hpp"
#include "ExceptionCatchMacros.hpp"

namespace FACEMC{

// Create an HDF5 type that represents the FACEMC::ParticleStateCore struct
H5::CompType ParticleStateCore::createHDF5DataType()
{
  H5::CompType memtype( sizeof(ParticleStateCore) );

  // the insertMember function can throw H5::DataTypeIException exceptions
  try
  {
    memtype.insertMember( "history_number",
			  HOFFSET( ParticleStateCore, history_number ),
                          Traits::HDF5TypeTraits<ParticleStateCore::historyNumberType>::dataType() );

    memtype.insertMember( "particle_type",
			  HOFFSET( ParticleStateCore, particle_type ),
			  Traits::HDF5TypeTraits<ParticleType>::dataType() );

    memtype.insertMember( "x_position",
			  HOFFSET( ParticleStateCore, x_position ),
			  Traits::HDF5TypeTraits<ParticleStateCore::positionType>::dataType() );

    memtype.insertMember( "y_position",
			  HOFFSET( ParticleStateCore, y_position ),
			  Traits::HDF5TypeTraits<ParticleStateCore::positionType>::dataType() );

    memtype.insertMember( "z_position",
			  HOFFSET( ParticleStateCore, z_position ),
			  Traits::HDF5TypeTraits<ParticleStateCore::positionType>::dataType() );

    memtype.insertMember( "x_direction",
			  HOFFSET( ParticleStateCore, x_direction ),
			  Traits::HDF5TypeTraits<ParticleStateCore::directionType>::dataType() );
    
    memtype.insertMember( "y_direction",
			  HOFFSET( ParticleStateCore, y_direction ),
			  Traits::HDF5TypeTraits<ParticleStateCore::directionType>::dataType() );
    
    memtype.insertMember( "z_direction",
			  HOFFSET( ParticleStateCore, z_direction ),
			  Traits::HDF5TypeTraits<ParticleStateCore::directionType>::dataType() );

    memtype.insertMember( "energy",
			  HOFFSET( ParticleStateCore, energy ),
			  Traits::HDF5TypeTraits<ParticleStateCore::energyType>::dataType() );

    memtype.insertMember( "time",
			  HOFFSET( ParticleStateCore, time ),
			  Traits::HDF5TypeTraits<ParticleStateCore::timeType>::dataType() );

    memtype.insertMember( "collision_number",
			  HOFFSET( ParticleStateCore, collision_number ),
			  Traits::HDF5TypeTraits<ParticleStateCore::collisionNumberType>::dataType() );

    memtype.insertMember( "generation_number",
			  HOFFSET( ParticleStateCore, generation_number ),
			  Traits::HDF5TypeTraits<ParticleStateCore::generationNumberType>::dataType() );

    memtype.insertMember( "weight",
			  HOFFSET( ParticleStateCore, weight ),
			  Traits::HDF5TypeTraits<ParticleStateCore::weightType>::dataType() );
  }

  HDF5_EXCEPTION_CATCH_AND_EXIT();

  return memtype;
}

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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end ParticleStateCore.cpp
//---------------------------------------------------------------------------//
