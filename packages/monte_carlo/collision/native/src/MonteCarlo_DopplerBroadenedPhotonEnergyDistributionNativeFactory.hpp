//---------------------------------------------------------------------------//
//!
//! \file  MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened photon energy dist. native factory decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

/*! The Doppler broadened photon energy distribution factory class that uses
 * Native data
 */
class DopplerBroadenedPhotonEnergyDistributionNativeFactory
{

public:

  //! Create a coupled complete Doppler broadened photon energy dist
  static void createCoupledCompleteDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
	 doppler_broadened_dist );

  //! Create a coupled complete Doppler broadened photon energy dist
  static void createCoupledCompleteDistribution(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
       doppler_broadened_dist );
  
  //! Create a subshell Doppler broadened photon energy dist
  static void createSubshellDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const unsigned endf_subshell,
	 std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
	 doppler_broadened_dist );

  //! Create a subshell Doppler broadened photon energy dist
  static void createSubshellDistribution(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const unsigned endf_subshell,
       std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution>&
       doppler_broadened_dist );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//
