//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleEnteringCellEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcher.hpp"

namespace MonteCarlo{

/*! The particle entering cell event dispatcher database class
 * \ingroup particle_entering_cell_event
 */
class ParticleEnteringCellEventDispatcher : public ParticleEventDispatcher<ParticleEnteringCellEventLocalDispatcher>
{
  typedef ParticleEventDispatcher<ParticleEnteringCellEventLocalDispatcher> BaseType;

public:

  //! Constructor
  ParticleEnteringCellEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleEnteringCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the particle entering cell event to the observers
  void dispatchParticleEnteringCellEvent(
                               const ParticleState& particle,
                               const Geometry::Model::EntityId cell_entering );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleEnteringCellEventDispatcher, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleEnteringCellEventDispatcher, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleEnteringCellEventDispatcher );

#endif // end MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
