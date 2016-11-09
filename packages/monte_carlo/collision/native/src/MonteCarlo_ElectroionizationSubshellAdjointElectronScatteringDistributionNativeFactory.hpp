//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint subshell electroionization scattering distribution native factory decl
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The subshell electroionization scattering distribution factory class that uses Native data
class ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory
{

public:

  //! Create a electroionization subshell distribution
  static void createAdjointElectroionizationSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const unsigned subshell,
    const double binding_energy,
    std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution>&
      electroionization_subshell_distribution );

//protected:


  //! Create the electroionization subshell distribution function
  static void createSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const std::vector<double> energy_grid,
    const unsigned subshell,
    std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
      subshell_distribution );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

