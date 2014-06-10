//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleEnteringCellEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event observer base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_ENTERING_CELL_EVENT_OBSERVER_HPP
#define FACEMC_PARTICLE_ENTERING_CELL_EVENT_OBSERVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_ModuleTraits.hpp"
#include "Facemc_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The cell entering observer base class
class ParticleEnteringCellEventObserver{
  
public:

  //! Constructor
  ParticleEnteringCellEventObserver(
    const ModuleTraits::InternalEstimatorHandle id,
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids,
    const bool auto_register_with_dispatchers );

  //! Destructor
  virtual ~ParticleEnteringCellEventObserver();

  //! Register the observer
  void registerWithParticleEnteringCellEventDispatcher(
   const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids);

  //! Update the observer
  virtual void updateFromParticleEnteringCellEvent( 
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalCellHandle cell_entering ) = 0;

private:

  // The estimator id corresponding to this observer
  ModuleTraits::InternalEstimatorHandle d_id;

  // Indicates if the observer has registered
  bool d_is_registered;
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_ENTERING_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleEnteringCellEventObserver.hpp
//---------------------------------------------------------------------------//

