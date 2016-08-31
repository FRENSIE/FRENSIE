//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The subshell electroionization scattering distribution Native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// FRENSIE Includes
//#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The subshell electroionization scattering distribution factory class that uses Native data
class ElectroionizationSubshellElectronScatteringDistributionNativeFactory //: public ElectroionizationSubshellElectronScatteringDistributionFactory
{

public:

  //! Create a electroionization subshell distribution
  static void createElectroionizationSubshellDistribution(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const unsigned subshell,
    const double binding_energy,
	std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
	  electroionization_subshell_distribution );

//protected:


  //! Create the electroionization subshell distribution function
  static void createSubshellDistribution(
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const std::vector<double> energy_grid,
    const unsigned subshell,
    ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution&
	 subshell_distribution );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

