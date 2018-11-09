//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationProperties.cpp
//! \author Alex Robinson
//! \brief  Simulation properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Set atomic relaxation mode to off
void SimulationProperties::setAtomicRelaxationModeOff(
                                                  const ParticleType particle )
{
  switch( particle )
  {
  case PHOTON:
    SimulationPhotonProperties::setAtomicRelaxationModeOff();
    break;
  case ELECTRON:
    SimulationElectronProperties::setAtomicRelaxationModeOff();
    break;
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: atomic relaxation mode only exists for photons "
                     "and electrons!" );
  }
}

// Set atomic relaxation mode to on
void SimulationProperties::setAtomicRelaxationModeOn(
                                                  const ParticleType particle )
{
  switch( particle )
  {
  case PHOTON:
    SimulationPhotonProperties::setAtomicRelaxationModeOn();
    break;
  case ELECTRON:
    SimulationElectronProperties::setAtomicRelaxationModeOn();
    break;
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: atomic relaxation mode only exists for photons "
                     "and electrons!" );
  }
}

// Return if atomic relaxation mode is on
bool SimulationProperties::isAtomicRelaxationModeOn(
                                            const ParticleType particle ) const
{
  switch( particle )
  {
  case PHOTON:
    return SimulationPhotonProperties::isAtomicRelaxationModeOn();
  case ELECTRON:
    return SimulationElectronProperties::isAtomicRelaxationModeOn();
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: atomic relaxation mode only exists for photons "
                     "and electrons!" );
  }
}

EXPLICIT_CLASS_SERIALIZE_INST( SimulationProperties );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SimulationProperties );

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties.cpp
//---------------------------------------------------------------------------//
