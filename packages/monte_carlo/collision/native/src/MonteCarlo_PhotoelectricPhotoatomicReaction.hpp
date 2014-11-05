//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoelectricPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The photoelectric photoatomic reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardPhotoatomicReaction.hpp"

namespace MonteCarlo{

/*! The photoelectric photoatomic reaction class
 * \details This class should be used to represent the total photoelectric
 * reaction and not the reaction with individual subshells.
 */
template<typename InterpPolicy, bool processed_cross_section = true>
class PhotoelectricPhotoatomicReaction : public StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Constructor 
  PhotoelectricPhotoatomicReaction(
		const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		const Teuchos::ArrayRCP<const double>& cross_section,
		const unsigned threshold_energy_index );

  //! Destructor
  ~PhotoelectricPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  virtual PhotoatomicReactionType getReactionType() const;

  //! Simulate the reaction
  virtual void react( PhotonState& photon, 
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PhotoelectricPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoelectricPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
