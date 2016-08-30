//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidStandardElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The void standard electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_STANDARD_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_STANDARD_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"

namespace MonteCarlo{

/*! The void standard electroatomic reaction class
* \details This class can be used to create a standard electroatomic reaction
* class that only return cross section information and not react.
*/

template<typename InterpPolicy, bool processed_cross_section = false>
class VoidStandardElectroatomicReaction : public StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Constructor
  VoidStandardElectroatomicReaction(
	const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	const Teuchos::ArrayRCP<const double>& cross_section,
	const unsigned threshold_energy_index );

  //! Constructor
  VoidStandardElectroatomicReaction(
	const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	const Teuchos::ArrayRCP<const double>& cross_section,
	const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher );

  //! Destructor
  ~VoidStandardElectroatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( ElectronState& electron,
		      ParticleBank& bank,
		      Data::SubshellType& shell_of_interaction ) const;

};

template<typename InterpPolicy, bool processed_cross_section>
VoidStandardElectroatomicReaction<InterpPolicy,processed_cross_section>::VoidStandardElectroatomicReaction(
	const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	const Teuchos::ArrayRCP<const double>& cross_section,
	const unsigned threshold_energy_index )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
        incoming_energy_grid,
        cross_section,
        threshold_energy_index )
  { /* ... */ }

template<typename InterpPolicy, bool processed_cross_section>
VoidStandardElectroatomicReaction<InterpPolicy,processed_cross_section>::VoidStandardElectroatomicReaction(
	const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	const Teuchos::ArrayRCP<const double>& cross_section,
	const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
        incoming_energy_grid,
        cross_section,
        threshold_energy_index,
        grid_searcher )
  { /* ... */ }

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
inline unsigned
VoidStandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons(
    const double energy ) const
{
  return 0u;
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
inline unsigned
VoidStandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons(
    const double energy ) const
{
  return 0u;
}

// Return reaction type
template<typename InterpPolicy, bool processed_cross_section>
inline ElectroatomicReactionType
VoidStandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return TOTAL_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
inline void
VoidStandardElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
       ElectronState& electron,
       ParticleBank& bank,
       Data::SubshellType& shell_of_interaction ) const
{ /* ... */ }

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_STANDARD_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidStandardElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
