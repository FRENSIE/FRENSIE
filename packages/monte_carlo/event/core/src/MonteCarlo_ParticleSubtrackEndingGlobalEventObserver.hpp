//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle subtrack ending event global observer bass class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_OBSERVER_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventTags.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

/*! The particle subtrack ending event global observer
 * \ingroup particle_subtrack_ending_global_event
 */
class ParticleSubtrackEndingGlobalEventObserver
{

public:

  //! Typedef for the observer event tag
  typedef ParticleSubtrackEndingGlobalEvent EventTag;

  //! Constructor
  ParticleSubtrackEndingGlobalEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleSubtrackEndingGlobalEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromGlobalParticleSubtrackEndingEvent(
					       const ParticleState& particle,
					       const double start_point[3],
					       const double end_point[3] ) = 0;

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleSubtrackEndingGlobalEventObserver, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleSubtrackEndingGlobalEventObserver );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleSubtrackEndingGlobalEventObserver );

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp
//---------------------------------------------------------------------------//
