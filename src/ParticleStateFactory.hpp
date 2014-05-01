//---------------------------------------------------------------------------//
//!
//! \file   ParticleStateFactory.hpp
//! \author Alex Robinson
//! \brief  Particle state factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_STATE_FACTORY_HPP
#define PARTICLE_STATE_FACTORY_HPP

// FACEMC Includes
#include "ParticleState.hpp"
#include "ParticleStateCore.hpp"
#include "ParticleType.hpp"

namespace FACEMC{

//! The particle state factory class
class ParticleStateFactory
{

public:

  //! Create a default particle state with the requested type an history num.
  static ParticleState::pointerType createState( 
			      const ParticleType type,
			      const ParticleState::historyNumberType history );

  //! Create a particle state with the requested core.
  static ParticleState::pointerType createState( 
					       const ParticleStateCore& core );

private:

  // Constructor
  ParticleStateFactory();
};

} // end FACEMC namespace

#endif // end PARTICLE_STATE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end ParticleStateFactory.hpp
//---------------------------------------------------------------------------//
