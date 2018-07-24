//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventTags.hpp
//! \author Alex Robinson
//! \brief  Event tag declarations.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_EVENT_TAGS_HPP
#define MONTE_CARLO_EVENT_TAGS_HPP

/*! \defgroup particle_colliding_in_cell_event Particle Colliding In Cell Event
 * \ingroup entity_events
 *
 * Infrastructure used to handle particle colliding in cell events.
 */

/*! \defgroup particle_crossing_surface_event Particle Crossing Surface Event
 * \ingroup entity_events
 *
 * Infrastructure used to handle particle crossing surface events.
 */

/*! \defgroup particle_entering_cell_event Particle Entering Cell Event
 * \ingroup entity_events
 *
 * Infrastructure used to handle particle entering cell events.
 */

/*! \defgroup particle_leaving_cell_event Particle Leaving Cell Event
 * \ingroup entity_events
 *
 * Infrastructure used to handle particle leaving cell events.
 */

/*! \defgroup particle_subtrack_ending_in_cell_event Particle Subtrack Ending In Cell Event
 * \ingroup entity_events
 *
 * Infrastructure used to handle particle subtrack ending in cell events.
 */

/*! \defgroup particle_gone_global_event Particle Gone Global Event
 * \ingroup global_events
 *
 * Infrastructure used to handle particle gone global events.
 */

/*! \defgroup particle_colliding_global_event Particle Colliding Global Event
 * \ingroup global_events
 *
 * Infrastructure used to handle particle colliding global events.
 */

/*! \defgroup particle_subtrack_ending_global_event Particle Subtrack Ending Global Event
 * \ingroup global_events
 *
 * Infrastructure used to handle particle subtrack ending global events.
 */

namespace MonteCarlo{

/*! The particle colliding in cell event tag
 * \ingroup particle_colliding_in_cell_event
 */
struct ParticleCollidingInCellEvent{};

/*! The particle crossing surface event tag
 * \ingroup particle_crossing_surface_event
 */
struct ParticleCrossingSurfaceEvent{};

/*! The particle entering cell event tag
 * \ingroup particle_entering_cell_event
 */
struct ParticleEnteringCellEvent{};

/*! The particle leaving cell event tag
 * \ingroup particle_leaving_cell_event
 */
struct ParticleLeavingCellEvent{};

/*! The particle subtrack ending in cell event tag
 * \ingroup particle_subtrack_ending_in_cell_event
 */
struct ParticleSubtrackEndingInCellEvent{};

/*! The particle gone global event
 * \ingroup particle_gone_global_event
 */
struct ParticleGoneGlobalEvent{};
  
/*! The particle colliding global event
 * \ingroup particle_colliding_global_event
 */
struct ParticleCollidingGlobalEvent{};
  
/*! The particle subrack ending global event
 * \ingroup particle_subtrack_ending_global_event
 */
struct ParticleSubtrackEndingGlobalEvent{};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_EVENT_TAGS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventTags.hpp
//---------------------------------------------------------------------------//
