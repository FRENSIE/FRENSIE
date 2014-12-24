//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The absorption electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ABSORPTION_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ABSORPTION_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"

namespace MonteCarlo{

/*! The absorption electroatomic reaction
 * \details This reaction should be used to represent miscellaneous
 * absorption reactions (e.g. heating).
 */
template<typename InterpPolicy, bool processed_cross_section = true>
class AbsorptionElectroatomicReaction : public StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{
  
public:

  //! Constructor
  AbsorptionElectroatomicReaction(
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cross_section,
	  const unsigned threshold_energy_index,
	  const ElectroatomicReactionType reaction );

  //! Destructor
  ~AbsorptionElectroatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( ElectronState& electron, 
	      ParticleBank& bank,
	      SubshellType& shell_of_interaction ) const;

private:

  // The reaction type
  ElectroatomicReactionType d_reaction;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AbsorptionElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ABSORPTION_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
