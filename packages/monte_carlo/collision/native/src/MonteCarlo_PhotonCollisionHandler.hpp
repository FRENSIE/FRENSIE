//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonCollisionHandler.hpp
//! \author Alex Robinson
//! \brief  Photon collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_COLLISION_HANDLER_HPP
#define MONTE_CARLO_PHOTON_COLLISION_HANDLER_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotonMaterial.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_StandardParticleCollisionHandler.hpp"

namespace MonteCarlo{

//! The photon collision handler traits
struct PhotonCollisionHandlerTraits
{
  //! The material used by this collision handler
  typedef PhotonMaterial MaterialType;

  //! The particle type used by this collision handler
  typedef PhotonState ParticleType;
};

//! The photon collision handler class
class PhotonCollisionHandler : public StandardParticleCollisionHandler<PhotonCollisionHandlerTraits>
{

private:

  // Typedef for the base type
  typedef StandardParticleCollisionHandler<PhotonCollisionHandlerTraits> BaseType;

public:

  //! The material used by this collision handler
  typedef PhotonCollisionHandlerTraits::MaterialType MaterialType;

  //! The particle type used by this collision handler
  typedef PhotonCollisionHandlerTraits::ParticleType ParticleType;

  //! Check if the particle type is valid
  static bool isParticleTypeValid( const ParticleState& particle );

  //! Constructor
  PhotonCollisionHandler( const bool analogue_collisions = true );

  //! Destructor
  virtual ~PhotonCollisionHandler()
  { /* ... */ }

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                                const PhotonState& photon,
                                const PhotoatomicReactionType reaction ) const;

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                               const PhotonState& photon,
                               const PhotonuclearReactionType reaction ) const;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonCollisionHandler.hpp
//---------------------------------------------------------------------------//
