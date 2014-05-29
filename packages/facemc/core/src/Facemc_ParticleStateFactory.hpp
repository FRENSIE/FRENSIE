//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleStateFactory.hpp
//! \author Alex Robinson
//! \brief  Particle state factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_STATE_FACTORY_HPP
#define FACEMC_PARTICLE_STATE_FACTORY_HPP

// FRENSIE Includes
#include "Facemc_ParticleState.hpp"
#include "Facemc_ParticleStateCore.hpp"
#include "Facemc_ParticleType.hpp"

namespace Facemc{

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

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_STATE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleStateFactory.hpp
//---------------------------------------------------------------------------//
