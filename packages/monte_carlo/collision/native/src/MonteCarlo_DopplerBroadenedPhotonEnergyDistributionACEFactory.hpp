//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened photon energy distribution ACE factory decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

/*! The Doppler broadened photon energy distribution factory class that uses
 * ACE data
 */
class DopplerBroadenedPhotonEnergyDistributionACEFactory
{

public:

  //! Create the subshell order array
  static void createSubshellOrderArray(
			   const Data::XSSEPRDataExtractor& raw_photoatom_data,
			   Teuchos::Array<SubshellType>& subshell_order );

  //! Create a coupled complete Doppler broadened photon energy dist
  static void createCoupledCompleteDistribution(
	       const Data::XSSEPRDataExtractor& raw_photoatom_data,
	       std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
	       doppler_broadened_dist,
	       const bool use_full_profile );

  //! Create a coupled complete Doppler broadened photon energy dist
  static void createCoupledCompleteDistribution(
       const Data::XSSEPRDataExtractor& raw_photoatom_data,
       std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
       doppler_broadened_dist,
       const bool use_full_profile );

  //! Create a decoupled complete Doppler broadened photon energy dist
  static void createDecoupledCompleteDistribution(
	       const Data::XSSEPRDataExtractor& raw_photoatom_data,
	       std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
	       doppler_broadened_dist,
	       const bool use_full_profile );

  //! Create a decoupled complete Doppler broadened photon energy dist
  static void createDecoupledCompleteDistribution(
       const Data::XSSEPRDataExtractor& raw_photoatom_data,
       std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
       doppler_broadened_dist,
       const bool use_full_profile );

  //! Create a subshell Doppler broadened photon energy dist
  static void createSubshellDistribution(
	       const Data::XSSEPRDataExtractor& raw_photoatom_data,
	       const unsigned endf_subshell,
	       std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
	       doppler_broadened_dist,
	       const bool use_full_profile );

  //! Create a subshell Doppler broadened photon energy dist
  static void createSubshellDistribution(
       const Data::XSSEPRDataExtractor& raw_photoatom_data,
       const unsigned endf_subshell,
       std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution>&
       doppler_broadened_dist,
       const bool use_full_profile );

private:

  //! Create the Compton profile distribution
  static void createComptonProfileDistArray(
      const Data::XSSEPRDataExtractor& raw_photoatom_data,
      const bool use_full_profile,
      DopplerBroadenedPhotonEnergyDistribution::ElectronMomentumDistArray&
      compton_profiles );

  //! Create the Compton profile distribution
  static void createComptonProfileDist(
		 Teuchos::Array<double>& raw_half_momentum_grid,
                 Teuchos::Array<double>& raw_half_profile,
                 const bool use_full_profile,
                 std::shared_ptr<const ComptonProfile>& compton_profile );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
