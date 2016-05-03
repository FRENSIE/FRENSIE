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
	Teuchos::RCP<const ElectroionizationSubshellElectronScatteringDistribution>&
	  electroionization_subshell_distribution )
{
  // Subshell distribution 
  ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution
                                      subshell_distribution( number_of_tables );

  // Create the subshell distribution
  createSubshellDistribution( table_info_location,
                              table_location,
                              number_of_tables,
	                      raw_electroionization_data,
	                      subshell_distribution );
 
  electroionization_subshell_distribution.reset( 
    new ElectroionizationSubshellElectronScatteringDistribution( 
        subshell_distribution, 
        binding_energy ) );
}

// Create the scattering function
void ElectroionizationSubshellElectronScatteringDistributionACEFactory::createSubshellDistribution(
       const unsigned table_info_location,
       const unsigned table_location,
       const unsigned number_of_tables,
       const Teuchos::ArrayView<const double>& raw_electroionization_data,
       ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution&
	 subshell_distribution )
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
  
  for( unsigned n = 0; n < number_of_tables; ++n )
  {
    subshell_distribution[n].first = table_energy_grid[n];

    subshell_distribution[n].second.reset( 
      new Utility::HistogramDistribution(
        raw_electroionization_data( table_location + table_offset[n], table_length[n] ),
        raw_electroionization_data( table_location + table_offset[n] + table_length[n] + 1, 
                                    table_length[n] - 1 ),
        true ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

