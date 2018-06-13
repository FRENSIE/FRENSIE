//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event observer base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_OBSERVER_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"
#include "Geometry_Model.hpp"
#include "Utility_Vector.hpp"
#include "Utility_SerializationHelpers.hpp"

/*! \defgroup particle_subtrack_ending_in_cell_event Particle Subtrack Ending In Cell Event
 * \ingroup entity_events
 *
 * Infrastructure used to acquire information from particle subtrack ending
 * in cell events.
 */

namespace MonteCarlo{

/*! The particle subtrack ending in cell event observer
 * \ingroup particle_subtrack_ending_in_cell_event
 */
class ParticleSubtrackEndingInCellEventObserver
{

public:

  //! The event tag type
  struct ParticleSubtrackEndingInCellEvent{};

  //! Typedef for the observer event tag
  typedef ParticleSubtrackEndingInCellEvent EventTag;

  //! Constructor
  ParticleSubtrackEndingInCellEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleSubtrackEndingInCellEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromParticleSubtrackEndingInCellEvent(
	     const ParticleState& particle,
	     const Geometry::Model::InternalCellHandle cell_of_subtrack,
	     const double track_length ) = 0;

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleSubtrackEndingInCellEventObserver, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleSubtrackEndingInCellEventObserver );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::ParticleSubtrackEndingInCellEventObserver );

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventObserver.hpp
//---------------------------------------------------------------------------//
