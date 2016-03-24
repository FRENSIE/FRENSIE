//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleType.cpp
//! \author Alex Robinson
//! \brief  Particle type enumeration and helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Test if the particle type name is valid
bool isValidParticleTypeName( const std::string& particle_type_name )
{
  return particle_type_name.compare( "Photon" ) == 0 ||
    particle_type_name.compare( "Neutron" ) == 0 ||
    particle_type_name.compare( "Electron" ) == 0 ||
    particle_type_name.compare( "Adjoint Photon" ) == 0 ||
    particle_type_name.compare( "Adjoint Neutron" ) == 0 ||
    particle_type_name.compare( "Adjoint Electron" ) == 0;
}

// Convert shorthand particle type name to verbose particle type name
/*! \details These shorthand names should correspond to the names that would
 * be encountered in DagMC.
 */
std::string convertShortParticleTypeNameToVerboseParticleTypeName(
				 const std::string& short_particle_type_name )
{
  if( short_particle_type_name == "n" )
    return "Neutron";
  else if( short_particle_type_name == "p" )
    return "Photon";
  else if( short_particle_type_name == "e" )
    return "Electron";
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the short particle type name ("
                     << short_particle_type_name << ") is not valid!" );
  }
}

// Convert the particle type name to a ParticleType enum
ParticleType convertParticleTypeNameToParticleTypeEnum(
					const std::string& particle_type_name )
{
  if( particle_type_name.compare( "Photon" ) == 0 )
    return PHOTON;
  else if( particle_type_name.compare( "Neutron" ) == 0 )
    return NEUTRON;
  else if( particle_type_name.compare( "Electron" ) == 0 )
    return ELECTRON;
  else if( particle_type_name.compare( "Adjoint Photon" ) == 0 )
    return ADJOINT_PHOTON;
  else if( particle_type_name.compare( "Adjoint Neutron" ) == 0 )
    return ADJOINT_NEUTRON;
  else if( particle_type_name.compare( "Adjoint Electron" ) == 0 )
    return ADJOINT_ELECTRON;
  else
    return UNKNOWN_PARTICLE;
}

// Convert the ParticleType enum to a string
std::string convertParticleTypeEnumToString( const ParticleType particle_type )
{
  switch( particle_type )
  {
  case PHOTON: return "Photon";
  case NEUTRON: return "Neutron";
  case ELECTRON: return "Electron";
  case ADJOINT_PHOTON: return "Adjoint Photon";
  case ADJOINT_NEUTRON: return "Adjoint Neutron";
  case ADJOINT_ELECTRON: return "Adjoint Electron";
  default:
    return "Unknown Particle";
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleType.cpp
//---------------------------------------------------------------------------//
