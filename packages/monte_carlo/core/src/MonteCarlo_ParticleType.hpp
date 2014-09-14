//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleType.hpp
//! \author Alex Robinson
//! \brief  Particle type enumeration and helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_TYPE_HPP
#define FACEMC_PARTICLE_TYPE_HPP

// HDF5 Includes
#include <H5Cpp.h>

// FRENSIE Includes
#include "Utility_HDF5TypeTraits.hpp"

namespace MonteCarlo{

enum ParticleType{
  PHOTON = 0,
  NEUTRON,
  ADJOINT_PHOTON,
  ADJOINT_NEUTRON,
  UNKNOWN_PARTICLE
};

//! Test if the particle type name is valid
bool isValidParticleTypeName( const std::string& particle_type_name );

//! Convert the particle type name to a ParticleType enum
ParticleType convertParticleTypeNameToParticleTypeEnum( 
				       const std::string& particle_type_name );

} // end MonteCarlo namespace

namespace Utility{

/*! The specialization of the MonteCarlo::HDF5TypeTraits for the 
 * MonteCarlo::ParticleStateCore struct
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<MonteCarlo::ParticleType>
{
  static inline H5::EnumType dataType()
  {
    H5::EnumType hdf5_particle_type( sizeof(short) );

    short particle_type = 0;
    
    hdf5_particle_type.insert( "PHOTON", &particle_type );
    
    particle_type = 1;
    
    hdf5_particle_type.insert( "NEUTRON", &particle_type );
    
    particle_type = 2;
    
    hdf5_particle_type.insert( "ADJOINT_PHOTON", &particle_type );
    
    particle_type = 3;
    
    hdf5_particle_type.insert( "ADJOINT_NEUTRON", &particle_type );
    
    return hdf5_particle_type;
  }

  static inline std::string name()
  {
    return "ParticleType";
  }

  //! Returns the zero value for this type
  static inline MonteCarlo::ParticleType zero()
  {
    return MonteCarlo::PHOTON;
  }

  //! Returns the unity value for this type
  static inline MonteCarlo::ParticleType one()
  {
    return MonteCarlo::NEUTRON;
  }
};

} // end Utility namespace

#endif // end FACEMC_PARTICLE_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleType.hpp
//---------------------------------------------------------------------------//
