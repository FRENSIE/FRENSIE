//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleLeavingCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event observer base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_LEAVING_CELL_EVENT_OBSERVER_HPP
#define FACEMC_PARTICLE_LEAVING_CELL_EVENT_OBSERVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_ModuleTraits.hpp"
#include "Facemc_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The particle leaving cell event observer base class
class ParticleLeavingCellEventObserver{
  
public:

  //! Constructor
  ParticleLeavingCellEventObserver(
    const ModuleTraits::InternalEstimatorHandle id,
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids,
    const bool auto_register_with_dispatchers );

  //! Destructor
  virtual ~ParticleLeavingCellEventObserver();

  //! Register the observer
  void registerWithParticleLeavingCellEventDispatcher(
   const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids);

  //! Update the observer
  virtual void updateFromParticleLeavingCellEvent(
	   const ParticleState& particle,
	   const Geometry::ModuleTraits::InternalCellHandle cell_leaving ) = 0;

private:

  // The estimator id corresponding to this observer
  ModuleTraits::InternalEstimatorHandle d_id;

  // Indicates if the observer has registered
  bool d_is_registered;
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_LEAVING_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleLeavingCellEventObserver.hpp
//---------------------------------------------------------------------------//
