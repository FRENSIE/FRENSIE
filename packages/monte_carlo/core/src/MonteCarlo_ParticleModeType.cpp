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
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert a MonteCarlo::ParticleModeType to a string
std::string ToStringTraits<MonteCarlo::ParticleModeType>::toString( const MonteCarlo::ParticleModeType type )
{
  switch( type )
  {
  case MonteCarlo::NEUTRON_MODE: return "Neutron Mode";
  case MonteCarlo::PHOTON_MODE: return "Photon Mode";
  case MonteCarlo::ELECTRON_MODE: return "Electron Mode";
  case MonteCarlo::NEUTRON_PHOTON_MODE: return "Neutron-Photon Mode";
  case MonteCarlo::PHOTON_ELECTRON_MODE: return "Photon-Electron Mode";
  case MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE: return "Neutron-Photon-Electron Mode";
  case MonteCarlo::ADJOINT_NEUTRON_MODE: return "Adjoint Neutron Mode";
  case MonteCarlo::ADJOINT_PHOTON_MODE: return "Adjoint Photon Mode";
  case MonteCarlo::ADJOINT_ELECTRON_MODE: return "Adjoint Electron Mode";
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Unknown particle mode encountered!" );
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
