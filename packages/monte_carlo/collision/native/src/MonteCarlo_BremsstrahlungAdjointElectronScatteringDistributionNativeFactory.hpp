//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung adjoint scattering distribution native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The bremsstrahlung adjoint distribution factory class that uses Native data
class BremsstrahlungAdjointElectronScatteringDistributionNativeFactory
{

public:

  //! Create a bremsstrahlung adjoint distribution
  template <typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createBremsstrahlungAdjointDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double>& adjoint_energy_grid,
    std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution>&
        scattering_distribution,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol = 1e-7 );

  //! Create the energy gain function
  template <typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createEnergyGainFunction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double> adjoint_energy_grid,
    std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
        energy_gain_function,
    const double evaluation_tol = 1e-7 );
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

