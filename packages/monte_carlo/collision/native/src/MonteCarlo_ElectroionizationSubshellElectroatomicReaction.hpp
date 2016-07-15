//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The electroionization subshell electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The electroionization electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class ElectroionizationSubshellElectroatomicReaction : public ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Basic Constructor
  ElectroionizationSubshellElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
            electroionization_subshell_distribution );

  //! Constructor
  ElectroionizationSubshellElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
            electroionization_subshell_distribution );


  //! Destructor
  ~ElectroionizationSubshellElectroatomicReaction()
  { /* ... */ }

  //! Return the differential cross section
  double getDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy ) const;

  //! Simulate the reaction
  void react( ElectronState& electron,
	      ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Get the interaction subshell (non-standard interface)
  unsigned getSubshell() const;

private:
  // The electroionization distribution
  std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
    d_electroionization_subshell_distribution;

  // The interaction subshell
  Data::SubshellType d_interaction_subshell;

  // The reaction type
  ElectroatomicReactionType d_reaction_type;
/*
  // The electroionization subshell scattering distribution
  ElectroionizationSubshellElectronScatteringDistribution
    d_scattering_distribution;
*/
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
