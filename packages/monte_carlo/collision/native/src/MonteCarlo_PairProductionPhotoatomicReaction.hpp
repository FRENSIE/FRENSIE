//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PairProductionPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The pair production photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_HPP
#define FACEMC_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_PairProductionPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The pair production photoatomic reaction class
class PairProductionPhotoatomicReaction : public PhotoatomicReaction
{

public:

  //! Constructor
  PairProductionPhotoatomicReaction(
		const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		const Teuchos::ArrayRCP<const double>& cross_section );

  //! Destructor
  ~PairProductionPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Simulate the reaction
  void react( PhotonState& photon, ParticleBank& bank ) const;

private:
  
  // The pair production scattering distribution
  PairProductionPhotonScatteringDistribution d_scattering_distribution;	      
};

} // end MonteCarlo namespace

#endif // end FACEMC_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PairProductionPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
