//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The void electroatomic reaction class decl.
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"
#include "MonteCarlo_StandardElectroatomicReaction.hpp"

namespace MonteCarlo{

/*! The void electroatomic reaction class
 * \details This class can be used to ignore any electroatomic reactions in standard form.
 */

template<typename InterpPolicy, bool processed_cross_section = false>
class VoidElectroatomicReaction : public StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{
  
public:

  //! Constructor
  VoidElectroatomicReaction(
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cross_section,
	  const unsigned threshold_energy_index,
      const ElectroatomicReactionType reaction );

  //! Destructor
  ~VoidElectroatomicReaction()
  { /* ... */ }

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( ElectronState& electron, 
              ParticleBank& bank,
              SubshellType& shell_of_interaction ) const;

private:

  // The reaction type
  ElectroatomicReactionType d_reaction;
};

// Constructor without doppler broadening
template<typename InterpPolicy, bool processed_cross_section>
VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::VoidElectroatomicReaction(
	   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	   const Teuchos::ArrayRCP<const double>& cross_section,
	   const unsigned threshold_energy_index,
	   const ElectroatomicReactionType reaction )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
						      incoming_energy_grid,
						      cross_section,
						      threshold_energy_index ),
    d_reaction( reaction )
{ /* ... */ }

// Return the cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection( 
                                                     const double energy ) const
{
  return 0.0;
}

// Return the threshold energy
template<typename InterpPolicy, bool processed_cross_section>
double VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::getThresholdEnergy() const
{ 
  return 0.0;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( 
                                                     const double energy ) const
{
  return 0u;
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( 
                                                     const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::react( 
				     ElectronState& electron, 
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  shell_of_interaction = UNKNOWN_SUBSHELL;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
