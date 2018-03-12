//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung scattering distribution native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The bremsstrahlung scattering distribution factory class that uses Native data
class BremsstrahlungElectronScatteringDistributionNativeFactory
{

public:

  //! Typedef for this type
  using ThisType = BremsstrahlungElectronScatteringDistributionNativeFactory;

  //! Create a simple dipole bremsstrahlung distribution
  template <typename TwoDGridPolicy = Utility::UnitBase<Utility::LogLogLog> >
  static void createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const std::vector<double>& bremsstrahlung_energy_grid,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol = 1e-7 );

  //! Create a simple dipole bremsstrahlung distribution
  template<typename TwoDGridPolicy = Utility::UnitBaseCorrelated<Utility::LogLogLog> >
  static void createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol = 1e-7 );

  //! Create a detailed 2BS bremsstrahlung distribution
  template<typename TwoDGridPolicy = Utility::UnitBaseCorrelated<Utility::LogLogLog> >
  static void createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const int atomic_number,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol = 1e-7 );

  //! Create a detailed 2BS bremsstrahlung distribution
  template<typename TwoDGridPolicy = Utility::UnitBaseCorrelated<Utility::LogLogLog> >
  static void createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const int atomic_number,
    const std::vector<double>& bremsstrahlung_energy_grid,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol = 1e-7 );

  //! Create the energy loss function
  template<typename TwoDGridPolicy = Utility::UnitBaseCorrelated<Utility::LogLogLog> >
  static void createEnergyLossFunction(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const std::vector<double> bremsstrahlung_energy_grid,
    std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
        energy_loss_function,
    const double evaluation_tol = 1e-7 );

};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

