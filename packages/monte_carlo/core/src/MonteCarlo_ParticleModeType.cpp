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

namespace Utility{

// Convert a MonteCarlo::ParticleModeType to a string
std::string ToStringTraits<MonteCarlo::ParticleModeType>::toString( const MonteCarlo::ParticleModeType type )
{
  switch( type )
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
    THROW_EXCEPTION( Utility::StringConversionException,
		     "Error: unknown particle mode encountered!" );
  }
}

// Place the MonteCarlo::ParticleModeType in a stream
void ToStringTraits<MonteCarlo::ParticleModeType>::toStream( std::ostream& os, const MonteCarlo::ParticleModeType type )
{
  os << ToStringTraits<MonteCarlo::ParticleModeType>::toString( type );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleModeType.cpp
//---------------------------------------------------------------------------//
