//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleModeType.cpp
//! \author Alex Robinson
//! \brief  Particle mode type helper function definitions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Test if the particle mode type name is valid
bool isValidParticleModeTypeName( const std::string& particle_mode_type_name )
{
  if( particle_mode_type_name == "Neutron Mode" )
    return true;
  else if( particle_mode_type_name == "Photon Mode" )
    return true;
  else if( particle_mode_type_name == "Electron Mode" )
    return true;
  else if( particle_mode_type_name == "Neutron-Photon Mode" )
    return true;
  else if( particle_mode_type_name == "Photon-Electron Mode" )
    return true;
  else if( particle_mode_type_name == "Neutron-Photon-Electron Mode" )
    return true;
  else if( particle_mode_type_name == "Adjoint Neutron Mode" )
    return true;
  else if( particle_mode_type_name == "Adjoint Photon Mode" )
    return true;
  else if( particle_mode_type_name == "Adjoint Electron Mode" )
    return true;
  else
    return false;
}

// Convert the particle mode type name to a ParticleModeType enum
ParticleModeType convertParticleModeTypeNameToParticleModeTypeEnum(
				   const std::string& particle_mode_type_name )
{
  // Make sure the particle mode type name is valid
  testPrecondition( isValidParticleModeTypeName( particle_mode_type_name ) );

  if( particle_mode_type_name == "Neutron Mode" )
    return NEUTRON_MODE;
  else if( particle_mode_type_name == "Photon Mode" )
    return PHOTON_MODE;
  else if( particle_mode_type_name == "Electron Mode" )
    return ELECTRON_MODE;
  else if( particle_mode_type_name == "Neutron-Photon Mode" )
    return NEUTRON_PHOTON_MODE;
  else if( particle_mode_type_name == "Photon-Electron Mode" )
    return PHOTON_ELECTRON_MODE;
  else if( particle_mode_type_name == "Neutron-Photon-Electron Mode" )
    return NEUTRON_PHOTON_ELECTRON_MODE;
  else if( particle_mode_type_name == "Adjoint Neutron Mode" )
    return ADJOINT_NEUTRON_MODE;
  else if( particle_mode_type_name == "Adjoint Photon Mode" )
    return ADJOINT_PHOTON_MODE;
  else if( particle_mode_type_name == "Adjoint Electron Mode" )
    return ADJOINT_ELECTRON_MODE;
  else
  {
    THROW_EXCEPTION( std::logic_error,
		     "Error: particle mode type name " <<
		     particle_mode_type_name << " is unknown!" );
  }
}

// Convert the unsigned to a ParticleModeType enum
ParticleModeType convertUnsignedToParticleModeTypeEnum(
					    const unsigned particle_mode_type )
{
  switch( particle_mode_type )
  {
  case 0:
    return NEUTRON_MODE;
  case 1:
    return PHOTON_MODE;
  case 2:
    return ELECTRON_MODE;
  case 3:
    return NEUTRON_PHOTON_MODE;
  case 4:
    return PHOTON_ELECTRON_MODE;
  case 5:
    return NEUTRON_PHOTON_ELECTRON_MODE;
  case 6:
    return ADJOINT_NEUTRON_MODE;
  case 7:
    return ADJOINT_PHOTON_MODE;
  case 8:
    return ADJOINT_ELECTRON_MODE;
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: unsigned integer " << particle_mode_type <<
		     " does not correspond to a particle mode type!" );
  }
}

// Convert a ParticleModeType enumeration to a string
std::string convertParticleModeTypeEnumToString(
					 const ParticleModeType particle_mode )
{
  switch( particle_mode )
  {
  case NEUTRON_MODE: return "Neutron Mode";
  case PHOTON_MODE: return "Photon Mode";
  case ELECTRON_MODE: return "Electron Mode";
  case NEUTRON_PHOTON_MODE: return "Neutron-Photon Mode";
  case PHOTON_ELECTRON_MODE: return "Photon-Electron Mode";
  case NEUTRON_PHOTON_ELECTRON_MODE: return "Neutron-Photon-Electron Mode";
  case ADJOINT_NEUTRON_MODE: return "Adjoint Neutron Mode";
  case ADJOINT_PHOTON_MODE: return "Adjoint Photon Mode";
  case ADJOINT_ELECTRON_MODE: return "Adjoint Electron Mode";
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: unknown particle mode encountered!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleModeType.cpp
//---------------------------------------------------------------------------//
