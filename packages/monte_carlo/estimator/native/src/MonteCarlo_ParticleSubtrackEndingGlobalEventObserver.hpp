//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle subtrack ending event global observer bass class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_OBSERVER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

//! The particle subtrack ending event global observer
class ParticleSubtrackEndingGlobalEventObserver
{

public:

  //! The event tag type
  struct ParticleSubtrackEndingGlobalEvent{};

  //! Typedef for the observer event tag
  typedef ParticleSubtrackEndingGlobalEvent EventTag;

  //! Constructor
  ParticleSubtrackEndingGlobalEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleSubtrackEndingGlobalEventObserver()
  { /* ... */ }
  
  //! Update the observer
  virtual void updateFromGlobalParticleSubtrackEndingEvent(
					       const ParticleState& particle,
					       const double start_point[3],
					       const double end_point[3] ) = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp
//---------------------------------------------------------------------------//
