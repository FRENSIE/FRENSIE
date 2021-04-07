//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleLeavingCellEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_LOCAL_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_LOCAL_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleLeavingCellEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

/*! The particle leaving cell event dispatcher
 * \ingroup particle_leaving_cell_event
 */
class ParticleLeavingCellEventLocalDispatcher : public ParticleEventLocalDispatcher<ParticleLeavingCellEventObserver>
{
  typedef ParticleEventLocalDispatcher<ParticleLeavingCellEventObserver> BaseType;

public:

  //! Constructor
  ParticleLeavingCellEventLocalDispatcher(
                                     const Geometry::Model::EntityId cell_id );

  //! Destructor
  ~ParticleLeavingCellEventLocalDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleLeavingCellEvent(
                                const ParticleState& particle,
	                        const Geometry::Model::EntityId cell_leaving );

private:

  // Default constructor
  ParticleLeavingCellEventLocalDispatcher();

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleLeavingCellEventLocalDispatcher, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleLeavingCellEventLocalDispatcher, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleLeavingCellEventLocalDispatcher );

#endif // end MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_LOCAL_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleLeavingCellEventLocalDispatcher.hpp
//---------------------------------------------------------------------------//
