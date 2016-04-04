//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event observer base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_OBSERVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

/*! \defgroup particle_subtrack_ending_in_cell_event Particle Subtrack Ending In Cell Event
 * \ingroup entity_events
 *
 * Infrastructure used to acquire information from particle subtrack ending
 * in cell events.
 */

namespace MonteCarlo{

/*! The particle subtrack ending in cell event observer
 * \ingroup particle_subtrack_ending_in_cell_event
 */
class ParticleSubtrackEndingInCellEventObserver
{
  
public:

  //! The event tag type
  struct ParticleSubtrackEndingInCellEvent{};

  //! Typedef for the observer event tag
  typedef ParticleSubtrackEndingInCellEvent EventTag;

  //! Constructor
  ParticleSubtrackEndingInCellEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleSubtrackEndingInCellEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromParticleSubtrackEndingInCellEvent(
	     const ParticleState& particle,
	     const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
	     const double track_length ) = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventObserver.hpp
//---------------------------------------------------------------------------//
