//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The electroionization subshell scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a electroionization subshell distribution
void ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
        const unsigned table_info_location,
        const unsigned table_location,
        const unsigned number_of_tables,
        const double binding_energy,
        const Teuchos::ArrayView<const double>& raw_electroionization_data,
        std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
          electroionization_subshell_distribution,
        const double evaluation_tol )
{
  // Subshell distribution
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> subshell_distribution;

  // Create the subshell distribution
  createSubshellDistribution( table_info_location,
                              table_location,
                              number_of_tables,
                              raw_electroionization_data,
                              subshell_distribution,
                              evaluation_tol );

  electroionization_subshell_distribution.reset(
    new ElectroionizationSubshellElectronScatteringDistribution(
        subshell_distribution,
        binding_energy,
        true,
        false ) );
}

// Create the scattering function
void ElectroionizationSubshellElectronScatteringDistributionACEFactory::createSubshellDistribution(
    const unsigned table_info_location,
    const unsigned table_location,
    const unsigned number_of_tables,
    const Teuchos::ArrayView<const double>& raw_electroionization_data,
    std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
            subshell_distribution,
    const double evaluation_tol )
{
  // Extract the energies for which knock-on sampling tables are given
  Teuchos::Array<double> table_energy_grid( raw_electroionization_data(
                                         table_info_location,
                                         number_of_tables ) );

  // Extract the length of the knock-on sampling tables
  Teuchos::Array<double> table_length( raw_electroionization_data(
                                    table_info_location + number_of_tables,
                                    number_of_tables ) );

  // Extract the offset of the knock-on sampling tables
  Teuchos::Array<double> table_offset( raw_electroionization_data(
                                    table_info_location + 2*number_of_tables,
                                    number_of_tables ) );

  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType
     function_data( number_of_tables );

  for( unsigned n = 0; n < number_of_tables; ++n )
  {
    function_data[n].first = table_energy_grid[n];

    function_data[n].second.reset(
      new Utility::HistogramDistribution(
        raw_electroionization_data( table_location + table_offset[n], table_length[n] ),
        raw_electroionization_data( table_location + table_offset[n] + table_length[n] + 1,
                                    table_length[n] - 1 ),
        true ) );
  }

  // Create the scattering function
  subshell_distribution.reset(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            function_data,
            1e-6,
            evaluation_tol ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

