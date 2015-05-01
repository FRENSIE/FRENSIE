//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution native factor decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

/*! The incoherent photon scattering distribution factory class that uses 
 * native data.
 */
class IncoherentPhotonScatteringDistributionNativeFactory : public IncoherentPhotonScatteringDistributionFactory
{

public:

  //! Create a basic incoherent distribution
  static void createIncoherentDistribution( 
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
	 incoherent_distribution,
	 const double kahn_sampling_cutoff_energy );

  //! Create an advanced Doppler broadened incoherent distribution
  static void createAdvancedDopplerBroadenedIncoherentDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
	 incoherent_distribution,
	 const double kahn_sampling_cutoff_energy );

protected:

  //! Create the scattering function
  static void createScatteringFunction( 
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const Utility::OneDDistribution>& scattering_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//
