//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionAdjointElectroatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The void absorption adjoint electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAdjointAtomicReaction.hpp"

namespace MonteCarlo{

/*! The void absorption adjoint electroatomic reaction class
 * \details This class can be used to ignore adjoint absorption reactions
 */
class VoidAbsorptionAdjointElectroatomicReaction : public VoidAdjointAtomicReaction<AdjointElectroatomicReaction>
{

public:

  //! Constructor
  VoidAbsorptionAdjointElectroatomicReaction()
  { /* ... */ }

  //! Destructor
  ~VoidAbsorptionAdjointElectroatomicReaction()
  { /* ... */ }

  //! Return the reaction type
  AdjointElectroatomicReactionType getReactionType() const final override;

  //! Simulate the reaction
  void react( AdjointElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const final override;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionAdjointElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
