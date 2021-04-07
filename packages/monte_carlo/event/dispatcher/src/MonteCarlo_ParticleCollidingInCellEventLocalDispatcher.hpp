//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

/*! The particle colliding in cell event dispatcher
 * \ingroup particle_colliding_in_cell_event
 */
class ParticleCollidingInCellEventLocalDispatcher : public ParticleEventLocalDispatcher<ParticleCollidingInCellEventObserver>
{
  typedef ParticleEventLocalDispatcher<ParticleCollidingInCellEventObserver> BaseType;

public:

  //! Constructor
  ParticleCollidingInCellEventLocalDispatcher(
                                     const Geometry::Model::EntityId cell_id );

  //! Destructor
  ~ParticleCollidingInCellEventLocalDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleCollidingInCellEvent(
                             const ParticleState& particle,
	                     const Geometry::Model::EntityId cell_of_collision,
                             const double inverse_total_cross_section );

private:

  // Default constructor
  ParticleCollidingInCellEventLocalDispatcher();

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleCollidingInCellEventLocalDispatcher, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleCollidingInCellEventLocalDispatcher, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleCollidingInCellEventLocalDispatcher );

#endif // end MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventLocalDispatcher.hpp
//---------------------------------------------------------------------------//
