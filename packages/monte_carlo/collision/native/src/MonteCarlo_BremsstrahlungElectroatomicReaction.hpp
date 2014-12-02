//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung Electroatomic reaction class decl.
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The bremsstrahlung electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class BremsstrahlungElectroatomicReaction : public StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Constructor with simple analytical photon angular distribution
  BremsstrahlungElectroatomicReaction( 
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution& 
              bremsstrahlung_scattering_distribution );

  //! Constructor with detailed photon angular distribution
  BremsstrahlungElectroatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution& 
              bremsstrahlung_scattering_distribution,
       const Teuchos::RCP<Utility::OneDDistribution>& angular_distribution,
       const double lower_cutoff_energy,
       const double upper_cutoff_energy );

  //! Destructor
  virtual ~BremsstrahlungElectroatomicReaction()
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
	      SubshellType& shell_of_interaction ) const;

private:

  // The bremsstrahlung scattering distribution
  BremsstrahlungElectronScatteringDistribution d_scattering_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_BremsstrahlungElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
