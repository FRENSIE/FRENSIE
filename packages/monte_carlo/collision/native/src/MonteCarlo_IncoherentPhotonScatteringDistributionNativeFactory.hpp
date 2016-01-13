//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution native factor decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistributionFactory.hpp"
#include "MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ScatteringFunction.hpp"
#include "MonteCarlo_IncoherentModelType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

/*! The incoherent photon scattering distribution factory class that uses 
 * native data.
 */
class IncoherentPhotonScatteringDistributionNativeFactory : public IncoherentPhotonScatteringDistributionFactory
{

public:

  //! Create an incoherent distribution
  static void createDistribution( 
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
	 incoherent_distribution,
	 const IncoherentModelType incoherent_model,
	 const double kahn_sampling_cutoff_energy,
	 const unsigned endf_subshell = 0u );

protected:

  //! Create a Waller-Hartree incoherent distribution
  static void createWallerHartreeDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
	 incoherent_distribution,
	 const double kahn_sampling_cutoff_energy );			       
  
  //! Create a Doppler broadened hybrid incoherent distribution
  static void createDopplerBroadenedHybridDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
    const std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
    doppler_broadened_dist,
    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
    incoherent_distribution,     
    const double kahn_sampling_cutoff_energy );

  //! Create a subshell incohrent distribution
  static void createSubshellDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const unsigned endf_subshell,
	 Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
	 incoherent_distribution,
	 const double kahn_sampling_cutoff_energy );
  
  //! Create a Doppler broadened subshell incoherent distribution
  static void createDopplerBroadenedSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
    const unsigned endf_subshell,
    const std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution>&
    doppler_broadened_dist,
    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
    incoherent_distribution,
    const double kahn_sampling_cutoff_energy );

private:
  
  //! Create the scattering function
  static void createScatteringFunction( 
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       std::shared_ptr<const ScatteringFunction>& scattering_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//
