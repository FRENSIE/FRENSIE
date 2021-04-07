//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution native
//!         factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionFactory.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_IncoherentAdjointModelType.hpp"
#include "MonteCarlo_ScatteringFunction.hpp"
#include "MonteCarlo_OccupationNumber.hpp"
#include "MonteCarlo_ComptonProfile.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

/*! \brief The incoherent adjoint photon scattering distribution factory class 
 * that uses native data
 */
class IncoherentAdjointPhotonScatteringDistributionNativeFactory : public IncoherentAdjointPhotonScatteringDistributionFactory
{
  // This type
  typedef IncoherentAdjointPhotonScatteringDistributionNativeFactory ThisType;

public:

  //! Create an incoherent adjoint distribution
  template<typename DataContainer>
  static void createDistribution(
                const DataContainer& data_container,
                std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
                incoherent_adjoint_distribution,
                const IncoherentAdjointModelType incoherent_adjoint_model,
                const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
                const double max_energy,
                const unsigned endf_subshell = 0u );

  //! Create a subshell distribution
  template<typename DataContainer>
  static void createSubshellDistribution(
        const DataContainer& data_container,
        std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&
        incoherent_adjoint_distribution,
        const IncoherentAdjointModelType incoherent_adjoint_model,
        const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
        const double max_energy,
        const unsigned endf_subshell );

private:

  // Create a Waller-Hartree incoherent adjoint distribution
  template<typename DataContainer>
  static void createWallerHartreeDistribution(
                const DataContainer& data_container,
                const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
                const double max_energy,
                std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
                incoherent_adjoint_distribution );

  // Create a subshell incoherent adjoint distribution
  template<typename DataContainer, typename BaseDistributionType>
  static void createSubshellDistributionImpl(
                     const DataContainer& data_container,
                     const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
                     const unsigned endf_subshell,
                     const double max_energy,
                     std::shared_ptr<BaseDistributionType>&
                     incoherent_adjoint_distribution );

  // Create a Doppler broadened subshell incoherent adjoint distribution
  template<typename DataContainer, typename BaseDistributionType>
  static void createDopplerBroadenedSubshellDistributionImpl(
                     const DataContainer& data_container,
                     const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
                     const unsigned endf_subshell,
                     const double max_energy,
                     std::shared_ptr<BaseDistributionType>&
                     incoherent_adjoint_distribution );

  // Create the scattering function
  static void createScatteringFunction(
              const Data::AdjointElectronPhotonRelaxationDataContainer&
              raw_adjoint_photoatom_data,
              std::shared_ptr<const ScatteringFunction>& scattering_function );

  // Create the scattering function
  static void createScatteringFunction(
              const Data::ElectronPhotonRelaxationDataContainer&
              raw_photoatom_data,
              std::shared_ptr<const ScatteringFunction>& scattering_function );

  // Create the occupation number
  static void createOccupationNumber(
                  const Data::AdjointElectronPhotonRelaxationDataContainer&
                  raw_adjoint_photoatom_data,
                  const unsigned endf_subshell,
                  std::shared_ptr<const OccupationNumber>& occupation_number );

  // Create the occupation number
  static void createOccupationNumber(
                  const Data::ElectronPhotonRelaxationDataContainer&
                  raw_photoatom_data,
                  const unsigned endf_subshell,
                  std::shared_ptr<const OccupationNumber>& occupation_number );

  // Create the Compton profile
  static void createComptonProfile(
                      const Data::AdjointElectronPhotonRelaxationDataContainer&
                      raw_adjoint_photoatom_data,
                      const unsigned endf_subshell,
                      std::shared_ptr<const ComptonProfile>& compton_profile );

  // Create the Compton profile
  static void createComptonProfile(
                      const Data::ElectronPhotonRelaxationDataContainer&
                      raw_adjoint_photoatom_data,
                      const unsigned endf_subshell,
                      std::shared_ptr<const ComptonProfile>& compton_profile );
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//
