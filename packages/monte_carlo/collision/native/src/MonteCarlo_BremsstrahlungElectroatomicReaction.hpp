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
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

//! The bremsstrahlung electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class BremsstrahlungElectroatomicReaction : public StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Basic Constructor
  BremsstrahlungElectroatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
              bremsstrahlung_distribution );

  //! Constructor
  BremsstrahlungElectroatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
              bremsstrahlung_distribution );

  //! Destructor
  virtual ~BremsstrahlungElectroatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Return the differential cross section
  double getDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy ) const;

  //! Return the differential cross section (efficient)
  double getDifferentialCrossSection(
    const unsigned incoming_energy_bin,
    const double incoming_energy,
    const double outgoing_energy ) const;

  //! Simulate the reaction
  void react( ElectronState& electron,
	      ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const;

private:

  // The bremsstrahlung scattering distribution
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    d_bremsstrahlung_distribution;
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
