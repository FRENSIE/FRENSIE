//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event observer base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_OBSERVER_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventTags.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_Model.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

/*! The particle colliding in cell event observer base class
 * \ingroup particle_colliding_in_cell_event
 */
class ParticleCollidingInCellEventObserver
{

public:


  //! Typedef for the observer event tag
  typedef ParticleCollidingInCellEvent EventTag;

  //! Constructor
  ParticleCollidingInCellEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleCollidingInCellEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromParticleCollidingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::Model::EntityId cell_of_collision,
	    const double inverse_total_cross_section ) = 0;

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleCollidingInCellEventObserver, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleCollidingInCellEventObserver );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleCollidingInCellEventObserver );

#endif // end MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventObserver.hpp
//---------------------------------------------------------------------------//
