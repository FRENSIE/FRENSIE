//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The subshell incoherent photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardPhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The subshell incoherent photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class SubshellIncoherentPhotoatomicReaction : public StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Basic constructor without Doppler broadening
  SubshellIncoherentPhotoatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const SubshellType interaction_subshell,
      const double binding_energy,
      const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number );

  //! Constructor without Doppler broadening
  SubshellIncoherentPhotoatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const SubshellType interaction_subshell,
      const double binding_energy,
      const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number );

  //! Basic constructor for Doppler broadening
  SubshellIncoherentPhotoatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const SubshellType interaction_subshell,
      const double binding_energy,
      const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number,
      const Teuchos::RCP<const Utility::OneDDistribution>& compton_profile );

  //! Constructor for Doppler broadening
  SubshellIncoherentPhotoatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const SubshellType interaction_subshell,
      const double binding_energy,
      const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number,
      const Teuchos::RCP<const Utility::OneDDistribution>& compton_profile );

  //! Destructor
  ~SubshellIncoherentPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  PhotoatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( PhotonState& photon, 
	      ParticleBank& bank,
	      SubshellType& shell_of_interaction ) const;

  //! Get the interaction subshell (non-standard interface)
  SubshellType getSubshell() const;

  //! Get the subshell binding energy (non-standard interface)
  double getSubshellBindingEnergy() const;

private:

  // The incoherent scattering distribution
  SubshellIncoherentPhotonScatteringDistribution d_scattering_distribution;
  
  // The reaction type
  PhotoatomicReactionType d_reaction_type;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_SubshellIncoherentPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end SubshellIncoherentPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
