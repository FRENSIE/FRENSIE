//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleLeavingCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event observer base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_OBSERVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

/*! \defgroup particle_leaving_cell_event Particle Leaving Cell Event
 * \ingroup entity_events
 * 
 * Infrastructure used to acquire information from particle leaving cell 
 * events.
 */

namespace MonteCarlo{

/*! The particle leaving cell event observer base class
 * \ingroup particle_leaving_cell_event
 */
class ParticleLeavingCellEventObserver{
  
public:

  //! The event tag type
  struct ParticleLeavingCellEvent{};
  
  //! Typedef for the observer event
  typedef ParticleLeavingCellEvent EventTag;

  //! Constructor
  ParticleLeavingCellEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleLeavingCellEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromParticleLeavingCellEvent(
	   const ParticleState& particle,
	   const Geometry::ModuleTraits::InternalCellHandle cell_leaving ) = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleLeavingCellEventObserver.hpp
//---------------------------------------------------------------------------//
