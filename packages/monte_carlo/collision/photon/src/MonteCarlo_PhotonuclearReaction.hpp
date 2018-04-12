//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearReaction.hpp
//! \author Alex Robinson, Ryan Pease
//! \brief  The photonuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTONUCLEAR_REACTION_HPP
#define MONTE_CARLO_PHOTONUCLEAR_REACTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_NuclearReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The photonuclear reaction base class
class PhotonuclearReaction : public NuclearReaction
{

public:

  //! Constructor
  PhotonuclearReaction()
  { /* ... */ }

  //! Destructor
  virtual ~PhotonuclearReaction()
  { /* ... */ }

  //! Return the reaction type
  virtual PhotonuclearReactionType getReactionType() const = 0;

  //! Simulate the reaction
  virtual void react( PhotonState& photon, ParticleBank& bank ) const = 0;
};

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotonuclearReaction,Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotonuclearReaction,Utility::LinLin,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTONUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearReaction.hpp
//---------------------------------------------------------------------------//
