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
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonScatteringDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The coherent scattering distribution class
class CoherentPhotonScatteringDistribution : public PhotonScatteringDistribution
{

public:

  //! Constructor
  CoherentPhotonScatteringDistribution(
  const Teuchos::RCP<Utility::OneDDistribution>& form_factor_function_squared );

  //! Destructor
  ~CoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon
  virtual void scatterPhoton( PhotonState& photon ) const;

private:

  // The coherent form factor function squared
  Teuchos::RCP<Utility::OneDDistribution> d_form_factor_function_squared;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
