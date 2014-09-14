//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleStateFactory.hpp
//! \author Alex Robinson
//! \brief  Particle state factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_STATE_FACTORY_HPP
#define FACEMC_PARTICLE_STATE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleStateCore.hpp"
#include "MonteCarlo_ParticleType.hpp"

namespace MonteCarlo{

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

} // end MonteCarlo namespace

#endif // end FACEMC_PARTICLE_STATE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleStateFactory.hpp
//---------------------------------------------------------------------------//
