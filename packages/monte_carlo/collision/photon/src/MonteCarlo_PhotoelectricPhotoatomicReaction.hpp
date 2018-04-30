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
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"

namespace MonteCarlo{

/*! The photoelectric photoatomic reaction class
 * \details This class should be used to represent the total photoelectric
 * reaction and not the reaction with individual subshells.
 */
template<typename InterpPolicy, bool processed_cross_section = true>
class PhotoelectricPhotoatomicReaction : public StandardReactionBaseImpl<PhotoatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<PhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic constructor
  PhotoelectricPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index );

  //! Constructor
  PhotoelectricPhotoatomicReaction(
     const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
     const std::shared_ptr<const std::vector<double> >& cross_section,
     const size_t threshold_energy_index,
     const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher );

  //! Destructor
  ~PhotoelectricPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const override;

  //! Return the number of electrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const override;

  //! Return the reaction type
  PhotoatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  virtual void react( PhotonState& photon,
		      ParticleBank& bank,
		      Data::SubshellType& shell_of_interaction ) const override;
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
