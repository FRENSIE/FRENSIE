//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_ParticleGenerationEventObserver.hpp
//! \author Alex Robinson
//! \brief  Source event observer base class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_GENERATION_EVENT_OBSERVER_HPP
#define FACEMC_PARTICLE_GENERATION_EVENT_OBSERVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_ModuleTraits.hpp"
#include "Facemc_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The source event observer base class
class ParticleGenerationEventObserver{

public:

  //! Constructor 
  ParticleGenerationEventObserver( 
   const ModuleTraits::InternalEstimatorHandle id,
   const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids,
   const bool auto_register_with_dispatchers );

  //! Destructor
  virtual ~ParticleGenerationEventObserver();

  //! Register the observer
  void registerWithParticleGenerationEventDispatcher(
   const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids);

  //! Update the observer 
  virtual void updateFromParticleGenerationEvent( 
					   const ParticleState& particle ) = 0;

private:

  // The estimator id corresponding to this observer
  ModuleTraits::InternalEstimatorHandle d_id;

  // Indicates if the observer has registered
  bool d_is_registered;  
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_GENERATION_EVENT_OBSERVER

//---------------------------------------------------------------------------//
// end Facemc_ParticleGenerationEventObserver.hpp
//---------------------------------------------------------------------------//
