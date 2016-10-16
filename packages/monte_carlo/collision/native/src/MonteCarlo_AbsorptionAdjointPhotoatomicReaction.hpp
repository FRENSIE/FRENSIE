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
#include "MonteCarlo_StandardGenericAtomicReaction.hpp"
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"

namespace MonteCarlo{

/*! The absorption adjoint photoatomic reaction
 * \details This reaction should be used to represent miscellaneous 
 * absorption reactions (e.g. the total reaction).
 */
template<typename InterpPolicy, bool processed_cross_section = true>
class AbsorptionAdjointPhotoatomicReaction : public StandardGenericAtomicReaction<AdjointPhotoatomicReaction,InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
  typedef StandardGenericAtomicReaction<AdjointPhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic constructor
  AbsorptionAdjointPhotoatomicReaction(
                   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
                   const Teuchos::ArrayRCP<const double>& cross_section,
                   const unsigned threshold_energy_index,
                   const AdjointPhotoatomicReactionType reaction );

  //! Constructor
  AbsorptionAdjointPhotoatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const AdjointPhotoatomicReactionType reaction );

  //! Destructor
  ~AbsorptionAdjointPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of adjoint photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the number of adjoint electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the reaction type
  AdjointPhotoatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( AdjointPhotonState& adjoint_photon,
	      ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const;

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