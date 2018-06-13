//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event observer base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_OBSERVER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"
#include "Geometry_Model.hpp"
#include "Utility_Vector.hpp"
#include "Utility_SerializationHelpers.hpp"

/*! \defgroup particle_crossing_surface_event Particle Crossing Surface Event
 * \ingroup entity_events
 *
 * Infrastructure used to acquire information from particle crossing surface
 * events.
 */

namespace MonteCarlo{

/*! The particle crossing surface event observer base class
 * \ingroup particle_crossing_surface_event
 */
class ParticleCrossingSurfaceEventObserver
{

public:

  //! The event tag type
  struct ParticleCrossingSurfaceEvent{};

  //! Typedef for the observer event tag
  typedef ParticleCrossingSurfaceEvent EventTag;

  //! Constructor
  ParticleCrossingSurfaceEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleCrossingSurfaceEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::Model::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine ) = 0;

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleCrossingSurfaceEventObserver, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleCrossingSurfaceEventObserver );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::ParticleCrossingSurfaceEventObserver );

#endif // end MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventObserver.hpp
//---------------------------------------------------------------------------//
