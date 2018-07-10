//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventActor.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event actor base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_ACTOR_HPP
#define MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_ACTOR_HPP

// Std Lib Includes
#include <functional>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventTags.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Geometry_Model.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

/*! The particle entering cell event actor base class
 * \ingroup particle_entering_cell_event
 */
class ParticleEnteringCellEventActor
{

public:

  //! Typedef for the actor event tag
  typedef ParticleEnteringCellEvent EventTag;

  //! This method can be used to simulate a generated particle for the desired optical path
  typedef std::function<void(ParticleState&,ParticleBank&,const double)>
  SimulateParticleForOpticalPath;

  //! Constructor
  ParticleEnteringCellEventActor()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleEnteringCellEventActor()
  { /* ... */ }

  //! Update the particle state and bank
  virtual void updateFromParticleEnteringCellEvent(
          const Geometry::Model::InternalCellHandle cell_entering,
          const double optical_path_to_next_cell,
          const SimulateParticleForOpticalPath& simulate_particle_track_method,
          ParticleState& particle,
          ParticleBank& bank ) const = 0;

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};
  
} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleEnteringCellEventActor, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleEnteringCellEventActor );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleEnteringCellEventActor );

#endif // end MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_ACTOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventActor.hpp
//---------------------------------------------------------------------------//
