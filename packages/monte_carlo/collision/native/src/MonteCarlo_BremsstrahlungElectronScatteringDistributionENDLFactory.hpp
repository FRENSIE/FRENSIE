//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistributionENDLFactory.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung scattering distribution ENDL factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_ENDL_FACTORY_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_ENDL_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Data_ENDLDataContainer.hpp"

namespace MonteCarlo{

//! The bremsstrahlung scattering distribution factory class that uses ENDL data
class BremsstrahlungElectronScatteringDistributionENDLFactory
{

public:

  //! Create a simple dipole bremsstrahlung distribution
  static void createBremsstrahlungDistribution(
	const Data::ENDLDataContainer& raw_electroatom_data,
    const std::vector<double>& bremsstrahlung_energy_grid,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
		        	  scattering_distribution );

  //! Create a detailed 2BS bremsstrahlung distribution
  static void createBremsstrahlungDistribution(
	const Data::ENDLDataContainer& raw_electroatom_data,
    const std::vector<double>& bremsstrahlung_energy_grid,
	std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const int atomic_number );

  //! Create the energy loss function
  static void createEnergyLossFunction(
	const Data::ENDLDataContainer& raw_electroatom_data,
    const std::vector<double>& bremsstrahlung_energy_grid,
    BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution&
        energy_loss_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG__ELECTRON_SCATTERING_DISTRIBUTION_ENDL_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionENDLFactory.hpp
//---------------------------------------------------------------------------//

