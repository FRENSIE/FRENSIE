//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The electroionization subshell scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp"
#include "Utility_TabularCDFDistribution.hpp"
#include "Utility_Vector.hpp"
#include "Utility_DesignByContract.hpp"

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
  Utility::ArrayView<const double> subshell_endf_designators =
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
  Utility::ArrayView<const double> binding_energies =
    raw_electroatom_data.extractSubshellBindingEnergies();

  // Extract the number of subshells (N_s)
  unsigned num_subshells = subshell_endf_designators.size();

  // Extract the subshell cross sections
  Utility::ArrayView<const double> raw_subshell_cross_sections =
    raw_electroatom_data.extractElectroionizationSubshellCrossSections();


  // Extract the electroionization data block (EION)
  Utility::ArrayView<const double> eion_block(
                      raw_electroatom_data.extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = raw_electroatom_data.returnEIONLoc();

  // Extract the number of knock-on tables by subshell (N_i)
  std::vector<double> num_tables(eion_block(0,num_subshells));

  // Extract the location of info about knock-on tables by subshell
  std::vector<double> table_info(eion_block(num_subshells,num_subshells));

  // Extract the location of knock-on tables by subshell
  std::vector<double> table_loc(eion_block(2*num_subshells,num_subshells));

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[shell_index]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[shell_index]- eion_loc - 1;


  // Subshell distribution
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution;

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
        KNOCK_ON_SAMPLING,
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
        const Utility::ArrayView<const double>& raw_electroionization_data,
        std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
          electroionization_subshell_distribution,
        const double evaluation_tol )
{
  // Subshell distribution
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution;

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
        KNOCK_ON_SAMPLING,
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
    const Utility::ArrayView<const double>& raw_electroionization_data,
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
            subshell_distribution,
    const double evaluation_tol )
{
  // Extract the energies for which knock-on sampling tables are given
  std::vector<double> table_energy_grid( raw_electroionization_data(
                                            table_info_location,
                                            number_of_tables ) );

  // Extract the length of the knock-on sampling tables
  std::vector<double> table_length( raw_electroionization_data(
                                       table_info_location + number_of_tables,
                                       number_of_tables ) );

  // Extract the offset of the knock-on sampling tables
  std::vector<double> table_offset( raw_electroionization_data(
                                       table_info_location + 2*number_of_tables,
                                       number_of_tables ) );

  // Create the scattering function
  std::vector<double> primary_grid( number_of_tables );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( number_of_tables );

  // Check if the file version is eprdata14 or eprdata12
  if ( is_eprdata14 )
  {
    for( size_t n = 0; n < number_of_tables; ++n )
    {
      primary_grid[n] = table_energy_grid[n];

      secondary_dists[n].reset(
        new Utility::TabularCDFDistribution<Utility::LogLog>(
          raw_electroionization_data( table_location + table_offset[n], table_length[n] ),
          raw_electroionization_data( table_location + table_offset[n] + table_length[n],
                                      table_length[n] ),
          true ) );
    }

    // Create the scattering function with LogLogLog interp (eprdata14)
    subshell_distribution.reset(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Correlated<Utility::LogLogLog> >(
                                                    primary_grid,
                                                    secondary_dists,
                                                    1e-6,
                                                    evaluation_tol ) );
  }
  else
  {
    for( size_t n = 0; n < number_of_tables; ++n )
    {
      primary_grid[n] = table_energy_grid[n];

      secondary_dists[n].reset(
        new Utility::TabularCDFDistribution<Utility::LinLin>(
          raw_electroionization_data( table_location + table_offset[n], table_length[n] ),
          raw_electroionization_data( table_location + table_offset[n] + table_length[n],
                                      table_length[n] ),
          true ) );
    }
    // Create the scattering function with LinLinLin interp (eprdata12)
    subshell_distribution.reset(
      new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLin> >(
                                                        primary_grid,
                                                        secondary_dists,
                                                        1e-6,
                                                        evaluation_tol ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

