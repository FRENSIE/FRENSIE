//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_LOCAL_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_LOCAL_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEnteringCellEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

/*! The particle entering cell event dispatcher class
 * \ingroup particle_entering_cell_event
 */
class ParticleEnteringCellEventLocalDispatcher : public ParticleEventLocalDispatcher<ParticleEnteringCellEventObserver>
{
  typedef ParticleEventLocalDispatcher<ParticleEnteringCellEventObserver> BaseType;

public:

  //! Constructor
  ParticleEnteringCellEventLocalDispatcher(
                                     const Geometry::Model::EntityId cell_id );

  //! Destructor
  ~ParticleEnteringCellEventLocalDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleEnteringCellEvent(
                               const ParticleState& particle,
                               const Geometry::Model::EntityId cell_entering );

private:

  // Default constructor
  ParticleEnteringCellEventLocalDispatcher();

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleEnteringCellEventLocalDispatcher, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleEnteringCellEventLocalDispatcher, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleEnteringCellEventLocalDispatcher );

#endif // end MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_LOCAL_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventLocalDispatcher.hpp
//---------------------------------------------------------------------------//
