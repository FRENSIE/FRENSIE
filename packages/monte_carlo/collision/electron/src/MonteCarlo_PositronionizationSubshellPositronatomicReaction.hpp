//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronionizationSubshellPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The positron-ionization subshell positron-atomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONIONIZATION_SUBSHELL_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_POSITRONIONIZATION_SUBSHELL_POSITRONATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronionizationPositronatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The positron-ionization positron-atomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class PositronionizationSubshellPositronatomicReaction : public PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef PositronionizationPositronatomicReaction<InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  PositronionizationSubshellPositronatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
            electroionization_subshell_distribution );

  //! Constructor
  PositronionizationSubshellPositronatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
            electroionization_subshell_distribution );


  //! Destructor
  ~PositronionizationSubshellPositronatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const final override;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double outgoing_energy ) const override;

  //! Simulate the reaction
  void react( PositronState& positron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const override;

  //! Return the reaction type
  PositronatomicReactionType getReactionType() const override;

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
