//---------------------------------------------------------------------------//
//!
//! \file   ParticleType.hpp
//! \author Alex Robinson
//! \brief  Particle type enumeration
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_TYPE_HPP
#define PARTICLE_TYPE_HPP

// HDF5 Includes
#include <H5Cpp.h>

// FACEMC Includes
#include "HDF5TypeTraits.hpp"

namespace FACEMC{

enum ParticleType{
  PHOTON = 0,
  NEUTRON,
  ADJOINT_PHOTON,
  ADJOINT_NEUTRON
};

namespace Traits{

/*! The specialization of the FACEMC::HDF5TypeTraits for the 
 * FACEMC::ParticleStateCore struct
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<ParticleType>
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
  static inline ParticleType zero()
  {
    return PHOTON;
  }

  //! Returns the unity value for this type
  static inline ParticleType one()
  {
    return NEUTRON;
  }
};

} // end Traits namespace

} // end FACEMC namespace

#endif // end PARTICLE_TYPE_HPP

//---------------------------------------------------------------------------//
// end ParticleType.hpp
//---------------------------------------------------------------------------//
