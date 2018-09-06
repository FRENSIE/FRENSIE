//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleLeavingCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleLeavingCellEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcher.hpp"

namespace MonteCarlo{

/*! The particle leaving cell event dispatcher database class
 * \ingroup particle_leaving_cell_event
 */
class ParticleLeavingCellEventDispatcher : public ParticleEventDispatcher<ParticleLeavingCellEventLocalDispatcher>
{
  typedef ParticleEventDispatcher<ParticleLeavingCellEventLocalDispatcher> BaseType;

public:

  //! Constructor
  ParticleLeavingCellEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleLeavingCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the particle leaving cell event to the observers
  void dispatchParticleLeavingCellEvent(
                                const ParticleState& particle,
                                const Geometry::Model::EntityId cell_leaving );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleLeavingCellEventDispatcher, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleLeavingCellEventDispatcher, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleLeavingCellEventDispatcher );

#endif // end MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleLeavingCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
