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
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
          electroionization_subshell_distribution,
    const unsigned subshell,
    const double evaluation_tol )
{
  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators =
    raw_electroatom_data.extractSubshellENDFDesignators();

  unsigned shell_index = 0;

  for( ; shell_index < subshell_endf_designators.size(); ++shell_index )
  {
    unsigned shell = Data::convertENDFDesignatorToSubshellEnum(
                        (unsigned)subshell_endf_designators[shell_index] );

    if ( subshell == shell )
      break;
  }

  // Extract the subshell binding energies
  Teuchos::ArrayView<const double> binding_energies =
    raw_electroatom_data.extractSubshellBindingEnergies();

  // Extract the number of subshells (N_s)
  unsigned num_subshells = subshell_endf_designators.size();

  // Extract the subshell cross sections
  Teuchos::ArrayView<const double> raw_subshell_cross_sections =
    raw_electroatom_data.extractElectroionizationSubshellCrossSections();


  // Extract the electroionization data block (EION)
  Teuchos::ArrayView<const double> eion_block(
                      raw_electroatom_data.extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = raw_electroatom_data.returnEIONLoc();

  // Extract the number of knock-on tables by subshell (N_i)
  Teuchos::Array<double> num_tables(eion_block(0,num_subshells));

  // Extract the location of info about knock-on tables by subshell
  Teuchos::Array<double> table_info(eion_block(num_subshells,num_subshells));

  // Extract the location of knock-on tables by subshell
  Teuchos::Array<double> table_loc(eion_block(2*num_subshells,num_subshells));

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[shell_index]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[shell_index]- eion_loc - 1;


  // Subshell distribution
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> subshell_distribution;

  // Create the subshell distribution
  createSubshellDistribution( subshell_info,
                              subshell_loc,
                              num_tables[shell_index],
                              raw_electroatom_data.isEPRVersion14(),
                              eion_block,
                              subshell_distribution,
                              evaluation_tol );

  electroionization_subshell_distribution.reset(
    new ElectroionizationSubshellElectronScatteringDistribution(
        subshell_distribution,
        binding_energies[shell_index],
        true,
        false ) );
}

// Create a electroionization subshell distribution
void ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
        const unsigned table_info_location,
        const unsigned table_location,
        const unsigned number_of_tables,
        const double binding_energy,
        const bool is_eprdata14,
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
                              is_eprdata14,
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
    const bool is_eprdata14,
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

  // Check if the file version is eprdata14 or eprdata12
  if ( is_eprdata14 )
  {
    // Create the scattering function with LogLogLog interp (eprdata14)
    subshell_distribution.reset(
      new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogLog>(
            function_data,
            1e-6,
            evaluation_tol ) );
  }
  else
  {
    // Create the scattering function with LinLinLin interp (eprdata12)
    subshell_distribution.reset(
      new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            function_data,
            1e-6,
            evaluation_tol ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

