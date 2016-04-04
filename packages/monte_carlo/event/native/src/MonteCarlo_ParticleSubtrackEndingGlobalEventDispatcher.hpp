//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle subtrack ending global event dispatcher
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleGlobalEventDispatcher.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"

namespace MonteCarlo{

/*! The particle subtrack ending global event dispatcher class
 * \ingroup particle_subtrack_ending_global_event
 */
class ParticleSubtrackEndingGlobalEventDispatcher : public ParticleGlobalEventDispatcher<ParticleSubtrackEndingGlobalEventObserver>
{
  
public:

  //! Constructor
  ParticleSubtrackEndingGlobalEventDispatcher();

  //! Destructor
  ~ParticleSubtrackEndingGlobalEventDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleSubtrackEndingGlobalEvent(const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp
//---------------------------------------------------------------------------//
