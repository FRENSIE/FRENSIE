//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoelectricPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The subshell photoelectric photoatomic reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"

namespace MonteCarlo{

//! The subshell photoelectric photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class SubshellPhotoelectricPhotoatomicReaction : public PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>
{

 public:

  //! Basic constructor
  SubshellPhotoelectricPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const Data::SubshellType interaction_subshell,
       const double binding_energy );

  //! Constructor
  SubshellPhotoelectricPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const Data::SubshellType interaction_subshell,
    const double binding_energy );

  //! Destructor
  ~SubshellPhotoelectricPhotoatomicReaction()
  { /* ... */ }

  //! Return the reaction type
  PhotoatomicReactionType getReactionType() const override;

  //! Get the interaction subshell (non-standard interface)
  Data::SubshellType getSubshell() const;

  //! Get the subshell binding energy (non-standard interface)
  double getSubshellBindingEnergy() const;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Simulate the reaction
  void react( PhotonState& photon,
	      ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const override;

private:

  // The interaction subshell
  Data::SubshellType d_interaction_subshell;

  // The subshell binding energy
  double d_binding_energy;

  // The reaction type
  PhotoatomicReactionType d_reaction_type;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_SubshellPhotoelectricPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellPhotoelectricPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
