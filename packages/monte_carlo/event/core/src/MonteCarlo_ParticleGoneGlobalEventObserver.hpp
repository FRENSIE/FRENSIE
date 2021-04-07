//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleGoneGlobalEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle gone global event observer base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_GONE_GLOBAL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_GONE_GLOBAL_EVENT_OBSERVER_HPP

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

/*! The particle gone global event observer
 * \ingroup particle_gone_global_event
 */
class ParticleGoneGlobalEventObserver
{

public:

  //! Typedef for the observer event tag
  typedef ParticleGoneGlobalEvent EventTag;

  //! Constructor
  ParticleGoneGlobalEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleGoneGlobalEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromGlobalParticleGoneEvent(
                                           const ParticleState& particle ) = 0;

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};
  
} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleGoneGlobalEventObserver, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleGoneGlobalEventObserver );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleGoneGlobalEventObserver );

#endif // end MONTE_CARLO_PARTICLE_GONE_GLOBAL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleGoneGlobalObserver.hpp
//---------------------------------------------------------------------------//
