//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The coherent photon scattering distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_COHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define FACEMC_COHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "Facemc_PhotonScatteringDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace Facemc{

//! The coherent scattering distribution class
class CoherentScatteringDistribution : public PhotonScatteringDistribution
{

public:

  //! Constructor
  CoherentPhotonScatteringDistribution( 
    const Teuchos::ArrayView<const double>& recoil_electron_momentum_squared,
    const Teuchos::ArrayView<const double>& integrated_coherent_form_factors );

  //! Destructor
  ~CoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon
  virtual void scatterPhoton( PhotonState& photon ) const;

private:

  //! The integrated coherent form factors
  Teuchos::Array<Utility::Pair<double,double> > 
  d_integrated_coherent_form_factors;
};

} // end Facemc namespace

#endif // end FACEMC_COHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_CoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
