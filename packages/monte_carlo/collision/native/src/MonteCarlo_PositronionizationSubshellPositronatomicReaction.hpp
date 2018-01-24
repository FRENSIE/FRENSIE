//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronionizationSubshellPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The positron-ionization subshell positron-atomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONIONIZATION_SUBSHELL_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_POSITRONIONIZATION_SUBSHELL_POSITRONATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PositronionizationPositronatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The positron-ionization positron-atomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class PositronionizationSubshellPositronatomicReaction : public PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
typedef PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  PositronionizationSubshellPositronatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
            electroionization_subshell_distribution,
    const double min_electron_energy );

  //! Constructor
  PositronionizationSubshellPositronatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
            electroionization_subshell_distribution,
    const double min_electron_energy );


  //! Destructor
  ~PositronionizationSubshellPositronatomicReaction()
  { /* ... */ }

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double outgoing_energy ) const;

  //! Simulate the reaction
  void react( PositronState& positron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

  //! Return the reaction type
  PositronatomicReactionType getReactionType() const;

  //! Get the interaction subshell (non-standard interface)
  unsigned getSubshell() const;

private:
  // The positron-ionization distribution
  std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
    d_electroionization_subshell_distribution;

  // The interaction subshell
  Data::SubshellType d_interaction_subshell;

  // The reaction type
  PositronatomicReactionType d_reaction_type;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PositronionizationSubshellPositronatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_POSITRONIONIZATION_SUBSHELL_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronionizationSubshellPositronatomicReaction.hpp
//---------------------------------------------------------------------------//
