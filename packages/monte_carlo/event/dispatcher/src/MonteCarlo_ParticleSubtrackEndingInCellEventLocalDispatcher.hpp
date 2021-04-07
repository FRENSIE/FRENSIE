//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

/*! The particle subtrack ending in cell event dispatcher class
 * \ingroup particle_subtrack_ending_in_cell_event
 */
class ParticleSubtrackEndingInCellEventLocalDispatcher : public ParticleEventLocalDispatcher<ParticleSubtrackEndingInCellEventObserver>
{
  typedef ParticleEventLocalDispatcher<ParticleSubtrackEndingInCellEventObserver> BaseType;

public:

  //! Constructor
  ParticleSubtrackEndingInCellEventLocalDispatcher(
                                   const Geometry::Model::EntityId entity_id );

  //! Destructor
  ~ParticleSubtrackEndingInCellEventLocalDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleSubtrackEndingInCellEvent(
                              const ParticleState& particle,
                              const Geometry::Model::EntityId cell_of_subtrack,
                              const double track_length );

private:

  // Default constructor
  ParticleSubtrackEndingInCellEventLocalDispatcher();

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleSubtrackEndingInCellEventLocalDispatcher, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleSubtrackEndingInCellEventLocalDispatcher );

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.hpp
//---------------------------------------------------------------------------//
