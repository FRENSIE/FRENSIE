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

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionFactory.hpp"
#include "MonteCarlo_IncoherentAdjointModelType.hpp"
#include "MonteCarlo_ScatteringFunction.hpp"
#include "MonteCarlo_OccupationNumber.hpp"
#include "MonteCarlo_ComptonProfile.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

/*! \brief The incoherent adjoint photon scattering distribution factory class 
 * that uses native data
 */
class IncoherentAdjointPhotonScatteringDistributionNativeFactory : public IncoherentAdjointPhotonScatteringDistributionFactory
{

private:

  // This type
  typedef IncoherentAdjointPhotonScatteringDistributionNativeFactory ThisType;

public:

  //! Create an incoherent adjoint distribution
  static void createDistribution(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
          incoherent_adjoint_distribution,
          const IncoherentAdjointModelType incoherent_adjoint_model,
          const double max_energy,
          const unsigned endf_subshell = 0u );

  //! Create an incoherent adjoint distribution
  static void createDistribution(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
          incoherent_adjoint_distribution,
          const IncoherentAdjointModelType incoherent_adjoint_model,
          const double max_energy,
          const Teuchos::ArrayRCP<const double>& critical_line_energies,
          const unsigned endf_subshell = 0 );

private:

  //! Create a Waller-Hartree incoherent adjoint distribution
  static void createWallerHartreeDistribution(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          const double max_energy,
          std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
          incoherent_adjoint_distribution );

  //! Create a subshell incoherent adjoint distribution
  static void createSubshellDistribution(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          const unsigned endf_subshell,
          const double max_energy,
          std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
          incoherent_adjoint_distribution );

  //! Create a Doppler broadened subshell incoherent adjoint distribution
  static void createDopplerBroadenedSubshellDistribution(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          const unsigned endf_subshell,
          const double max_energy,
          std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
          incoherent_adjoint_distribution );

private:

  //! Create the scattering function
  static void createScatteringFunction(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          std::shared_ptr<const ScatteringFunction>& scattering_function );

  //! Create the occupation number
  static void createOccupationNumber(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          const unsigned endf_subshell,
          std::shared_ptr<const OccupationNumber>& occupation_number );

  //! Create the Compton profile
  static void createComptonProfile(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          const unsigned endf_subshell,
          std::shared_ptr<const ComptonProfile>& compton_profile );
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//
