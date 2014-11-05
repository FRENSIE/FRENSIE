//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The incoherent photoatomic reaction class decl.
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_INCOHERENT_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The incoherent photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class IncoherentPhotoatomicReaction : public StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Constructor without doppler broadening
  IncoherentPhotoatomicReaction( 
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cross_section,
	  const unsigned threshold_energy_index,
          const Teuchos::RCP<Utility::OneDDistribution>& scattering_function );
 
  //! Constructor for doppler broadening
  IncoherentPhotoatomicReaction( 
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<Utility::OneDDistribution>& scattering_function,
       const Teuchos::Array<double>& subshell_binding_energies,
       const Teuchos::Array<double>& subshell_occupancies,
       const Teuchos::Array<SubshellType>& subshell_order,
       const Teuchos::RCP<ComptonProfileSubshellConverter>& subshell_converter,
       const IncoherentPhotonScatteringDistribution::ElectronMomentumDistArray&
       electron_momentum_dist_array );

  //! Destructor
  virtual ~IncoherentPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  PhotoatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( PhotonState& photon, 
	      ParticleBank& bank,
	      SubshellType& shell_of_interaction ) const;

private:

  // The incoherent scattering distribution
  IncoherentPhotonScatteringDistribution d_scattering_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_IncoherentPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_INCOHERENT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
