//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher database decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcher.hpp"

namespace MonteCarlo{

/*! The particle subtrack ending in cell event dispatcher database class
 * \ingroup particle_subtrack_ending_in_cell_event
 */
class ParticleSubtrackEndingInCellEventDispatcher : public ParticleEventDispatcher<ParticleSubtrackEndingInCellEventLocalDispatcher>
{
  typedef ParticleEventDispatcher<ParticleSubtrackEndingInCellEventLocalDispatcher> BaseType;

public:

  //! Constructor
  ParticleSubtrackEndingInCellEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleSubtrackEndingInCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the particle subtrack ending in cell event to the observers
  void dispatchParticleSubtrackEndingInCellEvent(
                              const ParticleState& particle,
                              const Geometry::Model::EntityId cell_of_subtrack,
                              const double track_length );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleSubtrackEndingInCellEventDispatcher, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleSubtrackEndingInCellEventDispatcher, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleSubtrackEndingInCellEventDispatcher );

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
