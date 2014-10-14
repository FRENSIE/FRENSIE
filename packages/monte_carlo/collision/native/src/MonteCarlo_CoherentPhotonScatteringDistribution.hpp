//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The coherent photon scattering distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_COHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonScatteringDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

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

  // The integrated coherent form factors
  Teuchos::Array<Utility::Pair<double,double> > 
  d_integrated_coherent_form_factors;

  // The recoil electron momentum squared
  Teuchos::ArrayRCP<const double> d_recoil_electron_momentum_squared;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
