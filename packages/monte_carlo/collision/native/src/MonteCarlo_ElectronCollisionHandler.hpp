//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronCollisionHandler.hpp
//! \author Alex Robinson
//! \brief  Electron collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_COLLISION_HANDLER_HPP
#define MONTE_CARLO_ELECTRON_COLLISION_HANDLER_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronMaterial.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_StandardParticleCollisionHandler.hpp"

namespace MonteCarlo{

//! The electron collision handler traits
struct ElectronCollisionHandlerTraits
{
  //! The material used by this collision handler
  typedef ElectronMaterial MaterialType;

  //! The particle type used by this collision handler
  typedef ElectronState ParticleType;
};

//! The electron collision handler class
class ElectronCollisionHandler : public StandardParticleCollisionHandler<ElectronCollisionHandlerTraits>
{

private:

  // Typedef for the base type
  typedef StandardParticleCollisionHandler<ElectronCollisionHandlerTraits> BaseType;

public:

  //! The material used by this collision handler
  typedef ElectronCollisionHandlerTraits::MaterialType MaterialType;

  //! The particle type used by this collision handler
  typedef ElectronCollisionHandlerTraits::ParticleType ParticleType;

  //! Constructor
  ElectronCollisionHandler( const bool analogue_collisions = true );

  //! Destructor
  virtual ~ElectronCollisionHandler()
  { /* ... */ }

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                              const ElectronState& electron,
                              const ElectroatomicReactionType reaction ) const;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronCollisionHandler.hpp
//---------------------------------------------------------------------------//
