//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleStateFactory.hpp
//! \author Alex Robinson
//! \brief  Particle state factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_STATE_FACTORY_HPP
#define MONTE_CARLO_PARTICLE_STATE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleType.hpp"

namespace MonteCarlo{

/*! The particle state factory class
 * \todo unit test
 */
class ParticleStateFactory
{

public:

  //! Create a default particle state with the requested type an history num.
  template<typename SmartPointer>
  static void createState( SmartPointer& particle,
			   const ParticleType type,
			   const ParticleState::historyNumberType history,
                           const bool probe = false );

private:

  // Constructor
  ParticleStateFactory();
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleStateFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_STATE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleStateFactory.hpp
//---------------------------------------------------------------------------//
