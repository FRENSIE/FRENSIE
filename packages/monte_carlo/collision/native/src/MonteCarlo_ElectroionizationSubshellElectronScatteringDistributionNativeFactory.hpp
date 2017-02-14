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
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The subshell electroionization scattering distribution factory class that uses Native data
class ElectroionizationSubshellElectronScatteringDistributionNativeFactory
{

public:

  //! Create a electroionization subshell distribution
  template <typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createElectroionizationSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double binding_energy,
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const bool use_weighted_interpolation = true );

//protected:


  //! Create the electroionization subshell distribution function
  template <typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const std::vector<double> energy_grid,
    const unsigned subshell,
    std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
      subshell_distribution );
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

