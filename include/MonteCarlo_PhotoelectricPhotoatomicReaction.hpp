//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoelectricPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The pair production photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoelectricPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The pair production photoatomic reaction class
class PhotoelectricPhotoatomicReaction : public PhotoatomicReaction
{

public:

  //! Constructor
  PhotoelectricPhotoatomicReaction(
		const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		const Teuchos::ArrayRCP<const double>& cross_section );

  //! Destructor
  ~PhotoelectricPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Simulate the reaction
  void react( PhotonState& photon, ParticleBank& bank ) const;

private:
  
  // The pair production scattering distribution
  PhotoelectricPhotonScatteringDistribution d_scattering_distribution;	      
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoelectricPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
