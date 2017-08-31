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
#include "MonteCarlo_AdjointElectronState.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Create a default particle state with the requested type an history num.
template<typename SmartPointer>
void ParticleStateFactory::createState(
                                SmartPointer& particle,
                                const ParticleType type,
                                const ParticleState::historyNumberType history )
{
  switch( type )
  {
  case PHOTON:
    particle.reset( new PhotonState( history ) );
    break;
  case NEUTRON:
    particle.reset( new NeutronState( history ) );
    break;
  case ELECTRON:
    particle.reset( new ElectronState( history ) );
    break;
  case ADJOINT_PHOTON:
    particle.reset( new AdjointPhotonState( history ) );
    break;
  case ADJOINT_ELECTRON:
    particle.reset( new AdjointElectronState( history ) );
    break;
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: The particle type requested cannot "
                     "currently be created by the ParticleStateFactory.\n" );
  }

  // Make sure the particle has been initialized
  testPostcondition( particle.get() );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_STATE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleStateFactory.cpp
//---------------------------------------------------------------------------//
