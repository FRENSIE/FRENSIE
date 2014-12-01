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
  if( particle_mode_type_name == "NEUTRON_MODE" )
    return true;
  else if( particle_mode_type_name == "PHOTON_MODE" )
    return true;
  else if( particle_mode_type_name == "ELECTRON_MODE" )
    return true;
  else if( particle_mode_type_name == "NEUTRON_PHOTON_MODE" )
    return true;
  else if( particle_mode_type_name == "PHOTON_ELECTRON_MODE" )
    return true;
  else if( particle_mode_type_name == "NEUTRON_PHOTON_ELECTRON_MODE" )
    return true;
  else if( particle_mode_type_name == "ADJOINT_NEUTRON_MODE" )
    return true;
  else if( particle_mode_type_name == "ADJOINT_PHOTON_MODE" )
    return true;
  else if( paticle_mode_type_name == "ADJOINT_ELECTRON_MODE" )
    return true;
  else
    return false;
}

// Convert the particle mode type name to a ParticleModeType enum
ParticleModeType convertParticleModeTypeNameToParticleModeTypeEnum(
				   const std::string& particle_mode_type_name )
{
  // Make sure the particle mode type name is valid
  testPrecondition( isValidParticleModeTypeName( particle_type_name ) );
  
  if( particle_mode_type_name == "NEUTRON_MODE" )
    return NEUTRON_MODE;
  else if( particle_mode_type_name == "PHOTON_MODE" )
    return PHOTON_MODE;
  else if( particle_mode_type_name == "ELECTRON_MODE" )
    return ELECTRON_MODE;
  else if( particle_mode_type_name == "NEUTRON_PHOTON_MODE" )
    return NEUTRON_PHOTON_MODE;
  else if( particle_mode_type_name == "PHOTON_ELECTRON_MODE" )
    return PHOTON_ELECTRON_MODE;
  else if( particle_mode_type_name == "NEUTRON_PHOTON_ELECTRON_MODE" )
    return NEUTRON_PHOTON_ELECTRON_MODE;
  else if( particle_mode_type_name == "ADJOINT_NEUTRON_MODE" )
    return ADJOINT_NEUTRON_MODE;
  else if( particle_mode_type_name == "ADJOINT_PHOTON_MODE" )
    return ADJOINT_PHOTON_MODE;
  else if( paticle_mode_type_name == "ADJOINT_ELECTRON_MODE" )
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleModeType.cpp
//---------------------------------------------------------------------------//
