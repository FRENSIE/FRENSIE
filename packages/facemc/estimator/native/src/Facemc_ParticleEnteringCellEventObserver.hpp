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

//! The particle entering cell event observer base class
class ParticleEnteringCellEventObserver
{
  
public:

  //! The event tag type
  struct ParticleEnteringCellEvent{};

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
	  const Geometry::ModuleTraits::InternalCellHandle cell_entering ) = 0;
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_ENTERING_CELL_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleEnteringCellEventObserver.hpp
//---------------------------------------------------------------------------//

