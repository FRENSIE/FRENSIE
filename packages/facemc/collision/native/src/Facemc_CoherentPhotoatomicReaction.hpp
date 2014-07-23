//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CoherentPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The incoherent photoatomic reaction class decl.
//! 
//---------------------------------------------------------------------------//

#ifndef FACEMC_COHERENT_PHOTOATOMIC_REACTION_HPP
#define FACEMC_COHERENT_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_PhotoatomicReaction.hpp"
#include "Facemc_CoherentPhotonScatteringDistribution.hpp"

namespace Facemc{

//! The incoherent photoatomic reaction class
class CoherentPhotoatomicReaction : public PhotoatomicReaction
{

public:

  //! Constructor
  CoherentPhotoatomicReaction( 
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const Teuchos::ArrayView<const double>& recoil_electron_momentum_squared,
      const Tuechos::ArrayView<const double>& integrated_coherent_form_factors,
      const CoherentPhotonScatteringDistribution::ElectronMomentumDistArray&
      electron_momentum_dist_array );

  //! Destructor
  virtual ~CoherentPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Simulate the reaction
  void react( PhotonState& photon, ParticleBank& bank ) const;

private:

  // The incoherent scattering distribution
  CoherentPhotonScatteringDistribution d_scattering_distribution;
};

} // end Facemc namespace

#endif // end FACEMC_COHERENT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_CoherentPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
