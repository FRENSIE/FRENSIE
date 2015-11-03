//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleModeType.hpp
//! \author Alex Robinson
//! \brief  Particle mode type enum and helper function delcarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_MODE_TYPE_HPP
#define MONTE_CARLO_PARTICLE_MODE_TYPE_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"

namespace MonteCarlo{

//! The particle transport mode enumeration
enum ParticleModeType
{
  NEUTRON_MODE = 0,
  PHOTON_MODE,
  ELECTRON_MODE,
  NEUTRON_PHOTON_MODE,
  PHOTON_ELECTRON_MODE,
  NEUTRON_PHOTON_ELECTRON_MODE,
  ADJOINT_NEUTRON_MODE,
  ADJOINT_PHOTON_MODE,
  ADJOINT_ELECTRON_MODE
};

//! Test if the particle mode type name is valid
bool isValidParticleModeTypeName( const std::string& particle_mode_type_name );

//! Test if the source particle type is compatible with the particle mode type
bool isParticleModeTypeCompatible( const ParticleModeType particle_mode,
				   const ParticleType particle_type );

//! Convert the particle mode type name to a ParticleModeType enum
ParticleModeType convertParticleModeTypeNameToParticleModeTypeEnum(
				  const std::string& particle_mode_type_name );

//! Convert the unsigned to a ParticleModeType enum
ParticleModeType convertUnsignedToParticleModeTypeEnum(
					   const unsigned particle_mode_type );

//! Convert a ParticleModeType enumeration to a string
std::string convertParticleModeTypeEnumToString(
					const ParticleModeType particle_mode );

//! Stream operator for printing ParticleModeType enums
inline std::ostream& operator<<( std::ostream& os,
				 const ParticleModeType particle_mode )
{
  os << convertParticleModeTypeEnumToString( particle_mode );
  return os;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_MODE_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleModeType.hpp
//---------------------------------------------------------------------------//
