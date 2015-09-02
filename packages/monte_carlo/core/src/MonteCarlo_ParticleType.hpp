//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleType.hpp
//! \author Alex Robinson
//! \brief  Particle type enumeration and helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_TYPE_HPP
#define MONTE_CARLO_PARTICLE_TYPE_HPP

// HDF5 Includes
#include <H5Cpp.h>

// FRENSIE Includes
#include "Utility_HDF5TypeTraits.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

enum ParticleType{
  PHOTON = 0,
  NEUTRON,
  ELECTRON,
  ADJOINT_PHOTON,
  ADJOINT_PHOTON_PROBE,
  ADJOINT_NEUTRON,
  ADJOINT_NEUTRON_PROBE,
  ADJOINT_ELECTRON,
  ADJOINT_ELECTRON_PROBE,
  UNKNOWN_PARTICLE,
  PARTICLE_end
};

//! Test if the particle type name is valid
bool isValidParticleTypeName( const std::string& particle_type_name );

//! Convert shorthand particle type name to verbose particle type name
std::string convertShortParticleTypeNameToVerboseParticleTypeName(
				 const std::string& short_particle_type_name );

//! Convert the particle type name to a ParticleType enum
ParticleType convertParticleTypeNameToParticleTypeEnum( 
				       const std::string& particle_type_name );

//! Convert the ParticleType enum to a string
std::string convertParticleTypeEnumToString( const ParticleType particle_type);

//! Stream operator for print ParticleType enums
inline std::ostream& operator<<( std::ostream& os,
				 const ParticleType particle_type )
{
  os << convertParticleTypeEnumToString( particle_type );
  return os;
}

} // end MonteCarlo namespace

namespace Utility{

/*! The specialization of the Utility::HDF5TypeTraits for the 
 * MonteCarlo::ParticleStateCore struct
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<MonteCarlo::ParticleType>
{
  static inline H5::EnumType dataType()
  {
    H5::EnumType hdf5_particle_type( sizeof( MonteCarlo::ParticleType ) );

    MonteCarlo::ParticleType particle_type = MonteCarlo::PHOTON;
    
    hdf5_particle_type.insert( "PHOTON", &particle_type );
    
    particle_type = MonteCarlo::NEUTRON;
    
    hdf5_particle_type.insert( "NEUTRON", &particle_type );
    
    particle_type = MonteCarlo::ELECTRON;
    
    hdf5_particle_type.insert( "ELECTRON", &particle_type );
    
    particle_type = MonteCarlo::ADJOINT_PHOTON;

    hdf5_particle_type.insert( "ADJOINT_PHOTON", &particle_type );
    
    particle_type = MonteCarlo::ADJOINT_NEUTRON;
    
    hdf5_particle_type.insert( "ADJOINT_NEUTRON", &particle_type );

    particle_type = MonteCarlo::ADJOINT_ELECTRON;
    
    hdf5_particle_type.insert( "ADJOINT_ELECTRON", &particle_type );
    
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

#endif // end MONTE_CARLO_PARTICLE_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleType.hpp
//---------------------------------------------------------------------------//
