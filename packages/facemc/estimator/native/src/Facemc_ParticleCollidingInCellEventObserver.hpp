//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCollidingInCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event observer base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_OBSERVER_HPP
#define FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_OBSERVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_ModuleTraits.hpp"
#include "Facemc_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The particle colliding in cell event observer base class
class ParticleCollidingInCellEventObserver
{
  
public:

  //! Constructor
  ParticleCollidingInCellEventObserver(
    const ModuleTraits::InternalEstimatorHandle id,
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids,
    const bool auto_register_with_dispatchers );

  //! Destructor
  virtual ~ParticleCollidingInCellEventObserver();

  //! Register the observer
  void registerWithParticleCollidingInCellEventDispatcher(
   const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids);

  //! Update the observer
  virtual void updateFromParticleCollidingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section ) = 0;

private:

  // The estimator id corresponding to this observer
  ModuleTraits::InternalEstimatorHandle d_id;

  // Indicates if the observer has registered
  bool d_is_registered;
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleCollidingInCellEventObserver.hpp
//---------------------------------------------------------------------------//
