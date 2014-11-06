//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_HPP

// Boost Includes
#include <boost/function.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"

namespace MonteCarlo{

//! The pair production photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class AtomicExcitationElectroatomicReaction : public StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Constructor
  AtomicExcitationElectroatomicReaction(
		const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		const Teuchos::ArrayRCP<const double>& cross_section,
		const unsigned threshold_energy_index );

  //! Destructor
  ~AtomicExcitationElectroatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Simulate the reaction
  void react( ElectronState& photon, ParticleBank& bank ) const;

private:

};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_AtomicExcitationElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
