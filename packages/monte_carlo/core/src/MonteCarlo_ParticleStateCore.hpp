//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_ParticleStateCore.hpp
//! \author Alex Robinson
//! \brief  Particle state core struct declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_STATE_CORE_HPP
#define FACEMC_PARTICLE_STATE_CORE_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "Utility_HDF5TypeTraits.hpp"

namespace MonteCarlo{

//! The particle state core struct
struct ParticleStateCore
{
  //! Typedef for history number type
  typedef unsigned long long historyNumberType;

  //! Typedef for position type
  typedef double positionType;

  //! Typedef for direction type
  typedef double directionType;
  
  //! Typedef for energy type
  typedef double energyType;

  //! Typedef for time type
  typedef double timeType;

  //! Typedef for collision number type;
  typedef unsigned collisionNumberType;

  //! Typedef for generation number type
  typedef unsigned generationNumberType;
  
  //! Typedef for weight type
  typedef double weightType;

  //! Default Constructor
  ParticleStateCore();

  //! Constructor
  ParticleStateCore( const historyNumberType history_number,
		     const ParticleType particle_type,
		     const positionType x_position,
		     const positionType y_position,
		     const positionType z_position,
		     const directionType x_direction,
		     const directionType y_direction,
		     const directionType z_direction,
		     const energyType energy,
		     const timeType time,
		     const collisionNumberType collision_number,
		     const generationNumberType generation_number,
		     const weightType weight );

  // The history number
  historyNumberType history_number;

  // The particle type
  ParticleType particle_type;

  // Position of the particle
  positionType x_position;
  positionType y_position;
  positionType z_position;

  // Direction of the particle
  directionType x_direction;
  directionType y_direction;
  directionType z_direction;
  
  // Energy of the particle (MeV)
  energyType energy;

  // Time of the particle (s)
  timeType time;

  // Collision number of the particle
  collisionNumberType collision_number;

  // The generation number of the particle
  generationNumberType generation_number;

  // The weight of the particle
  weightType weight;
};

} // end MonteCarlo namespace

namespace Utility{

/*! The specialization of the MonteCarlo::HDF5TypeTraits for the 
 * MonteCarlo::ParticleStateCore struct
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<MonteCarlo::ParticleStateCore>
{
  //! Returns the HDF5 data type object corresponding to the ParticleStateCore
  static inline H5::CompType dataType()
  {
    H5::CompType memtype( sizeof(MonteCarlo::ParticleStateCore) );

    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {
      memtype.insertMember( "history_number",
			    HOFFSET( MonteCarlo::ParticleStateCore, history_number ),
			    HDF5TypeTraits<MonteCarlo::ParticleStateCore::historyNumberType>::dataType() );
      
      memtype.insertMember( "particle_type",
			    HOFFSET( MonteCarlo::ParticleStateCore, particle_type ),
			    HDF5TypeTraits<MonteCarlo::ParticleType>::dataType() );
      
      memtype.insertMember( "x_position",
			    HOFFSET( MonteCarlo::ParticleStateCore, x_position ),
			    HDF5TypeTraits<MonteCarlo::ParticleStateCore::positionType>::dataType() );
      
      memtype.insertMember( "y_position",
			    HOFFSET( MonteCarlo::ParticleStateCore, y_position ),
			    HDF5TypeTraits<MonteCarlo::ParticleStateCore::positionType>::dataType() );
      
      memtype.insertMember( "z_position",
			    HOFFSET( MonteCarlo::ParticleStateCore, z_position ),
			    HDF5TypeTraits<MonteCarlo::ParticleStateCore::positionType>::dataType() );
      
    memtype.insertMember( "x_direction",
			  HOFFSET( MonteCarlo::ParticleStateCore, x_direction ),
			  HDF5TypeTraits<MonteCarlo::ParticleStateCore::directionType>::dataType() );
    
    memtype.insertMember( "y_direction",
			  HOFFSET( MonteCarlo::ParticleStateCore, y_direction ),
			  HDF5TypeTraits<MonteCarlo::ParticleStateCore::directionType>::dataType() );
    
    memtype.insertMember( "z_direction",
			  HOFFSET( MonteCarlo::ParticleStateCore, z_direction ),
			  HDF5TypeTraits<MonteCarlo::ParticleStateCore::directionType>::dataType() );
    
    memtype.insertMember( "energy",
			  HOFFSET( MonteCarlo::ParticleStateCore, energy ),
			  HDF5TypeTraits<MonteCarlo::ParticleStateCore::energyType>::dataType() );
    
    memtype.insertMember( "time",
			  HOFFSET( MonteCarlo::ParticleStateCore, time ),
			  HDF5TypeTraits<MonteCarlo::ParticleStateCore::timeType>::dataType() );
    
    memtype.insertMember( "collision_number",
			  HOFFSET( MonteCarlo::ParticleStateCore, collision_number ),
			  HDF5TypeTraits<MonteCarlo::ParticleStateCore::collisionNumberType>::dataType() );
    
    memtype.insertMember( "generation_number",
			  HOFFSET( MonteCarlo::ParticleStateCore, generation_number ),
			  HDF5TypeTraits<MonteCarlo::ParticleStateCore::generationNumberType>::dataType() );
    
    memtype.insertMember( "weight",
			  HOFFSET( MonteCarlo::ParticleStateCore, weight ),
			  HDF5TypeTraits<MonteCarlo::ParticleStateCore::weightType>::dataType() );
    }
    
    HDF5_EXCEPTION_CATCH_AND_EXIT();
    
    return memtype;
  }

  //! Returns the name of this type
  static inline std::string name()
  {
    return "ParticleStateCore";
  }

  //! Returns the zero value for this type
  static inline MonteCarlo::ParticleStateCore zero()
  {
    return MonteCarlo::ParticleStateCore();
  }

  //! Returns the unity value for this type
  static inline MonteCarlo::ParticleStateCore one()
  {
    return MonteCarlo::ParticleStateCore();
  }
};

} // end Utility namespace

#endif // end FACEMC_PARTICLE_STATE_CORE_HPP

//---------------------------------------------------------------------------//
// MonteCarlo_ParticleStateCore.hpp
//---------------------------------------------------------------------------//
