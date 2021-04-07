//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp
//! \author Luke Kersting
//! \brief  The subshell electroionization scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_ArrayView.hpp"

namespace MonteCarlo{

//! The subshell electroionization scattering distribution factory class that uses ACE data
class ElectroionizationSubshellElectronScatteringDistributionACEFactory
{

public:

  //! Create a electroionization subshell distribution
  static void createElectroionizationSubshellDistribution(
    const unsigned table_info_location,
    const unsigned table_location,
    const unsigned number_of_tables,
    const double binding_energy,
    const bool is_eprdata14,
    const Utility::ArrayView<const double>& raw_electroionization_data,
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const double evaluation_tol = 1e-7 );

  //! Create a electroionization subshell distribution
  static void createElectroionizationSubshellDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const unsigned subshell,
    const double evaluation_tol = 1e-7 );

protected:

  //! Create the electroionization subshell distribution function
  static void createSubshellDistribution(
    const unsigned table_info_location,
    const unsigned table_location,
    const unsigned number_of_tables,
    const bool is_eprdata14,
    const Utility::ArrayView<const double>& raw_electroionization_data,
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
      subshell_distribution,
    const double evaluation_tol = 1e-7 );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

