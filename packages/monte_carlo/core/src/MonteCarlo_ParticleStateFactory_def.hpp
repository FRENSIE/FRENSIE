//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleStateFactory.cpp
//! \author Alex Robinson
//! \brief  Particle state factory class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_STATE_FACTORY_DEF_HPP
#define MONTE_CARLO_PARTICLE_STATE_FACTORY_DEF_HPP

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_ParticleStateFactory.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Create a default particle state with the requested type an history num.
/*! \details Do not use the probe particle types. Instead specify that a 
 * probe particle is desired for the standard particle type.
 */
template<typename SmartPointer>
void ParticleStateFactory::createState(
			       SmartPointer& particle,
			       const ParticleType type,
			       const ParticleState::historyNumberType history,
                               const bool probe )
{
  switch( type )
  {
  case PHOTON:
    if( probe )
    {
      THROW_EXCEPTION( std::logic_error,
                       "Error: There is no photon probe state currently!" );
    }
    else
      particle.reset( new PhotonState( history ) );
    break;
  case NEUTRON:
    if( probe )
    {
      THROW_EXCEPTION( std::logic_error,
                       "Error: There is no neutron probe state currently!" );
    }
    else
      particle.reset( new NeutronState( history ) );
    break;
  case ELECTRON:
    if( probe )
    {
      THROW_EXCEPTION( std::logic_error,
                       "Error: There is no electron probe state currently!" );
    }
    else
      particle.reset( new ElectronState( history ) );
    break;
  case ADJOINT_PHOTON:
    if( probe )
      particle.reset( new AdjointPhotonProbeState( history ) );
    else
      particle.reset( new AdjointPhotonState( history ) );
    break;
  case ADJOINT_ELECTRON:
    particle.reset( new AdjointElectronState( history ) );
    break;
  default:
    THROW_EXCEPTION( std::logic_error,
		     "The particle type requested cannot "
		     "currently be created by the ParticleStateFactory! If "
                     "a probe state was requested use the standard particle "
                     "type and use true for the probe variable." );
  }

  // Make sure the particle has been initialized
  testPostcondition( particle.get() );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_STATE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleStateFactory.cpp
//---------------------------------------------------------------------------//
