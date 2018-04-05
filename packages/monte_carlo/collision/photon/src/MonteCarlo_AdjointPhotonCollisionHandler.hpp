//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonCollisionHandler.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_COLLISION_HANDLER_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_COLLISION_HANDLER_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonMaterial.hpp"
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_StandardAdjointParticleCollisionHandler.hpp"

namespace MonteCarlo{

//! The adjoint photon collision handler traits
struct AdjointPhotonCollisionHandlerTraits
{
  //! The material used by this collision handler
  typedef AdjointPhotonMaterial MaterialType;

  //! The particle type used by this collision handler
  typedef AdjointPhotonState ParticleType;
};

//! The adjoint photon collision handler class
class AdjointPhotonCollisionHandler : public StandardAdjointParticleCollisionHandler<AdjointPhotonCollisionHandlerTraits>
{

private:

  // Typedef for the base type
  typedef StandardAdjointParticleCollisionHandler<AdjointPhotonCollisionHandlerTraits> BaseType;

public:

  //! The material used by this collision handler
  typedef AdjointPhotonCollisionHandlerTraits::MaterialType MaterialType;

  //! The particle type used by this collision handler
  typedef AdjointPhotonCollisionHandlerTraits::ParticleType ParticleType;

  //! Constructor
  AdjointPhotonCollisionHandler( const bool analogue_collisions = true );

  //! Destructor
  virtual ~AdjointPhotonCollisionHandler()
  { /* ... */ }

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                         const AdjointPhotonState& adjoint_photon,
                         const AdjointPhotoatomicReactionType reaction ) const;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTON_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonCollisionHandler.hpp
//---------------------------------------------------------------------------//
