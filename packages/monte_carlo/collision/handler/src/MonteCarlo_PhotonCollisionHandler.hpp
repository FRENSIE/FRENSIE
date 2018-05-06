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

//! The photon collision handler class
class PhotonCollisionHandler : public StandardParticleCollisionHandler<PhotonMaterial>
{
  // Typedef for the base type
  typedef StandardParticleCollisionHandler<PhotonMaterial> BaseType;

public:

  //! The material used by this collision handler
  typedef BaseType::MaterialType MaterialType;

  //! The reaction enum type used by this collision handler
  typedef BaseType::ReactionEnumType ReactionEnumType;

  //! The particle type used by this collision handler
  typedef BaseType::ParticleStateType ParticleStateType;

  //! Constructor
  PhotonCollisionHandler( const bool analogue_collisions = true );

  //! Destructor
  virtual ~PhotonCollisionHandler()
  { /* ... */ }

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                               const PhotonState& photon,
                               const PhotonuclearReactionType reaction ) const;

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                         const Geometry::ModuleTraits::InternalCellHandle cell,
                         const double energy,
                         const PhotonuclearReactionType reaction ) const;

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSectionQuick(
                               const PhotonState& photon,
                               const PhotonuclearReactionType reaction ) const;

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSectionQuick(
                         const Geometry::ModuleTraits::InternalCellHandle cell,
                         const double energy,
                         const PhotonuclearReactionType reaction ) const;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonCollisionHandler.hpp
//---------------------------------------------------------------------------//
