//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_AdjointElectroAtomicReaction.hpp
//! \author Luke Kersting
//! \brief The Adjoint Electron reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Data_SubshellType.hpp"
#include "MonteCarlo_AtomicReaction.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"

namespace MonteCarlo{

//! The electron/positron reaction base class
class AdjointElectroatomicReaction : public AtomicReaction
{

public:

  //!Constructor
  AdjointElectroatomicReaction()
  { /* ... */ }

  //!Destructor
  virtual ~AdjointElectroatomicReaction()
  { /* ... */}

  //! Return the reaction type
  virtual AdjointElectroatomicReactionType getReactionType() const = 0;

  //! Simulate the reaction
  virtual void react( AdjointElectronState& electron,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction ) const = 0;

  //! Simulate the reaction and track the number of sampling trials
  virtual void react( AdjointElectronState& electron,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction,
                      unsigned& trials ) const;

};

// Simulate the reaction and track the number of sampling trials
inline void AdjointElectroatomicReaction::react(
                AdjointElectronState& electron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction,
                unsigned& trials ) const
{
  ++trials;

  this->react( electron, bank, shell_of_interaction );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroAtomicReaction.hpp
//---------------------------------------------------------------------------//
