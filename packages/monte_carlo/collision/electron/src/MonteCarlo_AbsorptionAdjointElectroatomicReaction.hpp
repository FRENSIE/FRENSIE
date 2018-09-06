//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionAdjointElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The absorption adjoint electroatomic reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"

namespace MonteCarlo{

/*! The absorption adjoint electroatomic reaction
 * \details This reaction should be used to represent miscellaneous 
 * absorption reactions (e.g. the total reaction).
 */
template<typename InterpPolicy, bool processed_cross_section = false>
class AbsorptionAdjointElectroatomicReaction : public StandardReactionBaseImpl<AdjointElectroatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<AdjointElectroatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic constructor
  AbsorptionAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const AdjointElectroatomicReactionType reaction );

  //! Constructor
  AbsorptionAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const AdjointElectroatomicReactionType reaction );

  //! Destructor
  ~AbsorptionAdjointElectroatomicReaction()
  { /* ... */ }

  //! Return the number of adjoint photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointPhotons( const double energy ) const override;

  //! Return the number of adjoint electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointElectrons( const double energy ) const override;

  //! Return the number of adjoint positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointPositrons( const double energy ) const override;

  //! Return the reaction type
  AdjointElectroatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  void react( AdjointElectronState& adjoint_electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const override;

private:

  // The reaction type
  AdjointElectroatomicReactionType d_reaction;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AbsorptionAdjointElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionAdjointElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
