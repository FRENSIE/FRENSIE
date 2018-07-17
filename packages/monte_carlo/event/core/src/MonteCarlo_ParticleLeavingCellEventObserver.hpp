//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleLeavingCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event observer base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_OBSERVER_HPP
#define MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_OBSERVER_HPP

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

/*! The particle leaving cell event observer base class
 * \ingroup particle_leaving_cell_event
 */
class ParticleLeavingCellEventObserver{

public:

  //! Typedef for the observer event
  typedef ParticleLeavingCellEvent EventTag;

  //! Constructor
  ParticleLeavingCellEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleLeavingCellEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromParticleLeavingCellEvent(
	   const ParticleState& particle,
	   const Geometry::Model::EntityId cell_leaving ) = 0;

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleLeavingCellEventObserver, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleLeavingCellEventObserver );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleLeavingCellEventObserver );

#endif // end MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleLeavingCellEventObserver.hpp
//---------------------------------------------------------------------------//
