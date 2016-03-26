//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event observer base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_OBSERVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

/*! \defgroup particle_colliding_in_cell_event Particle Colliding In Cell Event
 * \ingroup entity_events
 * 
 * Infrastructure used to acquire information from particle colliding
 * in cell events. 
 */

namespace MonteCarlo{

/*! The particle colliding in cell event observer base class
 * \ingroup particle_colliding_in_cell_event
 */
class ParticleCollidingInCellEventObserver
{
  
public:

  //! The event tag type
  struct ParticleCollidingInCellEvent{};

  //! Typedef for the observer event tag
  typedef ParticleCollidingInCellEvent EventTag;

  //! Constructor
  ParticleCollidingInCellEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleCollidingInCellEventObserver()
  { /* ... */ }
  
  //! Update the observer
  virtual void updateFromParticleCollidingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section ) = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventObserver.hpp
//---------------------------------------------------------------------------//
