//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The coherent photon scattering distribution definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CoherentPhotonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
CoherentPhotonScatteringDistribution::CoherentPhotonScatteringDistribution(
    const Teuchos::ArrayView<const double>& recoil_electron_momentum_squared,
    const Teuchos::ArrayView<const double>& integrated_coherent_form_factors )
  : d_recoil_electron_momentum_squared( recoil_electron_momentum_squared ),
    d_integrated_coherent_form_factors( integrated_coherent_form_factors )
{
  // Make sure the arrays are valid
  testPrecondition( recoil_electron_momentum_squared.size() > 0 );
  testPrecondition( integrated_coherent_form_factors.size() > 0 );
}

// Randomly scatter the photon
void CoherentPhotonScatteringDistribution::scatterPhoton( 
						    PhotonState& photon ) const
{
 
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
