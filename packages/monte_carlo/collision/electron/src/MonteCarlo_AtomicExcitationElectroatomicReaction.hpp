//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The pair production photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class AtomicExcitationElectroatomicReaction : public StandardReactionBaseImpl<ElectroatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<ElectroatomicReaction,InterpPolicy,processed_cross_section> 
    BaseType;

public:

  //! Basic Constructor
  AtomicExcitationElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>&
            energy_loss_distribution );

  //! Constructor
  AtomicExcitationElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>&
            energy_loss_distribution );

  //! Destructor
  ~AtomicExcitationElectroatomicReaction()
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

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  void react( ElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const override;

private:

  // The atomic excitation energy loss distribution
  std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>
    d_energy_loss_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_AtomicExcitationElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
