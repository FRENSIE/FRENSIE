//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleType.cpp
//! \author Alex Robinson
//! \brief  Particle type enumeration and helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
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
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Particle type name " << particle_type_name << " is not "
                     "supported!" );
  }
}

// Convert the geometry particle type enum to a ParticleType enum
ParticleType convertGeometryParticleTypeEnumToParticleTypeEnum(
                                   const Geometry::ParticleType particle_type )
{
  switch( particle_type )
  {
  case Geometry::PHOTON: return PHOTON;
  case Geometry::NEUTRON: return NEUTRON;
  case Geometry::ELECTRON: return ELECTRON;
  case Geometry::ADJOINT_PHOTON: return ADJOINT_PHOTON;
  case Geometry::ADJOINT_NEUTRON: return ADJOINT_NEUTRON;
  case Geometry::ADJOINT_ELECTRON: return ADJOINT_ELECTRON;
  default:
    THROW_EXCEPTION( std::logic_error,
                     "The geometry particle type " << particle_type <<
                     " is not supported!" );
  }
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
    THROW_EXCEPTION( std::logic_error,
                     "The particle type " << (int)particle_type << " is not "
                     "supported!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleType.cpp
//---------------------------------------------------------------------------//
