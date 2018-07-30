//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleCollidingInCellEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcher.hpp"

namespace MonteCarlo{

/*! The particle colliding in cell event dispatcher class
 * \ingroup particle_colliding_in_cell_event
 */
class ParticleCollidingInCellEventDispatcher : public ParticleEventDispatcher<ParticleCollidingInCellEventLocalDispatcher>
{
  typedef ParticleEventDispatcher<ParticleCollidingInCellEventLocalDispatcher> BaseType;

public:

  //! Constructor
  ParticleCollidingInCellEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleCollidingInCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the particle colliding in cell event to the observers
  void dispatchParticleCollidingInCellEvent(
                             const ParticleState& particle,
	                     const Geometry::Model::EntityId cell_of_collision,
                             const double inverse_total_cross_section );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleCollidingInCellEventDispatcher, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleCollidingInCellEventDispatcher, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleCollidingInCellEventDispatcher );

#endif // end MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
