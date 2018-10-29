//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint subshell electroionization scattering distribution native factory decl
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The subshell electroionization scattering distribution factory class that uses Native data
class ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory
{

  using ThisType = ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory;

public:

  //! Create a electroionization subshell distribution
  template <typename TwoDInterpPolicy = Utility::LogLogLog, template<typename> class TwoDGridPolicy = Utility::UnitBase>
  static void createElectroionizationSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const unsigned subshell,
    const double binding_energy,
    std::shared_ptr<ElectroionizationSubshellAdjointElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const double evaluation_tol );

//protected:


  //! Create the electroionization subshell distribution function
  template <typename TwoDInterpPolicy = Utility::LogLogLog, template<typename> class TwoDGridPolicy = Utility::UnitBase>
  static void createSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const std::vector<double> energy_grid,
    const unsigned subshell,
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
      subshell_distribution,
    const double evaluation_tol );
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

