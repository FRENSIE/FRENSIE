//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentAdjointPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The coherent adjoint photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardGenericAtomicReaction.hpp"
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_CoherentScatteringDistribution.hpp"

namespace MonteCarlo{

//! The coherent adjoint photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class CoherentAdjointPhotoatomicReaction : public StandardGenericAtomicReaction<AdjointPhotoatomicReaction,InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
  typedef StandardGenericAtomicReaction<AdjointPhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic Constructor
  CoherentAdjointPhotoatomicReaction(
                   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index,
		   const std::shared_ptr<const CoherentScatteringDistribution>&
		   scattering_distribution );

  //! Constructor
  CoherentAdjointPhotoatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const std::shared_ptr<const CoherentScatteringDistribution>&
    scattering_distribution );

  //! Destructor
  ~CoherentAdjointPhotoatomicReaction()
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

  // The coherent scattering distribution
  std::shared_ptr<const CoherentScatteringDistribution> d_scattering_distribution;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CoherentAdjointPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentAdjointPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
