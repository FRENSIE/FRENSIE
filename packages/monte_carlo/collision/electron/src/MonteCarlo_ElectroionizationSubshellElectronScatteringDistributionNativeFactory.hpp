//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The subshell electroionization scattering distribution Native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The subshell electroionization scattering distribution factory class that uses Native data
class ElectroionizationSubshellElectronScatteringDistributionNativeFactory
{

public:

  //! Typedef for this type
  using ThisType = ElectroionizationSubshellElectronScatteringDistributionNativeFactory;

  //! Create a electroionization subshell distribution
  template <typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createElectroionizationSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double binding_energy,
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const double evaluation_tol = 1e-7,
    const unsigned max_number_of_iterations = 500,
    const bool renormalize_max_knock_on_energy = false );

  //! Create a electroionization subshell distribution
  template <typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createElectroionizationSubshellDistribution(
      const std::map<double,std::vector<double> >& recoil_energy_data,
      const std::map<double,std::vector<double> >& recoil_pdf_data,
      const std::vector<double> energy_grid,
      const double binding_energy,
      std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
        electroionization_subshell_distribution,
      const double evaluation_tol = 1e-7,
      const unsigned max_number_of_iterations = 500,
      const bool in_ratio_form = false,
      const bool renormalize_max_knock_on_energy = false );

//protected:

  //! Create the electroionization subshell distribution function
  template <typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createSubshellDistribution(
    const std::map<double,std::vector<double> >& recoil_energy_data,
    const std::map<double,std::vector<double> >& recoil_pdf_data,
    const std::vector<double> energy_grid,
    const double binding_energy,
    std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>&
        subshell_distribution,
    const double evaluation_tol,
    const unsigned max_number_of_iterations,
    const bool renormalize_max_knock_on_energy = false );
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

