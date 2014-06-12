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

  //! The event tag type
  struct ParticleLeavingCellEvent{};
  
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
	   const Geometry::ModuleTraits::InternalCellHandle cell_leaving ) = 0;
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_LEAVING_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleLeavingCellEventObserver.hpp
//---------------------------------------------------------------------------//
