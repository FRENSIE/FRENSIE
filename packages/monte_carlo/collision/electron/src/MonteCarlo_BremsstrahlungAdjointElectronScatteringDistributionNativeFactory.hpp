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
  template <typename TwoDInterpPolicy = Utility::LogLogLog, template<typename> class TwoDGridPolicy = Utility::UnitBase>
  static void createBremsstrahlungDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double>& adjoint_energy_grid,
    std::shared_ptr<BremsstrahlungAdjointElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol = 1e-7 );

  //! Create the energy gain function
  template <typename TwoDInterpPolicy = Utility::LogLogLog, template<typename> class TwoDGridPolicy = Utility::UnitBase>
  static void createEnergyGainFunction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double> adjoint_energy_grid,
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
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

