//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The incoherent photoatomic reaction class decl.
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardPhotoatomicReaction.hpp"
#include "MonteCarlo_CoherentScatteringDistribution.hpp"

namespace MonteCarlo{

//! The coherent photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class CoherentPhotoatomicReaction : public StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Basic Constructor
  CoherentPhotoatomicReaction( 
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index,
		   const Teuchos::RCP<const CoherentScatteringDistribution>&
		   scattering_distribution );

  //! Constructor
  CoherentPhotoatomicReaction( 
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const Teuchos::RCP<const CoherentScatteringDistribution>&
       scattering_distribution );

  //! Destructor
  virtual ~CoherentPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the reaction type
  PhotoatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( PhotonState& photon, 
	      ParticleBank& bank,
	      SubshellType& shell_of_interaction ) const;

private:

  // The coherent scattering distribution
  Teuchos::RCP<const CoherentScatteringDistribution> d_scattering_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CoherentPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
