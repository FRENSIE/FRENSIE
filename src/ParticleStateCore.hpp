//---------------------------------------------------------------------------//
//! 
//! \file   ParticleStateCore.hpp
//! \author Alex Robinson
//! \brief  Particle state core struct declaration
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_STATE_CORE_HPP
#define PARTICLE_STATE_CORE_HPP

// FACEMC Includes
#include "ParticleType.hpp"
#include "HDF5TypeTraits.hpp"

namespace FACEMC{

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
  
  //! Create an HDF5 data type for HDF5 file export
  static H5::CompType createHDF5DataType();

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

namespace Traits{

/*! The specialization of the FACEMC::HDF5TypeTraits for the 
 * FACEMC::ParticleStateCore struct
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<ParticleStateCore>
{
  //! Returns the HDF5 data type object corresponding to the ParticleStateCore
  static inline H5::CompType dataType()
  {
    return ParticleStateCore::createHDF5DataType();
  }

  //! Returns the name of this type
  static inline std::string name()
  {
    return "ParticleStateCore";
  }

  //! Returns the zero value for this type
  static inline ParticleStateCore zero()
  {
    return ParticleStateCore();
  }

  //! Returns the unity value for this type
  static inline ParticleStateCore one()
  {
    return ParticleStateCore();
  }
};

} // end Traits namespace

} // end FACEMC namespace

#endif // end PARTICLE_STATE_CORE_HPP

//---------------------------------------------------------------------------//
// ParticleStateCore.hpp
//---------------------------------------------------------------------------//
