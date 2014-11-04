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

  //! Constructor
  SubshellPhotoelectricPhotoatomicReaction(
                const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		const Teuchos::ArrayRCP<const double>& cross_section,
		const unsigned threshold_energy_index,
		const SubshellType interaction_subshell,
		const double binding_energy );

  //! Destructor
  ~SubshellPhotoelectricPhotoatomicReaction()
  { /* ... */ }

  //! Simulate the reaction
  void react( PhotonState& photon,
	      ParticleBank& bank,
	      SubshellType& shell_of_interaction ) const;

  //! Get the interaction subshell (non-standard interface)
  SubshellType getSubshell() const;

  //! Get the subshell binding energy (non-standard interface)
  double getSubshellBindingEnergy() const;

private:

  // The interaction subshell
  SubshellType d_interaction_subshell;	

  // The subshell binding energy
  double d_binding_energy;
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
