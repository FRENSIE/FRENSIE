//---------------------------------------------------------------------------//
//!
//! \file   Facemc_IncoherentPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The incoherent photoatomic reaction class decl.
//! 
//---------------------------------------------------------------------------//

#ifndef FACEMC_INCOHERENT_PHOTOATOMIC_REACTION_HPP
#define FACEMC_INCOHERENT_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_PhotoatomicReaction.hpp"
#include "Facemc_IncoherentPhotonScatteringDistribution.hpp"

namespace Facemc{

//! The incoherent photoatomic reaction class
class IncoherentPhotoatomicReaction : public PhotoatomicReaction
{

public:

  //! Constructor
  IncoherentPhotoatomicReaction( 
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const Teuchos::ArrayView<const double>& recoil_electron_momentum,
       const Tuechos::ArrayView<const double>& scattering_function,
       const IncoherentPhotonScatteringDistribution::ElectronMomentumDistArray&
       electron_momentum_dist_array );

  //! Destructor
  virtual ~IncoherentPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Simulate the reaction
  void react( PhotonState& photon, ParticleBank& bank ) const;

private:

  // The incoherent scattering distribution
  IncoherentPhotonScatteringDistribution d_scattering_distribution;
};

} // end Facemc namespace

#endif // end FACEMC_INCOHERENT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_IncoherentPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
