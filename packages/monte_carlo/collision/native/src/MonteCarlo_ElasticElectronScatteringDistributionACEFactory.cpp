//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronScatteringDistributionACEFactory.hpp"
#include "Utility_TabularCDFDistribution.hpp"
#include "Utility_ElasticTwoDDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a cutoff elastic distribution
void ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::XSSEPRDataExtractor& raw_electroatom_data )
{
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function;

  ElasticElectronScatteringDistributionACEFactory::createScatteringFunction(
    raw_electroatom_data,
    scattering_function );

  cutoff_elastic_distribution.reset(
        new CutoffElasticElectronScatteringDistribution(
                scattering_function,
                true ) );
}

// Create a screened Rutherford elastic distribution
void ElasticElectronScatteringDistributionACEFactory::createScreenedRutherfordElasticDistribution(
    std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
    const unsigned atomic_number )
{
  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                atomic_number ) );
}

// Create the scattering function
/*! \details If the eprdata12 library is used the TwoDInterpPolicy will be set
 *  to LinLinLin to match MCNP6.1. If the eprdata14 library is used the
 *  TwoDInterpPolicy will be set to LogLogCosLog to match MCNP6.2.
 */
void ElasticElectronScatteringDistributionACEFactory::createScatteringFunction(
        const Data::XSSEPRDataExtractor& raw_electroatom_data,
        std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
            scattering_function )
{
  // Extract the elastic scattering information data block (ELASI)
  Teuchos::ArrayView<const double> elasi_block(
                     raw_electroatom_data.extractELASIBlock() );

  // Get the size of the angular energy grid
  int size = elasi_block.size()/3;

  // Get the distribution data
  Utility::FullyTabularTwoDDistribution::DistributionType function_data(size);

  // Extract the energy grid for elastic scattering angular distributions
  Teuchos::Array<double> angular_energy_grid(elasi_block(0,size));

  // Extract the table lengths for elastic scattering angular distributions
  Teuchos::Array<double> table_length(elasi_block(size,size));

  // Extract the offsets for elastic scattering angular distributions
  Teuchos::Array<double> offset(elasi_block(2*size,size));

  // Extract the elastic scattering angular distributions block (elas)
  Teuchos::ArrayView<const double> elas_block =
    raw_electroatom_data.extractELASBlock();

  // Check if the file version is eprdata14 or eprdata12
  if ( raw_electroatom_data.isEPRVersion14() )
  {
    for( unsigned n = 0; n < size; ++n )
    {
      function_data[n].first = angular_energy_grid[n];

      function_data[n].second.reset(
        new const Utility::TabularCDFDistribution<Utility::LogLogCos>(
          elas_block( offset[n], table_length[n] ),
          elas_block( offset[n] + table_length[n], table_length[n] ),
          true ) );
    }

    // Set the scattering function with LogLogCosLog interp (eprdata14)
    scattering_function.reset(
      new Utility::ElasticTwoDDistribution<Utility::LogLogCosLog>(
        function_data,
        0.999999 ) );
  }
  else
  {
    for( unsigned n = 0; n < size; ++n )
    {
      function_data[n].first = angular_energy_grid[n];

      function_data[n].second.reset(
        new const Utility::TabularCDFDistribution<Utility::LinLin>(
          elas_block( offset[n], table_length[n] ),
          elas_block( offset[n] + table_length[n], table_length[n] ),
          true ) );
    }

    // Set the scattering function with LinLinLin interp (eprdata12)
    scattering_function.reset(
      new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
        function_data ) );
  }

}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

