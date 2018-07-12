//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event observer base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_OBSERVER_HPP

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

/*! The particle entering cell event observer base class
 * \ingroup particle_entering_cell_event
 */
class ParticleEnteringCellEventObserver
{

public:

  //! Typedef for the observer event tag
  typedef ParticleEnteringCellEvent EventTag;

  //! Constructor
  ParticleEnteringCellEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleEnteringCellEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromParticleEnteringCellEvent(
	  const ParticleState& particle,
	  const Geometry::Model::EntityId cell_entering ) = 0;

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleEnteringCellEventObserver, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleEnteringCellEventObserver );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleEnteringCellEventObserver );

#endif // end MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventObserver.hpp
//---------------------------------------------------------------------------//

