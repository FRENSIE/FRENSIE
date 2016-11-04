//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_ElectroAtomicReaction.hpp
//! \author Luke Kersting
//! \brief The Electron reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Data_SubshellType.hpp"
#include "MonteCarlo_AtomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"

namespace MonteCarlo{

//! The electron/positron reaction base class
class ElectroatomicReaction : public AtomicReaction
{

public:

  //!Constructor
  ElectroatomicReaction()
  { /* ... */ }

  //!Destructor
  virtual ~ElectroatomicReaction()
  { /* ... */}

  //! Return the reaction type
  virtual ElectroatomicReactionType getReactionType() const = 0;

  //! Simulate the reaction
  virtual void react( ElectronState& electron,
		      ParticleBank& bank,
		      Data::SubshellType& shell_of_interaction ) const = 0;

  //! Simulate the reaction and track the number of sampling trials
  virtual void react( ElectronState& electron,
		      ParticleBank& bank,
		      Data::SubshellType& shell_of_interaction,
		      unsigned& trials ) const;

};

// Simulate the reaction and track the number of sampling trials
inline void ElectroatomicReaction::react( ElectronState& electron,
					ParticleBank& bank,
					Data::SubshellType& shell_of_interaction,
					unsigned& trials ) const
{
  ++trials;

  this->react( electron, bank, shell_of_interaction );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroAtomicReaction.hpp
//---------------------------------------------------------------------------//
