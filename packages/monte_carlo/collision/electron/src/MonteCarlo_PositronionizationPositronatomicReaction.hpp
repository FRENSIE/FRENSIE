//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronionizationPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The electroionization electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONIONIZATION_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_POSITRONIONIZATION_POSITRONATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"

namespace MonteCarlo{

/*! The electroionization electroatomic reaction class
* \details This class should be used to represent the total electroionization
* reaction and not the reaction with individual subshells.
*/

template<typename InterpPolicy, bool processed_cross_section = false>
class PositronionizationPositronatomicReaction : public StandardReactionBaseImpl<PositronatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<PositronatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  PositronionizationPositronatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index );

  //! Constructor
  PositronionizationPositronatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher );


  //! Destructor
  ~PositronionizationPositronatomicReaction()
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
  PositronatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  void react( PositronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const override;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PositronionizationPositronatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_POSITRONIONIZATION_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronionizationPositronatomicReaction.hpp
//---------------------------------------------------------------------------//
