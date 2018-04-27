//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The electroionization subshell electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The electroionization electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class ElectroionizationSubshellElectroatomicReaction : public StandardReactionBaseImpl<ElectroatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<ElectroatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  ElectroionizationSubshellElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
            electroionization_subshell_distribution );

  //! Constructor
  ElectroionizationSubshellElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const Data::SubshellType interaction_subshell,
    const std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
            electroionization_subshell_distribution );


  //! Destructor
  ~ElectroionizationSubshellElectroatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const override;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const override;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double outgoing_energy ) const override;

  //! Simulate the reaction
  void react( ElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const override;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const override;

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
