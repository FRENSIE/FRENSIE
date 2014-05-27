//---------------------------------------------------------------------------//
//!
//! \file   ParticleStateFactory.cpp
//! \author Alex Robinson
//! \brief  Particle state factory class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FACEMC Includes
#include "ParticleStateFactory.hpp"
#include "PhotonState.hpp"
#include "NeutronState.hpp"

namespace FACEMC{

// Constructor
ParticleStateFactory::ParticleStateFactory()
{ /* ... */ }

// Create a default particle state with the requested type an history num.
ParticleState::pointerType ParticleStateFactory::createState( 
			       const ParticleType type,
			       const ParticleState::historyNumberType history )
{
  ParticleState::pointerType particle;
  
  switch( type )
  {
  case PHOTON:
    particle.reset( new PhotonState( history ) );
    break;
  case NEUTRON:
    particle.reset( new NeutronState( history ) );
    break;
  default:
    std::string error_message = "Error: The particle type requested cannot ";
    error_message += "currently be created by the ParticleStateFactory.\n";

    throw std::logic_error( error_message );
  }
  
  // Make sure the particle has been initialized
  testPostcondition( particle.get() );

  return particle;
}

// Create a particle state with the requested core.
ParticleState::pointerType ParticleStateFactory::createState( 
					        const ParticleStateCore& core )
{
  ParticleState::pointerType particle;
    
  switch( core.particle_type )
  {
  case PHOTON:
    particle.reset( new PhotonState( core ) );
    break;
  case NEUTRON:
    particle.reset( new NeutronState( core ) );
    break;
  default:
    std::string error_message = "Error: The particle type found in the ";
    error_message += "particle state core cannot currently be created by the ";
    error_message += "ParticleStateFactory.\n";
    
    throw std::logic_error( error_message );
  }
  
  // Make sure the particle has been initialized
  testPostcondition( particle.get() );

  return particle;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end ParticleStateFactory.cpp
//---------------------------------------------------------------------------//
