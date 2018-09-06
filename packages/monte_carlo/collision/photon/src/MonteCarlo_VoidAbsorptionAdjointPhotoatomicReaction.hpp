//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionAdjointPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The void absorption adjoint photoatomic reaction declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_VoidAdjointAtomicReaction.hpp"

namespace MonteCarlo{

//! The void absorption adjoint photoatomic reaction
class VoidAbsorptionAdjointPhotoatomicReaction : public VoidAdjointAtomicReaction<AdjointPhotoatomicReaction>
{

public:

  //! The trials counter type
  typedef AdjointPhotoatomicReaction::Counter Counter;

  //! Constructor
  VoidAbsorptionAdjointPhotoatomicReaction()
  { /* ... */ }

  //! Destructor
  ~VoidAbsorptionAdjointPhotoatomicReaction()
  { /* ... */ }

  //! Return the reaction type
  AdjointPhotoatomicReactionType getReactionType() const final override;

  //! Simulation the reaction
  void react( AdjointPhotonState& adjoint_photon,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const final override;

  //! Simulate the reaction and track the number of sampling trials
  void react( AdjointPhotonState& adjoint_photon,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction,
              Counter& trials ) const final override;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionAdjointPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
