//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The absorption positron-atomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ABSORPTION_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_ABSORPTION_POSITRONATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"

namespace MonteCarlo{

/*! The absorption positron-atomic reaction
 * \details This reaction should be used to represent miscellaneous
 * absorption reactions (e.g. heating).
 */
template<typename InterpPolicy, bool processed_cross_section = false>
class AbsorptionPositronatomicReaction : public StandardReactionBaseImpl<PositronatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<PositronatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Constructor
  AbsorptionPositronatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const PositronatomicReactionType reaction );

  //! Constructor
  AbsorptionPositronatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const PositronatomicReactionType reaction );

  //! Destructor
  ~AbsorptionPositronatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const override;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const override;

  //! Return the reaction type
  PositronatomicReactionType getReactionType() const override;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double outgoing_energy ) const override;

  //! Simulate the reaction
  void react( PositronState& positron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const override;

private:

  // The reaction type
  PositronatomicReactionType d_reaction;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AbsorptionPositronatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ABSORPTION_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionPositronatomicReaction.hpp
//---------------------------------------------------------------------------//
