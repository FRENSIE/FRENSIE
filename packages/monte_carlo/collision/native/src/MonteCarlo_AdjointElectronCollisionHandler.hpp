//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronCollisionHandler.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTRON_COLLISION_HANDLER_HPP
#define MONTE_CARLO_ADJOINT_ELECTRON_COLLISION_HANDLER_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronMaterial.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_StandardAdjointParticleCollisionHandler.hpp"

namespace MonteCarlo{

//! The adjoint electron collision handler traits
struct AdjointElectronCollisionHandlerTraits
{
  //! The material used by this collision handler
  typedef AdjointElectronMaterial MaterialType;

  //! The particle type used by this collision handler
  typedef AdjointElectronState ParticleType;
};

//! The adjoint electron collision handler class
class AdjointElectronCollisionHandler : public StandardAdjointParticleCollisionHandler<AdjointElectronCollisionHandlerTraits>
{

private:

  // Typedef for the base type
  typedef StandardAdjointParticleCollisionHandler<AdjointElectronCollisionHandlerTraits> BaseType;

public:

  //! The material used by this collision handler
  typedef AdjointElectronCollisionHandlerTraits::MaterialType MaterialType;

  //! The particle type used by this collision handler
  typedef AdjointElectronCollisionHandlerTraits::ParticleType ParticleType;

  //! Constructor
  AdjointElectronCollisionHandler( const bool analogue_collisions = true );

  //! Destructor
  virtual ~AdjointElectronCollisionHandler()
  { /* ... */ }

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                         const AdjointElectronState& adjoint_electron,
                         const AdjointElectroatomicReactionType reaction ) const;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTRON_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronCollisionHandler.hpp
//---------------------------------------------------------------------------//
