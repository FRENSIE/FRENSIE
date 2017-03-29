//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The electroionization subshell adjoint electrotomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The electroionization adjoint electrotomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class ElectroionizationSubshellAdjointElectroatomicReaction : public ElectroionizationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
typedef ElectroionizationAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  ElectroionizationSubshellAdjointElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution>&
            electroionization_subshell_distribution );

  //! Constructor
  ElectroionizationSubshellAdjointElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution>&
            electroionization_subshell_distribution );


  //! Destructor
  ~ElectroionizationSubshellAdjointElectroatomicReaction()
  { /* ... */ }

  //! Simulate the reaction
  void react( AdjointElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

  //! Return the reaction type
  AdjointElectroatomicReactionType getReactionType() const;

  //! Get the interaction subshell (non-standard interface)
  unsigned getSubshell() const;

private:
  // The electroionization distribution
  std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution>
    d_electroionization_subshell_distribution;

  // The interaction subshell
  Data::SubshellType d_interaction_subshell;

  // The reaction type
  AdjointElectroatomicReactionType d_reaction_type;

};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
