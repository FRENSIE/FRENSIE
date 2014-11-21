//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The electroionization electroatomic reaction class decl.
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The electroionization electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class ElectroionizationElectroatomicReaction : public StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Constructor
  ElectroionizationElectroatomicReaction( 
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cross_section,
	  const unsigned threshold_energy_index,
      const Teuchos::RCP<Utility::OneDDistribution>& electroionization_subshell_cross_sections,
      const ElectroionizationElectronScatteringDistribution::ElectroionizationDistribution& 
      electroionization_scattering_distribution );


  //! Destructor
  ~ElectroionizationElectroatomicReaction()
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
	      unsigned& shell_of_interaction ) const;

private:

  // The electroionization scattering distribution
  ElectroionizationElectronScatteringDistribution d_scattering_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroionizationElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
