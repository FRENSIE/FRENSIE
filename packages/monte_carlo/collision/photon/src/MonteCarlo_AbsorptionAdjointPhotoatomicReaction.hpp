//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionAdjointPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The absorption adjoint photoatomic reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"

namespace MonteCarlo{

/*! The absorption adjoint photoatomic reaction
 * \details This reaction should be used to represent miscellaneous 
 * absorption reactions (e.g. the total reaction).
 */
template<typename InterpPolicy, bool processed_cross_section = true>
class AbsorptionAdjointPhotoatomicReaction : public StandardReactionBaseImpl<AdjointPhotoatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<AdjointPhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic constructor
  AbsorptionAdjointPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const AdjointPhotoatomicReactionType reaction );

  //! Constructor
  AbsorptionAdjointPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const AdjointPhotoatomicReactionType reaction );

  //! Destructor
  ~AbsorptionAdjointPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of adjoint photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointPhotons( const double energy ) const override;

  //! Return the number of adjoint electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointElectrons( const double energy ) const override;

  //! Return the number of adjoint positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointPositrons( const double energy ) const override;

  //! Return the reaction type
  AdjointPhotoatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  void react( AdjointPhotonState& adjoint_photon,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const override;

private:

  // The reaction type
  AdjointPhotoatomicReactionType d_reaction;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AbsorptionAdjointPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionAdjointPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
