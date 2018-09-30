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
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Convert the geometry particle type enum to a ParticleType enum
ParticleType convertGeometryParticleTypeEnumToParticleTypeEnum(
                                   const Geometry::ParticleType particle_type )
{
  switch( particle_type )
  {
    case Geometry::PHOTON: return PHOTON;
    case Geometry::NEUTRON: return NEUTRON;
    case Geometry::ELECTRON: return ELECTRON;
    case Geometry::POSITRON: return POSITRON;
    case Geometry::ADJOINT_PHOTON: return ADJOINT_PHOTON;
    case Geometry::ADJOINT_NEUTRON: return ADJOINT_NEUTRON;
    case Geometry::ADJOINT_ELECTRON: return ADJOINT_ELECTRON;
    case Geometry::ADJOINT_POSITRON: return ADJOINT_POSITRON;
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "The geometry particle type " << particle_type <<
                       " is not supported!" );
    }
  }
}
  
// Convert shorthand particle type name to particle type
/*! \details These shorthand names should correspond to the names that would
 * be encountered in DagMC.
 */
ParticleType convertShortParticleTypeNameToParticleTypeEnum(
				  const std::string& short_particle_type_name )
{
  if( short_particle_type_name == "n" )
    return NEUTRON;
  else if( short_particle_type_name == "p" )
    return PHOTON;
  else if( short_particle_type_name == "e" )
    return ELECTRON;
  else if( short_particle_type_name == "e+" )
    return POSITRON;
  else if( short_particle_type_name == "an" )
    return ADJOINT_NEUTRON;
  else if( short_particle_type_name == "ap" )
    return ADJOINT_PHOTON;
  else if( short_particle_type_name == "ae" )
    return ADJOINT_ELECTRON;
  else if( short_particle_type_name == "ae+" )
    return ADJOINT_POSITRON;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "The short particle type name ("
                     << short_particle_type_name << ") is not valid!" );
  }
}

// Get the particle type enum from an int
ParticleType convertIntToParticleType( const int raw_particle_type )
{
  switch( raw_particle_type )
  {
    case (int)PHOTON: return PHOTON;
    case (int)NEUTRON: return NEUTRON;
    case (int)ELECTRON: return ELECTRON;
    case (int)POSITRON: return POSITRON;
    case (int)ADJOINT_PHOTON: return ADJOINT_PHOTON;
    case (int)ADJOINT_NEUTRON: return ADJOINT_NEUTRON;
    case (int)ADJOINT_ELECTRON: return ADJOINT_ELECTRON;
    case (int)ADJOINT_POSITRON: return ADJOINT_POSITRON;
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "The raw particle type " << raw_particle_type <<
                       "is not supported!" );
    }
  }
}

} // end MonteCarlo namespace

namespace Utility{

// Convert a MonteCarlo::ParticleType to a string
std::string ToStringTraits<MonteCarlo::ParticleType>::toString( const MonteCarlo::ParticleType type )
{
  switch( type )
  {
  case MonteCarlo::PHOTON: return "Photon";
  case MonteCarlo::NEUTRON: return "Neutron";
  case MonteCarlo::ELECTRON: return "Electron";
  case MonteCarlo::POSITRON: return "Positron";
  case MonteCarlo::ADJOINT_PHOTON: return "Adjoint Photon";
  case MonteCarlo::ADJOINT_NEUTRON: return "Adjoint Neutron";
  case MonteCarlo::ADJOINT_ELECTRON: return "Adjoint Electron";
  case MonteCarlo::ADJOINT_POSITRON: return "Adjoint Positron";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "The particle type " << (int)type << " cannot be "
                     "converted to a string!" );

  }
}

// Place the MonteCarlo::ParticleType in a stream
void ToStringTraits<MonteCarlo::ParticleType>::toStream( std::ostream& os, const MonteCarlo::ParticleType type )
{
  os << ToStringTraits<MonteCarlo::ParticleType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleType.cpp
//---------------------------------------------------------------------------//
