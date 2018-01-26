//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation positron-atomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_POSITRONATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "MonteCarlo_StandardGenericAtomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The pair production photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class AtomicExcitationPositronatomicReaction : public StandardGenericAtomicReaction<PositronatomicReaction,InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
typedef StandardGenericAtomicReaction<PositronatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  AtomicExcitationPositronatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>&
            energy_loss_distribution );

  //! Constructor
  AtomicExcitationPositronatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>&
            energy_loss_distribution );

  //! Destructor
  ~AtomicExcitationPositronatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double outgoing_energy ) const;

  //! Return the reaction type
  PositronatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( PositronState& positron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

private:

  // The atomic excitation energy loss distribution
  std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>
    d_energy_loss_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_AtomicExcitationPositronatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationPositronatomicReaction.hpp
//---------------------------------------------------------------------------//
