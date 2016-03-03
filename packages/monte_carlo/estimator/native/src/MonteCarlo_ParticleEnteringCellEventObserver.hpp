//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event observer base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_OBSERVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

/*! \defgroup particle_entering_cell_event Particle Entering Cell Event
 * \ingroup entity_events
 *
 * Infrastructure used to acquire information from particle entering cell 
 * events.
 */

namespace MonteCarlo{

/*! The particle entering cell event observer base class
 * \ingroup particle_entering_cell_event
 */
class ParticleEnteringCellEventObserver
{
  
public:

  //! The event tag type
  struct ParticleEnteringCellEvent{};

  //! Typedef for the observer event tag
  typedef ParticleEnteringCellEvent EventTag;

  //! Constructor
  ParticleEnteringCellEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleEnteringCellEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromParticleEnteringCellEvent( 
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalCellHandle cell_entering ) = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventObserver.hpp
//---------------------------------------------------------------------------//

