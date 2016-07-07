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
class BremsstrahlungElectronScatteringDistributionNativeFactory //: public BremsstrahlungElectronScatteringDistributionFactory
{

public:

  //! Create a simple dipole bremsstrahlung distribution
  static void createBremsstrahlungDistribution(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
		        	  scattering_distribution );

  //! Create a detailed 2BS bremsstrahlung distribution
  static void createBremsstrahlungDistribution(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const int atomic_number );

  //! Create the energy loss function
  static void createEnergyLossFunction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::vector<double> energy_grid,
    BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution&
        energy_loss_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG__ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

